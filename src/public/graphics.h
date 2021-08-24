#ifndef MODULE_GRAPHICS_H
#define MODULE_GRAPHICS_H

#include <stdbool.h>

#ifndef uchar
    #define uchar  unsigned char
    #define ushort unsigned int
    #define uint   unsigned int
    #define ulong  unsigned long
#endif // uchar

#define MAX_BUFFER_VBOS 16
#define MAX_LAYOUT_ELEMENTS 16

//=============================================================
// Definitions
//=============================================================

// Define the vector and matrix types if they aren't already
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

    typedef struct Color
    {
        uchar r, g, b, a;
    } Color;

    typedef struct fColor
    {
        float r, g, b, a;
    } fColor;

#endif // MODULE_MATHS_H

//---------------------------------------------
// ~OpenGL

typedef struct VBOLayout
{
    struct
    {
        int type;
        uint size;
        uint offset;
        bool normalized;
    } elements[MAX_LAYOUT_ELEMENTS];

    uint stride;
} VBOLayout;

typedef struct VBO
{
    uint id;
    uint count;
    uint usage;
    VBOLayout layout;
} VBO;

typedef struct IBO
{
    uint id;
    uint count;
    uint usage;
} IBO;

typedef struct VAO
{
    uint id;

    VBO* vbos[MAX_BUFFER_VBOS];
    uint vboCount;

    IBO ibo;
} VAO;

typedef struct Shader
{
    uint id;
    int* locs;
} Shader;

typedef struct Texture
{
    uint id;
    int w, h;
    int mipmaps;
    int format;
} Texture;

//---------------------------------------------
// ~Mesh

typedef struct Vertex
{
    v3 pos;
    v2 texcoord;
    v2 texcoord2;
    v3 normal;
    Color color;
} Vertex;

typedef struct Mesh
{
    Vertex* verticies;
    uint vertexCount;
} Mesh;

//---------------------------------------------
// ~Renderer

typedef struct DrawCall
{
    int mode;
    uint vertexCount;
    VAO* vao;
    Texture* texture;

    m4 mvp;

} DrawCall;

typedef struct RenderBatch
{
    DrawCall* drawCalls;
    uint drawCallCount;
    float currentDepth;
} RenderBatch;

typedef struct Renderer
{
    RenderBatch* batches;
} Renderer;

//---------------------------------------------
// ~Enums


//=============================================================
// Prototypes
//=============================================================

//---------------------------------------------
// ~OpenGL

VAO*        vaoCreate(void);
void        vaoDestroy(VAO* vao);

void        vaoAddVBO(VAO* vao, VBO* vbo);
void        vaoSetIBO(VAO* vao, IBO ibo);
//- - - - - - - - - - - - - - -
VBO*        vboCreateStatic(const void* data, uint size);
VBO*        vboCreateDynamic(uint size);
void        vboDestroy(VBO* vbo);

void        vboBind(VBO* vbo);
void        vboUnbind(VBO* vbo);

void        vboSetLayout(VBO* vbo, VBOLayout layout);
void        vboSubmitData(const void* data, uint size);
//- - - - - - - - - - - - - - -
IBO         iboCreateStatic(const uint* data, uint size);
void        iboCreateDynamic(uint size);

void        iboBind(IBO ibo);
void        iboUnbind(IBO ibo);

void        iboSubmitData(const uint* data, uint size);
//- - - - - - - - - - - - - - -
Shader      shaderCreate(const char* vertPath, const char* fragPath);
void        shaderDestroy(Shader shader);

void        shaderBind(Shader shader);
void        shaderUnbind(Shader shader);

void        shaderUploadChar(Shader shader,  const char* loc, char val);
void        shaderUploadUChar(Shader shader, const char* loc, uchar val);
void        shaderUploadInt(Shader shader,   const char* loc, int val);
void        shaderUploadUInt(Shader shader,  const char* loc, uint val);
void        shaderUploadFloat(Shader shader, const char* loc, float val);
void        shaderUploadVec2(Shader shader,  const char* loc, v2 vec);
void        shaderUploadVec3(Shader shader,  const char* loc, v3 vec);
void        shaderUploadVec4(Shader shader,  const char* loc, v4 vec);
void        shaderUploadMat3(Shader shader,  const char* loc, m3 mat);
void        shaderUploadMat4(Shader shader,  const char* loc, m4 mat);

void        shaderUploadTexture(Shader shader, const char* loc, Texture tex);
void        shaderUploadColor(Shader shader, const char* loc, Color color);
//- - - - - - - - - - - - - - -
Texture     textureCreate(const char* path);
void        textureDestroy(Texture tex);

void        textureBind(Texture tex);
void        textureUnbind(Texture tex);

void        textureSetData(Texture tex, const void* data, uint size);

//---------------------------------------------
// ~Renderer

#endif // MODULE_GRAPHICS_H