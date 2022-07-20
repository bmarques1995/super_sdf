#ifndef CONTOUR_HH
#define CONTOUR_HH

#include <Eigen/Dense>
#include <vector>
#include <stb_truetype.h>

namespace SuperSDF
{
	enum class PointType
	{
		Line = 0,
		QuadraticBezier,
		CubicBezier
	};
	struct Point
	{
		Eigen::Array2f LocationPoint;
		Eigen::Array2f QuadraticControlPoint;
		Eigen::Array2f CubicControlPoint;
		PointType Type;

		Point(Eigen::Array2f locationPoint, Eigen::Array2f quadraticControlPoint, Eigen::Array2f cubicControlPoint, PointType type)
		{
			LocationPoint = locationPoint;
			QuadraticControlPoint = quadraticControlPoint;
			CubicControlPoint = cubicControlPoint;
			Type = type;
		}
	};

	class Contour
	{
	public:
		Contour();
		~Contour();

		size_t AddSurface(stbtt_vertex* vertex, size_t size, size_t start);

	private:
		std::vector<Point> m_Contour;
		bool m_Clockwise = true;
	};

}

#endif // CONTOUR_HH