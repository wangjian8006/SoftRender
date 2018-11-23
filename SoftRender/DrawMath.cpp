#include "DrawMath.h"

float DrawMath::PI = 3.14159274f;
float DrawMath::Deg2Rad = 0.0174532924f;
float DrawMath::Rad2Deg = 57.29578f;

int DrawMath::Clamp(int x, int min, int max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

float DrawMath::Interp(float x1, float x2, float t)
{
	return x1 + (x2 - x1) * t;
}

void DrawMath::TranslateToMatrix(const Vector3 &translate, Matrix4x4 &mt)
{
	mt.CopyRowFrom(Vector4(1, 0, 0, translate.x), 0);
    mt.CopyRowFrom(Vector4(0, 1, 0, translate.y), 1);
    mt.CopyRowFrom(Vector4(0, 0, 1, translate.z), 2);
    mt.CopyRowFrom(Vector4(0, 0, 0, 1), 3);
}

void DrawMath::ScaleToMatrix(const Vector3 &scale, Matrix4x4 &mt)
{
	mt.CopyRowFrom(Vector4(scale.x, 0, 0, 0), 0);
    mt.CopyRowFrom(Vector4(0, scale.y, 0, 0), 1);
    mt.CopyRowFrom(Vector4(0, 0, scale.z, 0), 2);
    mt.CopyRowFrom(Vector4(0, 0, 0, 1), 3);
}

void DrawMath::MatrixSetTRS(const Vector3 &translate, const Vector3 &euler, const Vector3 &scale, Matrix4x4 &mt)
{
	Matrix4x4 scaleMatrix = Matrix4x4();
	DrawMath::ScaleToMatrix(scale, scaleMatrix);

	Matrix4x4 rotationMatrix;
	DrawMath::EulerToMatrix(euler, rotationMatrix);

    Matrix4x4 translateMatrix = Matrix4x4();
    DrawMath::TranslateToMatrix(translate, translateMatrix);

	mt.CopyFrom(translateMatrix);
	mt.Append(rotationMatrix);
	mt.Append(scaleMatrix);
}

void DrawMath::MatrixSetTR(const Vector3 &translate, const Vector3 &euler, Matrix4x4 &mt)
{
	Matrix4x4 rotationMatrix;
	DrawMath::EulerToMatrix(euler, rotationMatrix);

    Matrix4x4 translateMatrix = Matrix4x4();
    translateMatrix.CopyRowFrom(Vector4(1, 0, 0, translate.x), 0);
    translateMatrix.CopyRowFrom(Vector4(0, 1, 0, translate.y), 1);
    translateMatrix.CopyRowFrom(Vector4(0, 0, 1, translate.z), 2);
    translateMatrix.CopyRowFrom(Vector4(0, 0, 0, 1), 3);

	mt.CopyFrom(translateMatrix);
	mt.Append(rotationMatrix);
}

void DrawMath::LookAtToRotationMatrix(const Vector3 &eye, const Vector3 &target, const Vector3 &up, Matrix4x4 &mt)
{
	Vector3 dir;
	dir.CopyFrom(target);
	dir = dir - eye;
	DrawMath::LookAtToRotationMatrix(dir, up, mt);
}

void DrawMath::LookAtToRotationMatrix(const Vector3 &dir, const Vector3 &up, Matrix4x4 &mt)
{
	mt.Identity();

	Vector3 zdir = dir;
	zdir.Normalize();
	Vector3 xdir = Vector3::CrossProduct(up, zdir);
	xdir.Normalize();
	Vector3 ydir = Vector3::CrossProduct(zdir, xdir);
		
	mt.CopyColumnFrom(xdir, 0);
	mt.CopyColumnFrom(ydir, 1);
	mt.CopyColumnFrom(zdir, 2);
}

void DrawMath::EulerToMatrix(const Vector3 &euler, Matrix4x4 &mt)
{
	Vector3 rotation;
	rotation.CopyFrom(euler);
	rotation = rotation * DrawMath::Deg2Rad;

    Matrix4x4 rotateMatrixZ = Matrix4x4();
    rotateMatrixZ.CopyRowFrom(Vector4(cos(rotation.z), -sin(rotation.z), 0, 0), 0);
    rotateMatrixZ.CopyRowFrom(Vector4(sin(rotation.z), cos(rotation.z), 0, 0), 1);
    rotateMatrixZ.CopyRowFrom(Vector4(0, 0, 1, 0), 2);
    rotateMatrixZ.CopyRowFrom(Vector4(0, 0, 0, 1), 3);

    Matrix4x4 rotateMatrixY = Matrix4x4();
    rotateMatrixY.CopyRowFrom(Vector4(cos(rotation.y), 0, sin(rotation.y), 0), 0);
    rotateMatrixY.CopyRowFrom(Vector4(0, 1, 0, 0), 1);
    rotateMatrixY.CopyRowFrom(Vector4(-sin(rotation.y), 0, cos(rotation.y), 0), 2);
    rotateMatrixY.CopyRowFrom(Vector4(0, 0, 0, 1), 3);

    Matrix4x4 rotateMatrixX = Matrix4x4();
    rotateMatrixX.CopyRowFrom(Vector4(1, 0, 0, 0), 0);
    rotateMatrixX.CopyRowFrom(Vector4(0, cos(rotation.x), -sin(rotation.x), 0), 1);
    rotateMatrixX.CopyRowFrom(Vector4(0, sin(rotation.x), cos(rotation.x), 0), 2);
    rotateMatrixX.CopyRowFrom(Vector4(0, 0, 0, 1), 3);

	mt.CopyFrom(rotateMatrixY);
	mt.Append(rotateMatrixX);
	mt.Append(rotateMatrixZ);
}

void DrawMath::MatrixToEuler(const Matrix4x4 &mt, Vector3 &euler)
{
    float sp = -mt.m[1][2];
    if (sp <= -1.0f) euler.x = -DrawMath::PI * 0.5f;
    else if (sp >= 1.0f) euler.x = DrawMath::PI * 0.5f;
    else euler.x = asin(sp);

    if (sp > 0.9999f)
    {
        euler.y = atan2(-mt.m[2][0], mt.m[0][0]);
        euler.z = 0.0f;
    }
    else
    {
        euler.y = atan2(mt.m[0][2], mt.m[2][2]);
        euler.z = atan2(mt.m[1][0], mt.m[1][1]);
    }

	euler = euler * DrawMath::Rad2Deg;
}

void DrawMath::QuaternionToMatrix(const Vector4 &rotation, Matrix4x4 &mt)
{
	mt.Identity();
    float x = rotation.x * 2.0f;
    float y = rotation.y * 2.0f;
    float z = rotation.z * 2.0f;
    float xx = rotation.x * x;
    float yy = rotation.y * y;
    float zz = rotation.z * z;

    float xy = rotation.x * y;
    float xz = rotation.x * z;
    float yz = rotation.y * z;

    float wx = rotation.w * x;
    float wy = rotation.w * y;
    float wz = rotation.w * z;

    mt.m[0][0] = 1.0f - (yy + zz);
    mt.m[0][1] = xy + wz;
    mt.m[0][2] = xz - wy;
    mt.m[0][3] = 0.0f;

    mt.m[1][0] = xy - wz;
    mt.m[1][1] = 1.0f - (xx + zz);
    mt.m[1][2] = yz + wx;
    mt.m[1][3] = 0.0f;

    mt.m[2][0] = xz + wy;
    mt.m[2][1] = yz - wx;
    mt.m[2][2] = 1.0f - (xx + yy);
    mt.m[2][3] = 0.0f;

    mt.m[3][0] = 0.0f;
    mt.m[3][1] = 0.0f;
    mt.m[3][2] = 0.0f;
    mt.m[3][3] = 1.0f;
}

void DrawMath::MartixToQuaternion(const Matrix4x4 &mt, Vector4 &rotation)
{
	float t = mt.m[0][0] + mt.m[1][1] + mt.m[2][2];

    if (t > 0.0f)
    {
        t = sqrt(t + 1.0f) * 0.5f;
        rotation.w = t;
        t = 0.5f / t;

        rotation.y = (mt.m[2][1] - mt.m[1][2]) * t;
        rotation.z = (mt.m[0][2] - mt.m[2][0]) * t;
        rotation.w = (mt.m[1][0] - mt.m[0][1]) * t;
    }
    else
    {
        int s_iNext[3] = { 1, 2, 0 };
        int i = 0;
        if (mt.m[1][1] > mt.m[0][0]) i = 1;
        if (mt.m[2][2] > mt.m[i][i]) i = 2;

        int j = s_iNext[i];
        int k = s_iNext[j];

		float* apkQuat[] = {&rotation.x, &rotation.y, &rotation.z};
        t = sqrt(mt.m[i][i] - mt.m[j][j] - mt.m[k][k] + 1.0f);
        *apkQuat[i] = t * 0.5f;
        t = 0.5f / t;
        rotation.w = (mt.m[k][j] - mt.m[j][k]) * t;
        *apkQuat[j] = (mt.m[j][i] + mt.m[i][j]) * t;
        *apkQuat[k] = (mt.m[k][i] + mt.m[i][k]) * t;
    }

    DrawMath::QuaternionNormalize(rotation);
}

void DrawMath::EulerToQuaternion(const Vector3 &euler, Vector4 &rotation)
{
	Vector3 e;
	e.CopyFrom(euler);
	e = e * DrawMath::Deg2Rad;

    float cX = (cos (e.x * 0.5f));
	float sX = (sin (e.x * 0.5f));

	float cY = (cos (e.y * 0.5f));
	float sY = (sin (e.y * 0.5f));

	float cZ = (cos (e.z * 0.5f));
	float sZ = (sin (e.z * 0.5f));
	
	Vector4 qX = Vector4(sX, 0.0F, 0.0F, cX);
	Vector4 qY = Vector4(0.0F, sY, 0.0F, cY);
    Vector4 qZ = Vector4(0.0F, 0.0F, sZ, cZ);

    //Quaternion q = (qY * qX) * qZ;
	Vector4 result = DrawMath::QuaternionMultiQuaternion(qY, qX);
	result = DrawMath::QuaternionMultiQuaternion(result, qZ);

	rotation.CopyFrom(result);
}
void DrawMath::QuaternionToEuler(const Vector4 &rotation, Vector3 &euler)
{
	Matrix4x4 mt;
	DrawMath::QuaternionToMatrix (rotation, mt);
	DrawMath::MatrixToEuler(mt, euler);
}

void DrawMath::QuaternionNormalize(Vector4 &rotation)
{
	float len = sqrt(rotation.x * rotation.x + rotation.y * rotation.y + rotation.z * rotation.z + rotation.w * rotation.w);
    if (len < 0.00001f){
        rotation.x = rotation.y = rotation.z = 0.0f;
		rotation.w = 1.0f;
    }else
	{
		rotation = rotation / len;
	}
}
Vector4 DrawMath::QuaternionMultiQuaternion(const Vector4 &q1, const Vector4 &q2)
{
	Vector4 result;
    result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return result;
}

Vector3 DrawMath::GetMatrixScale(Matrix4x4 &mt)
{
	Vector3 vec;
	Vector3 v0, v1, v2;
	mt.CopyColumnTo(v0, 0);
	mt.CopyColumnTo(v1, 1);
	mt.CopyColumnTo(v2, 2);

	vec.x = v0.Length();
	vec.y = v1.Length();
	vec.z = v2.Length();
	return vec;
}

void DrawMath::MatrixPerspective(Matrix4x4 &mt, float fovy, float aspect, float zn, float zf)
{
	float fax = 1.0f / (float)tan(fovy * 0.5f);
	mt.Zero();
	mt.m[0][0] = (float)(fax / aspect);
	mt.m[1][1] = (float)(fax);
	mt.m[2][2] = -(zf + zn) / (zf - zn);
	mt.m[2][3] = 2.0f * zn * zf / (zn - zf);
	mt.m[3][2] = -1.0f;
}
	
void DrawMath::ScreenProjection(Matrix4x4 &mt, int clientWidth, int clientHeight)
{
	mt.Zero();
	mt.m[0][0] = (float)clientWidth / 2.0f;
	mt.m[1][1] = (float)clientHeight / 2.0f;
	mt.m[2][1] = 1;
	mt.m[3][0] = mt.m[0][0];
	mt.m[3][1] = mt.m[1][1];
	mt.m[3][3] = 1;

	/*clientWidth / 2, 0, 0, 0,
	0, clientHeight / 2, 0, 0,
	0, 0, 1, 0,
	clientWidth / 2, clientHeight / 2, 0, 1*/
}

Vector3 DrawMath::ReflectVector(const Vector3 &I, const Vector3 &N)
{
	//¹«Ê½ R = I - 2(I¡¤N)
	float tmp = 2.0f * Vector3::Dot(I, N);
	return I - (N * tmp);
}