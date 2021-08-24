#include "public/maths.h"
#include <math.h> // sqrt, sin, cos, tan

//-----------------------------
// ~v2

v2 v2Add(v2 a, v2 b)
{
    return (v2){a.x + b.x, a.y + b.y};
}

v2 v2Sub(v2 a, v2 b)
{
    return (v2){a.x - b.x, a.y - b.y};
}

v2 v2Mul(v2 a, v2 b)
{
    return (v2){a.x * b.x, a.y * b.y};
}

v2 v2Div(v2 a, v2 b)
{
    return (v2){a.x / b.x, a.y / b.y};
}

v2 v2Addf(v2 a, float b)
{
    return (v2){a.x + b, a.y + b};
}

v2 v2Subf(v2 a, float b)
{
    return (v2){a.x - b, a.y - b};
}

v2 v2Mulf(v2 a, float b)
{
    return (v2){a.x * b, a.y * b};
}

v2 v2Divf(v2 a, float b)
{
    return (v2){a.x / b, a.y / b};
}


float v2Mag2(v2 a)
{
    return a.x * a.x + a.y * a.y;
}

float v2Mag(v2 a)
{
    return sqrtf(v2Mag2(a));
}

float v2Dot(v2 a, v2 b)
{
    return a.x * b.x + a.y * b.y;
}

float v2MinVal(v2 a)
{
    return MIN(a.x, a.y);
}

float v2MaxVal(v2 a)
{
    return MAX(a.x, a.y);
}

v2 v2Min(v2 a, v2 b)
{
    return (v2){MIN(a.x, b.x), MIN(a.y, b.y)};
}

v2 v2Max(v2 a, v2 b)
{
    return (v2){MAX(a.x, b.x), MAX(a.y, b.y)};
}

void v2Norm(v2* a)
{
    *a = v2Divf(*a, v2Mag(*a));
}

v2 v2NormTo(v2 a)
{
    return v2Divf(a, v2Mag(a));
}

void v2Rotate(v2* a, float angle)
{
    a->x = a->x * cosf(angle) - a->y * sinf(angle);
    a->y = a->x * sinf(angle) - a->y * cosf(angle);
}

v2 v2RotateTo(v2 a, float angle)
{
    return (v2) {
        a.x * cosf(angle) - a.y * sinf(angle),
        a.x * sinf(angle) - a.y * cosf(angle)
    };
}

//-----------------------------
// ~v3

v3 v3Add(v3 a, v3 b)
{
    return (v3){a.x + b.x, a.y + b.y, a.z + b.z};
}

v3 v3Sub(v3 a, v3 b)
{
    return (v3){a.x - b.x, a.y - b.y, a.z - b.z};
}

v3 v3Mul(v3 a, v3 b)
{
    return (v3){a.x * b.x, a.y * b.y, a.z * b.z};
}

v3 v3Div(v3 a, v3 b)
{
    return (v3){a.x / b.x, a.y / b.y, a.z / b.z};
}

v3 v3Addf(v3 a, float b)
{
    return (v3){a.x + b, a.y + b, a.z + b};
}

v3 v3Subf(v3 a, float b)
{
    return (v3){a.x - b, a.y - b, a.z - b};
}

v3 v3Mulf(v3 a, float b)
{
    return (v3){a.x * b, a.y * b, a.z * b};
}

v3 v3Divf(v3 a, float b)
{
    return (v3){a.x / b, a.y / b, a.z / b};
}

float v3Mag2(v3 a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

float v3Mag(v3 a)
{
    return sqrtf(v3Mag2(a));
}

float v3Dot(v3 a, v3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float v3MinVal(v3 a)
{
    return MIN(MIN(a.x, a.y), a.z);
}

float v3MaxVal(v3 a)
{
    return MAX(MAX(a.x, a.y), a.z);
}

v3 v3Min(v3 a, v3 b)
{
    return (v3) {
        MIN(a.x, b.x),
        MIN(a.y, b.y),
        MIN(a.z, b.z)
    };
}

v3 v3Max(v3 a, v3 b)
{
    return (v3) {
        MAX(a.x, b.x),
        MAX(a.y, b.y),
        MAX(a.z, b.z)
    };
}

void v3Norm(v3* a)
{
    *a = v3Divf(*a, v3Mag2(*a));
}

v3 v3NormTo(v3 a)
{
    return v3Divf(a, v3Mag2(a));
}

v3 v3Cross(v3 a, v3 b)
{
    return (v3) {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.z * b.z,
        a.x * b.y - a.y * b.x
    };
}

//-----------------------------
// ~v4

v4 v4Add(v4 a, v4 b)
{
    return (v4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

v4 v4Sub(v4 a, v4 b)
{
    return (v4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

v4 v4Mul(v4 a, v4 b)
{
    return (v4){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

v4 v4Div(v4 a, v4 b)
{
    return (v4){a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

v4 v4Addf(v4 a, float b)
{
    return (v4){a.x + b, a.y + b, a.z + b, a.w + b};
}

v4 v4Subf(v4 a, float b)
{
    return (v4){a.x - b, a.y - b, a.z - b, a.w - b};
}

v4 v4Mulf(v4 a, float b)
{
    return (v4){a.x * b, a.y * b, a.z * b, a.w * b};
}

v4 v4Divf(v4 a, float b)
{
    return (v4){a.x / b, a.y / b, a.z / b, a.w / b};
}

float v4Mag2(v4 a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

float v4Mag(v4 a)
{
    return sqrtf(v4Mag2(a));
}

float v4Dot(v4 a, v4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float v4MinVal(v4 a)
{
    return MIN(MIN(MIN(a.x, a.y), a.z), a.w);
}

float v4MaxVal(v4 a)
{
    return MAX(MAX(MAX(a.x, a.y), a.z), a.w);
}

v4 v4Min(v4 a, v4 b)
{
    return (v4) {
        MIN(a.x, b.x),
        MIN(a.y, b.y),
        MIN(a.z, b.z),
        MIN(a.w, b.w),
    };
}

v4 v4Max(v4 a, v4 b)
{
    return (v4) {
        MAX(a.x, b.x),
        MAX(a.y, b.y),
        MAX(a.z, b.z),
        MAX(a.w, b.w),
    };
}

void v4Norm(v4* a)
{
    *a = v4Divf(*a, v4Mag2(*a));
}

v4 v4NormTo(v4 a)
{
    return v4Divf(a, v4Mag2(a));
}

//-----------------------------
// ~m3

m3 m3Identity(void)
{
    return (m3) {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
}

m3 m3Add(m3 a, m3 b)
{
    return (m3) {
        a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02,
        a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12,
        a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22
    };
}

m3 m3Sub(m3 a, m3 b)
{
    return (m3) {
        a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02,
        a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12,
        a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22
    };
}

m3 m3Mul(m3 a, m3 b)
{
    return (m3) {
        a.m00 * b.m00, a.m01 * b.m01, a.m02 * b.m02,
        a.m10 * b.m10, a.m11 * b.m11, a.m12 * b.m12,
        a.m20 * b.m20, a.m21 * b.m21, a.m22 * b.m22
    };
}

m3 m3Div(m3 a, m3 b)
{
    return (m3) {
        a.m00 / b.m00, a.m01 / b.m01, a.m02 / b.m02,
        a.m10 / b.m10, a.m11 / b.m11, a.m12 / b.m12,
        a.m20 / b.m20, a.m21 / b.m21, a.m22 / b.m22
    };
}

m3 m3Addf(m3 a, float b)
{
    return (m3) {
        a.m00 + b, a.m01 + b, a.m02 + b,
        a.m10 + b, a.m11 + b, a.m12 + b,
        a.m20 + b, a.m21 + b, a.m22 + b
    };
}

m3 m3Subf(m3 a, float b)
{
    return (m3) {
        a.m00 - b, a.m01 - b, a.m02 - b,
        a.m10 - b, a.m11 - b, a.m12 - b,
        a.m20 - b, a.m21 - b, a.m22 - b
    };
}

m3 m3Mulf(m3 a, float b)
{
    return (m3) {
        a.m00 * b, a.m01 * b, a.m02 * b,
        a.m10 * b, a.m11 * b, a.m12 * b,
        a.m20 * b, a.m21 * b, a.m22 * b
    };
}

m3 m3Divf(m3 a, float b)
{
    return (m3) {
        a.m00 / b, a.m01 / b, a.m02 / b,
        a.m10 / b, a.m11 / b, a.m12 / b,
        a.m20 / b, a.m21 / b, a.m22 / b
    };
}

v3 m3Mulv3(m3 a, v3 b)
{
    return (v3) {
        a.m00 * b.x + a.m10 * b.y + a.m20 * b.z,
        a.m01 * b.x + a.m11 * b.y + a.m21 * b.z,
        a.m02 * b.x + a.m12 * b.y + a.m22 * b.z
    };
}

m3 m3Translate(m3 m, v2 t)
{
    m3 out = m;
    out.m20 = m.m00 * t.x + m.m10 * t.y + m.m20;
    out.m21 = m.m01 * t.x + m.m11 * t.y + m.m21;
    out.m22 = m.m02 * t.x + m.m12 * t.y + m.m22;
    return out;
}

m3 m3TranslateX(m3 m, float x)
{
    m3 out = m;
    out.m20 = m.m00 * x + m.m20;
    out.m21 = m.m01 * x + m.m21;
    out.m22 = m.m02 * x + m.m22;
    return out;
}

m3 m3TranslateY(m3 m, float y)
{
    m3 out = m;
    out.m20 = m.m10 * y + m.m20;
    out.m21 = m.m11 * y + m.m21;
    out.m22 = m.m12 * y + m.m22;
    return out;
}

m3 m3Rotate(m3 m, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);

    m3 out = m;

    out.m00 = m.m00 * c + m.m10 * s;
    out.m01 = m.m01 * c + m.m11 * s;
    out.m02 = m.m02 * c + m.m12 * s;

    out.m10 = m.m00 * -s + m.m10 * c;
    out.m11 = m.m01 * -s + m.m11 * c;
    out.m12 = m.m02 * -s + m.m12 * c;

    return out;
}

m3 m3Scale(m3 m, v2 s)
{
    m3 out = m;
    out.m00 *= s.x;
    out.m01 *= s.x;
    out.m02 *= s.x;
    out.m10 *= s.y;
    out.m11 *= s.y;
    out.m21 *= s.y;
    return out;
}

m3 m3ScaleX(m3 m, float x)
{
    m3 out = m;
    out.m00 *= x;
    out.m01 *= x;
    out.m02 *= x;
    return out;
}

m3 m3ScaleY(m3 m, float y)
{
    m3 out = m;
    out.m10 *= y;
    out.m11 *= y;
    out.m12 *= y;
    return out;
}

m3 m3Transform(m3 m, v2 t, float angle, v2 s)
{
    m3 mt = m3Translate(m, t);
    m3 mr = m3Rotate(m, angle);
    m3 ms = m3Scale(m, s);

    return m3Mul(m3Mul(ms, mr), mt);
}

//-----------------------------
// ~m4

m4 m4Identity(void)
{
    return (m4) {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

m4 m4Add(m4 a, m4 b)
{
    return (m4) {
        a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03,
        a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
        a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
        a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33
    };
}

m4 m4Sub(m4 a, m4 b)
{
    return (m4) {
        a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03,
        a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
        a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
        a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33
    };
}

m4 m4Mul(m4 a, m4 b)
{
    return (m4) {
        a.m00 * b.m00, a.m01 * b.m01, a.m02 * b.m02, a.m03 * b.m03,
        a.m10 * b.m10, a.m11 * b.m11, a.m12 * b.m12, a.m13 * b.m13,
        a.m20 * b.m20, a.m21 * b.m21, a.m22 * b.m22, a.m23 * b.m23,
        a.m30 * b.m30, a.m31 * b.m31, a.m32 * b.m32, a.m33 * b.m33
    };
}

m4 m4Div(m4 a, m4 b)
{
    return (m4) {
        a.m00 / b.m00, a.m01 / b.m01, a.m02 / b.m02, a.m03 / b.m03,
        a.m10 / b.m10, a.m11 / b.m11, a.m12 / b.m12, a.m13 / b.m13,
        a.m20 / b.m20, a.m21 / b.m21, a.m22 / b.m22, a.m23 / b.m23,
        a.m30 / b.m30, a.m31 / b.m31, a.m32 / b.m32, a.m33 / b.m33
    };
}

m4 m4Addf(m4 a, float b)
{
    return (m4) {
        a.m00 + b, a.m01 + b, a.m02 + b, a.m03 + b,
        a.m10 + b, a.m11 + b, a.m12 + b, a.m13 + b,
        a.m20 + b, a.m21 + b, a.m22 + b, a.m23 + b,
        a.m30 + b, a.m31 + b, a.m32 + b, a.m33 + b
    };
}

m4 m4Subf(m4 a, float b)
{
    return (m4) {
        a.m00 - b, a.m01 - b, a.m02 - b, a.m03 - b,
        a.m10 - b, a.m11 - b, a.m12 - b, a.m13 - b,
        a.m20 - b, a.m21 - b, a.m22 - b, a.m23 - b,
        a.m30 - b, a.m31 - b, a.m32 - b, a.m33 - b
    };
}

m4 m4Mulf(m4 a, float b)
{
    return (m4) {
        a.m00 * b, a.m01 * b, a.m02 * b, a.m03 * b,
        a.m10 * b, a.m11 * b, a.m12 * b, a.m13 * b,
        a.m20 * b, a.m21 * b, a.m22 * b, a.m23 * b,
        a.m30 * b, a.m31 * b, a.m32 * b, a.m33 * b
    };
}

m4 m4Divf(m4 a, float b)
{
    return (m4) {
        a.m00 / b, a.m01 / b, a.m02 / b, a.m03 / b,
        a.m10 / b, a.m11 / b, a.m12 / b, a.m13 / b,
        a.m20 / b, a.m21 / b, a.m22 / b, a.m23 / b,
        a.m30 / b, a.m31 / b, a.m32 / b, a.m33 / b
    };
}

v3 m4Mulv3(m4 a, v3 b, float w)
{
    v4 c = m4Mulv4(a, (v4){b.x, b.y, b.z, w});
    return (v3){c.x, c.y, c.z};
}

v4 m4Mulv4(m4 a, v4 b)
{
    return (v4) {
        a.m00 * b.x + a.m10 * b.y + a.m20 * b.z + a.m30 * b.w,
        a.m01 * b.x + a.m11 * b.y + a.m21 * b.z + a.m31 * b.w,
        a.m02 * b.x + a.m12 * b.y + a.m22 * b.z + a.m32 * b.w,
        a.m03 * b.x + a.m13 * b.y + a.m23 * b.z + a.m33 * b.w
    };
}

m4 m4Translate(m4 m, v3 t)
{
    m4 out = m;

    out.m00 += m.m00 * t.x;
    out.m02 += m.m02 * t.x;
    out.m03 += m.m03 * t.x;

    out.m10 += m.m00 * t.y;
    out.m12 += m.m02 * t.y;
    out.m13 += m.m03 * t.y;

    out.m20 += m.m00 * t.z;
    out.m22 += m.m02 * t.z;
    out.m23 += m.m03 * t.z;

    return out;
}

m4 m4TranslateX(m4 m, float x)
{
    m4 out = m;

    out.m30 += m.m00 * x;
    out.m31 += m.m01 * x;
    out.m32 += m.m02 * x;
    out.m33 += m.m03 * x;

    return out;
}

m4 m4TranslateY(m4 m, float y)
{
    m4 out = m;

    out.m30 += m.m10 * y;
    out.m31 += m.m11 * y;
    out.m32 += m.m12 * y;
    out.m33 += m.m13 * y;

    return out;
}

m4 m4TranslateZ(m4 m, float z)
{
    m4 out = m;

    out.m30 += m.m20 * z;
    out.m31 += m.m21 * z;
    out.m32 += m.m22 * z;
    out.m33 += m.m23 * z;

    return out;
}

// http://fastgraph.com/makegames/3drotation/
m4 m4Rotate(m4 m, v3 axis, float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;

    v3Norm(&axis);

    v3 at = v3Mulf(axis, t);
    v3 as = v3Mulf(axis, s);

    m4 rot = {0};

    rot.m00 = axis.x * at.x + c;
    rot.m01 = axis.y * at.x + as.z;
    rot.m02 = axis.z * at.x - as.y;

    rot.m10 = axis.x * at.y - as.z;
    rot.m11 = axis.y * at.y + c;
    rot.m12 = axis.z * at.y + as.x;

    rot.m20 = axis.x * at.z + as.y;
    rot.m21 = axis.y * at.z + as.x;
    rot.m22 = axis.z * at.z + c;

    rot.m33 = 1.0f;

    return m4Mul(m, rot);
}

m4 m4RotateX(m4 m, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);

    m4 rot = m4Identity();
    rot.m11 =  c;
    rot.m12 =  s;
    rot.m21 = -s;
    rot.m22 =  c;
    return m4Mul(m, rot);
}

m4 m4RotateY(m4 m, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);

    m4 rot = m4Identity();
    rot.m00 =  c;
    rot.m02 = -s;
    rot.m20 =  s;
    rot.m22 =  c;
    return m4Mul(m, rot);
}

m4 m4RotateZ(m4 m, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);

    m4 rot = m4Identity();
    rot.m00 =  c;
    rot.m01 =  s;
    rot.m10 = -s;
    rot.m11 =  c;
    return m4Mul(m, rot);
}

m4 m4Scale(m4 m, v3 s)
{
    m4 out = m;
    out.m00 *= s.x;
    out.m01 *= s.x;
    out.m02 *= s.x;
    out.m10 *= s.y;
    out.m11 *= s.y;
    out.m12 *= s.y;
    out.m20 *= s.z;
    out.m21 *= s.z;
    out.m22 *= s.z;
    return out;
}

m4 m4ScaleX(m4 m, float x)
{
    m4 out = m;
    out.m00 *= x;
    out.m01 *= x;
    out.m02 *= x;
    return out;
}

m4 m4ScaleY(m4 m, float y)
{
    m4 out = m;
    out.m10 *= y;
    out.m11 *= y;
    out.m12 *= y;
    return out;
}

m4 m4ScaleX(m4 m, float z)
{
    m4 out = m;
    out.m20 *= z;
    out.m21 *= z;
    out.m22 *= z;
    return out;
}

m4 m4Transform(m4 m, v3 t, v3 axis, float angle, v3 s)
{
    m4 mt = m4Translate(m, t);
    m4 mr = m4Rotate(m, axis, angle);
    m4 ms = m4Scale(m, s);

    return m4Mul(m4Mul(ms, mr), mt);
}

m4 m4LookAt(v3 eye, v3 target, v3 up)
{
    v3 f = v3NormTo(v3Sub(target, eye));
    v3 r = v3NormTo(v3Cross(f, up));
    v3 u = v3Cross(r, f);

    return (m4){
        r.x           , u.x           , -f.x          , 0.0f,
        r.y           , u.y           , -f.y          , 0.0f,
        r.z           , u.z           , -f.z          , 0.0f,
        -v3Dot(r, eye), -v3Dot(u, eye), -v3Dot(f, eye), 1.0f
    };
}

m4 m4Perspective(float fov, float aspect, float near, float far)
{
    float fovRad = 1.0f / tanf(fov * DEG2RAD * 0.5f);
    float nf = 1.0f / (near - far);

    m4 out = {0};
    out.m00 =  fovRad / aspect;
    out.m11 =  fovRad;
    out.m22 =  (near + far) * nf;
    out.m23 = -1.0f;
    out.m32 =  2.0f * near * far * nf;
    return out;
}

m4 m4Frustum(float left, float right, float bottom, float top, float near, float far)
{
    float rl =  1.0f / (right - left);
    float tb =  1.0f / (top   - bottom);
    float fn = -1.0f / (far   - near);
    float n2 =  2.0f * near;

    m4 out = {0};
    out.m00 = n2 * rl;
    out.m11 = n2 * tb;
    out.m20 = (right + left) * rl;
    out.m21 = (top + bottom) * tb;
    out.m22 = (far + near)   * fn;
    out.m23 = -1.0f;
    out.m32 = far * n2 * fn;
    return out;
}

m4 m4Orthographic(float left, float right, float bottom, float top, float near, float far)
{
    float rl =  1.0f / (right - left);
    float tb =  1.0f / (top   - bottom);
    float fn = -1.0f / (far   - near);

    m4 out = {0};
    out.m00 =  2.0f * rl;
    out.m11 =  2.0f * tb;
    out.m22 =  2.0f * fn;
    out.m30 = -(right + left) * rl;
    out.m31 = -(top + bottom) * tb;
    out.m32 =  (far + near)   * fn;
    out.m33 =  1.0f;
    return out;
}