#include "Spectrum_visualize.h"



void mfft(std::vector<base> & a, bool invert) {
	int n = (int)a.size();

	for (int i = 1, j = 0; i<n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i<n; i += len) {
			base w(1);
			for (int j = 0; j<len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i = 0; i<n; ++i)
			a[i] /= n;
}




Spectrum_visualize::Spectrum_visualize(const std::string& fileName):
	_samples(BUFFER_SIZE),
	VA2(sf::LinesStrip),
	VA1(sf::Quads)
{
	_sound_buffer.loadFromFile(fileName);
	_sound.setBuffer(_sound_buffer);
	_samplesRate = _sound_buffer.getSampleRate() * _sound_buffer.getChannelCount();


	//initialize cho ham window
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		_hammingWindow[i] = 0.54f - 0.46f * cos((2 * PI * i) / (BUFFER_SIZE));
	}

}


Spectrum_visualize::~Spectrum_visualize()
{
}

void Spectrum_visualize::take_samples_and_hammingWindow()
{
	int offset = _sound.getPlayingOffset().asSeconds() * _samplesRate;

	for (int i = 0; i < BUFFER_SIZE && i + offset < _sound_buffer.getSampleCount(); i++)
	{
		_samples[i] = Complex(_sound_buffer.getSamples()[i + offset] * _hammingWindow[i], 0);
	}
}

void Spectrum_visualize::update(float dt)
{
	take_samples_and_hammingWindow();

	//bins = CArray(_samples.data(), BUFFER_SIZE);

	//fft(bins);

	mfft(_samples, false);

	update_vertex_array();
}

void Spectrum_visualize::draw(sf::RenderWindow& window)
{
	window.draw(VA1);
	window.draw(VA2);
}

void Spectrum_visualize::update_vertex_array()
{
	VA1.clear();
	//VA2.clear();

	sf::Vector2f original_pos(50.f, 500.f);


	for (int i = 0; i < BUFFER_SIZE / 2 && i < 200; i++)
	{
		//sf::Vector2f samples_pos(i + i, abs(_samples[i]));
		float dB = abs(_samples[i]);

		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i, 500), sf::Color::Blue));
		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i, 500 - dB / 100000.f), sf::Color::White));
		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i + 3, 500 - dB / 100000.f), sf::Color::White));
		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i + 3, 500), sf::Color::Blue));

		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i, 500), sf::Color(255, 255, 255, 100)));
		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i + 3, 500), sf::Color(255, 255, 255, 100)));
		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i + 3, 500 + dB / 500000.f), sf::Color(255, 255, 255, 0)));
		VA1.append(sf::Vertex(sf::Vector2f(30 + 5 * i, 500 + dB / 500000.f), sf::Color(255, 255, 255, 0)));

		//VA2.append(sf::Vertex(sf::Vector2f(30 + 5 * i, 500 - dB / 100000.f), sf::Color::White));
		
	}
}

void Spectrum_visualize::play()
{
	_sound.play();
}
