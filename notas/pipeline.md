# Pipeline de renderizado

Es una serie de pasos para que los datos atraviesan para mostrarse en pantalla

### Etapas

* Shader de vertices: La información se alamacena en un arreglo y se convierte en un shader. Se aplica transformaciones de coordenadas y de iluminación

* Ensamblado de vertices en primitivas. Saber como los vertices se conectan unos con otros

* Rasterizacion: Cada primitiva se convierte en fragmentos (pixeles). 

* Shader de fragmentos: Cada pixel se procesa para aplicar su color final

* Los fragmentos procesados se combinan con el framebuffer

**SHADER** : Programa que se ejecuta en la GPU para realizar calculos y operaciones de forma iterativa durante el proceso de renderizado. Algunos de los calculos que hace es el caluclo de color,texturas, el brillo o la posicion de cada pixel y/o vertice