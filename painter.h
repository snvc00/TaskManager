#ifndef PAINTER_H_INCLUDED
#define PAINTER_H_INCLUDED

#include <windows.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LGREY 7
#define DGREY 8
#define LBLUE 9
#define LGREEN 10
#define LCYAN 11
#define LRED 12
#define LMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define MARG_CHAR "0" /// Caracter que se dibuja en los margenes
#define DEFAULT_COLOR WHITE, BLACK

void gotoxy(const int &x, const int &y);            ///Funcion que posiciona el cursor en la posicion x, y
void textColor(const int &fondo, const int &texto); ///Funcion que establecera el color del texto y el color del fondo
///Funcion que genera una ventana con ancho y largo determinados por parametros, color determinado por parametro y posicion inicial definido por xPos y Ypos
void drawWindow(const int &ancho, const int& largo, const int &color, const int &xPos, const int &yPos);

void gotoxy(const int &x, const int &y) {
    HANDLE puntero;
    puntero = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordenadas;
    coordenadas.X = x;
    coordenadas.Y= y;
    SetConsoleCursorPosition(puntero, coordenadas);
 }

void textColor(const int &fondo, const int &texto) {
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	int nuevocolor = texto + (fondo * 16);
	SetConsoleTextAttribute(Console, nuevocolor);
}

void drawWindow(const int &ancho, const int& largo, const int &color, const int &xPos, const int &yPos) {
    textColor(color, color);
    for (int i(0); i<largo; ++i) {
        gotoxy(xPos+i, yPos);
        std::cout << MARG_CHAR;
        gotoxy(xPos+i, yPos+ancho-1);
        std::cout << MARG_CHAR;
    }
    for (int i(0); i<ancho; ++i) {
        gotoxy(xPos, yPos+i);
        std::cout << MARG_CHAR;
        gotoxy(xPos+largo-1, yPos+i);
        std::cout << MARG_CHAR;
    }
    textColor(DEFAULT_COLOR);
}
#endif // PAINTER_H_INCLUDED
