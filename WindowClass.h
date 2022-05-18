#pragma once

#include <SFML/Graphics.hpp>
#include "ValueClass.h"

class Window {

	sf::RenderWindow* window = nullptr;

	void updateDraw()
	{
		for (int y = 0; y < tile_height; y++)
			for (int x = 0; x < tile_width; x++)
			{
				int indexTexture = y * tile_width + x + posz * tile_height * tile_width;
				int indexWindow = x + y * tile_width;
				float con = Map->NoiseArray[indexTexture] * 10;
				sf::Color color = sf::Color(255, 255, 255, 255 * con);

				Map2D[indexWindow].color = color;
				Map2D[indexWindow].position = sf::Vector2f(x, y);
			}

	}


	void update()
	{
		window->clear();
		window->draw(Map2D);
		window->display();
	}

	void close() {

		delete window;
	}



	void loop()
	{
		sf::Event event;
		while (window->isOpen())
		{
			changes = 0;

			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();

				}
				if (event.type == sf::Event::KeyPressed)
				{


					if (event.key.code == sf::Keyboard::Q)
					{
						Map->gen_NewSeed();
						changes = 1;
					}

					if (event.key.code == sf::Keyboard::A)
					{
						Map->_octaves++;
						changes = 1;
					}
					if (event.key.code == sf::Keyboard::D)
					{
						Map->_octaves--;
						changes = 1;
					}
					if (event.key.code == sf::Keyboard::Space && posz < tile_width - 1)
					{
						posz++;
					}
					if (event.key.code == sf::Keyboard::LShift && posz > 1)
					{
						posz--;
					}

					if (event.key.code == sf::Keyboard::R)
					{
						Map->_noiseCancelling -= 0.05;
						changes = 1;
					}
					if (event.key.code == sf::Keyboard::T)
					{
						Map->_noiseCancelling += 0.05;
						changes = 1;
					}
				}


			}
			if (changes)
			{
				Map->transformSeed();
			}
			updateDraw();
			update();


		}
		close();


	}


public:

	int tile_width = 200;
	int tile_height = 200;
	int tile_depth = 200;
	int posz = 1;
	bool changes = 0;
	sf::VertexArray Map2D;

	ValueNoise* Map;

	void start(unsigned int Width, unsigned int Height, const char* Title)
	{

		window = new sf::RenderWindow(sf::VideoMode(Width, Height), Title);
		Map = new ValueNoise(tile_width, tile_height, tile_depth);
		Map->gen_NewSeed();
		Map->transformSeed();
		Map2D.setPrimitiveType(sf::Points);
		Map2D.resize(tile_width * tile_height);

		loop();

	}

};