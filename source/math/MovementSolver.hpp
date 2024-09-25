#ifndef ODE_SOLVER
#define ODE_SOLVER

class MovementSolver;

#include "../defines.hpp"
#include INCL_ENGINE
#include INCL_GLM
#include INCL_GEOMETRY

class MovementSolver
{
public:

	enum class Solvers
	{
		EpxlicitEuler = 0,
		SemiImplicitEuler,
		VerletIntegration,
		Leapfrog,
		EndOfSolvers
	};

	static void ExplicitEulerSolver(Transform* transform, realStandard_t deltaTime)
	{
		transform->position += transform->velocity * deltaTime;
		transform->rotation += transform->angularVelocity * deltaTime;

		transform->velocity += transform->acceleration * deltaTime;
		transform->angularVelocity += transform->angularAcceleration * deltaTime;
	}

	static void SemiImplicitEulerSolver(Transform* transform, realStandard_t deltaTime)
	{
		transform->velocity += transform->acceleration * deltaTime;
		transform->angularVelocity += transform->angularAcceleration * deltaTime;

		transform->position += transform->velocity * deltaTime;
		transform->rotation += transform->angularVelocity * deltaTime;
	}

	// Accuracy
	static void VerletIntegrationSolver(Transform* transform, realStandard_t deltaTime = 0.0)
	{
		//Transform next = *current;

		//next.position = current->position + (current->position - previous->position) * (deltaTime / prevDeltaTime) + current->acceleration * (deltaTime * deltaTime);

		//// Update velocity based on new position
		//next.velocity = (next.position - previous->position) / (2.0 * deltaTime);

		//// Update rotation and angular velocity (simple linear interpolation, adjust if needed)
		//next.rotation = current->rotation + (current->rotation - previous->rotation) * deltaTime;
		//next.angularVelocity = (next.rotation - previous->rotation) / deltaTime;

		//*current = next;
	}


	//https://hu.wikipedia.org/wiki/Runge%E2%80%93Kutta-m%C3%B3dszer
	//static Transform RungeKutta4(Transform* transform, realStandard_t deltaTime = 0.0)
	//{
	//	Transform initial = *transform;
	//	Transform k1 = transform->Derive();
	//	
	//	transform->position += (k1.position + 2.0 * k2.position + 2.0 * k3.position + k4.position) / 6.0;
	//	transform->velocity += (k1.velocity + 2.0 * k2.velocity + 2.0 * k3.velocity + k4.velocity) / 6.0;
	//	transform->acceleration = VECTOR3(0.0); // (k1.acceleration + 2.0 * k2.acceleration + 2.0 * k3.acceleration + k4.acceleration) / 6.0;
	//	transform->rotation += (k1.rotation + 2.0 * k2.rotation + 2.0 * k3.rotation + k4.rotation) / 6.0;
	//	transform->angularVelocity += (k1.angularVelocity + 2.0 * k2.angularVelocity + 2.0 * k3.angularVelocity + k4.angularVelocity) / 6.0;
	//	transform->angularAcceleration = glm::identity<QUATERNION>(); // (k1.angularAcceleration + 2.0 * k2.angularAcceleration + 2.0 * k3.angularAcceleration + k4.angularAcceleration) / 6.0;
	//}


	static Transform LeapfrogSolver(Transform* transform, realStandard_t deltaTime, size_t n = 2)
	{
		for (size_t i = 0; i < n; i++)
		{
			SemiImplicitEulerSolver(transform, deltaTime / n);
		}
	}

	// Large scale

};


#endif
