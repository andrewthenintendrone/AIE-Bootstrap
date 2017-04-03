#include "Vector3.h"
#include <math.h>
#include <cstdlib>

#define PI 3.14159265

/*##################################################
Vector3 constructor and destructor
##################################################*/
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

Vector3::~Vector3()
{

}

/*##################################################
Vector3 Functions
##################################################*/
float Vector3::getMagnitude()
{
	return (float)sqrt(x * x + y * y + z * z);
}

void Vector3::Normalize()
{
	float magnitude = getMagnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

Vector3 Vector3::normalized()
{
	Vector3 temp = *this;
	float magnitude = getMagnitude();
	temp.Normalize();
	return temp;
}

/*##################################################
Vector3 shortcuts for commonly used Vector3s
##################################################*/
Vector3 Vector3::Up()
{
	return{ 0.0f, 1.0f, 0.0f };
}

Vector3 Vector3::Down()
{
	return{ 0.0f, -1.0f, 0.0f };
}

Vector3 Vector3::Left()
{
	return{ -1.0f, 0.0f, 0.0f };
}

Vector3 Vector3::Right()
{
	return{ -1.0f, 0.0f, 0.0f };
}

Vector3 Vector3::Forward()
{
	return{ 0.0f, 0.0f, 1.0f };
}

Vector3 Vector3::Back()
{
	return{ 0.0f, 0.0f, -1.0f };
}

Vector3 Vector3::Zero()
{
	return{ 0.0f, 0.0f, 0.0f };
}

Vector3 Vector3::Random(const int& range)
{
	return(Vector3((float)(rand() % (2 * range) - range), (float)(rand() % (2 * range) - range), (float)(rand() % (2 * range) - range)));
}

/*##################################################
Vector3 overloaded operators
##################################################*/
bool Vector3::operator == (const Vector3& rhs)
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

void Vector3::operator = (const Vector3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

void Vector3::operator += (const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

void Vector3::operator -= (const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

void Vector3::operator *= (const float& scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void Vector3::operator /= (const float& scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

std::ostream& operator << (std::ostream& stream, const Vector3& vector)
{
	stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}
