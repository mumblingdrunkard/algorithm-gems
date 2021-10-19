/*
 * Solution for https://www.codechef.com/problems/RGAME
 * Copyright 2021 mumblingdrunkard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/


#include <iostream>
#include <vector>

const uint64_t mod = 1e9 + 7;

uint64_t solve(size_t N) {
    uint64_t A_0;
    std::cin >> A_0;

    uint64_t p = 2;
    uint64_t m = 2 * A_0;
    uint64_t s = 0;

    for (auto i = 0; i < N; ++i) {
        int64_t n;
        std::cin >> n;

        s = (2*s + m * n) % mod;
        m = (m + p * n) % mod;
        p = (2 * p) % mod;
    }

    return s;
}

int main() {
    // make IO faster
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t T;      // declare T
    std::cin >> T; // read T

    for (auto t = 0; t < T; ++t) {        // for T testcases
        size_t N;                           // declare N
        std::cin >> N;                      // read N
        std::cout << solve(N) << std::endl; // print solution
    }
}
