#pragma once

template <typename T>
class Matrix {
public:
	std::vector<std::vector<T>> matrix;
	Matrix(unsigned int x, unsigned int y) {
		matrix.resize(x);
		for (size_t i = 0; i < x; i++) {
			matrix[i].resize(y);
		}
	}

	void set(unsigned int x, unsigned int y, T val) {
		matrix[x][y] = val;
	}

	T get(unsigned int x, unsigned int y) {
		return matrix[x][y];
	}


	template <typename T2>
	Matrix<T> operator*(T2 const& scalar) const {
		Matrix<T> temp = *this;
		for (unsigned int y = 0; y < temp.size(); y++) {
			for (unsigned int x = 0; x < temp[y].size(); x++) {
				temp[y][x] = scalar * temp[y][x];
			}
		}
		return temp;
	}

	T convolution(Matrix<T> const& mat, unsigned int const& cy, unsigned int const& cx) const {
		double output = 0;
		for (unsigned int y = cy - matrix.size() / 2; y < cy + matrix.size() / 2; y++) {
			unsigned int tempy = y;
			if (y < 0) {
				tempy = 0;
			} else if (y >= mat.matrix.size()) {
				tempy = mat.matrix.size() - 1;
			}
			for (unsigned int x = cx - matrix[0].size() / 2; x < cx + matrix[0].size() / 2; x++) {
				unsigned int tempx = x;
				if (x < 0) {
					tempx = 0;
				} else if (x >= mat.matrix[0].size()) {
					tempx = mat.matrix[0].size() - 1;
				}

				output += mat.matrix[tempy][tempx] * matrix[y - (cy - matrix.size() / 2)][ x - (cx - matrix[0].size() / 2)];
			}
		}
		return output;
	}
};

template <typename T>
inline Matrix<T> operator*(T const& scalar, Matrix<T>& m) {
	Matrix<T> temp = m;
	for (unsigned int y = 0; y < temp.matrix.size(); y++) {
		for (unsigned int x = 0; x < temp.matrix[y].size(); x++) {
			temp.set(y, x, scalar * temp.get(y, x));
		}
	}
	return temp;
}