//-----------------------------------------------DECLARACION DE VARIABLES GLOBALES--------------------------------------------------//

bmpInfoHeader* info;
bmpFileHeader* header;
unsigned char *img;
unsigned char *gray;
unsigned char *bin;
FILE *file;
pthread_barrier_t barrier; // variable de barrera pthread
pthread_mutex_t llave; // variable de mutext pthread
int value_init;
int value_finish;
int pixel;
int contador;
int acumWidth;
int cantThread;
int rowXthread;
int acumThread;
int ThreadNumber;
int flagLastThread;
int binaryUmbral;
int nearlyBlackUmbral;
int flag1;
int cantOnes;
int cantZeros;

//-----------------------------------------------DEFINICION DE FUNCIONES------------------------------------------------------------//


/*  Funcion que escribe en disco una imagen con extensión ".bmp" de 32 bits. Para este caso, la imagen binarizada
    ENTRADAS: - Una lista enlazada para guardar la informacion de la imagen.
              - El archivo de salida.
              - La informacion de los pixeles de una imagen.
              - La cabecera de informacion de la imagen.
              - La cabecera del fichero de la imagen procesada.
    SALIDA:   - Salida vacía.
*/
void writes(FILE* out,unsigned char* img,bmpInfoHeader* bInfoHeader, bmpFileHeader* bmpFile){

  // se asigna el valor predeterminado para archivos con extension ".bmp"
  uint16_t type = 0x4D42; 
  fwrite(&type,sizeof(uint16_t),1,out);

  // Se lee la cabecera de fichero completa
  fwrite(bmpFile, sizeof(bmpFileHeader), 1, out);

  // se lee la cabecera de información completa
  fwrite(bInfoHeader, sizeof(bmpInfoHeader), 1, out);

  // escritura de la informacion de la imagen
  fwrite(img,bInfoHeader->imgsize, 1, out);
  fclose(out);
}

/*  Funcion que analiza y concluye si una imagen es "cercana a negro". 
    ENTRADAS: - Una lista enlazada para guardar la informacion de la imagen.
              - El nombre del archivo de entrada.
              - La informacion de los pixeles de una imagen.
              - La cabecera de informacion de la imagen.
              - El valor en porcentaje a comparar de pixeles negros en una imagen.
              - Una bandera que indica si la informacion de la clasificacion de la imagen se muestra o no en pantalla.
    SALIDA:   - Salida vacia.
*/
void *isNearlyBlackOrNot(){

  /* bloqueo la entrada de las hebras para que cada una manipule cierta parte de la imagen y escriba 
      la nueva imagen griseada */
    // bloqueo la entrada de las hebras para que cada una manipule cierta parte de la imagen y escriba 
    // la nueva imagen griseada
    pthread_mutex_lock(&llave);
    
    // se asigna cierta cantidad de filas de la imagen a las hebras asi repartiendo la carga para cada una.
    // NOTA: En caso de que no se pueda distribuir equitativamente la carga para cada hebra, la ultima hebra 
    // deberá terminar el griseo de la imagen con las filas que sobraron
    while(acumThread < rowXthread && flagLastThread == 0){
      // se recorre por cada fila de la matriz de la imagen
      // pixel es el valor actual de la casilla, y acumWidth es el valor maximo de la casilla en fila
      // Ej: primera fila ->  desde pixel = 0 hasta acumWidth = 512 en caso de imagen de 512x512
      // La otra condicion es para que no se ejecute el proceso si la cantidad de hebras excede a la cantidad
      // de filas de la matriz. Esto quiere decir que si la variable pixel es igual a imgsize/4 no se ejecuta
      int y;
      while(pixel<acumWidth && pixel<info->imgsize/4){
          if(bin[contador] == 255){
            cantOnes++;
          }
          else{
            cantZeros++;
          }
          contador+=4;
          pixel++;
      }
      acumWidth = acumWidth + info->width;
      acumThread++;
      if(ThreadNumber == cantThread){
        flagLastThread = 1;
      }
      if(acumWidth == info->imgsize/4){
        flagLastThread = 0;
      }
    }
    ThreadNumber++;
    acumThread = 0;

    pthread_mutex_unlock(&llave);

}

/*  Funcion que convierte una imagen a su modo binario. 
    ENTRADAS: - La informacion de los pixeles de una imagen.
              - La cabecera de informacion de la imagen.
              - El umbral en valor pixel, el cual define cuales pixeles deben ser transformados a blanco o negro.
    SALIDA:   - La informacion de la imagen (pixeles) binarizada.
*/
void *convertToBinary(){

    /* bloqueo la entrada de las hebras para que cada una manipule cierta parte de la imagen y escriba 
      la nueva imagen griseada */
    // bloqueo la entrada de las hebras para que cada una manipule cierta parte de la imagen y escriba 
    // la nueva imagen griseada
    pthread_mutex_lock(&llave);
    
    // se asigna cierta cantidad de filas de la imagen a las hebras asi repartiendo la carga para cada una.
    // NOTA: En caso de que no se pueda distribuir equitativamente la carga para cada hebra, la ultima hebra 
    // deberá terminar el griseo de la imagen con las filas que sobraron
    while(acumThread < rowXthread && flagLastThread == 0){
      // se recorre por cada fila de la matriz de la imagen
      // pixel es el valor actual de la casilla, y acumWidth es el valor maximo de la casilla en fila
      // Ej: primera fila ->  desde pixel = 0 hasta acumWidth = 512 en caso de imagen de 512x512
      // La otra condicion es para que no se ejecute el proceso si la cantidad de hebras excede a la cantidad
      // de filas de la matriz. Esto quiere decir que si la variable pixel es igual a imgsize/4 no se ejecuta
      int y;
      while(pixel<acumWidth && pixel<info->imgsize/4){
          if(gray[contador] > binaryUmbral){
            bin[contador] = 255;
            bin[contador+1] = 255;
            bin[contador+2] = 255;
            bin[contador+3] = 255;
          }
          else{
            bin[contador] = 0;
            bin[contador+1] = 0;
            bin[contador+2] = 0;
            bin[contador+3] = 255;
          }
          contador+=4;
          pixel++;
      }
      acumWidth = acumWidth + info->width;
      acumThread++;
      if(ThreadNumber == cantThread){
        flagLastThread = 1;
      }
      if(acumWidth == info->imgsize/4){
        flagLastThread = 0;
      }
    }
    ThreadNumber++;
    acumThread = 0;
    pthread_mutex_unlock(&llave);

    pthread_barrier_wait(&barrier);
    pixel = 0;
    contador = 0;
    acumWidth = info->width;
    rowXthread = info->height / cantThread; // esto va a truncar hacia abajo
    if(rowXthread == 0){
      rowXthread = 1;
    }
    acumThread = 0;
    flagLastThread = 0;
    ThreadNumber = 0;
    // se inicializan las variables de los contadores de pixeles negros y blancos
    cantOnes = 0;
    cantZeros = 0;
    pthread_barrier_wait(&barrier);
    isNearlyBlackOrNot();
    //pthread_barrier_wait(&barrier);

}

/*  Funcion que convierte una imagen en escala de grises. 
    ENTRADAS: - La informacion de los pixeles de una imagen.
              - La cabecera de informacion de la imagen.
    SALIDA:   - La informacion de la imagen (pixeles) transformada a escala de grises.
*/
void *convertToGray(){

  
    // bloqueo la entrada de las hebras para que cada una manipule cierta parte de la imagen y escriba 
    // la nueva imagen griseada
    pthread_mutex_lock(&llave);
    
    // se asigna cierta cantidad de filas de la imagen a las hebras asi repartiendo la carga para cada una.
    // NOTA: En caso de que no se pueda distribuir equitativamente la carga para cada hebra, la ultima hebra 
    // deberá terminar el griseo de la imagen con las filas que sobraron
    while(acumThread < rowXthread && flagLastThread == 0){
      // se recorre por cada fila de la matriz de la imagen
      // pixel es el valor actual de la casilla, y acumWidth es el valor maximo de la casilla en fila
      // Ej: primera fila ->  desde pixel = 0 hasta acumWidth = 512 en caso de imagen de 512x512
      // La otra condicion es para que no se ejecute el proceso si la cantidad de hebras excede a la cantidad
      // de filas de la matriz. Esto quiere decir que si la variable pixel es igual a imgsize/4 no se ejecuta
      int y;
      while(pixel<acumWidth && pixel<info->imgsize/4){
          y = img[contador+2]*0.3+img[contador+1]*0.59+img[contador]*0.11;
          gray[contador] = y;
          gray[contador+1] = y;
          gray[contador+2] = y;
          gray[contador+3] = 255;
          contador+=4;
          pixel++;
      }
      acumWidth = acumWidth + info->width;
      acumThread++;
      if(ThreadNumber == cantThread){
        flagLastThread = 1;
      }
      if(acumWidth == info->imgsize/4){
        flagLastThread = 0;
      }
    }
    ThreadNumber++;
    acumThread = 0;

    // se desbloquea la seccion critica
    pthread_mutex_unlock(&llave);
    
    pthread_barrier_wait(&barrier);
    pixel = 0;
    contador = 0;
    acumWidth = info->width;
    rowXthread = info->height / cantThread; // esto va a truncar hacia abajo
    if(rowXthread == 0){
      rowXthread = 1;
    }
    acumThread = 0;
    flagLastThread = 0;
    ThreadNumber = 0;
    pthread_barrier_wait(&barrier);
    convertToBinary();

    
    //sleep(1);



}

/*  Funcion que lee un archivo de imagen y extrae la informacion de los pixeles para poder ser manipulados. 
    ENTRADAS: - Un archivo de tipo ".bmp".
              - La cabecera de informacion de la imagen.
              - La cabecera del fichero de la imagen procesada.
    SALIDA:   - La informacion de la imagen de un archivo de imagen ".bmp".
*/
//unsigned char *readRGB(FILE* file, bmpInfoHeader* bInfoHeader,bmpFileHeader* header)
void *readRGB(void *flag){
    int numero = *((int *)flag);
    //printf("hilo con numero = %d\n",numero );
    // ejecucion para 1 sola hebra
    if(numero == 1){
      
      //bmpFileHeader header;     /* cabecera */
      //unsigned char *imgdata;   /* datos de imagen */
      uint16_t type;        /* 2 bytes identificativos */


       /* Leemos los dos primeros bytes */
      fread(&type, sizeof(uint16_t), 1, file);
      if (type !=0x4D42){        /* Comprobamos el formato */
          fclose(file);
          return NULL;
      }

      /* Leemos la cabecera de fichero completa */
      fread(header, sizeof(bmpFileHeader), 1, file);

      /* Leemos la cabecera de información completa */
      fread(info, sizeof(bmpInfoHeader), 1, file);

      /* Reservamos memoria para las imagenes, ¿cuánta?
       Tanto como indique imgsize */
      img=(unsigned char*)malloc(info->imgsize);
      gray=(unsigned char*)malloc(info->imgsize);
      bin=(unsigned char*)malloc(info->imgsize);
      /* Nos situamos en el sitio donde empiezan los datos de imagen,
      nos lo indica el offset de la cabecera de fichero*/
      fseek(file, header->offset, SEEK_SET);

      /* Leemos los datos de imagen, tantos bytes como imgsize */
      fread(img, info->imgsize,1, file);
  
      fclose(file);
      
    }
    /* antes de terminar la funcion, se realiza una asignacion de variables globales,
       las cuales iran cambiando para cada hebra a medida que cada una de estas ejecute
       su tarea particular. Es por esto que se sincronizan todas antes de entrar a la siguiente función */
    pixel = 0;
    contador = 0;
    acumWidth = info->width;
    rowXthread = info->height / cantThread; // esto va a truncar hacia abajo
    if(rowXthread == 0){
      rowXthread = 1;
    }
    acumThread = 0;
    flagLastThread = 0;
    ThreadNumber = 0;
    pthread_barrier_wait(&barrier);
    convertToGray();
}

//-----------------------------------------------------------------------------------------------------------------------------------------//
