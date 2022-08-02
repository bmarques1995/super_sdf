#include "LinearAlgebra.hh"

SuperSDF::Point::Point(Eigen::Array2f locationPoint, Eigen::Array2f quadraticControlPoint, Eigen::Array2f cubicControlPoint, PointType type)
{
	LocationPoint = locationPoint;
	QuadraticControlPoint = quadraticControlPoint;
	CubicControlPoint = cubicControlPoint;
	Type = type;
	IsCorner = false;
}

float SuperSDF::Utils::Clamp(float value, float lowerValue, float upperValue)
{
	if (value <= lowerValue)
		value = lowerValue;
	if (value >= upperValue)
		value = upperValue;
	return value;
}

bool SuperSDF::Segment::Cross(const Segment& segment1, const Segment& segment2)
{
	bool initialSegmentCross, finalSegmentCross;
	bool component1Clockwise, component2Clockwise;

	component1Clockwise = CrossIsClockwise(segment2.InitialPoint - segment1.InitialPoint, segment1.FinalPoint - segment1.InitialPoint);
	component2Clockwise = CrossIsClockwise(segment2.FinalPoint - segment1.InitialPoint, segment1.FinalPoint - segment1.InitialPoint);
	initialSegmentCross = (component1Clockwise != component2Clockwise);

	component1Clockwise = CrossIsClockwise(segment1.InitialPoint - segment2.InitialPoint, segment2.FinalPoint - segment2.InitialPoint);
	component2Clockwise = CrossIsClockwise(segment1.FinalPoint - segment2.InitialPoint, segment2.FinalPoint - segment2.InitialPoint);
	finalSegmentCross = (component1Clockwise != component2Clockwise);

	return (initialSegmentCross && finalSegmentCross);
}

bool SuperSDF::Segment::CrossIsClockwise(const Eigen::Vector2f& vector1, const Eigen::Vector2f& vector2)
{
	Eigen::Vector3f expandedVector1, expandedVector2;
	expandedVector1 = Eigen::Vector3f(vector1(0), vector1(1), 0.0f);
	expandedVector2 = Eigen::Vector3f(vector2(0), vector2(1), 0.0f);
	return (expandedVector1.cross(expandedVector2)(2) < 0.0f);
}