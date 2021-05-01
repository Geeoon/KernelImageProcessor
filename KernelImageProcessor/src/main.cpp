#include "png++/png.hpp"
#include "math/Matrix.h"

int main() {

	png::image< png::rgb_pixel_16 > inputImage{ "images/source/liberty.png" };
	Matrix< double > inputMatrixR{ inputImage.get_height(), inputImage.get_width() };
	Matrix< double > inputMatrixG{ inputImage.get_height(), inputImage.get_width() };
	Matrix< double > inputMatrixB{ inputImage.get_height(), inputImage.get_width() };

	// load image to matrix for maniupulation
	for (unsigned int y = 0; y < inputImage.get_height(); y++) {
		for (unsigned int x = 0; x < inputImage.get_width(); x++) {
			inputMatrixR.set(y, x, inputImage[y][x].red);
			inputMatrixG.set(y, x, inputImage[y][x].green);
			inputMatrixB.set(y, x, inputImage[y][x].blue);
		}
	}

	Matrix< double > outputMatrixR{ inputImage.get_height(), inputImage.get_width() };
	Matrix< double > outputMatrixG{ inputImage.get_height(), inputImage.get_width() };
	Matrix< double > outputMatrixB{ inputImage.get_height(), inputImage.get_width() };

	Matrix< double > gaussBlurKernel{ 3, 3 };
	gaussBlurKernel.set(0, 0, 1.0);
	gaussBlurKernel.set(0, 1, 2.0);
	gaussBlurKernel.set(0, 2, 1.0);
	gaussBlurKernel.set(1, 0, 2.0);
	gaussBlurKernel.set(1, 1, 4.0);
	gaussBlurKernel.set(1, 2, 2.0);
	gaussBlurKernel.set(2, 0, 1.0);
	gaussBlurKernel.set(2, 1, 2.0);
	gaussBlurKernel.set(2, 2, 1.0);
	gaussBlurKernel = (1 / 16.0) * gaussBlurKernel;

	Matrix< double > identityKernel{ 3, 3 };
	identityKernel.set(0, 0, 0.0);
	identityKernel.set(0, 1, 0.0);
	identityKernel.set(0, 2, 0.0);
	identityKernel.set(1, 0, 0.0);
	identityKernel.set(1, 1, 1.0);
	identityKernel.set(1, 2, 0.0);
	identityKernel.set(2, 0, 0.0);
	identityKernel.set(2, 1, 0.0);
	identityKernel.set(2, 2, 0.0);

	for (unsigned int y = 0; y < inputImage.get_height(); y++) {
		for (unsigned int x = 0; x < inputImage.get_width(); x++) {
			outputMatrixR.set(y, x, identityKernel.convolution(inputMatrixR, y, x));
			outputMatrixG.set(y, x, identityKernel.convolution(inputMatrixG, y, x));
			outputMatrixB.set(y, x, identityKernel.convolution(inputMatrixB, y, x));
		}
	}

	// load matrix onto image
	png::image< png::rgb_pixel_16 > outputImage{ inputImage.get_width(), inputImage.get_height() };
	for (unsigned int y = 0; y < inputImage.get_height(); y++) {
		for (unsigned int x = 0; x < inputImage.get_width(); x++) {
			outputImage[y][x] = png::rgb_pixel_16(static_cast< png::uint_16 >(outputMatrixR.get(y, x)), static_cast< png::uint_16 >(outputMatrixG.get(y, x)), static_cast< png::uint_16 >(outputMatrixB.get(y, x)));
		}
	}

	outputImage.write("images/output/output.png");
	return 0;
}

