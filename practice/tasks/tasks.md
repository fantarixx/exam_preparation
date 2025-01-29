Тут представленны задания других групп с экзамена по ОП 1 курса ITMO IS y28.

# Задания
- Свой класс Vector.
    ```Cpp
    ```

- Свой класс Map.
    ```Cpp
    // ключ - всегда инт, значение - произвольный тип данных
    // можно испльзовать std::vector

    #include <iostream>
    #include <vector>
    
    class Map {
    
    };
    
    int main() {
        Map m_1{}; // пусть этот для инта
        m_1.add(1, 10);
        m_1.add(1, 20);
        m_1.del(1, 20);

        Map m_2 = m_1; // копирование мапы
        Map m_3{m_1}; // тоже копирование

        Map m_4 = m_1 + m_2; // объединение двух мапов
        Map m_5 = m_1 / m_2; // оставить только с уникальными ключами

        std::cout << m_1 << std::endl; // вывод вне struct

        return 0;
    }
    ```

- BitSet из 14 битов (20).
    ```Cpp
    ```

- Свой класс IntArray.
    ```Cpp
    int main() {
        IntArray a{3, 0};
        std::cout << a << std::endl;  // 0 0 0

        IntArray a2{2, 1};

        std::cout << a + a2 << std::endl;  // 0 0 0 1 1

        std::cout << 1 + a + 2 << std::endl;  // 1 0 0 0 2;

        a2 = a2;
        std::cout << a2 << std::endl;

        return 0;
    }
    ```
- (20).
    ```Cpp
    int main() {
        IntSet s;

        s = 4 + 5 + s + 1 + 2 + 3;

        std::cout << s << std::endl;  // 1 2 3 4 5;

        s = s + s;

        std::cout << s << std::endl;  // 1 2 3 4 5

        s = s - 2 - 3 - 4;

        std::cout << s << std::endl;  // 1 5

        IntSet s2;

        s2 = s2 + 3 + 4 + 5;

        std::cout << s + s2 << std::endl;  // 1 3 4 5

        std::cout << s - s2;  // 1
        
        return 0;
    }
  ```

  - Свой класс IntDoubleStore.
    ```Cpp
    #include <iostream>

    class IntDoubleStore {

    };

    int main()
    {
        IntDoubleStore store;

        store[1] = 1.0;
        store[2] = 2.2;

        store = store + 3;
        store += 4;

        std::cout << store << "\n"; // {1, 1.0} {2, 2.2} {3,0} {4,0}

        IntDoubleStore store2 = store - 3 - 2;

        std::cout << store2 << "\n"; // // {1, 1.0} {4,0}

        IntDoubleStore store3;

        store3[5] = 5;

        std::cout << store2 + store3 << "\n"; // {1, 1.0} {4,0} {5, 5}

        return 0;
    }
    ```

- .
    ```Cpp
    #include <array>
    #include <vector>
    #include <algorithm>


    // std deprecated 
    class IntSaver;


    int main() {

        std::array<int, 5> arr = {1,2,3,4,5};
        std::vector<IntSaver> v (arr.begin(), arr.end());


        std::reverse(v.begin(), v.end());
        for(auto& i : v)
            i *= 2;

        

        for(int i : arr) {
            std::cout << i; //  2 4 6 8 10
        } 
    
        return 0;
    }
    ```

- .
    ```Cpp
    struct less {
        bool operator()(int lhs, int rhs) const {
            return lhs < rhs;
        }
    };

    struct greater {
        bool operator()(int lhs, int rhs) const {
            return lhs > rhs;
        }
    };

    fix_right_arg(less Less, int num) {
        
    }

    fix_right_arg(greater Greater, int num) {
        
    }


    int main () {
        // реализовать функцию fix_right_arg 
        auto less7 = fix_right_arg(less{}, 7);
        auto great7 = fix_right_arg(greater{}, 7);


        std::cout << less7(1) << " " << less7(8); // 1 0
        std::cout << great7(1) << " " << great7(8); // 0 1

        return 0;
    }
    ```


# Вопросы
1. Что такое полиморфизм?
2. Какой бывает полиморфизм?
3. Что такое виртуальные функции?
4. Где применяются виртуальные функции?
5. Что из себя прдставляет стадия компиляции - линковка?
6. Привести пример кода с виртуальной фунцией.
7. В чем разница `lvalue` и `rvalue` ссылок?
8. Как работают `lvalue` и `rvalue` ссылки?
9. Что такое `this`?
10. Как работает `this`?
11. Почему работает `this`?
12. Почему программа в runtime знает на что указывает `this`?
13. За что отвечает `static`?
14. Когда используется `static`?
15. Знать как вычисляется размер структуры и уметь это делать.
16. Что такое `friend`?
17. Зачем нужен `friend`?