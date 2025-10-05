#include <iostream>
#include <type_traits>

// Retorno: tipo comum entre todos os Args (int→double, float→double, etc.)
template <typename... Args>
using common_arith_t = std::common_type_t<Args...>;

template <typename... Args>
std::enable_if_t<(sizeof...(Args) > 1) &&
                     (std::conjunction_v<std::is_arithmetic<Args>...>),
                 common_arith_t<Args...>>
Mul(Args... args) noexcept
{
    using R = common_arith_t<Args...>;
    R out = R{1};
    ((out *= static_cast<R>(args)), ...);
    return out;
}

int main()
{
    std::cout << Mul(2, 4, 5) << '\n'; // 40 (int)
    std::cout << Mul(2, 3.5) << '\n';  // 7.0 (promove para double)
    std::cout << Mul(2u, 3.0, 0.5f)
              << '\n';                   // 3.0 (promove para float/double)
    std::cout << Mul(2.6, 3.15) << '\n'; // 7.0 (promove para double)
    return 0;
}
