#include "GlyphShape.hh"

SuperSDF::GlyphShape::GlyphShape(unsigned charCode) :
	m_CharCode(charCode)
{
}

SuperSDF::GlyphShape::~GlyphShape()
{
}

void SuperSDF::GlyphShape::PushContours(const FontFace& font)
{
	stbtt_vertex* vertex;
	size_t size;
	size_t start = 0;
	font.GenGlyphMetrics(m_CharCode, &vertex, &size);
	for (size_t i = start; i < size; i = start)
	{
		Contour contour;
		start = contour.AddSurface(vertex,size,i);
		m_Contours.push_back(contour);
	}
	font.DeleteGlyphMetrics(&vertex);
}
