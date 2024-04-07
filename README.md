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

`<figure>
<img src="Images/hash_functions_code/hash_func_1.png" width=400>
</figure>`

<figure>
<img src="Images/charts/hash_func_1.png">
</figure>

### 2) Хеш-функция, возвращающая ASCII код первого символа

`<figure>
<img src="Images/hash_functions_code/hash_func_2.png" width=400>
</figure>`

<figure>
<img src="Images/charts/hash_func_2.png">
</figure>

### 3) Хэш-фукция, возвращающая длину слова

`<figure>
<img src="Images/hash_functions_code/hash_func_3.png" width=400>
</figure>
`
<figure>
<img src="Images/charts/hash_func_3.png">
</figure>

### 4) Хеш-функция, возвращающая сумму ASCII кодов букв слова

`<figure>
<img src="Images/hash_functions_code/hash_func_4.png" width=400>
</figure>`

**Для таблицы размера 101**

<figure>
<img src="Images/charts/hash_func_4_101.png">
</figure>

**Для таблицы размера 2003**

<figure>
<img src="Images/charts/hash_func_4.png">
</figure>

### 5) Хеш-функция, которая делает циклический сдвиг вправо результата для подстроки размера на 1 меньше и применяет к нему xor с ASCII кодом текущего символа
`<figure>
<img src="Images/hash_functions_code/hash_func_5.png" width=400>
</figure>`

<figure>
<img src="Images/charts/hash_func_5.png">
</figure>

### 6) Хеш-функция, аналогичная предыдущей, но циклический сдвиг теперь производится влево

`<figure>
<img src="Images/hash_functions_code/hash_func_6.png" width=400>
</figure>`

<figure>
<img src="Images/charts/hash_func_6.png">
</figure>

### 7) Хэш-функция, которая считает хэш по алгоритму djb2

`<figure>
<img src="Images/hash_functions_code/hash_func_7.png" width=400>
</figure>`

<figure>
<img src="Images/charts/hash_func_7.png">
</figure>