#include "LinearDistance.hh"
#include "Signal.hh"

float SuperSDF::LinearDistance::DistancePoint(const Eigen::Vector2f& location, const Point& p1, const Point& p2, float& abscissaOut)
{
	float abscissa = GetAbscissa(location, p1, p2);
	abscissaOut = abscissa;
	float derivativeOrdinate;

	Eigen::Vector2f orientedVector = (1 - abscissa) * p1.LocationPoint + abscissa * p2.LocationPoint;
	Eigen::Vector2f distanceVector = orientedVector - location;
	derivativeOrdinate = (abscissa) * (p2.LocationPoint - p1.LocationPoint)(1);

	Eigen::Vector3f cross(distanceVector(0), distanceVector(1), 0.0f);
	Eigen::Vector3f derivativeCross(abscissa, derivativeOrdinate, 0.0f);

	return distanceVector.norm() * Signal::Sgn(derivativeCross.cross(cross)(2));
}

float SuperSDF::LinearDistance::GetOrthogonality(const Eigen::Vector2f& location, const Point& p1, const Point& p2, float abscissa)
{
	float derivativeOrdinate = (abscissa) * (p2.LocationPoint - p1.LocationPoint)(1);
	Eigen::Vector2f orientedVector = (1 - abscissa) * p1.LocationPoint + abscissa * p2.LocationPoint;
	Eigen::Vector2f temp = orientedVector - location;
	Eigen::Vector3f derivativeVector(abscissa, derivativeOrdinate, 0.0f);
	Eigen::Vector3f distanceVector(temp(0), temp(1), 0.0f);
	derivativeVector.normalize();
	distanceVector.normalize();
	return derivativeVector.cross(distanceVector)(2);
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
	return Signal::Clamp((-1.0) * polynomial(0) / polynomial(1), 0.0f, 1.0f);
}
