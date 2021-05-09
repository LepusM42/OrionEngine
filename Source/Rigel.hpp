/******************************************************************************!
* \file Rigel.hpp
* \author Lepus
* \brief Math library developed for use in OrionEngine. Allows operations with
* vectors and matrices.
*******************************************************************************/
#pragma once
#include <vector>
namespace Rigel
{
	/**************************************************************************!
	* \class Vector
	* \brief An n-dimensional vector, containing n components of any supported
	* type. Supported type in this context means that the operations used by
	* Rigel vectors (multiplication, addition, etc.) are supported by the type
	* in question. Built-in types, such as int and float, are the intended types
	* for building Rigel vectors, as they support such operations.
	***************************************************************************/
	template <typename T>
	class Vector
	{
	public:
		//! Create a vector whose components are all one value.
		Vector(const T value, unsigned size);
		//! Copy the contents of an array into a Rigel vector.
		Vector(const T* array, unsigned size);
		//! Copy the contents of a std::vector into a Rigel vector.
		Vector(std::vector<T> array);
		//! Scale a vector by a scalar value.
		const Vector<T> operator*(T scalar);
		//! Find the dot product of two vectors.
		const T operator*(Vector<T> vector);
		//! Get the number of components this vector contains.
		unsigned size();
		//! Access a component.
		const T operator[](unsigned index);
		//! Magnitude of a vector.
		T magnitude();
	private:
		//! Allocate memory for a vector using the stored dimension.
		T* AllocateVector();
		//! List of values this vector contains. This can be used to represent a
		//! point in space or an n-dimensional line.
		T* m_components{};
		//! Number of components this vector contains.
		unsigned m_dim{ 0 };
	};

	/**************************************************************************!
	* \class Matrix
	* \brief An n*m-dimensional matrix, used to transform vectors and matrices.
	* Rigel matrices must be made up of data types that support basic arithmetic
	* operations, such as multiplication and addition. Built-in types, such as
	* int and float, are the intended types for building Rigel matrices, as they
	* support such operations.
	***************************************************************************/
	template <typename T>
	class Matrix
	{
	public:
		//! Copy constructor that deep copies the contents of one matrix into
		//! the new matrix.
		Matrix(const Matrix<T>& other);
		//! Create an identity matrix of a specified width.
		Matrix(unsigned width);
		//! Create a matrix of different dimensions containing one value.
		Matrix(const T value, unsigned width, unsigned height);
		//! Copy the contents of an array into a matrix of two different
		//! dimensions.
		Matrix(const T* array, unsigned width, unsigned height);
		//! Copy the contents of a vector into a matrix of two different
		//! dimensions.
		Matrix(std::vector<T> array, unsigned width, unsigned height);
		//! Copy the contents of a Rigel vector into a matrix of two different
		//! dimensions.
		Matrix(Vector<T> array, unsigned width, unsigned height);
		//! Create a matrix that rotates a vector about a point in 2D space.
		static Matrix<T> RotationMatrix2D(T theta);
		//! Create a matrix that rotates a vector about an axis in 3D space.
		static Matrix<T> RotationMatrix3D(Vector<T> axis, T theta);
		//! Create a matrix from a vector.
		static Matrix<T> MatrixFromVector(Vector<T> vector, bool transpose);
		//! Create a new resultant matrix by scaling an existing matrix by a 
		//! scalar value.
		const Matrix<T> operator*(T scalar);
		//! Scale a matrix by a scalar value.
		Matrix<T>& operator*=(T scalar);
		//! Multiply a matrix by another matrix.
		const Matrix<T> operator*(Matrix<T> matrix);
		//! Transform a vector by multiplying it by a matrix.
		const Vector<T> operator*(Vector<T> vector);
		//! Destructor deallocates the memory used for the internal matrix.
		~Matrix();
	private:
		//! Allocate memory for a matrix using the stored width and height.
		T** AllocateMatrix();
		//! List of values that the matrix contains.
		T** m_matrix{};
		//! Width of the matrix.
		unsigned m_width{ 0 };
		//! Height of the matrix.
		unsigned m_height{ 0 };
	};
}
#include "RigelVector.cpp" //Templated vector operations.
#include "RigelMatrix.cpp" //Templated matrix operations.