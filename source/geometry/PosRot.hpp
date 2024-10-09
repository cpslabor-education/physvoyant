#ifndef POSROT
#define POSROT

#include "../defines.hpp"
#include INCL_GLM
#define GLM_FORCE_QUAT_DATA_WXYZ
#include INCL_QUATERNION

class PosRot
{
public:
	PosRot() : vector(VECTOR3(0)), rotation(glm::identity<QUATERNION>())
	{

	}
	PosRot(realStandard_t number) : vector(VECTOR3(number)), rotation(glm::identity<QUATERNION>())
	{

	}
	PosRot(VECTOR3 vector, QUATERNION rotation) : vector(vector), rotation(rotation)
	{

	}
	VECTOR3 vector;
	QUATERNION rotation;
};


#endif
