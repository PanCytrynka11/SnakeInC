#include "functions.h" //zewnętrzny plik z funkcjami


int main(){
    srand((unsigned int)time(NULL)); //inicjalizacja generatora liczb losowych

    //Podstawowe zmienne
    int wynik=0;//wynik z poprzedniej gry
    int w_size = 20; //domyślny rozmiar planszy
    float speed = 1; //domyślna prędkość wensza
    char choice; //zmienna wyboru w menu
    // Alert dla osob z epilepsja (bez polskich znakow)
    clear();
    printf("UWAGA: Gra zawiera migajace swiatla.\n");
    printf("Osoby z epilepsja fotowrazliwa powinny zachowac ostroznosc.\n");
    printf("Nacisnij Enter aby kontynuowac lub Esc aby wyjsc.\n");
    do{
        choice = getch(); // wstepny wybor po alercie
        if (choice == 27) { // Esc
            return 0;
        }
    }while (choice != '\r'); // Enter

    
    while (true)
    {
        clear();
        printf("Witaj w grze Snake!\n\n");
        if(wynik != 0){
            printf("Twoj wynik to: %d\n\n", wynik);
        }
        printf("1. Start gry\n");
        printf("2. Wyjscie\n");
        choice = getch();
        switch (choice) {
            case '1':
                clear();
                do{
                    printf("Rozmiar planszy (domyslnie 20): %d\n", w_size);
                    printf("Predkosc (domyslnie 1): %.1f\n", speed);
                    printf("Zmienic wartosc? Wcisnij: R - Rozmiar; P - Predkosc; Esc - Nie zmieniaj");
                    choice = tolower(getch());
                    switch (choice)
                    {
                    case 'r':
                        do{
                            clear();
                            printf("\nPodaj rozmiar planszy (min 10, max 50): ");
                            scanf("%d", &w_size);
                            if (w_size < 10 || w_size > 50)
                            {
                                printf("Nieprawidlowy rozmiar. Sprobuj ponownie.\nKliknij by kontynowac.\n");
                                getch();
                            }
                        }while(w_size < 10 || w_size > 50);
                        break;
                    case 'p':
                        do{
                            clear();
                            printf("\nPodaj predkosc (0.1 - 10.0): ");
                            scanf("%f", &speed);
                            if (speed < 0.1 || speed > 10.0)
                            {
                                printf("Nieprawidlowa predkosc. Sprobuj ponownie.\nKliknij by kontynowac.\n");
                                getch();
                            }
                        }while(speed < 0.1 || speed > 10.0);
                        break;
                    default:
                        break;
                    }
                }while(choice == 'r' || choice == 'p');
                wynik = game(w_size, speed);
                break;
            case '2':
                return 0;
            default:
                printf("Nieprawidlowy wybor. Sprobuj ponownie.\nKliknij by kontynowac.\n");
                getch();
                break;
        }
    }
}
