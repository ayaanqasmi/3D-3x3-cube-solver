#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <windows.h>
using namespace std;
#include"solver.h"

void Cube::rotateClockwise(int face)
{
    char corner_1 = cube[face][2], side_1 = cube[face][1];
    /*swap CORNERS*/
    cube[face][2] = cube[face][0];
    cube[face][0] = cube[face][6];
    cube[face][6] = cube[face][8];
    cube[face][8] = corner_1;
    /*SIDE CUBES*/
    cube[face][1] = cube[face][3];
    cube[face][3] = cube[face][7];
    cube[face][7] = cube[face][5];
    cube[face][5] = side_1;
}
void Cube:: rotateCounterClockwise(int face)
{
    char corner_1 = cube[face][2], side_1 = cube[face][1];
    /*swap CORNERS*/
    cube[face][2] = cube[face][8];
    cube[face][8] = cube[face][6];
    cube[face][6] = cube[face][0];
    cube[face][0] = corner_1;
    /*SIDE CUBES*/
    cube[face][1] = cube[face][5];
    cube[face][5] = cube[face][7];
    cube[face][7] = cube[face][3];
    cube[face][3] = side_1;
}
/*void Cube::printCube()
{
    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 6; i++)
    {
        cout << "\n------------------" << endl;
        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0 && j != 0)
            {
                cout << endl;
            }
            switch (cube[i][j])
            {
            case 'Y':
                SetConsoleTextAttribute(col, 14);
                break;
            case 'W':
                SetConsoleTextAttribute(col, 15);
                break;
            case 'O':
                SetConsoleTextAttribute(col, 6);
                break;
            case 'R':
                SetConsoleTextAttribute(col, 4);
                break;
            case 'G':
                SetConsoleTextAttribute(col, 10);
                break;
            case 'B':
                SetConsoleTextAttribute(col, 9);
                break;
            }
            cout << cube[i][j] << " ";
        }
    }
    cout << '\n';
    SetConsoleTextAttribute(col, 15);
}
*/
void Cube::R()
{
    /*
        R: [3, 6, 9]
        white -> green
        green -> yellow
        yellow -> blue
        blue -> white
    */
    char temp_white[3] = { cube[0][2], cube[0][5], cube[0][8] };

    for (int i = 0; i < 3; i++)
    {
        cube[i][2] = cube[i + 1][2];
        cube[i][5] = cube[i + 1][5];
        cube[i][8] = cube[i + 1][8];
    }

    cube[3][2] = temp_white[0];
    cube[3][5] = temp_white[1];
    cube[3][8] = temp_white[2];

    rotateClockwise(5);
};
void Cube:: R_()
{
    /*
        R': [3, 6, 9]
        white -> blue
        blue -> yellow
        yellow -> green
        green -> white
    */
    char temp_blue[3] = { cube[3][2], cube[3][5], cube[3][8] };
    for (int i = 3; i >= 1; i--)
    {
        cube[i][2] = cube[i - 1][2];
        cube[i][5] = cube[i - 1][5];
        cube[i][8] = cube[i - 1][8];
    }

    cube[0][2] = temp_blue[0];
    cube[0][5] = temp_blue[1];
    cube[0][8] = temp_blue[2];

    rotateCounterClockwise(5);
};
void Cube::L()
{
    /*
        L: [1, 4, 7]
        while -> blue
        blue -> yellow
        yellow -> green
        green -> white
    */
    char temp_blue[3] = { cube[3][0], cube[3][3], cube[3][6] };
    for (int i = 3; i >= 1; i--)
    {
        cube[i][0] = cube[i - 1][0];
        cube[i][3] = cube[i - 1][3];
        cube[i][6] = cube[i - 1][6];
    }

    cube[0][0] = temp_blue[0];
    cube[0][3] = temp_blue[1];
    cube[0][6] = temp_blue[2];

    rotateClockwise(4);
}
void Cube::L_()
{
    /*
        L': [1, 4, 7]
        white -> green
        green -> yellow
        yellow -> blue
        blue -> white
    */
    char temp_white[3] = { cube[0][0], cube[0][3], cube[0][6] };

    for (int i = 0; i < 3; i++)
    {
        cube[i][0] = cube[i + 1][0];
        cube[i][3] = cube[i + 1][3];
        cube[i][6] = cube[i + 1][6];
    }

    cube[3][0] = temp_white[0];
    cube[3][3] = temp_white[1];
    cube[3][6] = temp_white[2];

    rotateCounterClockwise(4);
}
void Cube::U()
{
    /*
        U: [1][all]
        red -> green
        green -> orange
        orange -> blue
        blue -> red
    */
    char temp_green[3] = { cube[1][0], cube[1][1], cube[1][2] };
    /*SIDES*/
    // green -> red
    cube[1][0] = cube[5][0];
    cube[1][1] = cube[5][1];
    cube[1][2] = cube[5][2];
    // red -> blue
    cube[5][0] = cube[3][8];
    cube[5][1] = cube[3][7];
    cube[5][2] = cube[3][6];
    // blue -> orange
    cube[3][8] = cube[4][0];
    cube[3][7] = cube[4][1];
    cube[3][6] = cube[4][2];
    // orange -> green
    cube[4][0] = temp_green[0];
    cube[4][1] = temp_green[1];
    cube[4][2] = temp_green[2];

    rotateClockwise(0);
}
void Cube::U_()
{
    char temp_red[3] = { cube[5][0], cube[5][1], cube[5][2] };
    /*SIDES*/
    // red -> green
    cube[5][0] = cube[1][0];
    cube[5][1] = cube[1][1];
    cube[5][2] = cube[1][2];
    // green -> orange
    cube[1][0] = cube[4][0];
    cube[1][1] = cube[4][1];
    cube[1][2] = cube[4][2];
    // orange -> blue
    cube[4][0] = cube[3][8];
    cube[4][1] = cube[3][7];
    cube[4][2] = cube[3][6];

    // blue -> red
    cube[3][8] = temp_red[0];
    cube[3][7] = temp_red[1];
    cube[3][6] = temp_red[2];

    rotateCounterClockwise(0);
}
void Cube::F()
{
    char temp_white[3] = { cube[0][6], cube[0][7], cube[0][8] };

    cube[0][6] = cube[4][8];
    cube[0][7] = cube[4][5];
    cube[0][8] = cube[4][2];

    cube[4][2] = cube[2][0];
    cube[4][5] = cube[2][1];
    cube[4][8] = cube[2][2];

    cube[2][0] = cube[5][6];
    cube[2][1] = cube[5][3];
    cube[2][2] = cube[5][0];

    cube[5][0] = temp_white[0];
    cube[5][3] = temp_white[1];
    cube[5][6] = temp_white[2];

    rotateClockwise(1);
}
void Cube::F_()
{
    char temp_white[3] = { cube[0][6], cube[0][7], cube[0][8] };

    cube[0][6] = cube[5][0];
    cube[0][7] = cube[5][3];
    cube[0][8] = cube[5][6];

    cube[5][0] = cube[2][2];
    cube[5][3] = cube[2][1];
    cube[5][6] = cube[2][0];

    cube[2][0] = cube[4][2];
    cube[2][1] = cube[4][5];
    cube[2][2] = cube[4][8];

    cube[4][2] = temp_white[2];
    cube[4][5] = temp_white[1];
    cube[4][8] = temp_white[0];

    rotateCounterClockwise(1);
}
void Cube::B()
{
    char temp_white[3] = { cube[0][0], cube[0][1], cube[0][2] };

    cube[0][0] = cube[5][2];
    cube[0][1] = cube[5][5];
    cube[0][2] = cube[5][8];

    cube[5][2] = cube[2][8];
    cube[5][5] = cube[2][7];
    cube[5][8] = cube[2][6];

    cube[2][6] = cube[4][0];
    cube[2][7] = cube[4][3];
    cube[2][8] = cube[4][6];

    cube[4][0] = temp_white[2];
    cube[4][3] = temp_white[1];
    cube[4][6] = temp_white[0];

    rotateClockwise(3);
}
void Cube::B_()
{
    B();
    B();
    B();
}
void Cube::D()
{
    char temp_red[3] = { cube[5][6], cube[5][7], cube[5][8] };
    /*SIDES*/
    // red -> green
    cube[5][6] = cube[1][6];
    cube[5][7] = cube[1][7];
    cube[5][8] = cube[1][8];
    // green -> orange
    cube[1][6] = cube[4][6];
    cube[1][7] = cube[4][7];
    cube[1][8] = cube[4][8];
    // orange -> blue
    cube[4][6] = cube[3][2];
    cube[4][7] = cube[3][1];
    cube[4][8] = cube[3][0];

    // blue -> red
    cube[3][2] = temp_red[0];
    cube[3][1] = temp_red[1];
    cube[3][0] = temp_red[2];

    rotateClockwise(2);
}
void Cube::D_()
{
    char temp_green[3] = { cube[1][6], cube[1][7], cube[1][8] };
    /*SIDES*/
    // green -> red
    cube[1][6] = cube[5][6];
    cube[1][7] = cube[5][7];
    cube[1][8] = cube[5][8];
    // red -> blue
    cube[5][6] = cube[3][2];
    cube[5][7] = cube[3][1];
    cube[5][8] = cube[3][0];
    // blue -> orange
    cube[3][0] = cube[4][8];
    cube[3][1] = cube[4][7];
    cube[3][2] = cube[4][6];
    // orange -> green
    cube[4][6] = temp_green[0];
    cube[4][7] = temp_green[1];
    cube[4][8] = temp_green[2];
    rotateCounterClockwise(2);
}
void Cube::M()
{
    /*
        R: [3, 6, 9]
        white -> green
        green -> yellow
        yellow -> blue
        blue -> white
    */
    char temp_white[3] = { cube[0][1], cube[0][4], cube[0][7] };

    for (int i = 0; i < 3; i++)
    {
        cube[i][1] = cube[i + 1][1];
        cube[i][4] = cube[i + 1][4];
        cube[i][7] = cube[i + 1][7];
    }

    cube[3][1] = temp_white[0];
    cube[3][4] = temp_white[1];
    cube[3][7] = temp_white[2];
};
void Cube::M_()
{
    /*
        R': [3, 6, 9]
        white -> blue
        blue -> yellow
        yellow -> green
        green -> white
    */
    char temp_blue[3] = { cube[3][1], cube[3][4], cube[3][7] };
    for (int i = 3; i >= 1; i--)
    {
        cube[i][1] = cube[i - 1][1];
        cube[i][4] = cube[i - 1][4];
        cube[i][7] = cube[i - 1][7];
    }

    cube[0][1] = temp_blue[0];
    cube[0][4] = temp_blue[1];
    cube[0][7] = temp_blue[2];
};
void Cube::S()
{
    /*
        U: [1][all]
        red -> green
        green -> orange
        orange -> blue
        blue -> red
    */
    char temp_green[3] = { cube[1][3], cube[1][4], cube[1][5] };
    /*SIDES*/
    // green -> red
    cube[1][3] = cube[5][3];
    cube[1][4] = cube[5][4];
    cube[1][5] = cube[5][5];
    // red -> blue
    cube[5][3] = cube[3][5];
    cube[5][4] = cube[3][4];
    cube[5][5] = cube[3][3];
    // blue -> orange
    cube[3][5] = cube[4][3];
    cube[3][4] = cube[4][4];
    cube[3][3] = cube[4][5];
    // orange -> green
    cube[4][3] = temp_green[0];
    cube[4][4] = temp_green[1];
    cube[4][5] = temp_green[2];
}
void Cube::S_()
{
    char temp_red[3] = { cube[5][3], cube[5][4], cube[5][5] };
    /*SIDES*/
    // red -> green
    cube[5][3] = cube[1][3];
    cube[5][4] = cube[1][4];
    cube[5][5] = cube[1][5];
    // green -> orange
    cube[1][3] = cube[4][3];
    cube[1][4] = cube[4][4];
    cube[1][5] = cube[4][5];
    // orange -> blue
    cube[4][3] = cube[3][5];
    cube[4][4] = cube[3][4];
    cube[4][5] = cube[3][3];

    // blue -> red
    cube[3][5] = temp_red[0];
    cube[3][4] = temp_red[1];
    cube[3][3] = temp_red[2];
}
void Cube::turnUp()
{
    R();
    M();
    L_();
}
void Cube::turnDown()
{
    R_();
    M_();
    L();
}
void Cube::turnRight()
{
    U();
    S();
    D_();
}
void Cube::turnLeft()
{
    U_();
    S_();
    D();
}
bool Cube:: executeAlg(vector<Turn> alg)
{

    for (int i = 0; i < alg.size(); i++)
    {
        switch (alg[i])
        {
        case 0:
            R();
            break;
        case 1:
            R_();
            break;
        case 2:
            L();
            break;
        case 3:
            L_();
            break;
        case 4:
            U();
            break;
        case 5:
            U_();
            break;
        case 6:
            F();
            break;
        case 7:
            F_();
            break;
        case 8:
            B();
            break;
        case 9:
            B_();
            break;
        case 10:
            D();
            break;
        case 11:
            D_();
            break;
        case 12:
            M();
            break;
        case 13:
            M_();
            break;
        case 14:
            S();
            break;
        case 15:
            S_();
            break;
        case 16:
            turnUp();
            break;
        case 17:
            turnDown();
            break;
        case 18:
            turnRight();
            break;
        case 19:
            turnLeft();
            break;
        default:
            return 0;
        }
    }
    return 1;
}
void Cube::setCube(char arr[][9]) {
    for (int i = 0;i < 6;i++) {
        for (int j = 0;j < 9;j++) {
            cube[i][j] = arr[i][j];
        }
    }
}
//SOLVER ABSTRACT CLASS

void Solver:: sexy(int i)
{

    if (i == 0)
    {
        R();
        U();
        R_();
        U_();
        sol.push_back(Turn::R);
        sol.push_back(Turn::U);
        sol.push_back(Turn::R_);
        sol.push_back(Turn::U_);
    }
    else
    {
        L_();
        U_();
        L();
        U();
        sol.push_back(Turn::L_);
        sol.push_back(Turn::U_);
        sol.push_back(Turn::L);
        sol.push_back(Turn::U);
    }
}
void Solver:: reverseSexy()
{
    R_();
    D_();
    R();
    D();
    sol.push_back(Turn::R_);
    sol.push_back(Turn::D_);
    sol.push_back(Turn::R);
    sol.push_back(Turn::D);
}
void Solver:: sune()
{
    R();
    U();
    R_();
    U();
    R();
    U_();
    U_();
    R_();
    sol.push_back(Turn::R);
    sol.push_back(Turn::U);
    sol.push_back(Turn::R_);
    sol.push_back(Turn::U);
    sol.push_back(Turn::R);
    sol.push_back(Turn::U_);
    sol.push_back(Turn::U_);
    sol.push_back(Turn::R_);
}
void Solver:: cor()
{
    U();
    R();
    U_();
    L_();
    U();
    R_();
    U_();
    L();
    sol.push_back(Turn::U);
    sol.push_back(Turn::R);
    sol.push_back(Turn::U_);
    sol.push_back(Turn::L_);
    sol.push_back(Turn::U);
    sol.push_back(Turn::R_);
    sol.push_back(Turn::U_);
    sol.push_back(Turn::L);
}
// outputs coordinates of required edge
bool Solver::findEdge(char col1, char col2)
{

    // checks Top layer edge pairs
    if (cube[0][1] == col1 && cube[3][7] == col2)
    {
        currentEdge[0][0] = 0;
        currentEdge[0][1] = 1;
        currentEdge[1][0] = 3;
        currentEdge[1][1] = 1;
    }
    else if (cube[0][1] == col2 && cube[3][7] == col1)
    {
        currentEdge[1][0] = 0;
        currentEdge[1][1] = 1;
        currentEdge[0][0] = 3;
        currentEdge[0][1] = 1;
    }
    else if (cube[0][3] == col1 && cube[4][1] == col2)
    {
        currentEdge[0][0] = 0;
        currentEdge[0][1] = 3;
        currentEdge[1][0] = 4;
        currentEdge[1][1] = 1;
    }
    else if (cube[0][3] == col2 && cube[4][1] == col1)
    {
        currentEdge[1][0] = 0;
        currentEdge[1][1] = 3;
        currentEdge[0][0] = 4;
        currentEdge[0][1] = 1;
    }
    else if (cube[0][5] == col1 && cube[5][1] == col2)
    {
        currentEdge[0][0] = 0;
        currentEdge[0][1] = 5;
        currentEdge[1][0] = 5;
        currentEdge[1][1] = 1;
    }
    else if (cube[0][5] == col2 && cube[5][1] == col1)
    {
        currentEdge[1][0] = 0;
        currentEdge[1][1] = 5;
        currentEdge[0][0] = 5;
        currentEdge[0][1] = 1;
    }
    else if (cube[0][7] == col1 && cube[1][1] == col2)
    {
        currentEdge[0][0] = 0;
        currentEdge[0][1] = 7;
        currentEdge[1][0] = 1;
        currentEdge[1][1] = 1;
    }
    else if (cube[0][7] == col2 && cube[1][1] == col1)
    {
        currentEdge[1][0] = 0;
        currentEdge[1][1] = 7;
        currentEdge[0][0] = 1;
        currentEdge[0][1] = 1;
    }
    // checks bottom layer edge pairs
    else if (cube[2][1] == col1 && cube[1][7] == col2)
    {
        currentEdge[0][0] = 2;
        currentEdge[0][1] = 1;
        currentEdge[1][0] = 1;
        currentEdge[1][1] = 7;
    }
    else if (cube[2][1] == col2 && cube[1][7] == col1)
    {
        currentEdge[1][0] = 2;
        currentEdge[1][1] = 1;
        currentEdge[0][0] = 1;
        currentEdge[0][1] = 7;
    }
    else if (cube[2][3] == col1 && cube[4][7] == col2)
    {
        currentEdge[0][0] = 2;
        currentEdge[0][1] = 3;
        currentEdge[1][0] = 4;
        currentEdge[1][1] = 7;
    }
    else if (cube[2][3] == col2 && cube[4][7] == col1)
    {
        currentEdge[1][0] = 2;
        currentEdge[1][1] = 3;
        currentEdge[0][0] = 4;
        currentEdge[0][1] = 7;
    }
    else if (cube[2][5] == col1 && cube[5][7] == col2)
    {
        currentEdge[0][0] = 2;
        currentEdge[0][1] = 5;
        currentEdge[1][0] = 5;
        currentEdge[1][1] = 7;
    }
    else if (cube[2][5] == col2 && cube[5][7] == col1)
    {
        currentEdge[1][0] = 2;
        currentEdge[1][1] = 5;
        currentEdge[0][0] = 5;
        currentEdge[0][1] = 7;
    }
    else if (cube[2][7] == col1 && cube[3][1] == col2)
    {
        currentEdge[0][0] = 2;
        currentEdge[0][1] = 7;
        currentEdge[1][0] = 3;
        currentEdge[1][1] = 7;
    }
    else if (cube[2][7] == col2 && cube[3][1] == col1)
    {
        currentEdge[1][0] = 2;
        currentEdge[1][1] = 7;
        currentEdge[0][0] = 3;
        currentEdge[0][1] = 7;
    }
    // checks middle layer edge pairs
    else if (cube[1][3] == col1 && cube[4][5] == col2)
    {
        currentEdge[0][0] = 1;
        currentEdge[0][1] = 3;
        currentEdge[1][0] = 4;
        currentEdge[1][1] = 5;
    }
    else if (cube[1][3] == col2 && cube[4][5] == col1)
    {
        currentEdge[1][0] = 1;
        currentEdge[1][1] = 3;
        currentEdge[0][0] = 4;
        currentEdge[0][1] = 5;
    }
    else if (cube[1][5] == col1 && cube[5][3] == col2)
    {
        currentEdge[0][0] = 1;
        currentEdge[0][1] = 5;
        currentEdge[1][0] = 5;
        currentEdge[1][1] = 3;
    }
    else if (cube[1][5] == col2 && cube[5][3] == col1)
    {
        currentEdge[1][0] = 1;
        currentEdge[1][1] = 5;
        currentEdge[0][0] = 5;
        currentEdge[0][1] = 3;
    }
    else if (cube[3][5] == col1 && cube[5][5] == col2)
    {
        currentEdge[0][0] = 3;
        currentEdge[0][1] = 3;
        currentEdge[1][0] = 5;
        currentEdge[1][1] = 5;
    }
    else if (cube[3][5] == col2 && cube[5][5] == col1)
    {
        currentEdge[1][0] = 3;
        currentEdge[1][1] = 3;
        currentEdge[0][0] = 5;
        currentEdge[0][1] = 5;
    }
    else if (cube[3][3] == col1 && cube[4][3] == col2)
    {
        currentEdge[0][0] = 3;
        currentEdge[0][1] = 5;
        currentEdge[1][0] = 4;
        currentEdge[1][1] = 3;
    }
    else if (cube[3][3] == col2 && cube[4][3] == col1)
    {
        currentEdge[1][0] = 3;
        currentEdge[1][1] = 5;
        currentEdge[0][0] = 4;
        currentEdge[0][1] = 3;
    }
    else
        return 0;
    return 1;
}
// outputs coordinates of required face
bool Solver::findFace(char col)
{
    for (int i = 0; i < 6; i++)
    {
        if (cube[i][4] == col)
        {
            currentFace = i;
            return 1;
        }
    }
    return 0;
}
// permutates all possible positions of the given corner to see if it matches the colors
bool Solver::compareCorner(int corner[3][2], char col1, char col2, char col3)
{
    // 012
    if (cube[corner[0][0]][corner[0][1]] == col1 && cube[corner[1][0]][corner[1][1]] == col2 && cube[corner[2][0]][corner[2][1]] == col3)
    {
        for (int i = 0; i < 3; i++)
        {
            currentCorner[i][0] = corner[i][0];
            currentCorner[i][1] = corner[i][1];
        }
        return 1;
    }
    // 021
    else if (cube[corner[0][0]][corner[0][1]] == col1 && cube[corner[2][0]][corner[2][1]] == col2 && cube[corner[1][0]][corner[1][1]] == col3)
    {

        currentCorner[0][0] = corner[0][0];
        currentCorner[0][1] = corner[0][1];
        currentCorner[1][0] = corner[2][0];
        currentCorner[1][1] = corner[2][1];
        currentCorner[2][0] = corner[1][0];
        currentCorner[2][1] = corner[1][1];

        return 1;
    }
    // 102
    else if (cube[corner[1][0]][corner[1][1]] == col1 && cube[corner[0][0]][corner[0][1]] == col2 && cube[corner[2][0]][corner[2][1]] == col3)
    {

        currentCorner[0][0] = corner[1][0];
        currentCorner[0][1] = corner[1][1];
        currentCorner[1][0] = corner[0][0];
        currentCorner[1][1] = corner[0][1];
        currentCorner[2][0] = corner[2][0];
        currentCorner[2][1] = corner[2][1];

        return 1;
    }
    // 120
    else if (cube[corner[1][0]][corner[1][1]] == col1 && cube[corner[2][0]][corner[2][1]] == col2 && cube[corner[0][0]][corner[0][1]] == col3)
    {

        currentCorner[0][0] = corner[1][0];
        currentCorner[0][1] = corner[1][1];
        currentCorner[1][0] = corner[2][0];
        currentCorner[1][1] = corner[2][1];
        currentCorner[2][0] = corner[0][0];
        currentCorner[2][1] = corner[0][1];

        return 1;
    }
    // 201
    else if (cube[corner[2][0]][corner[2][1]] == col1 && cube[corner[0][0]][corner[0][1]] == col2 && cube[corner[1][0]][corner[1][1]] == col3)
    {

        currentCorner[0][0] = corner[2][0];
        currentCorner[0][1] = corner[2][1];
        currentCorner[1][0] = corner[0][0];
        currentCorner[1][1] = corner[0][1];
        currentCorner[2][0] = corner[1][0];
        currentCorner[2][1] = corner[1][1];

        return 1;
    }
    // 210
    else if (cube[corner[2][0]][corner[2][1]] == col1 && cube[corner[1][0]][corner[1][1]] == col2 && cube[corner[0][0]][corner[0][1]] == col3)
    {

        currentCorner[0][0] = corner[2][0];
        currentCorner[0][1] = corner[2][1];
        currentCorner[1][0] = corner[1][0];
        currentCorner[1][1] = corner[1][1];
        currentCorner[2][0] = corner[0][0];
        currentCorner[2][1] = corner[0][1];

        return 1;
    }
    return 0;
}
// outputs coordinates of required corner
bool Solver::findCorner(char col1, char col2, char col3 = 'W')
{
    int corner[3][2] = { 0, 0, 4, 0, 3, 6 };
    if (compareCorner(corner, col1, col2, col3))
        return 1;
    int corner1[3][2] = { 0, 2, 5, 2, 3, 8 };
    if (compareCorner(corner1, col1, col2, col3))
        return 1;
    int corner2[3][2] = { 0, 6, 1, 0, 4, 2 };
    if (compareCorner(corner2, col1, col2, col3))
        return 1;
    int corner3[3][2] = { 0, 8, 1, 2, 5, 0 };
    if (compareCorner(corner3, col1, col2, col3))
        return 1;
    int corner4[3][2] = { 2, 0, 1, 6, 4, 8 };
    if (compareCorner(corner4, col1, col2, col3))
        return 1;
    int corner5[3][2] = { 2, 2, 1, 8, 5, 6 };
    if (compareCorner(corner5, col1, col2, col3))
        return 1;
    int corner6[3][2] = { 2, 6, 3, 0, 4, 6 };
    if (compareCorner(corner6, col1, col2, col3))
        return 1;
    int corner7[3][2] = { 2, 8, 3, 2, 5, 8 };
    if (compareCorner(corner7, col1, col2, col3))
        return 1;
    return 0;
}
// inserts given white edge into white cross
void Solver::insertWhiteEdge(char col, int order)
{
    findEdge(col, 'W'); // identifies location of required edge pair
    findFace(col);      // identifies location of centre of color col
    // CASE 1: WHITE ON TOP/BOTTOM
    if (currentEdge[1][0] == 0 || currentEdge[1][0] == 2)
    {
        // Case that edge is at top layer with white facing the top
        if (currentEdge[1][0] == 0)
        {
            while (currentEdge[0][0] != 1)
            { // makes us face the edge
                turnRight();
                sol.push_back(Turn::y);
                findEdge(col, 'W');
            }
            findFace(col);
            if (currentFace == 1)
            {
                return;
            }
            else if (order <= 1)
            {
                while (currentEdge[0][0] != currentFace)
                {

                    U();
                    sol.push_back(Turn::U);

                    findEdge(col, 'W');
                }
                return;
            }
            else
            {

                F();
                F();
                sol.push_back(Turn::F);
                sol.push_back(Turn::F);
            }
        }

        findEdge(col, 'W');
        findFace(col);

        // Case that edge is at bottom layer and white is facing the bottom
        if (currentEdge[1][0] == 2 /*checks if white is in bottom layer*/)
        {

            while (currentFace != 1)
            {
                turnRight();
                sol.push_back(Turn::y);
                findFace(col);
            } // turns whole cube until we're facing the color face
            findEdge(col, 'W');
            while (currentEdge[0][0] != currentFace)
            {
                D();
                sol.push_back(Turn::D);

                findEdge(col, 'W');
            } // matches edge with centre

            F();
            F();
            sol.push_back(Turn::F);
            sol.push_back(Turn::F);
            return;
        }
    }
    // CASE 2: COLOR ON TOP/BOTTOM
    else if (currentEdge[0][0] == 0 || currentEdge[0][0] == 2)
    {
        // case that edge is at top layer and color is at top
        if (currentEdge[0][0] == 0)
        {
            while (currentEdge[1][0] != 1)
            {
                turnRight();
                sol.push_back(Turn::y);
                findEdge(col, 'W');
            }
            F();
            F();
            sol.push_back(Turn::F);
            sol.push_back(Turn::F);
        }

        findFace(col);
        findEdge(col, 'W');
        // make it into a bottom case
        // case that edge is at bottom layer and color is at bottom
        if (currentEdge[0][0] == 2 /*checks if color is in bottom layer*/)
        {

            while (currentFace != 1)
            {
                turnRight();
                sol.push_back(Turn::y);

                findFace(col);
            } // turns whole cube until we're facing the color face
            findEdge(col, 'W');
            while (currentEdge[1][0] != currentFace)
            { // checks whether white is facing us
                D();
                sol.push_back(Turn::D);
                findEdge(col, 'W');
            } // matches edge with centre
            F_();
            U_();
            R();
            U();
            sol.push_back(Turn::F_);
            sol.push_back(Turn::U_);
            sol.push_back(Turn::R);
            sol.push_back(Turn::U);
            return;
        }
    }
    // CASE 3: EDGE IS IN THE MIDDLE
    else
    {
        while (currentEdge[1][0] != 1)
        {
            turnRight();
            sol.push_back(Turn::y);
            findEdge(col, 'W');
        }
        findFace(col);
        if (currentEdge[1][1] == 3)
        {
            switch (currentFace)
            {
            case 1:
                U();
                L_();
                U_();
                sol.push_back(Turn::U);
                sol.push_back(Turn::L_);
                sol.push_back(Turn::U_);
                break;
            case 4:
                L_();
                sol.push_back(Turn::L_);
                break;
            case 5:
                U();
                U();
                L_();
                U();
                U();
                sol.push_back(Turn::U);
                sol.push_back(Turn::U);
                sol.push_back(Turn::L_);
                sol.push_back(Turn::U);
                sol.push_back(Turn::U);

                break;
            case 3:
                U_();
                L_();
                U();
                sol.push_back(Turn::U_);
                sol.push_back(Turn::L_);
                sol.push_back(Turn::U);

                break;
            }
        }
        else
        {

            switch (currentFace)
            {
            case 1:

                U_();
                R();
                U();
                sol.push_back(Turn::U_);
                sol.push_back(Turn::R);
                sol.push_back(Turn::U);
                break;
            case 5:

                R();
                sol.push_back(Turn::R);
                break;
            case 4:

                U();
                U();
                R();
                U();
                U();
                sol.push_back(Turn::U);
                sol.push_back(Turn::U);
                sol.push_back(Turn::R);
                sol.push_back(Turn::U);
                sol.push_back(Turn::U);
                break;
            case 3:

                U();
                R();
                U_();
                sol.push_back(Turn::U);
                sol.push_back(Turn::R);
                sol.push_back(Turn::U_);

                break;
            }
        }
    }
}
// inserts given corner into first layer
void Solver::insertWhiteCorner(char col1, char col2)
{
    findCorner(col1, col2);
    int tempFace;
    // case that corner is already solved
    if (currentCorner[2][0] == 2 && cube[currentCorner[0][0]][4] == col1)
        return;

    // case white is facing up
    else if (currentCorner[2][0] == 0)
    {

        findFace(col1);
        tempFace = currentFace;
        findFace(col2);
        while ((tempFace != 1 || currentFace != 5) && (tempFace != 5 || currentFace != 1))
        {
            turnRight();
            sol.push_back(Turn::y);
            findFace(col1);
            tempFace = currentFace;
            findFace(col2);
        }
        findCorner(col1, col2);
        while (currentCorner[2][1] != 8)
        {
            U();
            sol.push_back(Turn::U);
            findCorner(col1, col2);
        }
        for (int i = 0; i < 3; i++)
        {
            sexy(0);
        }
        return;
    }
    findCorner(col1, col2);
    // case white is facing side
    if (currentCorner[0][0] == 0 || currentCorner[1][0] == 0)
    {

        findFace(col1);
        tempFace = currentFace;
        findFace(col2);
        while ((tempFace != 1 || currentFace != 5) && (tempFace != 5 || currentFace != 1))
        {
            turnRight();
            sol.push_back(Turn::y);
            findFace(col1);
            tempFace = currentFace;
            findFace(col2);
        }
        findCorner(col1, col2);
        while ((currentCorner[2][0] != 1 || currentCorner[2][1] != 2) && (currentCorner[2][0] != 5 || currentCorner[2][1] != 0))
        {
            U();
            sol.push_back(Turn::U);
            findCorner(col1, col2);
        }
        if (currentCorner[2][0] == 1)
        {
            for (int i = 0; i < 5; i++)
            {
                sexy(0);
            }
        }
        else
            sexy(0);
        return;
    }
    // case that corner is at bottom
    else
    {
        while ((currentCorner[0][0] != 1 || currentCorner[0][1] != 8) && (currentCorner[1][0] != 1 || currentCorner[1][1] != 8) && (currentCorner[2][0] != 1 || currentCorner[2][1] != 8))
        {
            turnRight();
            sol.push_back(Turn::y);
            findCorner(col1, col2);
        }
        sexy(0);
        insertWhiteCorner(col1, col2);
    }
}
// inserts given edge into second layer
void Solver::insertColorEdge(char col1, char col2)
{
    findEdge(col1, col2);
    int temp = findFace(col1);
    findFace(col2);
    if (currentEdge[0][0] == temp && currentEdge[1][0] == currentFace)
        return;
    // col1 on top
    if (currentEdge[0][0] == 0)
    {

        findFace(col2);
        while (currentFace != 1)
        {
            turnRight();
            sol.push_back(Turn::y);
            findFace(col2);
        }
        findEdge(col1, col2);
        while (currentEdge[1][0] != 1)
        {
            U();
            sol.push_back(Turn::U);
            findEdge(col1, col2);
        }
        findFace(col1);
        if (currentFace == 4)
        {
            U_();
            sol.push_back(Turn::U_);
            sexy(1);
            turnLeft();
            sol.push_back(Turn::y_);
            sexy(0);
        }
        else
        {
            U();
            sol.push_back(Turn::U);
            sexy(0);
            turnRight();
            sol.push_back(Turn::y);
            sexy(1);
        }
        return;
    }
    else if (currentEdge[1][0] == 0)
    {

        findFace(col1);
        while (currentFace != 1)
        {
            turnRight();
            sol.push_back(Turn::y);
            findFace(col1);
        }
        findEdge(col1, col2);
        while (currentEdge[0][0] != 1)
        {
            U();
            sol.push_back(Turn::U);
            findEdge(col1, col2);
        }
        findFace(col2);
        if (currentFace == 4)
        {
            U_();
            sol.push_back(Turn::U_);
            sexy(1);
            turnLeft();
            sol.push_back(Turn::y_);
            sexy(0);
        }
        else
        {
            U();
            sol.push_back(Turn::U);
            sexy(0);
            turnRight();
            sol.push_back(Turn::y);
            sexy(1);
        }
        return;
    }
    else
    {
        findEdge(col1, col2);

        while ((currentEdge[0][0] != 1 || currentEdge[0][1] != 5) && (currentEdge[1][0] != 1 || currentEdge[1][1] != 5))
        {
            turnRight();
            sol.push_back(Turn::y);
            findEdge(col1, col2);
        }
        sexy(0);
        turnRight();
        sol.push_back(Turn::y);
        sexy(1);

        insertColorEdge(col1, col2);
    }
}
// checks for an exact patter of yellows in the last layer
bool Solver::onecheckOLL(int yel[], int len)
{

    for (int i = 0; i < len; i++)
    {
        if (yel[i] <= 8)
        {
            if (cube[0][yel[i]] != 'Y')
                return 0;
        }
        else
        {
            switch (yel[i])
            {
            case 9:
                if (cube[4][0] != 'Y')
                    return 0;
                break;
            case 10:
                if (cube[4][1] != 'Y')
                    return 0;
                break;
            case 11:
                if (cube[4][2] != 'Y')
                    return 0;
                break;
            case 12:
                if (cube[1][0] != 'Y')
                    return 0;
                break;
            case 13:
                if (cube[1][1] != 'Y')
                    return 0;
                break;
            case 14:
                if (cube[1][1] != 'Y')
                    return 0;
                break;
            case 15:
                if (cube[5][0] != 'Y')
                    return 0;
                break;
            case 16:
                if (cube[5][1] != 'Y')
                    return 0;
                break;
            case 17:
                if (cube[5][2] != 'Y')
                    return 0;
                break;
            case 18:
                if (cube[3][0] != 'Y')
                    return 0;
                break;
            case 19:
                if (cube[3][1] != 'Y')
                    return 0;
                break;
            case 20:
                if (cube[3][2] != 'Y')
                    return 0;
                break;
            }
        }
    }
    return 1;
}
// checks for any permutation of yellows in last layer
bool Solver::checkOLL(int yel[], int len)
{
    for (int i = 0; i < 4; i++)
    {
        if (onecheckOLL(yel, len))
            return 1;
        else
            U();
        sol.push_back(Turn::U);
    }
    return 0;
}
//void Solver:: outputSol()
//{
//    for (int i = 0; i < sol.size(); i++)
//    {
//        if (i % 15 == 0)
//            cout << endl;
//        switch (sol[i])
//        {
//        case 0:
//            cout << "R ";
//            break;
//        case 1:
//            cout << "R_ ";
//            break;
//        case 2:
//            cout << "L ";
//            break;
//        case 3:
//            cout << "L_ ";
//            break;
//        case 4:
//            cout << "U ";
//            break;
//        case 5:
//            cout << "U_ ";
//            break;
//        case 6:
//            cout << "F ";
//            break;
//        case 7:
//            cout << "F_ ";
//            break;
//        case 8:
//            cout << "B ";
//            break;
//        case 9:
//            cout << "B_ ";
//            break;
//        case 10:
//            cout << "D ";
//            break;
//        case 11:
//            cout << "D_ ";
//            break;
//        case 12:
//            cout << "M ";
//            break;
//        case 13:
//            cout << "M_ ";
//            break;
//        case 14:
//            cout << "S ";
//            break;
//        case 15:
//            cout << "S_ ";
//            break;
//        case 16:
//            cout << "x ";
//            break;
//        case 17:
//            cout << "x_ ";
//            break;
//        case 18:
//            cout << "y ";
//            break;
//        case 19:
//            cout << "y_ ";
//            break;
//        case 20:
//            cout << "z ";
//            break;
//        case 21:
//            cout << "z_ ";
//            break;
//        }
//    }
//}
void Solver::solveCube()
{
    // solves cube then reverts it back to original unsolved form, leaving us with a solution vector
    char tempCube[6][9];
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            tempCube[i][j] = this->cube[i][j];
        }
    }
    solveCross();
    F2L();
    OLL();
    PLL();
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            this->cube[i][j] = tempCube[i][j];
        }
    }
}

//BEGINNER SOLVER INHERITED CLASS

void BeginnerSolver::yellowCross()
{
    int cross[5] = { 1, 3, 4, 5, 7 };
    int line[3] = { 3, 4, 5 };
    int lshape[3] = { 4, 5, 7 };
    if (checkOLL(cross, 5))
    {
        return;
    }
    else if (checkOLL(line, 3))
    {

        F();
        sol.push_back(Turn::F);
        sexy(0);
        F_();
        sol.push_back(Turn::F_);
        return;
    }
    else if (checkOLL(lshape, 3))
    {

        F();
        sol.push_back(Turn::F);
        sexy(0);
        F_();
        sol.push_back(Turn::F_);
        U();
        sol.push_back(Turn::U);
        F();
        sol.push_back(Turn::F);
        sexy(0);
        F_();
        sol.push_back(Turn::F_);
    }
    else
    {

        F();
        sol.push_back(Turn::F);
        sexy(0);
        F_();
        sol.push_back(Turn::F_);
        F();
        sol.push_back(Turn::F);
        sexy(0);
        F_();
        sol.push_back(Turn::F_);
        U();
        sol.push_back(Turn::U);
        F();
        sol.push_back(Turn::F);
        sexy(0);
        F_();
        sol.push_back(Turn::F_);
    }
}
// get all yellow corners in their correct positions, regardless of permutation
void BeginnerSolver::orientYellowCorners()
{
    int tl[3][2] = { 0, 0, 4, 0, 3, 6 };
    int tr[3][2] = { 0, 2, 5, 2, 3, 8 };
    int bl[3][2] = { 0, 6, 4, 2, 1, 0 };
    int br[3][2] = { 0, 8, 5, 0, 1, 2 };
    findFace('G');

    while (currentFace != 1)
    {
        turnRight();
        sol.push_back(Turn::y);
        findFace('G');
    }
    if (compareCorner(br, 'O', 'G', 'Y') && compareCorner(bl, 'R', 'G', 'Y') && compareCorner(tl, 'R', 'B', 'Y') && compareCorner(tr, 'O', 'B', 'Y'))
        return;
    else
    {
        if (compareCorner(br, 'O', 'G', 'Y'))
        {
            cor();
        }
        else if (compareCorner(bl, 'R', 'G', 'Y'))
        {
            turnLeft();
            sol.push_back(Turn::y_);
            cor();
        }
        else if (compareCorner(tl, 'R', 'B', 'Y'))
        {
            turnRight();
            turnRight();
            sol.push_back(Turn::y);
            sol.push_back(Turn::y);
            cor();
        }
        else if (compareCorner(tr, 'O', 'B', 'Y'))
        {
            turnRight();
            sol.push_back(Turn::y);
            cor();
        }
        else
            cor();
        orientYellowCorners();
    }
}
void BeginnerSolver::solveCross()
{
    findFace('W');
    while (currentFace != 0)
    {
        turnUp();
        sol.push_back(Turn::x);
        findFace('W');
    }
    findFace('G');
    while (currentFace != 1)
    {
        turnRight();
        sol.push_back(Turn::y);
        findFace('G');
    }

    insertWhiteEdge('R', 1);
    insertWhiteEdge('G', 2);
    insertWhiteEdge('O', 3);
    insertWhiteEdge('B', 4);
    turnUp();
    turnUp(); // makes  white at bottom
    sol.push_back(Turn::x);
    sol.push_back(Turn::x);
}
// first two layer solver
void BeginnerSolver::F2L()
{
    insertWhiteCorner('R', 'B');

    insertWhiteCorner('R', 'G');

    insertWhiteCorner('O', 'B');

    insertWhiteCorner('G', 'O');

    insertColorEdge('R', 'B');

    insertColorEdge('R', 'G');

    insertColorEdge('O', 'B');

    insertColorEdge('O', 'G');
}
// orientation of last layer
void BeginnerSolver::OLL()
{
    yellowCross();

    if ((cube[4][1] == 'B' && cube[5][1] == 'G') || (cube[4][1] == 'G' && cube[5][1] == 'B') || (cube[4][1] == 'R' && cube[5][1] == 'O') || (cube[4][1] == 'O' && cube[5][1] == 'R'))
    {

        while (cube[4][1] != cube[4][4] && cube[5][1] != cube[5][4])
        {
            U();
            sol.push_back(Turn::U);
        }
        if (cube[1][1] == cube[1][4])
        {
            return;
        }
        else
        {
            sune();
        }
    }

    while (((cube[5][1] != cube[5][4]) || (cube[1][1] != cube[1][4])) && ((cube[5][1] != cube[5][4]) || (cube[3][7] != cube[3][4])) && ((cube[4][1] != cube[4][4]) || (cube[1][1] != cube[1][4])) && ((cube[4][1] != cube[4][4]) || (cube[3][7] != cube[3][4])))
    {

        U();
        sol.push_back(Turn::U);
    }
    while ((cube[5][1] != cube[5][4] || cube[3][7] != cube[3][4]))
    {

        turnRight();
        sol.push_back(Turn::y);
    }
    sune();
    while ((cube[5][1] != cube[5][4]))
    {

        U();
        sol.push_back(Turn::U);
    }
}
// permutation of last layer
void BeginnerSolver::PLL()
{
    orientYellowCorners();

    for (int i = 0; i < 4; i++)
    {
        if (cube[0][8] == 'Y')
        {
            U();
            sol.push_back(Turn::U);
        }
        else if (cube[5][0] == 'Y')
        {
            reverseSexy();
            reverseSexy();
            U();
            sol.push_back(Turn::U);
        }
        else
        {
            reverseSexy();
            reverseSexy();
            reverseSexy();
            reverseSexy();
            U();
            sol.push_back(Turn::U);
        }
    }
    while (cube[1][1] != cube[1][4])
    {
        U();
        sol.push_back(Turn::U);
    }
}
