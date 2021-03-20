from sympy import acot
from scipy.optimize import newton
import math as m


def f(x):
    return m.cos(x) - x * m.sin(x)


def fprim(x):
    return -2 * m.sin(x) - x * m.cos(x)


def f_i(c):
    return lambda x: acot(x) + c


def fixedPoint(f, x0, tolerance=10e-7, maxiter=100):
    error = 1
    itr = 0
    x = 0
    while error > tolerance and itr < maxiter:
        x = float(f(x0))  # sledeca vrednost niza
        error = abs(x0 - x)  # procena greske u trenutnom koraku
        x0 = x
        itr = itr + 1
    return x


def main():
    print("Funkcija za koju trazimo tri najmanje pozitivne nule: cosx - x * sinx = 0")
    while True:
        print("""Izaberite opciju za izracunavanje:
        1. Racunanje Njutnovom metodom
        2. Racunanje metodom proste iteracije
        0. Izadji 
        Vas izbor? """)
        option = int(input())
        if option == 1:
            x1 = newton(f, 0.5, fprim)
            x2 = newton(f, 3, fprim)
            x3 = newton(f, 6, fprim)
            print(f"x1 = {x1:.6f}, x2 = {x2:.6f}, x3 = {x3:.6f}")
        elif option == 2:
            x1 = fixedPoint(f_i(0), 0.6)
            x2 = fixedPoint(f_i(m.pi), 3)
            x3 = fixedPoint(f_i(m.pi * 2), 6)
            print(f"x1 = {x1:.6f}, x2 = {x2:.6f}, x3 = {x3:.6f}")
        elif option == 0:
            break
        else:
            print("Nepostojeca opcija!")


if __name__ == '__main__':
    main()
