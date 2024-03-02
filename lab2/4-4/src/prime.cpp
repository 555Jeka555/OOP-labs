#include "prime.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    //TODO: Чем vector<bool> отличается от других контейнеров
    // Ответ: vector<bool> оптимизирован для хранения булевых значений.
    // Это достигается с помощью того, что каждый элемент в vector<bool> использует
    // только один бит для хранения значения true/false
    std::vector<bool> isPrime(upperBound + 1, true);
    std::set<int> primes;

    isPrime[0] = false;

    //TODO не использовать квадратные корни - i*i
    for (int i = 2; i * i <= upperBound; ++i)
    {
        if (isPrime[i])
        {
            //TODO ускорить в 2 раза используя тот факт,
            // что чётные числа после первой итерации уже вычеркнуты
            if (i % 2 == 0 && i != 2)
            {
                continue;
            }

            int step = 2*i;
            if (i == 2)
            {
                step = i;
            }

            for (int j = i * i; j <= upperBound; j += step)
            {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= upperBound; ++i)
    {
        if (isPrime[i])
        {
            //TODO у insert есть версия с подсказкой
            primes.insert(primes.end(), i);
        }
    }
    return primes;
}
