#include "QuadraticDistance.hh"

float SuperSDF::QuadraticDistance::DistancePoint(const Eigen::Vector2f& location, const Point& p1, const Point& p2)
{
	//ok
	std::vector<float> abscissa;
	GetAbscissas(location, p1, p2, abscissa);
	std::vector<Eigen::Vector2f> points;
	for (auto& i : abscissa)
	{
		points.push_back(Interpolate2(i, p1, p2));
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
			roots.push_back(Utils::Clamp(i.real(), 0.0f, 1.0f));
	}
}

Eigen::Vector2f SuperSDF::QuadraticDistance::Interpolate2(float abscissa, const Point& p1, const Point& p2)
{
	return (1 - abscissa) * (1 - abscissa) * p1.LocationPoint
		+ 2 * (1 - abscissa) * p2.QuadraticControlPoint
		+ abscissa * abscissa * p2.LocationPoint;
}
