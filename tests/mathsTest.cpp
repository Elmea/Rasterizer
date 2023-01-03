#include <stdio.h>
#include <math.h>
#include "mathsTest.hpp"
#include <myMaths.hpp>

// ----------------------------[Float 2]----------------------------

bool test::TestFLoat2CrossProduct2D()
{
    myMaths::Float2 v{1, 2}, w{3, 4};
    return v.crossProduct2D(w) == -2;
}

bool test::TestFloat2DotProduct()
{
    myMaths::Float2 v{5, 5}, w{5, 5};
    return v.dotProduct(&w) == 50;
}

bool test::TestFloat2Magnitude()
{
    myMaths::Float2 v{5, 5};
    return v.magnitude() == sqrtf(50);
}

bool test::TestFloat2PlanRotation()
{
    float angle = 90;
    myMaths::Float2 v{0, 5};
    v.planRotation(angle);
    return ((int)v.x == -5 && (int)v.y == 0);
}

bool test::TestFloat2OperatorPlus()
{
    myMaths::Float2 v{1, 2}, w{3, 4}, u;
    u = v + w;
    return (u.x == 4 && u.y == 6);
}

bool test::TestFloat2OperatorTimes()
{
    myMaths::Float2 v{1, 2}, u;
    float test = 2;
    u = v * test;
    return (u.x == 2 && u.y == 4);
}

// ----------------------------[Float 3]----------------------------

bool test::TestFLoat3CrossProduct()
{
    myMaths::Float3 v{5, 5, 5}, w{5, 5, 5};
    myMaths::Float3 test = v.crossProduct(w);
    return (test.x == 0 && test.y == 0 && test.z == 0);
}

bool test::TestFloat3DotProduct()
{
    myMaths::Float3 v{5, 5, 5}, w{5, 5, 5};
    return v.dotProduct(w) == 75;
}

bool test::TestFloat3Magnitude()
{
    myMaths::Float3 v{5, 5, 5};
    return v.magnitude() == sqrtf(75);
}

bool test::TestFloat3Normalize()
{
    myMaths::Float3 v{5, 5, 5};
    v.normalize();
    return (v.x == 5/sqrtf(75) && v.y == 5/sqrtf(75) && v.z == 5/sqrtf(75));
}

bool test::TestFloat3GetNormalized()
{
    //a voir
    return true;
}

bool test::TestFloat3OperatorPlus()
{
    myMaths::Float3 v{1, 2, 4}, w{3, 4, 4}, u;
    u = v + w;
    return (u.x == 4 && u.y == 6 && u.z == 8);
}

bool test::TestFloat3OperatorTimes()
{
    myMaths::Float3 v{1, 2, 3}, u;
    float test = 2;
    u = v * test;
    return (u.x == 2 && u.y == 4 && u.z == 6);
}

// ----------------------------[Float 4]----------------------------

bool test::TestFloat4DotProduct()
{
    myMaths::Float4 v{5, 5, 5, 5}, w{5, 5, 5, 5};
    return v.dotProduct(w) == 100;
}

bool test::TestFloat4Magnitude()
{
    myMaths::Float4 v{5, 5, 5, 5};
    return v.magnitude() == sqrtf(75);
}

bool test::TestFloat4Normalize()
{
    myMaths::Float4 v{5, 5, 5, 5};
    v.normalize();
    return (v.x == 5/sqrtf(75) && v.y == 5/sqrtf(75) && v.z == 5/sqrtf(75) && v.w == 5/sqrtf(75));
}

bool test::TestFloat4Homogenize()
{
    myMaths::Float4 v{1, 2, 3, 5};
    v.homogenize();
    //printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w);
    return (v.x == 0.2f && v.y == 0.4f && v.z == 0.6f && v.w == 1);
}

bool test::TestFloat4OperatorPlus()
{
    myMaths::Float4 v{1, 2, 4, 5}, w{3, 4, 4, 6}, u;
    u = v + w;
    return (u.x == 4 && u.y == 6 && u.z == 8);
}

bool test::TestFloat4OperatorTimes()
{
    myMaths::Float4 v{1, 2, 3, 4}, u;
    float test = 2;
    u = v * test;
    return (u.x == 2 && u.y == 4 && u.z == 6);
}

// ----------------------------[Matrix]----------------------------

bool test::TestMatrixOperatorEqual1()
{
    myMaths::Mat4 m;
    float m1[4][4] = {{1, 2, 3, 4}, {4, 3, 2, 1}, {1, 2, 3, 4}, {4, 3, 2, 1}};
    m = m1;
    //printf("%f\n",m.mat[3][0]);
    return(m.mat[3][0] == 4);
}

bool test::TestMatrixOperatorEqual2()
{
    myMaths::Mat4 m1;
    myMaths::Mat4 m2;
    float m[4][4] = {{1, 2, 3, 4}, {4, 3, 2, 1}, {1, 2, 3, 4}, {4, 3, 2, 1}};
    m1 = m;
    m2 = m1;
    return(m2.mat[3][0] == 4);
}

bool test::TestMatrixOperatorTimes1()
{
    myMaths::Mat4 m;
    float m1[4][4] = {{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}};
    m = m1;
    myMaths::Float4 v1{2, 2, 2, 2};
    myMaths::Float4 v2 = (m*v1);
    return(v2.x == 16 && v2.y == 16 && v2.z == 16 && v2.w == 16);
  
}

bool test::TestMatrixOperatorTimes2()
{
    myMaths::Mat4 m1, m2;
    float m11[4][4] = {{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}};
    m1 = m11;
    float m22[4][4] = {{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}};
    m2 = m22;
    m1 = m1*m2;
    return(m1.mat[1][1] == 16);

}

bool test::TestMatrixOperatorTimes3()
{
    myMaths::Mat4 m;
    float m1[4][4] = {{2, 2, 2, 2}, {3, 3, 3, 3}, {1.5f, 1.5f, 1.5f, 1.5f}, {7.25f, 7.25f, 7.25f, 7.25f}};
    m = m1;
    float test = 3.5f;
    m = m*test;
    return(m.mat[0][1] == 7 && m.mat[1][1] == 10.5f && m.mat[2][1] == 5.25f && m.mat[3][1] == 25.375f);

}

bool test::TestMatrixOperatorTimes4()
{
    myMaths::Mat4 m;
    float m1[4][4] = {{2, 2, 2, 2}, {3, 3, 3, 3}, {1.5f, 1.5f, 1.5f, 1.5f}, {7.25f, 7.25f, 7.25f, 7.25f}};
    m = m1;
    int test = 3;
    m = m*test;
    return(m.mat[0][1] == 6 && m.mat[1][1] == 9 && m.mat[2][1] == 4.5f && m.mat[3][1] == 21.75f);

}

bool test::TestMatrixCreateTransformMatrix()
{
    myMaths::Mat4 m;
    myMaths::Float3 rotation{((sqrtf(3))/2)*180/3.141592, ((sqrtf(3))/2)*180/3.141592, ((sqrtf(3))/2)*180/3.141592};
    myMaths::Float3 position{1, 1, 0};
    myMaths::Float3 scale{1, 1, 1};
    m = m.CreateTransformMatrix(position,rotation, scale);
    
    for(int i=0; i<4; i++)
    {
        printf("{");
        for(int j=0; j<4; j++)
        {
            printf("%f; ",m.mat[i][j]);
        }
        printf("}");
        printf("\n");
    }
    

    int checkCount = 0;

    if (m.mat[0][0] <= 0.69f && m.mat[0][0] >= 0.67f)
        checkCount++;
    
    if (m.mat[0][1] <= 0.38f && m.mat[0][1] >= 0.36f)
        checkCount++;
    
    if (m.mat[0][2] <= 1.19f && m.mat[0][2] >= 1.17f)
        checkCount++;
    
    if (m.mat[0][3] == 0.f)
        checkCount++;
    
      if (m.mat[1][0] <= 1.14f && m.mat[1][0] >= 1.12f)
        checkCount++;
    
    if (m.mat[1][1] <= 0.85f && m.mat[1][1] >= 0.83f)
        checkCount++;
    
    if (m.mat[1][2] <= -0.072f && m.mat[1][2] >= -0.074f)
        checkCount++;
    
    if (m.mat[1][3] == 0.f)
        checkCount++;
    
      if (m.mat[2][0] == 0.f)
        checkCount++;
    
    if (m.mat[2][1] == 0.f)
        checkCount++;
    
    if (m.mat[2][2] == 0.f)
        checkCount++;
    
    if (m.mat[2][3] == 0.f)
        checkCount++;
    
     if (m.mat[3][0] == 0.f)
        checkCount++;
    
    if (m.mat[3][1] == 0.f)
        checkCount++;
    
    if (m.mat[3][2] == 0.f)
        checkCount++;
    
    if (m.mat[3][3] == 1.f)
        checkCount++;
    
     return checkCount == 16;

}



bool test::TestMatrixDeterminent()
{
    myMaths::Mat4 matrix;
    float matrice[4][4] = {{1.f, 2.f, 3.f, 4.f},
                           {2.f, 3.f, 4.f, 1.f},
                           {3.f, 4.f, 1.f, 2.f},
                           {4.f, 1.f, 2.f, 3.f}};

    matrix = matrice;

    //printf("%f\n", matrix.getDeterminent());

    return matrix.getDeterminent() == 160.f;
}

bool test::TestMatrixInvert()
{
    myMaths::Mat4 matrix;
    float matrice[4][4] = {{1.f, 3.f, 0.f, 0.f},
                           {2.f, 4.f, 0.f, 0.f},
                           {0.f, 0.f, 1.f, 0.f},
                           {0.f, 0.f, 0.f, 1.f}};

    matrix = matrice;

    myMaths::Mat4 temp;
    temp = matrix.getInverseMatrix();

    int checkCount = 0;

    if (temp.mat[0][0] == -2.f)
        checkCount++;
    if (temp.mat[0][1] == 1.5f)
        checkCount++;
    if (temp.mat[0][2] == 0.f)
        checkCount++;
    if (temp.mat[0][3] == 0.f)
        checkCount++;


    if (temp.mat[1][0] == 1.f)
        checkCount++;
    if (temp.mat[1][1] == -0.5f)
        checkCount++;
    if (temp.mat[1][2] == 0.f)
        checkCount++;
    if (temp.mat[1][3] == 0.f)
        checkCount++;

    if (temp.mat[2][0] == -0.f)
        checkCount++;
    if (temp.mat[2][1] == 0.f)
        checkCount++;
    if (temp.mat[2][2] == 1.f)
        checkCount++;
    if (temp.mat[2][3] == 0.f)
        checkCount++;

    if (temp.mat[3][0] == 0.f)
        checkCount++;
    if (temp.mat[3][1] == 0.f)
        checkCount++;
    if (temp.mat[3][2] == 0.f)
        checkCount++;
    if (temp.mat[3][3] == 1.f)
        checkCount++;

    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         printf("%f ", temp.mat[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("check : %d\n", checkCount);
    return checkCount == 16;
}

//-------------------------------------------------------------------------------------------

int main()
{
    printf("[----------------------------[Float 2]----------------------------]\n");
    printf("\n");
    if(test::TestFLoat2CrossProduct2D())
    printf("    - TestFLoat2CrossProduct2D √\n");
    else
    printf("    - TestFLoat2CrossProduct2D X\n");

    printf("\n");
    if(test::TestFloat2DotProduct())
    printf("    - TestFloat2DotProduct √\n");
    else
    printf("    - TestFloat2DotProduct X\n");

    printf("\n");
    if(test::TestFloat2Magnitude())
    printf("    - TestFloat2Magnitude √\n");
    else
    printf("    - TestFloat2Magnitude X\n");

    printf("\n");
    if(test::TestFloat2PlanRotation())
    printf("    - TestFloat2PlanRotation √\n");
    else
    printf("    - TestFloat2PlanRotation X\n");

    printf("\n");
    if(test::TestFloat2OperatorPlus())
    printf("    - TestFloat2OperatorPlus √\n");
    else
    printf("    - TestFloat2OperatorPlus X\n");

    printf("\n");
    if(test::TestFloat2OperatorTimes())
    printf("    - TestFloat2OperatorTimes √\n");
    else
    printf("    - TestFloat2OperatorTimes X\n");

    printf("\n");
    printf("[----------------------------[Float 3]----------------------------]\n");
    printf("\n");
    if(test::TestFLoat3CrossProduct())
    printf("    - TestFLoat3CrossProduct √\n");
    else
    printf("    - TestFLoat3CrossProduct X\n");

    printf("\n");
    if(test::TestFloat3DotProduct())
    printf("    - TestFloat3DotProduct √\n");
    else
    printf("    - TestFloat3DotProduct X\n");

    printf("\n");
    if(test::TestFloat3Magnitude())
    printf("    - TestFloat3Magnitude √\n");
    else
    printf("    - TestFloat3Magnitude X\n");

    printf("\n");
    if(test::TestFloat3Normalize())
    printf("    - TestFloat3Normalize √\n");
    else
    printf("    - TestFloat3Normalize X\n");

    printf("\n");
    if(test::TestFloat3OperatorPlus())
    printf("    - TestFloat3OperatorPlus √\n");
    else
    printf("    - TestFloat3OperatorPlus X\n");

    printf("\n");
    if(test::TestFloat3OperatorTimes())
    printf("    - TestFloat3OperatorTimes √\n");
    else
    printf("    - TestFloat3OperatorTimes X\n");

    printf("\n");
    printf("[----------------------------[Float 4]----------------------------]\n");
    printf("\n");
    if(test::TestFloat4DotProduct())
    printf("    - TestFloat4DotProduct √\n");
    else
    printf("    - TestFloat4DotProduct X\n");

    printf("\n");
    if(test::TestFloat4Magnitude())
    printf("    - TestFloat4Magnitude √\n");
    else
    printf("    - TestFloat4Magnitude X\n");

    printf("\n");
    if(test::TestFloat4Normalize())
    printf("    - TestFloat4Normalize √\n");
    else
    printf("    - TestFloat4Normalize X\n");

    printf("\n");
    if(test::TestFloat4Homogenize())
    printf("    - TestFloat4Homogenize √\n");
    else
    printf("    - TestFloat4Homogenize X\n");

    printf("\n");
    if(test::TestFloat4OperatorPlus())
    printf("    - TestFloat4OperatorPlus √\n");
    else
    printf("    - TestFloat4OperatorPlus X\n");

    printf("\n");
    if(test::TestFloat4OperatorTimes())
    printf("    - TestFloat4OperatorTimes √\n");
    else
    printf("    - TestFloat4OperatorTimes X\n");

    printf("\n");
    printf("[----------------------------[Matrix]----------------------------]\n");
    printf("\n");
    if(test::TestMatrixOperatorEqual1())
    printf("    - TestMatrixOperatorEqual1 √\n");
    else
    printf("    - TestMatrixOperatorEqual1 X\n");
    
    printf("\n");
    if(test::TestMatrixOperatorEqual2())
    printf("    - TestMatrixOperatorEqual2 √\n");
    else
    printf("    - TestMatrixOperatorEqual2 X\n");

    printf("\n");
    if(test::TestMatrixOperatorTimes1())
    printf("    - TestMatrixOperatorTimes1 √\n");
    else
    printf("    - TestMatrixOperatorTimes1 X\n");

    printf("\n");
    if(test::TestMatrixOperatorTimes2())
    printf("    - TestMatrixOperatorTimes2 √\n");
    else
    printf("    - TestMatrixOperatorTimes2 X\n");

    printf("\n");
    if(test::TestMatrixOperatorTimes3())
    printf("    - TestMatrixOperatorTimes3 √\n");
    else
    printf("    - TestMatrixOperatorTimes3 X\n");

    printf("\n");
    if(test::TestMatrixOperatorTimes4())
    printf("    - TestMatrixOperatorTimes4 √\n");
    else
    printf("    - TestMatrixOperatorTimes4 X\n");

    printf("\n");
    if(test::TestMatrixCreateTransformMatrix())
    printf("    - TestMatrixCreateTransformMatrix √\n");
    else
    printf("    - TestMatrixCreateTransformMatrix X\n");

    printf("\n");
    if(test::TestMatrixDeterminent())
    printf("    - TestMatrixDeterminent √\n");
    else
    printf("    - TestMatrixDeterminent X\n");

    printf("\n");
    if(test::TestMatrixInvert())
    printf("    - TestMatrixInvert √\n");
    else
    printf("    - TestMatrixInvert X\n");
    printf("\n");
    
    return 0;
}