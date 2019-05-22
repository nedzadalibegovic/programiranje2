#include <iostream>
using namespace std;

template <class T>
class Matrix {
	T* arr;
	size_t x, y;
public:
	Matrix(size_t x, size_t y) {
		this->x = x;
		this->y = y;
		arr = new T[x * y]();
	}

	Matrix(const Matrix& src) {
		x = src.x;
		y = src.y;
		arr = new T[x * y];

		for (size_t i = 0; i < x * y; i++)
			arr[i] = src.arr[i];
	}

	Matrix(Matrix&& src) {
		x = src.x;
		y = src.y;
		arr = src.arr;
		src.arr = nullptr;
	}

	~Matrix() {
		delete[] arr;
	}

	friend void swap(Matrix& lhs, Matrix& rhs) {
		using std::swap;

		swap(lhs.arr, rhs.arr);
		swap(lhs.x, rhs.x);
		swap(lhs.y, rhs.y);
	}

	Matrix& operator=(Matrix src) {
		swap(*this, src);
		return *this;
	}

	T& operator()(size_t i, size_t j) {
		return arr[i * y + j];
	}

	int sizeX() const { return x; }
	int sizeY() const { return y; }
};

int main() {
	Matrix<int> matrica(3, 3);

	int unos = 1;

	for (size_t i = 0; i < matrica.sizeX(); i++) {
		for (size_t j = 0; j < matrica.sizeY(); j++) {
			matrica(i, j) = unos++;
		}
	}

	Matrix<int> matrica1(matrica);

	for (size_t i = 0; i < matrica1.sizeX(); i++) {
		for (size_t j = 0; j < matrica1.sizeY(); j++) {
			cout << matrica1(i, j) << " ";
		}
		cout << "\n";
	}
}