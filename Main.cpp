#include <SFML/Graphics.hpp>
#include <ccomplex>
#include "SFML\Audio.hpp"
#include <iostream>
#include <valarray>
#include <cmath>
#include "Spectrum_visualize.h"

using namespace std;


int main()
{
	std::cout << "Type file name and press p to play audio \n";
	std::cout << "File name is name of audio file stored in Resoureces \n";
	std::cout << "File name (ass.wav): ";
	string fileName;
	std::cin >> fileName;
	std::cout << "\nLoading...";

	Spectrum_visualize sp("Resources/" + fileName);

	bool isPlayed = false;
	float time_per_frame = 1 / 60.f;
	float time_since_last_update = 0.f;
	sf::Clock c;
	
	float time_fps = 0.f;
	int count_frame = 0;

	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");


	while (window.isOpen())
	{
		time_since_last_update += c.restart().asSeconds();

		while (time_since_last_update >= time_per_frame)
		{
			time_since_last_update -= time_per_frame;

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)					
				{
					sp.play();
					
					isPlayed = true;
				}

			}

			
		}

		if (isPlayed)
		{
			sp.update(time_per_frame);
		}

		

		window.clear();
		sp.draw(window);
		window.display();

		time_fps += c.getElapsedTime().asSeconds();
		count_frame++;
		if (time_fps >= 1.f)
		{
			time_fps -= 1.f;
			system("cls");
			std::cout << "FPS: " << count_frame;
			count_frame = 0;
		}
	}

	return 0;
}
