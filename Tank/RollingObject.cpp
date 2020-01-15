#include"stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

void init(ConvexShape& pointer)
{
	pointer.setPointCount(3);
	pointer.setPoint(0, { 40,0 });
	pointer.setPoint(1, { -20,20 });
	pointer.setPoint(2, { -20,20 });
	pointer.setPosition({ 400, 300 });
	pointer.setFillColor(Color(0, 255, 0));
}

void onMouseMove(const Event::MouseMoveEvent& event, Vector2f& mousePosition)
{
	cout << "mouse x= " << event.x << ", y=" << event.y << endl;
	mousePosition = { float(event.x),float(event.y) };
}

void pollEvents(RenderWindow &window, Vector2f &mousePosition)
{
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::MouseMoved:
			onMouseMove(event.mouseMove, mousePosition);
			break;
		default:
			break;
		}
	}
}

float toDegrees(float radians)
{
	return float(double(radians)*180.0 / 3.14);
}

void update(const Vector2f &mousePosition, Sprite &tank)
{
	const Vector2f delta = mousePosition - tank.getPosition();
	const float angle = atan2(delta.y, delta.x);
	tank.setRotation(toDegrees(angle));
}

void redrawFrame(RenderWindow &window, Sprite &tank)
{
	window.clear();
	window.draw(tank);
	window.display();
}

int mitch()
{
	ContextSettings settings;
	settings.antialiasingLevel = 16;
	RenderWindow window(VideoMode({ 800,600 }), "RollingObject");
	Sprite tank;
	Image image1;
	Texture texture;
	image1.loadFromFile("E:/Tank/images/tank.png");
	texture.loadFromImage(image1);
	tank.setTexture(texture);
	tank.setTextureRect(IntRect(245, 10, 41, 77));
	tank.setOrigin(37, 37);
	tank.setPosition(400, 300);
	ConvexShape pointer;
	Vector2f mousePosition;

	init(pointer);
	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		update(mousePosition, tank);
		redrawFrame(window, tank);
	}

	return 0;
}