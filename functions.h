//Podstawowe biblioteki
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h> //bool, true, false
#include <windows.h> // for Sleep
#include <math.h> // ceil
#include <ctype.h> // tolower
#include <time.h> // time for srand

typedef struct snake_segment{
    int x, last_x;
    int y, last_y;
    struct snake_segment* next;
    struct snake_segment* prev;
    char skin; // znak reprezentujacy graficznie segment weza
} segment;

void clear(); //deklaracja funkcji czyszczenia ekranu
int game(int w_size, float speed); //deklaracja funkcji gry
bool check_snake_position(int x, int y, segment* ptr); //deklaracja funkcji sprawdzającej pozycję węża
void board(int w_size, segment* head, bool window[][w_size]); //deklaracja funkcji rysującej plansze
void snake_position(segment* head); //deklaracja funkcji aktualizującej pozycję węża
void free_snake(segment* head);
bool collision(segment* head, int w_size); //deklaracja funkcji sprawdzającej kolizje
