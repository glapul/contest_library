"""
Polygon drawer
"""
import matplotlib.path as mpath
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt



def read_polygon():
    xs = []
    ys = []
    n = int(raw_input())
    for i in range(n):
        x, y = (float(i) for i in raw_input().split())
        xs.append(x)
        ys.append(y)
    return zip(xs, ys)


ax = plt.subplot()
def draw_poly(vertices, line_style = 'go-'):
    global ax
    if len(vertices) < 1:
        return
    path_data = [ (mpath.Path.MOVETO, vertices[0])]
    for i in vertices[1:]:
        path_data.append( (mpath.Path.LINETO, i))
    path_data.append((mpath.Path.CLOSEPOLY, vertices[0]))
    codes, verts = zip(*path_data)
    path = mpath.Path(verts, codes)
    x, y = zip(*path.vertices)
    line, = ax.plot(x, y, line_style)
###############################################################################
# your code goes here
poly = read_polygon()
# point = read_polygon()
# point2 = read_polygon()
# point3 = read_polygon()
draw_poly(poly)
# draw_poly(point, 'rs-')
# draw_poly(point2, 'bo-')
# draw_poly(point3, 'bo-')

# stahp
###############################################################################

ax.grid()
ax.axis('equal')
plt.show()
