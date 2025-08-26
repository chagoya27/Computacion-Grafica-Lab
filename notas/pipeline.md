# Pipeline de renderizado

Es una serie de pasos para que los datos atraviesan para mostrarse en pantalla 

### Etapas

1. Todo nace de un establecimiento de coordenadas locales. Colocamos el modelo.

2. Ubicamos el modelo en un sistema de coordenadas global.

3. Ubicamos la camara sintetica. Coordenadas de la vista.

4. Sacamos la proyección. Transformamos de un entorno 3D a un entorno 2D. Se hace el cambio de base, cambio de espacios vectoriales. Se saca el sistema de coordenas de proyeccción. Hacemos normalización, ajustes de transformación and clipping (que tanto puedo ver).

5. Cambiamos a otro sistema de coordenadas. El sistema de coordenadas del dispositivo.

**PIVOTE DE UN OBJETO**: Lugar apartir del cual todas las operaciones se hacen apartir del pivote. 

**CÁMARA SINTÉTICA**: Para visualizar los objetos

**MODELO 3D**.: Visualización de datos en x,y,x

**RENDER**: Es el resultado del pipeline. Es el procesamiento de información de todo el renderizado


* Shader de vertices: La información se alamacena en un arreglo y se convierte en un shader. Se aplica transformaciones de coordenadas y de iluminación

* Ensamblado de vertices en primitivas. Saber como los vertices se conectan unos con otros

* Rasterizacion: Cada primitiva se convierte en fragmentos (pixeles). 

* Shader de fragmentos: Cada pixel se procesa , se manipula cad pixel para aplicar su color final

* Los fragmentos procesados se combinan con el framebuffer

**SHADER** : Programa que se ejecuta en la GPU para realizar calculos y operaciones de forma iterativa durante el proceso de renderizado. Es para conectar lo que pasa en la CPU con lo que pasa en la GPU.
Algunos de los calculos que hace es el caluclo de color,texturas, el brillo o la posicion de cada pixel y/o vertice