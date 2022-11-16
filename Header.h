#pragma once
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <stdlib.h>
#include <conio.h>

using namespace std;

double epsilon = 0.000000001;

class matrix
{
private:
	double** data;
	size_t _columns, _rows;

public:
	matrix() {
		srand(time(0));
		_rows = rand() % 3 + 2;
		_columns = _rows;
		data = new double* [_rows];
		for (size_t i = 0; i < _rows; ++i)
		{
			data[i] = new double[_columns];
		}
		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _columns; j++)
			{
				data[i][j] = (rand() % 300) / 10.0;
			}
		}
	}

	matrix(size_t rows, size_t columns) {
		if (columns < 1 or rows < 1) throw "Invalid matrix size";

		_columns = columns;
		_rows = rows;

		data = new double* [_rows];
		for (size_t i = 0; i < _rows; ++i)
		{
			data[i] = new double[_columns];
		}

		cout << "Input your values" << "\n";
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _columns; j++)
			{
				double _temp;
				cout << "Input value of index [" << i + 1 << "][" << j + 1 << "]: ";
				cin >> _temp;
				data[i][j] = _temp;
				cout << endl;
			}
		}
	}


	matrix(const matrix& m) {
		data = new double* [m._rows];
		for (size_t i = 0; i < m._rows; ++i)
		{
			data[i] = new double[m._columns];
		}

		_rows = m._rows;
		_columns = m._columns;

		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _columns; j++)
			{
				data[i][j] = m.data[i][j];
			}
		}

	}

	matrix(double** temp, int rows, int columns) {
		if (rows < 1 or columns < 1) throw "Invalid matrix size";

		_rows = rows;
		_columns = columns;

		data = new double* [_rows];
		for (size_t i = 0; i < _rows; ++i)
		{
			data[i] = new double[_columns];
		}

		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _columns; j++)
			{
				data[i][j] = temp[i][j];
			}
		}
	}

	matrix(const matrix& a, const matrix& b, const matrix& c) {
		if ((a._rows != 1 or a._columns != 3) or (b._rows != 1 or b._columns != 3) or (c._rows != 1 or c._columns != 3)) throw "Invalid matrix size";

		_rows = _columns = 3;

		data = new double* [_rows];
		for (size_t i = 0; i < _rows; i++)
		{
			data[i] = new double[_columns];
		}

		for (size_t i = 0; i < _rows; i++)
		{
			int k = 0;
			int j = 0;

			data[j][i] = a.data[k][i];
			j++;

			data[j][i] = b.data[k][i];
			j++;

			data[j][i] = c.data[k][i];
		}

	}

	~matrix() {
		for (size_t i = 0; i < _rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}

	//Getters
	size_t get_rows() { return _rows; }

	size_t get_columns() { return _columns; }

	//Перегрузка cout
	friend ostream& operator << (ostream& os, const matrix& m)
	{
		for (size_t i = 0; i < m._rows; ++i)
		{
			for (size_t j = 0; j < m._columns; ++j)
			{
				os << left << m.data[i][j] << '\t';
			}
			os << endl;
		}
		return os;
	}

	// оператор () для чтения/записи элемента матрицы по указанным индексам;
	double& operator()(int i, int j) {
		if ((i < 0 or i >= _rows) or (j < 0 or j >= _columns)) throw "Invalid index";
		return data[i][j];
	}

	//операторы сложения и вычитания матриц;
	matrix& operator+=(const matrix& m) {
		if (_rows != m._rows or _columns != m._columns) throw "Size of matrix doesn't equal";
		double** temp;

		temp = new double* [m._rows];
		for (size_t i = 0; i < m._rows; ++i)
		{
			temp[i] = new double[m._columns];
		}

		for (size_t i = 0; i < _rows; ++i)
		{
			for (size_t j = 0; j < _columns; ++j)
			{
				temp[i][j] = data[i][j] + m.data[i][j];
			}
		}

		for (size_t i = 0; i < _rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	matrix operator+(const matrix& m) const {
		matrix temp(*this);
		temp += m;
		return temp;
	}

	matrix& operator-=(const matrix& m) {
		if (_rows != m._rows or _columns != m._columns) throw "Size of matrix doesn't equal";
		double** temp;

		temp = new double* [m._rows];
		for (size_t i = 0; i < m._rows; ++i)
		{
			temp[i] = new double[m._columns];
		}

		for (size_t i = 0; i < _rows; ++i)
		{
			for (size_t j = 0; j < _columns; ++j)
			{
				temp[i][j] = data[i][j] - m.data[i][j];
			}
		}

		for (size_t i = 0; i < _rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	matrix operator-(const matrix& m) const {
		matrix temp(*this);
		temp -= m;
		return temp;
	}

	//оператор умножения матриц;
	matrix& operator*=(const matrix& m) {
		if (_columns != m._rows) throw "Size of matrix doesn't equal";

		double** temp;

		temp = new double* [_rows];
		for (size_t i = 0; i < _rows; i++)
		{
			temp[i] = new double[m._columns];
		}

		for (size_t rows = 0; rows < _rows; rows++)
		{
			for (size_t col = 0; col < m._columns; col++)
			{
				temp[rows][col] = 0;
				for (size_t in_column = 0; in_column < _columns; in_column++)
				{
					temp[rows][col] += data[rows][in_column] * m.data[in_column][col];
				}
			}
		}

		_columns = m._columns;

		for (size_t i = 0; i < _rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;

		data = temp;
		return *this;
	}

	matrix operator*(const matrix& m) {
		matrix temp(*this);
		temp *= m;
		return temp;
	}

	//оператор умножения матрицы на скаляр(обеспечить коммутативность);

	matrix& operator *= (double n) {
		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _columns; j++)
			{
				data[i][j] *= n;
			}
		}
		return *this;
	}
	matrix operator*(double n) {
		matrix temp(*this);
		temp *= n;
		return temp;
	}
	friend matrix& operator*= (double n, matrix& m) {
		for (size_t i = 0; i < m._rows; i++)
		{
			for (size_t j = 0; j < m._columns; j++)
			{
				m.data[i][j] *= n;
			}
		}
		return m;
	}
	friend matrix operator* (double n, matrix& m) {
		matrix temp(m);
		return n *= temp;
	}
	//оператор деления матрицы на скаляр;

	matrix& operator/=(double n) {
		if (n == 0) throw "Division by zero";
		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _columns; j++)
			{
				data[i][j] /= n;
			}
		}
		return *this;
	}

	matrix operator/(double n) {
		matrix temp(*this);
		temp /= n;
		return temp;
	}

	//метод вычисления следа матрицы - сумма членов главной диагонали, при условии, что матрица - квадратичная
	double trace() {
		if (_rows != _columns) throw "The matrix is not square";
		double trace = 0;
		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _columns; j++)
			{
				trace += data[i][j];
			}
		}
		return trace;
	}

	//Сравнение матриц
	bool operator==(const matrix& m) {
		if (_rows != m._rows or _columns != m._columns) {
			return false;
		}
		else {
			for (size_t i = 0; i < _rows; i++)
			{
				for (size_t j = 0; j < _columns; j++)
				{
					if (abs(data[i][j] - m.data[i][j]) > epsilon) {
						return false;
					}
				}
			}
			return true;
		}
	}

	bool operator!=(const matrix& m) {
		return !(*this == m);
	}

	friend double determenant(const matrix& m, int N) {
		if (m._columns != m._rows) {
			return 0;
		}
		else if (N == 1) {
			return m.data[0][0];
		}
		else if (N == 2) {
			return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
		}
		else if (N >= 3) {
			double determ = 0;

			for (int k = 0; k < N; k++) {

				double** temp = new double* [N - 1];
				for (int i = 0; i < N - 1; i++) {
					temp[i] = new double[N - 1];
				}

				for (int i = 1; i < N; i++) {
					for (int j = 0; j < N; j++) {

						if (j == k) {
							continue;
						}
						else if (j < k) {
							temp[i - 1][j] = m.data[i][j];
						}
						else {
							temp[i - 1][j - 1] = m.data[i][j];
						}
					}
				}
				/* cout << matrix(temp, N - 1, N - 1);*/
				determ += pow(-1, k + 2) * m.data[0][k] * determenant(matrix(temp, N - 1, N - 1), N - 1);

				for (size_t i = 0; i < static_cast<unsigned long long>(N) - 1; i++)
				{
					delete[] temp[i];
				}
				delete[] temp;
			}
			return determ;
		}
	}

	matrix& operator = (const matrix& m) {

		for (size_t i = 0; i < _rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
		data = new double* [m._rows];
		for (size_t i = 0; i < m._rows; ++i)
		{
			data[i] = new double[m._columns];
		}

		_rows = m._rows;
		_columns = m._columns;

		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < _columns; j++)
			{
				data[i][j] = m.data[i][j];
			}
		}
		return *this;
	}

	friend bool coplanarns(const matrix& a, const matrix& b, const matrix& c) {
		matrix final(a, b, c);
		double  det = determenant(final, final.get_columns());
		if (det == 0) return true;
		else return false;
	};

};