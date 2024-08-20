/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Vec2f Class
* Date: 12/30/2023
* Description: Vec2f class is a vector 2 struct that stores a float x and float y
*	useful for position, velocity, acceleteration, etc in 2D orthoginal plane.
******************************************************************************
*************/
#ifndef ECS_Vec2F_HPP
#define ECS_Vec2F_HPP

#include <math.h>

class Vec2f
{
public:
	// public information
	float x = 0;
	float y = 0;

	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	Vec2f()
	{
		this->x = 0;
		this->y = 0;
	}

	// default constructor
	Vec2f(const float initX, const float initY)
	{
		this->x = initX;
		this->y = initY;
	}

	// copy constructor
	Vec2f(const Vec2f& copy)
	{
		this->x = copy.x;
		this->y = copy.y;
	}
	
	// copy assignmnet operator
	Vec2f& operator=(const Vec2f rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}

	// destructor
	~Vec2f()
	{

	}

	// --------------------------------------------------------------------------------------------- //
	//									Operator Overloading
	// --------------------------------------------------------------------------------------------- //
	// Arethmetic Operators
	Vec2f  operator+ (const Vec2f& rhs) const;
	Vec2f  operator- (const Vec2f& rhs) const;
	Vec2f  operator* (const float& rhs) const;
	Vec2f  operator/ (const float& rhs) const;
	
	Vec2f& operator+=(const Vec2f& rhs);
	Vec2f& operator-=(const Vec2f& rhs);
	Vec2f& operator*=(const float& rhs);
	Vec2f& operator/=(const float& rhs);

	// Comparison operators
	bool operator==(const Vec2f& rhs) const;
	bool operator!=(const Vec2f& rhs) const;
	//bool operator>=(const Vec2f& rhs);
	//bool operator<=(const Vec2f & rhs);
	//bool operator> (const Vec2f& rhs);
	//bool operator< (const Vec2f & rhs);


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //




	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Compute Vector Length
	* Description: Gets length of this specific Vec2f object
	* Inputs: none
	* Outputs: length of vector
	*/
	inline float length() const;

	/* mFunction Name: compute angle
	* Description: computes angle between two Vec2f vectors. Assumes that 
	*	this vector object is [v1] and that input is [v2]
	* Inputs: second vector (ie, the target)
	* Outputs: float of angle in [RADIANS]
	*/
	inline float angle(const Vec2f& v2) const;

	/* mFunction Name: Compute Distance
	* Description: computes the distance between two vectors. Assumes that this object
	*	is [v1] and that input Vec2f is [v2]. Analogous to pathagorian theorem
	* Inputs: second vector to compare to
	* Outputs: float of the distance between vectors
	*/
	inline float dist(const Vec2f v2) const;

	/* mFunction Name: Compute Difference
	* Description: computes the vector difference between two vectors. Assumes that this object
	*	is [v1] and that input Vec2f is [v2]. Analogous to [v2] - [v1]
	*	[[Note]]: does not modifiy this object
	* Inputs: second vector to compare to
	* Outputs: difference vector of two vectors
	*/
	inline Vec2f difference(const Vec2f v2) const;

	/* mFunction Name: Unit Direction Vector
	* Description: Makes a direciton vector from current vector pointing to the
		supplied v2 vector, with length 1
	* Inputs: second vector to point towards
	* Outputs: Vector pointing from this object to v2
	*/
	inline Vec2f unitDirectoinVector(const Vec2f v2) const;

	/* mFunction Name: Normalize vector
	* Description: Normalizes the vector to be a unit vector
	* Inputs: none
	* Outputs: Normalized version of this Vec2f vector
	*/
	void normal();
	
	/* mFunction Name: Dot Product
	* Description: performs the dot product between two Vec2f
	* Inputs: Second vector to dot product with
	* Outputs:
	*/
	float dot(const Vec2f& v2) const;

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