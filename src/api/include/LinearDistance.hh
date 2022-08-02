#ifndef LINEAR_DISTANCE_HH
#define LINEAR_DISTANCE_HH

#include "LinearAlgebra.hh"

namespace SuperSDF
{
	class LinearDistance
	{
	public:
		static float DistancePoint(const Eigen::Vector2f& location, const Point& p1, const Point& p2);
	private:
		static float GetAbscissa(const Eigen::Vector2f& location, const Point& p1, const Point& p2);
	};
}

#endif
