#include "Signal.hh"

float SuperSDF::Signal::Clamp(float value, float lower, float upper)
{
	if (value <= lower)
		value = lower;
	if (value >= upper)
		value = upper;
	return value;
}

float SuperSDF::Signal::Sgn(float value)
{
	if (value > 0.0f)
		value = 1.0f;
	if (value < 0.0f)
		value = -1.0f;
	return value;
}
