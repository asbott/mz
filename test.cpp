#include "mz_vector.hpp"
#include "mz_matrix.hpp"

#include <iostream>
#include <ostream>

int main() {
    mz::fvec2 f2 = { .5f, .1f };
    mz::dvec3 d3 = { 1.7, 9.3, 51.7 };
    mz::ivec4 i4 = { 66, 67, 68, 69 };

    mz::u64vec4 u644 = { 1, 2, 3, 4 };

    f2 += u644;

    i4 = f2 + d3;

    mz::fmat4 mat = mz::projection::ortho<float>(0, 1, 0, 1, -1, 1);

    std::cout << "f2: "     << f2     << "\n";
    std::cout << "d3: "     << d3     << "\n";
    std::cout << "i4: "     << i4     << "\n";
    std::cout << "u644: "   << u644   << "\n";
    std::cout << "mat: "    << mat    << "\n";
}