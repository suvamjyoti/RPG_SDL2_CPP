#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x,float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D:: Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Subtrtact(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtrtact(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& v2)
{
	this->Add(v2);
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v2)
{
	this->Subtrtact(v2);
	return *this;
}
Vector2D& Vector2D::operator*=(const Vector2D& v2)
{
	this->Multiply(v2);
	return *this;
}
Vector2D& Vector2D::operator/=(const Vector2D& v2)
{
	this->Divide(v2);
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	//output as Vec2D(x,y);
	stream << "Vec2D(" << vec.x << "," << vec.y << ")"<<std::endl;
	return stream;
}

