#ifndef SIGNAL_HH
#define SIGNAL_HH

namespace SuperSDF
{
	class Signal
	{
	public:
		static float Clamp(float value, float lower, float upper);
		static float Sgn(float value);
	};
}

#endif // SIGNAL_HH
