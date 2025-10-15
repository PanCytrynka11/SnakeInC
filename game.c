#include "functions.h"


int game(int w_size, float speed){
    //Inicjalizacja zmiennych gry
    bool running = true;
    int wynik = 0;
    const int max_food_amount = ceil(w_size / 5); //ilosc owockow na planszy
    int curr_food_amount = 0; //aktualna ilosc owockow na planszy
    int food_x, food_y; //pozycja owocka
    char direction; //kierunek ruchu weza
    char key; //zmienna przechowujaca wcisniety klawisz
    //Inicjalizacja weza
    segment* head = (segment*)malloc(sizeof(segment)); //glowa weza
    head->skin = 'O'; //poczatkowy znak glowy weza
    head->next = NULL;
    head->prev = NULL;
    //pozycja weza
    head->x = w_size / 2;
    head->y = w_size / 2;
    //tworzenie planszy
    bool window[w_size][w_size];
    for(int i=0; i<w_size; i++){
        for(int j=0; j<w_size; j++){
            window[i][j] = false;
        }
    }
    // ...game logic...
    while (running)
    {
        //Copilot
        // Check for user input without blocking
        if (kbhit()) {
            key = tolower(getch());
            switch (key) {
                case 'w':
                    direction = 'N'; // up
                    head->skin = '^';
                    break;
                case 's':
                    direction = 'S'; // down
                    head->skin = 'v';
                    break;
                case 'a':
                    direction = 'W'; // left
                    head->skin = '<';
                    break;
                case 'd':
                    direction = 'E'; // right
                    head->skin = '>';
                    break;
                case 27:
                    running = false; // ESC to quit
                    break;
                default:
                    break;
            }
        }

        // Check for collisions
        if (collision(head, w_size)) {
            running = false;
            break; //koniec petli gry
        }

        // Zmiana lokalizacji weza
        head->last_x = head->x;
        head->last_y = head->y;
        switch (direction) {
            case 'N':
                head->y--;
                break;
            case 'S':
                head->y++;
                break;
            case 'W':
                head->x--;
                break;
            case 'E':
                head->x++;
                break;
            default:
                break;
        }
        snake_position(head); //aktualizacja pozycji segmentow weza

        //sprawdzenie czy wezel zjadl owocka
        //copilot
        if (window[head->y][head->x] == true){
            window[head->y][head->x] = false; //usuwanie owocka z planszy
            curr_food_amount--;
            wynik++;
            //dodawanie segmentu do weza

            segment* new_segment = (segment*)malloc(sizeof(segment));
            new_segment->skin = '+'; //znak segmentu weza
            // znajdź ogon po łańcuchu next
            segment* tail = head;
            while (tail->next != NULL) tail = tail->next;
            // dołącz nowy segment na końcu
            new_segment->next = NULL;
            new_segment->prev = tail;
            new_segment->x = tail->last_x;
            new_segment->y = tail->last_y;
            tail->next = new_segment;
        }
        

        clear();
        printf("Wynik: %d\n\n", wynik);

        //generowanie brakujących owocków
        while (curr_food_amount < max_food_amount){
            food_x = rand() % w_size;
            food_y = rand() % w_size;
            if (window[food_y][food_x] == false){
                if (!(check_snake_position(food_x, food_y, head))){
                    window[food_y][food_x] = true;
                    curr_food_amount++;
                }
            }
        }
        
        //rysowanie planszy
        board(w_size, head, window);
        
        if(running){
            printf("\n\nSterowanie: W - gora, S - dol, A - lewo, D - prawo, ESC - wyjscie\n");
        }
        Sleep((int)(1000/speed)); // Adjust speed as needed
    }
    free_snake(head);
    printf("\n\nKoniec gry! Nacisnij dowolny klawisz by kontynuowac.\n");
    getch();
    return wynik;
}
