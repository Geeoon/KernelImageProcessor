template <typename T>
class Matrix {
private:
	std::vector<std::vector<T>> matrix;

public:
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
};