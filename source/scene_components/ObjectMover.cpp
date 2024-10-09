#include "ObjectMover.hpp"
#include <vector>

ObjectMover::ObjectMover() : ID(0), solverType((MovementSolver::Solvers)0), leapfrogSteps(0)
{
}

ObjectMover::ObjectMover(const componentID_t& ID, const MovementSolver::Solvers& solverType, const uintStandard_t& leapfrogSteps)
	: ID(ID), solverType(solverType), leapfrogSteps(leapfrogSteps)
{
}

void* ObjectMover::Execute(Scene* caller, void* params)
{
	std::vector<GameObject*>& helper = (caller->gameObjects);
	realStandard_t deltaTime = TO_SECOND(Engine::GetInstance()->clock.ScaledPhysicsDeltaTime());
	for (size_t i = 0; i < helper.size(); i++)
	{
		Transform previous = helper[i]->transform;
		switch (solverType)
		{
			case MovementSolver::Solvers::EpxlicitEuler:
				MovementSolver::ExplicitEulerSolver(&(helper[i]->transform), deltaTime);
				break;
			case MovementSolver::Solvers::SemiImplicitEuler:
				MovementSolver::SemiImplicitEulerSolver(&(helper[i]->transform), deltaTime);
				break;
			case MovementSolver::Solvers::VerletIntegration:
				Engine::WriteInfo("VerletIntegration not implemented");
				MovementSolver::VerletIntegrationSolver(&(helper[i]->transform), deltaTime);
				break;
			case MovementSolver::Solvers::Leapfrog:
				MovementSolver::LeapfrogSolver(&(helper[i]->transform), deltaTime, leapfrogSteps);
				break;
			case MovementSolver::Solvers::RungeKutta4:
				MovementSolver::RungeKutta4(&(helper[i]->transform), deltaTime);
				break;
			case MovementSolver::Solvers::EndOfSolvers:
			default:
				Engine::WriteInfo("No solver selected at" __FILE__ + __LINE__);
				break;
		}
		if (caller->objectTree != nullptr && (!caller->objectTree->WithinSameSquare(helper[i]->transform.position.vector, previous.position.vector)))
		{
			caller->objectTree->MoveItem(caller->objectTree->Find(previous.position.vector), helper[i], caller->objectTree->Find(helper[i]->transform.position.vector));
		}
		helper[i]->transform.acceleration.vector = VECTOR3(0);
	}
	return nullptr;
}

ISceneComponent* ObjectMover::Clone(void* params) const
{
	return new ObjectMover(*this);
}

componentID_t ObjectMover::GetID()
{
	return ID;
}
