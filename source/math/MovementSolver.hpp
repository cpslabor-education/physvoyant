#ifndef ODE_SOLVER
#define ODE_SOLVER

class MovementSolver;
enum class Solvers;

#include "../defines.hpp"
#include INCL_ENGINE
#include INCL_GLM
#include INCL_GEOMETRY

class MovementSolver
{

	inline static VECTOR3 ApplyDelta(VECTOR3 original, VECTOR3 delta, realStandard_t deltaTime)
	{
		return original + delta * deltaTime;
	}

	inline static QUATERNION ApplyRotationDelta(QUATERNION original, QUATERNION angularVelocity, realStandard_t deltaTime)
	{
		return glm::normalize(original + angularVelocity * deltaTime);
	}

public:
	MovementSolver() = delete;
	~MovementSolver() = delete;

	enum class Solvers
	{
		EpxlicitEuler = 0,
		SemiImplicitEuler,
		VerletIntegration,
		Leapfrog,
		RungeKutta4,
		EndOfSolvers
	};

	static void ExplicitEulerSolver(Transform* transform, realStandard_t deltaTime)
	{
		transform->position.vector = ApplyDelta(transform->position.vector, transform->velocity.vector, deltaTime);
		transform->position.SetRotation(ApplyRotationDelta(transform->position.GetRotation(), transform->velocity.GetRotation(), deltaTime));

		transform->velocity.vector = ApplyDelta(transform->velocity.vector, transform->acceleration.vector, deltaTime);
		transform->velocity.SetRotation(ApplyRotationDelta(transform->velocity.GetRotation(), transform->acceleration.GetRotation(), deltaTime));
	}

	static void SemiImplicitEulerSolver(Transform* transform, realStandard_t deltaTime)
	{
		transform->velocity.vector = ApplyDelta(transform->velocity.vector, transform->acceleration.vector, deltaTime);
		transform->velocity.SetRotation(ApplyRotationDelta(transform->velocity.GetRotation(), transform->acceleration.GetRotation(), deltaTime));

		transform->position.vector = ApplyDelta(transform->position.vector, transform->velocity.vector, deltaTime);
		transform->position.SetRotation(ApplyRotationDelta(transform->position.GetRotation(), transform->velocity.GetRotation(), deltaTime));
	}

	// Accuracy
	static void VerletIntegrationSolver(Transform* transform, realStandard_t deltaTime)
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
	static void RungeKutta4(Transform* transform, realStandard_t deltaTime)
	{
		VECTOR3 k1 = transform->velocity.vector;
		QUATERNION q1 = transform->velocity.GetRotation();

		VECTOR3 k2 = ApplyDelta(transform->velocity.vector, transform->acceleration.vector + k1 * deltaTime / 2.0, deltaTime / 2.0);
		QUATERNION q2 = ApplyRotationDelta(transform->velocity.GetRotation(), transform->acceleration.GetRotation() + q1 * deltaTime / 2.0, deltaTime / 2.0);

		VECTOR3 k3 = ApplyDelta(transform->velocity.vector, transform->acceleration.vector + k2 * deltaTime / 2.0, deltaTime / 2.0);
		QUATERNION q3 = ApplyRotationDelta(transform->velocity.GetRotation(), transform->acceleration.GetRotation() + q2 * deltaTime / 2.0, deltaTime / 2.0);

		VECTOR3 k4 = ApplyDelta(transform->velocity.vector, transform->acceleration.vector + k3 * deltaTime, deltaTime);
		QUATERNION q4 = ApplyRotationDelta(transform->velocity.GetRotation(), transform->acceleration.GetRotation() + q3 * deltaTime / 2.0, deltaTime / 2.0);

		VECTOR3 delta = (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0 * deltaTime;
		QUATERNION deltaRotation = (q1 + 2.0 * q2 + 2.0 * q3 + q4) / 6.0 * deltaTime;

		transform->position.vector = transform->position.vector + delta * deltaTime;
		transform->position.SetRotation(ApplyRotationDelta(transform->position.GetRotation(), deltaRotation, 1));

		//transform->velocity.vector = delta;
		//transform->velocity.SetRotation(deltaRotation);
	}


	static void LeapfrogSolver(Transform* transform, realStandard_t deltaTime, uintStandard_t n = 2)
	{
		for (size_t i = 0; i < n; i++)
		{
			SemiImplicitEulerSolver(transform, deltaTime / n);
		}
	}

	// Large scale

};


#endif
