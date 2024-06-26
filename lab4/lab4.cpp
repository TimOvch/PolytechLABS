
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

#define    stop

//функция для вывода массива
void printArray(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

//замена по указателям
void swapUk(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//замена по ссылкам
void swapS(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

//нахождение минимального значения для встроенного двумерного массива
int minAr(int* nMas, const int rows, const int cols){
    //создаем переменную с максимально возможным значением, чтобы не потерять минимального
    int min = 2147483647;

    //ищем минимальное значение
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(*(nMas+i*rows+j) < min){
                min = *(nMas+i*rows+j);
            }
        }
    }

    //возвращаем
    return min;
}

//нахождение минимального значения для динамического двумерного массива
int minAr(int** nMas, int lenmas, int lenvmas){
    //создаем переменную с максимально возможным значением, чтобы не потерять минимального
    int min = 2147483647;

    //ищем минимальное значение
    for(int i = 0; i < lenmas; i++){
        for(int j = 0; j < lenvmas; j++){
            if(*((*(nMas+i))+j) < min){
                min = *((*(nMas+i))+j);
            }
        }
    }

    //возвращаем
    return min;
}

//моя функция для лексикографического сравнения строк
int MyStrCmp(const char*a,const char*b){
    //создаём флаг на случай равенства строк
    bool equal = 1;

    //создаем такой флаг, что в случае если a > b он будет равен 1, если нет 0
    bool aBolb = 0;
    
    //проходимся по значениям каждой строки и сравниваем
    int i = 0;
    while(true){
        if(a[i]==b[i]){ //случай равности
            if(a[i]=='\0'){//выход из цикла для равности
                break;
            }
            i++;
            continue;
        } else if((int(a[i]) > int(b[i])) || (b[i] == '\0')){ //случай a>b
            aBolb = 1;
            equal = 0;
            break;
        } else if((int(a[i]) < int(b[i])) || (a[i] == '\0')){ //случай b>a
            equal = 0;
            break;
        }
        i++;
    }

    //проверяем по флагам и возвращаем нужное значение
    if(equal){
        return 0;
    } else if(aBolb){
        return 1;
    } else{
        return -1;
    }
}

//глобальный массив високосного и невисокосного года, чтобы было меньше передавать в функцию
int nDayTab[2][12]={
        {31,28,31,30,31,30,31,31,30,31,30,31}, //невисокосный год
        {31,29,31,30,31,30,31,31,30,31,30,31}  //високосный год
        };

//функция подсчета дня с начала года из месяца и числа
int DayOfYear(int day, int month, int year){
    //создаем переменную для подсчета для с начала года
    int numOfDay = day;
    //проверка на високосность
    bool isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));

    //прибавляем значения целых прошедших месяцов в зависимоси от високосности
    for(int i = 0; i < month-1; i++){
        numOfDay+=nDayTab[isLeapYear][i];
    }

    //возвращаем значение
    return numOfDay;
}

//функция для подсчета месяца и числа из дня с начала года
void DayOfMonth(int numOfDay, int year,int *dayAndMonth){
    *dayAndMonth = 0; //первое значение для даты
    *(dayAndMonth + 1) = 1; //второе значение для месяца

    //проверка года на високосность
    bool isLeapYear = (year%400==0) || ((year%4 == 0) && (year%100!=0));

    //вводим счетчик для даты и с помощью него будем проверять количество месяцев
    int kDays = nDayTab[isLeapYear][0];

    //проверка на случай если месяц 0, то есть январь
    if(numOfDay > kDays){
        //пока переменная с днем с начала года по счету - переменная с суммой дней прошедших месяцов положительна делаем следующее:
        while(numOfDay - kDays > 0){
            //меняем дату
            dayAndMonth[0]=numOfDay-kDays;
            
            //прибавляем количество дней прошедшего месяца в счетчик для даты
            kDays+=nDayTab[isLeapYear][dayAndMonth[1]];

            //прибавляем месяц
            dayAndMonth[1]+=1;
        }
    } else{
        //в случае если количество дней с начала года < количество дней в первом месяце, значит кол-во дней с начала года = дата в месяце
        //а месяц в таком случае первый, какой у нас и стоит изначально
         dayAndMonth[0] = numOfDay;
    }
}

//функция для добавления в массив значения в случае уникальности
void uniquepush_back(int*& arr, int& size, int newVal){
    //Проверка на уникальность
    bool isunique = 1;
    for(int i = 0; i < size; i++){
        if(arr[i]==newVal){
            isunique = 0;
            break;
        }
    }

    if(isunique){
        //создаём новый массив на +1 элемент
        int newSize = size + 1;
        int *newArr = new int[newSize];

        //копируем значения из старого массива
        for(int i = 0; i < size; i++){
            newArr[i] = arr[i];
        }

        //добавляем новое значение
        newArr[size] = newVal;

        //освобождаем память, занятую старым массивом
        delete[] arr;

        //Обновляем указатель и размерность
        arr = newArr;
        size = newSize;
    }
}

//создаю функцию для вычисление суммы первых n натуральных чисел
int sumNatNums(int n){
    //создаём дно рекурсии
    if(n==1){
        return 1;
    }

    //считаем сумму для прошлого числа
    int prevSumNum = sumNatNums(n-1);

    //возвращаем сумму прошлого + настоящее
    return n + prevSumNum;
}


//функция для вывода в консоль переменного кол-ва параметров
void VarArgs (int start, ...){
    //все элементы в памяти расположенны за обязательным аргументом, поэтому выводим все, пока не встретим 0
    int* currentArg = &start;
    int totalargs = 1;
    while (*currentArg != 0)
    {
        std::cout<<"Argument: " << *currentArg << "\n";
        currentArg++;
        totalargs++;
    }
    std::cout << "Total arguments: " << totalargs;
    std::cout << '\n';
}

//версия функции с использованием макросов va
void VarArgs2(int count, ...){
    va_list list;
    va_start(list, count);
    for(int i = 0; i < count; i++){
        std::cout<<"Argument: " << va_arg(list, int) << "\n";
    }
    va_end(list);
    std::cout << "Total arguments: " << count << '\n';
}

//функция MyMin, которая возвращает адрес минимального числа
int* MyMin(int* arr, int size){
    int min = 2147483647;
    int* res = &min;
    for(int i = 0; i < size; i++){
        if(arr[i] < min){
            min = arr[i];
            res = &arr[i];
        }
    }
    return res;
}

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
    
    extern int* ref;
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
    val = IncByValue(val);
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

    int    nX = 1;
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
    }

    //ищу минимальное в двумерном динамическом массиве
    int res2 = minAr(dAr, n, m);

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
    int Ans2[2];
    DayOfMonth(295, 2023, Ans2);

    //выводим результаты и сравниваем
    std::cout << Ans2[0] << " " << Ans2[1] << '\n';

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
    std::cin >> newVal;

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

