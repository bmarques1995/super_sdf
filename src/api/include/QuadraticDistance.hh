#ifndef QUADRATIC_DISTANCE_HH
#define QUADRATIC_DISTANCE_HH

#include "LinearAlgebra.hh"

namespace SuperSDF
{
	class QuadraticDistance
	{
	public:
		static float DistancePoint(const Eigen::Vector2f& location, const Point& p1, const Point& p2, float& abscissaOut);
		static float GetOrthogonality(const Eigen::Vector2f& location, const Point& p1, const Point& p2, float abscissa);
	private:
		static void GetAbscissas(const Eigen::Vector2f& location, const Point& p1, const Point& p2, std::vector<float>& abscissas);
		static void GetRoots3(const Eigen::Array4f& polynomial, std::vector<float>& roots);
		static Eigen::Vector2f Interpolate(float abscissa, const Point& p1, const Point& p2);
		static float GetDerivativeInterpolation(float abscissa, const Point& p1, const Point& p2);
	};
}

#endif // DISTANCE_2_HH
