# Оптимизация хэш-таблиц при помощи ассемблерных инструкций

## Часть 1

## Задача

- Написать хэш-таблицу для строк фиксированного размера и 7 хэш-функций для неё:
    - хэш-функция, которая всегда возвращает 0
    - хэш-функция, которая возвращает ASCII код первого символа строки
    - хэш-функция, которая возвращает длину слова
    - хэш-функция, которая возвращает сумму ASCII кодов символом строки
    - хэш-функция, вычисляема рекурсивно
- Преобразовать текст в набор слов без знаков пунктуации (кол-во слов не меньше 40 000)
- Поместить полученный набор слов в хэш-таблицу и построить диаграммы, отображающие длины цепочек в ячейках хэш-таблицы после вставки слов, для каждой хэш-функции
- выяснить, для какой хэш-функции количество коллизий наименьшее

## Ход работы

Реализована хеш-таблица на двусвязном списке на трех массивах, общих для всех списков. Размер таблицы - 2003
### Функции хэш-таблицы:
- вставка (если элемент уже есть есть в хэш-таблицы, повторная вставка не производится)

## Полученные результаты

### 1) Хэш-функция, всегда возвращающая 0

```C
size_t hashFuncZero(char *str, size_t size) {

    assert(str);

    return 0 % size;
}
```

<figure>
<img src="Images/charts/hash_func_1.png">
</figure>

**Все слова, как и ожидалось, попали в список под индексом 0.**

### 2) Хеш-функция, возвращающая ASCII код первого символа

```C
size_t hashFuncLetterASCII(char *str, size_t size) {

    assert(str);

    return (size_t) str[0] % size;
}
```

<figure>
<img src="Images/charts/hash_func_2.png">
</figure>

**Все слова находятся в диапазоне [0;255]**

### 3) Хэш-функция, возвращающая длину слова

```C
size_t hashFuncLength(char *str, size_t size) {

    assert(str);

    return strlen(str) % size;
}
```

<figure>
<img src="Images/charts/hash_func_3.png">
</figure>

**Большое количеств артиклей и коротких слов привело к большому числу коллизий**

### 4) Хеш-функция, возвращающая сумму ASCII кодов букв слова

```C
size_t hashFuncSumASCII(char *str, size_t size) {

    assert(str);

    size_t ascii_sum = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        ascii_sum += (size_t) str[i];
    }

    return ascii_sum % size;
}
```

**Для таблицы размера 101**

<figure>
<img src="Images/charts/hash_func_4_101.png">
</figure>

**Для таблицы размера 2003**

<figure>
<img src="Images/charts/hash_func_4.png">
</figure>

**Распределение лучше, чем в предыдущих вариантах, но все равно не очень хорошее, особенно для таблицы размера 101**

### 5) Хеш-функция, которая делает циклический сдвиг вправо результата для подстроки размера на 1 меньше и применяет к нему xor с ASCII кодом текущего символа

```C
size_t hashFuncCycleShiftRight(char *str, size_t size) {

    assert(str);

    size_t hash = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        hash = myCycleShiftRight(hash) ^ (size_t) str[i];
    }

    return hash % size;
}
```

<figure>
<img src="Images/charts/hash_func_5.png">
</figure>

**Эта хэш-функция очень равномерно распределила элементы**

### 6) Хеш-функция, аналогичная предыдущей, но циклический сдвиг теперь производится влево

```C
size_t hashFuncCycleShiftLeft(char *str, size_t size) {

    assert(str);

    size_t hash = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        hash = myCycleShiftLeft(hash) ^ (size_t) str[i];
    }

    return hash % size;
}
```

<figure>
<img src="Images/charts/hash_func_6.png">
</figure>

**На диаграмме видны несколько пиков, где коллизия велика, потому распределение немного хуже, чем в прошлом варианте, из-за отсутствия равномерности.**

### 7) Хэш-функция, которая считает хэш по алгоритму djb2

```C
size_t hashFuncDjb2(char *str, size_t size) {

    assert(str);

    size_t hash = 5381;

    for (size_t i = 0; str[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (size_t) str[i];
    }

    return hash % size;
}
```

<figure>
<img src="Images/charts/hash_func_7.png">
</figure>

**Очень равномерное распределение, длина списков не превышает 12**

### Вывод

Лучшей хэш-функцией оказалось седьмая, немного хуже неё пятая и шестая

