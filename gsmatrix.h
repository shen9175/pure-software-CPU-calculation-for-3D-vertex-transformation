#ifndef GSMATRIX_H
#define GSMATRIX_H
#include "matrix.h"
#include "gsvector.h"
class GSMATRIX;
typedef const GSMATRIX& RGSMATRIX;
class GSMATRIX : public GeneralSlowMatrix<float>
{

	public:
	GSMATRIX():GeneralSlowMatrix<float>(4,4){}
	GSMATRIX(RGSVECTOR R0,RGSVECTOR R1,RGSVECTOR R2,RGSVECTOR R3);
	GSMATRIX(const float m00,const float m01,const float m02,const float m03,
			 const float m10,const float m11,const float m12,const float m13,
			 const float m20,const float m21,const float m22,const float m23,
			 const float m30,const float m31,const float m32,const float m33);
	GSMATRIX(const float *pArray):GeneralSlowMatrix<float>(4,4,pArray,16){}
	~GSMATRIX(){}
	GSMATRIX GSMATRIXSet(const float m00,const float m01,const float m02,const float m03,
			 const float m10,const float m11,const float m12,const float m13,
			 const float m20,const float m21,const float m22,const float m23,
			 const float m30,const float m31,const float m32,const float m33);
	GSMATRIX(const GeneralSlowMatrix<float> & M);

	bool GSMatrixIsIdentity(){return GeneralSlowMatrixIsIdentity(*this);}

	private:

		
};
inline GSMATRIX GSMatrixIdentity(){return GSMATRIX(GeneralSlowMatrixIdentity<float>(4,4));}
inline bool GSMatrixIsIdentity(RGSMATRIX M){return GeneralSlowMatrixIsIdentity(M);}
inline GSMATRIX GSMatrixMultiply(RGSMATRIX A, RGSMATRIX B){return A*B;}
inline GSMATRIX GSMatrixTranspose(RGSMATRIX M){return M.Transpose();}
inline GSVECTOR GSMatrixDeterminant(RGSMATRIX M){float det=M.Determinant();return GSVECTOR(det,det,det,det);}
inline GSMATRIX GSMatrixInverse(GSVECTOR* pDeterminant, RGSMATRIX M){return 1.0/pDeterminant->getX()*M.Adjoint();}

#endif

