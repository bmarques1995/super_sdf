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

		GlyphShape(unsigned charCode);
		~GlyphShape();

		void PushContours(const FontFace& font);

	private:
		unsigned m_CharCode;
		std::vector<Contour> m_Contours;
	};
}

#endif // GLYPH_SHAPE_HH
