#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(TestMatrix)
    {
    public:

        TEST_METHOD(AddMatrix)
        {
            // TODO: Your test code here
            Solver::Matrix mat1 = Solver::Matrix(2, 2);
            Solver::Matrix mat2 = Solver::Matrix(2, 2);
            mat1.setValue(1, 0, 0);
            mat1.setValue(1, 0, 1);
            mat1.setValue(1, 1, 0);
            mat1.setValue(1, 1, 1);

            mat2.setValue(1, 0, 0);
            mat2.setValue(1, 0, 1);
            mat2.setValue(1, 1, 0);
            mat2.setValue(1, 1, 1);

            mat1.add(&mat2);
            Assert::AreEqual(mat1.getValue(0, 0), 2.0);
            Assert::AreEqual(mat1.getValue(0, 1), 2.0);
            Assert::AreEqual(mat1.getValue(1, 0), 2.0);
            Assert::AreEqual(mat1.getValue(1, 1), 2.0);

            mat2.subtract(&mat1);
            Assert::AreEqual(mat2.getValue(0, 0), -1.0);
            Assert::AreEqual(mat2.getValue(0, 1), -1.0);
            Assert::AreEqual(mat2.getValue(1, 0), -1.0);
            Assert::AreEqual(mat2.getValue(1, 1), -1.0);
        }

    };
}