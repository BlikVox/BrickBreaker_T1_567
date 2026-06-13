# include <Siv3D.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

void Main()
{
	Array<Brick> bricks;
	Ball ball;
	Paddle paddle;

	for (int32 y = 0; y < 5; ++y)
	{
		for (int32 x = 0; x < (Scene::Width() / Brick::BrickSize.x); ++x)
		{
			bricks << Brick(x, y);
		}
	}

	while (System::Update())
	{
		// 更新
		for (auto& obj : bricks) {
			obj.update();
		}
		ball.update();
		paddle.update();

		for (auto it = bricks.begin(); it != bricks.end(); ++it)
		{
			if (it->reflect( ball )) {
				bricks.erase(it);
				break;
			}
		}
		paddle.reflect( ball );

		// 描画
		for (auto& obj : bricks) {
			obj.draw();
		}
		ball.draw();
		paddle.draw();
	}
}
