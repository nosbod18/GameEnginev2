#ifndef MODULE_GRAPHICS_H
#define MODULE_GRAPHICS_H

#ifndef uchar
    #define uchar  unsigned char
    #define ushort unsigned int
    #define uint   unsigned int
    #define ulong  unsigned long
    #define bool   unsigned char
#endif // uchar

//=============================================================
// Definitions
//=============================================================

// Define the vector and matrix types if they haven't been already
#ifndef MODULE_MATHS_H

    typedef struct v2 {
        float x;
        float y;
    } v2;

    typedef struct v3 {
        float x;
        float y;
        float z;
    } v3;

    typedef struct v4 {
        float x;
        float y;
        float z;
        float w;
    } v4;

    typedef struct iv2 {
        int x;
        int y;
    } iv2;

    typedef struct iv3 {
        int x;
        int y;
        int z;
    } iv3;

    typedef struct iv4 {
        int x;
        int y;
        int z;
        int w;
    } iv4;

    typedef struct m3 {
        float m00, m10, m20;
        float m01, m11, m21;
        float m02, m12, m22;
    } m3;

    typedef struct m4 {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    } m4;

    typedef struct c4 {
        uchar r;
        uchar g;
        uchar b;
        uchar a;
    } c4;

#endif // MODULE_MATHS_H

//-----------------------------
// ~VBO

typedef struct {
    struct {
        uint index;
        uint stride;
        uint offset;
    } layout;

    uint id;
} VBO;

//-----------------------------
// ~IBO

typedef struct {
    uint count;
    uint id;
} IBO;

//-----------------------------
// ~VAO

typedef struct {
    VBO vbos[8];
    uint vboCount;

    IBO ibo;
    uint id;
} VAO;

//-----------------------------
// ~Shader

typedef struct {
    int* locs;
    uint id;
} Shader;

//-----------------------------
// ~Texture

typedef struct {
    int  width;
    int  height;
    int  mipmaps;
    int  format;
    uint unit;
    uint id;
} Texture;

//-----------------------------
// ~Material

typedef struct {
    Texture* normalMap;
    Texture* ambientMap;
    Texture* diffuseMap;
    Texture* specularMap;

    v3 ambient;
	v3 diffuse;
	v3 specular;
	v3 emission;
	v3 transmittance;

	const char* name;

	bool  isTextured;
	float shininess;
	float refractiveIndex;
} Material;

//-----------------------------
// ~Mesh

typedef struct {
    v3*   vertices;
    uint* indices;
    v4*   colors;
    v2*   uvs;

    Material* material;

    uint vao;
    uint vbo;
    uint ibo;
} Mesh;

//-----------------------------
// ~Model

typedef struct {
    m4 transform;
    Mesh* meshes;
    const char* path;
} Model;

//-----------------------------
// ~Renderer


//-----------------------------
// ~Enums and other defines

typedef enum DrawMode {
    STATIC_DRAW     = 0x88E4, // GL_STATIC_DRAW
    DYNAMIC_DRAW    = 0x88E8, // GL_DYNAMIC_DRAW
    STREAM_DRAW     = 0x88E0  // GL_STREAM_DRAW
} DrawMode;

//=============================================================
// Prototypes
//=============================================================

//-----------------------------
// ~VBO

VBO         vboCreate(const void* data, uint size, uint stride, DrawMode mode);
void        vboDestroy(VBO vbo);

void        vboBind(VBO vbo);
void        vboUnbind(VBO vbo);

void        vboPushAttribute(VBO vbo, int type, int count, int normalized);
void        vboPushData(VBO vbo, const void* data, uint size);
void        vboSetData(VBO vbo, const void* data, uint size);

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

void        vaoPushVbo(VAO* vao, VBO vbo);
void        vaoSetIbo(VAO* vao, IBO ibo);

//-----------------------------
// ~Shader

Shader      shaderCreate(const char* vertPath, const char* fragPath);
Shader      shaderCreateFromSrc(const char* vertSrc, const char* fragSrc);
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
// ~Material

Material*   materialCreate(const char* path);
void        materialDestroy(Material* material);

//-----------------------------
// ~Mesh

Mesh*       meshCreate(v3* vertices, uint* indices, v4* colors, v2* uvs);
void        meshDestroy(Mesh* mesh);

//-----------------------------
// ~Model

Model*      modelCreate(const char* path);
void        modelDestroy(Model* model);

void        modelTranslate(Model* model, v3 pos);
void        modelRotate(Model* model, v3 axis, float angle);
void        modelScale(Model* model, v3 scale);
void        modelScaleUni(Model* model, float scale);

//-----------------------------
// ~Renderer

#endif // MODULE_GRAPHICS_H
