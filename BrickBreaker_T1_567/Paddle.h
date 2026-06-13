#pragma once

class Ball;

class Paddle
{
	Rect paddle;

public:
	Paddle()
		: paddle( { Arg::center(Cursor::Pos().x, 500), 60, 10 } )
	{}

	void draw() {
		paddle.rounded(3).draw();
	}

	void update() {
		paddle.pos.x = Cursor::Pos().x - 30;
	}

	void reflect(Ball& refBall);
};
