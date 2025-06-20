# Полный теоретический конспект по C++ (расширенный)

## 1. Шаблоны функций и классов

### Что такое шаблоны?

Шаблоны — это способ писать обобщённый код, который можно использовать с различными типами данных. Благодаря шаблонам, один и тот же алгоритм можно применять как к `int`, так и к `double`, `std::string` или даже к пользовательским типам. Шаблоны обрабатываются на этапе компиляции — компилятор создаёт реальные функции или классы, подставляя нужные типы.

### Шаблоны функций

Шаблон функции определяется с помощью ключевого слова `template`:

```cpp
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}
```

**Как это работает:**

- При вызове `max(3, 5)` компилятор создаст реализацию `max<int>`.
- При `max(3.5, 4.2)` — реализацию `max<double>`.

**Автоматический вывод типа**: компилятор сам может определить `T` из переданных аргументов.

### Шаблоны классов

Шаблоны классов позволяют описывать обобщённые структуры данных:

```cpp
template<typename T>
class Box {
    T value;
public:
    Box(T val) : value(val) {}
    T get() const { return value; }
};
```

Можно создать `Box<int>`, `Box<std::string>`, `Box<MyClass>` и т.д.

### Полная специализация

Полная специализация — это определение шаблона для конкретного типа:

```cpp
template<>
class Box<bool> {
    bool value;
public:
    Box(bool val) : value(val) {}
    std::string get() const {
        return value ? "true" : "false";
    }
};
```

### Частичная специализация

Частичная специализация возможна только для классов. Она позволяет изменить поведение шаблона при некоторых известных параметрах:

```cpp
template<typename T1, typename T2>
class Pair { /* ... */ };

template<typename T>
class Pair<T, T> { /* реализация, если оба типа одинаковы */ };
```

**Ограничения:** нельзя частично специализировать шаблоны функций (для них можно использовать `std::enable_if`, `concepts` или перегрузку).

## 2. Умные указатели

### Почему обычные указатели — плохо?

- Неуправляемый ресурс: легко забыть `delete`
- Могут быть `dangling` — указывают на удалённую память
- Нет ясной модели владения: кто должен удалять память?

### `std::unique_ptr`

- Единственный владелец ресурса
- Нельзя копировать, можно только переместить

```cpp
std::unique_ptr<int> ptr = std::make_unique<int>(42);
```

Автоматически вызовет `delete` при выходе из области видимости.

### `std::shared_ptr`

- Несколько владельцев
- Используется счётчик ссылок
- Как только последний `shared_ptr` уничтожается — объект удаляется

```cpp
auto p1 = std::make_shared<int>(10);
auto p2 = p1; // счётчик = 2
```

### `std::weak_ptr`

- Не увеличивает счётчик ссылок
- Используется для избежания циклических ссылок
- Перед использованием надо вызвать `.lock()` и проверить

```cpp
std::weak_ptr<Node> w = p;
if (auto s = w.lock()) { use(s); }
```

## 3. STL: Итераторы и алгоритмы

### Итераторы

Итераторы — это обобщённые указатели, которые позволяют перебирать элементы контейнера. Пример:

```cpp
std::vector<int> v = {1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it;
}
```

Типы итераторов:

- `InputIterator`, `OutputIterator`
- `ForwardIterator`
- `BidirectionalIterator`
- `RandomAccessIterator`

**Важно:** алгоритмы STL используют итераторы, а не сам контейнер напрямую.

### Алгоритмы STL

STL предлагает обширную библиотеку алгоритмов:

- **Поиск**: `find`, `find_if`, `binary_search`
- **Сортировка**: `sort`, `stable_sort`, `partial_sort`
- **Изменения**: `copy`, `transform`, `replace`, `remove`
- **Подсчёты**: `count`, `accumulate`, `all_of`, `any_of`

Пример:

```cpp
std::vector<int> v = {1, 5, 3};
std::sort(v.begin(), v.end());
```

## 4. STL: Последовательные контейнеры

### Назначение

Последовательные контейнеры STL предназначены для хранения и управления последовательностями элементов. Они сохраняют порядок вставки и предоставляют итераторы для обхода.

### Основные контейнеры

#### `std::vector`

- Динамический массив
- Быстрый доступ по индексу O(1)
- Быстро добавляет элементы в конец (`push_back`) — O(1) амортизированное
- При добавлении может перевыделяться память

```cpp
std::vector<int> v = {1, 2, 3};
v.push_back(4);
```

#### `std::deque`

- Двусторонняя очередь
- Быстрая вставка/удаление с обеих сторон (в отличие от `vector`, у которого это эффективно только с конца)

```cpp
std::deque<int> d;
d.push_front(1);
d.push_back(2);
```

#### `std::list`

- Двусвязный список
- Быстрая вставка/удаление в середине (при наличии итератора)
- Нет быстрого доступа по индексу

```cpp
std::list<int> lst = {1, 2, 3};
auto it = std::next(lst.begin());
lst.insert(it, 42);
```

#### `std::forward_list`

- Односвязный список
- Экономит память
- Поддерживает только прямой проход (нет `prev`/`--it`)

#### `std::array`

- Статический массив фиксированного размера
- Размер задаётся во время компиляции

```cpp
std::array<int, 3> arr = {1, 2, 3};
```

### Когда использовать

- `vector` — в большинстве случаев: эффективен, простой, поддерживает random access
- `list` — когда нужно часто вставлять/удалять элементы в середине
- `deque` — когда нужны вставки и с начала, и с конца
- `array` — когда размер известен заранее и требуется размещение на стеке

## 5. STL: Ассоциативные контейнеры

Ассоциативные контейнеры обеспечивают быстрый доступ к элементам по ключу.

### Упорядоченные (`map`, `set`)

Используют **красно-чёрные деревья** (self-balancing binary search tree).

#### Красно-чёрное дерево: свойства

- Каждый узел — красный или чёрный
- Корень — чёрный
- У красного узла оба потомка — чёрные
- Все пути от узла до листа содержат одинаковое число чёрных узлов

Это гарантирует высоту дерева O(log N), а значит:

- Вставка/поиск/удаление — логарифмические по времени

#### Контейнеры

- `std::set<T>` — множество уникальных значений
- `std::map<K, V>` — словарь (ключ-значение)
- `std::multiset<T>` — может содержать дубликаты
- `std::multimap<K, V>` — допускает несколько значений с одним ключом

### Неупорядоченные (`unordered_map`, `unordered_set`)

Используют **хеш-таблицы**. Обеспечивают O(1) среднее время доступа, но нет порядка элементов.

```cpp
std::unordered_map<std::string, int> scores;
scores["Alice"] = 10;
```

#### Когда использовать:

- `unordered_map` быстрее, если порядок не важен
- `map` полезен, если нужен отсортированный обход

## 6. STL: Адаптеры

### Что такое адаптеры контейнеров?

Это обёртки над другими контейнерами, предоставляющие ограниченный интерфейс.

### Виды адаптеров

#### `std::stack`

- Реализован на базе `deque` по умолчанию
- Методы: `push`, `pop`, `top`, `empty`, `size`

```cpp
std::stack<int> st;
st.push(1);
st.top(); // 1
```

#### `std::queue`

- FIFO (первым пришёл — первым вышел)
- Методы: `push`, `pop`, `front`, `back`, `empty`

#### `std::priority_queue`

- Элементы извлекаются в порядке приоритета (по умолчанию — наибольший элемент первым)
- Реализован через `std::make_heap`

```cpp
std::priority_queue<int> pq;
pq.push(5);
pq.push(3);
pq.top(); // 5
```

### Замечания

- Контейнер-адаптер не предоставляет итераторов
- Можно настроить поведение адаптера через указание базового контейнера (`vector`, `deque`, `list`)

## 7. Исключения

### Что такое исключения?

Механизм обработки ошибок, при котором выполнение переходит в `catch`-блок при возникновении исключительной ситуации.

```cpp
try {
    if (error) throw std::runtime_error("ошибка");
} catch (const std::exception& e) {
    std::cerr << e.what();
}
```

### Ключевые слова

- `throw` — выброс исключения
- `try` — блок, в котором может возникнуть исключение
- `catch` — обработчик исключения

### Иерархия

- `std::exception` — базовый класс
- `std::runtime_error`, `std::logic_error`, `std::out_of_range` и др.

### Пользовательские исключения

Можно создавать свои типы исключений:

```cpp
class MyException : public std::exception {
    const char* what() const noexcept override { return "my error"; }
};
```

### Практика

- Не бросать исключения в деструкторах
- Лучше ловить по `const&`, а не по значению
- Использовать `noexcept`, где гарантировано отсутствие исключений

## 8. Лямбды

### Что такое лямбда-выражения?

Лямбды — это анонимные функции, которые могут быть определены прямо на месте. Они часто используются с алгоритмами STL и позволяют кратко описывать поведение без необходимости отдельной функции.

### Синтаксис

```cpp
[capture](parameters) -> return_type {
    // тело
};
```

### Примеры

```cpp
auto sum = [](int a, int b) { return a + b; };
std::cout << sum(3, 4); // 7

std::vector<int> v = {1, 2, 3};
std::for_each(v.begin(), v.end(), [](int x) {
    std::cout << x << " ";
});
```

### Захват переменных

- `[=]` — захват по значению
- `[&]` — захват по ссылке
- `[x]` — захват конкретной переменной
- `[=, &x]` — всё по значению, `x` по ссылке

Лямбды могут быть `mutable`, `constexpr`, `noexcept`, захватывать переменные перемещения (`[val = std::move(obj)]`), и использоваться в качестве `std::function`.

---

## 9. Преобразования типов и CRTP

### Преобразования типов в C++

#### `static_cast`

- Явное безопасное преобразование между связанными типами

```cpp
float f = 3.14;
int i = static_cast<int>(f);
```

#### `dynamic_cast`

- Преобразование между полиморфными типами с проверкой RTTI

```cpp
Base* b = new Derived();
Derived* d = dynamic_cast<Derived*>(b);
```

#### `const_cast`

- Добавление/удаление `const`

```cpp
const int* ci = new int(5);
int* i = const_cast<int*>(ci);
```

#### `reinterpret_cast`

- Низкоуровневое побитовое преобразование (использовать осторожно!)

```cpp
int a = 42;
char* p = reinterpret_cast<char*>(&a);
```

### CRTP (Curiously Recurring Template Pattern)

Шаблон, при котором класс-наследник передаёт себя как параметр шаблону базового класса:

```cpp
template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() { std::cout << "Derived impl"; }
};
```

**Применения:**

- Статический полиморфизм
- CRTP используется в библиотеках для оптимизации (`Eigen`, `Boost.Operators`)

---

## 10. Move-семантика и категории выражений

### Зачем нужна move-семантика?

Позволяет избежать лишнего копирования, особенно для объектов, владеющих ресурсами (например, `std::string`, `std::vector`).

```cpp
std::string s1 = "Hello";
std::string s2 = std::move(s1); // s1 опустошается, s2 владеет строкой
```

### `std::move`

- Преобразует объект в **rvalue-reference**, разрешая его перемещение

```cpp
void take(std::string&& s) { std::cout << s; }
std::string str = "Test";
take(std::move(str));
```

### Правила пяти (и шести)

Если класс управляет ресурсами:

- Определи: `~Destructor`, `CopyConstructor`, `CopyAssignment`, `MoveConstructor`, `MoveAssignment`
- C++20: Rule of Zero, Rule of Six (`operator==`)

### Категории выражений (value categories)

- **lvalue** — имеет имя и может быть взята адресом
- **rvalue** — временное значение (например, результат выражения)
- **xvalue** (expiring value) — можно переместить (например, `std::move(obj)`)
- **glvalue** — объединяет `lvalue` и `xvalue`
- **prvalue** — pure rvalue (литералы, возвращаемые значения)

Понимание этих категорий важно для перегрузки функций, perfect forwarding и move-семантики.

## 8. Лямбды

### Что такое лямбда-выражения?

Лямбды — это анонимные функции, которые могут быть определены прямо на месте. Они часто используются с алгоритмами STL и позволяют кратко описывать поведение без необходимости отдельной функции.

### Синтаксис

```cpp
[capture](parameters) -> return_type {
    // тело
};
```

### Примеры

```cpp
auto sum = [](int a, int b) { return a + b; };
std::cout << sum(3, 4); // 7

std::vector<int> v = {1, 2, 3};
std::for_each(v.begin(), v.end(), [](int x) {
    std::cout << x << " ";
});
```

### Захват переменных

* `[=]` — захват по значению
* `[&]` — захват по ссылке
* `[x]` — захват конкретной переменной
* `[=, &x]` — всё по значению, `x` по ссылке

Лямбды могут быть `mutable`, `constexpr`, `noexcept`, захватывать переменные перемещения (`[val = std::move(obj)]`), и использоваться в качестве `std::function`.

---

## 9. Преобразования типов и CRTP

### Преобразования типов в C++

#### `static_cast`

* Явное безопасное преобразование между связанными типами

```cpp
float f = 3.14;
int i = static_cast<int>(f);
```

#### `dynamic_cast`

* Преобразование между полиморфными типами с проверкой RTTI

```cpp
Base* b = new Derived();
Derived* d = dynamic_cast<Derived*>(b);
```

#### `const_cast`

* Добавление/удаление `const`

```cpp
const int* ci = new int(5);
int* i = const_cast<int*>(ci);
```

#### `reinterpret_cast`

* Низкоуровневое побитовое преобразование (использовать осторожно!)

```cpp
int a = 42;
char* p = reinterpret_cast<char*>(&a);
```

### CRTP (Curiously Recurring Template Pattern)

Шаблон, при котором класс-наследник передаёт себя как параметр шаблону базового класса:

```cpp
template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() { std::cout << "Derived impl"; }
};
```

**Применения:**

* Статический полиморфизм
* CRTP используется в библиотеках для оптимизации (`Eigen`, `Boost.Operators`)

---

## 10. Move-семантика и категории выражений

### Зачем нужна move-семантика?

Позволяет избежать лишнего копирования, особенно для объектов, владеющих ресурсами (например, `std::string`, `std::vector`).

```cpp
std::string s1 = "Hello";
std::string s2 = std::move(s1); // s1 опустошается, s2 владеет строкой
```

### `std::move`

* Преобразует объект в **rvalue-reference**, разрешая его перемещение

```cpp
void take(std::string&& s) { std::cout << s; }
std::string str = "Test";
take(std::move(str));
```

### Правила пяти (и шести)

Если класс управляет ресурсами:

* Определи: `~Destructor`, `CopyConstructor`, `CopyAssignment`, `MoveConstructor`, `MoveAssignment`
* C++20: Rule of Zero, Rule of Six (`operator==`)

### Категории выражений (value categories)

* **lvalue** — имеет имя и может быть взята адресом
* **rvalue** — временное значение (например, результат выражения)
* **xvalue** (expiring value) — можно переместить (например, `std::move(obj)`)
* **glvalue** — объединяет `lvalue` и `xvalue`
* **prvalue** — pure rvalue (литералы, возвращаемые значения)

Понимание этих категорий важно для перегрузки функций, perfect forwarding и move-семантики.

## 11. Вариативные шаблоны

### Что это?

Вариативные шаблоны позволяют принимать переменное число параметров шаблона или аргументов функции. Это основа для реализации `std::tuple`, `std::apply`, форматирования, логгирования и прочего.

### Пример шаблона-функции:

```cpp
template<typename T>
void print(T arg) {
    std::cout << arg << '
';
}

template<typename T, typename... Args>
void print(T first, Args... rest) {
    std::cout << first << ' ';
    print(rest...);
}
```

### Fold expressions (C++17):

```cpp
template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args) << '
';
}
```

## 12. Метапрограммирование: `constexpr`, метафункции, SFINAE, концепты

### `constexpr`

Позволяет выполнять вычисления на этапе компиляции.

```cpp
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}
```

С C++20 можно использовать `constexpr` для почти всего, включая `std::vector` и `std::string` внутри `constexpr` функций.

### Метафункции

Шаблонные конструкции, возвращающие тип или значение на этапе компиляции.

```cpp
template<typename T>
struct is_pointer {
    static constexpr bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};
```

С C++11 появился `std::is_pointer<T>`, `std::enable_if`, `std::conditional`, и прочие из `<type_traits>`.

### SFINAE (Substitution Failure Is Not An Error)

Позволяет отсеивать неподходящие перегрузки шаблонов без ошибок компиляции.

```cpp
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
process(T val) { std::cout << "int"; }
```

### Концепты (C++20)

Позволяют задать ограничения на шаблонные параметры:

```cpp
template<typename T>
concept Printable = requires(T a) {
    std::cout << a;
};

template<Printable T>
void print(const T& value) {
    std::cout << value;
}
```

## 13. Concurrency

### Потоки

* `std::thread` создаёт отдельный поток

```cpp
void task() { std::cout << "Running in thread"; }
std::thread t(task);
t.join();
```

### Мьютексы

* `std::mutex`, `std::lock_guard`, `std::unique_lock` — обеспечивают защиту от гонок

```cpp
std::mutex m;
void safe() {
    std::lock_guard<std::mutex> lock(m);
    // доступ к общим данным
}
```

### Условные переменные

* `std::condition_variable` — для синхронизации потоков

### Проблемы многопоточности

* **Data races** — одновременный доступ к данным без синхронизации
* **Deadlocks** — взаимная блокировка ресурсов
* **False sharing** — два потока используют одну кеш-линию

### std::future и std::async

Позволяют запускать асинхронные задачи с возвращаемым результатом:

```cpp
std::future<int> fut = std::async([] { return 42; });
int result = fut.get();
```

---


