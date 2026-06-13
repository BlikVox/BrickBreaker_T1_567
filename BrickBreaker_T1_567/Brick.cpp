#include "stdafx.h"
#include "Brick.h"
#include "Ball.h"

const Size Brick::BrickSize{ 40, 20 };

bool Brick::reflect(Ball& refBall)
{
	auto& ball = refBall.getBall();
	auto& ballVelocity = refBall.getVelocity();

	if (!rect.intersects(ball)) {
		return false;
	}

	// ブロックの上辺、または底辺と交差していたら | If ball intersects with top or bottom of the block
	if (rect.bottom().intersects(ball) || rect.top().intersects(ball))
	{
		ballVelocity.y *= -1;
		return true;
	}
	else // ブロックの左辺または右辺と交差していたら
	{
		ballVelocity.x *= -1;
		return true;
	}

	return false;
}
