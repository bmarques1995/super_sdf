#include "FileHandler.hh"
#include <fstream>
#include <cstdio>

bool SuperSDF::FileHandler::ReadTextFile(std::string_view filepath, std::string* content)
{
	std::ifstream fileStream;
	fileStream.open(filepath.data(), std::ios::binary);
	if (!fileStream)
		return false;
	auto start = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint64_t fsize = fileStream.tellg() - start;
	fileStream.seekg(0, std::ios::beg);
	char* buffer = new char[fsize + 1];
	buffer[fsize] = '\0';
	fileStream.read(buffer, fsize);
	fileStream.close();
	*content = buffer;
	delete[] buffer;
	return true;
}

bool SuperSDF::FileHandler::WriteTextFile(std::string_view filepath, std::string content)
{
	bool stored = false;
	std::ofstream fileStream;
	fileStream.open(filepath.data(), std::ios::binary);
	if (!fileStream)
		return false;
	fileStream << content;
	fileStream.close();
	return true;
}

bool SuperSDF::FileHandler::ReadBinFile(std::string_view filepath, uint8_t** content)
{
	long size;
	FILE* fileHandler;
#ifdef _WIN32
	fopen_s(&fileHandler, filepath.data(), "rb");
#else
	fileHandler = fopen(filepath.data(), "rb");
#endif
	if (fileHandler != nullptr)
	{
		fseek(fileHandler, 0, SEEK_END);
		size = ftell(fileHandler); /* how long is the file ? */
		fseek(fileHandler, 0, SEEK_SET); /* reset */

		*content = new uint8_t[(size_t)size];
#ifdef _WIN32
		fread_s(*content, (size_t)size, (size_t)size, 1, fileHandler);
#else
		fread(*content, (size_t)size, 1, fileHandler);
#endif
		fclose(fileHandler);
		return true;
	}
	return false;
}

bool SuperSDF::FileHandler::WriteBinFile(std::string_view filepath, uint8_t* content, size_t size)
{
	FILE* fileHandler;
#ifdef _WIN32
	fopen_s(&fileHandler, filepath.data(), "rb");
#else
	fileHandler = fopen(filepath.data(), "rb");
#endif
	if (fileHandler != nullptr)
	{
		fseek(fileHandler, 0, SEEK_END);
		size = ftell(fileHandler); /* how long is the file ? */
		fseek(fileHandler, 0, SEEK_SET); /* reset */

		fwrite(content, (size_t)size, 1, fileHandler);
		fclose(fileHandler);
		return true;
	}
	return false;
}
