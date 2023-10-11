
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

// Custom function to calculate the square of a number
void square(int& n) {
    n = n * n;
}

int main() {
    std::vector<int> numbers{1, 2, 3, 4, 5};

    // Using parallel std::for_each loop to calculate the square of each number
    std::for_each(std::execution::par, numbers.begin(), numbers.end(), square);

    for (const auto& number : numbers) {
        std::cout << number << " ";
    }

    return 0;
}
