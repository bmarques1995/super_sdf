#include "GlyphShape.hh"

SuperSDF::GlyphShape::GlyphShape(unsigned charCode, const FontFace& font)
{
	m_DrawBox.StartPoint = Eigen::Vector2f(0, font.GetDescent());
	m_DrawBox.Dimensions = Eigen::Vector2f(font.GetAscent() - font.GetDescent(), font.GetAscent() - font.GetDescent());
	PushContours(charCode, font);
	CheckHullContours();
}

SuperSDF::GlyphShape::~GlyphShape()
{
}

void SuperSDF::GlyphShape::PrintContours() const
{
	for (auto& contour : m_Contours)
	{
		contour.PrintContour();
	}
}

void SuperSDF::GlyphShape::PushContours(unsigned charCode, const FontFace& font)
{
	stbtt_vertex* vertex;
	size_t size;
	size_t start = 0;
	font.GenGlyphShape(charCode, &vertex, &size);
	for (size_t i = start; i < size; i = start)
	{
		Contour contour;
		start = contour.AddSurface(vertex,size,i);
		m_Contours.push_back(contour);
	}
	font.DeleteGlyphShape(&vertex);
}

void SuperSDF::GlyphShape::CheckHullContours()
{
	std::vector<size_t> priorityCompare;
	size_t hullCounter = 0;
	size_t cutCounter = 0;
	for (size_t i = 0; i < m_Contours.size(); i++)
	{
		priorityCompare.push_back(i);
	}
	for (size_t i = 0; i < m_Contours.size(); i++)
	{
		Eigen::Vector2f point = m_Contours[i].GetPoints()[0].LocationPoint;
		bool belongsAnotherContour = false;
		bool isHull = true;
		for (size_t j = 0; j < priorityCompare.size(); j++)
		{
			if ((i != priorityCompare[j]) && m_Contours[priorityCompare[j]].PointBelongs(point, m_DrawBox))
			{
				isHull = false;
				break;
			}
		}
		if (isHull)
		{
			auto index = priorityCompare[i];
			priorityCompare[hullCounter] = i;
			priorityCompare[i] = index;
			hullCounter++;
		}
		else
			cutCounter++;

	}
	for (size_t i = 0; i < hullCounter; i++)
	{
		if (!m_Contours[priorityCompare[i]].IsClockwise())
			m_Contours[priorityCompare[i]].Flip();
	}
	for (size_t i = hullCounter; i < (hullCounter+cutCounter); i++)
	{
		if (m_Contours[priorityCompare[i]].IsClockwise())
			m_Contours[priorityCompare[i]].Flip();
	}
}
