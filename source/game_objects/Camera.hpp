#ifndef CAMERA
#define CAMERA

class Camera;

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_GEOMETRY
#include INCL_GLFW
#include "../scene_components/SceneComponentBase.hpp"
#include <vector>
#include <list>

class Camera : public SceneComponentBase
{
	GLuint program;
public:
	GLuint vertexShader;
	GLuint fragmentShader;
	Transform transform;
	std::list<IRenderable*> renderCollector;
	const static VECTOR3 forward;

	Camera();
	~Camera();

	GLuint GetProgram() { return program; };

	void InitComponents();
	//void RebuildVertexBuffer(uintStandard_t newSize);

	GLuint CompileShader(GLuint type, const char* source);
	void DeleteShader(GLuint& shader);

	void AttachShader(GLuint shader);
	void LinkProgram();

	// Inherited via ISceneComponent
	void* Execute(Scene* caller, void* params = nullptr) override;
	ISceneComponent* Clone(void* params = nullptr) const override;
};


#endif
