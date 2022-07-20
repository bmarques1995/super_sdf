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
	//This will not overflow, because the minimum polygon is a triangle
	Eigen::RowVector3f first_vector = Eigen::Vector3f(m_Contour[1].LocationPoint(0) - m_Contour[0].LocationPoint(0), m_Contour[1].LocationPoint(1) - m_Contour[0].LocationPoint(1), .0f);
	Eigen::RowVector3f second_vector = Eigen::Vector3f(m_Contour[2].LocationPoint(0) - m_Contour[1].LocationPoint(0), m_Contour[2].LocationPoint(1) - m_Contour[1].LocationPoint(1), .0f);
	Eigen::RowVector3f cross = first_vector.cross(second_vector);
	if (cross(2) < 0)
		m_Clockwise = true;
	else
		m_Clockwise = false;
    return vertex_pos;
}
