#ifndef GLYPH_HH
#define GLYPH_HH

#include "GlyphShape.hh"

namespace SuperSDF
{
	class Glyph
	{
	public:
		Glyph(unsigned charCode, const FontFace& fontFace);
		~Glyph();
		void PrintContours() const;
	private:
		GlyphShape m_GlyphShape;
		//metrics
		
		unsigned m_CharCode;
	};
}

#endif // GLYPH_HH
