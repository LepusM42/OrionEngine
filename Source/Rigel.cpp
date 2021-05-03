/******************************************************************************!
* \file Rigel.cpp
* \author Lepus
* \brief Math library developed for use in OrionEngine. Allows operations with
* vectors and matrices.
*******************************************************************************/
namespace Rigel
{
	template <typename T>
	Vector<T>::Vector(const T value, unsigned size) :
		m_dim(size)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			m_components.push_back(value);
		}
	}

	template <typename T>
	Vector<T>::Vector(const T* array, unsigned size) :
		m_dim(size)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			m_components.push_back(array[i]);
		}
	}

	template <typename T>
	Vector<T>::Vector(std::vector<T> array) :
		m_dim(array.size())
	{
		m_components = array;
	}

	template <typename T>
	const Vector<T> Vector<T>::operator*(T scalar)
	{
		std::vector<T> newVec = m_components;
		for (unsigned i = 0; i < m_dim; ++i)
		{
			newVec[i] = m_components[i] * scalar;
		}
		return newVec;
	}

	template <typename T>
	const T Vector<T>::operator*(Vector<T> vector)
	{
		T product{ 0 };
		if (m_dim != vector.m_dim) return product;
		for (unsigned i = 0; i < m_dim; ++i)
		{
			product += m_components[i] * vector[i];
		}
		return product;
	}
}