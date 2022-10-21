import sys

import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation
import time

color_baby_blue = '#95B9C7'
color_bright_blue = '#0909FF'
color_turq = '#48D1CC'
color_start_node = '#32CD32'
nodesize = 300

# The function to animate moving ants
def update(frame):
    if frame < 1:
        time.sleep(2)
    global colors, edge_colors, width, lines, length, i, pos, start, end, node_colors
    fig.clear()
    if i >= length:
        if kamada_kawai:
            nx.draw_kamada_kawai(g, font_color=color_baby_blue, edge_color=edge_colors, with_labels=labels,
                                 width=list(weights), node_size=nodesize, node_color=node_colors)
        else:
            nx.draw(g, pos=pos, font_color=color_baby_blue, edge_color=edge_colors, with_labels=labels,
                    width=list(weights), node_size=nodesize, node_color=node_colors)
        fig.set_facecolor("#00000F")
        return

    j = lines[i].split(' ')
    nodes_colored = []
    for x in j:
        x = x.split('-')
        nodes_colored.append(x[1])
        if g.nodes[x[1]]['color'] == 'orange':
            g.nodes[x[1]]['color'] = 'yellow'
        else:
            g.nodes[x[1]]['color'] = 'orange'

    for n in g.nodes():
        if n in nodes_colored:
            continue
        g.nodes[n]['color'] = color_bright_blue
    i += 1

    g.nodes[start]['color'] = color_bright_blue
    g.nodes[end]['color'] = color_bright_blue

    node_colors = nx.get_node_attributes(g, 'color').values()
    pos = nx.get_node_attributes(g, 'pos')
    if kamada_kawai:
        nx.draw_kamada_kawai(g, font_color='white', edge_color=edge_colors, node_color=node_colors,
                             width=list(weights), node_size=nodesize)
    else:
        nx.draw(g, pos=pos, font_color='white', edge_color=edge_colors, node_color=node_colors,
                width=list(weights), node_size=nodesize)

    fig.set_facecolor("#00000F")


# init Graph and plot
fig = plt.figure()
g = nx.Graph()

# variables initalization
kamada_kawai = True
speed = 1
big_map = False
labels = True

# read arguments
if '--coord' in sys.argv:
    kamada_kawai = False
if '--fast' in sys.argv:
    speed = 0.1
if '--slow' in sys.argv:
    speed = 10
if '--big' in sys.argv:
    labels = False
    nodesize = 3

x = input()
# skip number of ants
while len(x) != 0:
    if x[0].isdigit():
        break
    x = input()

#read default nodes and edges
x = input()
while len(x) != 0:
    x = x.strip()
    if x[0] == '#':
        x = input()
        continue
    elif x.count(' ') == 2:
        x = x.split(' ')
        g.add_node(x[0], pos=(int(x[1]), int(x[2])), color=color_bright_blue)
    else:
        x = x.split('-')
        g.add_edge(x[0], x[1], color=color_bright_blue, weight=1)    
    x = input()


#read the found paths
x = input()
while len(x) != 0:
    x = x.strip()
    x = x.split(' ')
    i = len(x)
    j = 0
    while i - 1:
        g.edges[x[j], x[j + 1]]['color'] = color_turq
        g.edges[x[j], x[j + 1]]['weight'] = 2
        i -= 1
        j += 1
    g.nodes[x[0]]['color'] = color_start_node
    g.nodes[x[-1]]['color'] = 'red'
    start = x[0]
    end = x[-1]
    x = input()

# get and update all attributes to graph
edge_colors = nx.get_edge_attributes(g, 'color').values()
node_colors = nx.get_node_attributes(g, 'color').values()
weights = nx.get_edge_attributes(g, 'weight').values()
pos = nx.get_node_attributes(g, 'pos')

# draw the first plot
if kamada_kawai:
    nx.draw_kamada_kawai(g, edge_color=edge_colors, node_color=node_colors, width=list(weights), node_size=nodesize)
else:
    nx.draw(g, pos=pos, edge_color=edge_colors, node_color=node_colors, width=list(weights), node_size=nodesize)

fig.set_facecolor("#00000F")

# read data from moving ants
x = input()
lines = []
while len(x) != 0:
    lines.append(x)
    x = input()

length = len(lines)
i = 0

# animate moving ants
anim = matplotlib.animation.FuncAnimation(fig, update, frames=200, interval=100*speed, repeat=True)

plt.show()
