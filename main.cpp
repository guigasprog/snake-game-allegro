#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_primitives.h>
#include <allegro_image.h>
#include <keyboard.h>
#include <conio.h>
#include <stdlib.h>
#include <string>

using namespace std;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fEventos = NULL;
ALLEGRO_EVENT ev;

int cellSize = 30;
int cellCount = 20;
class Cobra {
public:
    int positionX;
    int positionY;

    Cobra(){
        randomPosition();
    }
    void desenhar() {
        al_draw_filled_rectangle(positionX * cellSize, positionY * cellSize, (positionX * cellSize) + cellSize, (positionY * cellSize) + cellSize, al_map_rgb(255, 140, 0));
    }
    void randomPosition(){
        this->positionX = rand() % (cellCount - 1);
        this->positionY = rand() % (cellCount - 1);
    }
    void setPositionX(int x) {
        this->positionX = x;
    }
    void setPositionY(int y) {
        this->positionY = y;
    }
};

class Comida {
public:
    int positionX;
    int positionY;
    int engolida;
    ALLEGRO_BITMAP *objeto;

    Comida(){
        objeto = al_load_bitmap("./png/apple.png");
        randomPosition();
        this->engolida = 0;
    }
    ~Comida(){
        al_destroy_bitmap(objeto);
    }

    void desenhar(Cobra cobra){
        if(cobra.positionX == this->positionX && cobra.positionY == this->positionY){
            randomPosition();
            this->engolida++;
        }
        al_draw_bitmap(objeto,positionX *cellSize, positionY * cellSize,1);
    }

    void randomPosition(){
        this->positionX = rand() % (cellCount - 1);
        this->positionY = rand() % (cellCount - 1);
    }
};


int main(){

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

    al_init_font_addon();

    ALLEGRO_FONT* font = al_create_builtin_font();

    janela = al_create_display(cellSize * cellCount, cellSize * cellCount);
    al_set_window_position(janela, 100,100);
    al_set_window_title(janela, "RETRO SNAKE");
    al_set_display_icon(janela, al_load_bitmap("./png/apple.png"));


    float time = (1.0 / 30.0);
    ALLEGRO_TIMER *timer = al_create_timer(time);

    fEventos = al_create_event_queue();
    al_register_event_source(fEventos, al_get_display_event_source(janela));
    al_register_event_source(fEventos, al_get_timer_event_source(timer));
    al_register_event_source(fEventos, al_get_keyboard_event_source());


    ALLEGRO_COLOR bg = al_map_rgb(173,204,96);
    ALLEGRO_COLOR comida = al_map_rgb(43, 51,24);
    ALLEGRO_COLOR cobra = al_map_rgb(43, 51,24);




    Comida apple = Comida();
    Cobra snake = Cobra();
    while(true){

        al_wait_for_event_timed(fEventos, &ev, 0.006);
        al_clear_to_color(bg);
        snake.desenhar();
        apple.desenhar(snake);

        //MOVE
        if(ev.type == ALLEGRO_EVENT_KEY_UP){
            if(ev.keyboard.keycode == ALLEGRO_KEY_W) {
                snake.positionY--;
            } else if(ev.keyboard.keycode == ALLEGRO_KEY_S) {
                snake.positionY++;
            } else if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
                snake.positionX--;
            } else if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
                snake.positionX++;
            } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                break;
            }
        }
        if(snake.positionY == -1) {
            snake.positionY = cellCount;
        } else if(snake.positionY == cellCount) {
            snake.positionY = 0;
        } else if(snake.positionX == -1) {
            snake.positionX = cellCount;
        } else if(snake.positionX == cellCount) {
            snake.positionX = 0;
        }

        al_draw_textf(font, al_map_rgb(0, 0, 0), 10, 20, 0, "Placar: %i" , apple.engolida);
        al_flip_display();
        al_rest(0.1);

    }

    al_destroy_display(janela);
    al_destroy_event_queue(fEventos);
}
