#include <iostream>
#include <vector>

const uint64_t mod = 1e9 + 7; // just a big prime

uint64_t solve(const std::vector<uint64_t> &A) {
    uint64_t p = 2;        // starting power
    uint64_t m = 2 * A[0]; // starting multiplier
    uint64_t s = 0;        // starting sum

    // iterate from A[1] to A[N]
    for (auto it = A.cbegin() + 1; it != A.cend(); ++it) {
        auto n = *it;            // get n from iterator
        s = (2*s + m * n) % mod; // update running sum
        m = (m + p * n) % mod;   // update multiplier
        p = (2 * p) % mod;       // update power
    }

    return s;
}

int main() {
    size_t T;      // declare T
    std::cin >> T; // read T

    for (auto t = 0; t < T; ++t) {        // for T testcases
        size_t N;                           // declare N
        std::cin >> N;                      // read N
        std::vector<uint64_t> A(N + 1);     // create vector of N + 1 elements
        for (auto &n : A) std::cin >> n;    // for all elements, read in
        std::cout << solve(A) << std::endl; // print solution
    }
}
