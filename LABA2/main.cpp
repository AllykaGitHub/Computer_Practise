#include <iostream>
#include <fstream>
#include "linear.cpp"
#include "operator.cpp"

#include "test_runner.h"
#include "linear_test.h"
#include "PCA.h"

using namespace Linear;

void runTests() {
    TestRunner tr;
    tr.RunTest(TestLinearLibrary, "Usual matrix test");
    tr.RunTest(TestDiagonalMatrix, "Diagonal matrix test");
    tr.RunTest(TestUnitMatrix, "Unit matrix test");
    tr.RunTest(TestUpperTriangularMatrix, "Upper triangular matrix test");
    tr.RunTest(TestLowerTriangular, "Lower triangular matrix test");
    tr.RunTest(TestSymmetricMatrix, "Symmetric matrix test");
    tr.RunTest(TestVectors, "Vectors test");
}

int main() {
    runTests();

    Matrix<double> data = FromFile<double>("data.txt");
    Matrix<double> scores = FromFile<double>("scores.txt");
    Matrix<double> loadings = FromFile<double>("loadings.txt");

    PCA d(data);

    d.center();
    d.scale();

    d.show();
    auto [T, P, E] = d.nipals(4);
    std::cout << T << "\n\n" << P << "\n\n" << E << "\n\n";

    auto deviation = d.deviation();
    auto scope = d.scope();
    for (double sc : scope) {
        std::cout << sc << ' ';
    }

    std::cout << '\n';

    for (double dev : deviation) {
        std::cout << dev << ' ';
    }



    std::cout << '\n' << d.dispersion_mean() << ' ' << d.dispersion_general() << ' ' << d.dispersion_explained() << '\n';

    return 0;
}
