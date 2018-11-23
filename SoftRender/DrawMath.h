#pragma once
#include <math.h>
#include "Vector.h"
#include "Matrix.h"

struct Rect
{
	float x, y, w, h;
}; 

class DrawMath
{
public:
	static float PI;
	static float Deg2Rad;
	static float Rad2Deg;

	static int Clamp(int x, int min, int max);
	static float Interp(float x1, float x2, float t);

	static void MatrixSetTRS(const Vector3 &translate, const Vector3 &euler, const Vector3 &scale, Matrix4x4 &mt);
	static void MatrixSetTR(const Vector3 &translate, const Vector3 &euler, Matrix4x4 &mt);
	static void TranslateToMatrix(const Vector3 &translate, Matrix4x4 &mt);
	static void ScaleToMatrix(const Vector3 &scale, Matrix4x4 &mt);
	static Vector3 GetMatrixScale(Matrix4x4 &mt);

	static void LookAtToRotationMatrix(const Vector3 &eye, const Vector3 &target, const Vector3 &up, Matrix4x4 &mt);
	static void LookAtToRotationMatrix(const Vector3 &dir, const Vector3 &up, Matrix4x4 &mt);
	static void EulerToMatrix(const Vector3 &euler, Matrix4x4 &mt);
	static void MatrixToEuler(const Matrix4x4 &mt, Vector3 &euler);
	static void QuaternionToMatrix(const Vector4 &rotation, Matrix4x4 &mt);
	static void MartixToQuaternion(const Matrix4x4 &mt, Vector4 &rotation);
	static void EulerToQuaternion(const Vector3 &euler, Vector4 &rotation);
	static void QuaternionToEuler(const Vector4 &rotation, Vector3 &euler);

	static void QuaternionNormalize(Vector4 &rotation);
	static Vector4 QuaternionMultiQuaternion(const Vector4 &leftRotation, const Vector4 &rightRotation);

	static void MatrixPerspective(Matrix4x4 &mt, float fovy, float aspect, float zn, float zf);
	static void ScreenProjection(Matrix4x4 &mt, int clientWidth, int clientHeight);

	static Vector3 ReflectVector(const Vector3 &I, const Vector3 &N);
};

