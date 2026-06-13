#include "stdafx.h"
#include "Paddle.h"
#include "Ball.h"

void Paddle::reflect(Ball& refBall)
{
	auto& ball = refBall.getBall();
	auto& ballVelocity = refBall.getVelocity();
	if ((0 < ballVelocity.y) && paddle.intersects(ball))
	{
		ballVelocity = Vec2{ (ball.x - paddle.center().x) * 10, -ballVelocity.y }.setLength(refBall.BallSpeedPerSec);
	}
}
