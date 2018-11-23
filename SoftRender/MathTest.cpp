#include "DrawCamera.h"
#include "DrawMath.h"

void TestMath()
{
	DrawCamera* camera = new DrawCamera();
	camera->GetTransform()->SetPosition(Vector3(0, 100.0f, 0));
	camera->GetTransform()->SetEulerAngle(Vector3(89.4269943f, 180.0f, 0.0));

	printf("%s\r\n", (camera->GetTransform()->GetWorldMatrix().toString()));
	Vector4 quaternion = Vector4(0.0, 0.710633337f, -0.703562558f, 0.0);

	//euler and quaternion -> matrix
	Matrix4x4 m1, m2, m3;
	DrawMath::EulerToMatrix(camera->GetTransform()->GetEulerAngle(), m1);
	DrawMath::LookAtToRotationMatrix(camera->GetTransform()->GetPosition(), Vector3(0, 0, -1), Vector3::Up(), m2);
	DrawMath::QuaternionToMatrix(quaternion, m3);

	printf("%s\r\n", m1.toString());
	printf("%s\r\n", m2.toString());
	printf("%s\r\n", m3.toString());

	//matrix -> euler;
	Vector3 e1, e2;
	DrawMath::MatrixToEuler(m1, e1);
	e2 = camera->GetTransform()->GetEulerAngle();

	printf("%s\r\n", e1.toString());
	printf("%s\r\n", e2.toString());

	Matrix4x4 me1, me2;
	DrawMath::EulerToMatrix(e1, me1);
	DrawMath::EulerToMatrix(e2, me2);
	printf("%s\r\n", me1.toString());
	printf("%s\r\n", me2.toString());

	//matrix -> quaternion
	Vector4 q1, q2;
	DrawMath::MartixToQuaternion(m1, q1);
	q2.CopyFrom(quaternion);

	printf("%s\r\n", q1.toString());
	printf("%s\r\n", q2.toString());

	Matrix4x4 mq1, mq2;
	DrawMath::QuaternionToMatrix(q1, mq1);
	DrawMath::QuaternionToMatrix(q2, mq2);

	printf("%s\r\n", mq1.toString());
	printf("%s\r\n", mq2.toString());

	//quaternion ->euler
	Vector3 er1, er2;
	DrawMath::QuaternionToEuler(quaternion, er1);
	er2 = camera->GetTransform()->GetEulerAngle();

	printf("%s\r\n", er1.toString());
	printf("%s\r\n", er2.toString());

	Matrix4x4 mer1, mer2;
	DrawMath::EulerToMatrix(er1, mer1);
	DrawMath::EulerToMatrix(er2, mer2);

	printf("%s\r\n", mer1.toString());
	printf("%s\r\n", mer2.toString());

	//euler -> quaternion
	Vector4 re1, re2;
	DrawMath::EulerToQuaternion(camera->GetTransform()->GetEulerAngle(), re1);
	re2.CopyFrom(quaternion);

	printf("%s\r\n", re1.toString());
	printf("%s\r\n", re2.toString());

	Matrix4x4 mre1, mre2;
	DrawMath::QuaternionToMatrix(re1, mre1);
	DrawMath::QuaternionToMatrix(re2, mre2);

	printf("%s\r\n", mre1.toString());
	printf("%s\r\n", mre2.toString());

	getchar();
}