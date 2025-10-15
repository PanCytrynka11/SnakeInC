#include "functions.h"


// funkcja czyszcząca ekran
void clear(){
    system("cls");
}

// funkcja sprawdzająca położenie węża na planszy (iteracyjnie po wskaźnikach next)
bool check_snake_position(int x, int y, segment* head){
    for (segment* p = head; p != NULL; p = p->next){
        if (p->x == x && p->y == y) return true;
    }
    return false;
}

// funkcja rysująca planszę
void board(int w_size, segment* head, bool window[][w_size]){
    char plansza[(w_size + 2) * (w_size + 3) + 1];
    char* out = plansza;

    for (int i = 0; i < w_size + 2; i++) {
        *out++ = '#';
    }
    *out++ = '\n';

    for (int y = 0; y < w_size; y++) {
        *out++ = '#';
        for (int x = 0; x < w_size; x++) {
            char cell = window[y][x] ? '6' : ' ';
            for (segment* seg = head; seg != NULL; seg = seg->next) {
                if (seg->x == x && seg->y == y) {
                    cell = seg->skin;
                    break;
                }
            }
            *out++ = cell;
        }
        *out++ = '#';
        *out++ = '\n';
    }

    for (int i = 0; i < w_size + 2; i++) {
        *out++ = '#';
    }
    *out++ = '\n';
    *out = '\0';

    printf("%s", plansza);
}


// przesunięcie ciała węża według poprzednich pozycji (iteracyjnie po next)
void snake_position(segment* head){
    if (head == NULL) return;
    int prev_x = head->last_x;
    int prev_y = head->last_y;
    for (segment* s = head->next; s != NULL; s = s->next){
        s->last_x = s->x;
        s->last_y = s->y;
        s->x = prev_x;
        s->y = prev_y;
        prev_x = s->last_x;
        prev_y = s->last_y;
    }
}

//funcja kolizji weza ze sciana lub samym soba
bool collision(segment* head, int w_size){
    //kolizja ze sciana
    if (head->x < 0 || head->x >= w_size || head->y < 0 || head->y >= w_size)
    {
        return true;
    }
    //kolizja z samym soba
    if (check_snake_position(head->x, head->y, head->next))
    {
        return true;
    }
    return false;
}

void free_snake(segment* head){
    while (head != NULL){
        segment* next = head->next;
        free(head);
        head = next;
    }
}
