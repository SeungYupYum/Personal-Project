from graph import Graph # type: ignore
from graph_algorithms import get_diameter # type: ignore
from graph_algorithms import get_clustering_coefficient # type: ignore
from graph_algorithms import get_degree_distribution # type: ignore

import math
import random
import matplotlib.pyplot as plt
import numpy as np

def eros_renyi_graph_generator(num_nodes):
    p = (2 * math.log(num_nodes)) / num_nodes
    
    # Initialize the graph: empty edge list and nodes
    edges = []
    v = 1
    w = -1

    # Main loop to generate edges
    while v < num_nodes:
        # Draw a random number uniformly between 0 and 1
        r = random.uniform(0, 1)
        
        # Calculate the skip (next node index to consider)
        w += 1 + math.floor(math.log(1 - r) / math.log(1 - p))
        
        # Update to skip over runs of 0's
        while w >= v and v < num_nodes:
            w -= v
            v += 1
        
        # Add an edge if within bounds
        if v < num_nodes:
            edges.append((v, w))

    # Return the graph as a list of edges
    return edges

def barabasi_albert_graph_generator(num_nodes, d):
    # Initialize the M array to store edges
    M = [0] * (2 * num_nodes * d)
    
    for v in range(num_nodes):
        for i in range(d):
            # Add v to M
            M[2 * ((v * d) + i)] = v
            
            r = random.randint(0, 2 * ((v * d) + i))
            M[2 * ((v * d) + i) + 1] = M[r]
            
    # Create the edge list
    edges = []
    for i in range(num_nodes * d):
        edges.append((M[(2 * i)], M[(2 * i) + 1]))
    
    return edges

def phase2_degree_distribution():
    d = 5

    small_ba_graph = eros_renyi_graph_generator(1000)
    small_ba = Graph(1000, small_ba_graph)
    dict1 = get_degree_distribution(small_ba)
    dict1_lin = dict(sorted(dict1.items()))
    

    medium_ba_graph = eros_renyi_graph_generator(10000)
    medium_ba = Graph(10000, medium_ba_graph)
    dict2 = get_degree_distribution(medium_ba)
    dict2_lin = dict(sorted(dict2.items()))
    

    large_ba_graph = eros_renyi_graph_generator(100000)
    large_ba = Graph(100000, large_ba_graph)
    dict3 = get_degree_distribution(large_ba)
    dict3_lin = dict(sorted(dict3.items()))
    
    
    plt.figure()  # Create a new figure
    plt.plot(list(dict1_lin.keys()), list(dict1_lin.values()), marker='s', linestyle='--')
    plt.xlabel("Degree")
    plt.ylabel("Frequency")
    plt.title("Degree Distribution for Small GNP with Size 1000 (lin-lin)")
    plt.legend()
    plt.show()

    # Plot for dict2
    plt.figure()  # Create a new figure
    plt.plot(list(dict2_lin.keys()), list(dict2_lin.values()), marker='s', linestyle='--')
    plt.xlabel("Degree")
    plt.ylabel("Frequency")
    plt.title("Degree Distribution for Medium GNP with Size 10000 (lin-lin)")
    plt.legend()
    plt.show()

    # Plot for dict3
    plt.figure()  # Create a new figure
    plt.plot(list(dict3_lin.keys()), list(dict3_lin.values()), marker='^', linestyle=':')
    plt.xlabel("Degree")
    plt.ylabel("Frequency")
    plt.title("Degree Distribution for Large GNP with Size 100000 (lin-lin)")
    plt.legend()
    plt.show()

    dict1_log2 = {math.log2(k): math.log2(v) for k, v in dict1_lin.items()}
    dict2_log2 = {math.log2(k): math.log2(v) for k, v in dict2_lin.items()}
    dict3_log2 = {math.log2(k): math.log2(v) for k, v in dict3_lin.items()}

    plt.figure()  # Create a new figure
    plt.plot(list(dict1_log2.keys()), list(dict1_log2.values()), marker='s', linestyle='--')
    plt.xlabel("Degree")
    plt.ylabel("Frequency")
    plt.title("Degree Distribution for Small GNP with Size 1000 (log-log)")
    plt.legend()
    plt.show()

    # Plot for dict2
    plt.figure()  # Create a new figure
    plt.plot(list(dict2_log2.keys()), list(dict2_log2.values()), marker='s', linestyle='--')
    plt.xlabel("Degree")
    plt.ylabel("Frequency")
    plt.title("Degree Distribution for Medium GNP with Size 10000 (log-log)")
    plt.legend()
    plt.show()

    # Plot for dict3
    plt.figure()  # Create a new figure
    plt.plot(list(dict3_log2.keys()), list(dict3_log2.values()), marker='^', linestyle=':')
    plt.xlabel("Degree")
    plt.ylabel("Frequency")
    plt.title("Degree Distribution for Large GNP with Size 100000 (log-log)")
    plt.legend()
    plt.show()
    
def phase2_other():
    size = [100, 200, 300, 400, 500, 1000, 1500, 2000, 2500, 5000, 10000, 20000, 30000, 40000, 50000, 100000, 1000000]
    avg_diameter_lin = []
    avg_clustering_coefficient_lin = []
    
    for n in size:
        print("Size: ", n)
        avg_diameter = 0
        avg_clustering_coefficient = 0
        for iteration in range(100):
            if iteration == 50:
                print("Half way")
            if iteration == 99:
                print("Last iteration")
            gnp_graph = eros_renyi_graph_generator(n)
            gnp = Graph(n, gnp_graph)
            gnp_diameter = get_diameter(gnp)
            gnp_clustering_coefficient = get_clustering_coefficient(gnp)
            avg_diameter += gnp_diameter
            avg_clustering_coefficient += gnp_clustering_coefficient

        avg_diameter = avg_diameter / 50
        avg_clustering_coefficient = avg_clustering_coefficient / 50
        avg_diameter_lin.append(avg_diameter)
        avg_clustering_coefficient_lin.append(avg_clustering_coefficient)

    print("linear diameter per size: ", avg_diameter_lin)
    print("linear clustering coefficient: ", avg_clustering_coefficient_lin)

phase2_degree_distribution()