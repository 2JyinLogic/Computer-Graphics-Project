#pragma once


#include "Vector3.h"
#include "global.h"

class Camel
{
public:
	Camel();
	void init(Vector3 pos, float angle);

	Vector3 pos();//λ��
	Vector3 lookAt();//����

	~Camel();

public:
	float x;
	float y;
	float z;
	float angle;
};