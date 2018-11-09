#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct point
{
	int x, y;
};

int main() {

	srand(time(0));

	RenderWindow app(VideoMode(400, 533), "Doodle Game!");
	app.setFramerateLimit(60);

	Texture t1, t2, t3;
	t1.loadFromFile("DoodleJumpImages/background.png");
	t2.loadFromFile("DoodleJumpImages/platform.png");
	t3.loadFromFile("DoodleJumpImages/doodle.png");

	Sprite sBackground(t1), sPlat(t2), sPers(t3);

	point plat[20];

	// 장애물 10개의 좌표 생성 
	for (int i = 0; i < 10; i++)
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 533;
	}

	int x = 100, y = 100, h = 200;
	float dx = 0, dy = 0;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}
		// 캐릭터 이동 
		if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
		if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

		// 계속 아래로 캐릭터를 Down 
		dy += 0.2;
		y += dy;
		// y좌표가 500값을 넘으면 다시 튕겨 올라감 
		// 490 .. 480 .... 이런식으로 다시 Up & Down 
		if (y > 500) dy = -10;

		if (y < h)
			for (int i = 0; i < 10; i++)
			{
				// h 값을 캐릭터의 y 좌표로 설정 
				y = h;
				plat[i].y = plat[i].y - dy;
				// 화면의 최대 크기를 넘으면 새로 장애물을 생성 
				if (plat[i].y > 533) { plat[i].y = 0; plat[i].x = rand() % 400; }
			}

		for (int i = 0; i < 10; i++) {
			if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
				&& (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)) dy = -10;
		}

		sPers.setPosition(x, y);

		app.draw(sBackground);
		app.draw(sPers);
		// 장애물 좌표 설정 & Draw
		for (int i = 0; i < 10; i++)
		{
			sPlat.setPosition(plat[i].x, plat[i].y);
			app.draw(sPlat);
		}

		app.display();
	}

	return 0;
}