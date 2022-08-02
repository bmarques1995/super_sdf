#ifndef LINEAR_ALGEBRA_HH
#define LINEAR_ALGEBRA_HH

#include <Eigen/Dense>
#include <vector>

namespace SuperSDF
{
	struct DrawBox
	{
		Eigen::Vector2f StartPoint;
		Eigen::Vector2f Dimensions;
	};

	enum class PointType
	{
		Line = 0,
		QuadraticBezier,
		CubicBezier
	};

	struct Utils
	{
		static float Clamp(float value, float lowerValue, float upperValue);
	};

	struct Point
	{
		Eigen::Vector2f LocationPoint;
		Eigen::Vector2f QuadraticControlPoint;
		Eigen::Vector2f CubicControlPoint;
		PointType Type;
		bool IsCorner;

		Point(Eigen::Array2f locationPoint, Eigen::Array2f quadraticControlPoint, Eigen::Array2f cubicControlPoint, PointType type);
	};

	struct Segment
	{
		Eigen::Vector2f InitialPoint;
		Eigen::Vector2f FinalPoint;

		static bool Cross(const Segment& segment1, const Segment& segment2);
		
	private:
		static bool CrossIsClockwise(const Eigen::Vector2f& vector1, const Eigen::Vector2f& vector2);
	};
}

#endif // FONT_HELPERS_HH
