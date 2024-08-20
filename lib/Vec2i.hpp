/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Vec2i Class
* Date: 12/30/2023
* Description: Vec2i class is a vector 2 struct that stores a int x and int y
*	useful for position, velocity, acceleteration, etc in 2D orthoginal plane.
******************************************************************************
*************/
#ifndef ECS_Vec2I_HPP
#define ECS_Vec2I_HPP

#include <math.h>

class Vec2i
{
public:
	// public information
	int x = 0;
	int y = 0;

	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	Vec2i()
	{
		this->x = 0;
		this->y = 0;
	}

	// default constructor
	Vec2i(const int initX, const int initY)
	{
		this->x = initX;
		this->y = initY;
	}

	// copy constructor
	Vec2i(const Vec2i& copy)
	{
		this->x = copy.x;
		this->y = copy.y;
	}
	
	// copy assignmnet operator
	Vec2i& operator=(const Vec2i rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}

	// destructor
	~Vec2i()
	{

	}

	// --------------------------------------------------------------------------------------------- //
	//									Operator Overloading
	// --------------------------------------------------------------------------------------------- //
	// Arethmetic Operators
	Vec2i  operator+ (const Vec2i& rhs) const;
	Vec2i  operator- (const Vec2i& rhs) const;
	Vec2i  operator* (const int& rhs) const;
	Vec2i  operator/ (const int& rhs) const;
	
	Vec2i& operator+=(const Vec2i& rhs);
	Vec2i& operator-=(const Vec2i& rhs);
	Vec2i& operator*=(const int& rhs);
	Vec2i& operator/=(const int& rhs);

	// Comparison operators
	bool operator==(const Vec2i& rhs) const;
	bool operator!=(const Vec2i& rhs) const;
	//bool operator>=(const Vec2i& rhs) const;
	//bool operator<=(const Vec2i & rhs) const;
	//bool operator> (const Vec2i& rhs) const;
	//bool operator< (const Vec2i & rhs) const;


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //




	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Compute Vector Length
	* Description: Gets length of this specific Vec2i object
	* Inputs: none
	* Outputs: length of vector
	*/
	inline int length() const;

	/* mFunction Name: compute angle
	* Description: computes angle between two Vec2i vectors. Assumes that 
	*	this vector object is [v1] and that input is [v2]
	* Inputs: second vector (ie, the target)
	* Outputs: int of angle in [RADIANS]
	*/
	inline int angle(const Vec2i& v2) const;

	/* mFunction Name: Compute Distance
	* Description: computes the distance between two vectors. Assumes that this object
	*	is [v1] and that input Vec2i is [v2]. Analogous to pathagorian theorem
	* Inputs: second vector to compare to
	* Outputs: int of the distance between vectors
	*/
	inline int dist(const Vec2i v2) const;

	/* mFunction Name: Compute Difference
	* Description: computes the vector difference between two vectors. Assumes that this object
	*	is [v1] and that input Vec2i is [v2]. Analogous to [v2] - [v1]
	*	[[Note]]: does not modifiy this object
	* Inputs: second vector to compare to
	* Outputs: difference vector of two vectors
	*/
	inline Vec2i difference(const Vec2i v2) const;

	/* mFunction Name: Unit Direction Vector
	* Description: Makes a direciton vector from current vector pointing to the
		supplied v2 vector, with length 1
	* Inputs: second vector to point towards
	* Outputs: Vector pointing from this object to v2
	*/
	inline Vec2i unitDirectoinVector(const Vec2i v2) const;

	/* mFunction Name: Normalize vector
	* Description: Normalizes the vector to be a unit vector
	* Inputs: none
	* Outputs: Normalized version of this Vec2f vector
	*/
	void normal();

	/* mFunction Name: Dot Product
	* Description: performs the dot product between two Vec2i
	* Inputs: Second vector to dot product with
	* Outputs:
	*/
	inline int dot(const Vec2i& v2) const;

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

#endif