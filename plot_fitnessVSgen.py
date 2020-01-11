#!/usr/bin/env python3

import matplotlib.pyplot as plt
import os
import functools
import operator
import numpy as np
import pandas as pd

DIR1 = "fifthExperimentBatch"
DIR2 = "sixthExperimentBatch"


def extractFitnesses(dir):
    fitnesses = []
    for fname in os.listdir(DIR1):
        if fname != "config.txt":
            with open(dir + "/" + fname) as fd:
                data = fd.read().strip().split("\n")
                data = list(filter(lambda x: x.startswith("Total"), data))
                data = list(map(lambda x: x[x.find(":") + 2:], data))
                data = list(map(float, data))
                fitnesses.append(data)
    return fitnesses


def cumulativeFitness(fitnesses, pop_size):
    cumulativeFitnesses = [0 for _ in range(20)]
    for f in fitnesses:
        for j in range(20):
            cumulativeFitnesses[j] += f[j] / pop_size
    return list(map(lambda x: x/500, cumulativeFitnesses))


if __name__ == '__main__':
    fitnesses1 = extractFitnesses(DIR1)
    fitnesses2 = extractFitnesses(DIR2)

    cumulativeFitnesses1 = cumulativeFitness(fitnesses1, 10)
    cumulativeFitnesses2 = cumulativeFitness(fitnesses2, 50)

    df = pd.DataFrame({'Generations': range(0, 20), 'Population = 10': cumulativeFitnesses1, 'Population = 50': cumulativeFitnesses2 })

    plt.plot('Generations', 'Population = 10', data=df, marker='', color='red', linewidth=2)
    plt.plot('Generations', 'Population = 50', data=df, marker='', color='blue', linewidth=2)
    plt.legend()
    plt.title("Population fitness vs Generation with λ1 = 1, λ2 = 0, μ1 = 2, μ2 = 5")
    plt.xlabel("Generations")
    plt.ylabel("Average population fitness (normalized)")
    plt.savefig("plot3.png")

