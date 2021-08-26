#include "graphics.h"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <stdio.h>  // FILE, fprintf, stderr
#include <stdlib.h> // malloc, calloc, free

#define glCheck(x_) glClearError(); x_; if (!glLogCall(__FILE__, __func__, __LINE__)) exit(1)

static inline void glClearError()
{
	while (glGetError() != GL_NO_ERROR) {}
}

static inline int glLogCall(const char* file, const char* func, int line)
{
    GLenum error = glGetError();
	if (error)
	{
		fprintf(stderr, "[%10s:%3d] [ERROR] [OPENGL] %s(): %x\n", file, line, func, error);
		return 0;
	}
    return 1;
}

//-----------------------------
// ~VBO

static uint dataTypeToGLType(DataType type);
static uint dataTypeSize(DataType type);

VBO vboCreate(const void* data, uint size, DrawMode mode, uint stride)
{
    VBO vbo;
    glCheck(glGenBuffers(1, &vbo.id));
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, vbo.id));
    glCheck(glBufferData(GL_ARRAY_BUFFER, size, data, mode));
    vbo.layout.stride = stride;
    return vbo;
}

void vboDestroy(VBO vbo)
{
    glCheck(glDeleteBuffers(1, &vbo.id));
}

void vboPushLayout(VBO vbo, const char* name, uint type, bool normalized)
{
    (void)name;

    vboBind(vbo);

    glCheck(glEnableVertexAttribArray(vbo.layout.index));
    glCheck(glVertexAttribPointer(
        vbo.layout.index,
        dataTypeSize(type),
        dataTypeToGLType(type),
        normalized,
        vbo.layout.stride,
        (const void*)&vbo.layout.offset
    ));

    vbo.layout.index++;
    vbo.layout.offset += dataTypeSize(type);
}

void vboSubmitData(VBO vbo, const void* data, uint size, uint offset)
{
    vboBind(vbo);
    glCheck(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

//- - - - - - - - - - - - - - -

static uint dataTypeToGLType(DataType type)
{
    switch (type)
    {
        case DATA_TYPE_BYTE:    return GL_BYTE;
        case DATA_TYPE_UBYTE:   return GL_UNSIGNED_BYTE;
        case DATA_TYPE_INT:     return GL_INT;
        case DATA_TYPE_INT2:    return GL_INT;
        case DATA_TYPE_INT3:    return GL_INT;
        case DATA_TYPE_INT4:    return GL_INT;
        case DATA_TYPE_UINT:    return GL_UNSIGNED_INT;
        case DATA_TYPE_FLOAT:   return GL_FLOAT;
        case DATA_TYPE_FLOAT2:  return GL_FLOAT;
        case DATA_TYPE_FLOAT3:  return GL_FLOAT;
        case DATA_TYPE_FLOAT4:  return GL_FLOAT;
    };

    return 0;
}

static uint dataTypeSize(DataType type)
{
    switch (type)
    {
        case DATA_TYPE_BYTE:   return 1;
        case DATA_TYPE_UBYTE:  return 1;
        case DATA_TYPE_INT:    return 4;
        case DATA_TYPE_UINT:   return 4;
        case DATA_TYPE_FLOAT:  return 4;
        case DATA_TYPE_FLOAT2: return 8;
        case DATA_TYPE_INT2:   return 8;
        case DATA_TYPE_FLOAT3: return 12;
        case DATA_TYPE_INT3:   return 12;
        case DATA_TYPE_FLOAT4: return 16;
        case DATA_TYPE_INT4:   return 16;
    };

    return 0;
}

//-----------------------------
// ~IBO

IBO iboCreate(const void* data, uint size, DrawMode mode)
{
    IBO ibo = {0};
    glCheck(glGenBuffers(1, &ibo.id));
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.id));
    glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode));
    return ibo;
}

void iboDestroy(IBO ibo)
{
    glCheck(glDeleteBuffers(1, &ibo.id));
}

void iboBind(IBO ibo)
{
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.id));
}

void iboUnbind(IBO ibo)
{
    (void)ibo;
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void iboSubmitData(IBO ibo, const void* data, uint size, uint offset)
{
    iboBind(ibo);
    glCheck(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}

//-----------------------------
// ~VAO

VAO* vaoCreate(void)
{
    VAO* vao = malloc(sizeof *vao);

    if (vao)
        glCheck(glGenVertexArrays(1, &vao->id));

    return vao;
}

void vaoDestroy(VAO* vao)
{
    if (!vao)
        return;

    for (uint i = 0; i < vao->vboCount; ++i)
        vboDestroy(vao->vbos[i]);

    iboDestroy(vao->ibo);
    glCheck(glDeleteVertexArrays(1, &vao->id));

    free(vao);
    vao = NULL;
}

void vaoBind(VAO* vao)
{
    if (!vao)
        return;

    glCheck(glBindVertexArray(vao->id));
}

void vaoUnbind(VAO* vao)
{
    (void)vao;
    glCheck(glBindVertexArray(0));
}

void vaoAttachVbo(VAO* vao, VBO vbo)
{
    if (!vao || vao->vboCount == MAX_VAO_VBOS)
        return;

    vao->vbos[vao->vboCount++] = vbo;
}

void vaoSetIbo(VAO* vao, IBO ibo)
{
    if (!vao)
        return;

    vao->ibo = ibo;
}

//-----------------------------
// ~Shader

static char* shaderParse(const char* srcPath);
static uint  shaderCompile(const char* srcPath, uint type);

Shader shaderCreate(const char* vertPath, const char* fragPath)
{
    Shader shader;
    glCheck(shader.id = glCreateProgram());
    uint vs = shaderCompile(vertPath, GL_VERTEX_SHADER);
    uint fs = shaderCompile(fragPath, GL_FRAGMENT_SHADER);

	glCheck(glAttachShader(shader.id, vs));
	glCheck(glAttachShader(shader.id, fs));

	glCheck(glLinkProgram(shader.id));
	glCheck(glValidateProgram(shader.id));

    glCheck(glDetachShader(shader.id, vs));
    glCheck(glDetachShader(shader.id, fs));

    return shader;
}

void shaderDestroy(Shader shader)
{
    glCheck(glDeleteProgram(shader.id));
}

void shaderBind(Shader shader)
{
    glCheck(glUseProgram(shader.id));
}

void shaderUnbind(Shader shader)
{
    (void)shader;
    glCheck(glUseProgram(0));
}

void shaderSubmitInt(Shader shader, const char* loc, int val)
{
    shaderBind(shader);
    glCheck(glUniform1i(glGetUniformLocation(shader.id, loc), val));
}

void shaderSubmitUInt(Shader shader, const char* loc, uint val)
{
    shaderBind(shader);
    glCheck(glUniform1ui(glGetUniformLocation(shader.id, loc), val));
}

void shaderSubmitFloat(Shader shader, const char* loc, float val)
{
    shaderBind(shader);
    glCheck(glUniform1f(glGetUniformLocation(shader.id, loc), val));
}

void shaderSubmitVec2(Shader shader, const char* loc, v2 vec)
{
    shaderBind(shader);
    glCheck(glUniform2f(glGetUniformLocation(shader.id, loc), vec.x, vec.y));
}

void shaderSubmitVec3(Shader shader, const char* loc, v3 vec)
{
    shaderBind(shader);
    glCheck(glUniform3f(glGetUniformLocation(shader.id, loc), vec.x, vec.y, vec.z));
}

void shaderSubmitVec4(Shader shader, const char* loc, v4 vec)
{
    shaderBind(shader);
    glCheck(glUniform4f(glGetUniformLocation(shader.id, loc), vec.x, vec.y, vec.z, vec.w));
}

void shaderSubmitMat3(Shader shader, const char* loc, m3 mat)
{
    shaderBind(shader);
    glCheck(glUniformMatrix3fv(glGetUniformLocation(shader.id, loc), 1, GL_FALSE, &mat.m00));
}

void shaderSubmitMat4(Shader shader, const char* loc, m4 mat)
{
    shaderBind(shader);
    glCheck(glUniformMatrix4fv(glGetUniformLocation(shader.id, loc), 1, GL_FALSE, &mat.m00));
}

void shaderSubmitColor(Shader shader, const char* loc, c4 color)
{
    shaderBind(shader);
    glCheck(glUniform4i(glGetUniformLocation(shader.id, loc), color.r, color.g, color.b, color.a));
}

void shaderSubmitTexture(Shader shader, const char* loc, Texture tex)
{
    shaderBind(shader);
    glCheck(glUniform1i(glGetUniformLocation(shader.id, loc), tex.unit));
}

//- - - - - - - - - - - - - - -

static char* shaderParse(const char* srcPath)
{
    FILE* fp = fopen(srcPath, "r");

    if (!fp)
        return NULL;

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    rewind(fp);

    char* src = malloc(length * sizeof *src);

    if (!src)
        return NULL;

    fread(src, sizeof(char), length, fp);
    src[length] = '\0';

    fclose(fp);
    return src;
}

static uint shaderCompile(const char* srcPath, uint type)
{
    char* src = shaderParse(srcPath);

    glCheck(unsigned int id = glCreateShader(type));
    glCheck(glShaderSource(id, 1, (const GLchar* const *)&src, NULL));
    glCheck(glCompileShader(id));

    // Check if shader compiled successfully
    int compiled;
    glCheck(glGetShaderiv(id, GL_COMPILE_STATUS, &compiled));

    if (compiled == GL_FALSE)
    {
        char message[512];
        glCheck(glGetShaderInfoLog(id, 512, NULL, message));

        fprintf(stderr, "[%10s:%3d] [ERROR] [OPENGL] %s(): ", __FILE__, __LINE__, __func__);
        fprintf(stderr, "Failed to compile %s shader at %s!\n",
            type == GL_VERTEX_SHADER ? "vertex" : "fragment", srcPath);
        fprintf(stderr, "%s\n", message);

        glCheck(glDeleteShader(id));
        return 0;
    }

    free(src);
    return id;
}

//-----------------------------
// ~Texture

Texture textureCreate(const char* path)
{
    Texture tex;

    glCheck(glGenTextures(1, &tex.id));
	glCheck(glBindTexture(GL_TEXTURE_2D, tex.id));

    textureGenerate(&tex, path);

	static uint unit = 0;
	tex.unit = unit++;

    glCheck(glBindTexture(GL_TEXTURE_2D, tex.unit));

    return tex;
}

void textureGenerate(Texture* tex, const char* path)
{
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	stbi_set_flip_vertically_on_load(1);

    uchar* data = stbi_load(path, &tex->w, &tex->h, &tex->format, 0);

    if (!data)
        return;

    GLenum format = 0;
    switch (tex->format)
    {
        case 1: format = GL_RED;  break;
        case 3: format = GL_RGB;  break;
        case 4: format = GL_RGBA; break;
        default: 				  break;
    }

    glCheck(glTexImage2D(GL_TEXTURE_2D, 0, format, tex->w, tex->h, 0, format, GL_UNSIGNED_BYTE, data));

    stbi_image_free(data);
}

void textureDestroy(Texture tex)
{
    glCheck(glDeleteTextures(1, &tex.id));
}

void textureBind(Texture tex)
{
    glCheck(glActiveTexture(GL_TEXTURE0 + tex.unit));
    glCheck(glBindTexture(GL_TEXTURE_2D, tex.id));
}

void textureUnbind(Texture tex)
{
    (void)tex;
    glCheck(glBindTexture(GL_TEXTURE_2D, 0));
}
