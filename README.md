# Оптимизация хэш-таблиц при помощи низкоуровневого кода

## Задача

- Часть 1
    - написать хэш-таблицу для строк фиксированного размера и несколько хэш-функций для неё
    - выяснить, какая хэш-функция дает лучшее распределение
    - посмотреть, как транслируется код хэш-функций, использующих циклический сдвиг
- Часть 2
    - оптимизировать функции, которые больше всего влияют на время работы программы, использовать для этого три метода оптимизации
        - функции, написанные на ассемблере
        - ассемблерные вставки
        - SIMD инструкции
    - рассчитать КПД оптимизации по формуле: $\frac{коэффициент \ ускорения}{кол-во \ ассемблерных \ инструкций} * 1000$

## Ход работы

Реализована хэш-таблица на двусвязных списках, использующих три массива, общие для всех списков.

## Часть 1: Сравнение хэш-функций

<figure>
<img src="Images/charts/merged_3:3.png">
</figure>

### Исходники графиков
- [return 0](Images/charts/hash_func_1.png)
- [return int(word[0])](Images/charts/hash_func_2.png)
- [return  len(word)](Images/charts/hash_func_3.png)
- [return sum_ASCII(word) size=101](Images/charts/hash_func_4_101.png)
- [return sum_ASCII(word)](Images/charts/hash_func_4.png)
- [return ror(hash(n - 1)) * int(word[n])](Images/charts/hash_func_5.png)
- [return rol(hash(n - 1)) * int(word[n])](Images/charts/hash_func_6.png)
- [return djb2(word)](Images/charts/hash_func_7.png)
- [return crc32(word)](Images/charts/hash_func_8.png)

### Равномерность распределения

| Хэш-функция | Алгоритм | Дисперсия|
|:-----------:|:--------:|:---------:|
|   1   | return 0| 291 * 10<sup>2</sup>|
|   2   | return int(word[0])  |723|
|   3   | return  len(word) | 159 * 10|
|   4   | return sum_ASCII(word) | 20.7 |
|   5   | return ror(hash(n - 1)) * int(word[n])  | 3.4|
|   6   | return rol(hash(n - 1)) * int(word[n]) | 7.8|
|   7   | return djb2(word)  | 2.6 |
|   8   | return crc32(word) | 2.5 |

**Лучшее распределение оказалось у хэш-функции CRC32. В дальнейшем будем использовать ее. К тому же мы сможем оптимизировать её вычисление при помощи SIMD
инструкции.**

### Трансляция пятой и шестой хэш-функций

Компилятор `x86-64 gcc 13.2` на сайте https://godbolt.org/ транслирует код следующим образом

*Исходный код*

```C
    return (num >> 8 * sizeof(size_t) - 1) | (num << 1)
```

 *Оптимизация -O0*

 ```assembly
    mov     rax, QWORD PTR [rbp-8]
    rol     rax
```

 *Оптимизация -O1*

 ```assembly
    rol     rax
```

**При любом уровне оптимизации компилятор использовал при трансляции ассемблерную команду циклического сдвига, но при уровне оптимизации -O0 данные пересылаются из памяти, а при более высоком уровне оптимизации используются только регистры, что эффективнее.**

## Часть 2: Что оптимизировать?

Первая оптимизация - использовать -O3 )))

При помощи утилиты `callgrind` определим, какие функции больше всего влияют на время работы хэш-таблицы. (Результаты профилирования [здесь](callgrind))

<figure>
<img src="Images/сallgrind/no_opt.png" width=800>
</figure>

**Оказалось, что 30% времени занимает strcmp и столько же хэш-функция CRC32. Будем оптимизировать...**

### Оптимизируем

1)  Все слова из нашего текста оказались не длиннее 19 символов, а значить каждое из них влезет в 256 бит. Будем использовать в качестве ключей хэш-таблицы `union`.

```C
union Word {
    char str[32];
    __m256i packed;
};
```

Теперь все слова выровнены и мы можем использовать для сравнения SIMD инструкцию `_mm256_cmpeq_epi8()`.

2) Для ускорения хэш-функции CRC32 будем использовать `_mm_crc32_u8()`.

### Результаты оптимизации

||||Ускорение относительно||
|:-:|:-:|:-:|:-:|:-:|
| Оптимизация | Время, c |-O0| -O3| Предыдущей версии |
| -O0         |26.6|    1| 0.6| - |
| -O3         |16.7|1.6 | 1 | 1.6 |
| -O3 + strcmp| 11.7 | 2.3 | 1.4 | 1.4 |
| -O3 + strcmp + crc32| 10.5 | 2.5 | 1.6 | 1.1 |

*После оптимизации*

<figure>
<img src="Images/сallgrind/opt_strcmp_crc32.png" width=800>
</figure>

**Вес остальных функций не больше 0.02% поэтому дальнейшие оптимизации этой хэш-таблицы нецелесообразны

Но одна из задач работы - использовать три вида оптимизации, поэтому в учебных целях было проведены следующие попытки ускорения:
- хэш-функция `return sum(ASCII(word))` оптимизирована при помощи функции, написанной на ассемблере. Прирост производительности: 20.0 / 17.7 * 100% = 113%
- хэш-функция `rol(hash(n - 1)) * int(word[n])` оптимизирована при помощи ассемблерной вставки. Прирост производительность осталась на прежнем уровне.

### КПД = $\frac{2.5}{3} * 1000 \approx 833,3$