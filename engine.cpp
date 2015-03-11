#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define WHITE   2
#define BLACK   1
#define NONE    0

#define PAWN			0
#define KNIGHT			1
#define BISHOP			2
#define ROOK			3
#define QUEEN			4
#define KING			5
#define EMPTY           6


typedef struct Tabla {
       int type;   
       int value; 
} Tabla;

  Tabla tabla[8][8];
  Tabla clona[8][8];


typedef struct King {
        int posx;
        int posy;
        int type;
} King;

King king;

typedef struct Rezultat {
        int x;
        int y;
} Rezultat;

typedef struct Piese {
        int x;
        int y;
        int type;
} Piese;

void initializare (Tabla tabla[8][8]) {
     //initializari pioni
      
  for (int j=0;j<8;j++) {
      tabla[1][j].value = PAWN;
      tabla[1][j].type = WHITE;
      
      tabla[6][j].value = PAWN;
      tabla[6][j].type = BLACK;
  }
   //initializari ture
   tabla[0][0].value = tabla[0][7].value = tabla[7][0].value = tabla[7][7].value = ROOK; 
   tabla[0][0].type = tabla[0][7].type = WHITE;
   tabla[7][0].type = tabla[7][7].type = BLACK;
   
   //initializari cai
   tabla[0][1].value = tabla[0][6].value = tabla[7][1].value = tabla[7][6].value = KNIGHT;
   tabla[0][1].type = tabla[0][6].type = WHITE;
   tabla[7][1].type = tabla[7][6].type = BLACK;
   
   //initializari nebuni
   tabla[0][2].value = tabla[0][5].value = tabla[7][2].value = tabla[7][5].value = BISHOP;
   tabla[0][2].type = tabla[0][5].type = WHITE;
   tabla[7][2].type = tabla[7][5].type = BLACK;
   
    //initializari regine
   tabla[0][3].value = tabla[7][3].value = QUEEN;
   tabla[0][3].type = WHITE;
   tabla[7][3].type = BLACK;
   
   //initializari regi
   tabla[0][4].value = tabla[7][4].value = KING;
   tabla[0][4].type = WHITE;
   tabla[7][4].type = BLACK;
   
   //initializari restul
   for (int i=2;i<6;i++)
       for (int j=0;j<8;j++) {
           tabla[i][j].value = EMPTY;
           tabla[i][j].type = NONE;
           }
}

int check_king() {
    int i=0,j=0;
 //verificare in stanga regelui
  for( i=king.posx-1; i>=0; i--)
  {
       if (tabla[king.posy][i].type == king.type || tabla[king.posy][i].value==PAWN || tabla[king.posy][i].value==KNIGHT || tabla[king.posy][i].value==BISHOP || tabla[king.posy][i].value==KING) break;
       if (tabla[king.posy][i].value == QUEEN || tabla[king.posy][i].value == ROOK ) return 1;
  }
  //verificare in dreapta regelui
  for( i=king.posx+1; i<=7; i++)
  {
       if (tabla[king.posy][i].type == king.type || tabla[king.posy][i].value==PAWN || tabla[king.posy][i].value==KNIGHT || tabla[king.posy][i].value==BISHOP || tabla[king.posy][i].value==KING) break;
       if (tabla[king.posy][i].value == QUEEN || tabla[king.posy][i].value == ROOK ) return 1;
  }  
  //verificare deasupra regelui
  for( i=king.posy+1; i<=7; i++)
  {
        if (tabla[i][king.posx].type == king.type || tabla[i][king.posx].value==PAWN || tabla[i][king.posx].value==KNIGHT || tabla[i][king.posx].value==BISHOP || tabla[i][king.posx].value==KING) break;
       if (tabla[i][king.posx].value == QUEEN || tabla[i][king.posx].value == ROOK ) return 1;
  }  
  //verificare sub rege
  for( i=king.posy-1; i>=0; i--)
  {
       if (tabla[i][king.posx].type == king.type || tabla[i][king.posx].value==PAWN || tabla[i][king.posx].value==KNIGHT || tabla[i][king.posx].value==BISHOP || tabla[i][king.posx].value==KING) break;
       if (tabla[i][king.posx].value == QUEEN || tabla[i][king.posx].value == ROOK ) return 1;
  }  
  //verificare diagonala dreapta sus
   for( i=king.posy+1,j=king.posx+1; i<=7,j<=7; i++,j++)
  {
       if (tabla[i][j].type == king.type || tabla[i][j].value==PAWN || tabla[i][j].value==KNIGHT || tabla[i][j].value==ROOK || tabla[i][j].value==KING) break;
       if (tabla[i][j].value == QUEEN || tabla[i][j].value == BISHOP ) return 1;
  } 
  if ( king.type == BLACK && king.posy-1>=0 && king.posx+1<=7 && tabla[king.posy-1][king.posx+1].value==PAWN && tabla[king.posy-1][king.posx+1].type==WHITE) return 1;
  
  //verificare diagonala stanga sus
   for( i=king.posy+1,j=king.posx-1; i<=7,j>=0; i++,j--)
  {
       if (tabla[i][j].type == king.type || tabla[i][j].value==PAWN || tabla[i][j].value==KNIGHT || tabla[i][j].value==ROOK || tabla[i][j].value==KING) break;
       if (tabla[i][j].value == QUEEN || tabla[i][j].value == BISHOP) return 1;
  } 
  if ( king.type == BLACK && king.posy-1>=0 && king.posx-1>=0 && tabla[king.posy-1][king.posx-1].value==PAWN && tabla[king.posy-1][king.posx-1].type==WHITE) return 1; 
  
  //verificare diagonala stanga jos
  for( i=king.posy-1,j=king.posx-1; i>=0,j>=0; i--,j--)
  {
       if (tabla[i][j].type == king.type || tabla[i][j].value==KNIGHT || tabla[i][j].value==ROOK || tabla[i][j].value==KING) break;
       if (tabla[i][j].value == QUEEN || tabla[i][j].value == BISHOP) return 1;
  } 
  if ( king.type == WHITE && king.posy+1<=7 && king.posx-1>=0 && tabla[king.posy+1][king.posx-1].value==PAWN && tabla[king.posy+1][king.posx-1].type==BLACK) return 1; 
  
  //verificare diagonala dreapta jos
  for( i=king.posy-1,j=king.posx+1; i>=0,j<=7; i--,j++)
  {
      if (tabla[i][j].type == king.type || tabla[i][j].value==KNIGHT || tabla[i][j].value==ROOK || tabla[i][j].value==KING) break;
      if (tabla[i][j].value == QUEEN || tabla[i][j].value == BISHOP) return 1;
  }  
  if ( king.type == WHITE && king.posy+1<=7 && king.posx+1<=7 && tabla[king.posy+1][king.posx+1].value==PAWN && tabla[king.posy+1][king.posx+1].type==BLACK) return 1;
  
  //verificare cai
  if (king.posy+2<=7 && king.posx+1<=7 && tabla[king.posy+2][king.posx+1].value == KNIGHT && tabla[king.posy+2][king.posx+1].type != king.type) return 1;
  if (king.posy+2<=7 && king.posx-1>=0 && tabla[king.posy+2][king.posx-1].value == KNIGHT && tabla[king.posy+2][king.posx-1].type != king.type) return 1;
  if (king.posy+1<=7 && king.posx-2>=0 && tabla[king.posy+1][king.posx-2].value == KNIGHT && tabla[king.posy+1][king.posx-2].type != king.type) return 1;
  if (king.posy+1<=7 && king.posx+2<=7 && tabla[king.posy+1][king.posx+2].value == KNIGHT && tabla[king.posy+1][king.posx+2].type != king.type) return 1;
  if (king.posy-1>=0 && king.posx-2>=0 && tabla[king.posy-1][king.posx-2].value == KNIGHT && tabla[king.posy-1][king.posx-2].type != king.type) return 1;
  if (king.posy-2>=0 && king.posx-1>=0 && tabla[king.posy-2][king.posx-1].value == KNIGHT && tabla[king.posy-2][king.posx-1].type != king.type) return 1;
  if (king.posy-1>=0 && king.posx+2<=7 && tabla[king.posy-1][king.posx+2].value == KNIGHT && tabla[king.posy-1][king.posx+2].type != king.type) return 1;
  if (king.posy-2>=0 && king.posx+1<=7 && tabla[king.posy-2][king.posx+1].value == KNIGHT && tabla[king.posy-2][king.posx+1].type != king.type) return 1;
  return 0;
}
//transforma coordonate de tip intreb in coordonate de tip char
char* transf(int coloana, int linie)
{
    static char s[2];

      if (coloana == 0 ) s[0]='a';
      if (coloana == 1 ) s[0]='b';
      if (coloana == 2 ) s[0]='c';
      if (coloana == 3 ) s[0]='d';
      if (coloana == 4 ) s[0]='e';
      if (coloana == 5 ) s[0]='f';
      if (coloana == 6 ) s[0]='g';
      if (coloana == 7 ) s[0]='h';
           
      if (linie == 0 ) s[1] = '1';     
      if (linie == 1 ) s[1] = '2';
      if (linie == 2 ) s[1] = '3';
      if (linie == 3 ) s[1] = '4';
      if (linie == 4 ) s[1] = '5';
      if (linie == 5 ) s[1] = '6';
      if (linie == 6 ) s[1] = '7';
      if (linie == 7 ) s[1] = '8';
     

     return s;
}

//transforma din coordonate de tip char in coordonate de tip intreg
int transforma(char coloana, char linie)
{
    int lin=0,col=0;

      if (coloana =='a' ) col = 0;
      if (coloana =='b' ) col = 1;
      if (coloana =='c' ) col = 2;
      if (coloana =='d' ) col = 3;
      if (coloana =='e' ) col = 4;
      if (coloana =='f' ) col = 5;
      if (coloana =='g' ) col = 6;
      if (coloana =='h' ) col = 7;
           
      if (linie =='1' ) lin = 0;
      if (linie =='2' ) lin = 1;
      if (linie =='3' ) lin = 2;
      if (linie =='4' ) lin = 3;
      if (linie =='5' ) lin = 4;
      if (linie =='6' ) lin = 5;
      if (linie =='7' ) lin = 6;
      if (linie =='8' ) lin = 7;   

     return lin*10 + col;
}
//functie ce realizeaza mutarea propriu-zisa a engine-ului
int miscare_engineSide(char *s, int stm)
{
	int linie=0, coloana =0,rez=0,linie1=0,coloana1=0,provval=0,provtype=0;
    char lin,col;
 
	if (s[0] < 'a' || s[0] > 'h' || s[1] < '0' || s[1] > '9' || s[2] < 'a' || s[2] > 'h' || s[3] < '0' || s[3] > '9') return -1;

    rez=transforma(s[2],s[3]);
    coloana = rez%10;
    linie = rez/10;

    rez=transforma(s[0],s[1]);
    coloana1 = rez%10;
    linie1 = rez/10;

    if ( tabla[linie][coloana].type == stm ) return 1;
    if ( tabla[linie1][coloana1].value == EMPTY || stm!=tabla[linie1][coloana1].type) return 2;
    if ( tabla[linie1][coloana1].value == KING && tabla[linie1][coloana1].type == king.type) {
         king.posx = coloana;
         king.posy = linie;
         }
    
    provval = tabla[linie][coloana].value;
    provtype = tabla[linie][coloana].type;
    
    tabla[linie][coloana].value =  tabla[linie1][coloana1].value;
    tabla[linie][coloana].type = tabla[linie1][coloana1].type;
    tabla[linie1][coloana1].value = EMPTY;
    tabla[linie1][coloana1].type = NONE;
    
    if ( check_king() != 0) {

          tabla[linie1][coloana1].value =  tabla[linie][coloana].value;
          tabla[linie1][coloana1].type = tabla[linie][coloana].type;
          if ( tabla[linie1][coloana1].value == KING && tabla[linie1][coloana1].type == king.type) {
             king.posx = coloana1;
             king.posy = linie1;
             }
          tabla[linie][coloana].value =  provval;
          tabla[linie][coloana].type = provtype;
          if ((( linie == 7 && stm==WHITE) || (linie ==0 && stm==BLACK)) && tabla[linie][coloana].type==PAWN)  tabla[linie][coloana].value = QUEEN;
                 
          return 3;
          }

    return 0;
       
}
//functie ce proceseaza miscarile facute de oponent
int miscare_oponent(char *s, int stm)
{
	int linie=0, coloana =0,rez=0,linie1=0,coloana1=0;
    char lin,col;
    
	if (s[0] < 'a' || s[0] > 'h' || s[1] < '0' || s[1] > '9' || s[2] < 'a' || s[2] > 'h' || s[3] < '0' || s[3] > '9') return -1;

    rez=transforma(s[2],s[3]);
    coloana = rez%10;
    linie = rez/10;

    rez=transforma(s[0],s[1]);
    coloana1 = rez%10;
    linie1 = rez/10;

    if ( tabla[linie][coloana].type == stm ) return -2;
    if ( tabla[linie1][coloana1].value == EMPTY || stm!=tabla[linie1][coloana1].type) return -2;
   //pentru rocada
    if ( stm==BLACK && linie1==7 && coloana1==4 && tabla[linie1][coloana1].value==KING && tabla[linie1][coloana1].type==BLACK && coloana==6 && tabla[7][7].value==ROOK && tabla[7][7].type==BLACK && tabla[7][6].value==EMPTY) {
         tabla[7][6].value = KING;
         tabla[7][6].type = BLACK;
         tabla[7][4].value = EMPTY;
         tabla[7][4].type = NONE;
         
         king.posx = 6;
         king.posy = 7;
         
         tabla[7][5].value = ROOK;
         tabla[7][5].type = BLACK;
         tabla[7][7].value = EMPTY;
         tabla[7][7].type = NONE;
         return 0;
         }
    if ( stm==BLACK && linie1==7 && coloana1==4 && tabla[linie][coloana].value==KING && tabla[linie1][coloana1].type==BLACK && coloana==2 && tabla[7][0].value==ROOK && tabla[7][0].type==BLACK && tabla[7][1].value==EMPTY && tabla[7][2].value==EMPTY && tabla[7][3].value==EMPTY) {
         tabla[7][2].value = KING;
         tabla[7][2].type = BLACK;
         tabla[7][4].value = EMPTY;
         tabla[7][4].type = NONE;
         
         king.posx = 2;
         king.posy = 7;
         
         tabla[7][3].value = ROOK;
         tabla[7][3].type = BLACK;
         tabla[7][0].value = EMPTY;
         tabla[7][0].type = NONE;
         return 0;
         }
         
    if ( stm==WHITE && linie1==0 && coloana1==4 && tabla[linie1][coloana1].value==KING && tabla[linie1][coloana1].type==WHITE && coloana==6 && tabla[0][7].value==ROOK && tabla[0][7].type==WHITE && tabla[0][6].value==EMPTY) {
         tabla[0][6].value = KING;
         tabla[0][6].type = WHITE;
         tabla[0][4].value = EMPTY;
         tabla[0][4].type = NONE;
         
         king.posx = 6;
         king.posy = 0;
         
         tabla[0][5].value = ROOK;
         tabla[0][5].type = WHITE;
         tabla[0][7].value = EMPTY;
         tabla[0][7].type = NONE;
         return 0;
         }
    if ( stm==WHITE && linie1==0 && coloana1==4 && tabla[linie1][coloana1].value==KING && tabla[linie1][coloana1].type==WHITE && coloana==2 && tabla[0][0].value==ROOK && tabla[0][0].type==WHITE && tabla[0][1].value==EMPTY && tabla[0][2].value==EMPTY && tabla[0][3].value==EMPTY) {
         tabla[0][2].value = KING;
         tabla[0][2].type = WHITE;
         tabla[0][4].value = EMPTY;
         tabla[0][4].type = NONE;
         
         king.posx = 2;
         king.posy = 0;
         
         tabla[0][3].value = ROOK;
         tabla[0][3].type = WHITE;
         tabla[0][0].value = EMPTY;
         tabla[0][0].type = NONE;
         return 0;
         }
   
    tabla[linie][coloana].value =  tabla[linie1][coloana1].value;
    tabla[linie][coloana].type = tabla[linie1][coloana1].type;
    tabla[linie1][coloana1].value = EMPTY;
    tabla[linie1][coloana1].type = NONE;
    //pentru transformarea pionului in regina cand ajunge pe ultima linie
    if ((( linie == 7 && stm==WHITE) || (linie ==0 && stm==BLACK)) && tabla[linie][coloana].type==PAWN)  tabla[linie][coloana].value = QUEEN;
    return 0;
       
}
//change side to move
int change_stm(int stm) {

    if (stm == WHITE) return BLACK;
       else return WHITE;
}

//genereaza toate miscarile posibile pentru pionul de pe pozitia (x,y)
Rezultat* miscare_pion ( int x, int y, int engineSide, int* nr) {
        
        static Rezultat rez[3];
        int i=0;
        if (engineSide == BLACK) {
        if (x == 6) {
           if (tabla[x-2][y].value == EMPTY && tabla[x-1][y].value == EMPTY) { 
                rez[i].x = x-2; 
                rez[i].y = y;
                i++;
                }
                }
        if ( x-1>=0 && tabla[x-1][y].value == EMPTY) { 
            rez[i].x = x-1; 
            rez[i].y = y;
            i++;
            }
        if (x-1>=0 && y+1<=7 && tabla[x-1][y+1].type != engineSide && tabla[x-1][y+1].type !=NONE ) { 
            rez[i].x = x-1; 
            rez[i].y = y+1;
            i++;
            }
        if (x-1 >=0 && y-1>=0 && tabla[x-1][y-1].type != engineSide && tabla[x-1][y-1].type !=NONE) { 
            rez[i].x = x-1; 
            rez[i].y = y-1;
            i++;
            }
        } else {
        if (x == 1) {
           if (tabla[x+2][y].value == EMPTY && tabla[x+1][y].value == EMPTY) { 
                rez[i].x = x+2; 
                rez[i].y = y;
                i++;
                }
                }
        if ( x+1>=0 && tabla[x+1][y].value == EMPTY) { 
            rez[i].x = x+1; 
            rez[i].y = y;
            i++;
            }
        if (x+1>=0 && y+1<=7 && tabla[x+1][y+1].type != engineSide && tabla[x+1][y+1].type !=NONE ) { 
            rez[i].x = x+1; 
            rez[i].y = y+1;
            i++;
            }
        if (x+1 >=0 && y-1>=0 && tabla[x+1][y-1].type != engineSide && tabla[x+1][y-1].type !=NONE) { 
            rez[i].x = x+1; 
            rez[i].y = y-1;
            i++;
            }
        }
        *nr =i;
        return rez;

}
//genereaza toate miscarile posibile pentru tura de pe pozitia (x,y)
Rezultat* miscare_tura ( int x, int y, int engineSide, int* nr) {
        
       static Rezultat rez[3];
       int j=0,i=0;
       for (i=x+1; i<8; i++) {
            if (tabla[i][y].value == EMPTY ) {
               rez[j].x=i;
               rez[j].y=y;
               j++;
               } else if (tabla[i][y].type != engineSide && tabla[i][y].value != EMPTY) {
                                  rez[j].x = i;
                                  rez[j].y = y;
                                  j++;
                                  break;
                                  } else  if (tabla[i][y].type == engineSide) break;
            
            }
         for (i=x-1; i>=0; i--) {
            if (tabla[i][y].value == EMPTY ) {
               rez[j].x=i;
               rez[j].y=y;
               j++;
               } else if (tabla[i][y].type != engineSide && tabla[i][y].value != EMPTY) {
                                  rez[j].x = i;
                                  rez[j].y = y;
                                  j++;
                                  break;
                                  } else  if (tabla[i][y].type == engineSide) break;

            }
         for (i=y-1; i>=0; i--) {
            if (tabla[x][i].value == EMPTY ) {
               rez[j].x=x;
               rez[j].y=i;
               j++;
               } else if (tabla[x][i].type != engineSide && tabla[x][i].value != EMPTY) {
                                  rez[j].x = x;
                                  rez[j].y = i;
                                  j++;
                                  break;
                                  } else  if (tabla[x][i].type == engineSide) break;
            
            }
           for (i=y+1; i<8; i++) {
            if (tabla[x][i].value == EMPTY ) {
               rez[j].x=x;
               rez[j].y=i;
               j++;
               } else if (tabla[x][i].type != engineSide && tabla[x][i].value != EMPTY) {
                                  rez[j].x = x;
                                  rez[j].y = i;
                                  j++;
                                  break;
                                  } else  if (tabla[x][i].type == engineSide) break;
            }
        *nr =j;
        return rez;

}
//genereaza toate miscarile posibile pentru calul de pe pozitia (x,y)
Rezultat* miscare_cal ( int x, int y, int engineSide, int* nr) {
        
        static Rezultat rez[3];
        int i=0;
        if( x-2>=0 && y-1>=0 && tabla[x-2][y-1].type !=engineSide ) {
            rez[i].x = x-2;
            rez[i].y = y-1;
            i++;
            }
        if( x-2>=0 && y+1<8 && tabla[x-2][y+1].type !=engineSide ) {
            rez[i].x = x-2;
            rez[i].y = y+1;
            i++;
            }
         if( x-1>=0 && y+2<8 && tabla[x-1][y+2].type !=engineSide ) {
            rez[i].x = x-1;
            rez[i].y = y+2;
            i++;
            }
         if( x-1>=0 && y-2>=0 && tabla[x-1][y-2].type !=engineSide ) {
            rez[i].x = x-1;
            rez[i].y = y-2;
            i++;
            }
         if( x+1<8 && y+2<8 && tabla[x+1][y+2].type !=engineSide ) {
            rez[i].x = x+1;
            rez[i].y = y+2;
            i++;
            }
         if( x+2<8 && y+1<8 && tabla[x+2][y+1].type !=engineSide ) {
            rez[i].x = x+2;
            rez[i].y = y+1;
            i++;
            }
         if( x+2<8 && y-1>=0 && tabla[x+2][y-1].type !=engineSide ) {
            rez[i].x = x+2;
            rez[i].y = y-1;
            i++;
            }
          if( x+1<8 && y-2>=0 && tabla[x+1][y-2].type !=engineSide ) {
            rez[i].x = x+1;
            rez[i].y = y-2;
            i++;
            }
        *nr =i;
        return rez;

}
//genereaza toate miscarile posibile pentru nebunul de pe pozitia (x,y)
Rezultat* miscare_nebun ( int x, int y, int engineSide,int* nr) {
        
        static Rezultat rez[3];
        int i=0,j=0;
        int n=0;
        if ( x-1 >=0 && y+1<8 ) {
        for (i=x-1, j=y+1; i>=0, j<8; i--, j++) {
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }
        }
        if ( x-1 >=0 && y-1>=0 ) {
        for (i=x-1, j=y-1; i>=0, j>=0; i--, j--) {
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }
        }
        if (x+1 < 8) {
        for (i=x+1, j=y-1; i<8, j>=0; i++, j--) {
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }       
        }
        if (x+1 < 8) {
         for (i=x+1, j=y+1; i<8, j<8; i++, j++) {
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }     
        }
         *nr =n;
        return rez;

}

//genereaza toate miscarile posibile pentru regina de pe pozitia (x,y)
Rezultat* miscare_regina ( int x, int y, int engineSide, int*nr) {
        
        static Rezultat rez[3];
        int i=0,j=0;
        int n=0;
        if ( x-1 >=0 && y+1<8 ) {
        for (i=x-1, j=y+1; i>=0, j<8; i--, j++) {
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }
        }
        if ( x-1 >=0 && y-1>=0 ) {
        for (i=x-1, j=y-1; i>=0, j>=0; i--, j--) {
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }
        }
        if ( x+1 <8 && y-1>=0 ) {
        for (i=x+1, j=y-1; i<8, j>=0; i++, j--) {
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }       
        }
        if ( x+1<8 && y+1<8 ) {
        for (i=x+1, j=y+1; i<8, j<8; i++, j++) {
           
            if (tabla[i][j].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=j;
               n++;
               } else if (tabla[i][j].type != engineSide && tabla[i][j].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = j;
                                  n++;
                                  break;
                                  } else  if (tabla[i][j].type == engineSide) break;
        }    
        }
        if ( x+1 <8) {
        for (i=x+1; i<8; i++) {
            if (tabla[i][y].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=y;
               n++;
               } else if (tabla[i][y].type != engineSide && tabla[i][y].value != EMPTY) {
                                  rez[n].x = i;
                                  rez[n].y = y;
                                  n++;
                                  break;
                                  } else  if (tabla[i][y].type == engineSide) break;
            
            }
            }
        if ( x-1 >=0) {
         for (i=x-1; i>=0; i--) {
            if (tabla[i][y].value == EMPTY ) {
               rez[n].x=i;
               rez[n].y=y;
               n++;
               } else if (tabla[i][y].type != engineSide && tabla[i][y].value != EMPTY) {
                                  rez[n].x=i;
                                  rez[n].y=y;
                                  n++;
                                  break;
                                  } else  if (tabla[i][y].type == engineSide) break;
            
            }
            }
         if ( y-1 >=0) {
         for (i=y-1; i>=0; i--) {
            if (tabla[x][i].value == EMPTY ) {
               rez[n].x=x;
               rez[n].y=i;
               n++;
               } else if (tabla[x][i].type != engineSide && tabla[x][i].value != EMPTY) {
                                  rez[n].x=x;
                                  rez[n].y=i;
                                  n++;
                                  break;
                                  } else  if (tabla[x][i].type == engineSide) break;
            
            }
            }
            if (y+1<8 ) {
           for (i=y+1; i<8; i++) {
            if (tabla[x][i].value == EMPTY ) {
               rez[n].x=x;
               rez[n].y=i;
               n++;
               } else if (tabla[x][i].type != engineSide && tabla[x][i].value != EMPTY) {
                                  rez[n].x=x;
                                  rez[n].y=i;
                                  n++;
                                  break;
                                  } else  if (tabla[x][i].type == engineSide) break;
            } 
            }
       *nr =n;
        return rez;

}
//genereaza toate miscarile posibile pentru regele de pe pozitia (x,y)
Rezultat* miscare_rege ( int x, int y, int engineSide, int* nr) {
        
        static Rezultat rez[3];
        int i=0;
        if (x+1<=7 && ( tabla[x+1][y].value == EMPTY || tabla[x+1][y].type !=engineSide ) ){ 
           rez[i].x = x+1; 
           rez[i].y = y;
           i++;
           }
                
        if ( x-1>=0 && (tabla[x-1][y].value == EMPTY  || tabla[x-1][y].type !=engineSide )) { 
            rez[i].x = x-1; 
            rez[i].y = y;
            i++;
            }
        if (x-1>=0 && y+1<=7 && ( tabla[x-1][y+1].value == EMPTY || tabla[x-1][y+1].type !=engineSide) ) { 
            rez[i].x = x-1; 
            rez[i].y = y+1;
            i++;
            }
        if (x-1 >=0 && y-1>=0 && ( tabla[x-1][y-1].value == EMPTY || tabla[x-1][y-1].type !=engineSide)) { 
            rez[i].x = x-1; 
            rez[i].y = y-1;
            i++;
            }
        if (x+1<=7 && y+1<=7 && ( tabla[x+1][y+1].value == EMPTY || tabla[x+1][y+1].type !=engineSide) ) { 
            rez[i].x = x+1; 
            rez[i].y = y+1;
            i++;
            }
        if (x+1<=7 && y-1>=0 && ( tabla[x+1][y-1].value == EMPTY || tabla[x+1][y-1].type !=engineSide)) { 
            rez[i].x = x+1; 
            rez[i].y = y-1;
            i++;
            }   
         if (y+1<=7 &&  (tabla[x][y+1].value == EMPTY || tabla[x][y+1].type !=engineSide ) ) { 
            rez[i].x = x; 
            rez[i].y = y+1;
            i++;
            }          
        if ( y-1>=0 && (tabla[x][y-1].value == EMPTY || tabla[x][y-1].type !=engineSide ) ) { 
            rez[i].x = x; 
            rez[i].y = y-1;
            i++;
            }          
        *nr =i;
        return rez;

}



int main(int argc, const char * argv[]){
  
  int stm = WHITE;                                 // side to move
  int engineSide=0;                            // side played by engine
  int i, score,j,ox,oy,nr=0,n=0;
  char inBuf[80], command[80];
  
  Rezultat *rez = NULL;

  //initializari tabla de sah
  initializare(tabla);

  //initializare pozitie rege
  king.posx = 4;
  king.posy = 7;
  king.type = BLACK;

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  
  while(1){
           
        fflush(stdout); 
        
       	if (stm == engineSide) {
      
               int ceva=0;
               char* st=NULL;
               char* str=NULL;
               char string[5];
               string[0]='\0';
               string[1]='\0';
               string[2]='\0';
               string[3]='\0';
               string[4]='\0';
               string[5]='\0';

               ox = rand() % 8 ;
               oy = rand() % 8 ;

               while ( tabla[ox][oy].type != engineSide) {
                 ox = rand() % 8 ;
                 oy = rand() % 8 ; 
                 }
                     
               st = transf(oy,ox);
               snprintf(string, 2, "%s", st);           
              
               Rezultat *rez = NULL;
               if (tabla[ox][oy].value == PAWN ) rez = miscare_pion(ox,oy,engineSide,& nr); 
                  else if (tabla[ox][oy].value == ROOK ) rez = miscare_tura(ox,oy,engineSide,& nr); 
                       else if (tabla[ox][oy].value == BISHOP ) rez = miscare_nebun(ox,oy,engineSide,& nr); 
                            else if (tabla[ox][oy].value == KNIGHT ) rez = miscare_cal(ox,oy,engineSide,& nr); 
                                 else if (tabla[ox][oy].value == QUEEN ) rez = miscare_regina(ox,oy,engineSide,& nr); 
                                      else if (tabla[ox][oy].value == KING ) rez = miscare_rege(ox,oy,engineSide,& nr); 
            
               if (nr>0) {
                         
                  n = rand() % nr;
                  str = transf(rez[n].y,rez[n].x);
                  snprintf(string, 4, "%s%s", string,str);
                  char mutare[4];
                  strncpy(mutare,string,4);
                  mutare[4]='\0';
                  ceva = miscare_engineSide(mutare,stm);
               
                  if( ceva ==0 && check_king() ==0) {
               
                     printf("move %s\n", mutare);
                     stm = change_stm(stm);
                     } 
               }
        } else {
               
             fgets(inBuf, 80, stdin);
             sscanf(inBuf, "%s", command);
             if ( miscare_oponent(command,stm) != -1 ) stm = change_stm(stm);
             
         
        if(!strcmp(command, "quit"))    { break; } 
        if(!strcmp(command, "force"))   { engineSide = NONE;    continue; }
        if(!strcmp(command, "new"))     { engineSide = BLACK; initializare(tabla); continue; }
        if(!strcmp(command, "go"))      { engineSide = stm;  continue; }
        if(!strcmp(command, "xboard"))  { initializare(tabla); continue;  }
        if(!strcmp(command, "white"))   { stm = WHITE; engineSide = BLACK;    continue; }
        if(!strcmp(command, "black"))   { stm = BLACK; engineSide = WHITE; king.posy = 0; king.type = WHITE; continue; }        

              }
        }
    return 0;
}
