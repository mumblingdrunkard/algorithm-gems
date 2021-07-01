#include <iostream>
#include <vector>
#include <cstdint>
#include <cstddef>

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;

    std::vector<int64_t> A(N + 1);
    for (size_t i = 1; i < A.size(); ++i) {
        std::cin >> A[i];
    }

    for (size_t k = 0; k < Q; ++k) {
        size_t command;
        std::cin >> command;
        if (command == 1) {
            size_t L, R;
            int64_t X;
            std::cin >> L >> R >> X;
            for (size_t i = L; i < R + 1; ++i) {
                A[i] += (X + i - L) * (X + i - L);
            }
        } else {
            size_t Y;
            std::cin >> Y;
            std::cout << A[Y] << std::endl;
        }
    }

    return 0;
}

