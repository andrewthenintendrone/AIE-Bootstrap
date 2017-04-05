#include "Vector2.h"

/*##################################################
Vector2 constructor and destructor
##################################################*/
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(const float& value)
{
	x = value;
	y = value;
}

Vector2::Vector2(float newX, float newY)
{
    x = newX;
    y = newY;
}

Vector2::Vector2(const Vector2& vector)
{
	x = vector.x;
	y = vector.y;
}

Vector2::~Vector2()
{

}

/*##################################################
Vector2 Functions
##################################################*/
float Vector2::dot(Vector2& rhs)
{
	return(x * rhs.x + y * rhs.y);
}

float Vector2::magnitude()
{
    return sqrt(x * x + y * y);
}

float Vector2::squaremagnitude()
{
    return(x * x + y * y);
}

void Vector2::normalise()
{
    float mag = magnitude();
    x /= mag;
    y /= mag;
}

Vector2 Vector2::normalized()
{
	Vector2 temp(*this);
    float magnitude = temp.magnitude();
    temp.normalise();
    return temp;
}

float Vector2::angle(Vector2& rhs)
{
	return acosf(Vector2::dot(rhs.normalized()));
}

Vector2 Vector2::perpendicular()
{
	return Vector2(-y, x);
}

/*##################################################
Vector2 shortcuts for commonly used Vector2s
##################################################*/
Vector2 Vector2::Up()
{
    return{ 0, 1 };
}

Vector2 Vector2::Down()
{
    return{ 0, -1 };
}

Vector2 Vector2::Left()
{
    return{ -1, 0 };
}

Vector2 Vector2::Right()
{
    return{ -1, 0 };
}

Vector2 Vector2::Zero()
{
    return{ 0, 0 };
}

/*##################################################
Vector2 overloaded operators
##################################################*/
Vector2::operator float* ()
{
	return &x;
}

float& Vector2::operator [] (const int& index)
{
	return v[index];
}

bool Vector2::operator == (const Vector2& rhs)
{
    return (x == rhs.x && y == rhs.y);
}

void Vector2::operator = (const Vector2& rhs)
{
    x = rhs.x;
    y = rhs.y;
}

Vector2 Vector2::operator + (const Vector2& rhs)
{
	Vector2 temp(*this);
    temp += rhs;
    return temp;
}

void Vector2::operator += (const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

Vector2 Vector2::operator - (const Vector2& rhs)
{
	Vector2 temp(*this);
    temp -= rhs;
    return temp;
}

void Vector2::operator -= (const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

Vector2 Vector2::operator * (const float& scalar)
{
	Vector2 temp(*this);
	temp *= scalar;
	return temp;
}

Vector2 operator * (const float& scalar, Vector2& vector)
{
	return vector * scalar;
}

void Vector2::operator *= (const float& scalar)
{
	x *= scalar;
	y *= scalar;
}

Vector2 Vector2::operator / (const float& scalar)
{
	Vector2 temp(*this);
	temp /= scalar;
	return temp;
}

void Vector2::operator /= (const float& scalar)
{
	x /= scalar;
	y /= scalar;
}

std::ostream& operator << (std::ostream& stream, const Vector2& vector)
{
    stream << "(" << vector.x << ", " << vector.y << ")";
    return stream;
}
