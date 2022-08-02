#include "LinearDistance.hh"

float SuperSDF::LinearDistance::DistancePoint(const Eigen::Vector2f& location, const Point& p1, const Point& p2)
{
	float abscissa = GetAbscissa(location, p1, p2);

	Eigen::Vector2f distanceVector = (1 - abscissa) * p1.LocationPoint + abscissa * p2.LocationPoint;

	return distanceVector.norm();
}

float SuperSDF::LinearDistance::GetAbscissa(const Eigen::Vector2f& location, const Point& p1, const Point& p2)
{
	//ok
	Eigen::Vector2f coeff_p;
	Eigen::Vector2f coeff_p1;
	Eigen::Array2f polynomial;
	coeff_p = location - p1.LocationPoint;
	coeff_p1 = p2.LocationPoint - p1.LocationPoint;
	polynomial << (-1.0) * coeff_p1.dot(coeff_p), coeff_p1.dot(coeff_p1);
	return Utils::Clamp((-1.0) * polynomial(0) / polynomial(1), 0.0f, 1.0f);
}
