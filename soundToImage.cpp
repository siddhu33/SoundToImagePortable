#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "colorManipulation.cpp"

//uses SFML to load audio, convert into image using HSV encoding, and then display.
void audio_to_image(std::string inputFile, std::string outputFile) {
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(inputFile))
	{
		std::cout << "File load of " << inputFile << " is unsuccessful.\n";
	}
	const sf::Int16 *sampleArray = buffer.getSamples();
	unsigned int channelCount = buffer.getChannelCount();
	sf::Uint64 sampleCount = buffer.getSampleCount();
	std::cout << inputFile << "\nChannel Count:" << channelCount << "\nSample Count:" << sampleCount << "\n";
	int seconds = sampleCount / channelCount / buffer.getSampleRate();
	std::cout << "Length: " << seconds << "s\n";
	int horizontal = 210 * (int)std::ceil(std::sqrt(seconds));
	int vertical = (sampleCount / channelCount) / horizontal + 1;
	std::cout << "Image dimensions:[" << horizontal << "," << vertical << "]\n";
	sf::Uint8* imageArray = new sf::Uint8[horizontal*vertical*4];
	int imageSeek = 0;
	for (uint i = 0; i < sampleCount; i += 2) {
		/*double left = sampleArray[i] / 32768.0;
		double right = sampleArray[i + 1] / 32768.0;
		hsv inColor;
		inColor.h = 180.0 * (left + 1.0);
		inColor.s = right / 2.0 + 0.5;
		inColor.v = 0.5;
		rgb outColor = hsv2rgb(inColor);
		*/
		imageArray[imageSeek] = sampleArray[i] >> 8;
		imageArray[imageSeek + 1] = sampleArray[i] & 0xFF;
		imageArray[imageSeek + 2] = sampleArray[i+1] >> 8;
		imageArray[imageSeek + 3] = sampleArray[i+1] & 0xFF;
		imageSeek += 4;
	}
	sf::Image outputImage;
	outputImage.create(horizontal, vertical, imageArray);
	if (!outputImage.saveToFile(outputFile))
		std::cout << "Output save of " << outputFile << " is unsuccessful.\n";
}

void image_to_audio(std::string inputFile, std::string outputFile) {
	sf::Image inputImage;
	if (!inputImage.loadFromFile(inputFile))
	{
		std::cerr << "File load of " << inputFile << " is unsuccessful.\n";
	}
	const sf::Uint8 *imageArray = inputImage.getPixelsPtr();
	sf::Vector2u size = inputImage.getSize();
	int totalPixels = size.x*size.y * 4;
	std::vector<sf::Int16> samples;
	for (int i = 0; i < totalPixels; i += 4) {
		/*rgb pixel = { imageArray[i] / 255.0,imageArray[i + 1] / 255.0,imageArray[i + 2] / 255.0 };
		hsv out = rgb2hsv(pixel);
		samples.push_back((sf::Int16)(32768.0*(out.h - 180.0) / 180.0));
		samples.push_back((sf::Int16)(32768.0*(out.s - 0.5) * 2.0));*/
		sf::Int16 left = (imageArray[i] << 8) | imageArray[i + 1];
		sf::Int16 right = (imageArray[i + 2] << 8) | imageArray[i + 3];
		samples.push_back(left);
		samples.push_back(right);
	}
	sf::OutputSoundFile file;
	const sf::Int16 *start = &samples[0];
	if (!file.openFromFile(outputFile, 44100, 2))
		std::cerr << "File load of " << outputFile << " is unsuccessful.\n";
	file.write(start, samples.size());
}



int main(int argc, char** argv) {
	int mode;
	std::string inputFile;
	std::string outputFile;
	if (argc < 4) {
		std::cout << "USAGE:\nSoundToImagePortable [mode] [input_file] [output_file]\nMode Options:\n0-Audio to Image\n1-Image to Audio\n";
	}
	else {
		mode = atoi(argv[1]);
		inputFile = argv[2];
		outputFile = argv[3];
		if (mode == 0) {
			audio_to_image(inputFile, outputFile);
			std::cout << "Image " << outputFile << " created.\n";
		}
		else if (mode == 1){
			image_to_audio(inputFile, outputFile);
			std::cout << "Audio file " << outputFile << " has been created.\n";
		}
		else {
			std::cout << "Invalid mode\n";
		}
	}
	return 0;
}
