
/*************************************************************
    Практическое занятие №3. Функции.
    Объявление, определение, вызов.
    Передача параметров. Возвращение значения.
    Указатели на функции
*************************************************************/
#include <iostream>
//#include <tchar.h>
//#include <cstdio>
#include <cstdarg>
#include "other.hpp"
#include <ctime>

#define stop

int main()
{
    srand(time(0));
    /////////////////////////////////////////////////////////////////////////////
    // Задание 1. Ссылки.
    //Объявите ссылку на тип double. Посредством ссылки измените значение

    double Doub = 1.5;
    double& ssDuob = Doub;
    ssDuob = 2.5;

    //Раскомментируйте  следующую строчку. Что следует сделать, чтобы
    //linker не выдавал ошибки при создании exe-файла. Подсказка: ref - это
    //внешняя по отношению к данному файлу ссылка!
    
    extern int& ref;
    ref++;

    //Раскомментируйте следующую строку. Что следует сделать, чтобы
    //компилятор не выдавал ошибки
    int dopPer = 1;

    int& ref1 = dopPer;


    //Задан указатель:
    char c='A';
    char* pc = &c; // сам указатель
    //Объявите ссылку на указатель. Посредством ссылки измените
    //а) значение по адресу
    //б) сам адрес

    char* &ukpc = pc; // ссылка на указателб
    char cc = 'C'; // переменная для создания другого указателя
    char* ukcc = &cc;

    //а)
    *ukpc = 'B'; // меняю значение
    //б)
    ukpc = ukcc; // меняю адрес
    
    //Задание 2. Отличия при передаче параметров а) по значению,
    // б) по ссылке, в) по указателю
    //Объявите и определите три функции , которые увеличивают заданное
    //с помощью параметра значение на 1 ( а) - IncByValue(),
    // б) - IncByPointer(), в) - IncByReference() ).
    //Проверьте правильность с помощью отладчика.
    //
    //Замечание: объявления функций принято помещать в заголовочный файл
    int val =1;//значение этой переменной должно быть увеличено с помощью
                //каждой из функций на единицу
    val =  IncByValue(val);
    IncByPointer(&val);
    IncByReference(val);
  
    stop


    //Задание 2а. Передача параметров c помощью указателя и по ссылке.
    //Перегруженные имена функций.
    //Создайте функцию (функции) Swap(), которая меняет значения
    //переменных nX и nY местами.
    // а)Функция должна принимать два указателя на int, оперируя с
    //которыми менять значения переменных в вызывающей программе
    // б)Функция должна принимать две ссылки на int
    //Проверьте правильность с помощью приведенного ниже фрагмента.

    int nX = 1;
    int nY = -1;
    swapUk(&nX, &nY);    //поменяли местами значения nX и nY с
                        //помощью указателей на nX и nY
    swapS(nX, nY);    //а теперь обратно с помощью ссылок на nX и nY
    stop

    //Задание 3. Указатели на массивы в качестве аргументов.
    //3a.Напишите два варианта функции поиска минимального элемента
    //1. во встроенном двухмерном массиве
    //2. в динамическом двухмерном массиве (обе размерности вычисляются)
    const int N = 2; // Можно также использовать #define N 10
    const int M = 4; // Можно также использовать #define M 10

    //встроенный массив
    int ar[N][M] = {{2,3,1,4},{5,7,8,6}}; //создаю двумерный массив
    int res1 = minAr(&ar[0][0], N, M);  //ищу в нем минимум через функцию
    for(int i = 0; i < N; i++){
        printArray(ar[i], M);
    }
    std::cout << "Result for min in innermas: " << res1 << '\n';
    
    //динамический массив
    //создаю переменные для кол-ва строк и столбцов
    int n = 2;
    int m = 4;

    //создаю двумерный динамический массив
    int** dAr = new int*[n];

    //создаю в нем одномерные динамические массивы и заполняю рандомными значениями
    for(int i = 0; i < n; i++){
        dAr[i] = new int[m];
        for(int j = 0; j < m; j++){
            dAr[i][j] = rand()%10;
        }
        printArray(dAr[i], m);
    }

    //ищу минимальное в двумерном динамическом массиве
    int res2 = minAr(dAr, n, m);
    std::cout << "Result for min in dynamicmas: " << res2 << '\n';
    //очищаю памнять выделенную на внутренние одномерные массивы
    for(int i = 0; i < n; i++){
        delete[] dAr[i];
    }

    //очищаю память выделенную на двумерный динамический массив
    delete[] dAr;

    //3b. Напишите функцию сравнения двух строк - MyStrCmp():
    //Функция должна принимать два указателя на сравниваемые
    //строки (возможно Вы должны указать компилятору, что функция
    //не имеет права модифицировать содержимое строк)
    //Функция должна возвращать отрицательное значение, если
    //первая строка лексиграфически меньше второй, 0 - если
    //они равны и положительное значение, если первая строка
    //больше второй.
    //Вспомните, что признаком конца строки является нулевой байт.
    
    //Создайте две строки для сравнения:
    const char* str1 = "abcd";
    const char* str2 = "acbd";
    //Вызовите функцию сравнения
    int resstr = MyStrCmp(str1,str2);
    //Выведите результат сравнения с помощью cout:
    std::cout << resstr << " " << strcmp(str1, str2) << '\n';
    stop

    //Задание 4.Ссылки в качестве параметров. Передача указателя на встроенный
    //массив в качестве параметра функции.
    //Напишите две взаимодополняющие друг друга функции:
    //1.  ... DayOfYear(...)
    //- преобразует день месяца (число,месяц и год задаются в качестве параметров)
    //в порядковый день года(возвращаемое значение)
    //2. ... DayOfMonth(...) - функция преобразует порядковый день года в день месяца
    // (принимает год и порядковый день года в качестве параметров и должна сформировать
    // день месяца и номер месяца и каким-то образом сообщить эти значения вызывающей процедуре)
    
    //Проверьте работоспособность обеих функций с помощью следующего фрагмента:
    

    //В процессе вычислений Вам придется учитывать "високосный - невисокосный" год.
    //Для этого предлагается в каждую функцию в качестве одного из параметров передавать
    //данные приведенного ниже двухмерного массива nDayTab
    
    //Вызов функции DayOfYear
    std::cout << DayOfYear(22, 10, 2023) << '\n';

    //Проверка результата обратной функцией DayOfMonth
    int day;
    int month;
    int* ukday = &day;
    int* ukmonth = &month;
    DayOfMonth(295, 2023, ukday, ukmonth);

    //выводим результаты и сравниваем
    std::cout << day << " " << month << '\n';

    stop
    //Задание 5. Создайте одномерный массив (размерность вычисляется в процессе
    //выполнения программы), заполните его значениями.
    //Напишите функцию, которая добавляет в массив новое значение только при условии,
    //что такого значения в массиве еще нет. Подсказка: при этом размер
    //массива должен увеличиться!
    //Для проверки напишите функцию, которая выводит значения всех элементов на экран

    //запрашиваем размерность массива
    int size;
    std::cout << "Enter array size:";
    std::cin >> size;

    //создаём динамически массив
    int* arrForFunc = new int[size];

    //заполняем его значениями
    for(int i = 0; i < size; i++){
        arrForFunc[i] = rand()%100; // заполнил массив значениями
    }
    
    //выводим массив перед добавлением нового значенияж
    printArray(arrForFunc, size);

    //запрашиваем новое значение
    int newVal;
    std::cout << "Enter new value:";
    //std::cin >> newVal;

    //добавляем новое значение в массив
    uniquepush_back(arrForFunc, size, newVal);

    //выводим массив после добавления нового значенияж
    printArray(arrForFunc, size);

    //освобождаем память
    delete[] arrForFunc;


    //Задание 6. Рекурсивные функции. Напишите рекурсивную функцию вычисления
    //суммы первых N натуральных чисел.

    int resRecFunc = sumNatNums(5);

    //можно вычислить и без рекурсии
    int resRecFunc1 = (5*(5+1))/2;



    //Задание 7а. Функции с переменным числом параметров.
    //Напишите функцию (дана заготовка VarArgs, не использующая
    // макросы), которая принимает переменное число аргументов
    // типа int и выводит на печать число принятых параметров и
    // их значения.
    // Признаком конца списка является нулевое значение.
    
    int nN1=5, nN2=11, nN3=4, nN4=7, nN5=-1;
    VarArgs(nN1,0,0);
    VarArgs(nN1,nN2,0);
    VarArgs(nN1,nN2,nN3,nN4,nN5,0);
    stop


    //Задание 7б. Модифицируйте функцию 7а с помощью макросов
    // va_start, va_arg, va_end

    VarArgs2(3,1,2,3);
    VarArgs2(5,nN1,nN2,nN3,nN4,nN5);

    //Задание 8. Возвращение адреса.
    //Напишите функцию, которая находит минимальное значение в массиве,
    // таким образом, чтобы ее вызов можно было использовать слева от знака
    // равенства: *MyMin(параметры) = 0;
    
    int mas[5] = {1,2,3,4,5};
    *MyMin(mas, 5) = 5;

    std::cout << mas[0];

    return 0;
}//main

