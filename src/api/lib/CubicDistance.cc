#include "CubicDistance.hh"

float SuperSDF::CubicDistance::DistancePoint(const Eigen::Vector2f& location, const Point& p1, const Point& p2)
{
	//ok
	std::vector<float> abscissa;
	GetAbscissas(location, p1, p2, abscissa);
	std::vector<Eigen::Vector2f> points;
	for (auto& i : abscissa)
	{
		points.push_back(Interpolate3(i, p1, p2));
	}
	float minorDistance = INFINITY;
	for (size_t i = 0; i < points.size(); i++)
	{
		Eigen::Vector2f distanceVector = points[i] - location;
		float norm = distanceVector.norm();
		if (norm < minorDistance)
			minorDistance = norm;
	}
	return minorDistance;
}

void SuperSDF::CubicDistance::GetAbscissas(const Eigen::Vector2f& location, const Point& p1, const Point& p2, std::vector<float>& abscissas)
{
	Eigen::Vector2f coeff_p;
	Eigen::Vector2f coeff_p1;
	Eigen::Vector2f coeff_p2;
	Eigen::Vector2f coeff_p3;
	Eigen::Array<float, 6, 1> polynomialDerivation;
	coeff_p = location - p1.LocationPoint;
	coeff_p1 = p2.QuadraticControlPoint - p1.LocationPoint;
	coeff_p2 = p2.CubicControlPoint - 2 * p2.QuadraticControlPoint + p1.LocationPoint;
	coeff_p3 = p2.LocationPoint - 3 * p2.CubicControlPoint + 3 * p2.QuadraticControlPoint - p1.LocationPoint;
	polynomialDerivation << (-1.0) * coeff_p1.dot(coeff_p),
		3 * coeff_p1.dot(coeff_p1) - coeff_p2.dot(coeff_p),
		9 * coeff_p1.dot(coeff_p2) - coeff_p2.dot(coeff_p),
		4 * coeff_p1.dot(coeff_p3) + 6 * coeff_p2.dot(coeff_p2),
		5 * coeff_p2.dot(coeff_p3),
		coeff_p3.dot(coeff_p3);
	GetRoots5(polynomialDerivation, abscissas);
}

void SuperSDF::CubicDistance::GetRoots5(const Eigen::Array<float, 6, 1>& polynomial, std::vector<float>& roots)
{
	Eigen::Array<float, 6, 1> polynomialCopy = polynomial;
	for (size_t i = 0; i < polynomialCopy.size(); i++)
	{
		polynomialCopy(i) /= polynomialCopy(polynomialCopy.size() - 1);
	}
	Eigen::Matrix<float, 5, 5> eigvals;
	eigvals << 0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		0 - polynomialCopy(0), 0 - polynomialCopy(1), 0 - polynomialCopy(2), 0 - polynomialCopy(3), 0 - polynomialCopy(4);
	Eigen::Vector<Eigen::scomplex, 5> rawRoots = eigvals.eigenvalues();
	for (auto& i : rawRoots)
	{
		if (i.imag() == 0.0f)
			roots.push_back(Utils::Clamp(i.real(), 0.0f, 1.0f));
	}
}

Eigen::Vector2f SuperSDF::CubicDistance::Interpolate3(float abscissa, const Point& p1, const Point& p2)
{
	return (1 - abscissa) * (1 - abscissa) * (1 - abscissa) * p1.LocationPoint
		+ 3 * (1 - abscissa) * (1 - abscissa) * abscissa * p2.QuadraticControlPoint
		+ 3 * (1 - abscissa) * abscissa * abscissa * p2.CubicControlPoint
		+ abscissa * abscissa * abscissa * p2.LocationPoint;
}
