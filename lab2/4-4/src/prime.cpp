#include "prime.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    //TODO: ��� vector<bool> ���������� �� ������ �����������
    // �����: vector<bool> ������������� ��� �������� ������� ��������.
    // ��� ����������� � ������� ����, ��� ������ ������� � vector<bool> ����������
    // ������ ���� ��� ��� �������� �������� true/false
    std::vector<bool> isPrime(upperBound + 1, true);
    std::set<int> primes;

    isPrime[0] = false;

    //TODO �� ������������ ���������� ����� - i*i
    for (int i = 2; i * i <= upperBound; ++i)
    {
        if (isPrime[i])
        {
            //TODO �������� � 2 ���� ��������� ��� ����,
            // ��� ������ ����� ����� ������ �������� ��� ����������
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
            //TODO � insert ���� ������ � ����������
            primes.insert(primes.end(), i);
        }
    }
    return primes;
}
