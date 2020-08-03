#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glut.h>

class ShaderFactory {
public:
    ShaderFactory(const std::string& filepath);

    std::string GetVertexShader() const { return VertexSource_; };

    std::string GetFragmentShader() const { return FragmentSource_; };

    unsigned int CreateShader();

    unsigned int CompileShader(unsigned int type, const std::string& source);

private:
    std::string VertexSource_;
	std::string FragmentSource_;
};