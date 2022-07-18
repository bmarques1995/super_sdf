#ifndef FILE_HANDLER_HH
#define FILE_HANDLER_HH

#include <string>
#include <cstdint>

namespace SuperSDF
{
	class FileHandler
	{
	public:
		static bool ReadTextFile(std::string_view filepath, std::string* content);
		static bool WriteTextFile(std::string_view filepath, std::string content);
		static bool ReadBinFile(std::string_view filepath, uint8_t** content);
		static bool WriteBinFile(std::string_view filepath, uint8_t* content, size_t size);
	private:

	};
}

#endif // FILE_HANDLER_HH
