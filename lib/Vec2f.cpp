/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "Vec2f.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //



// --------------------------------------------------------------------------------------------- //
//									Operator Overloading
// --------------------------------------------------------------------------------------------- //
// Arethmetic Operators
Vec2f Vec2f::operator+ (const Vec2f& rhs) const
{
	return Vec2f(this->x + rhs.x, this->y + rhs.y);
}
Vec2f Vec2f::operator- (const Vec2f& rhs) const
{
	return Vec2f(this->x - rhs.x, this->y - rhs.y);
}
Vec2f Vec2f::operator* (const float& rhs) const
{
	return Vec2f(this->x * rhs, this->y * rhs);
}
Vec2f Vec2f::operator/ (const float& rhs) const
{
	return Vec2f(this->x / rhs, this->y / rhs);
}

Vec2f& Vec2f::operator+=(const Vec2f& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
Vec2f& Vec2f::operator-=(const Vec2f& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}
Vec2f& Vec2f::operator*=(const float& rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}
Vec2f& Vec2f::operator/=(const float& rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

// Comparison operators
bool Vec2f::operator==(const Vec2f& rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vec2f::operator!=(const Vec2f& rhs) const
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
	* Description: Gets length of this specific Vec2f object
	* Inputs: none
	* Outputs: length of vector
	*/
float Vec2f::length() const
{
	return sqrt(x * x + y * y);
}


/* mFunction Name: compute angle
* Description: computes angle between two Vec2f vectors. Assumes that
*	this vector object is [v1] and that input is [v2]
* Inputs: second vector (ie, the target)
* Outputs: float of angle in [RADIANS]
*/
float Vec2f::angle(const Vec2f& v2) const
{
	return atan2f(v2.y - y, v2.x - x);
}


/* mFunction Name: Compute Distance
* Description: computes the distance between two vectors. Assumes that this object
*	is [v1] and that input Vec2f is [v2]. Analogous to pathagorian theorem
* Inputs: second vector to compare to
* Outputs: float of the distance between vectors
*/
float Vec2f::dist(const Vec2f v2) const
{
	Vec2f diff = difference(v2);
	return sqrtf(diff.x*diff.x + diff.y*diff.y);
}


/* mFunction Name: Compute Difference
* Description: computes the vector difference between two vectors. Assumes that this object
*	is [v1] and that input Vec2f is [v2]. Analogous to [v2] - [v1]
*	[[Note]]: does not modifiy this object
* Inputs: second vector to compare to
* Outputs: difference vector of two vectors
*/
Vec2f Vec2f::difference(const Vec2f v2) const 
{
	return v2 - *this;
}

/* mFunction Name: Unit Direction Vector
* Description: Makes a direciton vector from current vector pointing to the
	supplied v2 vector, with length 1
* Inputs: second vector to point towards
* Outputs: Vector pointing from this object to v2
*/
Vec2f Vec2f::unitDirectoinVector(const Vec2f v2) const
{
	Vec2f diff = difference(v2);
	float len = diff.length();
	return Vec2f(diff.x / len, diff.y / len);
}

/* mFunction Name: Normalize vector
* Description: Normalizes the vector to be a unit vector
* Inputs: none
* Outputs: Normalized version of this Vec2f vector
*/
void Vec2f::normal()
{
	float len = this->length();
	this->x = x/len;
	this->y = y/len;
}

/* mFunction Name: Dot Product
* Description: performs the dot product between two Vec2f
* Inputs: Second vector to dot product with
* Outputs:
*/
float Vec2f::dot(const Vec2f& v2) const
{
	// Calculate the dot product
	float dotProduct = this->x * v2.x + this->y * v2.y;
	
	// Calculate the magnitudes (lengths) of the vectors
	float magnitude1 = std::sqrt(this->x * this->x + this->y * this->y);
	float magnitude2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);

	if(magnitude1 * magnitude2 == 0)
	{
		return 0.f;
	}
	
	// Normalize the dot product by dividing by the product of the magnitudes
	return dotProduct / (magnitude1 * magnitude2);
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