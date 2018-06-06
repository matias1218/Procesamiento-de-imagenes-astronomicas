//-------------------------------------------DEFINICION DE ESTRUCTURAS----------------------------------------------//

/* Estas estructuras definen el header de la imagen con extension ".bmp"
   Su uso está restringido solo para imagenes de 32 bits. */  

typedef struct bmpFileHeader
{
  /* 2 bytes de identificación */
  uint32_t size;        /* Tamaño del archivo */
  uint16_t resv1;       /* Reservado */
  uint16_t resv2;       /* Reservado */
  uint32_t offset;      /* Offset hasta hasta los datos de imagen */
} bmpFileHeader;

typedef struct bmpInfoHeader
{
  uint32_t headersize;      /* Tamaño de la cabecera */
  uint32_t width;       /* Ancho */
  uint32_t height;      /* Alto */
  uint16_t planes;          /* Planos de color (Siempre 1) */
  uint16_t bpp;             /* bits por pixel */
  uint32_t compress;        /* compresión */
  uint32_t imgsize;     /* tamaño de los datos de imagen */
  uint32_t bpmx;        /* Resolución X en bits por metro */
  uint32_t bpmy;        /* Resolución Y en bits por metro */
  uint32_t colors;      /* colors used en la paleta */
  uint32_t imxtcolors;      /* Colores importantes. 0 si son todos */
  uint32_t v1;      /* Colores importantes. 0 si son todos */
  uint32_t v2;      /* Colores importantes. 0 si son todos */
  uint32_t v3;      /* Colores importantes. 0 si son todos */
  uint32_t v4;      /* Colores importantes. 0 si son todos */
  uint32_t v5;      /* Colores importantes. 0 si son todos */
  uint32_t v6;      /* Colores importantes. 0 si son todos */
  uint32_t v7;      /* Colores importantes. 0 si son todos */
  uint32_t v8;      /* Colores importantes. 0 si son todos */
  uint32_t v9;      /* Colores importantes. 0 si son todos */
  uint32_t v10;      /* Colores importantes. 0 si son todos */
  uint32_t v11;      /* Colores importantes. 0 si son todos */
  uint32_t v12;      /* Colores importantes. 0 si son todos */
  uint32_t v13;      /* Colores importantes. 0 si son todos */
  uint32_t v14;      /* Colores importantes. 0 si son todos */
  uint32_t v15;      /* Colores importantes. 0 si son todos */
  uint32_t v16;      /* Colores importantes. 0 si son todos */
  uint32_t v17;      /* Colores importantes. 0 si son todos */
  uint32_t v18;      /* Colores importantes. 0 si son todos */
  uint32_t v19;      /* Colores importantes. 0 si son todos */
  uint32_t v20;      /* Colores importantes. 0 si son todos */
  uint32_t v21;      /* Colores importantes. 0 si son todos */     
} bmpInfoHeader;



//------------------------------------------DECLARACION DE FUNCIONES----------------------------------------------//

void *readRGB();
void *convertToGray();
void *convertToBinary();
void *isNearlyBlackOrNot();
void writes(FILE* file,unsigned char* img,bmpInfoHeader* bInfoHeader, bmpFileHeader* bmpFile);

//----------------------------------------------------------------------------------------------------------------//
