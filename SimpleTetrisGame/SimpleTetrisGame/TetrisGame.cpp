#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
// Background의 가로줄 M = 20, 세로줄 N = 10
const int M = 20;
const int N = 10;

// field initialized
int field[M][N] = {0};

// 위치 
struct Point
{int x,y;
} a[4], b[4];


// Block Structure
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};


bool check()
{
   for (int i=0;i<4;i++)
	   // Block이 오른쪽, 왼쪽으로 들어가거나, field의 Y좌표를 초과하면 return 
	  if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

	  // 다른 경우는 항상 true 
   return 1;
};


int main()
{
	// 단일 블록 수정
	a[0].x = 0; a[0].y = 1;
	a[1].x = 1; a[1].y = 1;
	a[2].x = 1; a[2].y = 2;
	a[3].x = 1; a[3].y = 3;
	// 난수 발생기
    srand(time(0));	 

	// window의 사이즈 및 title 설정 
	RenderWindow window(VideoMode(320, 480), "The Game!");

	// Texture를 통해 Image를 불러옴
    Texture t1,t2,t3;
	t1.loadFromFile("TetrisImages/tiles.png");
	t2.loadFromFile("TetrisImages/background.png");
	t3.loadFromFile("TetrisImages/frame.png");

	// Sprite로 표현
	Sprite s(t1), background(t2), frame(t3);

	// 블록의 이동 위치 dx, rotate 회전, colorNum 블록의 color index
    int dx=0; bool rotate=0; int colorNum=1;
	// timer가 delay를 넘어가게 되면 블록이 내려옴
	float timer=0,delay=0.3; 

	Clock clock;



    while (window.isOpen())
    {	
		// restart된 시간부터의 time값 (초)
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

        Event e;
        while (window.pollEvent(e))
        {	// pollEvent가 종료되면 윈도우도 종료 
            if (e.type == Event::Closed)
                window.close();

			// 입력된 키 값에 따라 제어 
			if (e.type == Event::KeyPressed)
			  if (e.key.code==Keyboard::Up) rotate=true;
			  else if (e.key.code==Keyboard::Left) dx=-1;
			  else if (e.key.code==Keyboard::Right) dx=1;
		}
		// 마찬가지로, delay를 더 빠르게 해줌
	if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

	//// <- Move -> ///
	for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=dx; }
    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];

	//////Rotate////// -----> OK
	if (rotate)
	  {
		Point p = a[1]; //center of rotation
		for (int i=0;i<4;i++)
		  {
			int x = a[i].y-p.y;
			int y = a[i].x-p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
	 	  }
   	    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
	  }

	///////Tick//////
	if (timer>delay)
	  {
	    for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

		if (!check())
		{
		 for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;

		 // Block의 color를 지정 
		 colorNum=1+rand()%7;
		 int n=rand()%7;
		 for (int i=0;i<4;i++)
		   {
		    a[i].x = figures[n][i] % 2;
		    a[i].y = figures[n][i] / 2;
		   }
		}

	  	timer=0;
	  }

	///////check lines//////////
    int k=M-1;
	for (int i=M-1;i>0;i--)
	{
		int count=0;
		for (int j=0;j<N;j++)
		{
		    if (field[i][j]) count++;
		    field[k][j]=field[i][j];
		}
		if (count<N) k--;
	}

    dx=0; rotate=0; delay=0.3;

    /////////draw//////////
    window.clear(Color::White);	
    window.draw(background);
		  
	

	for (int i=0;i<M;i++)
	 for (int j=0;j<N;j++)
	   {
         if (field[i][j]==0) continue;
		 s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
		 s.setPosition(j*18,i*18);
		 s.move(28,31); //offset
		 window.draw(s);
	   }

	for (int i=0;i<4;i++)
	  {
		s.setTextureRect(IntRect(colorNum*18,0,18,18));
		s.setPosition(a[i].x*18,a[i].y*18);
		s.move(28,31); //offset
		window.draw(s);
	  }

	window.draw(frame);
 	window.display();
	}

    return 0;
}