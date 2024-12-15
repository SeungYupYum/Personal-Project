# explanations for these functions are provided in requirements.py

from graph import Graph
from collections import deque
import math

def bfs_max_distance(graph: Graph, start_vertex: int):
	distances = {node: float('inf') for node in range(graph.get_num_nodes())}
	distances[start_vertex] = 0
	bfs_queue = deque([start_vertex])
	
	while bfs_queue:
		current = bfs_queue.popleft()
		current_distance = distances[current]

		for neighbor in graph.get_neighbors(current):
			if distances[neighbor] == float('inf'):  # Not visited
				distances[neighbor] = current_distance + 1
				bfs_queue.append(neighbor)
	
	# Find the node with the maximum distance from the start node
	max_distance = -1
	farthest_node = start_vertex
	
	for node, distance in distances.items():
		if distance != float('inf') and distance > max_distance:
			max_distance = distance
			farthest_node = node
			
	return farthest_node, max_distance

def get_diameter(graph: Graph) -> int:
	start_vertex = graph.select_single_vertex()
	diameter = -1

	while True:
		farthest_node, current_max_distance = bfs_max_distance(graph, start_vertex)

		if current_max_distance == diameter:
			break

		diameter = current_max_distance
		start_vertex = farthest_node
	
	return diameter

def number_of_triangle(graph: Graph):
	# To store degree : set of verticies
	degree_vertex_map = {}
	# To store vertex : degree
	vertex_degree_map = {}
	# Set to store which vertex is visted
	visited = set()
	# To store later neighbor, vertex : later vertices in the degeneracy order
	later_neighbor = {}

	# Initialize degree-vertex map & vertex-degree map
	for vertex in graph.get_vertex_list():
		degree = len(graph.get_neighbors(vertex))
		vertex_degree_map[vertex] = degree
		if degree in degree_vertex_map:
			degree_vertex_map[degree].add(vertex)
		else:
			degree_vertex_map[degree] = {vertex}

	while len(visited) != graph.get_num_nodes():
		# get the currently minimum key, and select vertex in the set
		min_key = min(degree_vertex_map.keys())
		selected_vertex = degree_vertex_map[min_key].pop()

		if len(degree_vertex_map[min_key]) == 0:
			del degree_vertex_map[min_key]

		# reduce 1 from the vertex degree map
		selected_vertex_neighbor_set = graph.get_neighbors(selected_vertex)
		later_neighbor_set = selected_vertex_neighbor_set - visited
		for vertex in later_neighbor_set:
			current_degree = vertex_degree_map[vertex]
			new_degree = current_degree - 1

			degree_vertex_map[current_degree].remove(vertex)
			if len(degree_vertex_map[current_degree]) == 0:
				del degree_vertex_map[current_degree]

			if new_degree in degree_vertex_map:
				degree_vertex_map[new_degree].add(vertex)
			else:
				degree_vertex_map[new_degree] = set()
				degree_vertex_map[new_degree].add(vertex)
			
			vertex_degree_map[vertex] = new_degree		

		# add the difference into later_neighbor
		later_neighbor[selected_vertex] = later_neighbor_set

		# add selected vertex into visited set
		visited.add(selected_vertex)
	
	traiangle = 0

	for v in graph.get_vertex_list():
		later_neighbor_set = later_neighbor[v]

		for u in later_neighbor_set:
			for w in later_neighbor_set:
				if u in graph.get_neighbors(w):
					traiangle += 1
					
	return traiangle / 2

def two_edge_path(graph: Graph):
	vertex_list = graph.get_vertex_list()
	two_edge_path = 0

	for vertex in vertex_list:
		degree = len(graph.get_neighbors(vertex))
		two_edge_path += (degree * (degree - 1)) / 2
	return two_edge_path

def get_clustering_coefficient(graph: Graph) -> float:
	numerator = 3 * number_of_triangle(graph)
	denominator = two_edge_path(graph)

	return numerator / denominator

def get_degree_distribution(graph: Graph) -> dict[int, int]:
	degree_distribution = {}

	for vertex in graph.graph_structure:
		degree = len(graph.get_neighbors(vertex))

		if degree in degree_distribution:
			degree_distribution[degree] += 1
		else:
			degree_distribution[degree] = 1
	
	return degree_distribution
