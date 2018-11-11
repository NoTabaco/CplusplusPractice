#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main() {

	RenderWindow app(VideoMode(256, 256), "15-Puzzle!");
	// 초당 60프레임 설정
	app.setFramerateLimit(60);

	Texture t;
	t.loadFromFile("PuzzleImages/15.png");
	// 256 / 64 = 4 
	int w = 64;
	int grid[6][6] = { 0 };
	Sprite sprite[20];

	int n = 0;
	for (int i = 0;i < 4 ; i++)
		for (int j = 0; j < 4; j++)
		{
			n++;
			sprite[n].setTexture(t);
			sprite[n].setTextureRect(IntRect(i*w, j*w, w, w));
			grid[i + 1][j + 1] = n;
		}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				app.close();
			}

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					Vector2i pos = Mouse::getPosition(app);
					// x, y -> 1, 2, 3, 4의 값을 가짐
					int x = pos.x / w + 1;
					int y = pos.y / w + 1;

					int dx = 0;
					int dy = 0;

					if (grid[x + 1][y] == 16) { dx = 1; dy = 0; };
					if (grid[x][y + 1] == 16) { dx = 0; dy = 1; };
					if (grid[x][y - 1] == 16) { dx = 0; dy = -1; };
					if (grid[x - 1][y] == 16) { dx = -1; dy = 0; };

					int n = grid[x][y];
					grid[x][y] = 16;
					grid[x + dx][y + dy] = n;

					// animation
					sprite[16].move(-dx * w, -dy * w);
					float speed = 3;

					for (int i = 0; i < 64; i += speed)
					{
						sprite[n].move(speed*dx, speed*dy);
						app.draw(sprite[16]);
						app.draw(sprite[n]);
						app.display();

					}
				}
		}

		app.clear(Color::White);
		for (int i = 0; i < 4 ; i++)
			for (int j = 0; j < 4; j++)
			{
				int n = grid[i + 1][j + 1];
				sprite[n].setPosition(i * w, j * w);
				app.draw(sprite[n]);
			}
		// 잊지 말자 ... 
		app.display();
	}

	return 0;
}
