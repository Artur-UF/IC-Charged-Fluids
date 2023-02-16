import imageio
import imageio.v3 as iio
from pathlib import Path
import os

images = list()

path0 = '/home/arturuf/Documentos/video-ic'

for file in Path(path0).iterdir():
    if not file.is_file():
        continue
    images.append(iio.imread(file))

path1 = os.path.join(os.getcwd(), f'movie-ic.gif')

'''
with imageio.get_writer(path1, mode='I') as writer:
    for filename in images:
        image = imageio.imread(filename)
        writer.append_data(image)
'''

imageio.mimsave(path1, images, fps=24)
