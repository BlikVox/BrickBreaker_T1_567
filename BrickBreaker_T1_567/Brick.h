#pragma once

class Ball;

class Brick
{
public:
	// 静的メンバ定数 -> 実体が別にある
	// 静的(static) メンバ(クラス宣言内で書かれている) 定数(const)
	static const Size BrickSize;
	
	Rect rect;
	
public:
	Brick(int32 x, int32 y)
		: rect({ (x * BrickSize.x), (60 + y * BrickSize.y), BrickSize })
	{}
	
	Brick()
		: rect( BrickSize )
	{}
	
	void draw() {
		rect.stretched(-1).draw(HSV{ rect.y - 40 });
	}
	
	void update() {
	
	}
	
	bool reflect(Ball& refBall);
};
