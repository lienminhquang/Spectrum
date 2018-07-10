#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <cmath>
#include <complex>
#include <valarray>

#define PI 3.1415926535897f
typedef std::complex<double> base;
typedef std::valarray<std::complex<double>> CArray;
typedef std::complex<double> Complex;

#define BUFFER_SIZE 16384

class Spectrum_visualize
{
public:
	Spectrum_visualize(const std::string& fileName);
	~Spectrum_visualize();

	void take_samples_and_hammingWindow();
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void update_vertex_array();
	void play();

private:

	float _hammingWindow[BUFFER_SIZE];
	std::vector<base> _samples;
	int _samplesRate;
	sf::SoundBuffer _sound_buffer;
	sf::Sound _sound;

	CArray bins;

	sf::VertexArray VA1;
	sf::VertexArray VA2;
};

