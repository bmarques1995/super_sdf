#include "Shader.hh"

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
	m_ShaderMapping[GL_VERTEX_SHADER] = "Vertex";
	m_ShaderMapping[GL_FRAGMENT_SHADER] = "Vertex";
	std::vector<unsigned> shaders;

	shaders.push_back(Compile(vertexSource, GL_VERTEX_SHADER));
	shaders.push_back(Compile(fragmentSource, GL_FRAGMENT_SHADER));

	m_ProgramID = Link(shaders);
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::Bind() const
{
	glUseProgram(m_ProgramID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

unsigned Shader::Compile(const char* source, GLenum type)
{
	unsigned shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	CheckCompileErrors(shader, m_ShaderMapping[type]);
	return shader;
}

unsigned Shader::Link(const std::vector<unsigned>& shaders)
{
	unsigned program = glCreateProgram();
	for (auto& shader: shaders) 
	{
		glAttachShader(program, shader);
	}
	
	glLinkProgram(program);
	CheckLinkErrors(program);
	for (auto& shader : shaders)
	{
		glDeleteShader(shader);
	}
	return program;
}

void Shader::CheckCompileErrors(unsigned int shader, std::string_view shaderType)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* infoLog = new GLchar[maxLength+1];
		infoLog[maxLength] = '\0';

		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR in: " << shaderType << " Shader\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		
		delete[] infoLog;
	}
	
}

void Shader::CheckLinkErrors(unsigned int program)
{
	int success;
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* infoLog = new GLchar[maxLength + 1];
		infoLog[maxLength] = '\0';
		
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		std::cout << "ERROR::SHADER_LINK_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		
		delete[] infoLog;
	}
}
