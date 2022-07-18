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
	
	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&m_FontInfo, &ascent, &descent, &lineGap);

	m_Ascent = roundf(ascent * m_Scale);
	m_Descent = roundf(descent * m_Scale);
	m_LineGap = roundf(lineGap * m_Scale);
}

SuperSDF::FontFace::~FontFace()
{
	delete[] m_Buffer;
}

void SuperSDF::FontFace::GetGlyphMetrics(unsigned glyphCode)
{
	std::cout << "Original Scale: " << m_FontHeight / m_Scale << "\n";
	stbtt_vertex* verts;
	int num_verts = stbtt_GetGlyphShape(&m_FontInfo, stbtt_FindGlyphIndex(&m_FontInfo, glyphCode), &verts);
	std::cout << "Glyph: " << (char) glyphCode <<"\n";
	std::cout << "(X,Y) [QX,QY] {CX,CY} PAD TYP\n";
	for (size_t i = 0; i < num_verts; i++)
	{
		std::cout << "(" << verts[i].x << "," << verts[i].y << ") "
			<< "[" << verts[i].cx << "," << verts[i].cy << "] "
			<< "{" << verts[i].cx1 << "," << verts[i].cy1 << "} "
			<< verts[i].padding << " ";
		switch (verts[i].type)
		{
		case STBTT_vmove:
			std::cout << "Control\n";
			break;
		case STBTT_vline:
			std::cout << "Line\n";
			break;
		case STBTT_vcurve:
			std::cout << "Quadratic\n";
			break;
		case STBTT_vcubic:
			std::cout << "Cubic\n";
			break;
		default:
			break;
		}
	}
}

stbtt_fontinfo& SuperSDF::FontFace::GetFontInfo()
{
	return m_FontInfo;
}
