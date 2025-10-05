As páginas **18 a 21** do livro ***Programming with C++20***
(Andreas Fertig) tratam da seção **1.1 – “Programming
before Concepts”**, que explica como era a programação
genérica em C++ **antes da introdução dos *Concepts***
no padrão C++20.
Aqui vai um resumo e explicação detalhada dos pontos
principais dessas páginas:

---

### 🔹 Contexto

Antes dos *Concepts*, o C++ permitia criar funções genéricas
com **templates**. Isso era poderoso, mas trazia desvantagens:

* Erros de compilação difíceis de entender.
* Nenhuma forma clara de **especificar requisitos de tipo**
(por exemplo, “este tipo deve suportar o operador `+`”).
* Abuso de técnicas como **SFINAE** (*Substitution Failure
Is Not An Error*) e `std::enable_if`, que tornavam o código
confuso.

---

### 🔹 Exemplo usado: Função `Add`

O autor começa com uma função genérica `Add` que deve somar vários valores:

```cpp
const int x = Add(2, 3, 4, 5);
const int y = Add(2, 3);
const int z = Add(2, 3.0);  // ← deveria dar erro
```

A ideia é que `Add`:

* aceite um número variável de argumentos (`variadic templates`);
* funcione apenas quando **todos os tipos forem iguais** (por exemplo, todos `int`);
* não aceite misturas como `int` e `double`.

---

### 🔹 Ferramentas auxiliares (helpers)

Para fazer isso antes dos *Concepts*, o autor usa dois *helpers*:

1. **`are_same_v`** – verifica se todos os tipos em um *parameter pack* são iguais:

   ```cpp
   template<typename T, typename... Ts>
   constexpr inline bool are_same_v =
       std::conjunction_v<std::is_same<T, Ts>...>;
   ```

   * Usa *type traits* (`std::is_same`) para comparar tipos.
   * Usa `std::conjunction_v` (C++17) para combinar vários testes booleanos.

2. **`first_arg_t`** – obtém o tipo do primeiro argumento:

   ```cpp
   template<typename T, typename...>
   struct first_arg { using type = T; };

   template<typename... Args>
   using first_arg_t = typename first_arg<Args...>::type;
   ```

---

### 🔹 Implementação da `Add` (pré-C++20)

Com esses *helpers*, a função é escrita assim:

```cpp
template<typename... Args>
std::enable_if_t<are_same_v<Args...>, first_arg_t<Args...>>
Add(const Args&... args) noexcept {
    return (... + args);
}
```

* `std::enable_if_t<condição, tipo>` **habilita** a função
apenas se a condição for verdadeira.
* `(... + args)` é um **fold expression** (C++17), que soma todos os argumentos.
* Se `are_same_v` for falso, a função não é instanciada (SFINAE).

👉 O problema: essa linha com `enable_if_t` é **difícil
de ler e entender**, especialmente para iniciantes.

---

### 🔹 Dificuldades do modelo antigo

O autor destaca os problemas:

* **Pouca clareza**: o código não diz claramente “esta
função requer que todos os tipos sejam iguais”.
* **Erros enormes de compilação**: o compilador mostra
mensagens longas, listando todas as sobrecargas tentadas.
* **Sintaxe obscura**: o uso de `enable_if_t`, `typename`,
`::value`, etc., torna o código verboso.

---

### 🔹 Introdução dos *Concepts* (antecipando a mudança)

Na página 21, começa a seção **1.2 – “Start using
Concepts”**, mostrando como o mesmo exemplo fica **muito
mais simples** com C++20:

```cpp
template<typename... Args>
requires are_same_v<Args...>
auto Add(Args&&... args) noexcept {
    return (... + args);
}
```

* O novo **`requires`** é direto e legível:
  “Esta função requer que todos os tipos sejam iguais”.
* O retorno `auto` é visível e limpo.
* O código é mais expressivo e elimina `enable_if`.

---

### 🔹 Conclusão das páginas 18–21

Essas páginas mostram a **evolução da metaprogramação** em C++:

* **Antes dos Concepts**: código com `enable_if`, `type traits`,
SFINAE — poderoso, porém difícil.
* **Com Concepts (C++20)**: sintaxe clara, expressiva e
legível, permitindo definir **requisitos explícitos**
sobre tipos genéricos.

