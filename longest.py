# Найти самую длинную подпоследовательность возрастающих чисел
import numpy as np

def longest_increasing_subsequence(arr):
    arr = np.array(arr)
    n = len(arr)

    if n == 0:
        return []

    lis = np.ones(n, dtype=int)

    # Используем векторизацию для заполнения lis
    for i in range(1, n):
        lis[i] = np.max(np.where(arr[:i] < arr[i], lis[:i], 0)) + 1
    # arr[:i] < arr[i] поэлементно сравнивает чила в массиве, если условие верно, 
    # к предыдущей масимальной длине последовательности прибавляем 1, иначе сбрасываеи подсчет последовательности

    max_length = np.max(lis)

    # Восстановление самой длинной возрастающей подпоследовательности
    subsequence = []
    current_length = max_length
    for i in range(n - 1, -1, -1):
        if lis[i] == current_length: # с конца ищем элемент, на котором максимальная последоовательность закончилась
            subsequence.append(arr[i])
            current_length -= 1

    return subsequence[::-1]

arr = [1, 2, 5, 6, 7, 10]
result = longest_increasing_subsequence(arr)
print(result)
