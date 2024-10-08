#include "Vector2D.h"
#include <string>
#include <algorithm>

Vector2D::Vector2D() : x { 0.0f }, y { 0.0f }
{
}

Vector2D::Vector2D(float x, float y) : x { x }, y { y }
{
}

Vector2D::Vector2D(const Vector2D& source) : x { source.x }, y { source.y }
{
}

Vector2D::Vector2D(Vector2D&& source) noexcept : x { source.x }, y { source.y }
{
}

const Vector2D Vector2D::Zero { 0.0f, 0.0f };
const Vector2D Vector2D::Up { 0.0f, -1.0f };
const Vector2D Vector2D::Down { 0.0f, 1.0f };
const Vector2D Vector2D::Left { -1.0f, 0.0f };
const Vector2D Vector2D::Right { 1.0f, 0.0f };

float Vector2D::Distance(const Vector2D& v1, const Vector2D& v2)
{
	return (v1 - v2).Magnitude();
}

float Vector2D::Dot(const Vector2D& v1, const Vector2D& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2D Vector2D::Lerp(const Vector2D& v1, const Vector2D& v2, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);
	return (1 - t) * v1 + t * v2;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
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

Vector2D& Vector2D::Normalize()
{
	float magnitude { this->Magnitude() };

	if (magnitude > 0)
	{
		*this /= magnitude;
	}

	return *this;
}

Vector2D Vector2D::GetNormalized() const
{
	Vector2D result { *this };
	result.Normalize();

	return result;
}

Vector2D& Vector2D::Negate()
{
	*this *= -1;

	return *this;
}

float Vector2D::Magnitude() const
{
	return sqrtf(powf(this->x, 2) + powf(this->y, 2));
}

std::string Vector2D::ToString() const
{
	return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

Vector2D operator*(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x * v2.x, v1.y * v2.y);
}

Vector2D operator/(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x / v2.x, v1.y / v2.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}

Vector2D operator*(const Vector2D& vec, const float& i)
{
	return Vector2D(vec.x * i, vec.y * i);
}

Vector2D operator*(const float& i, const Vector2D& vec)
{
	return vec * i;
}

Vector2D operator/(const Vector2D& vec, const float& i)
{
	return Vector2D(vec.x / i, vec.y / i);
}

Vector2D operator/(const float& i, const Vector2D& vec)
{
	return vec / i;
}

Vector2D& Vector2D::operator*=(const float& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::operator/=(const float& i)
{
	this->x /= i;
	this->y /= i;

	return *this;
}

Vector2D& Vector2D::operator=(const Vector2D& vec)
{
    this->x = vec.x;
	this->y = vec.y;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << vec.ToString();
	return stream;
}