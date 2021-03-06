// Tank.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "map.h"
#include "view.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "Mission.h"
#include "level.h"
#include <list>

using namespace sf;
using namespace std;

class Entity
{
public:
	vector <Object> obj;
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	FloatRect getRect() 
	{	//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}
	virtual void update(float time) = 0;
};

class Player : public Entity
{
public:
	enum { left, right, up, down, stay } state;
	int playerScore;
	bool isShoot;
	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
		playerScore = 0; state = stay; obj = lev.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		if (name == "Player") 
		{
			sprite.setTextureRect(IntRect(0, 85, w, h));
			sprite.setOrigin(35, 35);
		}
	}

	void update(float time)
	{
		control();
		switch (state)
		{
			case left: dx = -speed; dy = 0; sprite.setRotation(-90);  break;
			case right: dx = speed; dy = 0; sprite.setRotation(90);  break;
			case up: dx = 0; dy = -speed; sprite.setRotation(0);  break;
			case down: dx = 0; dy = speed; sprite.setRotation(180); break;
		}
		x += dx * time;
		checkCollisionWithMap(dx*time, 0);
		y += dy * time;
		checkCollisionWithMap(0, dy*time);
		sprite.setPosition(x + w / 5, y + h / 2);
		if (!isMove) 
		{ 
			speed = 0; 
		}
		setPlayerCoordinateForView(x, y);
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0) 
					{ 
						y = obj[i].rect.top - h;  
						dy = 0; 
					}
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; 
					cout << "Есть попадание"<<endl;
					}
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
			}
	}

	

	void control()
	{
		int CurrentFrame = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			state = right;
			speed = 0.1;
		} //первая координата Х положительна =>идём вправо
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			state = up;
			speed = 0.1;
		} //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			state = down;
			speed = 0.1;
		} //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)
	//getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			isShoot = true;
		}
	}
};

class Enemy :public Entity
{
public:
	int direction;
	enum { left, right, up, down, stay } state;
	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		obj = lvl.GetObjects("solid");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
		if (name == "Enemy") {
			sprite.setTextureRect(IntRect(8, 1, w, h));
			dx = 0.1;
			dy = 0.1;
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				//если встретили препятствие (объект с именем solid)
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0.1; }
				if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; }

			}
	}

	void update(float time)
	{
		if (name == "Enemy") {
			moveTimer += time;

			if (moveTimer>3000)
			{ 
				direction = rand() % 3 + 1;
				//dx *= -1;
				moveTimer = 0; 
			}
			cout << "Direction= " << direction << endl;
			switch (direction)
			{
			case 0:
				dx = -0.1; 
				dy = 0;
				//checkCollisionWithMap(dx, 0);
				break;
			case 1:
				dx = 0.1;
				dy = 0;
				//checkCollisionWithMap(dx, 0);
				break;
			case 2:
				dx = 0; 
				dy = 0.1;
				//checkCollisionWithMap(0, dy);
				break;
			case 3:
				dx = 0; 
				dy = -0.1;
				//checkCollisionWithMap(0, dy);
				break;
			}
			checkCollisionWithMap(dx, 0);
			x += dx * time;
			checkCollisionWithMap(0, dy);
			y += dy * time;

			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) 
			{ 
				life = false; 
			}
		}
	}
};

class Bullet : public Entity
{
public:
	int direction;
	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.GetObjects("solid");
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 80;
	}
	void update(float time)
	{
		switch (direction)
		{
		case 0:dx = -speed; dy = 0;
			break;
		case 1:dx = speed; dy = 0;
			break;
		case 2:dx = 0; dy = -speed;
			break;
		case 3:dx = 0; dy = speed;
			break;
		case 4:dx = 0; dy = -speed;
			break;
		case 5:dx = 0; dy = -speed;
			break;
		}
		x += dx * time;
		y += dy * time;

		if (x <= 0)
		{
			x = 1;
		}
		if (y <= 0)
		{
			y = 1;
		}
		sprite.setPosition(x + w / 2, y + h / 2);
	}
};

int main()
{
	Clock clock;
	float CurrentFrame = 0;
	int createObjectForMapTimer = 0;
	bool showMissionText = true;
		
	RenderWindow window(VideoMode(1920, 1080), "Tanks");
	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	//AnimationManager anim;


	Level lvl;
	lvl.LoadFromFile("map02.tmx");
	//////////////////////////////////////////////////////////////////////////////////////////
	Image heroImage;
	heroImage.loadFromFile("E:/Tank/images/tanks.png");
	
	Image EnemyImage;
	EnemyImage.loadFromFile("E:/Tank/images/tanks.png");

	Object player = lvl.GetObject("Player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	Player p(heroImage, "Player", lvl, player.rect.left, player.rect.top, 75, 82);
	//p.sprite.setOrigin(37, 37);

	std::list<Entity*>  entities;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка
	std::vector<Object> e = lvl.GetObjects("Enemy");//все объекты врага на tmx карте хранятся в этом векторе
	for (int i = 0; i < e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
	{
		entities.push_back(new Enemy(EnemyImage, "Enemy", lvl, e[i].rect.left, e[i].rect.top, 71, 80));//и закидываем в список всех наших врагов с карты
	}

	Image BulletImage;
	BulletImage.loadFromFile("E:/Tank/images/bullet.png");
	BulletImage.createMaskFromColor(Color(0, 0, 0));

	////////////////////////Create a map/////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (p.isShoot == true) { p.isShoot = false; entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state)); }//если выстрелили, то появляется пуля. enum передаем как int 
			if (event.type == Event::KeyPressed)//событие нажатия клавиши
				if ((event.key.code == Keyboard::Escape)) 
				{
					window.close();
					return 0;
				}

			
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		p.update(time);
		for (it = entities.begin(); it != entities.end(); it++)
		{
			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "Enemy")
				{
					if ((*it)->dx > 0)
					{
						cout << "(*it)->x" << (*it)->x << "\n";
						cout << "p.x" << p.x << "\n";
						(*it)->x = p.x - (*it)->w;
						(*it)->dx *= -1;
						cout << "new(*it)->x" << (*it)->x << "\n";
						cout << "newp.x" << p.x << "\n\n";
					}
					if ((*it)->dx < 0)
					{
						(*it)->x = p.x + p.w;
						(*it)->dx *= -1;
					}
					if (p.dx < 0)
					{
						p.x = (*it)->x + (*it)->w;
					}
					if (p.dx > 0)
					{
						p.x = (*it)->x - p.w;
					}
				}
			}
		}
		for (it = entities.begin(); it != entities.end(); it++) 
		{ 
			(*it)->update(time); 
		}//для всех элементов списка(пока это только враги,но могут быть и пули к примеру) активируем ф-цию update

		window.setView(view);
		window.clear();
		lvl.Draw(window);
		for (it = entities.begin(); it != entities.end(); it++)
		{
			window.draw((*it)->sprite); //рисуем entities объекты (сейчас это только враги)
		}
		window.draw(p.sprite);
		window.display();
	}
    return 0;
}

