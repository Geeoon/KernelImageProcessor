#include "CImg.h"
#include "png++/png.hpp"
#include "math/Matrix.h"

int main() {

	png::image< png::rgb_pixel_16 > inputImage{ "images/source/liberty.png" };
	Matrix< png::uint_16 > inputMatrixR{ inputImage.get_height(), inputImage.get_width() };
	Matrix< png::uint_16 > inputMatrixG{ inputImage.get_height(), inputImage.get_width() };
	Matrix< png::uint_16 > inputMatrixB{ inputImage.get_height(), inputImage.get_width() };

	// load image to matrix for maniupulation
	for (unsigned int y = 0; y < inputImage.get_height(); y++) {
		for (unsigned int x = 0; x < inputImage.get_width(); x++) {
			inputMatrixR.set(y, x, inputImage[y][x].red);
			inputMatrixG.set(y, x, inputImage[y][x].green);
			inputMatrixB.set(y, x, inputImage[y][x].blue);
		}
	}

	Matrix< png::uint_16 > outputMatrixR{ inputImage.get_height(), inputImage.get_width() };
	Matrix< png::uint_16 > outputMatrixG{ inputImage.get_height(), inputImage.get_width() };
	Matrix< png::uint_16 > outputMatrixB{ inputImage.get_height(), inputImage.get_width() };

	// load matrix onto image
	png::image< png::rgb_pixel_16 > outputImage{ inputImage.get_width(), inputImage.get_height() };
	for (unsigned int y = 0; y < inputImage.get_height(); y++) {
		for (unsigned int x = 0; x < inputImage.get_width(); x++) {
			outputImage[y][x] = png::rgb_pixel_16(outputMatrixR.get(y, x), outputMatrixG.get(y, x), outputMatrixB.get(y, x));
		}
	}
	outputImage.write("images/output/output.png");
	return 0;
}

