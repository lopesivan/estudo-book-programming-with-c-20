Boa pergunta, Ivan 😄 — vamos destrinchar linha por linha o que acontece em:

```cpp
std::cout << Mul(2u, 3.0, 0.5f) << '\n';
```

---

## 🔹 1. Tipos dos argumentos

| Valor  | Tipo em C++    | Categoria                        |
| ------ | -------------- | -------------------------------- |
| `2u`   | `unsigned int` | inteiro sem sinal                |
| `3.0`  | `double`       | ponto flutuante                  |
| `0.5f` | `float`        | ponto flutuante (menor precisão) |

Portanto, `Mul` recebe três tipos diferentes:
`unsigned int`, `double`, `float`.

---

## 🔹 2. O `Mul` usa `std::common_type_t<Args...>`

Essa *type trait* encontra o **tipo comum de promoção** entre todos os parâmetros.
As regras seguem a **conversão aritmética usual do C++**:

1. Se houver `double`, ele vence — todos são promovidos a `double`.
2. `float` e inteiros sobem para `double`.
3. O resultado será, portanto:

```cpp
using R = std::common_type_t<unsigned int, double, float>; // → double
```

---

## 🔹 3. Conversão e multiplicação

Dentro da função:

```cpp
R out = R{1};  // out é double, começa em 1.0
((out *= static_cast<R>(args)), ...);  // fold expression
```

O *fold expression* equivale a:

```cpp
out *= static_cast<double>(2u);
out *= static_cast<double>(3.0);
out *= static_cast<double>(0.5f);
```

Passo a passo:

```
out = 1.0 * 2.0  → 2.0
out = 2.0 * 3.0  → 6.0
out = 6.0 * 0.5  → 3.0
```

---

## 🔹 4. Resultado final

O valor retornado é `3.0` (tipo `double`),
e portanto o `std::cout` imprime:

```
3
```

Se você quisesse ver explicitamente o tipo, poderia testar:

```cpp
std::cout << std::boolalpha << std::is_same_v<
    decltype(Mul(2u, 3.0, 0.5f)), double> << '\n';
```

→ imprime `true`.

---

## 🔹 5. Em resumo

✔️ `std::common_type_t` promove todos os tipos aritméticos para um tipo comum seguro (neste caso `double`).
✔️ `static_cast<R>` força a coerência antes de multiplicar.
✔️ O resultado é calculado com precisão de ponto flutuante.

---

Quer que eu te mostre uma versão alternativa que **mantém o tipo mais preciso do primeiro argumento** (em vez de promover tudo)? Isso é útil em contextos genéricos onde você quer preservar o tipo dominante.

