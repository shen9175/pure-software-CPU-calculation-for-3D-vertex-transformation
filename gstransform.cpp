#include "gstransform.h"

//Scaling factors
GSMATRIX GSMatrixScaling(const float& ScaleX, const float& ScaleY, const float& ScaleZ)
{
	return GSMATRIX(ScaleX,	    0,     0,     0,
					   0,	 ScaleY,   0,     0,
					   0,       0,   ScaleZ,  0,
					   0,	    0,     0,      1);
}


//Scaling factors (S_x, S_y, S_z)
GSMATRIX GSMatrixScalingFromVector(RGSVECTOR Scale)
{
	return GSMATRIX(	Scale.getX(),			0,				0,     			0,
							0,	 			Scale.getY(),	    0,     			0,
							0,       			0,			Scale.getZ(), 		0,
					   		0,	    			0,        		0,      		1);
}


//Construct a x-axis rotation matrix R_x Clockwise angle theta to rotate
GSMATRIX GSMatrixRotationX(const float& Angle)
{
	return GSMATRIX(	1,					0,								0,					0,
						0,	cos(GSConvertToRadians(Angle)), sin(GSConvertToRadians(Angle)),		0,
						0,	-sin(GSConvertToRadians(Angle)),cos(GSConvertToRadians(Angle)),		0,
						0,					0,								0,					1);
}



//Construct a y-axis rotation matrix R_y Clockwise angle theta to rotate
GSMATRIX GSMatrixRotationY(const float& Angle)
{
	return GSMATRIX(	cos(GSConvertToRadians(Angle)),					0,				-sin(GSConvertToRadians(Angle)),					0,
									0,									1,								0,									0,
						sin(GSConvertToRadians(Angle)),					0,				cos(GSConvertToRadians(Angle)),						0,
									0,									0,								0,									1);

}




//Construct a z-axis rotation matrix R_z Clockwise angle theta to rotate
GSMATRIX GSMatrixRotationZ(const float& Angle)
{
	return GSMATRIX(	cos(GSConvertToRadians(Angle)),		sin(GSConvertToRadians(Angle)),				0,					0,
						-sin(GSConvertToRadians(Angle)),	cos(GSConvertToRadians(Angle)),				0,					0,
									0,									0,								1,					0,
									0,									0,								0,					1);
}



//Construct an arbitrary axis rotation matrix R_n Clockwise angle theta to rotate
GSMATRIX GSMatrixRotationAxis(RGSVECTOR Axis, const float& Angle)
{
	return GSMATRIX	(
						cos(GSConvertToRadians(Angle))+(1-cos(GSConvertToRadians(Angle)))*pow(Axis.getX(),2),	
						(1-cos(GSConvertToRadians(Angle)))*Axis.getX()*Axis.getY()+sin(GSConvertToRadians(Angle))*Axis.getZ(),
						(1-cos(GSConvertToRadians(Angle)))*Axis.getX()*Axis.getZ()-sin(GSConvertToRadians(Angle))*Axis.getY(),
						0,
						(1-cos(GSConvertToRadians(Angle)))*Axis.getX()*Axis.getY()-sin(GSConvertToRadians(Angle))*Axis.getZ(),
						cos(GSConvertToRadians(Angle))+(1-cos(GSConvertToRadians(Angle)))*pow(Axis.getY(),2),
						(1-cos(GSConvertToRadians(Angle)))*Axis.getY()*Axis.getZ()+sin(GSConvertToRadians(Angle))*Axis.getX(),
						0,
						(1-cos(GSConvertToRadians(Angle)))*Axis.getX()*Axis.getZ()+sin(GSConvertToRadians(Angle))*Axis.getY(),
						(1-cos(GSConvertToRadians(Angle)))*Axis.getY()*Axis.getZ()-sin(GSConvertToRadians(Angle))*Axis.getX(),
						cos(GSConvertToRadians(Angle))+(1-cos(GSConvertToRadians(Angle)))*pow(Axis.getZ(),2),
						0,
						0,									0,								0,					1
					);
}

//Construct a translation matrix
GSMATRIX GSMatrixTranslation(const float& OffsetX,const float& OffsetY,const float& OffsetZ)
{
	return GSMATRIX(		1,				0,				0,			0,
							0,				1,				0,			0,
							0,				0,				1,			0,
						OffsetX,		OffsetY,		OffsetZ,		1);
}
//Construct a translation matrix from componenets in a vector: Transplation factor(t_x, t_y, t_z)
GSMATRIX GSMatrixTranslationFromVector(RGSVECTOR Offset)
{
	return GSMATRIX(		1,					0,					0,				0,
							0,					1,					0,				0,
							0,					0,					1,				0,
						Offset.getX(),		Offset.getY(),		Offset.getZ(),		1);
}
//Computes the vector-matrix product vM
GSVECTOR GSVector3Transform(RGSVECTOR V, RGSMATRIX M)
{
	return GSVECTOR(*(V.getGSM())*M);
}
//Computes the vector-matrix product vM where V_w=1 for transforming points:
GSVECTOR GSVector3TransformCoord(RGSVECTOR V, RGSMATRIX M)
{
	GSVECTOR vec=GSVectorSetW(V,1);
	return GSVECTOR(*(vec.getGSM())*M);
}
//Computes the vector-matrix product vM where V_w=0 for transforming vectors:
GSVECTOR GSVector3TransformNormal(RGSVECTOR V, RGSMATRIX M)
{
	GSVECTOR vec=GSVectorSetW(V,0);
	return GSVECTOR(*(vec.getGSM())*M);
}
//Outputs resulting view matrix V, Input camera position Q(EyePosition), target point T(FocusPosition), world up vector j(UpDirection)
GSMATRIX GSMatrixLookAtLH(RGSVECTOR EyePosition, RGSVECTOR FocusPosition, RGSVECTOR UpDirection)
{
	GSVECTOR w=(FocusPosition-EyePosition)/GSVector3Length(FocusPosition-EyePosition);
	GSVECTOR u=GSVector3Cross(UpDirection,w)/GSVector3Length(GSVector3Cross(UpDirection,w));
	GSVECTOR v=GSVector3Cross(w,u);
//esay way(less computation->no matrix inverse needed):
/* 	GSMATRIX View	(
					u.getX(),v.getX(),w.getX(),0,
					u.getY(),v.getY(),w.getY(),0,
					u.getZ(),v.getZ(),w.getZ(),0,
					-1*GSVector3Dot(EyePosition,u).getX(),-1*GSVector3Dot(EyePosition,v).getX(),-1*GSVector3Dot(EyePosition,w).getX(),1
					);
*/

//complex way(more computation->matrix inverse needed):
	w=GSVectorSetW(w,0);
	u=GSVectorSetW(u,0);
	v=GSVectorSetW(v,0);
	GSVECTOR Q=GSVectorSetW(EyePosition,1);
	GSMATRIX View(u,v,w,Q);
	View=View.Inverse();
	return View;
}
//Output: return projection matrix(NDC) Input:FovAngleY->Vertical field of view angle in radians; AspectRatio->display window's width/height; NearZ->distance to near plane; FarZ->distance to far plane;
GSMATRIX GSMatrixPerspectiveFovLH(const float& FovAngleY, const float& AspectRatio, const float& NearZ, const float& FarZ)
{
	GSMATRIX Projection	(
						1/(AspectRatio*tan(FovAngleY/2)),				0,				0,						0,
										0,					1/tan(FovAngleY/2),			0,						0,
										0,								0,		FarZ/(FarZ-NearZ),				1,
										0,								0,		-NearZ*FarZ/(FarZ-NearZ),		0
						);
	return Projection;
}


/*
int main()
{
	GSMATRIX a=GSMatrixLookAtLH(GSVECTOR(-20,35,-50,0),GSVECTOR(10,0,30,0),GSVECTOR(0,1,0,0));
	std::cout<<a<<std::endl;
	GSMATRIX b=GSMatrixPerspectiveFovLH(GSConvertToRadians(45),4/3.0,1,100);
	std::cout<<b<<std::endl;
}*/
