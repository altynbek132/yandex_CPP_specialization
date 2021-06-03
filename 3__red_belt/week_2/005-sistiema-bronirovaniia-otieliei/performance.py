# PERFORMANCE:

from math import *


def main():
    Q = 10 ** 5
    T = 10 ** 18
    L = 12
    C = 10 ** 9
    R = 1000
    W = 86400

    book = log(Q) * L
    # book += interval  # amortized
    clients = 1
    rooms = 1  # store room count
    complexities = [book, clients, rooms]
    print('complexities: {complexities}'.format(complexities=complexities))

    coeff = 50
    compl_total = sum(complexities) * Q * coeff

    cpu = 10 ** 9
    max_time = 1

    T = compl_total / cpu
    print('time: {time}'.format(time=T))


if __name__ == '__main__':
    main()
