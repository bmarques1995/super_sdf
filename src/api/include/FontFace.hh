#ifndef FONT_FACE_HH
#define FONT_FACE_HH

#include <stb_truetype.h>
#include <cstdint>
#include <string>
#include <cmath>

namespace SuperSDF
{
	class FontFace
	{
	public:
		FontFace(std::string_view fontpath, float fontHeight);
		~FontFace();

		void GenGlyphShape(unsigned glyphCode, stbtt_vertex** vertices, size_t* verticesSize) const;
		void DeleteGlyphShape(stbtt_vertex** vertices) const;
		float GetScale() const;
		float GetHeight() const;
		float GetAscent() const;
		float GetDescent() const;
	private:
		float m_Scale;
		float m_FontHeight;
		stbtt_fontinfo m_FontInfo;
		uint8_t* m_Buffer;
		int32_t m_Ascent, m_Descent, m_LineGap;
	};
}

#endif
