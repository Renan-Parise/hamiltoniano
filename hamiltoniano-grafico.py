import itertools
import networkx as nx
import matplotlib.pyplot as plt

def encontrar_circuitos_hamiltonianos(grafo):

    def e_valido(v, pos, caminho):
        if grafo[caminho[pos - 1]][v] == 0:
            return False
        if v in caminho:
            return False
        return True

    def util_hamiltoniana(caminho, pos):
        if pos == len(grafo):
            return True

        for v in range(len(grafo)):
            if e_valido(v, pos, caminho):
                caminho[pos] = v

                if util_hamiltoniana(caminho, pos + 1):
                    return True

                caminho[pos] = -1

        return False

    def calcular_custo_caminho(caminho):
        custo = 0
        for i in range(len(caminho) - 1):
            custo += grafo[caminho[i]][caminho[i + 1]]
        return custo

    n = len(grafo)
    caminho = [-1] * n
    caminho[0] = 0

    if not util_hamiltoniana(caminho, 1):
        print("Não existe um circuito hamiltoniano possível.")
        return

    G = nx.Graph()
    G.add_nodes_from(range(n))

    for i in range(n):
        for j in range(i + 1, n):
            if grafo[i][j] != 0:
                G.add_edge(i, j, weight=grafo[i][j])

    pos = nx.spring_layout(G)
    labels = {i: f'{chr(ord("A") + i)}' for i in G.nodes}

    nx.draw(G, pos, with_labels=True, labels=labels)
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    plt.show()

    caminhos = []
    for perm in itertools.permutations(range(1, n)):
        perm = (0, ) + perm + (0, )
        caminhos.append(perm)

    caminhos.sort(key=lambda x: calcular_custo_caminho(x))

    for caminho in caminhos:
        custo = calcular_custo_caminho(caminho)
        nomes_cidades = ''.join(chr(ord('A') + i) for i in caminho)
        print(f"Caminho {nomes_cidades}: ({custo})")


encontrar_circuitos_hamiltonianos([[0, 4, 2, 1],
                                   [4, 0, 13, 9],
                                   [2, 13, 0, 8],
                                   [1, 9, 8, 0]])
