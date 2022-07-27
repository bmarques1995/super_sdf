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

	size_t vertex_pos = PushPoints(vertex, size, start);
	SetClockwise();
	SetCorners();
	return vertex_pos;
}

void SuperSDF::Contour::PrintContour() const
{
	std::vector<int> location_x;
	std::vector<int> location_y;
	std::vector<int> control_x;
	std::vector<int> control_y;
	std::vector<int> cubicControl_x;
	std::vector<int> cubicControl_y;

	for (auto& i : m_Contour)
	{
		location_x.push_back(i.LocationPoint(0));
		location_y.push_back(i.LocationPoint(1));
		control_x.push_back(i.QuadraticControlPoint(0));
		control_y.push_back(i.QuadraticControlPoint(1));
		cubicControl_x.push_back(i.CubicControlPoint(0));
		cubicControl_y.push_back(i.CubicControlPoint(1));
	}

	std::cout << "Clockwise<-" << (m_Clockwise ? "TRUE" : "FALSE") << "\n";
	std::cout << "Location_X<-c(";
	for (size_t i = 0; i < location_x.size(); i++)
	{
		std::cout << location_x[i];
		if (i != (location_x.size() - 1))
			std::cout << ",";
	}
	std::cout << ")\n";
	std::cout << "Location_Y<-c(";
	for (size_t i = 0; i < location_y.size(); i++)
	{
		std::cout << location_y[i];
		if (i != (location_y.size() - 1))
			std::cout << ",";
	}
	std::cout << ")\n";
	std::cout << "Control_X<-c(";
	for (size_t i = 0; i < control_x.size(); i++)
	{
		std::cout << control_x[i];
		if (i != (control_x.size() - 1))
			std::cout << ",";
	}
	std::cout << ")\n";
	std::cout << "Control_Y<-c(";
	for (size_t i = 0; i < control_y.size(); i++)
	{
		std::cout << control_y[i];
		if (i != (control_y.size() - 1))
			std::cout << ",";
	}
	std::cout << ")\n";
	std::cout << "CubicControl_X<-c(";
	for (size_t i = 0; i < cubicControl_x.size(); i++)
	{
		std::cout << cubicControl_x[i];
		if (i != (cubicControl_x.size() - 1))
			std::cout << ",";
	}
	std::cout << ")\n";
	std::cout << "CubicControl_Y<-c(";
	for (size_t i = 0; i < cubicControl_y.size(); i++)
	{
		std::cout << cubicControl_y[i];
		if (i != (cubicControl_y.size() - 1))
			std::cout << ",";
	}
	std::cout << ")\n\n";
}

const std::vector<SuperSDF::Point>& SuperSDF::Contour::GetPoints() const
{
	return m_Contour;
}

const bool SuperSDF::Contour::PointBelongs(const Eigen::Vector2f& point, const DrawBox& drawBox) const
{
	Segment shoot = { point,Eigen::Vector2f((drawBox.StartPoint(0) + drawBox.Dimensions(0) + 1),point(1)) };
	Segment contourSegment;
	size_t crossingCounter = 0;
	for (size_t i = 0; i < m_Contour.size(); i++)
	{
		contourSegment = { m_Contour[i].LocationPoint, m_Contour[(i + 1) % m_Contour.size()].LocationPoint };
		if (Segment::Cross(shoot, contourSegment))
			crossingCounter++;
	}
	return 1 == (crossingCounter % 2);
}

const bool SuperSDF::Contour::IsClockwise() const
{
	return m_Clockwise;
}

void SuperSDF::Contour::Flip()
{
	for (size_t i = 0; i < m_Contour.size() / 2; i++)
	{
		Point p = m_Contour[i];
		m_Contour[i] = m_Contour[m_Contour.size() - i - 1];
		m_Contour[m_Contour.size() - i - 1] = p;
	}
	m_Clockwise = !m_Clockwise;
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
			m_Contour.push_back(Point(Eigen::Array2f(vertex[vertex_pos].x, vertex[vertex_pos].y), Eigen::Array2f(10000.0f, 10000.0f), Eigen::Array2f(10000.0f, 10000.0f), PointType::Line));
			break;
		case STBTT_vcurve:
			m_Contour.push_back(Point(Eigen::Array2f(vertex[vertex_pos].x, vertex[vertex_pos].y), Eigen::Array2f(vertex[vertex_pos].cx, vertex[vertex_pos].cy), Eigen::Array2f(10000.0f, 10000.0f), PointType::QuadraticBezier));
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
	size_t lowerAdjacent = (point + m_Contour.size() - 1) % m_Contour.size();
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
