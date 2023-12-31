#include <Model/ShaderCompiler.hpp>

std::string ShaderCompiler::readCodesFromFIle(const std::string& filename) {
  // Load source file
  std::ifstream reader;
  std::string code;

  // Open source file
  reader.open(filename.c_str(), std::ios::in);
  if (!reader.is_open()) {
    // Finish with error message if source file could not be opened
    fprintf(stderr, "Failed to load a shader: %s\n", filename.c_str());
    exit(1);
  }

  // Load entire contents of a file and store to a string variable
  {
    // Move seek position to the end
    reader.seekg(0, std::ios::end);
    // Reserve memory location for code characters
    code.reserve(reader.tellg());
    // Move seek position back to the beginning
    reader.seekg(0, std::ios::beg);

    // Load entire file and copy to "code" variable
    code.assign(std::istreambuf_iterator<char>(reader),
                std::istreambuf_iterator<char>());
  }

  // Close file
  reader.close();

  return code;
}

GLuint ShaderCompiler::compile(const std::string& code, GLuint type) {
  // Create a shader
  GLuint shaderId = glCreateShader(type);

  // Compile a source code
  const char* codeChars = code.c_str();
  glShaderSource(shaderId, 1, &codeChars, NULL);
  glCompileShader(shaderId);

  // Check whther compile is successful
  GLint compileStatus;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
  if (compileStatus == GL_FALSE) {
    // Terminate with error message if compilation failed
    fprintf(stderr, "Failed to compile a shader!\n");

    // Get length of error message
    GLint logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
      // Get error message
      GLsizei length;
      std::string errMsg;
      errMsg.resize(logLength);
      glGetShaderInfoLog(shaderId, logLength, &length, &errMsg[0]);

      // Print error message and corresponding source code
      fprintf(stderr, "[ ERROR ] %s\n", errMsg.c_str());
      fprintf(stderr, "%s\n", code.c_str());
    }
    exit(1);
  }

  return shaderId;
}

GLuint ShaderCompiler::buildShaderProgram(const std::string& vertexShaderCode,
                                          const std::string& fragmentShaderCode) {
  // Compile shader files
  GLuint vertShaderId = ShaderCompiler::compile(vertexShaderCode, GL_VERTEX_SHADER);
  GLuint fragShaderId = ShaderCompiler::compile(fragmentShaderCode, GL_FRAGMENT_SHADER);

  // Link shader objects to the program
  GLuint programId = glCreateProgram();
  glAttachShader(programId, vertShaderId);
  glAttachShader(programId, fragShaderId);
  glLinkProgram(programId);

  // Check whether link is successful
  GLint linkState;
  glGetProgramiv(programId, GL_LINK_STATUS, &linkState);
  if (linkState == GL_FALSE) {
    // Terminate with error message if link is failed
    fprintf(stderr, "Failed to link shaders!\n");

    // Get length of error message
    GLint logLength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
      // Get error message
      GLsizei length;
      std::string errMsg;
      errMsg.resize(logLength);
      glGetProgramInfoLog(programId, logLength, &length, &errMsg[0]);

      // Print error message
      fprintf(stderr, "[ ERROR ] %s\n", errMsg.c_str());
    }
    exit(1);
  }

  // Disable shader program and return its ID
  glUseProgram(0);
  return programId;
}