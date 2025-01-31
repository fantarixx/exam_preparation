# exam_preparation
preparation for OP 1 semester ITMO IS y28

# Диф зачет I семестр

## Темы 

0. Встроенные типы данных, представление чисел в памяти, строки 
1. Преобразования типов (явные и неявные)
2. Структуры и объединения
3. Указатели
4. Массивы
5. Устройство памяти, сегменты
6. Стек вызова функций
7. Ссылки
8. Перегрузка функций
9. namespace 
10. Компиляция, этапы, ошибки компиляции
11. ООП (абстракция, инкапсуляция, наследование, полиморфизм)
12. Классы. Специальные методы
13. Перегрузка операторов
14. Шаблоны функций, классов. Частичная и полная специализация.

### Структура репозитория
- Список тем в этом файле.
- Модуль teory - модуль с теорией по данным темам.
- Модуль practice - модуль в котором лежат условия задач других групп, а также устные вопросы, которые у них спршивали. Также в этом модуле будет мое решение этих задач - ну потому что мой же репозитоиий.
  Как устроен модуль practice:
    - Есть библиотеки для конкретных классов (`vector`, `map`, etc).
    - Эти библиотеки подключаются в библиотеку `tasks`, в которой есть структура `tasks`, отвечающая за тесты к заданиям, упомянутым в tasks.mdв этом же модуле.
    - В мейне подключается библиотека `tasks` и вызываются тесты для самописных классов.
    - Если захотите потренироваться, то клоните репозиторий изменяйте/удаляйте файлы `.cpp`, `.h` в библиотеках `vector` и тд.
