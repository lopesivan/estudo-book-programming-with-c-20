#include <concepts>
#include <iostream>
#include <type_traits>

#include <concepts>
#include <type_traits>

template <typename... Args>
requires (sizeof... (Args) > 1)&&
(std::conjunction_v<std::is_arithmetic<Args>...>)
auto Mul (Args... args) noexcept
{
    using R = std::common_type_t<Args...>;
    R out = R{1};
    ((out *= static_cast<R> (args)), ...);
    return out;
}

int main()
{
    std::cout << Mul (2, 4, 5) << '\n';    // 40 (int)
    std::cout << Mul (2, 3.5) << '\n';     // 7.0 (promove para double)
    std::cout << Mul (2u, 3, 0.5f) << '\n'; // 3.0 (promove para float/double)
    std::cout << Mul (2u, 3, 0.5f) << '\n'; // 3.0 (promove para float/double)
    std::cout << Mul (3.17, 3.8, 0.5) << '\n'; // 3.0 (promove para float/double)
    return 0;
}
