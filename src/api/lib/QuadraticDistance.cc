#include "QuadraticDistance.hh"
#include "Signal.hh"

float SuperSDF::QuadraticDistance::DistancePoint(const Eigen::Vector2f& location, const Point& p1, const Point& p2, float& abscissaOut)
{
	//ok
	std::vector<float> abscissa;
	float signal = 1.0f;
	GetAbscissas(location, p1, p2, abscissa);
	std::vector<Eigen::Vector2f> points;
	for (auto& i : abscissa)
	{
		points.push_back(Interpolate(i, p1, p2));
	}
	float minorDistance = INFINITY;
	for (size_t i = 0; i < points.size(); i++)
	{
		Eigen::Vector2f distanceVector = points[i] - location;
		float norm = distanceVector.norm();
		if (norm < minorDistance)
		{
			minorDistance = norm;
			Eigen::Vector3f cross(distanceVector(0), distanceVector(1), 0.0f);
			Eigen::Vector3f derivativeCross(points[i](0), GetDerivativeInterpolation(points[i](0), p1, p2), 0.0f);
			signal = Signal::Sgn(derivativeCross.cross(cross)(2));
			abscissaOut = points[i](0);
		}
	}
	return minorDistance*signal;
}

float SuperSDF::QuadraticDistance::GetOrthogonality(const Eigen::Vector2f& location, const Point& p1, const Point& p2, float abscissa)
{
	Eigen::Vector3f derivativeVector(abscissa, GetDerivativeInterpolation(abscissa, p1, p2), 0.0f);
	Eigen::Vector2f temp = Interpolate(abscissa, p1, p2) - location;
	Eigen::Vector3f distanceVector(temp(0), temp(1), 0.0f);
	derivativeVector.normalize();
	distanceVector.normalize();
	return derivativeVector.cross(distanceVector)(2);
}

void SuperSDF::QuadraticDistance::GetAbscissas(const Eigen::Vector2f& location, const Point& p1, const Point& p2, std::vector<float>& abscissas)
{
	Eigen::Vector2f coeff_p;
	Eigen::Vector2f coeff_p1;
	Eigen::Vector2f coeff_p2;
	Eigen::Array4f polynomialDerivation;
	coeff_p = location - p1.LocationPoint;
	coeff_p1 = p2.QuadraticControlPoint - p1.LocationPoint;
	coeff_p2 = p2.LocationPoint - 2 * p2.QuadraticControlPoint + p1.LocationPoint;
	polynomialDerivation << (-1.0) * coeff_p1.dot(coeff_p),
		2 * coeff_p1.dot(coeff_p1) - coeff_p2.dot(coeff_p),
		3 * coeff_p1.dot(coeff_p2),
		coeff_p2.dot(coeff_p2);
	GetRoots3(polynomialDerivation, abscissas);
}

void SuperSDF::QuadraticDistance::GetRoots3(const Eigen::Array4f& polynomial, std::vector<float>& roots)
{
	Eigen::Array4f polynomialCopy = polynomial;
	for (size_t i = 0; i < polynomialCopy.size(); i++)
	{
		polynomialCopy(i) /= polynomialCopy(polynomialCopy.size() - 1);
	}
	Eigen::Matrix3f eigvals;
	eigvals << 0, 1, 0,
		0, 0, 1,
		0 - polynomialCopy(0), 0 - polynomialCopy(1), 0 - polynomialCopy(2);
	Eigen::Vector3cf rawRoots = eigvals.eigenvalues();
	for (auto& i : rawRoots)
	{
		if (i.imag() == 0.0f)
			roots.push_back(Signal::Clamp(i.real(), 0.0f, 1.0f));
	}
}

Eigen::Vector2f SuperSDF::QuadraticDistance::Interpolate(float abscissa, const Point& p1, const Point& p2)
{
	return (1 - abscissa) * (1 - abscissa) * p1.LocationPoint
		+ 2 * (1 - abscissa) * abscissa * p2.QuadraticControlPoint
		+ abscissa * abscissa * p2.LocationPoint;
}

float SuperSDF::QuadraticDistance::GetDerivativeInterpolation(float abscissa, const Point& p1, const Point& p2)
{
	return (2*(p2.QuadraticControlPoint-p1.LocationPoint) 
		+ 2*(p2.LocationPoint-2*p2.QuadraticControlPoint+p1.LocationPoint))(1);
}
