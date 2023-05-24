#pragma once
#include "olcPixelGameEngine.h"
#include <iostream>
#include <algorithm>
#include "solver.h"
using namespace std;
const float Pi = 3.141592653589;
const float QuarterTurn = Pi / 4;
const float HalfTurn = Pi / 2;
const float FullTurn = Pi;

// vec3D stores 3 float values, representing vertices on a 3D plane
//  w is added to deal with matrix multiplications with 4x4 matrices
// this class stores operations for multiple operations involving x,y,z coordinates, including operator overloading
class mat4x4;
class vec3D
{
    friend vec3D Matrix_MultiplyVector(mat4x4&, vec3D&);
    friend vec3D Vector_MultiplyMatrix(mat4x4&, vec3D&);
public:
    float x, y, z;
    float w = 1;
    vec3D();
    vec3D(float a, float b, float c);

    float Vector_Length() const;
    vec3D Vector_Normalize();
    float Vector_DotProduct(const vec3D& v2);
    float Vector_DotProduct(const vec3D& v1, const vec3D& v2);
    vec3D Vector_CrossProduct(vec3D& v1, vec3D& v2);
    vec3D Vector_CrossProduct(vec3D& v2);

    bool operator==(const vec3D rhs);
    vec3D& operator+=(const vec3D& rhs);
    vec3D& operator-=(const vec3D& rhs);
    vec3D& operator*=(const float& rhs);
    vec3D& operator/=(const float& rhs);
    vec3D operator+(const vec3D& rhs);
    vec3D operator-(const vec3D& rhs);
    vec3D operator*(const float& rhs);
    vec3D operator/(const float& rhs);
};

// triangle stores 3 vertices, representing the coordinates of the triangles, as well as the color of each triangle
struct triangle
{
    vec3D p[3];
    int col[3];
};

// mat4x4 stores a 4x4 matrix of floats.
// This class has methods to create different types of matrixes that we may need, such as rotation, translation, and projection matrices
// This also includes matrix calculation operations

class mat4x4
{
    friend vec3D Matrix_MultiplyVector(mat4x4&, vec3D&);
    friend vec3D Vector_MultiplyMatrix(mat4x4&, vec3D&);
public:
    float m[4][4] = { 0 };
    mat4x4 Matrix_MakeIdentity();
    mat4x4 Matrix_MakeRotationX(float fAngleRad);
    mat4x4 Matrix_MakeRotationY(float fAngleRad);
    mat4x4 Matrix_MakeRotationZ(float fAngleRad);
    mat4x4 Matrix_MakeTranslation(float x, float y, float z);
    mat4x4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
    mat4x4 operator*(mat4x4& rhs);
    mat4x4& operator*=(mat4x4& rhs);
 
};

vec3D Matrix_MultiplyVector(mat4x4&, vec3D&);
vec3D Vector_MultiplyMatrix(mat4x4&, vec3D&);

class mesh
{
public:
    vector<triangle> tris;
    void setTris(int s);                            // pushes triangles to be rendered for a nxnxn cube into tris
    void setColor(int s);                           // sets the correct colors of each triangle in tris
    void updateColor(triangle& tri, char arr[][9]); // takes 2D cube array as input. Colors the cube
    bool checkTri(vec3D v1, vec3D v2, triangle t);
    void squareColor(triangle& t, char c);
};

//OLC GAME ENGINE CLASS WITH IMPLEMENTATION
class olcEngine3D : public olc::PixelGameEngine, public mat4x4, public vec3D, public BeginnerSolver
{

private:
    mesh meshCube; // instance of mesh. This is the actual cube
    int numSides;
    mat4x4 matProj; // matrix used for projection calculations
    vec3D fTheta;   // stores a vector representing angle of rotation of the cube in x,y, and z directions
    vec3D offset;   // distance from object
    vec3D vCamera;  // placeholder Camera
    float fAlpha[3];
    float fBeta[3];
    float fGamma[3];
    int rm[3];
    int um[3];
    int fm[3];
    bool solve = 0;
    int currentMove = 0;
    int ts = 5;
    BeginnerSolver begSolve;
    Solver* solveList[1];

    /*Rotation functions need to be implemented here*/
public:
    olcEngine3D(int s = 3)
    {
        sAppName = "Cube"; // name of app
        numSides = s;
    }
    bool OnUserCreate() override
    {
        solveList[0] = &begSolve;
        
        for (int i = 0; i < 3; i++)
        {
            rm[i] = 0;
            fAlpha[i] = 0;
            um[i] = 0;
            fBeta[i] = 0;

            if (i != 2)
            {
                fm[i] = 0;
                fGamma[i] = 0;
            }
        }
        // initializes our placeholder camera, vCamera
        vCamera = { 0, 0, -200 };
        // number of sides of our cube, s

        // how far away do we want to push the cube back, or offset it. The bigger it gets, the bigger we need to set the z-component
        offset = { 0, 0, 0 };
        offset.z = 5*numSides;
        // sets triangles into the mesh
        meshCube.setTris(numSides);
        if (numSides != 3)
        {
            meshCube.setColor(numSides);
        }
        // colors the mesh

        // meshCube.updateColor(cube);

        // creates a projection matrix and stores it in matProj
        matProj = Matrix_MakeProjection(90.0f, (float)ScreenHeight() / (float)ScreenWidth(), 0.1f, 1000.0f);
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        // meshCube.updateColor(cube);
        for (int i = 0; i < 3; i++)
        {
            if (rm[i] != 0)
                fAlpha[i] += rm[i] * 2 * ts * fElapsedTime;
            if (um[i] != 0)
                fBeta[i] += um[i] * 2 * ts * fElapsedTime;
            if (i != 2)
                if (fm[i] != 0)
                    fGamma[i] += fm[i] * 2 * ts * fElapsedTime;
        }

        // Gets user inputs to move rotate the cube or any of its sides
        if (GetKey(olc::DOWN).bHeld)
        {
            fTheta.x += 1.0f * fElapsedTime;
        }
        if (GetKey(olc::UP).bHeld)
        {
            fTheta.x -= 1.0f * fElapsedTime;
        }

        if (GetKey(olc::LEFT).bHeld)
        {
            fTheta.y -= 1.0f * fElapsedTime;
        }
        if (GetKey(olc::RIGHT).bHeld)
        {
            fTheta.y += 1.0f * fElapsedTime;
        }
        if (GetKey(olc::MINUS).bHeld)
        {
            offset.z+=5*fElapsedTime;
        }
        if (GetKey(olc::EQUALS).bHeld)
        {

            offset.z -= 5*fElapsedTime;
        }

        if (solve == 0)
        {
            if (GetKey(olc::ENTER).bPressed)
            {
                begSolve.setCube(this->cube);
                solveList[0]->solveCube();
                this->sol = solveList[0]->sol;
                solve = 1;
            }

            if (GetKey(olc::R).bPressed)
            {
                rm[0] = -1;
            }
            if (GetKey(olc::R).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                rm[0] = 1;
            }

            if (GetKey(olc::M).bPressed)
            {
                rm[1] = -1;
            }
            if (GetKey(olc::M).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                rm[1] = 1;
            }

            if (GetKey(olc::L).bPressed)
            {
                rm[2] = 1;
            }
            if (GetKey(olc::L).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                rm[2] = -1;
            }

            if (GetKey(olc::U).bPressed)
            {
                um[0] = -1;
            }
            if (GetKey(olc::U).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                um[0] = 1;
            }

            if (GetKey(olc::D).bPressed)
            {
                um[1] = 1;
            }
            if (GetKey(olc::D).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                um[1] = -1;
            }

            if (GetKey(olc::F).bPressed)
            {
                fm[0] = 1;
            }
            if (GetKey(olc::F).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                fm[0] = -1;
            }

            if (GetKey(olc::B).bPressed)
            {
                fm[1] = -1;
            }
            if (GetKey(olc::B).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                fm[1] = 1;
            }

            if (GetKey(olc::Y).bPressed)
            {
                um[0] = -1;
                um[1] = -1;
                um[2] = -1;
            }
            if (GetKey(olc::Y).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                um[0] = 1;
                um[1] = 1;
                um[2] = 1;
            }

            if (GetKey(olc::X).bPressed)
            {
                rm[0] = -1;
                rm[1] = -1;
                rm[2] = -1;
            }
            if (GetKey(olc::X).bPressed && GetKey(olc::SHIFT).bHeld)
            {
                rm[0] = 1;
                rm[1] = 1;
                rm[2] = 1;
            }
        }
        else
        {
            if (rm[0] + rm[1] + rm[2] + um[0] + um[1] + um[2] + fm[0] + fm[1] == 0)
            {
                switch (sol[currentMove])
                {
                case 0:

                    rm[0] = -1;
                    break;
                case 1:
                    rm[0] = 1;
                    break;
                case 2:
                    rm[2] = 1;
                    break;
                case 3:
                    rm[2] = -1;
                    break;
                case 4:
                    um[0] = -1;
                    break;
                case 5:
                    um[0] = 1;
                    break;
                case 6:
                    fm[0] = 1;
                    break;
                case 7:
                    fm[0] = -1;
                    break;
                case 8:
                    fm[1] = -1;
                    break;
                case 9:
                    fm[1] = 1;
                    break;
                case 10:
                    um[1] = 1;
                    break;
                case 11:
                    um[1] = -1;
                    break;
                case 12:
                    rm[1] = -1;
                    break;
                case 13:
                    rm[1] = 1;
                    break;
                case 16:
                    rm[0] = -1;
                    rm[1] = -1;
                    rm[2] = -1;
                    break;
                case 17:
                    rm[0] = 1;
                    rm[1] = 1;
                    rm[2] = 1;
                    break;
                case 18:
                    um[0] = -1;
                    um[1] = -1;
                    um[2] = -1;
                    break;
                case 19:
                    um[0] = 1;
                    um[1] = 1;
                    um[2] = 1;

                    break;
                }
                currentMove++;
                if (currentMove >= sol.size())
                    solve = 0;
            }
        }
        // sets the background to a nice titanium gray
        FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(86, 95, 107));

        mat4x4 matRotZ, matRotX, matRotY; // Matrices used to rotate a vertex in x,y,or z directions

        // stores triangles to be sorted later. This prevents glitching
        vector<triangle> vecTrianglesToRaster;

        // Drawing the triangles:
        for (auto& tri : meshCube.tris)
        { // Goes through each triangle, tri, in meshCube
            meshCube.updateColor(tri, cube);
            int c = 1;
            triangle triProjected;  // holds result of matrix multiplication
            triangle triTranslated; // hold translated matrix
            triangle triRotatedS;   // hold Z rotated triangle
            triangle triRotatedC;   // holds X rotated Z rotated triangle

            // Rotates the (n-2)'th layer from the middle layer counter clockwise.
            // n=1 is middle layer for odd dimensioned cubes
            // n=0 is first left to-middle layer for even dimensioned cubes
            // add/subtract 2 to move right/left a layer
            //  for the final left layer, you have to select n=-s and another variable, say m=-s+2 to either be equal to tri.p->x. Idk why this
            //  make fAlpha negative for clockwise rotation
            int n;
            n = 3;

            matRotX = Matrix_MakeRotationX(0);
            for (int i = 0; i < 3; i++)
            {
                triRotatedS.p[i] = Matrix_MultiplyVector(matRotX, tri.p[i]);
            }

            // R

            if (rm[0] != 0)
            {
                if (tri.p->x == n)
                {
                    matRotX = Matrix_MakeRotationX(fAlpha[0]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotX, tri.p[i]);
                    }
                }
            }
            // M
            if (rm[1] != 0)
            {
                if (tri.p->x == n - 2)
                {

                    matRotX = Matrix_MakeRotationX(fAlpha[1]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotX, tri.p[i]);
                    }
                }
            }
            // L
            if (rm[2] != 0)
            {
                if (tri.p->x == n - 4 || tri.p->x == n - 6)
                {

                    matRotX = Matrix_MakeRotationX(fAlpha[2]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotX, tri.p[i]);
                    }
                }
            }
            // U
            if (um[0] != 0)
            {
                if (tri.p->y == n - 4 || tri.p->y == n - 6)
                {

                    matRotY = Matrix_MakeRotationY(fBeta[0]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotY, tri.p[i]);
                    }
                }
            }
            // S
            if (um[1] != 0)
            {
                if (tri.p->y == n)
                {

                    matRotY = Matrix_MakeRotationY(fBeta[1]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotY, tri.p[i]);
                    }
                }
            }
            // D
            if (um[2] != 0)
            {
                if (tri.p->y == n - 2)
                {
                    matRotY = Matrix_MakeRotationY(fBeta[2]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotY, tri.p[i]);
                    }
                }
            }
            // F
            if (fm[0] != 0)
            {
                if (tri.p->z == n - 4 || tri.p->z == n - 6)
                {

                    matRotZ = Matrix_MakeRotationZ(fGamma[0]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotZ, tri.p[i]);
                    }
                }
            }
            // B
            if (fm[1] != 0)
            {
                if (tri.p->z == n)
                {

                    matRotZ = Matrix_MakeRotationZ(fGamma[1]);
                    for (int i = 0; i < 3; i++)
                    {
                        triRotatedS.p[i] = Matrix_MultiplyVector(matRotZ, tri.p[i]);
                    }
                }
            }

            if (rm[0] * fAlpha[0] > HalfTurn)
            {
                (rm[0] == -1) ? R() : R_();
                rm[0] = 0;
                fAlpha[0] = 0;
            }
            if (rm[1] * fAlpha[1] > HalfTurn)
            {
                (rm[1] == -1) ? M() : M_();
                rm[1] = 0;
                fAlpha[1] = 0;
            }
            if (rm[2] * fAlpha[2] > HalfTurn)
            {
                (rm[2] == 1) ? L() : L_();
                rm[2] = 0;
                fAlpha[2] = 0;
            }
            if (um[0] * fBeta[0] > HalfTurn)
            {
                (um[0] == -1) ? U() : U_();
                um[0] = 0;
                fBeta[0] = 0;
            }
            if (um[1] * fBeta[1] > HalfTurn)
            {
                (um[1] == 1) ? D() : D_();
                um[1] = 0;
                fBeta[1] = 0;
            }
            if (um[2] * fBeta[2] > HalfTurn)
            {
                (um[2] == -1) ? S() : S_();
                um[2] = 0;
                fBeta[2] = 0;
            }
            if (fm[0] * fGamma[0] > HalfTurn)
            {
                (fm[0] == 1) ? F() : F_();
                fm[0] = 0;
                fGamma[0] = 0;
            }
            if (fm[1] * fGamma[1] > HalfTurn)
            {
                (fm[1] == -1) ? B() : B_();
                fm[1] = 0;
                fGamma[1] = 0;
            }

            // Sets rotation matrices X and Y
            matRotY = Matrix_MakeRotationY(2 * fTheta.y);
            matRotX = Matrix_MakeRotationX(2 * fTheta.x);

            // Rotates cube along X axis based on user input
            for (int i = 0; i < 3; i++)
            {
                triRotatedS.p[i] = Matrix_MultiplyVector(matRotX, triRotatedS.p[i]);
            }

            // Rotates cube along Y axis based on user input (Order of X and Y rotation doesnt matter)
            for (int i = 0; i < 3; i++)
            {
                triRotatedC.p[i] = Matrix_MultiplyVector(matRotY, triRotatedS.p[i]);
            }

            // Adds a slight tilt to the cube just cos it looks nice
            matRotY = Matrix_MakeRotationY(-5.7);
            matRotX = Matrix_MakeRotationX(-5.8);
            for (int i = 0; i < 3; i++)
            {
                triRotatedC.p[i] = Matrix_MultiplyVector(matRotY, triRotatedC.p[i]);
            }
            for (int i = 0; i < 3; i++)
            {
                triRotatedC.p[i] = Matrix_MultiplyVector(matRotX, triRotatedC.p[i]);
            }

            // We need to Translate the cube before projecting it, so that the viewing origin may be different to the cubes origin, thus we can add perspective to the cube by offsetting it

            triTranslated = triRotatedC;
            for (int i = 0; i < 3; i++)
            {
                triTranslated.p[i] += offset;
            }

            // Setting Normal by finding cross product
            vec3D normal, line1, line2;

            line1 = triTranslated.p[1] - triTranslated.p[0];
            line2 = triTranslated.p[2] - triTranslated.p[0];

            normal = Vector_CrossProduct(line1, line2);

            // normalizing normal to turn it into a unit vector
            normal.Vector_Normalize();

            // Finding dot product to compare our POV to the cube. If<0, that means the vector has a component facing us, and thus, we render it

            if (normal.Vector_DotProduct(vCamera) < 0)
            {

                // Projecting all vertices of current triangle, from 3D to 2D, tri, and storing it in triProjected
                for (int i = 0; i < 3; i++)
                {
                    triProjected.p[i] = Matrix_MultiplyVector(matProj, triTranslated.p[i]);
                }

                // dividing the vertice with w so that w can be 1 and be ignored
                for (int i = 0; i < 3; i++)
                {
                    triProjected.p[i] /= triProjected.p[i].w;
                }
                // Right now, the matrix has been projected, but not Scaled into view. For that, We do the following:
                vec3D vOffsetView = { 1, 0.8, 0 };
                for (int i = 0; i < 3; i++)
                {
                    triProjected.p[i] += vOffsetView;
                }

                // To bring everything into screen width:
                for (int i = 0; i < 3; i++)
                {
                    triProjected.p[i].x *= 0.5f * (float)ScreenWidth();
                    triProjected.p[i].y *= 0.5f * (float)ScreenWidth();
                    triProjected.col[i] = tri.col[i];
                }

                // stores triangles to raster in order to sort them later
                vecTrianglesToRaster.push_back(triProjected);
            }
        }

        // Sort triangles back to front in terms of z axis. This makes the program wayyy smoother

        sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
            {
                // Avg z points for the triangles. swaps if z1>z2
                float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
                float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;

                return z1 > z2;
            });
        for (auto& triProjected : vecTrianglesToRaster)
        { // loops thru triangles to raster now instead of unsorted list

            // fills in triangles with color
            FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
                triProjected.p[1].x, triProjected.p[1].y,
                triProjected.p[2].x, triProjected.p[2].y,
                olc::Pixel(triProjected.col[0], triProjected.col[1], triProjected.col[2]));

            // Draws outline:
            /*DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
                triProjected.p[1].x, triProjected.p[1].y,
                triProjected.p[2].x, triProjected.p[2].y,
                olc::Pixel(0, 0, 0));*/

            DrawLine(triProjected.p[0].x, triProjected.p[0].y, triProjected.p[1].x, triProjected.p[1].y, olc::Pixel(0, 0, 0));
            DrawLine(triProjected.p[1].x, triProjected.p[1].y, triProjected.p[2].x, triProjected.p[2].y, olc::Pixel(0, 0, 0));
            DrawLine(triProjected.p[0].x, triProjected.p[0].y, triProjected.p[2].x, triProjected.p[2].y, olc::Pixel(0, 0, 0));
        }
        return true;
    }
};