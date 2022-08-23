import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation
import sys

# The function to animate moving ants
def update(frame):
    global colors, edge_colors, width, lines, length, i, pos
    if i >= length - 2:
        nx.draw(g, pos=pos, font_color='white', edge_color=edge_colors,
               width=list(weights), node_size=10)
        fig.set_facecolor("#00000F")
        return

    j = lines[i].split(' ')
    nodes_colored = []
    for q in j:
        x = q.split('-')
        nodes_colored.append(x[1])
        if g.nodes[x[1]]['color'] == 'red':
            g.nodes[x[1]]['color'] = 'yellow'
        else:
            g.nodes[x[1]]['color'] = 'red'

    for n in g.nodes():
        if n in nodes_colored:
            continue
        g.nodes[n]['color'] = 'blue'
    i += 1

    node_colors = nx.get_node_attributes(g, 'color').values()
    pos = nx.get_node_attributes(g, 'pos')
    nx.draw(g, pos=pos ,font_color='white', edge_color=edge_colors, node_color=node_colors,
                         width=list(weights), node_size=10)
    fig.set_facecolor("#00000F")


# init Graph and plot
fig = plt.figure()
g = nx.Graph()

# open and read default nodes and edges
f = open("is_shortest_way", 'r')
for x in f:
    x = x.strip()
    if x[0] == '#' or x[0].isdigit():
         continue
    elif '-' in x:
        y = x.split('-')
        g.add_edge(y[0], y[1], color='yellow', weight=1)
    else:
        y = x.split(' ')
        g.add_node(y[0], pos=(int(y[1]), int(y[2])), color='blue')
f.close()

# open and read the found paths
f = open("paths", 'r')
for x in f:
    x = x.strip()
    y = x.split(' ')
    i = len(y) - 1
    j = 0
    while i:
        g.edges[y[j], y[j + 1]]['color'] = 'green'
        g.edges[y[j], y[j + 1]]['weight'] = 2
        i -= 1
        j += 1
f.close()

# get and update all attributes to graph
edge_colors = nx.get_edge_attributes(g, 'color').values()
node_colors = nx.get_node_attributes(g, 'color').values()
weights = nx.get_edge_attributes(g, 'weight').values()
pos = nx.get_node_attributes(g, 'pos')

# draw the first plot
nx.draw(g, pos=pos, edge_color=edge_colors, node_color=node_colors, width=list(weights), node_size=10)
fig.set_facecolor("#00000F")

# read data from moving ants
with open('send_ants_short') as f:
    lines = [line.rstrip() for line in f]
f.close()
length = len(lines)
i = 0

# animate moving ants
anim = matplotlib.animation.FuncAnimation(fig, update, frames=200, interval=100, repeat=True)

plt.show()
