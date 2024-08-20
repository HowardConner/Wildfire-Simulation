/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "Vec2i.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //



// --------------------------------------------------------------------------------------------- //
//									Operator Overloading
// --------------------------------------------------------------------------------------------- //
// Arethmetic Operators
Vec2i Vec2i::operator+ (const Vec2i& rhs) const
{
	return Vec2i(this->x + rhs.x, this->y + rhs.y);
}
Vec2i Vec2i::operator- (const Vec2i& rhs) const
{
	return Vec2i(this->x - rhs.x, this->y - rhs.y);
}
Vec2i Vec2i::operator* (const int& rhs) const
{
	return Vec2i(this->x * rhs, this->y * rhs);
}
Vec2i Vec2i::operator/ (const int& rhs) const
{
	return Vec2i(this->x / rhs, this->y / rhs);
}

Vec2i& Vec2i::operator+=(const Vec2i& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
Vec2i& Vec2i::operator-=(const Vec2i& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}
Vec2i& Vec2i::operator*=(const int& rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}
Vec2i& Vec2i::operator/=(const int& rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

// Comparison operators
bool Vec2i::operator==(const Vec2i& rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vec2i::operator!=(const Vec2i& rhs) const
{
	return (this->x != rhs.x && this->y != rhs.y);
}

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
int Vec2i::length() const
{
	return sqrt(x * x + y * y);
}


/* mFunction Name: compute angle
* Description: computes angle between two Vec2i vectors. Assumes that
*	this vector object is [v1] and that input is [v2]
* Inputs: second vector (ie, the target)
* Outputs: int of angle in [RADIANS]
*/
int Vec2i::angle(const Vec2i& v2) const
{
	return atan2f(v2.y - y, v2.x - x);
}


/* mFunction Name: Compute Distance
* Description: computes the distance between two vectors. Assumes that this object
*	is [v1] and that input Vec2i is [v2]. Analogous to pathagorian theorem
* Inputs: second vector to compare to
* Outputs: int of the distance between vectors
*/
int Vec2i::dist(const Vec2i v2) const
{
	Vec2i diff = difference(v2);
	return sqrtf(diff.x*diff.x + diff.y*diff.y);
}


/* mFunction Name: Compute Difference
* Description: computes the vector difference between two vectors. Assumes that this object
*	is [v1] and that input Vec2i is [v2]. Analogous to [v2] - [v1]
*	[[Note]]: does not modifiy this object
* Inputs: second vector to compare to
* Outputs: difference vector of two vectors
*/
Vec2i Vec2i::difference(const Vec2i v2) const 
{
	return v2 - *this;
}

/* mFunction Name: Unit Direction Vector
* Description: Makes a direciton vector from current vector pointing to the
	supplied v2 vector, with length 1
* Inputs: second vector to point towards
* Outputs: Vector pointing from this object to v2
*/
Vec2i Vec2i::unitDirectoinVector(const Vec2i v2) const
{
	Vec2i diff = difference(v2);
	float len = diff.length();
	return Vec2i(diff.x / len, diff.y / len);
}

/* mFunction Name: Normalize vector
* Description: Normalizes the vector to be a unit vector
* Inputs: none
* Outputs: Normalized version of this Vec2f vector
*/
void Vec2i::normal()
{
	int len = this->length();
	this->x = x/len;
	this->y = y/len;
}

/* mFunction Name: Dot Product
* Description: performs the dot product between two Vec2i
* Inputs: Second vector to dot product with
* Outputs:
*/
inline int Vec2i::dot(const Vec2i& v2) const
{
	return this->x * v2.x + this->y * v2.y;
}


// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //




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