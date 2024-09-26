#ifndef PHYSICS_CALCULATOR
#define PHYSICS_CALCULATOR

#include "../defines.hpp"
#include INCL_INTERFACES
#include INCL_MATH

class ObjectMover : public ISceneComponent
{
public:
	componentID_t ID;
	MovementSolver::Solvers solverType;
	uintStandard_t leapfrogSteps;

	ObjectMover();
	ObjectMover(const componentID_t& ID, const MovementSolver::Solvers& solverType, const uintStandard_t& leapfrogSteps);
	~ObjectMover() = default;


	// Inherited via ISceneComponent
	void* Execute(Scene* caller, void* params) override;

	ISceneComponent* Clone(void* params) const override;

	componentID_t GetID() override;
};


#endif
