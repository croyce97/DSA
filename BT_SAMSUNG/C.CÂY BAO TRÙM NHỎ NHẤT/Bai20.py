import matplotlib.pyplot as plt
import networkx as nx

def draw_graph(graph):
  """Vẽ đồ thị"""
  plt.figure(figsize=(8, 8))
  nx.draw(graph, with_labels=True)
  plt.show()

def find_min_spanning_tree(graph):
  """Tìm cây bao trùm min"""
  # Khởi tạo một cây bao trùm rỗng.
  tree = nx.Graph()

  # Sắp xếp các cạnh theo trọng số giảm dần.
  edges = sorted(graph.edges(data=True), key=lambda x: x[2]['weight'], reverse=True)

  # Lặp lại qua tất cả các cạnh.
  for edge in edges:
    # Nếu xóa cạnh này không làm đồ thị mất liên thông thì thêm nó vào cây bao trùm.
    if nx.is_connected(graph.copy().remove_edge(edge[0], edge[1])):
      tree.add_edge(edge[0], edge[1], weight=edge[2]['weight'])

  return tree

def animate(graph, tree):
  """Vẽ hoạt hình quá trình dựng cây bao trùm min"""
  # Khởi tạo một khung hình mới.
  fig = plt.figure(figsize=(8, 8))
  ax = fig.add_subplot(1, 1, 1)

  # Vẽ đồ thị ban đầu.
  draw_graph(graph)

  # Lặp lại qua tất cả các cạnh của cây bao trùm.
  for edge in tree.edges(data=True):
    # Vẽ cạnh đó.
    ax.plot([edge[0], edge[1]], color='red', linewidth=2)

    # Cập nhật khung hình.
    plt.pause(0.5)
    plt.draw()

def main():
  # Tạo đồ thị
  graph = nx.Graph()
  graph.add_edges_from([(0, 1, {'weight': 1}), (0, 2, {'weight': 7}), (1, 3, {'weight': 2}), (2, 3, {'weight': 4}), (3, 4, {'weight': 5})])

  # Tìm cây bao trùm min
  tree = find_min_spanning_tree(graph)

  # Vẽ hoạt hình
  animate(graph, tree)

if __name__ == '__main__':
  main()
