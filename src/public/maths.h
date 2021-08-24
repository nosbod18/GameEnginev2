#ifndef MODULE_MATHS_H
#define MODULE_MATHS_H

//-------------------------------------------------------------
// Definitions
//-------------------------------------------------------------

#ifndef uchar
    #define uchar  unsigned char
    #define ushort unsigned int
    #define uint   unsigned int
    #define ulong  unsigned long
#endif // uchar

#ifndef PI
    #define PI       3.14159265358979323846264338327950
    #define TAU      6.28318530717958647692528676655901
    #define PI_2     1.57079632679489661923132169163975
    #define PI_4     0.78539816339744830961566084581988
    #define DEG2RAD  0.01745329251994329576923690768489
    #define RAD2DEG 57.29577951308232087679815481410517
#endif // PI

#ifndef MIN
    #define MIN(x_, y_)         ((x_) < (y_) ? (x_) : (y_))
    #define MAX(x_, y_)         ((x_) > (y_) ? (x_) : (y_))
    #define CLAMP(x_, lo_, hi_) (MAX(lo_, MIN(x_, hi_)))
    #define ABS(x_)             ((x_) < 0 ? -(x_) : (x_))
    #define FLOOR(x_)           ((int)(x_))
    #define CEIL(x_)            ((int)(x_) + 1)
    #define ROUND(x_)           ((x_) < 0.5 ? (int)(x_) : (int)(x_) + 1)
#endif // MIN

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

typedef v4 quat;

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

//-----------------------------
// 2D

typedef struct Line
{
    float x0, y0;
    float x1, y1;
} Line;

typedef struct Rect
{
    float x, y;
    float w, h;
} Rect;

typedef struct Circle
{
    float x, y;
    float r;
} Circle;

//-----------------------------
// 3D

typedef struct Plane
{
    float x, y, z;
    float n; // normal
} Plane;

typedef struct AABB
{
    float x, y, z;
    float w, h, d; // d is depth
} AABB;

typedef struct Sphere
{
    float x, y, z;
    float r;
} Sphere;

typedef struct Frustum
{
    Plane planes[6]; // Top -> bottom -> left -> right -> near -> far
} Frustum;

//-------------------------------------------------------------
// Prototypes
//-------------------------------------------------------------

//-----------------------------
// ~v2

v2      v2Add(v2 a, v2 b);
v2      v2Sub(v2 a, v2 b);
v2      v2Mul(v2 a, v2 b);
v2      v2Div(v2 a, v2 b);

v2      v2Addf(v2 a, float b);
v2      v2Subf(v2 a, float b);
v2      v2Mulf(v2 a, float b);
v2      v2Divf(v2 a, float b);

float   v2Mag2(v2 a);
float   v2Mag(v2 a);
float   v2Dot(v2 a, v2 b);

float   v2MinVal(v2 a);
float   v2MaxVal(v2 a);

v2      v2Min(v2 a, v2 b);
v2      v2Max(v2 a, v2 b);

void    v2Norm(v2* a);
v2      v2NormTo(v2 a);

void    v2Rotate(v2* a, float angle);
v2      v2RotateTo(v2 a, float angle);

//-----------------------------
// ~v3

v3      v3Add(v3 a, v3 b);
v3      v3Sub(v3 a, v3 b);
v3      v3Mul(v3 a, v3 b);
v3      v3Div(v3 a, v3 b);

v3      v3Addf(v3 a, float b);
v3      v3Subf(v3 a, float b);
v3      v3Mulf(v3 a, float b);
v3      v3Divf(v3 a, float b);

float   v3Mag2(v3 a);
float   v3Mag(v3 a);
float   v3Dot(v3 a, v3 b);

float   v3MinVal(v3 a);
float   v3MaxVal(v3 a);

v3      v3Min(v3 a, v3 b);
v3      v3Max(v3 a, v3 b);

void    v3Norm(v3* a);
v3      v3NormTo(v3 a);

v3      v3Cross(v3 a, v3 b);

//-----------------------------
// ~v4

v4 v4Add(v4 a, v4 b);
v4 v4Sub(v4 a, v4 b);
v4 v4Mul(v4 a, v4 b);
v4 v4Div(v4 a, v4 b);

v4 v4Addf(v4 a, float b);
v4 v4Subf(v4 a, float b);
v4 v4Mulf(v4 a, float b);
v4 v4Divf(v4 a, float b);

float v4Mag2(v4 a);
float v4Mag(v4 a);
float v4Dot(v4 a, v4 b);

float v4MinVal(v4 a);
float v4MaxVal(v4 a);

v4 v4Min(v4 a, v4 b);
v4 v4Max(v4 a, v4 b);

void v4Norm(v4* a);
v4   v4NormTo(v4 a);

//-----------------------------
// ~m3

m3 m3Identity(void);

m3 m3Add(m3 a, m3 b);
m3 m3Sub(m3 a, m3 b);
m3 m3Mul(m3 a, m3 b);
m3 m3Div(m3 a, m3 b);

m3 m3Addf(m3 a, float b);
m3 m3Subf(m3 a, float b);
m3 m3Mulf(m3 a, float b);
m3 m3Divf(m3 a, float b);

v3 m3Mulv3(m3 a, v3 b);

m3 m3Translate(m3 m, v2 t);
m3 m3TranslateX(m3 m, float x);
m3 m3TranslateY(m3 m, float y);

m3 m3Rotate(m3 m, float angle); // Can only rotate around the z axis

m3 m3Scale(m3 m, v2 s);
m3 m3ScaleX(m3 m, float x);
m3 m3ScaleY(m3 m, float y);

m3 m3Transform(m3 m, v2 t, float angle, v2 s);

//-----------------------------
// ~m4

m4 m4Identity(void);

m4 m4Add(m4 a, m4 b);
m4 m4Sub(m4 a, m4 b);
m4 m4Mul(m4 a, m4 b);
m4 m4Div(m4 a, m4 b);

m4 m4Addf(m4 a, float b);
m4 m4Subf(m4 a, float b);
m4 m4Mulf(m4 a, float b);
m4 m4Divf(m4 a, float b);

v3 m4Mulv3(m4 a, v3 b, float w);
v4 m4Mulv4(m4 a, v4 b);

m4 m4Translate(m4 m, v3 t);
m4 m4TranslateX(m4 m, float x);
m4 m4TranslateY(m4 m, float y);
m4 m4TranslateZ(m4 m, float z);

m4 m4Rotate(m4 m, v3 axis, float angle);
m4 m4RotateX(m4 m, float angle);
m4 m4RotateY(m4 m, float angle);
m4 m4RotateZ(m4 m, float angle);

m4 m4Scale(m4 m, v3 s);
m4 m4ScaleX(m4 m, float x);
m4 m4ScaleY(m4 m, float y);
m4 m4ScaleX(m4 m, float z);

m4 m4Transform(m4 m, v3 t, v3 axis, float angle, v3 s);

m4 m4LookAt(v3 eye, v3 target, v3 up);
m4 m4Perspective(float fov, float aspect, float near, float far);

m4 m4Frustum(float left, float right, float bottom, float top, float near, float far);
m4 m4Orthographic(float left, float right, float bottom, float top, float near, float far);

//-----------------------------
// ~Color

#define COLOR_LIGHTGRAY  (Color){ 200, 200, 200, 255 }
#define COLOR_GRAY       (Color){ 130, 130, 130, 255 }
#define COLOR_DARKGRAY   (Color){  80,  80,  80, 255 }
#define COLOR_YELLOW     (Color){ 253, 249,   0, 255 }
#define COLOR_GOLD       (Color){ 255, 203,   0, 255 }
#define COLOR_ORANGE     (Color){ 255, 161,   0, 255 }
#define COLOR_PINK       (Color){ 255, 109, 194, 255 }
#define COLOR_RED        (Color){ 230,  41,  55, 255 }
#define COLOR_MAROON     (Color){ 190,  33,  55, 255 }
#define COLOR_GREEN      (Color){   0, 228,  48, 255 }
#define COLOR_LIME       (Color){   0, 158,  47, 255 }
#define COLOR_DARKGREEN  (Color){   0, 117,  44, 255 }
#define COLOR_SKYBLUE    (Color){ 102, 191, 255, 255 }
#define COLOR_BLUE       (Color){   0, 121, 241, 255 }
#define COLOR_DARKBLUE   (Color){   0,  82, 172, 255 }
#define COLOR_PURPLE     (Color){ 200, 122, 255, 255 }
#define COLOR_VIOLET     (Color){ 135,  60, 190, 255 }
#define COLOR_DARKPURPLE (Color){ 112,  31, 126, 255 }
#define COLOR_BEIGE      (Color){ 211, 176, 131, 255 }
#define COLOR_BROWN      (Color){ 127, 106,  79, 255 }
#define COLOR_DARKBROWN  (Color){  76,  63,  47, 255 }

#endif // MODULE_MATHS_H