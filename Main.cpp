#include <SFML/Graphics.hpp>
#include <ccomplex>
#include "SFML\Audio.hpp"
#include <iostream>
#include <valarray>
#include <cmath>
#include "Spectrum_visualize.h"

using namespace std;

//#define PI 3.1415926535897

//typedef std::complex<double> Complex;
//
//typedef std::valarray<std::complex<double>> CArray;
//
//void fft(CArray &x)
//{
//	const int N = x.size();
//	if (N <= 1) return;
//
//	CArray even = x[slice(0, N / 2, 2)];
//	CArray  odd = x[slice(1, N / 2, 2)];
//
//	fft(even);
//	fft(odd);
//
//	for (int k = 0; k < N / 2; k++)
//	{
//		Complex t = polar(1.0, -2 * PI * k / N) * odd[k];
//		x[k] = even[k] + t;
//		x[k + N / 2] = even[k] - t;
//	}
//}
//
//void compute_spectrum(CArray& arr, sf::VertexArray& verA)
//{
//	verA.clear();
//
//	for (float i(3); i < arr.size() / 2; ++i)
//	{
//		verA.append(sf::Vertex(sf::Vector2f(30 + 2*i, 500), sf::Color::Blue));
//		verA.append(sf::Vertex(sf::Vector2f(30 + 2*i , 500 - abs(arr[(int)i]) / 100000.f), sf::Color::White));
//		verA.append(sf::Vertex(sf::Vector2f(30 + 2*i + 3, 500 - abs(arr[(int)i]) / 100000.f), sf::Color::White));
//		verA.append(sf::Vertex(sf::Vector2f(30 + 2*i + 3, 500), sf::Color::Blue));
//	}
//}
//
//void hammingWindow(CArray& carr, float* hwindow, int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		carr[i].real(carr[i].real() * hwindow[i]);
//	}
//}


int main()
{

	std::cout << "File name (.wav): ";
	string fileName;
	std::cin >> fileName;

	Spectrum_visualize sp("Resources/" + fileName);

	//sf::VertexArray mVertexArray(sf::Quads);

	bool isPlayed = false;

	/*sf::SoundBuffer _soundBuffer;
	_soundBuffer.loadFromFile("Resources/ass.wav");
	sf::Sound s(_soundBuffer);

	float rate = _soundBuffer.getSampleRate() * _soundBuffer.getChannelCount();

	const int SIZE = 16384;
	std::vector<Complex> sample(SIZE);
	CArray bin(SIZE);
	
	float hwindow[SIZE];*/


	//for (size_t i = 0; i < SIZE; i++)
	//{
	//	hwindow[i] = 0.54f - 0.46f * cos((2 * PI * i) / (SIZE));
	//	
	//}



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
					//s.play();
					isPlayed = true;
				}

			}

			
		}

		if (isPlayed)
		{
			/*int offset = s.getPlayingOffset().asSeconds() * rate;
		

			for (int i(0); i + offset < _soundBuffer.getSampleCount() && i < SIZE ; ++i)
			{
				if (i + offset -SIZE / 2 <= 0) continue;

				sample[i] = (Complex(_soundBuffer.getSamples()[i + offset - SIZE / 2] * hwindow[i], 0));
			}

			

			bin = CArray(sample.data(), SIZE);
			fft(bin);
			compute_spectrum(bin, mVertexArray);*/

			sp.update(time_per_frame);
		}

		

		window.clear();
		//window.draw(mVertexArray);
		sp.draw(window);
		window.display();
		/*if (isPlayed) {
			float dt = s.getPlayingOffset().asSeconds();
			dt = 0;
		}*/

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