/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef VECTOR_GRID_HPP
#define VECTOR_GRID_HPP

#include "Array_Grid.hpp"	// inherit

template <class T>
class Vector_Grid : public Array_Grid<T>
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	/* Precondition:
	*	Type <T> must support overloaded == operator (comparison)
	*	Type <T> must support overloaded = operator  (assignment)
	*/
	Vector_Grid(const T& nullData, const size_t& sizeX = 0, const size_t& sizeY = 0);

	// copy constructor
	Vector_Grid(const Vector_Grid& copy);

	// copy assignment
	Vector_Grid& operator=(const Vector_Grid& lhs);
	
	// copy assignment
	Vector_Grid& operator=(const std::initializer_list<T>& lhs);

	// destructor
	~Vector_Grid();



	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters
	// redefine the size of the array, Dimensions: (X, Y)
	inline void setSize(const size_t& sizeX, const size_t& sizeY);




	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //



private:

	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //



};

// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //


/* mFunction Name:
* Description:
* Inputs:
* Outputs:
*/


/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/

// --------------------------------------------------------------------------------------------- //
// --------------------------------------------------------------------------------------------- //
//										Function Definitions
// --------------------------------------------------------------------------------------------- //
// --------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //
// constructor
template <class T>
Vector_Grid<T>::Vector_Grid(const T& nullData, const size_t& sizeX, const size_t& sizeY) :
	Array_Grid<T>(nullData, sizeX, sizeY)
{

}

// copy constructor
template <class T>
Vector_Grid<T>::Vector_Grid(const Vector_Grid& copy) : Array_Grid<T>(copy)
{

}

// copy assignment
template <class T>
Vector_Grid<T>& Vector_Grid<T>::operator=(const Vector_Grid& lhs)
{
	// invoke copy assignment operator
	Array_Grid<T>::operator=(lhs);

	return *this;
}

// copy assignment
template <class T>
Vector_Grid<T>& Vector_Grid<T>::operator=(const std::initializer_list<T>& initList)
{
	// invoke the same Array_Grid implimentation
	Array_Grid<T>::operator=(initList);

	return *this;
}

// destructor
template <class T>
Vector_Grid<T>::~Vector_Grid()
{
	// handled by Array_Grid<T>::~Array_Grid
	// std::cout<<"~Vector_Grid() called"<<std::endl;
}

// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// setters
template <class T>
inline void Vector_Grid<T>::setSize(const size_t& sizeX, const size_t& sizeY)
{
	// call resize
	this->resize({ sizeX, sizeY }, false);
}


#endif