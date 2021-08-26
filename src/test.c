#include "core.h"
#include "graphics.h"
#include "math.h"

#include "glad/glad.h"

#include <stdio.h>
#include <stdlib.h>


#define glCheck(x_) glClearError(); x_; if (!glCheckError(__FILE__, __func__, __LINE__)) exit(-1)

static inline void glClearError()
{
	while (glGetError() != GL_NO_ERROR) {}
}

static inline int glCheckError(const char* file, const char* func, int line)
{
    GLenum error = glGetError();
	if (error)
	{
		fprintf(stderr, "[%10s:%3d] [ERROR] [OPENGL] %s(): 0x%x\n", file, line, func, error);
		return 0;
	}
    return 1;
}

struct
{
    float x, y;
} vertices[] = {
    {-0.5f, -0.5f},
    { 0.0f,  0.5f},
    { 0.5f, -0.5f},
};

int main(void)
{
    Window* window = windowCreate("Sandbox", 640, 480, 0);

    VAO* vao = vaoCreate();
    vaoBind(vao);

    VBO vbo = vboCreate(vertices, sizeof vertices, sizeof *vertices, STATIC_DRAW);
    vboPushAttribute(vbo, GL_FLOAT, 2, 0);

    vaoPushVbo(vao, vbo);

    const char* vert =
        "#version 330 core"
        "layout(location = 0) in vec2 aPosition;"
        "void main()"
        "{"
            "gl_Position = aPosition;"
        "}";

    const char* frag =
        "#version 330 core"
        "out vec4 fColor;"
        "void main()"
        "{"
            "fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
        "}";

    Shader shader = shaderCreateFromSrc(vert, frag);
    shaderBind(shader);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (windowIsOpen(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        vaoBind(vao);
        vboBind(vbo);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        windowPollEvents(window);
        windowSwapBuffers(window);
    }

    vaoDestroy(vao);
    windowDestroy(window);

    return 0;
}
