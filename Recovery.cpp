
int main()
{
//////////////////Time//////////////////////////////////
	Clock clock;
////////////////////////////////////////////////////////

	float CurrentFrame = 0;
	RenderWindow window(VideoMode(800, 600), "Tanks");
	
	//Player p("tanks.png");

///////////////////Танк/////////////////////////////////	
	Image tankimage; //создаем объект Image (изображение)
	tankimage.loadFromFile("E:/Прог/C++/Tank/images/tanks.png");
	Texture tankTexture;
	tankTexture.loadFromImage(tankimage);
	Sprite tankSprite;
	tankSprite.setTexture(tankTexture);
	tankSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	//tankSprite.setOrigin(37.f, 37.f);
	tankSprite.setOrigin(37, 37);
////////////////////////////////////////////////////////
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("E:/Прог/C++/Tank/images/note.jpg");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			tankSprite.setRotation(-90);
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 7)CurrentFrame -= 7;
			tankSprite.setTextureRect(IntRect(90 * int(CurrentFrame), 85, 75, 82));
			tankSprite.move(-0.1*time, 0); 
		} //первая координата Х отрицательна =>идём влево
		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{ 
			tankSprite.setRotation(90);
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 7)
				CurrentFrame -= 7;
			tankSprite.setTextureRect(IntRect(90 * int(CurrentFrame), 85, 75, 82));
			tankSprite.move(0.1*time, 0); 
		} //первая координата Х положительна =>идём вправо
		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{ 
			tankSprite.setRotation(0);
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 7)CurrentFrame -= 7;
			tankSprite.setTextureRect(IntRect(90 * int(CurrentFrame), 85, 75, 82));
			tankSprite.move(0, -0.1*time); 
		} //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::Down)) 
		{ 
			tankSprite.setRotation(180);
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 7)CurrentFrame -= 7;
			tankSprite.setTextureRect(IntRect(90 * int(CurrentFrame), 85, 75, 82));
			tankSprite.move(0, 0.1*time); 
		} //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)
		

		window.clear();
		window.draw(s_map);
		window.draw(tankSprite);
		
		window.display();
	}
    return 0;
}

