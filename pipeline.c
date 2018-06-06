//------------------------------------------IMPORTACION DE LIBRERIAS----------------------------------------------//

#include "library.h"

//--------------------------------------------------MAIN----------------------------------------------------------//

/*  La funcion main realiza la lectura-escritura de N imagenes, las cuales son procesadas para poder determinar si son cercanas
    a ser totalmente negras "nearly black". Los parametros de entrada son especificados a continuacion:
    ENTRADAS DEL PROGRAMA:   - *Los archivos de Imagenes con extension ".bmp" de 32 bits.
                             - **Cantidad de imagenes a procesar.
                             - El umbral en valor pixel al cual la imagen será binarizada (0 - 255).
                             - El porcentaje de comparacion de pixeles negros para una imagen (0% - 100%).
                             - Una bandera que indica si los resultados son visualizados por pantalla.
    SALIDAS DEL PROGRAMA:    - Las imagenes binarizadas respectivas de cada imagen procesada.
                             - La respectiva clasificación de las imagenes (Si es nearly black).

    *El programa procesará imagenes solo si estas poseen el nombre "imagen_N.bmp", donde N especifica el numero de la imagen (1..n).
    La secuencialidad de la lectura de multiples imagenes dependerá de que se siga este orden.

    **EL programa puede procesar N imagenes, siempre y cuando estas existan. Si no existen, el programa se cerrará en el ultimo valor
    procesado correctamente  
*/                          


int main(int argc, char  *argv[]){

  system("clear");


	int umbral = 100;
	int rate = 60;

	char param;
	char *cantImages1 = NULL;
  char *cantThread1 = NULL;
	char *binaryUmbral1 = NULL;
	char *nearlyBlackUmbral1 = NULL;
	flag1 = 0;
  int cantImages;
  

  // ------------------------------ Bloque de GETOPT() --------------------------------------//

	/**El bucle se realiza mientras el resultado sea -1, ya que este es el valor que se retorna cuando ya se han leído todos los parámetros.
	 *Los parámetros de la función getopt() son los siguientes:
	 *Primer parámetro: Cantidad de parámetros ingresados por la consola. Viene dado por el valor del parámetro argc del main.
	 *Segundo parámetro: Son los valores de los parámetros (en forma de Strings) ingresados por la consola. Viene dado por el parámetro argv del main.
	 *Tercer parámetro: Es el formato de lectura de parámetros considerado en la consola. Para este ejemplo se usan tres parámetros, los cuales son
	  c, u, n y b los cuales son separados por dos puntos (:) indicando que cada uno debe tener un valor al ingresarlos por consola.
	 *Se debe considerar que el valor que toma la variable optarg (la cual viene incluída por defecto en la librería unistd.h) es el valor
	 que tiene cada parámetro ingresado por consola, por lo que al recorrer estos parámetros, tomarán respectivamente los valores dados para
	 c, u, n y b.
	*/
	while((param = getopt(argc, argv, "c:h:u:n:b")) != -1){
		switch(param){
			case 'c':
        if(atoi(optarg) == 0){
          printf("FORMAT ERROR IN -c ARGUMENT\n");
          exit(1);
        }
        else{
          cantImages1 = optarg;
        }
				break;
      case 'h':
        if(atoi(optarg) == 0){
          printf("FORMAT ERROR IN -h ARGUMENT\n");
          exit(1);
        }
        else{
          cantThread1 = optarg;
        }
        break;
			case 'u':
        if(atoi(optarg) == 0){
          printf("FORMAT ERROR IN -u ARGUMENT\n");
          exit(1);
        }
        else{
          binaryUmbral1 = optarg;
        }
				break;
			case 'n':
        if(atoi(optarg) == 0){
          printf("FORMAT ERROR IN -n ARGUMENT\n");
          exit(1);
        }
        else{
          nearlyBlackUmbral1  = optarg;
        }	
				break;
			case 'b':
				flag1 = 1;
				break;
			
		}
	}

  //------------------------------ Bloque de verificacion de entradas -----------------------//

  if(cantImages1 == NULL){
    printf("NOT VALUE IN -c ARGUMENT\n");
    exit(1);
  }
  else{
    if(cantThread1 == NULL){
      printf("NOT VALUE IN -h ARGUMENT\n");
      exit(1);
    }
    else{
      if(binaryUmbral1 == NULL){
        printf("NOT VALUE IN -u ARGUMENT\n");
        exit(1);
      }
      else{
        if(nearlyBlackUmbral1 == NULL){
          printf("NOT VALUE IN -n ARGUMENT\n");
          exit(1);
        }
        else{
          cantImages= atoi(cantImages1);
          cantThread= atoi(cantThread1);
          binaryUmbral= atoi(binaryUmbral1);
          nearlyBlackUmbral= atoi(nearlyBlackUmbral1);
          if(cantImages < 0){
            printf("INVALID AMOUNT OF IMAGES\n");
            exit(1);
          }
          else{
            if(cantImages < 0){
              printf("INVALID AMOUNT OF IMAGES\n");
              exit(1);
            }
            else{
              if(binaryUmbral < 0 || binaryUmbral > 255){
                printf("INVALID PIXEL VALUE\n");
                exit(1);
              }
              else{
                if(nearlyBlackUmbral < 0 || nearlyBlackUmbral > 100){
                  printf("INVALID RATIO VALUE\n");
                  exit(1);
                }
              }
            }
          }
        }
      }
    }
  }
  //---------------------------------------------------------------------------------------//


  int imageNumber = 1;
  const char *nameIn = "imagen_";
  const char *nameOut = "salida_";
  char bufIn[32] = { 0 };
  char bufOut[32] = { 0 };

  // Inicio de muestreo por pantalla: si la flag de mostrar datos por pantala está activado, se muestra la cabecera de la clasificacion:

  if(flag1 == 1){
    printf("|        image        |    nearly black    |\n");
    printf("|---------------------|--------------------|\n");
    // -----o------- 
  }

  // ------------------------------- Bloque de PIPELINE------------------------------//

  /* El flujo de procesamiento de las imagenes esta basado en la cantidad de imagenes
     disponibles. Para cada imagenen, se realiza una serie de procesos, los cuales 
     corresponden a las etapas del ciclo. Estas etaps son:
     - Lectura de imagen
     - Conversion a escala de grises
     - Conversion a Binario
     - Clasificacion de Imagen
     - Escritura en disco
  */

  while(imageNumber<=cantImages){
      
    sprintf(bufIn, "%s%d.bmp", nameIn, imageNumber);
    sprintf(bufOut, "%s%d.bmp", nameOut, imageNumber);

    FILE *save;
    file = fopen(bufIn, "rb");
    save = fopen(bufOut, "wb");

    if (file == NULL) {   //se condiciona una bifurcacion para algun tipo de error de apertura de los archivos
      printf("c %s \n",bufIn);
      printf("IMAGE NOT FOUND\n");
      printf("Aborting...\n",bufIn);
      exit (1);
    }
    else{
      if(save == NULL){
          printf("FAILED INITIALIZATION OF OUT FILE %s \n",bufOut);
          exit (1);
      }else{
        // ------------ Inicio de ciclo ------------

        header = (bmpFileHeader*)malloc(sizeof(bmpFileHeader));
        info = (bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));

        // se inicializan los hilos
        pthread_t hilos[cantThread];
        // se inicializa la barrera de hilos
        pthread_barrier_init(&barrier,NULL,cantThread);
        pthread_mutex_init(&llave,NULL);

        int i = 0;
        while(i < cantThread){

          if(i == 0){
            // crear primer hilo
            int *arg = malloc(sizeof(*arg));
            *arg = 1;
            pthread_create(&hilos[0],NULL,readRGB,arg);
            i++;
          }
          else{
            // se crea el resto de los hilos
            int *arg = malloc(sizeof(*arg));
            *arg = 0;
            pthread_create(&hilos[i],NULL,readRGB,arg);
            i++;
          }
        }
        /* se determina la proporcion de pixeles negros en la imagen binarizada.
           Se divide la cantidad de pixeles negros encontrados por la cantidad total de
           pixeles en la imagen. La division de imgSize en 4 representa la combinacion de RGBA 
           por cada pixel */ 

        /* se espera a la finalizacion de todas las hebras para poder proseguir al analisis y
           escritura de la imagen */
        imageNumber++;
        i = 0;
        while(i < cantThread){
          pthread_join(hilos[i],NULL);
          i++;
        }

        // --------------------- Analisis de resultados --------------------------------------

        int cantPIxels= info->imgsize/4;
        float zerosProportions = ((float)cantZeros/cantPIxels)*100; 
        if (zerosProportions >= nearlyBlackUmbral)
        {
          if(flag1 == 1){
            printf("|   %14s    |        yes         |\n",bufIn );
          }
        }
        else{
          if(flag1 == 1){
            printf("|   %14s    |        no          |\n", bufIn);
          }
        }
 
        // ---------------------- Escritura de imagen ----------------------------------------
        writes(save,bin,info,header);
      }
    }
  }

  // -------------------------------------------------------------------------------------------//
	return 0;
}



