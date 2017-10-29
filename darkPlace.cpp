#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define IZQUIERDA 75
#define DERECHA 77
#define ESPACIO 32
#define REINICIAR 114

char avion_11[] = {' ', ' ', ' ', 219 , ' ', ' ', ' ', 0};
char avion_12[] = {' ', '|', 220, '*', 220, '|', ' ', 0};
char avion_13[] = {220 , '*', ' ', '*', ' ', '*', 220, 0};

char explocion_l1[] = {' ',' ','*','*',' ',' ',' ',0};
char explocion_l2[] = {' ','*','*','*','*',' ',' ',0};
char explocion_l3[] = {' ',' ','*','*',' ',' ',' ',0};

char explocion_r1[] = {'*',' ','*','*',' ','*',' ',0};
char explocion_r2[] = {' ','*','*','*','*',' ',' ',0};
char explocion_r3[] = {'*',' ','*','*',' ','*',' ',0};

char borrar_avion[]={' ',' ',' ',' ',' ',' ',' ',0};

int num_vidas = 3;   // variables de la nave
int corazones = 3;
int ix = 40;
int iy = 19;

int y = 8, x = 12;    // variables de asteroides
int yy = 17, xx = 12;
int x1 = 58, y1 = 6;
int x2 = 70, y2 = 9;

int i, v;

int dd = 0;
bool disparo = false;
int sco = 0;
bool game = false;

// variables para rutina de cambio de nivel
int repeticion = 0, nivel = 1;
bool condicion = false;
int xb;

void gotoxy(int x, int y)  // funcion que posiciona el cursos en la coordenada (x,y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void vidas(int vi)
{
    gotoxy(2,1); printf("VIDAS %d", vi );   // imprimmir en un lugar de la pantalla
}

void barraSalud(int n)
{
   gotoxy(72,1); printf(" ");
   gotoxy(73,1); printf(" ");
   gotoxy(74,1); printf(" ");

   for(v = 0 ; v < n ; v++)
   {
     gotoxy(72+v,1);
     printf("%c", 3 );
   }
}

void explocion()
{
  gotoxy(ix, iy); puts(explocion_l1);
  gotoxy(ix, iy+1); puts(explocion_l2);
  gotoxy(ix, iy+2); puts(explocion_l3);

  Sleep(380);

  gotoxy(ix, iy); puts(explocion_r1);
  gotoxy(ix, iy+1); puts(explocion_r2);
  gotoxy(ix, iy+2); puts(explocion_r3);

  Sleep(380);

  gotoxy(ix, iy); puts(avion_11);
  gotoxy(ix, iy+1); puts(avion_12);
  gotoxy(ix, iy+2); puts(avion_13);
}

void jugar(void) // rutina de los asteroides
{
  if(!disparo) xb = ix;

  gotoxy( xb + 3, iy + dd ); printf("%c", 219);

  gotoxy(x,y);   printf("%c", 2 );
  gotoxy(xx,yy); printf("%c", 2 );
  gotoxy(x1,y1); printf("%c", 2 );
  gotoxy(x2,y2); printf("%c", 2 );

  Sleep(70);

  gotoxy(x,y);   printf(" ");
  gotoxy(xx,yy); printf(" ");
  gotoxy(x1,y1); printf(" ");
  gotoxy(x2,y2); printf(" ");

  gotoxy( xb + 3, iy + dd ); printf(" ");

  if( disparo == true) dd--;
  if( iy + dd < 5 )
  {
    dd = 0;
    disparo = false;
  }

  if (y > 20 || x == xb + 3 && iy + dd <= y )  //rutina asteroides
  {
    y = 4;
    x = (rand() % 70) + 6;
    sco++;
    gotoxy (2,2);    printf("score: %i", sco);


    if ( y == 4) {
      condicion = false;
    }
  }

  if (yy > 20 || xx == xb + 3 && iy + dd <= yy)
  {
    yy = 4;
    xx = (rand() % 70) + 6;
     sco++;
     gotoxy (2,2);    printf("score: %i", sco);

  }

  if (y1 > 20 || x1 == xb + 3 && iy + dd <= y1)
  {
    y1 = 4;
    x1 = (rand() % 70) + 6;
     sco++;
     gotoxy (2,2);    printf("score: %i", sco);

  }

  if (y2 > 20 || x2 == xb + 3 && iy + dd <= y2 )
  {
    y2 = 4;
    x2 = (rand() % 70) + 6;
     sco++;
     gotoxy (2,2);    printf("score: %i", sco);

  }

  if(kbhit())
{

  unsigned char tecla = getch();

  switch (tecla)
   {
    case IZQUIERDA:

        if ( x > 4 )
        {
          gotoxy(ix, iy); puts(borrar_avion);
          gotoxy(ix, iy+1); puts(borrar_avion);
          gotoxy(ix, iy+2); puts(borrar_avion);

          ix -= 2;

          gotoxy(ix, iy); puts(avion_11);
          gotoxy(ix, iy+1); puts(avion_12);
          gotoxy(ix, iy+2); puts(avion_13);
        }
        break;

    case DERECHA :

        if ( ix < 70)
        {
          gotoxy(ix, iy); puts(borrar_avion);
          gotoxy(ix, iy+1); puts(borrar_avion);
          gotoxy(ix, iy+2); puts(borrar_avion);

          ix += 2;

          gotoxy(ix, iy); puts(avion_11);
          gotoxy(ix, iy+1); puts(avion_12);
          gotoxy(ix, iy+2); puts(avion_13);
        }
        break;

    case ESPACIO:
          disparo = true;
        break;

    case REINICIAR:
        if( num_vidas == 0 )
        {
            num_vidas = 3;
            game = true;
        }

      } //fin del swich
  }// fin del if

  //rutina para golpes de asteroides

  if( (x > ix  && x < ix + 6 && y == iy - 1) || (xx > ix  && xx < ix + 6 && yy == iy - 1) || (x1 > ix  && x1 < ix + 6 && y1 == iy - 1) || (x2 > ix  && x2 < ix + 6 && y2 == iy - 1))
  {
    corazones --;
    barraSalud(corazones);
    printf("\a");

  }

  gotoxy(ix, iy); puts(avion_11);
  gotoxy(ix, iy+1); puts(avion_12);
  gotoxy(ix, iy+2); puts(avion_13);

  if (!corazones)
  {
    num_vidas--;
    vidas(num_vidas);
    explocion();
    corazones = 3;
    barraSalud(corazones);
  }

  if (!condicion)
  {
    repeticion ++;
    condicion = true;
  }
  if ( repeticion == 18 )
   {
     nivel++;
     gotoxy( 35 , 1 ); printf("NIVEL %i", nivel );

     gotoxy(ix, iy); puts(borrar_avion);
     gotoxy(ix, iy + 1); puts(borrar_avion);
     gotoxy(ix, iy + 2); puts(borrar_avion);

     iy -= 2;

     gotoxy(ix, iy); puts(avion_11);
     gotoxy(ix, iy + 1); puts(avion_12);
     gotoxy(ix, iy + 2); puts(avion_13);

     repeticion = 0;

  }
  y++; yy++; y1++; y2++;
}

void pintar_marco()       // funcion que pinta los limites del escenario
{
     // Lineas horizontals
     for(int i=2; i < 78; i++){
        gotoxy (i, 3); printf ("%c", 205);
        gotoxy(i, 23); printf ("%c", 205);
     }
     //Lineas verticales
     for(int v=4; v < 23; v++){
        gotoxy (2,v);  printf ("%c", 186);
        gotoxy(77,v);  printf ("%c", 186);
     }
     // Esquinas
     gotoxy  (2,3);    printf ("%c", 201);
     gotoxy (2,23);    printf ("%c", 200);
     gotoxy (77,3);    printf ("%c", 187);
     gotoxy(77,23);    printf ("%c", 188);
}

int main()
{
  vidas(num_vidas);
  barraSalud(corazones);
  gotoxy( 35 , 1 ); printf("NIVEL %i", nivel );
  gotoxy (2,2);    printf("score: %i", sco);

  pintar_marco();

  gotoxy(ix, iy); puts(avion_11);
  gotoxy(ix, iy+1); puts(avion_12);
  gotoxy(ix, iy+2); puts(avion_13);

  while (num_vidas > 0 && nivel <= 6 || game == true)
  {
    jugar();
  }

  gotoxy( 35 , 15 ); printf("GAME OVER");

  Sleep(200);
  getch();
  return 0;
}
