import numpy as np
import random


#definicja funkcji optymalizowanej
def function(x):
    return (2 * x[0] ** 2) + (x[1] ** 3) - (x[2] ** 2) + (7 * x[3] ** 2) - (2 * x[4] ** 5)

#ograniczenia zadania
def is_valid(x):
    return (0 <= x[0] <= 10 and
            0 <= x[1] % 10 in {1, 2, 3, 4, 5, 6, 7} and
            0 <= x[2] >= 1 and
            0 <= x[3] <= 20 and
            0 <= x[4] > 5)

#tworzenie populacji początkowej
def initialize_population(pop_size, chromosome_length):
    population = []
    while len(population) < pop_size:
        individual = np.random.randint(0, 26, chromosome_length)
        if is_valid(individual):
            population.append(individual)
    return population


# selekcja ruletkowa osobników, szansa na bycie wybranym jest proporcjonalne do jakości osobnika
def selection(population, scores):
    min_score = np.min(scores)
    if min_score < 0:
        scores = scores - min_score

    total_score = np.sum(scores)
    if total_score == 0:
        probabilities = np.ones(len(population)) / len(population)
    else:
        probabilities = scores / total_score

    selected_indices = np.random.choice(len(population), size=len(population), replace=True, p=probabilities)
    return [population[i] for i in selected_indices]

#krzyżowanie osobników, wybiera się locus za którym następuje wymiana genów
def crossover(parent1, parent2):
    locus = np.random.randint(1, len(parent1) - 1)
    child1 = np.concatenate((parent1[:locus], parent2[locus:]))
    child2 = np.concatenate((parent2[:locus], parent1[locus:]))
    return child1, child2

#mutacja osobnika, na podstawie wskaźnika mutacji przypadkowo wybiera się geny które będą mutowane i zmienia się ich wartość na przypadkową
def mutate(individual, mutation_rate):
    for i in range(len(individual)):
        if random.random() < mutation_rate:
            individual[i] = np.random.randint(0, 26)
    return individual

def genetic_algorithm(pop_size, chromosome_length, generations, mutation_rate):
    population = initialize_population(pop_size, chromosome_length)
    best_solution = None
    best_score = 0

    for generation in range(generations):
        scores = np.array([function(ind) for ind in population])
        best_index = np.argmax(scores)

        if scores[best_index] > best_score:
            best_score = scores[best_index]
            best_solution = population[best_index]

        selected_population = selection(population, scores)
        next_population = []

        for i in range(0, pop_size, 2):
            parent1, parent2 = selected_population[i], selected_population[i + 1]
            child1, child2 = crossover(parent1, parent2)
            next_population.extend([mutate(child1, mutation_rate), mutate(child2, mutation_rate)])

        population = [ind for ind in next_population if is_valid(ind)]

        while len(population) < pop_size:
            individual = np.random.randint(0, 26, chromosome_length)
            if is_valid(individual):
                population.append(individual)

    return best_solution, best_score

population_size = 100
chromosome_length = 5
generations = 3000
mutation_rate = 0.01

(best_solution, best_score) = genetic_algorithm(population_size, chromosome_length, generations, mutation_rate)

print("Najlepsze rozwiązanie:", best_solution)
print("Najlepszy wynik:", best_score)


