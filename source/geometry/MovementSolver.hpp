#ifndef ODE_SOLVER
#define ODE_SOLVER

#include "../defines.hpp"
#include INCL_GLM
#include INCL_ENGINE
#include INCL_GEOMETRY

static class MovementSolver
{
	// TODO: Aplly friciton
	// TODO: Assert time > 0

	static Transform Derivatives(const Transform& s)
	{
		Transform derivatives;
		derivatives.position = s.velocity;
		derivatives.velocity = s.acceleration;
		derivatives.acceleration = VECTOR3(0.0);
		derivatives.rotation = s.angularVelocity;
		derivatives.angularVelocity = s.angularAcceleration;
		derivatives.angularAcceleration = QUATERNION(0.0, 0.0, 0.0, 0.0);
		return derivatives;
	};
public:
	// static realStandard_t globalFriction;
	// static VECTOR3 globalGravity;

	// Simple system

	static void ExplicitEulerSolver(Transform* transform, realStandard_t deltaTime = 0.0)
	{
		if (deltaTime == 0.0) // in the magical case where deltaTime is LESS than zero; reverse deltaTime
		{
			deltaTime = TO_SECOND(Engine::GetInstance()->clock.ScaledPhysicsDeltaTime());
		}
		transform->position += transform->velocity * deltaTime;
		transform->rotation += transform->angularVelocity * deltaTime;

		transform->velocity += transform->acceleration * deltaTime;
		transform->angularVelocity += transform->angularAcceleration * deltaTime;
	}

	static void SemiImplicitEulerSolver(Transform* transform, realStandard_t deltaTime = 0.0)
	{
		if (deltaTime == 0.0) // in the magical case where deltaTime is LESS than zero; reverse deltaTime
		{
			deltaTime = TO_SECOND(Engine::GetInstance()->clock.ScaledPhysicsDeltaTime());
		}
		transform->velocity += transform->acceleration * deltaTime;
		transform->angularVelocity += transform->angularAcceleration * deltaTime;

		transform->position += transform->velocity * deltaTime;
		transform->rotation += transform->angularVelocity * deltaTime;
	}

	// Accuracy
	static Transform VerletIntegration(const Transform& previous, const Transform& current, realStandard_t deltaTime, realStandard_t prevDeltaTime)
	{
		Transform next = current;

		next.position = current.position + (current.position - previous.position) * (deltaTime / prevDeltaTime) + current.acceleration * (deltaTime * deltaTime);

		// Update velocity based on new position
		next.velocity = (next.position - previous.position) / (2.0 * deltaTime);

		// Update rotation and angular velocity (simple linear interpolation, adjust if needed)
		next.rotation = current.rotation + (current.rotation - previous.rotation) * deltaTime;
		next.angularVelocity = (next.rotation - previous.rotation) / deltaTime;

		// Update angular acceleration (placeholder for actual calculation)
		next.angularAcceleration = QUATERNION(0.0f, 0.0f, 0.0f, 0.0f);

		return next;
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

	static Transform Leapfrog(Transform* transform, realStandard_t deltaTime = 0.0, size_t n = 2)
	{
		for (size_t i = 0; i < n; i++)
		{
			SemiImplicitEulerSolver(transform, deltaTime / n);
		}
	}

	// Large scale

};


#endif
