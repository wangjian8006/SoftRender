#pragma once
#include "Vector.h"

#define SWAP_VALUE(a, b, temp) temp=a;a=b;b=temp;

struct Matrix4x4
{
	float m[4][4];

	Matrix4x4()
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = 0;
	}
	Matrix4x4(float a1,float a2,float a3,float a4,
			 float b1,float b2,float b3,float b4,
			 float c1,float c2,float c3,float c4,
		     float d1,float d2,float d3,float d4)
	{
		m[0][0] = a1;m[0][1] = a2;m[0][2] = a3;m[0][3] = a4;
		m[1][0] = b1;m[1][1] = b2;m[1][2] = b3;m[1][3] = b4;
		m[2][0] = c1;m[2][1] = c2;m[2][2] = c3;m[2][3] = c4;
		m[3][0] = d1;m[3][1] = d2;m[3][2] = d3;m[3][3] = d4;
	}

	void Zero()
	{
		float* ptr = m[0];
		for (int i = 0; i < 16; ++i) ptr[i] = 0;
	}

	void Identity()
	{
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f; 
		m[0][1] = m[0][2] = m[0][3] = 0.0f;
		m[1][0] = m[1][2] = m[1][3] = 0.0f;
		m[2][0] = m[2][1] = m[2][3] = 0.0f;
		m[3][0] = m[3][1] = m[3][2] = 0.0f;
	}

	void CopyColumnFrom(const Vector4 &vec, int col)
	{
		if (col < 0 || col > 3) return;
		m[0][col] = vec.x;
		m[1][col] = vec.y;
		m[2][col] = vec.z;
		m[3][col] = vec.w;
	}
	
	void CopyColumnFrom(const Vector3 &vec, int col)
	{
		if (col < 0 || col > 3) return;
		m[0][col] = vec.x;
		m[1][col] = vec.y;
		m[2][col] = vec.z;
	}

	void CopyColumnTo(Vector4 &vec, int col)
	{
		if (col < 0 || col > 3) return;
		vec.x = m[0][col];
		vec.y = m[1][col];
		vec.z = m[2][col];
		vec.w = m[3][col];
	}

	void CopyColumnTo(Vector3 &vec, int col)
	{
		if (col < 0 || col > 3) return;
		vec.x = m[0][col];
		vec.y = m[1][col];
		vec.z = m[2][col];
	}

	void CopyRowFrom(const Vector4 &vec, int row)
	{
		if (row < 0 || row > 3) return;
		m[row][0] = vec.x;
		m[row][1] = vec.y;
		m[row][2] = vec.z;
		m[row][3] = vec.w;
	}

	void CopyRowFrom(const Vector3 &vec, int row)
	{
		if (row < 0 || row > 3) return;
		m[row][0] = vec.x;
		m[row][1] = vec.y;
		m[row][2] = vec.z;
	}

	void CopyRowTo(Vector4 &vec, int row)
	{
		if (row < 0 || row > 3) return;
		vec.x = m[row][0];
		vec.y = m[row][1];
		vec.z = m[row][2];
		vec.w = m[row][3];
	}

	void CopyRowTo(Vector3 &vec, int row)
	{
		if (row < 0 || row > 3) return;
		vec.x = m[row][0];
		vec.y = m[row][1];
		vec.z = m[row][2];
	}

	void CopyTo(Matrix4x4 &toMt)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) 
				toMt.m[i][j] = m[i][j];
	}

	void CopyFrom(const Matrix4x4 &fromMt)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) 
				m[i][j] = fromMt.m[i][j];
	}

	void Append(const Matrix4x4 &mt)
	{
		float m00 = m[0][0] * mt.m[0][0] + m[0][1] * mt.m[1][0] + m[0][2] * mt.m[2][0] + m[0][3] * mt.m[3][0];
		float m01 = m[0][0] * mt.m[0][1] + m[0][1] * mt.m[1][1] + m[0][2] * mt.m[2][1] + m[0][3] * mt.m[3][1];
		float m02 = m[0][0] * mt.m[0][2] + m[0][1] * mt.m[1][2] + m[0][2] * mt.m[2][2] + m[0][3] * mt.m[3][2];
		float m03 = m[0][0] * mt.m[0][3] + m[0][1] * mt.m[1][3] + m[0][2] * mt.m[2][3] + m[0][3] * mt.m[3][3];

		float m10 = m[1][0] * mt.m[0][0] + m[1][1] * mt.m[1][0] + m[1][2] * mt.m[2][0] + m[1][3] * mt.m[3][0];
		float m11 = m[1][0] * mt.m[0][1] + m[1][1] * mt.m[1][1] + m[1][2] * mt.m[2][1] + m[1][3] * mt.m[3][1];
		float m12 = m[1][0] * mt.m[0][2] + m[1][1] * mt.m[1][2] + m[1][2] * mt.m[2][2] + m[1][3] * mt.m[3][2];
		float m13 = m[1][0] * mt.m[0][3] + m[1][1] * mt.m[1][3] + m[1][2] * mt.m[2][3] + m[1][3] * mt.m[3][3];

		float m20 = m[2][0] * mt.m[0][0] + m[2][1] * mt.m[1][0] + m[2][2] * mt.m[2][0] + m[2][3] * mt.m[3][0];
		float m21 = m[2][0] * mt.m[0][1] + m[2][1] * mt.m[1][1] + m[2][2] * mt.m[2][1] + m[2][3] * mt.m[3][1];
		float m22 = m[2][0] * mt.m[0][2] + m[2][1] * mt.m[1][2] + m[2][2] * mt.m[2][2] + m[2][3] * mt.m[3][2];
		float m23 = m[2][0] * mt.m[0][3] + m[2][1] * mt.m[1][3] + m[2][2] * mt.m[2][3] + m[2][3] * mt.m[3][3];

		float m30 = m[3][0] * mt.m[0][0] + m[3][1] * mt.m[1][0] + m[3][2] * mt.m[2][0] + m[3][3] * mt.m[3][0];
		float m31 = m[3][0] * mt.m[0][1] + m[3][1] * mt.m[1][1] + m[3][2] * mt.m[2][1] + m[3][3] * mt.m[3][1];
		float m32 = m[3][0] * mt.m[0][2] + m[3][1] * mt.m[1][2] + m[3][2] * mt.m[2][2] + m[3][3] * mt.m[3][2];
		float m33 = m[3][0] * mt.m[0][3] + m[3][1] * mt.m[1][3] + m[3][2] * mt.m[2][3] + m[3][3] * mt.m[3][3];

		m[0][0] = m00;m[0][1] = m01;m[0][2] = m02;m[0][3] = m03;
		m[1][0] = m10;m[1][1] = m11;m[1][2] = m12;m[1][3] = m13;
		m[2][0] = m20;m[2][1] = m21;m[2][2] = m22;m[2][3] = m23;
		m[3][0] = m30;m[3][1] = m31;m[3][2] = m32;m[3][3] = m33;
	}

	Matrix4x4 operator*(const Matrix4x4& rhs) const
    {
        Matrix4x4 mat;
		for (int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j)
			{
				mat.m[j][i] = (m[j][0] * rhs.m[0][i]) +
							  (m[j][1] * rhs.m[1][i]) +
							  (m[j][2] * rhs.m[2][i]) +
							  (m[j][3] * rhs.m[3][i]);
			}
        return mat;
    }

	//转置
	void Transpose()
	{
		float temp;
		SWAP_VALUE(m[0][1], m[1][0], temp);
		SWAP_VALUE(m[0][2], m[2][0], temp);
		SWAP_VALUE(m[0][3], m[3][0], temp);

		SWAP_VALUE(m[1][2], m[2][1], temp);
		SWAP_VALUE(m[1][3], m[3][1], temp);

		SWAP_VALUE(m[2][3], m[3][2], temp);
	}

	//行列式
	float Det()
	{
		float _3142_3241 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
		float _3143_3341 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
		float _3144_3441 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
		float _3243_3342 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
		float _3244_3442 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
		float _3344_3443 = m[2][2] * m[3][3] - m[2][3] * m[3][2];

		float result = m[0][0] * (m[1][1] * _3344_3443 - m[1][2] * _3244_3442 + m[1][3] * _3243_3342)
				- m[0][1] * (m[1][0] * _3344_3443 - m[1][2] * _3144_3441 + m[1][3] * _3143_3341)
				+ m[0][2] * (m[1][0] * _3244_3442 - m[1][1] * _3144_3441 + m[1][3] * _3142_3241)
				- m[0][3] * (m[1][0] * _3243_3342 - m[1][1] * _3143_3341 + m[1][2] * _3142_3241);
		float a1 = m[1][1] * _3344_3443;
		float a2 = m[1][2] * _3244_3442;
		float a3 = m[1][3] * _3243_3342;
		
		float b1 = m[1][0] * _3344_3443;
		float b2 = m[1][2] * _3144_3441;
		float b3 = m[1][3] * _3143_3341;

		float c = (m[1][0] * _3244_3442 - m[1][1] * _3144_3441 + m[1][3] * _3142_3241);
		float d = (m[1][0] * _3243_3342 - m[1][1] * _3143_3341 + m[1][2] * _3142_3241);


		return result;
	}

	//逆矩阵
	void Inverse(Matrix4x4 *out = NULL)
	{
		float det = this->Det();
		if (det == 0) return;

		float _2132_2231(m[1][0] * m[2][1] - m[1][1] * m[2][0]);
		float _2133_2331(m[1][0] * m[2][2] - m[1][2] * m[2][0]);
		float _2134_2431(m[1][0] * m[2][3] - m[1][3] * m[2][0]);
		float _2142_2241(m[1][0] * m[3][1] - m[1][1] * m[3][0]);
		float _2143_2341(m[1][0] * m[3][2] - m[1][2] * m[3][0]);
		float _2144_2441(m[1][0] * m[3][3] - m[1][3] * m[3][0]);
		float _2233_2332(m[1][1] * m[2][2] - m[1][2] * m[2][1]);
		float _2234_2432(m[1][1] * m[2][3] - m[1][3] * m[2][1]);
		float _2243_2342(m[1][1] * m[3][2] - m[1][2] * m[3][1]);
		float _2244_2442(m[1][1] * m[3][3] - m[1][3] * m[3][1]);
		float _2334_2433(m[1][2] * m[2][3] - m[1][3] * m[2][2]);
		float _2344_2443(m[1][2] * m[3][3] - m[1][3] * m[3][2]);
		float _3142_3241(m[2][0] * m[3][1] - m[2][1] * m[3][0]);
		float _3143_3341(m[2][0] * m[3][2] - m[2][2] * m[3][0]);
		float _3144_3441(m[2][0] * m[3][3] - m[2][3] * m[3][0]);
		float _3243_3342(m[2][1] * m[3][2] - m[2][2] * m[3][1]);
		float _3244_3442(m[2][1] * m[3][3] - m[2][3] * m[3][1]);
		float _3344_3443(m[2][2] * m[3][3] - m[2][3] * m[3][2]);

		if (out == NULL) out = new Matrix4x4();
		float invDet = 1.0f / det;

		out->m[0][0] = +invDet * (m[1][1] * _3344_3443 - m[1][2] * _3244_3442 + m[1][3] * _3243_3342);
		out->m[0][1] = -invDet * (m[0][1] * _3344_3443 - m[0][2] * _3244_3442 + m[0][3] * _3243_3342);
		out->m[0][2] = +invDet * (m[0][1] * _2344_2443 - m[0][2] * _2244_2442 + m[0][3] * _2243_2342);
		out->m[0][3] = -invDet * (m[0][1] * _2334_2433 - m[0][2] * _2234_2432 + m[0][3] * _2233_2332);

		out->m[1][0] = -invDet * (m[1][0] * _3344_3443 - m[1][2] * _3144_3441 + m[1][3] * _3143_3341);
		out->m[1][1] = +invDet * (m[0][0] * _3344_3443 - m[0][2] * _3144_3441 + m[0][3] * _3143_3341);
		out->m[1][2] = -invDet * (m[0][0] * _2344_2443 - m[0][2] * _2144_2441 + m[0][3] * _2143_2341);
		out->m[1][3] = +invDet * (m[0][0] * _2334_2433 - m[0][2] * _2134_2431 + m[0][3] * _2133_2331);

		out->m[2][0] = +invDet * (m[1][0] * _3244_3442 - m[1][1] * _3144_3441 + m[1][3] * _3142_3241);
		out->m[2][1] = -invDet * (m[0][0] * _3244_3442 - m[0][1] * _3144_3441 + m[0][3] * _3142_3241);
		out->m[2][2] = +invDet * (m[0][0] * _2244_2442 - m[0][1] * _2144_2441 + m[0][3] * _2142_2241);
		out->m[2][3] = -invDet * (m[0][0] * _2234_2432 - m[0][1] * _2134_2431 + m[0][3] * _2132_2231);

		out->m[3][0] = -invDet * (m[1][0] * _3243_3342 - m[1][1] * _3143_3341 + m[1][2] * _3142_3241);
		out->m[3][1] = +invDet * (m[0][0] * _3243_3342 - m[0][1] * _3143_3341 + m[0][2] * _3142_3241);
		out->m[3][2] = -invDet * (m[0][0] * _2243_2342 - m[0][1] * _2143_2341 + m[0][2] * _2142_2241);
		out->m[3][3] = +invDet * (m[0][0] * _2233_2332 - m[0][1] * _2133_2331 + m[0][2] * _2132_2231);

		this->CopyFrom(*out);
	}

	Vector4 MultiplyPoint(const Vector3 &lp)
	{
		Vector4 v = Vector4(lp.x, lp.y, lp.z, 1.0f);
		return this->MultiplyPoint(v);
	}

	Vector3 MultiplyPoint3(const Vector3 &lp)
	{
		Vector3 v;
        v.x = lp.x * m[0][0] + lp.y * m[0][1] + lp.z * m[0][2] + m[0][3];
        v.y = lp.x * m[1][0] + lp.y * m[1][1] + lp.z * m[1][2] + m[1][3];
        v.z = lp.x * m[2][0] + lp.y * m[2][1] + lp.z * m[2][2] + m[2][3];
		return v;
	}

	Vector4 MultiplyPoint(const Vector4 &lp)
	{
		Vector4 v;
        v.x = lp.x * m[0][0] + lp.y * m[0][1] + lp.z * m[0][2] + lp.w * m[0][3];
        v.y = lp.x * m[1][0] + lp.y * m[1][1] + lp.z * m[1][2] + lp.w * m[1][3];
        v.z = lp.x * m[2][0] + lp.y * m[2][1] + lp.z * m[2][2] + lp.w * m[2][3];
		v.w = lp.x * m[3][0] + lp.y * m[3][1] + lp.z * m[3][2] + lp.w * m[3][3];
		return v;
	}

	char* toString()
	{
		char* str = new char[200];
		sprintf_s(str, 200, "%10f %10f %10f %10f\r\n%10f %10f %10f %10f\r\n%10f %10f %10f %10f\r\n%10f %10f %10f %10f\r\n", 
						m[0][0], m[0][1], m[0][2], m[0][3],
						m[1][0], m[1][1], m[1][2], m[1][3],
						m[2][0], m[2][1], m[2][2], m[2][3],
						m[3][0], m[3][1], m[3][2], m[3][3]);
		return str;
	}
};