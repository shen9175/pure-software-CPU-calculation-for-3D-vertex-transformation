#ifndef GSVECTOR_H
#define GSVECTOR_H

#include "matrix.h"
#define GS_PI 		3.141592654f
#define GS_2PI 		6.283185307f
#define GS_1DIVPI 	0.318309886f
#define GS_1DIV2PI 	0.159154943f
#define GS_PIDIV2 	1.570796327f
#define GS_PIDIV4	0.785398163f
#define GSMin(a,b)	(((a)<(b))?(a):(b))
#define GSMax(a,b)	(((a)>(b))?(a):(b))

typedef struct _GSFLOAT2
{
	float x;
	float y;
}GSFLOAT2;

typedef struct _GSFLOAT3
{
	float x;
	float y;
	float z;
}GSFLOAT3;

typedef struct _GSFLOAT4
{
	float x;
	float y;
	float z;
	float w;
}GSFLOAT4;


inline float GSConvertToRadians(float fDegrees)
{
	return fDegrees*(GS_PI/180.0f);
}

inline float GSConvertToDegrees(float fRadians)
{
	return fRadians*(180.0f/GS_PI);
}

class GSVECTOR;
typedef const GSVECTOR& RGSVECTOR;

class GSVECTOR
{

	public:
	GSVECTOR();
	GSVECTOR(const GSFLOAT2 *pSource);
	GSVECTOR(const GSFLOAT3 *pSource);
	GSVECTOR(const GSFLOAT4 *pSource);
	GSVECTOR(const float m1,const float m2,const float m3,const float m4){gsm = new GeneralSlowMatrix<float> (1,4,{m1,m2,m3,m4});}
	GSVECTOR(RGSVECTOR);
	GSVECTOR(const GeneralSlowMatrix<float>& M);
	GSVECTOR& operator=(RGSVECTOR);
	GSVECTOR operator+(RGSVECTOR);
	GSVECTOR operator-(RGSVECTOR);
	~GSVECTOR();
	float getX() const {return (*(this->gsm))(0,0);}
	float getY() const {return (*(this->gsm))(0,1);}
	float getZ() const {return (*(this->gsm))(0,2);}
	float getW() const {return (*(this->gsm))(0,3);}
	GeneralSlowMatrix<float>* getGSM() const{return gsm;}
	private:
	GeneralSlowMatrix<float>* gsm;
		
};

void GSStoreFloat2(GSFLOAT2 *pDestination, RGSVECTOR V);
void GSStoreFloat3(GSFLOAT3 *pDestination, RGSVECTOR V);
void GSStoreFloat4(GSFLOAT4 *pDestination, RGSVECTOR V);
float GSVectorGetX(RGSVECTOR V);
float GSVectorGetY(RGSVECTOR V);
float GSVectorGetZ(RGSVECTOR V);
float GSVectorGetW(RGSVECTOR V);
GSVECTOR GSVectorSetX(RGSVECTOR V, float x);
GSVECTOR GSVectorSetY(RGSVECTOR V, float y);
GSVECTOR GSVectorSetZ(RGSVECTOR V, float z);
GSVECTOR GSVectorSetW(RGSVECTOR V, float w);

GSVECTOR& operator+=(GSVECTOR& V1, RGSVECTOR V2);
GSVECTOR& operator-=(GSVECTOR& V1, RGSVECTOR V2);
GSVECTOR& operator*=(GSVECTOR& V1, RGSVECTOR V2);
GSVECTOR& operator/=(GSVECTOR& V1, RGSVECTOR V2);
GSVECTOR& operator*=(GSVECTOR& V, float s);
GSVECTOR& operator/=(GSVECTOR& V, float s);

GSVECTOR operator+(RGSVECTOR V1, RGSVECTOR V2);
GSVECTOR operator-(RGSVECTOR V1, RGSVECTOR V2);
GSVECTOR operator*(RGSVECTOR V1, RGSVECTOR V2);
GSVECTOR operator/(RGSVECTOR V1, RGSVECTOR V2);
GSVECTOR operator*(RGSVECTOR V, float s);
GSVECTOR operator*(float, RGSVECTOR V);
GSVECTOR operator/(RGSVECTOR V, float s);
std::ostream& operator<<(std::ostream& os, RGSVECTOR v);

GSVECTOR GSVectorZero();
GSVECTOR GSVectorSplatOne();
GSVECTOR GSVectorSet(float x, float y, float z, float w);
GSVECTOR GSVectorReplicate(float s);
GSVECTOR GSVectorSplatX(RGSVECTOR V);
GSVECTOR GSVectorSplatY(RGSVECTOR V);
GSVECTOR GSVectorSplatZ(RGSVECTOR V);
GSVECTOR GSVectorSplatW(RGSVECTOR V);

GSVECTOR GSVector3Length(RGSVECTOR V);//input v Returns ||v||
GSVECTOR GSVector3LengthSq(RGSVECTOR V);//input v returns ||v||^2
GSVECTOR GSVector3Dot(RGSVECTOR V1, RGSVECTOR V2);
GSVECTOR GSVector3Cross(RGSVECTOR V1, RGSVECTOR V2);
GSVECTOR GSVector3Normalize(RGSVECTOR V);
GSVECTOR GSVector3Orthogonal(RGSVECTOR V);
GSVECTOR GSVector3AngleBetweenVectors(RGSVECTOR V1, RGSVECTOR V2);
void GSVector3ComponentsFromNormal(GSVECTOR pParallel, GSVECTOR pPerpendicular, RGSVECTOR V, RGSVECTOR Normal);
bool GSVector3Equal(RGSVECTOR V1, RGSVECTOR V2);
bool GSVector3NotEqual(RGSVECTOR V1, RGSVECTOR V2);


GSVECTOR GSVectorMax(RGSVECTOR V1,RGSVECTOR V2);


GSVECTOR GSVectorAbs(RGSVECTOR V);


#endif















