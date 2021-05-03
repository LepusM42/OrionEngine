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
		Vector(const T value, unsigned size);
		Vector(const T* array, unsigned size);
		Vector(std::vector<T> array);
		const Vector<T> operator*(T scalar);
		const T operator*(Vector<T> vector);
	private:
		std::vector<T> m_components{};
		unsigned m_dim{ 0 };
	};
}
#include "Rigel.cpp"