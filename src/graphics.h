#ifndef SRC_GRAPHICS_H
#define SRC_GRAPHICS_H
#ifndef MODULE_GRAPHICS_H
#define MODULE_GRAPHICS_H

#include <stdbool.h>

#ifndef uchar
    #define uchar  unsigned char
    #define ushort unsigned int
    #define uint   unsigned int
    #define ulong  unsigned long
#endif // uchar

#define MAX_VAO_VBOS 16

//=============================================================
// Definitions
//=============================================================

// Define the vector and matrix types if they haven't been already
#ifndef MODULE_MATHS_H

    typedef struct v2
    {
        float x, y;
    } v2;

    typedef struct v3
    {
        float x, y, z;
    } v3;

    typedef struct v4
    {
        float x, y, z, w;
    } v4;

    typedef struct iv2
    {
        int x, y;
    } iv2;

    typedef struct iv3
    {
        int x, y, z;
    } iv3;

    typedef struct iv4
    {
        int x, y, z, w;
    } iv4;

    typedef struct m3
    {
        float m00, m10, m20;
        float m01, m11, m21;
        float m02, m12, m22;
    } m3;

    typedef struct m4
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    } m4;

    typedef struct c4
    {
        uchar r, g, b, a;
    } c4;

#endif // MODULE_MATHS_H

//-----------------------------
// ~VBO

typedef struct VBO
{
    struct {
        uint index;
        uint stride;
        uint offset;
    } layout;

    uint id;
} VBO;

//-----------------------------
// ~IBO

typedef struct IBO
{
    uint count;
    uint id;
} IBO;

//-----------------------------
// ~VAO

typedef struct VAO
{
    VBO vbos[MAX_VAO_VBOS];
    uint vboCount;
    uint vboIndex;

    IBO ibo;

    uint id;
} VAO;

//-----------------------------
// ~Shader

typedef struct Shader
{
    int* locs;
    uint id;
} Shader;

//-----------------------------
// ~Texture

typedef struct Texture
{
    int  w;
    int  h;
    int  mipmaps;
    int  format;
    uint unit;
    uint id;
} Texture;

//-----------------------------
// ~Mesh

typedef struct Vertex
{
    v3 pos;
    v2 texcoord;
    c4 color;
} Vertex;

typedef struct Mesh
{
    Vertex* vertices;
    uint vertexCount;
} Mesh;

//-----------------------------
// ~Model


//-----------------------------
// ~Renderer


//-----------------------------
// ~Enums

typedef enum DataType
{
    DATA_TYPE_BYTE = 0,
    DATA_TYPE_UBYTE,
    DATA_TYPE_INT,
    DATA_TYPE_INT2,
    DATA_TYPE_INT3,
    DATA_TYPE_INT4,
    DATA_TYPE_UINT,
    DATA_TYPE_FLOAT,
    DATA_TYPE_FLOAT2,
    DATA_TYPE_FLOAT3,
    DATA_TYPE_FLOAT4,
} DataType;

typedef enum DrawMode
{
    STATIC_DRAW     = 0x88E4, // GL_STATIC_DRAW
    DYNAMIC_DRAW    = 0x88E8, // GL_DYNAMIC_DRAW
    STREAMING_DRAW  = 0x88E0  // GL_STREAM_DRAW
} DrawMode;

//=============================================================
// Prototypes
//=============================================================

//-----------------------------
// ~VBO

VBO         vboCreate(const void* data, uint size, DrawMode mode, uint stride);
void        vboDestroy(VBO vbo);

void        vboBind(VBO vbo);
void        vboUnbind(VBO vbo);

void        vboPushLayout(VBO vbo, const char* name, uint type, bool normalized);
void        vboSubmitData(VBO vbo, const void* data, uint size, uint offset);

//-----------------------------
// ~IBO

IBO         iboCreate(const void* data, uint size, DrawMode mode);
void        iboDestroy(IBO ibo);

void        iboBind(IBO ibo);
void        iboUnbind(IBO ibo);

void        iboSubmitData(IBO ibo, const void* data, uint size, uint offset);

//-----------------------------
// ~VAO

VAO*        vaoCreate(void);
void        vaoDestroy(VAO* vao);

void        vaoBind(VAO* vao);
void        vaoUnbind(VAO* vao);

void        vaoAttachVbo(VAO* vao, VBO vbo);
void        vaoSetIbo(VAO* vao, IBO ibo);

//-----------------------------
// ~Shader

Shader      shaderCreate(const char* vertPath, const char* fragPath);
void        shaderDestroy(Shader shader);

void        shaderBind(Shader shader);
void        shaderUnbind(Shader shader);

void        shaderSubmitInt(Shader shader,   const char* loc, int val);
void        shaderSubmitUInt(Shader shader,  const char* loc, uint val);
void        shaderSubmitFloat(Shader shader, const char* loc, float val);
void        shaderSubmitVec2(Shader shader,  const char* loc, v2 vec);
void        shaderSubmitVec3(Shader shader,  const char* loc, v3 vec);
void        shaderSubmitVec4(Shader shader,  const char* loc, v4 vec);
void        shaderSubmitMat3(Shader shader,  const char* loc, m3 mat);
void        shaderSubmitMat4(Shader shader,  const char* loc, m4 mat);

void        shaderSubmitColor(Shader shader, const char* loc, c4 color);
void        shaderSubmitTexture(Shader shader, const char* loc, Texture tex);

//-----------------------------
// ~Texture

Texture     textureCreate(const char* path);
void        textureGenerate(Texture* tex, const char* path);
void        textureDestroy(Texture tex);

void        textureBind(Texture tex);
void        textureUnbind(Texture tex);

//-----------------------------
// ~Mesh


//-----------------------------
// ~Model

//-----------------------------
// ~Renderer

#endif // MODULE_GRAPHICS_H


#endif /* SRC_GRAPHICS_H */
