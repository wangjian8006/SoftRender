#pragma once
#include <math.h>
#include <Windows.h>
#include <stdio.h>

struct Vector4
{
	float x, y, z, w;
	Vector4()
	{
		x = y = z = w = .0f;
	}
	Vector4(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
		w = .0f;
	}
	Vector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	float Length()
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	void MultiValue(float value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		this->w *= value;
	}

	void CopyFrom(const Vector4 &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}

	void CopyTo(Vector4& vec)
	{
		vec.x = x;
		vec.y = y;
		vec.z = z;
		vec.w = w;
	}

	Vector4 operator+(const Vector4& b) const
    {
        Vector4 vec;
		vec.x = this->x + b.x;
        vec.y = this->y + b.y;
        vec.z = this->z + b.z;
		vec.w = this->w + b.w;
        return vec;
    }

	Vector4 operator-(const Vector4& b) const
    {
        Vector4 vec;
		vec.x = this->x - b.x;
        vec.y = this->y - b.y;
        vec.z = this->z - b.z;
		vec.w = this->w - b.w;
        return vec;
    }
	
	Vector4 operator*(const Vector4& b) const
    {
        Vector4 vec;
		vec.x = this->x * b.x;
        vec.y = this->y * b.y;
        vec.z = this->z * b.z;
		vec.w = this->w * b.w;
        return vec;
    }

	Vector4 operator/(const float& b) const
    {
        Vector4 vec;
		vec.x = this->x / b;
        vec.y = this->y / b;
        vec.z = this->z / b;
		vec.w = this->w / b;
        return vec;
    }

	Vector4 operator*(const float& b) const
    {
        Vector4 vec;
		vec.x = this->x * b;
        vec.y = this->y * b;
        vec.z = this->z * b;
		vec.w = this->w * b;
        return vec;
    }

	void Normalize()
	{
		float len = this->Length();
		this->x /= len;
		this->y /= len;
		this->z /= len;
		this->w /= len;
	}

	char* toString()
	{
		char* str = new char[60];
		sprintf_s(str, 60, "(%10f, %10f, %10f, %10f)\r\n", x, y, z, w);
		return str;
	}

	void Homogenize()
	{
		float rhw = 1.0f / w;
		x *= rhw;
		y *= rhw;
		z *= rhw;
		w *= rhw;
	}

	void Lerp(const Vector4 &a, const Vector4 &b, float rate)
	{
		this->x = a.x + (b.x - a.x) * rate;
		this->y = a.y + (b.y - a.y) * rate;
		this->z = a.z + (b.z - a.z) * rate;
		this->w = a.w + (b.w - a.w) * rate;
	}
};

struct Vector3
{
	float x, y, z;

	Vector3()
	{
		x = y = z = .0f;
	}
	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	float Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	void CopyFrom(const Vector3 &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	void CopyTo(Vector3 &vec)
	{
		vec.x = x;
		vec.y = y;
		vec.z = z;
	}

	Vector3 operator+(const Vector3& b) const
    {
        Vector3 vec;
		vec.x = this->x + b.x;
        vec.y = this->y + b.y;
        vec.z = this->z + b.z;
        return vec;
    }

	Vector3 operator-(const Vector3& b) const
    {
        Vector3 vec;
		vec.x = this->x - b.x;
        vec.y = this->y - b.y;
        vec.z = this->z - b.z;
        return vec;
    }

	Vector3 operator-(const Vector4& b) const
    {
        Vector3 vec;
		vec.x = this->x - b.x;
        vec.y = this->y - b.y;
        vec.z = this->z - b.z;
        return vec;
    }

	Vector3 operator*(const Vector3& b) const
    {
        Vector3 vec;
		vec.x = this->x * b.x;
        vec.y = this->y * b.y;
		vec.z = this->z * b.z;
        return vec;
    }

	Vector3 operator*(const float& b) const
    {
        Vector3 vec;
		vec.x = this->x * b;
        vec.y = this->y * b;
		vec.z = this->z * b;
        return vec;
    }

	Vector3 operator-() const
	{
		Vector3 vec;
		vec.x = this->x * -1;
        vec.y = this->y * -1;
		vec.z = this->z * -1;
        return vec;
	}

	void Normalize()
	{
		float len = this->Length();
		this->x /= len;
		this->y /= len;
		this->z /= len;
	}

	void Lerp(const Vector3 &a, const Vector3 &b, float rate)
	{
		this->x = a.x + (b.x - a.x) * rate;
		this->y = a.y + (b.y - a.y) * rate;
		this->z = a.z + (b.z - a.z) * rate;
	}

	char* toString()
	{
		char* str = new char[50];
		sprintf_s(str, 50, "(%10f, %10f, %10f)\r\n", x, y, z);
		return str;
	}

	//²æ³Ë
	static Vector3 CrossProduct(const Vector3 &a, const Vector3& b)
	{
		Vector3 vec;
		vec.x = a.y * b.z - a.z * b.y;
		vec.y = a.z * b.x - a.x * b.z;
		vec.z = a.x * b.y - a.y * b.x;
		return vec;
	}

	static float Dot(const Vector3&a, const Vector3 &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	static Vector3 Up()
	{
		Vector3 vec;
		vec.x = vec.z = 0;
		vec.y = 1;
		return vec;
	}
};

struct Vector2
{
	float x, y;
	Vector2()
	{
		x = y = .0f;
	}
	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	float Length()
	{
		return sqrt(x * x + y * y);
	}
	void MultiValue(float value)
	{
		this->x *= value;
		this->y *= value;
	}

	void CopyFrom(const Vector2 &vec)
	{
		x = vec.x;
		y = vec.y;
	}

	void CopyTo(Vector2 &vec)
	{
		vec.x = x;
		vec.y = y;
	}

	Vector2 operator+(const Vector2& b) const
    {
        Vector2 vec;
		vec.x = this->x + b.x;
        vec.y = this->y + b.y;
        return vec;
    }

	Vector2 operator-(const Vector2& b) const
    {
        Vector2 vec;
		vec.x = this->x - b.x;
        vec.y = this->y - b.y;
        return vec;
    }

	Vector2 operator*(const float b) const
    {
        Vector2 vec;
		vec.x = this->x * b;
        vec.y = this->y * b;
        return vec;
    }

	void Normalize()
	{
		float len = this->Length();
		this->x /= len;
		this->y /= len;
	}

	void Lerp(const Vector2 &a, const Vector2 &b, float rate)
	{
		this->x = a.x + (b.x - a.x) * rate;
		this->y = a.y + (b.y - a.y) * rate;
	}

	char* toString()
	{
		char* str = new char[30];
		sprintf_s(str, 30, "(%10f, %10f)\r\n", x, y);
		return str;
	}
};

struct DrawColor
{
	unsigned char r; 
	unsigned char g;
	unsigned char b;
	unsigned char a;

	DrawColor()
	{
		r = g = b = a = 0;
	}

	DrawColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	void CopyFrom(const DrawColor& color)
	{
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		this->a = color.a;
	}

	void Lerp(const DrawColor &a, const DrawColor &b, float rate)
	{
		this->r = Clamp(0, 255, a.r + (int)((float)(b.r - a.r) * rate));
		this->g = Clamp(0, 255, a.g + (int)((float)(b.g - a.g) * rate));
		this->b = Clamp(0, 255, a.b + (int)((float)(b.b - a.b) * rate));
		this->a = Clamp(0, 255, a.a + (int)((float)(b.a - a.a) * rate));
	}

	static unsigned char Clamp(int min, int max, int value)
	{
		if (value < min) value = min;
		else if (value > max) value = max;
		return value;
	}

	static unsigned int ColorToInt(const DrawColor& color)
	{
		int R = (int)(color.r);
		int G = (int)(color.g);
		int B = (int)(color.b);
		int A = (int)(color.a);
		return (A<<24) | (R << 16) | (G << 8) | (B);
	}

	static DrawColor IntToColor(unsigned int i)
	{
		DrawColor color;
		color.b = i & 0xff; i = i >> 8;
		color.g = i & 0xff; i = i >> 8;
		color.r = i & 0xff; i = i >> 8;
		color.a = i & 0xff;
		return color;
	}

	static Vector4 ColorToFloat(const DrawColor& color)
	{
		Vector4 vec;
		vec.x = (float)color.r / 255.0f;
		vec.y = (float)color.g / 255.0f;
		vec.z = (float)color.b / 255.0f;
		vec.w = (float)color.a / 255.0f;
		return vec;
	}

	static DrawColor FloatToColor(const Vector4& f)
	{
		DrawColor color;
		color.r = (unsigned char)(f.x * 255.0f);
		color.g = (unsigned char)(f.y * 255.0f);
		color.b = (unsigned char)(f.z * 255.0f);
		color.a = (unsigned char)(f.w * 255.0f);
		return color;
	}

	static Vector3 ColorToFloat3(const DrawColor& color)
	{
		Vector3 vec;
		vec.x = (float)color.r / 255.0f;
		vec.y = (float)color.g / 255.0f;
		vec.z = (float)color.b / 255.0f;
		return vec;
	}

	DrawColor operator+(const DrawColor& b) const
    {
        DrawColor color;
		color.r = Clamp(0, 255, (int)(this->r + b.r));
        color.g = Clamp(0, 255, (int)(this->g + b.g));
        color.b = Clamp(0, 255, (int)(this->b + b.b));
		color.a = Clamp(0, 255, (int)(this->a + b.a));
        return color;
    }

	DrawColor operator-(const DrawColor& b) const
    {
        DrawColor color;
		color.r = Clamp(0, 255, (int)(this->r - b.r));
        color.g = Clamp(0, 255, (int)(this->g - b.g));
        color.b = Clamp(0, 255, (int)(this->b - b.b));
		color.a = Clamp(0, 255, (int)(this->a - b.a));
        return color;
    }
	
	DrawColor operator*(const DrawColor& b) const
    {
        DrawColor color;
		color.r = Clamp(0, 255, (int)(this->r * b.r));
        color.g = Clamp(0, 255, (int)(this->g * b.g));
        color.b = Clamp(0, 255, (int)(this->b * b.b));
		color.a = Clamp(0, 255, (int)(this->a * b.a));
        return color;
    }

	DrawColor operator/(const DrawColor& b) const
    {
		DrawColor color;
		color.r = Clamp(0, 255, (int)(this->r / b.r));
        color.g = Clamp(0, 255, (int)(this->g / b.g));
        color.b = Clamp(0, 255, (int)(this->b / b.b));
		color.a = Clamp(0, 255, (int)(this->a / b.a));
        return color;
    }

	DrawColor operator*(const float& b) const
    {
        DrawColor color;
		color.r = Clamp(0, 255, (int)(this->r * b));
        color.g = Clamp(0, 255, (int)(this->g * b));
        color.b = Clamp(0, 255, (int)(this->b * b));
		color.a = Clamp(0, 255, (int)(this->a * b));
        return color;
    }

	DrawColor operator*(const Vector4& b) const
    {
        DrawColor color;
		color.r = Clamp(0, 255, (int)(this->r * b.x));
        color.g = Clamp(0, 255, (int)(this->g * b.y));
        color.b = Clamp(0, 255, (int)(this->b * b.z));
		color.a = Clamp(0, 255, (int)(this->a * b.w));
        return color;
    }

	DrawColor operator+(const Vector4& b) const
    {
        DrawColor color;
		color.r = Clamp(0, 255, (int)(this->r + b.x));
        color.g = Clamp(0, 255, (int)(this->g + b.y));
        color.b = Clamp(0, 255, (int)(this->b + b.z));
		color.a = Clamp(0, 255, (int)(this->a + b.w));
        return color;
    }
};