#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(TestMatrix)
    {
    public:

        TEST_METHOD(InitialiseMatrix)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 3);
            Assert::AreEqual(mat1.getValue(0, 0), 0.0);
            Assert::AreEqual(mat1.getValue(0, 1), 0.0);
            Assert::AreEqual(mat1.getValue(0, 2), 0.0);
            Assert::AreEqual(mat1.getValue(1, 0), 0.0);
            Assert::AreEqual(mat1.getValue(1, 1), 0.0);
            Assert::AreEqual(mat1.getValue(1, 2), 0.0);

            mat1 = Solver::Matrix(2, 3, {4,6,5,2,3,7});
            Assert::AreEqual(mat1.getValue(0, 0), 4.0);
            Assert::AreEqual(mat1.getValue(0, 1), 6.0);
            Assert::AreEqual(mat1.getValue(0, 2), 5.0);
            Assert::AreEqual(mat1.getValue(1, 0), 2.0);
            Assert::AreEqual(mat1.getValue(1, 1), 3.0);
            Assert::AreEqual(mat1.getValue(1, 2), 7.0);
        }

        TEST_METHOD(AddMatrix)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 3);
            Solver::Matrix mat2 = Solver::Matrix(2, 3);
            mat1.setValue(4.0,  0, 0);
            mat1.setValue(2.0,  0, 1);
            mat1.setValue(3.0,  0, 2);
            mat1.setValue(5.0,  1, 0);
            mat1.setValue(7.0,  1, 1);
            mat1.setValue(6.0,  1, 2);

            mat2.setValue(1.0,  0, 0);
            mat2.setValue(8.0,  0, 1);
            mat2.setValue(9.0,  0, 2);
            mat2.setValue(3.0,  1, 0);
            mat2.setValue(5.0,  1, 1);
            mat2.setValue(4.0,  1, 2);

            mat1.add(&mat2);
            Assert::AreEqual(mat1.getValue(0, 0), 5.0);
            Assert::AreEqual(mat1.getValue(0, 1), 10.0);
            Assert::AreEqual(mat1.getValue(0, 2), 12.0);
            Assert::AreEqual(mat1.getValue(1, 0), 8.0);
            Assert::AreEqual(mat1.getValue(1, 1), 12.0);
            Assert::AreEqual(mat1.getValue(1, 2), 10.0);
        }

        TEST_METHOD(SubtractMatrix)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 4);
            Solver::Matrix mat2 = Solver::Matrix(2, 4);
            mat1.setValue(6.0, 0, 0);
            mat1.setValue(5.0, 0, 1);
            mat1.setValue(4.0, 0, 2);
            mat1.setValue(1.0, 0, 3);
            mat1.setValue(2.0, 1, 0);
            mat1.setValue(3.0, 1, 1);
            mat1.setValue(-7.0, 1, 2);
            mat1.setValue(8.0, 1, 3);

            mat2.setValue(1.0, 0, 0);
            mat2.setValue(4.0, 0, 1);
            mat2.setValue(2.0, 0, 2);
            mat2.setValue(3.0, 0, 3);
            mat2.setValue(6.0, 1, 0);
            mat2.setValue(-1.0, 1, 1);
            mat2.setValue(0.0, 1, 2);
            mat2.setValue(5.0, 1, 3);

            mat1.subtract(&mat2);
            Assert::AreEqual(mat1.getValue(0, 0), 5.0);
            Assert::AreEqual(mat1.getValue(0, 1), 1.0);
            Assert::AreEqual(mat1.getValue(0, 2), 2.0);
            Assert::AreEqual(mat1.getValue(0, 3), -2.0);
            Assert::AreEqual(mat1.getValue(1, 0), -4.0);
            Assert::AreEqual(mat1.getValue(1, 1), 4.0);
            Assert::AreEqual(mat1.getValue(1, 2), -7.0);
            Assert::AreEqual(mat1.getValue(1, 3), 3.0);
        }

        TEST_METHOD(ScalarMultiplication)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 3);
            mat1.setValue(3.0,  0, 0);
            mat1.setValue(2.0,  0, 1);
            mat1.setValue(5.0,  0, 2);
            mat1.setValue(6.0,  1, 0);
            mat1.setValue(1.0,  1, 1);
            mat1.setValue(7.0,  1, 2);

            mat1.multiplyBy(4.0);
            Assert::AreEqual(mat1.getValue(0, 0), 12.0);
            Assert::AreEqual(mat1.getValue(0, 1), 8.0);
            Assert::AreEqual(mat1.getValue(0, 2), 20.0);
            Assert::AreEqual(mat1.getValue(1, 0), 24.0);
            Assert::AreEqual(mat1.getValue(1, 1), 4.0);
            Assert::AreEqual(mat1.getValue(1, 2), 28.0);
        }

        TEST_METHOD(DotMatrices)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 3);
            Solver::Matrix mat2 = Solver::Matrix(3, 1);
            mat1.setValue(4.0, 0, 0);
            mat1.setValue(7.0, 0, 1);
            mat1.setValue(6.0, 0, 2);
            mat1.setValue(2.0, 1, 0);
            mat1.setValue(3.0, 1, 1);
            mat1.setValue(1.0, 1, 2);

            mat2.setValue(8.0, 0, 0);
            mat2.setValue(5.0, 1, 0);
            mat2.setValue(9.0, 2, 0);

            Solver::Matrix result;
            result = mat1.dot(mat2);

            Assert::AreEqual(result.getRowSize(), static_cast<std::size_t>(2));
            Assert::AreEqual(result.getColSize(), static_cast<std::size_t>(1));

            Assert::AreEqual(result.getValue(0, 0), 121.0);
            Assert::AreEqual(result.getValue(1, 0), 40.0);
            
            mat1.resizeMarix(2, 4);
            mat2.resizeMarix(4, 1);

            mat1.setValue(2.0, 0, 0);
            mat1.setValue(3.0, 0, 1);
            mat1.setValue(5.0, 0, 2);
            mat1.setValue(1.0, 0, 3);
            mat1.setValue(4.0, 1, 0);
            mat1.setValue(6.0, 1, 1);
            mat1.setValue(0.0, 1, 2);
            mat1.setValue(7.0, 1, 3);
            mat2.setValue(3.0, 0, 0);
            mat2.setValue(4.0, 1, 0);
            mat2.setValue(2.0, 2, 0);
            mat2.setValue(9.0, 3, 0);

            result = mat1.dot(mat2);

            Assert::AreEqual(result.getRowSize(), static_cast<std::size_t>(2));
            Assert::AreEqual(result.getColSize(), static_cast<std::size_t>(1));

            Assert::AreEqual(result.getValue(0, 0), 37.0);
            Assert::AreEqual(result.getValue(1, 0), 99.0);
        }

    };
}