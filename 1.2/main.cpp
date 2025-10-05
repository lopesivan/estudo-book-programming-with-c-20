#include <iostream>
#include <type_traits>

// are_same_v: true se todos os tipos no pack são iguais ao primeiro
template <typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

// first_arg_t: tipo do primeiro argumento do pack
template <typename T, typename...>
struct first_arg
{
    using type = T;
};

template <typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

// Implementação estilo pré-C++20 com enable_if + fold expression (C++17)
template <typename... Args>
std::enable_if_t<are_same_v<Args...>, first_arg_t<Args...>>
        Add (const Args& ... args) noexcept
{
    static_assert (sizeof... (Args) > 1, "Add requer pelo menos dois operandos");
    return (... + args);
}

int main()
{
    std::cout << Add (2, 4) << '\n';       // OK
    // std::cout << Add(2, 3.0) << '\n';   // ERRO de compilação (tipos diferentes)
    return 0;
}
