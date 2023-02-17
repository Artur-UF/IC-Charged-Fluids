import imageio
import imageio.v3 as iio
from pathlib import Path
import os
from pygifsicle import optimize

paths = list()

images = list()


# Caminho da pasta com os frames
path0 = '/home/arturuf/videoic'

for file in Path(path0).iterdir():
	paths.append(file)

paths.sort()

for file in paths:    
    if not file.is_file():
        continue
    images.append(iio.imread(file))


# Caminho para o gif a ser criado
path1 = os.path.join(os.getcwd(), f'movie-ic-LB7-TF30.gif')

# Aqui vc pode escolher o fps
imageio.mimsave(path1, images, 'GIF', fps=60)

optimize(path1)

