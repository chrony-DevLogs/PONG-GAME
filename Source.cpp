#include "raylib.h"
#include <iostream>
#include <thread>

//Setting a ball BluePrint 

class Ball {

	public:
		float ballRadius{ 0.0f };
		float ballSpeedX{ 1 };
		float ballSpeedY{ 1 };
		float ballX{ 0.0f };
		float ballY{ 0.0f };

		Ball(float* ballX,float* ballY,float* ballRadius,float* ballSpeedX, float* ballSpeedY) {
			this->ballX = *ballX;
			this->ballY = *ballY;
			this->ballRadius = *ballRadius;
			this->ballSpeedX = *ballSpeedX;
			this->ballSpeedY = *ballSpeedY;

		}

		void drawMyBall() {
			DrawCircle((int)this->ballX, (int)this->ballY, this->ballRadius, WHITE);
		}

};


//Setting a paddle BluePrint

class Paddle {
	public:
		int paddleX{ 0 };
		int paddleY{ 0 };
		int paddleWidth{ 0 };
		int paddleHeight{ 0 };
		int paddleSpeed{ 1 };

		int score{ 0 };
		std::string scoreT{ std::to_string(this->score) };

		Paddle(int* paddleX, int* paddleY, int* paddleWidth, int* paddleHeight,int* paddleSpeed) {
			this->paddleX = *paddleX;
			this->paddleY = *paddleY;
			this->paddleWidth = *paddleWidth;
			this->paddleHeight = *paddleHeight;
			this->paddleSpeed = *paddleSpeed;
		}

		void drawPaddle() {
			DrawRectangle(this->paddleX,this->paddleY,this->paddleWidth,this->paddleHeight,WHITE);
		}

};


void reset(float *ballX, float *ballY, float* newX,float* newY);
void increaseScore(int* score, std::string* scoreT);
//start Program

int main(void) {

	SetTargetFPS(60);

	InitWindow(800, 600,"PONG");


	//setting Up our ball attributes 

	float ballX{GetScreenWidth() / 2.0f};
	float ballY{ GetScreenHeight() / 2.0f };

	float ballRadius{ 5.0f };

	float ballSpeedX{ 200.0f };
	float ballSpeedY{ 300.0f };

	// setting Up our Paddles attributes 
	int paddleXp1{50};
	int paddleYp1{ GetScreenHeight() /2};

	int paddleXp2{ GetScreenWidth() - 50};
	int paddleYp2{ GetScreenHeight() / 2 };

	int paddleWidth{10};
	int paddleHeight{100};

	int paddleSpeed{ 300 };

	Ball myBall = Ball(&ballX, &ballY, &ballRadius,&ballSpeedX,&ballSpeedY);

	Paddle paddleP1 = Paddle(&paddleXp1, &paddleYp1, &paddleWidth, &paddleHeight,&paddleSpeed);
	Paddle paddleP2 = Paddle(&paddleXp2, &paddleYp2, &paddleWidth, &paddleHeight,&paddleSpeed);

	while (!WindowShouldClose())
	{
		BeginDrawing();

			ClearBackground(BLACK);
			DrawFPS(GetScreenWidth()/2, 10);
			DrawText(paddleP1.scoreT.c_str(), 100, 10, 20, WHITE);
			DrawText(paddleP2.scoreT.c_str(), GetScreenWidth() - 100, 10, 20, WHITE);

			//drawing the ball and give it some collision to the top and bottom edges

			myBall.drawMyBall();
			myBall.ballX += myBall.ballSpeedX * GetFrameTime();
			myBall.ballY += myBall.ballSpeedY * GetFrameTime();

			if (myBall.ballY > GetScreenHeight()) {
				myBall.ballSpeedY *= -1;
			}
			if (myBall.ballY < 0) {
				myBall.ballY = 0;
				myBall.ballSpeedY *= -1;
			}

			
			//drawing the paddles

			paddleP1.drawPaddle();
			paddleP2.drawPaddle();

			// setting Up Controls over P1

			if (paddleP1.paddleY >= 0) {
				if (IsKeyDown(KEY_W)) {
					paddleP1.paddleY -= (int)(paddleP1.paddleSpeed * GetFrameTime());

				}
			}

			if ((paddleP1.paddleY + paddleP1.paddleHeight) <= GetScreenHeight()) {
				if (IsKeyDown(KEY_S)) {
					paddleP1.paddleY += (int)(paddleP1.paddleSpeed * GetFrameTime());
				}
			}

			//setting up controls over P2
			if (paddleP2.paddleY >= 0) {
				if (IsKeyDown(KEY_O)) {
					paddleP2.paddleY -= (int)(paddleP2.paddleSpeed * GetFrameTime());
				}
			}
			if ((paddleP2.paddleY + paddleP2.paddleHeight) <= GetScreenHeight()) {
				if (IsKeyDown(KEY_L)) {
					paddleP2.paddleY += (int)(paddleP2.paddleSpeed * GetFrameTime());
				}
			}

		//TODO: give the ball some colligion with te paddles 

			if ((myBall.ballY <= paddleP1.paddleY + paddleP1.paddleHeight) && (myBall.ballY >= paddleP1.paddleY) && (myBall.ballX <= paddleP1.paddleX + paddleWidth)) {
				myBall.ballSpeedX *= -1.0f;
				myBall.ballSpeedY = (myBall.ballY - paddleP1.paddleY) / (paddleHeight / 2) * ballSpeedY;
			}



			if ((myBall.ballY <= paddleP2.paddleY + paddleP1.paddleHeight) && (myBall.ballY >= paddleP2.paddleY) && (myBall.ballX >= paddleP2.paddleX)) {
				myBall.ballSpeedX *= -1.0f;

			}




			//reset The Ball

			if (myBall.ballX < 0) {
				reset(&myBall.ballX, &myBall.ballY, &ballX, &ballY);
				increaseScore(&paddleP2.score, &paddleP2.scoreT);
			}
			if (myBall.ballX > GetScreenWidth()) {
				reset(&myBall.ballX, &myBall.ballY, &ballX,&ballY);
				increaseScore(&paddleP1.score, &paddleP1.scoreT);

			}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void reset(float* ballX,float* ballY , float* newBallX,float* newBallY ) {

	*ballX = *newBallX;
	*ballY = *newBallY;
	
}

void increaseScore(int* score, std::string* scoreT) {
	*score += 1;
	*scoreT = { std::to_string(*score) };
}