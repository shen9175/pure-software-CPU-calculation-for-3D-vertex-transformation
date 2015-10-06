#include "gsvector.h"

GSVECTOR::GSVECTOR()
{
	gsm = new GeneralSlowMatrix<float> (1,4);
}
GSVECTOR::GSVECTOR(const GSFLOAT2 *pSource)
{
	float array[4];

	array[0]=pSource->x;
	array[1]=pSource->y;
	array[2]=0;
	array[3]=0;

	gsm = new GeneralSlowMatrix<float> (1,4,array,sizeof(array)/sizeof(float));
}
GSVECTOR::GSVECTOR(const GSFLOAT3 *pSource)
{
	float array[4];

	array[0]=pSource->x;
	array[1]=pSource->y;
	array[2]=pSource->z;
	array[3]=0;

	gsm = new GeneralSlowMatrix<float> (1,4,array,sizeof(array)/sizeof(float));
}
GSVECTOR::GSVECTOR(const GSFLOAT4 *pSource)
{
	float array[4];

	array[0]=pSource->x;
	array[1]=pSource->y;
	array[2]=pSource->z;
	array[3]=pSource->w;

	gsm = new GeneralSlowMatrix<float> (1,4,array,sizeof(array)/sizeof(float));
}
GSVECTOR::~GSVECTOR()
{
	delete gsm;
}


GSVECTOR::GSVECTOR(RGSVECTOR V)
{
	gsm = new GeneralSlowMatrix<float> (1,4);
	*gsm=(*V.getGSM());
}


GSVECTOR::GSVECTOR(const GeneralSlowMatrix<float>& M)
{
	gsm = new GeneralSlowMatrix<float> (1,4);
	for(unsigned int j=0;j<4;++j)
	{
		if(j<M.getCol())
			(*gsm)(0,j)=M(0,j);
		else
			(*gsm)(0,j)=0;
	}
}

GSVECTOR& GSVECTOR::operator=(RGSVECTOR V)
{
	delete gsm;//relese memory on previous space
	gsm = new GeneralSlowMatrix<float> (1,4);
	*gsm=(*V.getGSM());
}
GSVECTOR GSVECTOR::operator+(RGSVECTOR V)
{
	GeneralSlowMatrix<float> temp=(*(this->gsm))+(*(V.getGSM()));

	GSFLOAT4 input;
	input.x=temp(0,0);
	input.y=temp(0,1);
	input.z=temp(0,2);
	input.w=temp(0,3);	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVECTOR::operator-(RGSVECTOR V)
{
	GeneralSlowMatrix<float> temp=(*(this->gsm))-(*(V.getGSM()));//turn vector to gsmatrix, use matrix operator+-*/

	GSFLOAT4 input;
	input.x=temp(0,0);
	input.y=temp(0,1);
	input.z=temp(0,2);
	input.w=temp(0,3);	
	GSVECTOR v(&input);
	return v;
}

void GSStoreFloat2(GSFLOAT2 *pDestination, RGSVECTOR V)
{
	(*pDestination).x=(*(V.getGSM()))(0,0);
	(*pDestination).y=(*(V.getGSM()))(0,1);

}
void GSStoreFloat3(GSFLOAT3 *pDestination, RGSVECTOR V)
{
	(*pDestination).x=(*(V.getGSM()))(0,0);
	(*pDestination).y=(*(V.getGSM()))(0,1);
	(*pDestination).z=(*(V.getGSM()))(0,2);
}
void GSStoreFloat4(GSFLOAT4 *pDestination, RGSVECTOR V)
{
	(*pDestination).x=(*(V.getGSM()))(0,0);
	(*pDestination).y=(*(V.getGSM()))(0,1);
	(*pDestination).z=(*(V.getGSM()))(0,2);
	(*pDestination).w=(*(V.getGSM()))(0,3);
}
float GSVectorGetX(RGSVECTOR V)
{
	return (*(V.getGSM()))(0,0);
}
float GSVectorGetY(RGSVECTOR V)
{
	return (*(V.getGSM()))(0,1);
}
float GSVectorGetZ(RGSVECTOR V)
{
	return (*(V.getGSM()))(0,2);
}
float GSVectorGetW(RGSVECTOR V)
{
	return (*(V.getGSM()))(0,3);
}
GSVECTOR GSVectorSetX(RGSVECTOR V, float x)
{
	GSVECTOR RET=V;
	(*(RET.getGSM()))(0,0)=x;
	return RET;
	//(*(V.getGSM()))(0,0)=x;
}
GSVECTOR GSVectorSetY(RGSVECTOR V, float y)
{
	GSVECTOR RET=V;
	(*(RET.getGSM()))(0,1)=y;
	return RET;
	//(*(V.getGSM()))(0,1)=y;
}
GSVECTOR GSVectorSetZ(RGSVECTOR V, float z)
{
	GSVECTOR RET=V;
	(*(RET.getGSM()))(0,2)=z;
	return RET;
	//(*(V.getGSM()))(0,2)=z;
}
GSVECTOR GSVectorSetW(RGSVECTOR V, float w)
{
	GSVECTOR RET=V;
	(*(RET.getGSM()))(0,3)=w;
	return RET;
	//(*(V.getGSM()))(0,3)=w;
}

GSVECTOR& operator+=(GSVECTOR& V1, RGSVECTOR V2)
{
	(*(V1.getGSM()))(0,0)=(*(V1.getGSM()))(0,0)+(*(V2.getGSM()))(0,0);
	(*(V1.getGSM()))(0,1)=(*(V1.getGSM()))(0,1)+(*(V2.getGSM()))(0,1);
	(*(V1.getGSM()))(0,2)=(*(V1.getGSM()))(0,2)+(*(V2.getGSM()))(0,2);
	(*(V1.getGSM()))(0,3)=(*(V1.getGSM()))(0,3)+(*(V2.getGSM()))(0,3);
}
GSVECTOR& operator-=(GSVECTOR& V1, RGSVECTOR V2)
{
	(*(V1.getGSM()))(0,0)=(*(V1.getGSM()))(0,0)-(*(V2.getGSM()))(0,0);
	(*(V1.getGSM()))(0,1)=(*(V1.getGSM()))(0,1)-(*(V2.getGSM()))(0,1);
	(*(V1.getGSM()))(0,2)=(*(V1.getGSM()))(0,2)-(*(V2.getGSM()))(0,2);
	(*(V1.getGSM()))(0,3)=(*(V1.getGSM()))(0,3)-(*(V2.getGSM()))(0,3);
}
GSVECTOR& operator*=(GSVECTOR& V1, RGSVECTOR V2)
{
	(*(V1.getGSM()))(0,0)=(*(V1.getGSM()))(0,0)*(*(V2.getGSM()))(0,0);
	(*(V1.getGSM()))(0,1)=(*(V1.getGSM()))(0,1)*(*(V2.getGSM()))(0,1);
	(*(V1.getGSM()))(0,2)=(*(V1.getGSM()))(0,2)*(*(V2.getGSM()))(0,2);
	(*(V1.getGSM()))(0,3)=(*(V1.getGSM()))(0,3)*(*(V2.getGSM()))(0,3);
}
GSVECTOR& operator/=(GSVECTOR& V1, RGSVECTOR V2)
{
	(*(V1.getGSM()))(0,0)=(*(V1.getGSM()))(0,0)/(*(V2.getGSM()))(0,0);
	(*(V1.getGSM()))(0,1)=(*(V1.getGSM()))(0,1)/(*(V2.getGSM()))(0,1);
	(*(V1.getGSM()))(0,2)=(*(V1.getGSM()))(0,2)/(*(V2.getGSM()))(0,2);
	(*(V1.getGSM()))(0,3)=(*(V1.getGSM()))(0,3)/(*(V2.getGSM()))(0,3);
}
GSVECTOR& operator*=(GSVECTOR& V, float s)
{
	(*(V.getGSM()))(0,0)=(*(V.getGSM()))(0,0)*s;
	(*(V.getGSM()))(0,1)=(*(V.getGSM()))(0,1)*s;
	(*(V.getGSM()))(0,2)=(*(V.getGSM()))(0,2)*s;
	(*(V.getGSM()))(0,3)=(*(V.getGSM()))(0,3)*s;
}
GSVECTOR& operator/=(GSVECTOR& V, float s)
{
	if(s==0) throw std::runtime_error("divided by 0!");
	(*(V.getGSM()))(0,0)=(*(V.getGSM()))(0,0)/s;
	(*(V.getGSM()))(0,1)=(*(V.getGSM()))(0,1)/s;
	(*(V.getGSM()))(0,2)=(*(V.getGSM()))(0,2)/s;
	(*(V.getGSM()))(0,3)=(*(V.getGSM()))(0,3)/s;
}

GSVECTOR operator+(RGSVECTOR V1, RGSVECTOR V2)
{
	GeneralSlowMatrix<float> temp=(*(V1.getGSM()))+(*(V2.getGSM()));

	GSFLOAT4 input;
	input.x=temp(0,0);
	input.y=temp(0,1);
	input.z=temp(0,2);
	input.w=temp(0,3);	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR operator-(RGSVECTOR V1, RGSVECTOR V2)
{
	GeneralSlowMatrix<float> temp=(*(V1.getGSM()))-(*(V2.getGSM()));
	GSFLOAT4 input;
	input.x=temp(0,0);
	input.y=temp(0,1);
	input.z=temp(0,2);
	input.w=temp(0,3);	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR operator*(RGSVECTOR V1, RGSVECTOR V2)//element-wise multiplication
{
	GSFLOAT4 input;
	input.x=V1.getX()*V2.getX();
	input.y=V1.getY()*V2.getY();
	input.z=V1.getZ()*V2.getZ();
	input.w=V1.getW()*V2.getW();	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR operator/(RGSVECTOR V1, RGSVECTOR V2)
{
	GSFLOAT4 input;
	input.x=V1.getX()/V2.getX();
	input.y=V1.getY()/V2.getY();
	input.z=V1.getZ()/V2.getZ();
	input.w=V1.getW()/V2.getW();	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR operator*(RGSVECTOR V, float s)
{
	GSFLOAT4 input;
	input.x=V.getX()*s;
	input.y=V.getY()*s;
	input.z=V.getZ()*s;
	input.w=V.getW()*s;	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR operator*(float s, RGSVECTOR V)
{
	GSFLOAT4 input;
	input.x=s*V.getX();
	input.y=s*V.getY();
	input.z=s*V.getZ();
	input.w=s*V.getW();	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR operator/(RGSVECTOR V, float s)
{
	if(s==0) throw std::runtime_error("divided by 0!");
	GSFLOAT4 input;
	input.x=V.getX()/s;
	input.y=V.getY()/s;
	input.z=V.getZ()/s;
	input.w=V.getW()/s;	
	GSVECTOR v(&input);
	return v;
}


GSVECTOR GSVectorZero()
{
	GSFLOAT4 input;
	input.x=0;
	input.y=0;
	input.z=0;
	input.w=0;	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorSplatOne()
{
	GSFLOAT4 input;
	input.x=1;
	input.y=1;
	input.z=1;
	input.w=1;	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorSet(float x, float y, float z, float w)
{
	GSFLOAT4 input;
	input.x=x;
	input.y=y;
	input.z=z;
	input.w=w;	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorReplicate(float s)
{
	GSFLOAT4 input;
	input.x=s;
	input.y=s;
	input.z=s;
	input.w=s;	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorSplatX(RGSVECTOR V)
{
	GSFLOAT4 input;
	input.x=V.getX();
	input.y=V.getX();
	input.z=V.getX();
	input.w=V.getX();	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorSplatY(RGSVECTOR V)
{
	GSFLOAT4 input;
	input.x=V.getY();
	input.y=V.getY();
	input.z=V.getY();
	input.w=V.getY();	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorSplatZ(RGSVECTOR V)
{
	GSFLOAT4 input;
	input.x=V.getZ();
	input.y=V.getZ();
	input.z=V.getZ();
	input.w=V.getZ();	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorSplatW(RGSVECTOR V)
{
	GSFLOAT4 input;
	input.x=V.getW();
	input.y=V.getW();
	input.z=V.getW();
	input.w=V.getW();	
	GSVECTOR v(&input);
	return v;
}

GSVECTOR GSVector3Length(RGSVECTOR V)//input v Returns ||v||
{
	float length=sqrt((V.getX())*(V.getX())+(V.getY())*(V.getY())+(V.getZ())*(V.getZ()));
	GSFLOAT4 input;
	input.x=length;
	input.y=length;
	input.z=length;
	input.w=length;	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVector3LengthSq(RGSVECTOR V)//input v returns ||v||^2
{
	float length=(V.getX())*(V.getX())+(V.getY())*(V.getY())+(V.getZ())*(V.getZ());
	GSFLOAT4 input;
	input.x=length;
	input.y=length;
	input.z=length;
	input.w=length;	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVector3Dot(RGSVECTOR V1, RGSVECTOR V2)
{
	float dot=(V1.getX())*(V2.getX())+(V1.getY())*(V2.getY())+(V1.getZ())*(V2.getZ());
	GSFLOAT4 input;
	input.x=dot;
	input.y=dot;
	input.z=dot;	
	input.w=dot;
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVector3Cross(RGSVECTOR V1, RGSVECTOR V2)
{
	GSFLOAT3 input;
	input.x=(V1.getY())*(V2.getZ())-(V1.getZ())*(V2.getY());
	input.y=(V1.getZ())*(V2.getX())-(V1.getX())*(V2.getZ());
	input.z=(V1.getX())*(V2.getY())-(V1.getY())*(V2.getX());	
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVector3Normalize(RGSVECTOR V)
{
	return V/GSVector3Length(V);
/*
    // Compute the maximum absolute value component.
    GSVECTOR vAbs = GSVectorAbs(V);
    GSVECTOR max0 = GSVectorSplatX(vAbs);
    GSVECTOR max1 = GSVectorSplatY(vAbs);
    GSVECTOR max2 = GSVectorSplatZ(vAbs);
    max0 = GSVectorMax(max0, max1);
    max0 = GSVectorMax(max0, max2);

    // Divide by the maximum absolute component.
    GSVECTOR normalized = V/max0;

    // Set to zero when the original length is zero.
    XMVECTOR mask = XMVectorNotEqual(g_XMZero, max0);
    normalized = XMVectorAndInt(normalized, mask);

    XMVECTOR t0 = XMVector3LengthSq(normalized);
    XMVECTOR length = XMVectorSqrt(t0);

    // Divide by the length to normalize.
    normalized = XMVectorDivide(normalized, length);

    // Set to zero when the original length is zero or infinity.  In the
    // latter case, this is considered to be an unexpected condition.
    normalized = XMVectorAndInt(normalized, mask);
    return normalized;*/
}

GSVECTOR GSVector3Orthogonal(RGSVECTOR V)
{

//http://blog.selfshadow.com/2011/10/17/perp-vectors/
//Hughes-Möller method:

	GSVECTOR absV=GSVectorAbs(V);

	if(absV.getX() <= absV.getY() && absV.getX() <= absV.getZ())
	{
		GSFLOAT3 input;
		input.x=0;
		input.y=-V.getZ();
		input.z=V.getY();	
		GSVECTOR ret(&input);
		return ret;	
	}
	else if(absV.getY()<=absV.getX()&&absV.getY()<=absV.getZ())
	{
		GSFLOAT3 input;
		input.x=-V.getZ();
		input.y=0;
		input.z=V.getX();	
		GSVECTOR ret(&input);
		return ret;
	}
	else
	{
		GSFLOAT3 input;
		input.x=-V.getY();
		input.y=V.getX();
		input.z=0;
		GSVECTOR ret(&input);
		return ret;
	}


}
GSVECTOR GSVector3AngleBetweenVectors(RGSVECTOR V1, RGSVECTOR V2)
{
	float angleRadian=acos((GSVector3Dot(V1,V2)/GSVector3Length(V1)*GSVector3Length(V2)).getX());
	GSFLOAT4 input;
	input.x=angleRadian;
	input.y=angleRadian;
	input.z=angleRadian;
	input.w=angleRadian;	
	GSVECTOR v(&input);
	return v;
}
void GSVector3ComponentsFromNormal(GSVECTOR *pParallel, GSVECTOR *pPerpendicular, RGSVECTOR V, RGSVECTOR Normal)
{
	*pParallel=GSVector3Dot(V,Normal)/GSVector3LengthSq(Normal)*Normal;
	*pPerpendicular=V-*pParallel;
}
bool GSVector3Equal(RGSVECTOR V1, RGSVECTOR V2)
{
	if(*(V1.getGSM())==*(V2.getGSM()))
		return true;
	else
		return false;
}
bool GSVector3NotEqual(RGSVECTOR V1, RGSVECTOR V2)
{
	if(*(V1.getGSM())==*(V2.getGSM()))
		return false;
	else
		return true;
}

GSVECTOR GSVectorAbs(RGSVECTOR V)
{
	GSFLOAT4 input;
	input.x=abs(V.getX());
	input.y=abs(V.getY());
	input.z=abs(V.getZ());
	input.w=abs(V.getW());
	GSVECTOR v(&input);
	return v;
}
GSVECTOR GSVectorMax(RGSVECTOR V1,RGSVECTOR V2)
{
	GSFLOAT4 input;
	input.x=GSMax(V1.getX(),V2.getX());
	input.y=GSMax(V1.getY(),V2.getY());
	input.z=GSMax(V1.getY(),V2.getY());	
	input.w=GSMax(V1.getZ(),V2.getZ());
	GSVECTOR v(&input);
	return v;
}




/*
std::ostream& operator<<(std::ostream& os, RGSVECTOR v)
{
	GSFLOAT3 dest;
	GSStoreFloat3(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ")";
	return os;
}*/
/*
int main()
{
	std::cout.setf(std::ios_base::boolalpha);


	GSVECTOR P = GSVectorZero();
	GSVECTOR Q = GSVectorSplatOne();
	GSVECTOR U = GSVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	GSVECTOR V = GSVectorReplicate(-2.0f);
	GSVECTOR W = GSVectorSplatZ(u);

	std::cout << "P = " << P << std::endl;
	std::cout << "Q = " << Q << std::endl;
	std::cout << "U = " << U << std::endl;
	std::cout << "V = " << V << std::endl;
	std::cout << "W = " << W << std::endl;


	GSVECTOR n = GSVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	GSVECTOR u = GSVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	GSVECTOR v = GSVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	GSVECTOR w = GSVectorSet(0.707f, 0.707f, 0.0f, 0.0f);
	
	// Vector addition: GSVECTOR operator + 
	GSVECTOR a = u + v;

	// Vector subtraction: GSVECTOR operator - 
	GSVECTOR b = u - v;

	// Scalar multiplication: GSVECTOR operator * 
	GSVECTOR c = 10.0f*u;

	// ||u||
	GSVECTOR L = GSVector3Length(u);

	// d = u / ||u||
	GSVECTOR d = GSVector3Normalize(u);

	// s = u dot v
	GSVECTOR s = GSVector3Dot(u, v);

	// e = u x v
	GSVECTOR e = GSVector3Cross(u, v);

	// Find proj_n(w) and perp_n(w)
	GSVECTOR projW;
	GSVECTOR perpW;
	GSVector3ComponentsFromNormal(&projW, &perpW, w, n);

	// Does projW + perpW == w?
	bool equal = GSVector3Equal(projW + perpW, w) != 0;
	bool notEqual = GSVector3NotEqual(projW + perpW, w) != 0;

	// The angle between projW and perpW should be 90 degrees.
	GSVECTOR angleVec = GSVector3AngleBetweenVectors(projW, perpW);
	float angleRadians = GSVectorGetX(angleVec);
	float angleDegrees = GSConvertToDegrees(angleRadians);

	std::cout << "u                   = " << u << std::endl;
	std::cout << "v                   = " << v << std::endl;
	std::cout << "w                   = " << w << std::endl;
	std::cout << "n                   = " << n << std::endl;
	std::cout << "a = u + v           = " << a << std::endl;
	std::cout << "b = u - v           = " << b << std::endl;
	std::cout << "c = 10 * u          = " << c << std::endl;
	std::cout << "d = u / ||u||       = " << d << std::endl;
	std::cout << "e = u x v           = " << e << std::endl;
	std::cout << "L  = ||u||          = " << L << std::endl;
	std::cout << "s = u.v             = " << s << std::endl;
	std::cout << "projW               = " << projW << std::endl;
	std::cout << "perpW               = " << perpW << std::endl;
	std::cout << "projW + perpW == w  = " << equal << std::endl;
	std::cout << "projW + perpW != w  = " << notEqual << std::endl;
	std::cout << "angle               = " << angleDegrees << std::endl;



	return 0;
}


*/

