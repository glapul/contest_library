"""
Polygon drawer
"""
import matplotlib.path as mpath
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt


ax = plt.subplot()


vertices = [(0,0),(0,1),(1,1),(1,0)]
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


draw_poly(vertices)
draw_poly([(1,2), (2,1), (0,0)], 'r^--')
ax.grid()
ax.axis('equal')
plt.show()
