#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <algorithm>
#include "solver.h"
#include "Graphics.h"
using namespace std;

// Vec3D
vec3D::vec3D()
{
    x = y = z = 0;
}
vec3D::vec3D(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}

float vec3D::Vector_Length() const
{
    return sqrtf(x * x + y * y + z * z);
}
vec3D vec3D::Vector_Normalize()
{
    vec3D v(0, 0, 0);
    v.x = (this->x) / Vector_Length();
    v.y = (this->y) / Vector_Length();
    v.z = (this->z) / Vector_Length();
    return v;
}
float vec3D::Vector_DotProduct(const vec3D& v2)
{
    return (x * v2.x + y * v2.y + z * v2.z);
}
float vec3D::Vector_DotProduct(const vec3D& v1, const vec3D& v2)
{
    return (v1.x * v2.x + v1.x * v2.y + v1.z * v2.z);
}
vec3D vec3D::Vector_CrossProduct(vec3D& v1, vec3D& v2)
{
    vec3D v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}
vec3D vec3D::Vector_CrossProduct(vec3D& v2)
{
    vec3D v;
    v.x = y * v2.z - z * v2.y;
    v.y = z * v2.x - x * v2.z;
    v.z = x * v2.y - y * v2.x;
    return v;
}

// Operator overloading:
vec3D& vec3D::operator+=(const vec3D& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}
vec3D& vec3D::operator-=(const vec3D& rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}
vec3D& vec3D::operator*=(const float& rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}
vec3D& vec3D::operator/=(const float& rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}
vec3D vec3D::operator+(const vec3D& rhs)
{
    vec3D v(0, 0, 0);
    v.x = this->x + rhs.x;
    v.y = this->y + rhs.y;
    v.z = this->z + rhs.z;
    return v;
}
vec3D vec3D::operator-(const vec3D& rhs)
{
    vec3D v(0, 0, 0);
    v.x = this->x - rhs.x;
    v.y = this->y - rhs.y;
    v.z = this->z - rhs.z;
    return v;
}
vec3D vec3D::operator*(const float& rhs)
{
    vec3D v = { 0, 0, 0 };
    v.x = this->x * rhs;
    v.y = this->y * rhs;
    v.z = this->z * rhs;
    return v;
}
vec3D vec3D::operator/(const float& rhs)
{
    vec3D v(0, 0, 0);
    v.x = this->x / rhs;
    v.y = this->y / rhs;
    v.z = this->z / rhs;
    return v;
}
bool vec3D::operator==(const vec3D rhs)
{
    if (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z)
    {
        return 1;
    }
    else
        return 0;
}

// 4x4 matrix

// Creates Identity matrix
mat4x4 mat4x4::Matrix_MakeIdentity()
{
    mat4x4 matrix;
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;
    return matrix;
}
// The following create a counter-clockwise X/Y/Z-rotation transformation on a vertice
mat4x4 mat4x4::Matrix_MakeRotationX(float fAngleRad)
{
    mat4x4 matrix;
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = cosf(fAngleRad);
    matrix.m[1][2] = sinf(fAngleRad);
    matrix.m[2][1] = -sinf(fAngleRad);
    matrix.m[2][2] = cosf(fAngleRad);
    matrix.m[3][3] = 1.0f;
    return matrix;
}
mat4x4 mat4x4::Matrix_MakeRotationY(float fAngleRad)
{
    mat4x4 matrix;
    matrix.m[0][0] = cosf(fAngleRad);
    matrix.m[0][2] = sinf(fAngleRad);
    matrix.m[2][0] = -sinf(fAngleRad);
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = cosf(fAngleRad);
    matrix.m[3][3] = 1.0f;
    return matrix;
}
mat4x4 mat4x4::Matrix_MakeRotationZ(float fAngleRad)
{
    mat4x4 matrix;
    matrix.m[0][0] = cosf(fAngleRad);
    matrix.m[0][1] = sinf(fAngleRad);
    matrix.m[1][0] = -sinf(fAngleRad);
    matrix.m[1][1] = cosf(fAngleRad);
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;
    return matrix;
}

mat4x4 mat4x4::Matrix_MakeTranslation(float x, float y, float z)
{
    mat4x4 matrix;
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;
    matrix.m[3][0] = x;
    matrix.m[3][1] = y;
    matrix.m[3][2] = z;
    return matrix;
}
// Creates a matrix to apply projection to a vertex using a super complicated formuala
mat4x4 mat4x4::Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
{
    float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
    mat4x4 matrix;
    matrix.m[0][0] = fAspectRatio * fFovRad;
    matrix.m[1][1] = fFovRad;
    matrix.m[2][2] = fFar / (fFar - fNear);
    matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    matrix.m[2][3] = 1.0f;
    matrix.m[3][3] = 0.0f;
    return matrix;
}
// Some operations:
mat4x4 mat4x4::operator*(mat4x4& rhs)
{
    mat4x4 matrix;
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            matrix.m[r][c] = rhs.m[r][0] * m[0][c] + rhs.m[r][1] * m[1][c] + rhs.m[r][2] * m[2][c] + rhs.m[r][3] * m[3][c];
    return matrix;
}
mat4x4& mat4x4::operator*=(mat4x4& rhs)
{
    mat4x4 matrix;
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            matrix.m[r][c] = rhs.m[r][0] * m[0][c] + rhs.m[r][1] * m[1][c] + rhs.m[r][2] * m[2][c] + rhs.m[r][3] * m[3][c];
    *this = matrix;
    return *this;
}
vec3D Matrix_MultiplyVector(mat4x4& m, vec3D& i)
{
    vec3D v;
    v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
    v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
    v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
    v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
    return v;
}
vec3D Vector_MultiplyMatrix(mat4x4& m, vec3D& i)
{
    vec3D v;
    i.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
    i.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
    i.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
    i.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
    return i;
}

// mesh contains a vector of triangles, along with 2 methods
//MESH CLASS
void mesh::setTris(int s)
{
    // takes each vertex as the top-right-front corner of a cube and creates triangles from it
    // in z,x and y axes if they don't exceed bounds aka the size of side s

    int x, y, z;
    int c = -1;
    vec3D verts[3];
    for (float x = s; x >= -s; x -= 2)
    {
        for (float y = s; y >= -s; y -= 2)
        {
            for (float z = s; z >= -s; z -= 2)
            {
                if (x != s && y != s && z != s && x != -s && y != -s && z != -s)
                    continue;
                verts[0].x = x;
                verts[0].y = y;
                verts[0].z = z;
                if (y - 2 >= -s && x - 2 >= -s)
                {

                    if (z > 0)
                    {

                        verts[1].x = x;
                        verts[1].y = y - 2;
                        verts[1].z = z;
                        verts[2].x = x - 2;
                        verts[2].y = y - 2;
                        verts[2].z = z;

                        tris.push_back({ verts[0], verts[1], verts[2] });
                        verts[1].x = x - 2;
                        verts[1].y = y - 2;
                        verts[1].z = z;
                        verts[2].x = x - 2;
                        verts[2].y = y;
                        verts[2].z = z;
                        tris.push_back({ verts[0], verts[1], verts[2] });
                    }
                    else
                    {

                        verts[1].x = x;
                        verts[1].y = y - 2;
                        verts[1].z = z;
                        verts[2].x = x - 2;
                        verts[2].y = y - 2;
                        verts[2].z = z;

                        tris.push_back({ verts[0], verts[2], verts[1] });

                        verts[1].x = x - 2;
                        verts[1].y = y - 2;
                        verts[1].z = z;
                        verts[2].x = x - 2;
                        verts[2].y = y;
                        verts[2].z = z;
                        tris.push_back({ verts[0], verts[2], verts[1] });
                    }
                }

                if (z - 2 >= -s && x - 2 >= -s)
                {

                    if (y > 0)
                    {

                        verts[1].x = x - 2;
                        verts[1].y = y;
                        verts[1].z = z - 2;
                        verts[2].x = x;
                        verts[2].y = y;
                        verts[2].z = z - 2;

                        tris.push_back({ verts[0], verts[1], verts[2] });

                        verts[1].x = x - 2;
                        verts[1].y = y;
                        verts[1].z = z;
                        verts[2].x = x - 2;
                        verts[2].y = y;
                        verts[2].z = z - 2;
                        tris.push_back({ verts[0], verts[1], verts[2] });
                    }
                    else
                    {
                        verts[1].x = x - 2;
                        verts[1].y = y;
                        verts[1].z = z - 2;
                        verts[2].x = x;
                        verts[2].y = y;
                        verts[2].z = z - 2;

                        tris.push_back({ verts[0], verts[2], verts[1] });

                        verts[1].x = x - 2;
                        verts[1].y = y;
                        verts[1].z = z;
                        verts[2].x = x - 2;
                        verts[2].y = y;
                        verts[2].z = z - 2;
                        tris.push_back({ verts[0], verts[2], verts[1] });
                    }
                }
                if (y - 2 >= -s && z - 2 >= -s)
                {

                    if (x > 0)
                    {
                        verts[1].x = x;
                        verts[1].y = y;
                        verts[1].z = z - 2;
                        verts[2].x = x;
                        verts[2].y = y - 2;
                        verts[2].z = z - 2;

                        tris.push_back({ verts[0], verts[1], verts[2] });

                        verts[1].x = x;
                        verts[1].y = y - 2;
                        verts[1].z = z - 2;
                        verts[2].x = x;
                        verts[2].y = y - 2;
                        verts[2].z = z;
                        tris.push_back({ verts[0], verts[1], verts[2] });
                    }
                    else
                    {
                        verts[1].x = x;
                        verts[1].y = y;
                        verts[1].z = z - 2;
                        verts[2].x = x;
                        verts[2].y = y - 2;
                        verts[2].z = z - 2;

                        tris.push_back({ verts[0], verts[2], verts[1] });

                        verts[1].x = x;
                        verts[1].y = y - 2;
                        verts[1].z = z - 2;
                        verts[2].x = x;
                        verts[2].y = y - 2;
                        verts[2].z = z;
                        tris.push_back({ verts[0], verts[2], verts[1] });
                    }
                }
            }
        }
    }
}
void mesh::setColor(int s)
{
    int c = 0;
    for (auto tri : tris)
    {

        if (tri.p[0].x == s && tri.p[1].x == s && tri.p[2].x == s)
        {
            tris[c].col[0] = 255;
            tris[c].col[1] = 0;
            tris[c].col[2] = 0;
        }
        else if (tri.p[0].x == -s && tri.p[1].x == -s && tri.p[2].x == -s)
        {

            tris[c].col[0] = 255;
            tris[c].col[1] = 165;
            tris[c].col[2] = 0;
        }
        else if (tri.p[0].z == s && tri.p[1].z == s && tri.p[2].z == s)
        {

            tris[c].col[0] = 0;
            tris[c].col[1] = 255;
            tris[c].col[2] = 0;
        }
        else if (tri.p[0].z == -s && tri.p[1].z == -s && tri.p[2].z == -s)
        {

            tris[c].col[0] = 0;
            tris[c].col[1] = 0;
            tris[c].col[2] = 255;
        }
        else if (tri.p[0].y == s && tri.p[1].y == s && tri.p[2].y == s)
        {

            tris[c].col[0] = 255;
            tris[c].col[1] = 255;
            tris[c].col[2] = 255;
        }
        else if (tri.p[0].y == -s && tri.p[1].y == -s && tri.p[2].y == -s)
        {

            tris[c].col[0] = 255;
            tris[c].col[1] = 255;
            tris[c].col[2] = 0;
        }
        else
        {
            tris[c].col[0] = 0;
            tris[c].col[1] = 0;
            tris[c].col[2] = 0;
        }

        c++;
    }
}
void mesh::updateColor(triangle& tri, char arr[][9])
{
    vec3D vt;
    vec3D v[6] = { vec3D(-3, -3, -3), vec3D(-1, -3, 3), vec3D(3, -3, -3), vec3D(-3, 3, -3), vec3D(-3, -3, 1), vec3D(-1, 3, 3) };

    for (int i = 0; i < 9; i++)
    {

        vt = v[0];
        vt.x += 2;
        vt.y += 2;
        if (checkTri(v[0], vt, tri))
        {
            squareColor(tri, arr[1][i]);
        }
        vt = v[1];
        vt.x -= 2;
        vt.z -= 2;
        if (checkTri(v[1], vt, tri))
        {
            squareColor(tri, arr[0][i]);
        }
        vt = v[2];
        vt.y += 2;
        vt.z += 2;
        if (checkTri(v[2], vt, tri))
        {
            squareColor(tri, arr[5][i]);
        }
        vt = v[3];
        vt.x += 2;
        vt.z += 2;
        if (checkTri(v[3], vt, tri))
        {
            squareColor(tri, arr[2][i]);
        }
        vt = v[4];
        vt.y += 2;
        vt.z += 2;
        if (checkTri(v[4], vt, tri))
        {
            squareColor(tri, arr[4][i]);
        }
        vt = v[5];
        vt.y -= 2;
        vt.x -= 2;
        if (checkTri(v[5], vt, tri))
        {
            squareColor(tri, arr[3][i]);
        }

        v[0].x += 2;
        if (v[0].x >= 3)
        {
            v[0].x = -3;
            v[0].y += 2;
        }
        v[1].x += 2;
        if (v[1].x > 3)
        {
            v[1].x = -1;
            v[1].z -= 2;
        }
        v[2].z += 2;
        if (v[2].z >= 3)
        {
            v[2].z = -3;
            v[2].y += 2;
        }
        v[3].x += 2;
        if (v[3].x >= 3)
        {
            v[3].x = -3;
            v[3].z += 2;
        }
        v[4].z -= 2;
        if (v[4].z < -3)
        {
            v[4].z = 1;
            v[4].y += 2;
        }
        v[5].x += 2;
        if (v[5].x > 3)
        {
            v[5].x = -1;
            v[5].y -= 2;
        }
    }
}
bool mesh::checkTri(vec3D v1, vec3D v2, triangle t)
{
    if ((t.p[0] == v1 && t.p[1] == v2) || (t.p[0] == v2 && t.p[1] == v1) ||
        (t.p[1] == v1 && t.p[2] == v2) || (t.p[1] == v2 && t.p[2] == v1) ||
        (t.p[2] == v1 && t.p[0] == v2) || (t.p[2] == v2 && t.p[0] == v1))
    {
        return 1;
    }
    else
        return 0;
}
void mesh::squareColor(triangle& t, char c)
{
    switch (c)
    {
    case 'B':
        t.col[0] = 0;
        t.col[1] = 0;
        t.col[2] = 255;
        break;
    case 'R':
        t.col[0] = 255;
        t.col[1] = 0;
        t.col[2] = 0;
        break;
    case 'G':
        t.col[0] = 0;
        t.col[1] = 255;
        t.col[2] = 0;
        break;
    case 'O':
        t.col[0] = 255;
        t.col[1] = 165;
        t.col[2] = 0;
        break;
    case 'Y':
        t.col[0] = 255;
        t.col[1] = 255;
        t.col[2] = 0;
        break;
    case 'W':
        t.col[0] = 255;
        t.col[1] = 255;
        t.col[2] = 255;
        break;
    default:
        t.col[0] = 33;
    }
}

//game engine file implementation is in header file
