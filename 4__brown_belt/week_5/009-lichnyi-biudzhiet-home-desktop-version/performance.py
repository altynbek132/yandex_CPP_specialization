"""
implementation
read all domains

"""
from math import *


def measure(complexities, time_limit, Q):
    coeff = 50
    complexity_total = sum(complexities) * coeff * Q

    cpu = 10 ** 9
    time = complexity_total / cpu
    print('time: {time}'.format(time=time))
    print('time_limit: {time_limit}'.format(time_limit=time_limit))


def main():
    # Количество запросов
    Q = 100
    # даты
    D = 99 * 365
    # value
    V = 1000000
    time_limit = 1

    complexities = [
        1,
        D,
        D,
    ]

    measure(complexities, time_limit, Q)
    pass


if __name__ == '__main__':
    main()
