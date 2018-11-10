#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// s1, s2의 충돌 여부 
bool isCollide(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}


int main() {

	srand(time(0));

	RenderWindow app(VideoMode(520, 450), "Arkanoid Game!");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("ArkanoidImages/block01.png");
	t2.loadFromFile("ArkanoidImages/background.jpg");
	t3.loadFromFile("ArkanoidImages/ball.png");
	t4.loadFromFile("ArkanoidImages/paddle.png");

	Sprite sBackground(t2), sBall(t3), sPaddle(t4);
	sPaddle.setPosition(300, 440);
	sBall.setPosition(300, 300);

	Sprite block[1000];

	int n = 0;
	for (int i = 1 ; i <= 10 ; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}

	float dx = 6, dy = 5;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}
		// Ball x 좌표에 관한 충돌 제어
		sBall.move(dx, 0);
		for (int i = 0; i < n ; i++)
			if (isCollide(sBall, block[i])) { block[i].setPosition(-100, 0); dx = -dx; }

		// Ball y 좌표에 관한 충돌 제어
		sBall.move(0, dy);
		for (int i = 0; i < n; i++)
			if (isCollide(sBall, block[i])) { block[i].setPosition(-100, 0); dy = -dy; }

		Vector2f b = sBall.getPosition();
		// Ball이 오른, 왼 화면 밖으로 나갈시 다시 안으로 들어오게 설정
		if (b.x < 0 || b.x > 520) dx = -dx;
		if (b.y < 0 || b.y > 450) dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

		// random으로 y값 반동 설정
		if (isCollide(sPaddle, sBall)) dy = -(rand() % 5 + 2);

		app.clear();
		app.draw(sBackground);
		app.draw(sBall);
		app.draw(sPaddle);

		for (int i = 0; i < n; i++)
			app.draw(block[i]);

		app.display();
	}

	return 0;
}