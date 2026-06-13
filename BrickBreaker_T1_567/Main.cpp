# include <Siv3D.hpp>

/// @brief ブロック
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
};
const Size Brick::BrickSize{ 40, 20 };

/// @brief ボール
class Ball
{
	const double BallSpeedPerSec;// = 480.0;
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

	}
};

/// @brief パドル
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
};

void Main()
{
	Array<Brick> bricks;
	Ball ball;
	Paddle paddle;

	// 1 つのブロックのサイズ | Size of a single block
	//constexpr Size BrickSize{ 40, 20 };

	//// ボールの速さ（ピクセル / 秒） | Ball speed (pixels / second)
	//constexpr double BallSpeedPerSec = 480.0;

	//// ボールの速度 | Ball velocity
	//Vec2 ballVelocity{ 0, -BallSpeedPerSec };

	//// ボール | Ball
	//Circle ball{ 400, 400, 8 };

	//// ブロックの配列 | Array of bricks
	//Array<Rect> bricks;

	for (int32 y = 0; y < 5; ++y)
	{
		for (int32 x = 0; x < (Scene::Width() / Brick::BrickSize.x); ++x)
		{
			bricks << Brick(x, y);
			//bricks << Rect{ (x * BrickSize.x), (60 + y * BrickSize.y), BrickSize };
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

		// 描画
		for (auto& obj : bricks) {
			obj.draw();
		}
		ball.draw();
		paddle.draw();

		// パドル | Paddle
		//const Rect paddle{ Arg::center(Cursor::Pos().x, 500), 60, 10 };

		//// ボールを移動させる | Move the ball
		//ball.moveBy(ballVelocity * Scene::DeltaTime());

		//// ブロックを順にチェックする | Check bricks in sequence
		//for (auto it = bricks.begin(); it != bricks.end(); ++it)
		//{
		//	// ブロックとボールが交差していたら | If block and ball intersect
		//	if (it->intersects(ball))
		//	{
		//		// ブロックの上辺、または底辺と交差していたら | If ball intersects with top or bottom of the block
		//		if (it->bottom().intersects(ball) || it->top().intersects(ball))
		//		{
		//			// ボールの速度の Y 成分の符号を反転する | Reverse the sign of the Y component of the ball's velocity
		//			ballVelocity.y *= -1;
		//		}
		//		else // ブロックの左辺または右辺と交差していたら
		//		{
		//			// ボールの速度の X 成分の符号を反転する | Reverse the sign of the X component of the ball's velocity
		//			ballVelocity.x *= -1;
		//		}

		//		// ブロックを配列から削除する（イテレータは無効になる） | Remove the block from the array (the iterator becomes invalid)
		//		bricks.erase(it);

		//		// これ以上チェックしない | Do not check any more
		//		break;
		//	}
		//}

		//// 天井にぶつかったら | If the ball hits the ceiling
		//if ((ball.y < 0) && (ballVelocity.y < 0))
		//{
		//	// ボールの速度の Y 成分の符号を反転する | Reverse the sign of the Y component of the ball's velocity
		//	ballVelocity.y *= -1;
		//}

		//// 左右の壁にぶつかったら | If the ball hits the left or right wall
		//if (((ball.x < 0) && (ballVelocity.x < 0))
		//	|| ((Scene::Width() < ball.x) && (0 < ballVelocity.x)))
		//{
		//	// ボールの速度の X 成分の符号を反転する | Reverse the sign of the X component of the ball's velocity
		//	ballVelocity.x *= -1;
		//}

		//// パドルにあたったら | If the ball hits the left or right wall
		//if ((0 < ballVelocity.y) && paddle.intersects(ball))
		//{
		//	// パドルの中心からの距離に応じてはね返る方向（速度ベクトル）を変える | Change the direction (velocity vector) of the ball depending on the distance from the center of the paddle
		//	ballVelocity = Vec2{ (ball.x - paddle.center().x) * 10, -ballVelocity.y }.setLength(BallSpeedPerSec);
		//}

		//// すべてのブロックを描画する | Draw all the bricks
		//for (const auto& brick : bricks)
		//{
		//	// ブロックの Y 座標に応じて色を変える | Change the color of the brick depending on the Y coordinate
		//	brick.stretched(-1).draw(HSV{ brick.y - 40 });
		//}

		//// マウスカーソルを非表示にする | Hide the mouse cursor
		//Cursor::RequestStyle(CursorStyle::Hidden);

		//// ボールを描く | Draw the ball
		//ball.draw();

		//// パドルを描く | Draw the paddle
		//paddle.rounded(3).draw();
	}
}
