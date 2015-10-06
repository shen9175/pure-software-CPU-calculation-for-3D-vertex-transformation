#ifndef GSTRANSFORM_H
#define GSTRANSFORM_H
#include "gsmatrix.h"

GSMATRIX GSMatrixScaling(const float& ScaleX, const float& ScaleY, const float& ScaleZ);//Scaling factors
GSMATRIX GSMatrixScalingFromVector(RGSVECTOR Scale);//Scaling factors (S_x, S_y, S_z)
GSMATRIX GSMatrixRotationX(const float& Angle);//Construct a x-axis rotation matrix R_x Clockwise angle theta to rotate
GSMATRIX GSMatrixRotationY(const float& Angle);//Construct a y-axis rotation matrix R_y Clockwise angle theta to rotate
GSMATRIX GSMatrixRotationZ(const float& Angle);//Construct a z-axis rotation matrix R_z Clockwise angle theta to rotate
GSMATRIX GSMatrixRotationAxis(RGSVECTOR Axis, const float& Angle);//Construct an arbitrary axis rotation matrix R_n Clockwise angle theta to rotate
GSMATRIX GSMatrixTranslation(const float& OffsetX,const float& OffsetY,const float& OffsetZ);//Construct a translation matrix
GSMATRIX GSMatrixTranslationFromVector(RGSVECTOR Offset);//Construct a translation matrix from componenets in a vector: Transplation factor(t_x, t_y, t_z)
GSVECTOR GSVector3Transform(RGSVECTOR V, RGSMATRIX M);//Computes the vector-matrix product vM
GSVECTOR GSVector3TransformCoord(RGSVECTOR V, RGSMATRIX M);//Computes the vector-matrix product vM where V_w=1 for transforming points:
GSVECTOR GSVector3TransformNormal(RGSVECTOR V, RGSMATRIX M);//Computes the vector-matrix product vM where V_w=0 for transforming vectors:
GSMATRIX GSMatrixLookAtLH(RGSVECTOR EyePosition, RGSVECTOR FocusPosition, RGSVECTOR UpDirection);//Outputs resulting view matrix V, Input camera position Q, target point T, world up vector j
GSMATRIX GSMatrixPerspectiveFovLH(const float& FovAngleY, const float& AspectRatio, const float& NearZ, const float& FarZ);//return projection matrix
#endif




