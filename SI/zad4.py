import numpy as np
import matplotlib.pyplot as plt

# generowanie liczb
np.random.seed(0)
num_samples_per_class = 100
X0 = np.random.multivariate_normal([0, 0], [[1, .75], [.75, 1]], num_samples_per_class)
X1 = np.random.multivariate_normal([1, 4], [[1, .75], [.75, 1]], num_samples_per_class)

X = np.vstack([X0, X1])
y = np.hstack([np.zeros(num_samples_per_class), np.ones(num_samples_per_class)])

# normalizacja cech
X_mean = X.mean(axis=0)
X_std = X.std(axis=0)
X = (X - X_mean) / X_std

class LogisticRegression:
    def __init__(self, learning_rate=0.01, num_iter=1000):
        self.lr = learning_rate
        self.num_iter = num_iter

    def add_intercept(self, X):
        intercept = np.ones((X.shape[0], 1))
        return np.concatenate((intercept, X), axis=1)

    def sigmoid(self, z):
        return 1 / (1 + np.exp(-z))

    def fit(self, X, y):
        X = self.add_intercept(X)
        self.theta = np.zeros(X.shape[1])
        for i in range(self.num_iter):
            z = np.dot(X, self.theta)
            h = self.sigmoid(z)
            gradient = np.dot(X.T, (h - y)) / y.size
            self.theta -= self.lr * gradient

    def predict_prob(self, X):
        X = self.add_intercept(X)
        return self.sigmoid(np.dot(X, self.theta))

    def predict(self, X, threshold=0.5):
        return self.predict_prob(X) >= threshold

# inicjalizacja modelu
model = LogisticRegression(learning_rate=0.1, num_iter=3000)
model.fit(X, y)

# predykcje
sample_points = np.array([[0, 0], [1, 1], [-1, -1]])
normalized_sample_points = (sample_points - X_mean) / X_std
predictions = model.predict(normalized_sample_points)

print("Sample points:", sample_points)
print("Predictions:", predictions)

plt.figure(figsize=(10, 7))

# Dane treningowe
plt.scatter(X[y == 0][:, 0], X[y == 0][:, 1], color='blue',edgecolors='black', label='Cecha 1')
plt.scatter(X[y == 1][:, 0], X[y == 1][:, 1], color='red',edgecolors='black', label='Cecha 2')

# krzywa regresji
x_values = np.linspace(X[:, 0].min(), X[:, 0].max(), 100)
y_values = -(model.theta[0] + model.theta[1] * x_values) / model.theta[2]
plt.plot(x_values, y_values, label='Granica decyzyjna', color='red')

plt.scatter(normalized_sample_points[:, 0], normalized_sample_points[:, 1], color='green', edgecolors='black', label='Predykcje')

plt.xlabel('Cecha 1')
plt.ylabel('Cecha 2')
plt.legend()
plt.title('Granica decyzyjna regresji logistycznej')
plt.show()
