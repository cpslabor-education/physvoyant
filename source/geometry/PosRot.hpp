#ifndef POSROT
#define POSROT

#include "../defines.hpp"
#include INCL_GLM
#define GLM_FORCE_QUAT_DATA_WXYZ
#include INCL_QUATERNION

class PosRot
{
	QUATERNION rotation;
public:
	PosRot(realStandard_t number = 0) : vector(VECTOR3(number)), rotation(glm::identity<QUATERNION>())
	{

	}
	PosRot(VECTOR3 vector, QUATERNION rotation = glm::identity<QUATERNION>()) : vector(vector), rotation(glm::normalize(rotation))
	{

	}
	VECTOR3 vector;

	QUATERNION GetRotation() const
	{
		return rotation;
	}

	void SetRotation(const QUATERNION& value)
	{
		rotation = glm::normalize(value);
	}
};


#endif
