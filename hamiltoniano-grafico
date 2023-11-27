import itertools
import networkx as nx
import matplotlib.pyplot as plt

def find_hamiltonian_circuits(graph):

	def is_valid(v, pos, path):
		if graph[path[pos - 1]][v] == 0:
			return False
		if v in path:
			return False
		return True

	def hamiltonian_util(path, pos):
		if pos == len(graph):
			return True

		for v in range(len(graph)):
			if is_valid(v, pos, path):
				path[pos] = v

				if hamiltonian_util(path, pos + 1):
					return True

				path[pos] = -1

		return False

	def calculate_path_cost(path):
		cost = 0
		for i in range(len(path) - 1):
			cost += graph[path[i]][path[i + 1]]
		return cost

	n = len(graph)
	path = [-1] * n
	path[0] = 0

	if not hamiltonian_util(path, 1):
		print("Não existe um circuito hamiltoniano possível.")
		return

	G = nx.Graph()
	G.add_nodes_from(range(n))

	for i in range(n):
		for j in range(i + 1, n):
			if graph[i][j] != 0:
				G.add_edge(i, j, weight=graph[i][j])

	pos = nx.spring_layout(G)
	labels = {i: f'{chr(ord("A") + i)}' for i in G.nodes}

	nx.draw(G, pos, with_labels=True, labels=labels)
	edge_labels = nx.get_edge_attributes(G, 'weight')
	nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

	plt.show()

	paths = []
	for perm in itertools.permutations(range(1, n)):
		perm = (0, ) + perm + (0, )
		paths.append(perm)

	paths.sort(key=lambda x: calculate_path_cost(x))

	for path in paths:
		cost = calculate_path_cost(path)
		city_names = ''.join(chr(ord('A') + i) for i in path)
		print(f"Caminho {city_names}: ({cost})")


graph = [[0, 4, 2, 1], [4, 0, 13, 9], [2, 13, 0, 8], [1, 9, 8, 0]]

find_hamiltonian_circuits(graph)
