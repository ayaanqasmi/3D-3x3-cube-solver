#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <windows.h>
using namespace std;
/*Takes Green as front, white as top Initially*/
/*
______________
| 0 || 1 || 2 |
|___||___||___|
| 3 || 4 || 5 |
|___||___||___|
| 6 || 7 || 8 |
|___||___||___|

*/
enum Turn
{
    R,
    R_,
    L,
    L_,
    U,
    U_,
    F,
    F_,
    B,
    B_,
    D,
    D_,
    M,
    M_,
    S,
    S_,
    x,
    x_,
    y,
    y_,
    z,
    z_
};
class Cube
{
protected:
    char cube[6][9] = {
        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'}, // white//Top
        {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'}, // green//Front
        {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'}, // yellow//Bottom
        {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'}, // blue//Back
        {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, // orange//Left
        {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}  // red//Right
    };
    // rotate a face clockwise
    void rotateClockwise(int face);
    // rotate a face anticlockwise
    void rotateCounterClockwise(int face);

   /*display in the order: Top,front,bottom,back,left,right*/
   // void printCube();
    // Moves available to us
    void R();
    void R_();
    void L();
    void L_();
    void U();
    void U_();
    void F();
    void F_();
    void B();
    void B_();
    void D();
    void D_();
    void M();
    void M_();
    void S();
    void S_();
    void turnUp();
    void turnDown();
    void turnRight();
    void turnLeft();
    //algorith executioner
    bool executeAlg(vector<Turn> alg);
public:
    void setCube(char arr[][9]);
};

class Solver : public Cube
{
protected:
    int currentFace;
    int currentEdge[2][2];
    int currentCorner[3][2];

    // ALGORITHMS:
    void sexy(int i);
    void reverseSexy();
    void sune();
    void cor();
    // outputs coordinates of required edge
    bool findEdge(char col1, char col2);
    // outputs coordinates of required face
    bool findFace(char col);
    // permutates all possible positions of the given corner to see if it matches the colors
    bool compareCorner(int corner[3][2], char col1, char col2, char col3);
    // outputs coordinates of required corner
    bool findCorner(char col1, char col2, char col3 );
    // inserts given white edge into white cross
    void insertWhiteEdge(char col, int order);
    // inserts given corner into first layer
    void insertWhiteCorner(char col1, char col2);
    // inserts given edge into second layer
    void insertColorEdge(char col1, char col2);
    // checks for an exact patter of yellows in the last layer
    bool onecheckOLL(int yel[], int len);
    // checks for any permutation of yellows in last layer
    bool checkOLL(int yel[], int len);

    // white cross solver
    virtual void solveCross() = 0;
    // first two layer solver
    virtual void F2L() = 0;
    // orientation of last layer
    virtual void OLL() = 0;
    // permutation of last layer
    virtual void PLL() = 0;

public:
    
    /*void outputSol()
    {
        for (int i = 0; i < sol.size(); i++)
        {
            if (i % 15 == 0)
                cout << endl;
            switch (sol[i])
            {
            case 0:
                cout << "R ";
                break;
            case 1:
                cout << "R_ ";
                break;
            case 2:
                cout << "L ";
                break;
            case 3:
                cout << "L_ ";
                break;
            case 4:
                cout << "U ";
                break;
            case 5:
                cout << "U_ ";
                break;
            case 6:
                cout << "F ";
                break;
            case 7:
                cout << "F_ ";
                break;
            case 8:
                cout << "B ";
                break;
            case 9:
                cout << "B_ ";
                break;
            case 10:
                cout << "D ";
                break;
            case 11:
                cout << "D_ ";
                break;
            case 12:
                cout << "M ";
                break;
            case 13:
                cout << "M_ ";
                break;
            case 14:
                cout << "S ";
                break;
            case 15:
                cout << "S_ ";
                break;
            case 16:
                cout << "x ";
                break;
            case 17:
                cout << "x_ ";
                break;
            case 18:
                cout << "y ";
                break;
            case 19:
                cout << "y_ ";
                break;
            case 20:
                cout << "z ";
                break;
            case 21:
                cout << "z_ ";
                break;
            }
        }
    }*/
    // outputs solution
    void solveCube();
    // solution vector
    vector<Turn> sol;

};

class BeginnerSolver : public Solver
{
    private:
    // makes a yellow cross, not oriented
    void yellowCross();
    // get all yellow corners in their correct positions, regardless of permutation
    void orientYellowCorners();
    void solveCross();
    // first two layer solver
    void F2L();
    // orientation of last layer
    void OLL();
    // permutation of last layer
    void PLL();
};
