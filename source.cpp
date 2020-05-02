#include <stdio.h>
#include <bangtal.h>
#include <time.h>
#include <stdlib.h>

#define FAIRY 0
#define BOMB 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

SceneID scene0, scene1, scene2,scene3,scene4;
ObjectID title, start, help, play, goBack, A,B;
ObjectID Items[6];
ObjectID Heart[5]; 

int HP[5] = { 100, 150, 200, 250, 300 }; // Left Heart Position
int height = 600;
int i = 4;
int num;
int score = 0;

TimerID timer1, timer2, timer3;
SoundID O, X;

const Second animationTime = 0.01f;

void GameOver() {
	playSound(X);
	hideObject(Heart[i]);
	i--;

	if (i == -1) {
		enterScene(scene2);
		stopTimer(timer2);
	}
}

int Random() {
	srand((unsigned int)time(NULL));
	num = rand() % 6;
	return num;
}

void Fall(int j) {
	if (j == FAIRY) {
		if (height > 0) { 
			height = height - 10;
			locateObject(Items[FAIRY], scene1, 600, height);
			setTimer(timer1, animationTime);
			startTimer(timer1);
			
			if (height <= 0) {
				hideObject(Items[FAIRY]);
				height = 600;
				Fall(Random());
				showObject(Items[Random()]);
				
			}

		}
	}

	else if (j== BOMB){
		if (height > 0) {
			height = height - 30;
			locateObject(Items[BOMB], scene1, 600, height);
			setTimer(timer1, animationTime);
			startTimer(timer1);
			
		}
			if (height <= 0) {
				hideObject(Items[BOMB]);
				height = 600;
				Fall(Random());
				showObject(Items[Random()]);
				
			}
	}

	else if (j == UP) {
		if (height > 0) {
			height = height - 40;
			locateObject(Items[UP], scene1, 600, height);
			setTimer(timer1, animationTime);
			startTimer(timer1);

		}
		if (height <= 0) {
			hideObject(Items[UP]);
			height = 600;
			Fall(Random());
			showObject(Items[Random()]);

		}
	}

	else if (j == DOWN) {
		if (height > 0) {
			height = height - 20;
			locateObject(Items[DOWN], scene1, 600, height);
			setTimer(timer1, animationTime);
			startTimer(timer1);

		}
		if (height <= 0) {
			hideObject(Items[DOWN]);
			height = 600;
			Fall(Random());
			showObject(Items[Random()]);
		}

	}

	else if (j == LEFT) {
		if (height > 0) {
			height = height - 50;
			locateObject(Items[LEFT], scene1, 600, height);
			setTimer(timer1, animationTime);
			startTimer(timer1);

			if (height <= 0) {
				hideObject(Items[LEFT]);
				height = 600;
				Fall(Random());
				showObject(Items[Random()]);

			}

		}
	}

	else if (j == RIGHT) {
		if (height > 0) {
			height = height - 30;
			locateObject(Items[RIGHT], scene1, 600, height);
			setTimer(timer1, animationTime);
			startTimer(timer1);

			if (height <= 0) {
				hideObject(Items[RIGHT]);
				height = 600;
				Fall(Random());
				showObject(Items[Random()]);

			}

		}
	}


}

void timerCallback(TimerID timer) {
		Fall(num);

		if (timer == timer2) {
			enterScene(scene4);
			increaseTimer(timer3, score);
			showTimer(timer3);
		}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == start) {
		enterScene(scene1);
		showTimer(timer2);
	}

	if (object == play) {
		startTimer(timer2);
		Fall(Random());
		showObject(Items[Random()]);
		hideObject(play);
	}

	if (object == help) {
		enterScene(scene3);
	}

	if (object == goBack) {
		enterScene(scene0);
	}

	if (object == Items[FAIRY] || object == Items[LEFT]) {
		if (action == MouseAction::MOUSE_DRAG_LEFT) {
			playSound(O);
			hideObject(Items[FAIRY]);
			hideObject(Items[LEFT]);
			score++;
		}

		else {
			GameOver();
		}
	}

	if (object == Items[BOMB]|| object == Items[RIGHT]) {
		if (action == MouseAction::MOUSE_DRAG_RIGHT) {
			playSound(O);
			hideObject(Items[BOMB]);
			hideObject(Items[RIGHT]);
			score++;
		}

		else {
			GameOver();
		}
	}

	if (object == Items[DOWN]) {
		if (action == MouseAction::MOUSE_DRAG_UP) {
			playSound(O);
			hideObject(Items[DOWN]);
			score++;
		}

		else {
			GameOver();
		}
	}

	if (object == Items[UP]) {
		if (action == MouseAction::MOUSE_DRAG_DOWN) {
			hideObject(Items[UP]);
			playSound(O);
			score++;
		}

		else {
			GameOver();
		}
	}
	
}

void game_init() {

	scene0 = createScene("후크 선장과의 결투", "후크vs피터팬.jpg");
	
	title = createObject("제목.png");
	locateObject(title, scene0, 350, 500);
	showObject(title);
	scaleObject(title, 3);


	start = createObject("시작.png");
	locateObject(start, scene0, 400, 100);
	showObject(start);
	scaleObject(start, 1.5);

	help = createObject("방법.png");
	locateObject(help, scene0, 700, 100);
	showObject(help);
	scaleObject(help, 1.5);


	scene1 = createScene("후크 선장과의 결투", "전투창.jpg");

	play = createObject("플레이.png");
	locateObject(play, scene1, 600, 100);
	showObject(play);
	scaleObject(help, 1.5);
	

	A = createObject("피터팬.png");
	locateObject(A, scene1, 100, 0);
	showObject(A);

	B = createObject("후크선장.png");
	locateObject(B, scene1, 900, 0);
	showObject(B);

	char heartImage[20];
	for (int k = 0; k < 5; k++) {
		sprintf_s(heartImage, "RH%d.png", k);
		Heart[k] = createObject(heartImage);
		locateObject(Heart[k], scene1, HP[k],600 );
		scaleObject(Heart[k], 0.5);
		showObject(Heart[k]);
	}

	char itemImage[20];
	for (int k = 0; k < 6; k++) {
		sprintf_s(itemImage, "item%d.png", k);
		Items[k] = createObject(itemImage);
		scaleObject(Items[k], 0.6);
		showObject(Items[k]);
	}

	O = createSound("O.wav");
	X = createSound("X.wav");

	scene2 = createScene("게임 오버", "게임오버.jpg");

	scene3 = createScene("게임 방법", "방법창.jpg");

	goBack = createObject("돌아가기.png");
	locateObject(goBack, scene3, 1000, 600);
	showObject(goBack);
	scaleObject(goBack, 1.5);

	scene4 = createScene("당신의 점수", "스코어창.jpg");
	
}

int main() {

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	game_init();
	
	timer1 = createTimer(60.0f);
	timer2 = createTimer(60.0f);
	timer3 = createTimer(0.0f);

	startGame(scene0);
	
}