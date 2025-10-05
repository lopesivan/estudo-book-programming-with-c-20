#include <iostream>
#include <type_traits>
#include <concepts>

// Helpers iguais aos do exemplo anterior
template <typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template <typename T, typename...>
struct first_arg
{
    using type = T;
};

template <typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

// Versão com requires (C++20)
template <typename... Args>
requires (are_same_v<Args...>&& (sizeof... (Args) > 1)&&
          requires (Args... a)
{
    {
        (... + a)
    }
    noexcept -> std::same_as<first_arg_t<Args...>>;
})
auto Add (Args&& ... args) noexcept
{
    return (... + args);
}

int main()
{
    std::cout << Add (2, 4) << '\n';
    // std::cout << Add(2, 3.0) << '\n'; // ERRO: tipos diferentes
    return 0;
}
