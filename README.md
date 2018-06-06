
# Manual de Usuario

Este manual explica de manera breve el uso del programa.

####  Compilación
Para compilar el programa, basta con abrir una terminal sea en Linux o Windows dentro de la carpeta donde se encuentra el archivo de programa y ejecutar el comando:

###### Linux:

	$ make    
 
#### Ejecución
Para ejecutar el programa, basta con ejecutar por consola el siguiente comando:

	 $ ./pipeline -c A -h B -u C -n D -b 

Parametro  | Valor
------------- | -------------
A  | Cantidad de imagenes
B  | Cantidad de Hebras
C  | Umbral en valor pixel
D  | Umbral porcentaje de negro

El valor -b puede ser omitido si no se requiere la visualización de resultados por pantalla.

### Consideraciones Generales
El programa procesará imagenes solo si estas poseen el nombre:
> imagen_N.bmp 

donde  N especifica el valor numérico de la imagen (1..n).
La secuencialidad de la lectura de multiples imagenes dependerá de que se siga este orden para cada imagen.

Ejemplo:
> imagen_1.bmp
imagen_2.bmp
imagen_3.bmp
.
.
.
imagen_N.bmp

