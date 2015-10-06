#include "gsmatrix.h"
GSMATRIX::GSMATRIX(RGSVECTOR R0,RGSVECTOR R1,RGSVECTOR R2,RGSVECTOR R3):GeneralSlowMatrix<float>(4,4,{R0.getX(),R0.getY(),R0.getZ(),R0.getW(),
																									  R1.getX(),R1.getY(),R1.getZ(),R1.getW(),
																									  R2.getX(),R2.getY(),R2.getZ(),R2.getW(),
																									  R3.getX(),R3.getY(),R3.getZ(),R3.getW()}){}


/* this is a correct constructor except above
GSMATRIX::GSMATRIX(RGSVECTOR R0,RGSVECTOR R1,RGSVECTOR R2,RGSVECTOR R3):GeneralSlowMatrix<float>(4,4)
{

	m[0][0]=R0.getX();
	m[0][1]=R0.getY();
	m[0][2]=R0.getZ();
	m[0][3]=R0.getW();
	m[1][0]=R1.getX();
	m[1][1]=R1.getY();
	m[1][2]=R1.getZ();
	m[1][3]=R1.getW();
	m[2][0]=R2.getX();
	m[2][1]=R2.getY();
	m[2][2]=R2.getZ();
	m[2][3]=R2.getW();
	m[3][0]=R3.getX();
	m[3][1]=R3.getY();
	m[3][2]=R3.getZ();
	m[3][3]=R3.getW();

}*/

/*this is a wrong for construtor
GSMATRIX::GSMATRIX(RGSVECTOR R0,RGSVECTOR R1,RGSVECTOR R2,RGSVECTOR R3)
{

	float array[16];
	array[0]=R0.getX();
	array[1]=R0.getY();
	array[2]=R0.getZ();
	array[3]=R0.getW();
	array[4]=R1.getX();
	array[5]=R1.getY();
	array[6]=R1.getZ();
	array[7]=R1.getW();
	array[8]=R2.getX();
	array[9]=R2.getY();
	array[10]=R2.getZ();
	array[11]=R2.getW();
	array[12]=R3.getX();
	array[13]=R3.getY();
	array[14]=R3.getZ();
	array[15]=R3.getW();
	this->GeneralSlowMatrix<float>(4,4,array,16);

}*/


GSMATRIX::GSMATRIX(const float m00,const float m01,const float m02,const float m03,
			 	   const float m10,const float m11,const float m12,const float m13,
				   const float m20,const float m21,const float m22,const float m23,
				   const float m30,const float m31,const float m32,const float m33):GeneralSlowMatrix<float>(4,4,{m00,m01,m02,m03,
																											 	  m10,m11,m12,m13,
																												  m20,m21,m22,m23,
																												  m30,m31,m32,m33}){}


/*this is a correct constructor except above
GSMATRIX::GSMATRIX(const float m00,const float m01,const float m02,const float m03,
			 	   const float m10,const float m11,const float m12,const float m13,
				   const float m20,const float m21,const float m22,const float m23,
				   const float m30,const float m31,const float m32,const float m33):GeneralSlowMatrix<float>(4,4)
{
	m[0][0]=m00;
	m[0][1]=m01;
	m[0][2]=m02;
	m[0][3]=m03;
	m[1][0]=m10;
	m[1][1]=m11;
	m[1][2]=m12;
	m[1][3]=m13;
	m[2][0]=m20;
	m[2][1]=m21;
	m[2][2]=m22;
	m[2][3]=m23;
	m[3][0]=m30;
	m[3][1]=m31;
	m[3][2]=m32;
	m[3][3]=m33;
}*/
/* this is a wrong for contructor
GSMATRIX::GSMATRIX(const float m00,const float m01,const float m02,const float m03,
			 	   const float m10,const float m11,const float m12,const float m13,
				   const float m20,const float m21,const float m22,const float m23,
				   const float m30,const float m31,const float m32,const float m33)
{

	float array[16];
	array[0]=m00;
	array[1]=m01;
	array[2]=m02;
	array[3]=m03;
	array[4]=m10;
	array[5]=m11;
	array[6]=m12;
	array[7]=m13;
	array[8]=m20;
	array[9]=m21;
	array[10]=m22;
	array[11]=m23;
	array[12]=m30;
	array[13]=m31;
	array[14]=m32;
	array[15]=m33;
	this->GeneralSlowMatrix<float>(4,4,array,16);
}*/

GSMATRIX GSMATRIX::GSMATRIXSet(const float m00,const float m01,const float m02,const float m03,
			 const float m10,const float m11,const float m12,const float m13,
			 const float m20,const float m21,const float m22,const float m23,
			 const float m30,const float m31,const float m32,const float m33)
{
	m[0][0]=m00;
	m[0][1]=m01;
	m[0][2]=m02;
	m[0][3]=m03;
	m[1][0]=m10;
	m[1][1]=m11;
	m[1][2]=m12;
	m[1][3]=m13;
	m[2][0]=m20;
	m[2][1]=m21;
	m[2][2]=m22;
	m[2][3]=m23;
	m[3][0]=m30;
	m[3][1]=m31;
	m[3][2]=m32;
	m[3][3]=m33;
	
	return *this;
}

GSMATRIX::GSMATRIX(const GeneralSlowMatrix<float>&M):GeneralSlowMatrix<float>(4,4)//chop or pad GeneralSlowMatrix into 4x4 GSMatrix
{
	for(unsigned int i=0;i<4;++i)
	{
		for(unsigned int j=0;j<4;++j)
		{
			if(i<M.getRow()&&j<M.getCol())
				m[i][j]=M[i][j];
			else
				m[i][j]=0;
		}
	}
}




std::ostream& operator<<(std::ostream& os, RGSVECTOR v)
{
	GSFLOAT4 dest;
	GSStoreFloat4(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, RGSMATRIX m)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
			os << m(i, j) << "\t";
		os << std::endl;
	}
	return os;
}

/*

int main()
{


	GSMATRIX A(1.0f, 0.0f, 0.0f, 0.0f,
               0.0f, 2.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 4.0f, 0.0f,
			   1.0f, 2.0f, 3.0f, 1.0f);

	GSMATRIX B = GSMatrixIdentity();

	GSMATRIX C = A * B;

	GSMATRIX D = GSMatrixTranspose(A);

	GSVECTOR det = GSMatrixDeterminant(A);
	GSMATRIX E = GSMatrixInverse(&det, A);

	GSMATRIX F = A * E;
 
	std::cout << "A = "                    << std::endl << A << std::endl;

	std::cout << "B = "                    << std::endl << B << std::endl;
	std::cout << "C = A*B = "              << std::endl << C << std::endl;

	std::cout << "D = transpose(A) = "     << std::endl << D << std::endl;
	std::cout << "det = determinant(A) = " << det << std::endl << std::endl;
	std::cout << "E = inverse(A) = "       << std::endl << E << std::endl;
	std::cout << "F = A*E = "              << std::endl << F << std::endl;
 
	return 0;
}




*/





/*
int main()
{
	GSMATRIX a(1,0,0,0,
			   0,1,0,0,
			   0,0,1,0,
			   0,0,0,1);
	std::cout.setf(std::ios_base::boolalpha);
	std::cout<<GSMatrixIsIdentity(a)<<std::endl;
	std::cout<<a.GSMatrixIsIdentity()<<std::endl;
}*/
