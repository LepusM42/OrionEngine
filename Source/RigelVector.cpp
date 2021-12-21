/******************************************************************************!
* \file RigelVector.cpp
* \author Lepus
* \brief Contains all implementation of vector operations in the Rigel Math
* Library.
*******************************************************************************/
namespace Rigel
{
	/**************************************************************************!
	* \fn Vector<T>::Vector(const T value, unsigned size);
	* \brief Create a vector whose components are all one value.
	* \param value Value that will make up all components of this vector.
	* \param size Number of components this vector will contain.
	***************************************************************************/
	template <typename T>
	Vector<T>::Vector(const T value, unsigned size) :
		m_dim(size)
	{
		m_components = AllocateVector();
		for (unsigned i = 0; i < m_dim; ++i)
		{
			m_components[i] = value;
		}
	}

	/**************************************************************************!
	* \fn Vector<T>::Vector(const T* array, unsigned size);
	* \brief Copy the contents of an array into a Rigel vector.
	* \param array Array whose contents will be deep copied into this vector.
	* \param size Number of components this vector will contain.
	***************************************************************************/
	template <typename T>
	Vector<T>::Vector(const T* array, unsigned size) :
		m_dim(size)
	{
		m_components = AllocateVector();
		for (unsigned i = 0; i < m_dim; ++i)
		{
			m_components[i] = array[i];
		}
	}

	/**************************************************************************!
	* \fn Vector<T>::Vector(std::vector<T> array);
	* \brief Copy the contents of a std::vector into a Rigel vector.
	* \param array Vector to copy into this vector. The new vector will have the
	*  same number of components as the passed in vector.
	***************************************************************************/
	template <typename T>
	Vector<T>::Vector(std::vector<T> array) :
		m_dim(array.size())
	{
		m_components = AllocateVector();
		for (unsigned i = 0; i < m_dim; ++i)
		{
			m_components[i] = array[i];
		}
	}

	/**************************************************************************!
	* \fn const Vector<T> Vector<T>::operator*(T scalar);
	* \brief Scale a vector by a scalar value.
	* \param scalar Factor by which to scale the vector.
	* \return A new vector equal to the original scaled by the passed in value.
	***************************************************************************/
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

	/**************************************************************************!
	* \fn const T Vector<T>::operator*(Vector<T> vector);
	* \brief Find the dot product of two vectors.
	* \param vector Other vector to multiply this vector by.
	* \return The dot product of the two vectors, which is equal to the sum of
	*  the products of each of their respective components.
	***************************************************************************/
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

	/**************************************************************************!
	* \fn unsigned Vector<T>::size();
	* \brief Get the number of components this vector contains.
	* \return Number of components this vector contains.
	***************************************************************************/
	template <typename T>
	unsigned Vector<T>::size()
	{
		return m_dim;
	}

	/**************************************************************************!
	* \fn T Vector<T>::magnitude();
	* \brief Magnitude of a vector.
	* \return The magnitude of the vector, equal to the square root of the dot
	*  product of the vector and itself.
	***************************************************************************/
	template <typename T>
	T Vector<T>::magnitude()
	{
		return static_cast<T>(sqrt((*this) * (*this)));
	}

	/**************************************************************************!
	* \fn const T Vector<T>::operator[](unsigned index);
	* \brief Access a component.
	* \param index Which component to access.
	* \return Value of the component stored at the specified index.
	***************************************************************************/
	template <typename T>
	const T Vector<T>::operator[](unsigned index) const
	{
		return m_components[index];
	}

	/**************************************************************************!
	* \fn const T Vector<T>::operator[](unsigned index);
	* \brief Access a component.
	* \param index Which component to access.
	* \return Value of the component stored at the specified index.
	***************************************************************************/
	template <typename T>
	T& Vector<T>::operator[](unsigned index)
	{
		return m_components[index];
	}

	/**************************************************************************!
	* \fn T* Vector<T>::AllocateVector();
	* \brief Allocate memory for a vector using the stored dimension.
	* \return Block of memory large enough to hold the data necessary for this
	*  vector. The size of this block is equal to the product of the number of
	*  components this vector contains and the size of the data type used for
	*  this vector.
	***************************************************************************/
	template <typename T>
	T* Vector<T>::AllocateVector()
	{
		return new T[m_dim];
	}
}