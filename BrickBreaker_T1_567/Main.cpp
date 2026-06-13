# include <Siv3D.hpp>

// 前方宣言
class Ball;

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

	bool reflect(Ball& refBall);
};
const Size Brick::BrickSize{ 40, 20 };

/// @brief ボール
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

	void reflect(Ball& refBall)
	{
		auto& ball = refBall.getBall();
		auto& ballVelocity = refBall.getVelocity();
		if ((0 < ballVelocity.y) && paddle.intersects(ball))
		{
			ballVelocity = Vec2{ (ball.x - paddle.center().x) * 10, -ballVelocity.y }.setLength(refBall.BallSpeedPerSec);
		}
	}
};

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
