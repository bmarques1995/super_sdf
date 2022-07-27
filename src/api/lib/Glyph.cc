#include "Glyph.hh"

SuperSDF::Glyph::Glyph(unsigned charCode, const FontFace& fontFace) :
	m_GlyphShape(charCode, fontFace)
{
	m_CharCode = charCode;
}

SuperSDF::Glyph::~Glyph()
{
}

void SuperSDF::Glyph::PrintContours() const
{
	m_GlyphShape.PrintContours();
}