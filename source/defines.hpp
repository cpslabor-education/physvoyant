#ifndef DEFINES
#define DEFINES

// 0: no debug
// 1: debug
// 2: memory allocation
#define DEBUG_LEVEL 0

#define ARCHITECTURE 64

#if DEBUG_LEVEL >= 2
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#define MAX_WINDOWS 1

#define INCL_CAMERA "../game_objects/Camera.hpp"
#define INCL_COMPONENTS "../components/include_components.hpp"
#define INCL_DATA_STRUCTURES "../data_structures/include_data_structures.hpp"
#define INCL_ENGINE "../engine/Engine.hpp"
#define INCL_GAME_OBJECTS "../game_objects/include_objects.hpp"
#define INCL_GEOMETRY "../geometry/include_geometry.hpp"
#define INCL_INTERFACES "../interfaces/include_interfaces.hpp"
#define INCL_RENDERER "../renderer/Renderer.hpp"
#define INCL_SCENE "../scene/Scene.hpp"
#define INCL_GLFW <GLFW/glfw3.h>
#define INCL_GLM <glm/glm.hpp>
#define INCL_QUATERNION <glm/gtc/quaternion.hpp>
#define INCL_QUATERNION_EXTENSIONS <glm/gtx/quaternion.hpp>

#define GLM_PRECISION glm::packed_highp
#define VECTOR3 glm::vec<3, double, glm::packed_highp>
#define QUATERNION glm::qua<double, GLM_PRECISION>
#define TRANSFORM_MATRIX glm::tmat4x4<double>


// Null check
#define NULL_CHECK_FUNCTION_CALL(ptr, func, ...) \
	do\
	{\
		if ((ptr) != NULL) \
		{ \
			func(__VA_ARGS__); \
		} \
	} while(0)

#define NULL_CHECK(ptr) \
	do\
	{\
		if ((ptr) == 0)\
		{\
			throw std::bad_alloc();\
		}\
	} while (0)


// Scientific notations

#define SNE0 (1.0e0)
#define SNE1 (1.0e-1)
#define SNE2 (1.0e-2)
#define SNE3 (1.0e-3)
#define SNE4 (1.0e-4)
#define SNE5 (1.0e-5)
#define SNE6 (1.0e-6)
#define SNE7 (1.0e-7)
#define SNE8 (1.0e-8)
#define SNE9 (1.0e-9)
#define SNE10 (1.0e-10)
#define SNE11 (1.0e-11)
#define SNE12 (1.0e-12)
#define SNE13 (1.0e-13)
#define SNE14 (1.0e-14)
#define SNE15 (1.0e-15)
#define SNE16 (1.0e-16)
#define SNE17 (1.0e-17)
#define SNE18 (1.0e-18)
#define SNE19 (1.0e-19)
#define SNE20 (1.0e-20)
#define SNE21 (1.0e-21)
#define SNE22 (1.0e-22)
#define SNE23 (1.0e-23)
#define SNE24 (1.0e-24)
#define SNE25 (1.0e-25)
#define SNE26 (1.0e-26)
#define SNE27 (1.0e-27)
#define SNE28 (1.0e-28)
#define SNE29 (1.0e-29)
#define SNE30 (1.0e-30)
#define SNE31 (1.0e-31)
#define SNE32 (1.0e-32)
#define SNE33 (1.0e-33)
#define SNE34 (1.0e-34)
#define SNE35 (1.0e-35)
#define SNE36 (1.0e-36)
#define SNE37 (1.0e-37)
#define SNE38 (1.0e-38)
#define SNE39 (1.0e-39)
#define SNE40 (1.0e-40)
#define SNE41 (1.0e-41)
#define SNE42 (1.0e-42)
#define SNE43 (1.0e-43)
#define SNE44 (1.0e-44)
#define SNE45 (1.0e-45)
#define SNE46 (1.0e-46)
#define SNE47 (1.0e-47)
#define SNE48 (1.0e-48)
#define SNE49 (1.0e-49)
#define SNE50 (1.0e-50)
#define SNE51 (1.0e-51)
#define SNE52 (1.0e-52)
#define SNE53 (1.0e-53)
#define SNE54 (1.0e-54)
#define SNE55 (1.0e-55)
#define SNE56 (1.0e-56)
#define SNE57 (1.0e-57)
#define SNE58 (1.0e-58)
#define SNE59 (1.0e-59)
#define SNE60 (1.0e-60)
#define SNE61 (1.0e-61)
#define SNE62 (1.0e-62)
#define SNE63 (1.0e-63)
#define SNE64 (1.0e-64)


#endif // !DEFINES
