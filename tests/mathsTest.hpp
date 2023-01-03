#pragma once 

namespace test
{
    bool TestFLoat2CrossProduct2D();
    bool TestFloat2DotProduct();
    bool TestFloat2Magnitude();
    bool TestFloat2PlanRotation();
    bool TestFloat2OperatorPlus();
    bool TestFloat2OperatorTimes();

    bool TestFLoat3CrossProduct();
    bool TestFloat3DotProduct();
    bool TestFloat3Magnitude();
    bool TestFloat3Normalize();
    bool TestFloat3GetNormalized();
    bool TestFloat3OperatorPlus();
    bool TestFloat3OperatorTimes();

    bool TestFloat4DotProduct();
    bool TestFloat4Magnitude();
    bool TestFloat4Normalize();
    bool TestFloat4Homogenize();
    bool TestFloat4OperatorPlus();
    bool TestFloat4OperatorTimes();

    bool TestMatrixOperatorEqual1();
    bool TestMatrixOperatorEqual2();
    bool TestMatrixOperatorTimes1();
    bool TestMatrixOperatorTimes2();
    bool TestMatrixOperatorTimes3();
    bool TestMatrixOperatorTimes4();
    bool TestMatrixCreateTransformMatrix();
    bool TestMatrixDeterminent();
    bool TestMatrixInvert();
}