#pragma once

class Ball
{
public:
	const double BallSpeedPerSec;// = 480.0;

private:
	Vec2 ballVelocity{ 0, -BallSpeedPerSec };

	Circle ball;

public:
	Ball(double speed = 480.0)
		: ball( Circle{ 400, 400, 8 } )	// 初期化子リスト
		, BallSpeedPerSec( speed )
	{}

	void draw() {
		ball.draw();
	}

	void update() {
		ball.moveBy(ballVelocity * Scene::DeltaTime());

		// 天井にぶつかったら | If the ball hits the ceiling
		if ((ball.y < 0) && (ballVelocity.y < 0))
		{
			ballVelocity.y *= -1;
		}

		// 左右の壁にぶつかったら | If the ball hits the left or right wall
		if (((ball.x < 0) && (ballVelocity.x < 0))
			|| ((Scene::Width() < ball.x) && (0 < ballVelocity.x)))
		{
			ballVelocity.x *= -1;
		}
	}

	Vec2& getVelocity() { return ballVelocity; }
	Circle& getBall() { return ball; }
};
