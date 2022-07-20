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

		void DebugGlyphMetrics(unsigned glyphCode) const;
		void GenGlyphMetrics(unsigned glyphCode, stbtt_vertex** vertices, size_t* verticesSize) const;
		void DeleteGlyphMetrics(stbtt_vertex** vertices) const;
		float GetScale() const;
		float GetHeight() const;
	private:
		float m_Scale;
		float m_FontHeight;
		stbtt_fontinfo m_FontInfo;
		uint8_t* m_Buffer;
		uint32_t m_Ascent, m_Descent, m_LineGap;
	};
}

#endif
