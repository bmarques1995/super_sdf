#include "FontFace.hh"
#include "FileHandler.hh"
#include <cstdlib>
#include <iostream>

SuperSDF::FontFace::FontFace(std::string_view fontpath, float fontHeight) :
	m_FontHeight(fontHeight)
{
	bool readResult = FileHandler::ReadBinFile(fontpath, &m_Buffer);
	if (!readResult)
		exit(1);
	if (!stbtt_InitFont(&m_FontInfo, m_Buffer, 0))
	{
		exit(2);
	}
	m_Scale = stbtt_ScaleForPixelHeight(&m_FontInfo, m_FontHeight);
	
	
	stbtt_GetFontVMetrics(&m_FontInfo, &m_Ascent, &m_Descent, &m_LineGap);
}

SuperSDF::FontFace::~FontFace()
{
	delete[] m_Buffer;
}

void SuperSDF::FontFace::GenGlyphShape(unsigned glyphCode, stbtt_vertex** vertices, size_t* verticesSize) const
{
	*verticesSize = (size_t)stbtt_GetGlyphShape(&m_FontInfo, stbtt_FindGlyphIndex(&m_FontInfo, glyphCode), vertices);
}

void SuperSDF::FontFace::DeleteGlyphShape(stbtt_vertex** vertices) const
{
	stbtt_FreeShape(&m_FontInfo, *vertices);
}

float SuperSDF::FontFace::GetScale() const
{
	return m_Scale;
}

float SuperSDF::FontFace::GetHeight() const
{
	return m_FontHeight;
}

float SuperSDF::FontFace::GetAscent() const
{
	return m_Ascent;
}

float SuperSDF::FontFace::GetDescent() const
{
	return m_Descent;
}
