#ifndef GLYPH_SHAPE_HH
#define GLYPH_SHAPE_HH

#include "Contour.hh"
#include <stb_truetype.h>
#include "FontFace.hh"

namespace SuperSDF
{
	class GlyphShape
	{
	public:

		GlyphShape(unsigned charCode, const FontFace& font);
		~GlyphShape();
		void PrintContours() const;
	private:
		void PushContours(unsigned charCode, const FontFace& font);
		void CheckHullContours();

		std::vector<Contour> m_Contours;
		DrawBox m_DrawBox;
	};
}

#endif // GLYPH_SHAPE_HH
