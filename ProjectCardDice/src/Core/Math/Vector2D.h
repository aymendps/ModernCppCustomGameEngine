#pragma once
#include <algorithm>
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& source);
	Vector2D(Vector2D&& source) noexcept;
	~Vector2D() = default;

	static const Vector2D Zero, Up, Down, Left, Right;

	/// <summary>
	/// Returns the distance between two vectors
	/// </summary>
	/// <param name="v1">First Vector</param>
	/// <param name="v2">Second Vector</param>
	static float Distance(const Vector2D& v1, const Vector2D& v2);

	/// <summary>
	/// Returns the dot product of two vectors
	/// </summary>
	/// <param name="v1">First Vector</param>
	/// <param name="v2">Second Vector</param>
	static float Dot(const Vector2D& v1, const Vector2D& v2);

	/// <summary>
	/// Linearly interpolates between two vectors. The interpolant t is clamped to the range [0, 1].
	/// When t = 0 returns v1.
	/// When t = 1 return v2.
	/// When t = 0.5 returns the midpoint of v1 and v2.
	/// </summary>
	/// <param name="v1">First Vector</param>
	/// <param name="v2">Second Vector</param>
	/// <param name="t">Value used to interpolate between v1 and v2</param>
	/// <returns>Interpolated vector</returns>
	static Vector2D Lerp(const Vector2D& v1, const Vector2D& v2, float t);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	/// <summary>
	/// Normalizes the vector itself
	/// </summary>
	/// <returns>Reference to the calling vector</returns>
	Vector2D& Normalize();

	/// <summary>
	/// Returns a normalized copy of the vector
	/// </summary>
	Vector2D GetNormalized() const;

	/// <summary>
	/// Negates the vector itself. Same as multiplying by -1
	/// </summary>
	Vector2D& Negate();

	float Magnitude() const;

	friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator*(const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator/(const Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	friend Vector2D operator*(const Vector2D& vec, const float& i);
	friend Vector2D operator*(const float& i, const Vector2D& vec);
	friend Vector2D operator/(const Vector2D& vec, const float& i);
	friend Vector2D operator/(const float& i, const Vector2D& vec);

	Vector2D& operator*=(const float& i);
	Vector2D& operator/=(const float& i);

	Vector2D& operator=(const Vector2D& vec);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

