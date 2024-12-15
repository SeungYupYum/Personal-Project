# explanations for member functions are provided in requirements.py
# each file that uses a graph should import it from this file.

from collections.abc import Iterable
import random

class Graph:
	def __init__(self, num_nodes: int, edges: Iterable[tuple[int, int]]):
		self.num_node = num_nodes
		self.num_edge = 0
		self.graph_structure = {i: set() for i in range(num_nodes)}  # Initialize all nodes

		for edge in edges:
			vertex1 = edge[0]
			vertex2 = edge[1]
			
			self.graph_structure[vertex1].add(vertex2)
			self.graph_structure[vertex2].add(vertex1)

			self.num_edge += 1

	def get_num_nodes(self) -> int:
		return self.num_node

	def get_num_edges(self) -> int:
		return self.num_edge

	def get_neighbors(self, node: int) -> Iterable[int]:
		return self.graph_structure[node]

	def select_single_vertex(self):
		vertex = random.choice(list(self.graph_structure.keys()))
		
		while len(self.get_neighbors(vertex)) == 0:
			vertex = random.choice(list(self.graph_structure.keys()))
		
		return vertex
	
	def get_vertex_list(self):
		return list(self.graph_structure.keys())
	# feel free to define new methods in addition to the above
	# fill in the definitions of each required member function (above),
	# and for any additional member functions you define
