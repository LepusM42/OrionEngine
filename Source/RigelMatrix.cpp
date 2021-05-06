/******************************************************************************!
* \file RigelMatrix.cpp
* \author Lepus
* \brief Contains all implementation of matrix operations in the Rigel Math
* Library.
*******************************************************************************/
namespace Rigel
{
	/**************************************************************************!
	* \fn Matrix<T>::Matrix(const Matrix<T>& other);
	* \brief Copy constructor that deep copies the contents of one matrix into
	*  the new matrix.
	* \param other Copied matrix.
	***************************************************************************/
	template <typename T>
	Matrix<T>::Matrix(const Matrix<T>& other) :
		m_width{ other.m_width },
		m_height{ other.m_height }
	{
		m_matrix = AllocateMatrix();
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < m_width; ++j)
			{
				m_matrix[i][j] = other.m_matrix[i][j];
			}
		}
	}

	/**************************************************************************!
	* \fn Matrix<T>::Matrix(unsigned width);
	* \brief Create an identity matrix of a specified width. This is a matrix
	*  consisting of all 0's, save for a diagonal of 1's.
	* \param width Used for the width and height of the created matrix.
	***************************************************************************/
	template <typename T>
	Matrix<T>::Matrix(unsigned width) :
		m_width{ width },
		m_height{ width }
	{
		m_matrix = AllocateMatrix();
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < m_width; ++j)
			{
				m_matrix[i][j] = i == j;
			}
		}
	}

	/**************************************************************************!
	* \fn Matrix<T>:: Matrix(const T value, unsigned width, unsigned height);
	* \brief Create a matrix of different dimensions containing one value.
	* \param value Value to fill the matrix with.
	* \param width Width of the matrix to be created.
	* \param height Height of the matrix to be created.
	***************************************************************************/
	template <typename T>
	Matrix<T>:: Matrix(const T value, unsigned width, unsigned height) :
		m_width{ width },
		m_height{ height }
	{
		m_matrix = AllocateMatrix();
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < m_width; ++j)
			{
				m_matrix[i][j] = value;
			}
		}
	}

	/**************************************************************************!
	* \fn Matrix<T>::Matrix(const T* array, unsigned width, unsigned height);
	* \brief Copy the contents of an array into a matrix of two different
	*  dimensions.
	* \param array List of values to pass into this matrix.
	* \param width Width of the matrix to be created.
	* \param height Height of the matrix to be created.
	***************************************************************************/
	template <typename T>
	Matrix<T>::Matrix(const T* array, unsigned width, unsigned height) :
		m_width{ width },
		m_height{ height }
	{
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < m_width; ++j)
			{
				m_matrix[i][j] = array[i][j];
			}
		}
	}

	/**************************************************************************!
	* \fn Matrix<T>::Matrix(std::vector<T> vector, unsigned width,
	*  unsigned height);
	* \brief Copy the contents of a vector into a matrix of two different
	*  dimensions.
	* \param vector List of values to pass into this matrix.
	* \param width Width of the matrix to be created.
	* \param height Height of the matrix to be created.
	***************************************************************************/
	template <typename T>
	Matrix<T>::Matrix(std::vector<T> vector, unsigned width, unsigned height) :
		m_width{ width },
		m_height{ height }
	{
		m_matrix = AllocateMatrix();
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < m_width; ++j)
			{
				m_matrix[i][j] = vector[i][j];
			}
		}
	}

	/**************************************************************************!
	* \fn Matrix<T>::Matrix(Vector<T> vector, unsigned width, unsigned height);
	* \brief Copy the contents of a Rigel vector into a matrix of two different
	*  dimensions.
	* \param vector List of values to pass into this matrix.
	* \param width Width of the matrix to be created.
	* \param height Height of the matrix to be created.
	***************************************************************************/
	template <typename T>
	Matrix<T>::Matrix(Vector<T> vector, unsigned width, unsigned height) :
		m_width{ width },
		m_height{ height }
	{
		m_matrix = AllocateMatrix();
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < m_width; ++j)
			{
				m_matrix[i][j] = vector[i][j];
			}
		}
	}

	/**************************************************************************!
	* \fn Matrix<T> Matrix<T>::RotationMatrix2D(T theta);
	* \brief Create a matrix that rotates a vector about the origin in 2D space.
	* \param theta How far input vectors will be rotated.
	* \return Matrix used to perform a rotation by the given amount about the
	*  origin in 2D space.
	***************************************************************************/
	template <typename T>
	Matrix<T> Matrix<T>::RotationMatrix2D(T theta)
	{
		T rotationMatrixValues[4] = { cos(theta), -sin(theta),
									  sin(theta),  cos(theta) };
		return Matrix<T>(rotationMatrixValues, 2, 2);
	}

	/**************************************************************************!
	* \fn Matrix<T> Matrix<T>::RotationMatrix3D(Vector<T> axis, T theta);
	* \brief Create a matrix that rotates a vector about an axis in 3D space.
	* \param axis 3D directional vector from the origin representing an axis
	*  about which input vectors will be rotated.
	* \param theta How far input vectors will be rotated.
	* \return Matrix used to perform a rotation by the given amount about a
	*  directional vector from the origin in 3D space.
	***************************************************************************/
	template <typename T>
	Matrix<T> Matrix<T>::RotationMatrix3D(Vector<T> axis, T theta)
	{
		T a = axis[0],
		  b = axis[1],
		  c = axis[2];
		T rotationMatrixValues[9] = { 0, -c,  b,
									  c,  0, -a,
									 -b,  a,  0 };
		Matrix<T> m0 = Matrix(rotationMatrixValues, 3, 3);
		m0 *= (sin(theta) / axis.magnitude());
		Matrix<T> m1 = Matrix<T>::MatrixFromVector(axis, false);
		Matrix<T> m2 = Matrix<T>::MatrixFromVector(axis, true);
		Matrix<T> m3 = ((m1 * m3) * 1 / (axis * axis)) * (1 - cos(theta));
		Matrix<T> m4 = Matrix<T>(3) * cos(theta);
		Matrix<T> finalMatrix = m3 + m4 + m0;
		return finalMatrix;
	}

	//!
	/**************************************************************************!
	* \fn Matrix<T> Matrix<T>::MatrixFromVector(Vector<T> vector,
	   bool transpose);
	* \brief Create a matrix from a vector.
	* \param vector Vector to convert to a matrix.
	* \param transpose Whether to swap the width and height of the resulting
	*  matrix, swapping the columns and rows in the process.
	* \return If transpose is false, returns a matrix with width of 1, or a
	*  matrix with height of 1 otherwise. The components of this matrix are
	*  equal to those of the original vector.
	***************************************************************************/
	template <typename T>
	Matrix<T> Matrix<T>::MatrixFromVector(Vector<T> vector, bool transpose)
	{
		unsigned width, height;
		if (transpose)
		{
			width = vector.size();
			height = 1;
		}
		else
		{
			width = 1;
			height = vector.size();
		}
		return Matrix<T>(vector, width, height);
	}

	/**************************************************************************!
	* \fn const Matrix<T> Matrix<T>::operator*(T scalar);
	* \brief Create a new resultant matrix by scaling an existing matrix by a
	*  scalar value.
	* \param scalar Value by which this matrix will be scaled.
	* \return A new matrix, equal to the original scaled by the passed in value.
	***************************************************************************/
	template <typename T>
	const Matrix<T> Matrix<T>::operator*(T scalar)
	{
		Matrix<T> newMatrix(*this);
		newMatrix *= scalar;
		return newMatrix;
	}

	/**************************************************************************!
	* \fn Matrix<T>& Matrix<T>::operator*=(T scalar);
	* \brief Scale a matrix by a scalar value.
	* \param scalar Value by which this matrix will be scaled.
	* \return A reference to the scaled matrix.
	***************************************************************************/
	template <typename T>
	Matrix<T>& Matrix<T>::operator*=(T scalar)
	{
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < m_width; ++j)
			{
				m_matrix[i][j] = m_matrix[i][j] * scalar;
			}
		}
		return *this;
	}

	/**************************************************************************!
	* \fn const Matrix<T> Matrix<T>::operator*(Matrix<T> other);
	* \brief Multiply a matrix by another matrix.
	* \param other Other matrix, which will be transformed by this matrix. The
	*  height of the other matrix must be equal to the height of this matrix.
	* \return The product of the two matrices. If the two matrices cannot be
	*  multiplied due to a difference in dimension as detailed above, a zero
	*  matrix is returned.
	***************************************************************************/
	template <typename T>
	const Matrix<T> Matrix<T>::operator*(Matrix<T> other)
	{
		Matrix<T> newMatrix(0, other.m_width, m_height);
		T sum;
		if (m_width != other.m_height)
		{
			return newMatrix;
		}
		for (unsigned i = 0; i < m_height; ++i)
		{
			for (unsigned j = 0; j < other.m_width; ++j)
			{
				sum = 0;
				for (unsigned k = 0; k < other.m_height; ++k)
				{
					sum += m_matrix[i][k] * other.m_matrix[k][j];
				}
				newMatrix.m_matrix[i][j] = sum;
			}
		}
		return newMatrix;
	}

	/**************************************************************************!
	* \fn const Vector<T> Matrix<T>::operator*(Vector<T> vector);
	* \brief Transform a vector by multiplying it by a matrix.
	* \param vector Vector to transform. The dimension of this vector must be
	*  equal to the width of the matrix it is being transformed by.
	* \return A new vector, transformed by this matrix. If the dimension of the
	*  vector is not equal to the width of the matrix, a zero vector is returned.
	***************************************************************************/
	template <typename T>
	const Vector<T> Matrix<T>::operator*(Vector<T> vector)
	{
		unsigned size = vector.size();
		Vector<T> newVector(0, size);
		T sum;
		if (m_width != size)
		{
			return newVector;
		}
		for (unsigned i = 0; i < m_height; ++i)
		{
			sum = 0;
			for (unsigned j = 0; j < size; ++j)
			{
				sum += m_matrix[i][j] * vector[j];
			}
			newVector[i] = sum;
		}
		return newVector;
	}

	/**************************************************************************!
	* \fn T* Matrix<T>::AllocateMatrix();
	* \brief Allocate memory for a matrix using the stored width and height.
	* \return Block of memory large enough to hold the data necessary for this
	*  matrix. The size of this block is equal to the product of the width of the
	*  matrix, the height of the matrix, and the size of the data type used for
	*  this matrix.
	***************************************************************************/
	template <typename T>
	T* Matrix<T>::AllocateMatrix()
	{
		return new T[m_width * m_height]{ 0 };
	}

	/**************************************************************************!
	* \fn Matrix<T>::~Matrix();
	* \brief Destructor deallocates the memory used for the internal matrix.
	***************************************************************************/
	template <typename T>
	Matrix<T>::~Matrix()
	{
		delete[] m_matrix;
	}
}