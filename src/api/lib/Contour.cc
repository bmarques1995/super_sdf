#include "Contour.hh"
#include <iostream>

SuperSDF::Contour::Contour()
{
}

SuperSDF::Contour::~Contour()
{
}

size_t SuperSDF::Contour::AddSurface(stbtt_vertex* vertex, size_t size, size_t start)
{
	//todo
	//return also vertex control, for tests
	
	size_t vertex_pos = PushPoints(vertex,size,start);
	SetClockwise();
	SetCorners();
    return vertex_pos;
}

void SuperSDF::Contour::SetClockwise()
{
	//This will not overflow, because the minimum polygon is a triangle, and the contour must match a polygon
	Eigen::RowVector3f first_vector = Eigen::Vector3f(m_Contour[1].LocationPoint(0) - m_Contour[0].LocationPoint(0), m_Contour[1].LocationPoint(1) - m_Contour[0].LocationPoint(1), .0f);
	Eigen::RowVector3f second_vector = Eigen::Vector3f(m_Contour[2].LocationPoint(0) - m_Contour[1].LocationPoint(0), m_Contour[2].LocationPoint(1) - m_Contour[1].LocationPoint(1), .0f);
	Eigen::RowVector3f cross = first_vector.cross(second_vector);
	if (cross(2) < 0)
		m_Clockwise = true;
	else
		m_Clockwise = false;
}

void SuperSDF::Contour::SetCorners()
{
	for (size_t i = 0; i < m_Contour.size(); i++)
	{
		m_Contour[i].IsCorner = CheckCorner(i, 3.0f);
	}
}

size_t SuperSDF::Contour::PushPoints(stbtt_vertex* vertex, size_t size, size_t start)
{
	size_t vertex_pos = start;
	m_Contour.clear();
	for (size_t control_count = 0; vertex_pos < size; vertex_pos++)
	{
		switch (vertex[vertex_pos].type)
		{
		case STBTT_vmove:
			control_count++;
			break;
		case STBTT_vline:
			m_Contour.push_back(Point(Eigen::Array2f(vertex[vertex_pos].x, vertex[vertex_pos].y), Eigen::Array2f(.0f, .0f), Eigen::Array2f(.0f, .0f), PointType::Line));
			break;
		case STBTT_vcurve:
			m_Contour.push_back(Point(Eigen::Array2f(vertex[vertex_pos].x, vertex[vertex_pos].y), Eigen::Array2f(vertex[vertex_pos].cx, vertex[vertex_pos].cy), Eigen::Array2f(.0f, .0f), PointType::QuadraticBezier));
			break;
		case STBTT_vcubic:
			m_Contour.push_back(Point(Eigen::Array2f(vertex[vertex_pos].x, vertex[vertex_pos].y), Eigen::Array2f(vertex[vertex_pos].cx, vertex[vertex_pos].cy), Eigen::Array2f(vertex[vertex_pos].cx1, vertex[vertex_pos].cy1), PointType::CubicBezier));
			break;
		default:
			break;
		}
		if (control_count > 1)
			break;
	}
	return vertex_pos;
}

bool SuperSDF::Contour::CheckCorner(size_t point, float toleranceAngle)
{
	size_t lowerAdjacent = (point + m_Contour.size() - 1)% m_Contour.size();
	size_t upperAdjacent = (point + 1) % m_Contour.size();
	Eigen::Vector3f lowerDerivation;
	Eigen::Vector3f upperDerivation;
	switch (m_Contour[point].Type)
	{
	case PointType::QuadraticBezier:
		lowerDerivation << m_Contour[point].LocationPoint(0) - m_Contour[point].QuadraticControlPoint(0), m_Contour[point].LocationPoint(1) - m_Contour[point].QuadraticControlPoint(1), 0;
		break;
	case PointType::CubicBezier:
		lowerDerivation << m_Contour[point].LocationPoint(0) - m_Contour[point].CubicControlPoint(0), m_Contour[point].LocationPoint(1) - m_Contour[point].CubicControlPoint(1), 0;
		break;
	case PointType::Line:
	default:
		lowerDerivation << m_Contour[point].LocationPoint(0) - m_Contour[lowerAdjacent].LocationPoint(0), m_Contour[point].LocationPoint(1) - m_Contour[lowerAdjacent].LocationPoint(0), 0;
		break;
	}
	switch (m_Contour[upperAdjacent].Type)
	{
	case PointType::QuadraticBezier:
	case PointType::CubicBezier:
		upperDerivation << m_Contour[upperAdjacent].QuadraticControlPoint(0) - m_Contour[point].LocationPoint(0), m_Contour[upperAdjacent].QuadraticControlPoint(1) - m_Contour[point].LocationPoint(1), 0;
		break;
	case PointType::Line:
	default:
		upperDerivation << m_Contour[upperAdjacent].LocationPoint(0) - m_Contour[point].LocationPoint(0), m_Contour[point].LocationPoint(1) - m_Contour[lowerAdjacent].LocationPoint(0), 0;
		break;
	}
	lowerDerivation.normalize();
	upperDerivation.normalize();

	Eigen::RowVector3f cross = lowerDerivation.cross(upperDerivation);
	return !(abs((asin(cross(2))) * 180 / acos(-1)) <= toleranceAngle);
}
