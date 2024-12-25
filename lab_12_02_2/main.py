from ctypes import *

lib = cdll.LoadLibrary('./out/libarr.so')

fib = lib.fib_arr
fib.argtypes = [POINTER(c_int), c_size_t]
fib.restype = c_int

filter = lib.filter
filter.argtypes = [POINTER(c_int), POINTER(c_size_t), POINTER(c_int), c_size_t]
filter.restype = c_int

def main():
    print('Заполнение массива числами Фиббоначи')
    size = int(input('Введите длину массива: '))
    while (size <= 0):
        print('Длина не может быть отрицательной или 0. Попробуйте еще раз')
        size = int(input('Введите длину массива: '))
    
    arr = (c_int * size)()
    res = fib(arr, c_size_t(size))
    if res != 0:
        print('Ошибка')
        return
    
    print('Массив, заполненный числами Фиббоначи:')
    for i in arr:
        print(i, end=' ')
    print()

    print()
    print('Фильтрация массива')
    arr = list(map(int, input('Введите массив для фильтрации (в одну строку): ').split()))

    c_arr_type = c_int * len(arr)
    c_arr = c_arr_type(*arr)

    print('1. Обращение к библиотеке для уточнения размера новго массива:')

    new_size = c_size_t()
    res = filter(None, byref(new_size), c_arr, c_size_t(len(arr)))
    if res != 0:
        print('Ошибка')
        return
    
    new_arr = (c_int * new_size.value)()

    res = filter(new_arr, byref(new_size), c_arr, c_size_t(len(arr)))
    if res != 0:
        print('Ошибка')
        return
    
    print('Отфильтрованный массив:')
    for i in new_arr:
        print(i, end=' ')
    print()

    print('2. Выделение памяти с запасом: ')

    new_size = c_size_t(len(arr))
    new_arr = (c_int * new_size.value)()

    res = filter(new_arr, byref(new_size), c_arr, c_size_t(len(arr)))

    if res != 0:
        print('Ошибка')
        return
    
    print('Отфильтрованный массив:')
    for i in new_arr:
        print(i, end=' ')
    print()

main()
