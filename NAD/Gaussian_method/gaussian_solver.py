import numpy as np


# Funkcija koja pravi matricu iz teksta zadatka
def create_matrix_system(n):
    try:
        assert n > 0, "Dimenzija n mora biti veca od nule!"
        A = np.zeros((n, n))
        b = np.zeros(n)

        for i in range(n):
            for j in range(n):
                A[i, j] = (i + j) ** 2
                b[i] += A[i, j]

        return A, b
    except AssertionError as msg:
        print(msg)


# Klasa za resavanje sistema pomocu Guasove metode eliminacije sa parcijalnim pivotiranjem
class GaussWithPivot:
    def __init__(self, A, b):
        self.A = A
        self.b = b

        self.n = len(A)
        self.x = np.zeros(self.n)

        self._elimination()
        self._backsub()

    def _elimination(self):
        for i in range(self.n - 1):
            j = self.A[i:, i].argmax() + i
            if self.A[j, i] == 0:
                raise ValueError("Matrica je singularna")
            if j != i:
                self.A[[j, i], :] = self.A[[i, j], :]
                self.b[[j, i]] = self.b[[i, j]]

            for row in range(i + 1, self.n):
                m = self.A[row, i] / self.A[i, i]
                self.A[row, i:] = self.A[row, i:] - m * self.A[i, i:]
                self.b[row] = self.b[row] - m * self.b[i]

    def _backsub(self):
        for i in range(self.n - 1, -1, -1):
            if self.A[i, i] != 0:
                self.x[i] = (self.b[i] - np.dot(self.A[i, i + 1:], self.x[i + 1:])) / self.A[i, i]
            else:
                self.x[i] = 1.  # Slucaj kada sistem ima beskonacno resenja


def main():
    for n in range(2, 5):
        print("n = {}".format(n))
        A, b = create_matrix_system(n)
        print("Matrica koeficijenata A:\n {}".format(A))
        print("Kolona slobodnih clanova b:\n {}".format(b[:, None]))
        solution = GaussWithPivot(A, b)
        print("Rešenje sistema: ")
        print(solution.x)


if __name__ == '__main__':
    main()
