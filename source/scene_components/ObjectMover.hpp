#ifndef OBJECTS_MOVER
#define OBJECTS_MOVER

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_MATH
#include "SceneComponentBase.hpp"

class ObjectMover : public SceneComponentBase
{
public:
	MovementSolver::Solvers solverType;
	uintStandard_t leapfrogSteps;

	ObjectMover(const componentID_t ID = 0, const MovementSolver::Solvers solverType = static_cast<MovementSolver::Solvers>(0), const uintStandard_t leapfrogSteps = 0);
	~ObjectMover() = default;

	// Inherited via ISceneComponent
	void* Execute(Scene* caller, void* params) override;
	ISceneComponent* Clone(void* params) const override;
};


#endif
