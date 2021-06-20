#pragma once

namespace Hazel {

struct FTimeStep
{
	FTimeStep(float InTime = 0.0f)
		: Time(InTime) {}

	operator float() const { return Time; }

	float GetDeltaSeconds() const { return Time; }
	float GetDeltaMiliseconds() const { return Time * 1000.f; }

private:

	float Time;
};

}