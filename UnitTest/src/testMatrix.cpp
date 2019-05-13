#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.hpp"
#include "Jacobi.hpp"

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
            Solver::Matrix mat1 = Solver::Matrix(2, 3, { 4,2,3,5,7,6 });
            Solver::Matrix mat2 = Solver::Matrix(2, 3, { 1,8,9,3,5,4 });
            // Add to Matrix
            mat1.add(mat2);
            // Expected result
            Solver::Matrix result = Solver::Matrix(2, 3, { 5,10,12,8,12,10 });
            Assert::IsTrue(mat1 == result);
        }

        TEST_METHOD(SubtractMatrix)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 4, { 6,5,4,1,2,3,-7,8 });
            Solver::Matrix mat2 = Solver::Matrix(2, 4, { 1,4,2,3,6,-1,0,5 });
            // Subtract from matrix
            mat1.subtract(mat2);
            // Expected result
            Solver::Matrix result = Solver::Matrix(2, 4, { 5,1,2,-2,-4,4,-7,3 });
            Assert::IsTrue(mat1 == result);
        }

        TEST_METHOD(ScalarMultiplication)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 3, { 3,2,5,6,1,7 });
            // Multiply Matrix by a number
            mat1.multiplyBy(4.0);
            // Expected result
            Solver::Matrix result = Solver::Matrix(2, 3, { 12,8,20,24,4,28 });
            Assert::IsTrue(mat1 == result);
        }

        TEST_METHOD(DotMatrices)
        {
            Solver::Matrix mat1 = Solver::Matrix(2, 3, { 4,7,6,2,3,1 });
            Solver::Matrix mat2 = Solver::Matrix(3, 1, { 8,5,9 });
            // Expected result
            Solver::Matrix expectedResult(2, 1, { 121,40 });
            // Actual result
            Solver::Matrix actualResult = mat1.dot(mat2);
            Assert::IsTrue(expectedResult == actualResult);
            
            mat1.resizeMarix(2, 4, {2,3,5,1,4,6,0,7});
            mat2.resizeMarix(4, 1, { 3,4,2,9 });
            // Expected result
            expectedResult = Solver::Matrix(2, 1, { 37,99 });
            // Actual result
            actualResult = mat1.dot(mat2);
            Assert::IsTrue(expectedResult == actualResult);
        }

        TEST_METHOD(DiagonallyDominantMatrices)
        {
            Solver::Matrix mat1 = Solver::Matrix(3, 3, {
                     3,-2, 1,
                     1,-3, 2,
                    -1, 2, 4
                });
            Assert::IsTrue(mat1.isDiagonallyDominant());

            mat1 = Solver::Matrix(3, 3, {
                    -2, 2, 1,
                     1, 3, 2,
                     1,-2, 0
                });
            Assert::IsTrue(!mat1.isDiagonallyDominant());

            mat1 = Solver::Matrix(3, 3, {
                    -4, 2, 1,
                     1, 6, 2,
                     1,-2, 5
                });
            Assert::IsTrue(mat1.isDiagonallyDominant());
        }

        TEST_METHOD(JacobiSolver)
        {
            Solver::Matrix A = Solver::Matrix(2, 2, { 2, 1, 5, 7 });
            Solver::Matrix B = Solver::Matrix(2, 1, { 11,13 });
            Solver::Matrix X = Solver::Matrix(2, 1, { 1,1 });
            Solver::Jacobi solver(&A, &B, &X, 25, 0.0000001);
            solver.solve();
            Assert::AreEqual(X.getValue(0, 0), 7.111, 0.001);
            Assert::AreEqual(X.getValue(1, 0), -3.222, 0.001);
            
            A = Solver::Matrix(3, 3, { 2, 1, 1, -1, 3, -1, 1, -1, 2 });
            B = Solver::Matrix(3, 1, { 7,2,5 });
            X = Solver::Matrix(3, 1, { 0,0,0 });
            solver = Solver::Jacobi(&A, &B, &X, 30, 0.000005);
            solver.solve();
            Assert::AreEqual(X.getValue(0, 0), 1.0, 0.000005);
            Assert::AreEqual(X.getValue(1, 0), 2.0, 0.000005);
            Assert::AreEqual(X.getValue(2, 0), 3.0, 0.000005);

            A = Solver::Matrix(5, 5,
                { 
                     300,-100,   0,   0,   0,
                    -100, 200,-100,   0,   0,
                       0,-100, 200,-100,   0,
                       0,   0,-100, 200,-100,
                       0,   0,   0,-100, 300
                });
            B = Solver::Matrix(5, 1, { 200 * 100,0,0,0,200 * 500 });
            X = Solver::Matrix(5, 1, { 0,0,0,0,0 });
            solver = Solver::Jacobi(&A, &B, &X, 100, 0.0000001);
            solver.solve();
            // Expected result
            Assert::AreEqual(X.getValue(0, 0), 140, 0.000001);
            Assert::AreEqual(X.getValue(1, 0), 220, 0.000001);
            Assert::AreEqual(X.getValue(2, 0), 300, 0.000001);
            Assert::AreEqual(X.getValue(3, 0), 380, 0.000001);
            Assert::AreEqual(X.getValue(4, 0), 460, 0.000001);
        }

    };
}