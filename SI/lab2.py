import numpy as np
import matplotlib.pyplot as plt

# generowanie losowych danych liniowych
np.random.seed()
X = 2 * np.random.rand(100, 1)
Y = 5 + 3 * X + np.random.randn(100, 1)

# tworzenie parametrów
a = np.random.randn(1)
b = np.random.randn(1)
learning_rate = 0.005
iteration = 1000
m = len(X)

# gradient
for i in range(iteration):
    y_pred = a * X + b
    error = y_pred - Y
    grad_a = (2/m) * np.sum(error * X)
    grad_b = (2/m) * np.sum(error)
    a -= learning_rate * grad_a
    b -= learning_rate * grad_b

# obliczenie błędu
mse = np.mean((y_pred - Y)**2)

# predykcja 5 następnych wartości Y
X_next = np.array([[X.max() + 0.1 * (i + 1)] for i in range(5)])
y_pred_next = a * X_next + b

# rysowanie punktów i linii regresji
plt.scatter(X, Y)
plt.plot(X, y_pred, color='red')
plt.scatter(X_next, y_pred_next, color='black')

# dodanie linii od punktów do krzywej regresji
for x, y, yp in zip(X, Y, y_pred):
    plt.plot([x, x], [y, yp], color='green', linewidth=0.5)

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Wykres modelu regresji liniowej')

# dodawanie tekstu na diagramie
plt.text(0.05, 0.9, f"a: {a[0]:.2f}", transform=plt.gca().transAxes)
plt.text(0.05, 0.85, f"b: {b[0]:.2f}", transform=plt.gca().transAxes)
plt.text(0.05, 0.8, f"MSE: {mse:.2f}", transform=plt.gca().transAxes)

plt.show()
