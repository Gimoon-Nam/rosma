// 20200804남기문 퍼즐.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include<Bangtal.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#pragma comment(lib,"Bangtal.lib")

SceneID start, title;
ObjectID 완성본, startButton, endButton, restartButton, p1;
//조각1, 조각2, 조각3, 조각4, 조각5, 조각6, 조각7, 조각8, 조각9,
ObjectID 조각[9], piece_pos[9];
SoundID 퀴즈, 해결, BGM, Intro;
EventID d;
TimerID 퍼즐;

#define _MAX 9
const int nMAX = 9;

void BubbleSort(int* nArr, int nArrSize);

char isValid() {
	int err = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = i + 1; j < 8; j++) {
			if (piece_pos[i] > piece_pos[j]) {
				err++;
			}
		}
	}
	return err % 2 == 0;

}


int X[3] = { 250, 422, 594 };
int Y[3] = { 500, 328, 156 };



TimerID createTimer(Second second, bool timershown) {

	TimerID timer = createTimer(second);
	if (timershown == true) {
		showTimer(timer);
	}
	return timer;

}

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(name, image);
	locateObject(object, scene, x, y);
	if (shown == true) {
		showObject(object);
	}

	return object;

}


SoundID createSound(const wchar_t* sound, bool soundplay) {

	SoundID soundname = createSound(sound);
	if (soundplay == true) {
		playSound(soundname);
	}
	return soundname;
}



void showImageMessage(const wchar_t* image, const wchar_t* message) {
	showImageViewer(image);
	showMessage(message);
}

bool closed1 = true, closed2 = true, closed3 = true, locked = true, locked2 = true, power = true, closedbox = true, closed5 = true;

/*void timerCallback(TimerID timer) {
	if (timer == 퍼즐) {
		increaseTimer(퍼즐, 3600.0f);
	}
}*/

void sceneCallback(SceneID scene, EventID event)
{
	if (scene == title) {
		if (event == EVENT_ENTER_SCENE) {
			//변수 생성 및 초기화 부분
			srand((unsigned)time(NULL));

			bool Check[9] = { false, };


			do {
				for (int i = 0; i < nMAX; i++) {
					Check[i] = false;
				}
				for (int i = 0; i < nMAX - 1; )
				{
					int nTemp = rand() % 8;

					if (Check[nTemp] == false)
					{
						Check[nTemp] = true;
						piece_pos[i] = nTemp;
						++i;
					}
				}
				piece_pos[8] = 8;
			} while (!isValid());
			for (int i = 0; i < nMAX; i++) {
				locateObject(조각[piece_pos[i]], title, X[i % 3], Y[i / 3]);
			}
			playSound(BGM);
			setTimer(퍼즐, 3600.0f);
			startTimer(퍼즐);
		}
		else if (event == EVENT_LEAVE_SCENE)
			stopSound(BGM);
	}
}
char isFinished() {
	for (int i = 0; i < 9; i++) {
		if (piece_pos[i] != i) {
			return 0;
		}
	}
	return 1;
}

void mouseCallback(ObjectID object, int x_pos, int y_pos, MouseAction action) {

	if (object == startButton) {
		enterScene(title);
		return;
	}
	else if (object == endButton) {
		endGame();
		return;
	}
	else if (object == restartButton) {
		enterScene(title);
		return;
	}


	int i;
	for (i = 0; i < nMAX; i++) {
		if (조각[piece_pos[i]] == object) {
			break;
		}
	}


	char up, down, left, right;
	int x = i % 3, y = i / 3;

	if (x == 0) {
		left = 0;
	}
	else {
		left = 1;
	}

	if (x == 2) {
		right = 0;
	}
	else {
		right = 1;
	}

	if (y == 0) {
		up = 0;
	}
	else {
		up = 1;
	}

	if (y == 2) {
		down = 0;
	}
	else {
		down = 1;
	}

	if (up) {
		if (
			piece_pos[i - 3] == 8) {
			piece_pos[i - 3] = piece_pos[i];
			piece_pos[i] = 8;

			locateObject(조각[piece_pos[i - 3]], title, X[(i - 3) % 3], Y[(i - 3) / 3]);
			locateObject(조각[piece_pos[i]], title, X[i % 3], Y[i / 3]);


			if (isFinished()) {
				enterScene(start);
				hideObject(startButton);
				showObject(restartButton);
				//stopTimer(퍼즐);
				//getTimer(퍼즐);
				float a = 3600 - getTimer(퍼즐);
				char message[20];
				sprintf_s(message, "클리어! %2.f초", a);
				showMessage(message);
			}
			return;

		}
	}

	if (down) {
		if (piece_pos[i + 3] == 8) {
			piece_pos[i + 3] = piece_pos[i];
			piece_pos[i] = 8;

			locateObject(조각[piece_pos[i + 3]], title, X[(i + 3) % 3], Y[(i + 3) / 3]);
			locateObject(조각[piece_pos[i]], title, X[i % 3], Y[i / 3]);


			if (isFinished()) {
				enterScene(start);
				hideObject(startButton);
				showObject(restartButton);
				//stopTimer(퍼즐);
				//getTimer(퍼즐);
				float a = 3600 - getTimer(퍼즐);
				char message[20];
				sprintf_s(message, "클리어! %2.f초", a);
				showMessage(message);
			}
			return;
		}
	}

	if (left) {
		if (piece_pos[i - 1] == 8) {
			piece_pos[i - 1] = piece_pos[i];
			piece_pos[i] = 8;

			locateObject(조각[piece_pos[i - 1]], title, X[(i - 1) % 3], Y[(i - 1) / 3]);
			locateObject(조각[piece_pos[i]], title, X[i % 3], Y[i / 3]);


			if (isFinished()) {
				enterScene(start);
				hideObject(startButton);
				showObject(restartButton);
				//stopTimer(퍼즐);
				//getTimer(퍼즐);
				float a = 3600 - getTimer(퍼즐);
				char message[20];
				sprintf_s(message, "클리어! %2.f초", a);
				showMessage(message);
			}
			return;
		}
	}

	if (right) {
		if (piece_pos[i + 1] == 8) {
			piece_pos[i + 1] = piece_pos[i];
			piece_pos[i] = 8;

			locateObject(조각[piece_pos[i + 1]], title, X[(i + 1) % 3], Y[(i + 1) / 3]);
			locateObject(조각[piece_pos[i]], title, X[i % 3], Y[i / 3]);


			if (isFinished()) {
				endGame();
				hideObject(startButton);
				showObject(restartButton);
				//stopTimer(퍼즐);
				//getTimer(퍼즐);
				float a = 3600 - getTimer(퍼즐);
				char message[20];
				sprintf_s(message, "클리어!%2.f", a);
				showMessage(message);
			}
			return;
		}
	}

}



int main() {

	setSceneCallback(sceneCallback);
	setMouseCallback(mouseCallback);
	//setTimerCallback(timerCallback);



	title = createScene("Game", "title.png");
	start = createScene("start", "title.png");


	for (int i = 0; i < nMAX; i++) {
		char words[20], tem_data[20];
		sprintf_s(words, "%d.jpg", i);
		sprintf_s(tem_data, "조각 %d", i);
		조각[i] = createObject(tem_data, words, title, X[i % 3], Y[i / 3], true);
		scaleObject(조각[i], 0.7f);
	}



	완성본 = createObject("완성본", "레이튼교수.jpg", title, 885, 250, true);
	scaleObject(완성본, 0.4f);

	BGM = createSound(L"theme.wav", false);


	startButton = createObject("시작버튼", "start.png", start, 590, 370, true);

	endButton = createObject("종료버튼", "end.png", start, 590, 320, true);

	restartButton = createObject("재시작버튼", "restart.png", start, 590, 370, false);

	퍼즐 = createTimer(3600.0f, false);

	startGame(start);
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
