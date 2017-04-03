#pragma once
#include <iostream>

class Vector3
{
public:
	// variables
	float x;
	float y;
	float z;

	// constructors and destructor
	Vector3();
	Vector3(float newX, float newY, float newZ);
	~Vector3();

	// functions
	float getMagnitude();
	void Normalize();
	Vector3 Vector3::normalized();

	// static Vector3 shortcuts
	static Vector3 Up();
	static Vector3 Down();
	static Vector3 Left();
	static Vector3 Right();
	static Vector3 Forward();
	static Vector3 Back();
	static Vector3 Zero();
	static Vector3 Random(const int& range);

	// operator overloads
	bool operator == (const Vector3& rhs);
	void operator = (const Vector3& vec);
	void operator += (const Vector3& vec);
	void operator -= (const Vector3& vec);
	void operator *= (const float& scalar);
	void operator /= (const float& scalar);
	friend std::ostream& operator << (std::ostream& stream, const Vector3& vector);
};