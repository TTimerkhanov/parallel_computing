import numpy as np
import matplotlib.pyplot as plt


def mandelbrot(threshold, density):
    atlas = np.empty((density, density))

    with open('set', 'r') as f:
        for line in f.readlines():
            i, j, val = line.split(",")
            atlas[int(i), int(j)] = val

    plt.imshow(atlas.T, interpolation="nearest")
    plt.show()

mandelbrot(120, 6000)