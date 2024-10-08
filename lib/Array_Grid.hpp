/*****************************************************************************
**************
* Programmer: Conner Howard
* Project:
* Date:
* Description: Data Structure like std::array that is generated in a 2d grid	
*	format, while maintaining linear access for memory cache efficiency.
*	Structure is accessable through (x,y) coordinates or iterator (index)
******************************************************************************
*************/
#ifndef ARRAY_GRID_HPP
#define ARRAY_GRID_HPP

#include <iostream>
#include <array>
#include <algorithm>
#include <initializer_list>
#include <cassert>

using std::array;


/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/
template <class U>
U* newArray(const size_t& X, const size_t& Y, const U& defaultData)
{
	// define variables
	size_t count = 0;
	U* pMem = nullptr;

	// loop until you get a pointer or timeout
	while (pMem == nullptr && count < 20)
	{
		// allocate new pointer
		pMem = new U[X * Y];

		count++;
	}

	if (pMem != nullptr)
	{
		for (count = 0; count < (X * Y); count++)
		{
			pMem[count] = defaultData;
		}
	}

	return pMem;
}

///* Function Name:
//* Description:
//* Inputs:
//* Preconditions:
//* Outputs:
//* Returns:
//* Postconditions:
//*/
//template <class U>
//inline void deleteArray(const U* inArray)
//{
//	// free the original array
//	delete[] inArray;
//}

template <class U>
inline void copyArray(const U* src, U* dest, const unsigned& maxIndex)
{
	for (unsigned index = 0; index < maxIndex; index++)
	{
		dest[index] = src[index];
	}
}

template <class T>
class Array_Grid
{
public:
	struct size_t_pair
	{
		size_t x;
		size_t y;
	};
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	/* Precondition:
	*	Type <T> must support overloaded == operator (comparison)
	*	Type <T> must support overloaded = operator  (assignment)
	*/
	Array_Grid(const T& initFillData, const size_t& sizeX, const size_t& sizeY);

	// copy constructor
	Array_Grid(const Array_Grid& copy);

	// copy assignment
	Array_Grid& operator=(const Array_Grid& lhs);

	// copy assignment (initializer list overload)
	//	NOTE: undefined result if initializer list does not match Grid length
	Array_Grid& operator=(const std::initializer_list<T>& initList);

	// destructor
	~Array_Grid();


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters
	// redefine the size of the array, Dimensions: (X, Y)
	//inline void setSize(const size_t& sizeX, const size_t& sizeY);
	// Access specifice sell to set data
	void set(const T& newData, const size_t& whereX, const size_t& whereY);
	// Set all data in array to newData
	void setAll(const T& newData);
	// Override the current default initializer value
	inline void setDefaultInitializer(const T& newInitializerValue);
	// Access and override current NullData
	//void setNullData(const T& newNullData);


	// getters
	// access at (x,y)
	inline T& at(const size_t& whereX, const size_t& whereY) const;
	// access at (x,y)
	inline T& operator()(const size_t& whereX, const size_t& whereY) const;
	// access via index operator (index)
	inline T& operator()(const size_t& index) const;
	// remove element (replace with Initial Fill) at (x,y)
	inline T remove(const size_t& whereX, const size_t& whereY);
	// returns a copy of the current default initializer value
	inline const T& getDefaultInitialzier();
	// // get the current value of the NullData
	//inline const T& getNullData() const;
	// returns the size of the array in (x,y) dimensional values
	inline size_t_pair size() const;
	// get the total length of the 1d array
	inline size_t getLength() const;
	// returns the value of number of full cells (index length)
	inline size_t getIndexCount() const;		
	// returns the memory size of array (in bytes)
	inline unsigned sizeofArray() const;

	// checks
	// is cell considered empty (equal to null data)
	// inline bool empty(const size_t& whereX, const size_t& whereY) const;	
	// Is point in bounds of grid
	inline bool isInGrid(const size_t& whereX, const size_t& whereY) const;

	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* Function Name: Copy array
	* Description: copies the data from src to dest, resizing dest as needed.
	*	if dest is larger, shrinks it, if dest is smaller, grows it
	* Inputs: src arrGrid, destination arrGrid
	* Preconditions:
	* Outputs: none
	* Returns: none
	* Postconditions:
	*/
	void copyArrayData(const Array_Grid<T>& src);

	/* Function Name: Fill Array with Data
	* Description: Fills entire array with the supplied newData, overwriting any
	*	previous values. Does not modify the nullData Set.
	* Inputs: New data to overwrite the array
	* Preconditions: none
	* Outputs: array filled with newData
	* Returns: none
	* Postconditions:
	*/
	void fill(const T& newData);

	/* Function Name: Clear Array
	* Description: Sets all array values to the NullData set. Action discards all
	*	overwritten data
	* Inputs: none
	* Preconditions:
	* Outputs: array_grid now set entirely to NullData
	* Returns: none
	* Postconditions:
	*/
	void clear();

protected:
	size_t_pair mSize;
	// size_t mCurrentlyOccupied;
	T mDefaultInitializer;
	T* mData = nullptr;
	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: resize array
	* Description: resizes the array off of the given new size. keeps data depending on the chosen option
	*	default deletes the data on a resize
	* Inputs: new index count size of the array, T/F to copy the old data over or to wipe it
	* Outputs: none
	*/
	void resize(const size_t_pair& newSize, const bool& clear = false);


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
Array_Grid<T>::Array_Grid(const T& initFillData, const size_t& sizeX, const size_t& sizeY) : mDefaultInitializer(initFillData)
{
	this->mSize.x = sizeX;
	this->mSize.y = sizeY;
	this->resize(mSize, false);
}

// copy constructor
template <class T>
Array_Grid<T>::Array_Grid(const Array_Grid& copy) : mDefaultInitializer(copy.mDefaultInitializer)
{
	this->mSize.x = copy.mSize.x;
	this->mSize.y = copy.mSize.y;

	this->copyArrayData(copy);
}

// copy assignment
template <class T>
Array_Grid<T>& Array_Grid<T>::operator=(const Array_Grid& lhs)
{
	this->mSize.x = lhs.mSize.x;
	this->mSize.y = lhs.mSize.y;
	this->mDefaultInitializer = lhs.mDefaultInitializer;

	this->copyArrayData(lhs);
	return *this;
}

// copy assignment (initializer list overload)
//	NOTE: undefined result if initializer list does not match Grid length
template <class T>
Array_Grid<T>& Array_Grid<T>::operator=(const std::initializer_list<T>& initList)
{
	assert(initList.size() == this->getLength() && "FATAL ERROR: Initializer List incompatable size");

	size_t i = 0;
	for(const auto& elem : initList)
	{
		this->operator()(i++) = elem;
	}
	return *this;
}


// destructor
template <class T>
Array_Grid<T>::~Array_Grid()
{
	//std::cout<<"~Array_Grid() called"<<std::endl;
	// free the data if its not in use
	if (this->mData != nullptr)
	{
		delete[] this->mData;
		//std::cout<<"data deleted"<<std::endl;
	}
	//std::cout<<"--"<<std::endl;
}

// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// setters
//template <class T>
//inline void Array_Grid<T>::setSize(const size_t& sizeX, const size_t& sizeY)
//{
//	// call resize
//	resize({ sizeX, sizeY }, false);
//}

template <class T>
void Array_Grid<T>::set(const T& newData, const size_t& whereX, const size_t& whereY)
{
	this->at(whereX, whereY) = newData;
}

// Set all data in array to newData
template <class T>
void Array_Grid<T>::setAll(const T& newData)
{
	for (int index = 0; index < getLength(); index++)
	{
		this->mData = newData;
	}
}

template <class T>
void Array_Grid<T>::setDefaultInitializer(const T& newInitializerValue)
{
	this->mDefaultInitializer = newInitializerValue;
}

// getters
template <class T>
inline T& Array_Grid<T>::at(const size_t& whereX, const size_t& whereY) const
{
	return this->mData[whereY*mSize.x + whereX];
}

template <class T>
inline T& Array_Grid<T>::operator()(const size_t& whereX, const size_t& whereY) const
{
	return at(whereX, whereY);
}


template <class T>
inline T& Array_Grid<T>::operator()(const size_t& index) const
{
	return this->mData[index];
}


template <class T>
inline T Array_Grid<T>::remove(const size_t& whereX, const size_t& whereY)
{
	// check data and make return value
	T temp = this->at(whereX, whereY);
	
	// return result
	return temp;
}

template <class T>
inline const T& Array_Grid<T>::getDefaultInitialzier()
{
	return this->mDefaultInitializer;
}

template <class T>
inline typename Array_Grid<T>::size_t_pair Array_Grid<T>::size() const
{
	return this->mSize;
}

template <class T>
inline size_t Array_Grid<T>::getLength() const
{
	return this->mSize.x * mSize.y;
}

template <class T>
inline size_t Array_Grid<T>::getIndexCount() const
{
	return this->mSize.x * this->mSize.y;
}

template <class T>
inline unsigned Array_Grid<T>::sizeofArray() const
{
	return this->mSize.x * this->mSize.y * sizeof this->mDefaultInitializer;
}

// checks
// template <class T>
// bool Array_Grid<T>::empty(const size_t& whereX, const size_t& whereY) const	// is cell considered empty
// {
// 	return this->at(whereX, whereY) == this->mDefaultInitializer;
// }

template <class T>
bool Array_Grid<T>::isInGrid(const size_t& whereX, const size_t& whereY) const
{
	return whereX < this->mSize.x && whereY < this->mSize.y;
}

// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name: Copy array
* Description: copies the data from src to dest, resizing dest as needed.
*	if dest is larger, shrinks it, if dest is smaller, grows it
* Inputs: src arrGrid, destination arrGrid
* Preconditions:
* Outputs: none
* Returns: none
*/
template <class T>
void Array_Grid<T>::copyArrayData(const Array_Grid<T>& src)
{
	// check array needs resizing
	if (src.mSize.x != this->mSize.x || src.mSize.y != this->mSize.y || this->mData == nullptr)
	{
		this->resize(src.mSize, true);
	}

	// copy array data
	copyArray(src.mData, this->mData, (mSize.y * mSize.x));
}

/* Function Name: Fill Array with Data
* Description: Fills entire array with the supplied newData, overwriting any
*	previous values. Does not modify the nullData Set.
* Inputs: New data to overwrite the array
* Preconditions: none
* Outputs: array filled with newData
* Returns: none
* Postconditions:
*/
template <class T>
void Array_Grid<T>::fill(const T& newData)
{
	// iterate through list and overwrite the data
	for (int index = 0; index < this->getIndexCount(); index++)
	{
		this->mData[index] = newData;
	}
}

/* Function Name: Clear Array
* Description: Sets all array values to the NullData set. Action discards all
*	overwritten data
* Inputs: none
* Preconditions:
* Outputs: array_grid now set entirely to NullData
* Returns: none
* Postconditions:
*/
template <class T>
void Array_Grid<T>::clear()
{
	// simply calls fill but supplies the nullData values
	this->fill(this->mDefaultInitializer);
}


// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: resize array
* Description: resizes the array off of the given new size. keeps data depending on the chosen option
*	default deletes the data on a resize
* Inputs: new index count size of the array, T/F to copy the old data over or to wipe it
* Outputs: none
*/
template <class T>
void Array_Grid<T>::resize(const size_t_pair& newSize, const bool& clear)
{
	// generate new array
	// create the new array
	T* pMem = newArray<T>(newSize.x, newSize.y, this->mDefaultInitializer);

	// copy data if requested
	if (clear == false && this->mData != nullptr)
	{
		// copy the data from this to pMem
		copyArray(this->mData, pMem, static_cast<const unsigned>(mSize.y * mSize.x));

		// now clear the old data and pin the new
		delete[] this->mData;
		this->mData = pMem;
	}
	// otherwise, just pin the new data
	else
	{
		// discarding data (if any) and replacing with blank
		if (this->mData != nullptr)
		{
			// note this does not work great with pointers
			delete[] this->mData;
		}

		// attach new data
		this->mData = pMem;
	}

	// set new size
	this->mSize = newSize;
}






// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //


#endif