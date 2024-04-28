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

const int cellSize = 30;
const int cellCount = 20;

struct vetor{
    int x;
    int y;

    void subir(){y --;};

    void descer(){y ++;};

    void esquerda(){x --;};

    void direita(){x ++;};

};

class Cobra{

public:
    int contador = 0;
    vetor corpo[(cellCount * cellCount)];

    Cobra(){
        randomPositionCobra();
    }
    void desenhar() {
        for (int i=0; i<contador;i++){
            int positionX = corpo[i].x;
            int positionY = corpo[i].y;
            al_draw_filled_rounded_rectangle(positionX * cellSize, positionY * cellSize, (positionX * cellSize) + cellSize, (positionY * cellSize) + cellSize, (cellSize/4) , (cellSize/4), al_map_rgb(255, 140, 0));
        }
    }
    void randomPositionCobra(){
        for(int i=0; i < 3;i++){
            corpo[i] = {(6-i),9};
            contador ++;
        }
    }

    void subirCobra(){
        int i = contador;
        for(;i > 0;i--){
            corpo[i] = corpo[i-1];
        }
        corpo[i].subir();
    }
    void descerCobra(){
        int i = contador;
        for(;i > 0;i--){
            corpo[i] = corpo[i-1];
        }
        corpo[i].descer();
    }
    void esquerdaCobra(){
        int i = contador;
        for(;i > 0;i--){
            corpo[i] = corpo[i-1];
        }
        corpo[i].esquerda();
    }
    void direitaCobra(){
        int i = contador;
        for(;i > 0;i--){
            corpo[i] = corpo[i-1];
        }
        corpo[i].direita();
    }

    void aumentar(){
        this->contador ++;
    }

};



class Comida{

public:
    vetor position;
    int engolida;
    ALLEGRO_BITMAP *objeto;

    Comida(){
        objeto = al_load_bitmap("./png/apple.png");
        randomPositionFood();
        this->engolida = 0;
    }
    ~Comida(){
        al_destroy_bitmap(objeto);
    }

    void desenhar(){
        al_draw_bitmap(objeto,position.x *cellSize, position.y * cellSize,1);
    }

    bool comeu(Cobra cobra){
        if (position.x == cobra.corpo[0].x && position.y == cobra.corpo[0].y){
            return true;
        }
        return false;
    }

    void randomPositionFood(){
        this->position.x = rand() % (20 - 1);
        this->position.y = rand() % (20 - 1);
    }
    void engolir(){
        this->engolida ++;
    }
};


void comeu(Comida comi, Cobra cob){
    if (comi.position.x == cob.corpo[0].x && comi.position.y == cob.corpo[0].y){
        cob.aumentar();
        comi.randomPositionFood();
        comi.engolir();
    };
}

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


    Comida apple;
    Cobra snake;
    while(true){

        al_wait_for_event_timed(fEventos, &ev, 0.00166);
        al_clear_to_color(bg);
        if(apple.comeu(snake)){
            apple.engolir();
            apple.randomPositionFood();
            snake.aumentar();
        }
        snake.desenhar();
        apple.desenhar();

        //MOVE
        if(ev.type == ALLEGRO_EVENT_KEY_UP){
            if(ev.keyboard.keycode == ALLEGRO_KEY_W) {
                snake.subirCobra();
            } else if(ev.keyboard.keycode == ALLEGRO_KEY_S) {
                snake.descerCobra();
            } else if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
                snake.esquerdaCobra();
            } else if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
                snake.direitaCobra();
            } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                break;
            }
        }
        if(snake.corpo[0].y == -1) {
            snake.corpo[0].y = cellCount;
        } else if(snake.corpo[0].y == cellCount) {
            snake.corpo[0].y = 0;
        } else if(snake.corpo[0].x == -1) {
            snake.corpo[0].x = cellCount;
        } else if(snake.corpo[0].x == cellCount) {
            snake.corpo[0].x = 0;
        }

        al_draw_textf(font, al_map_rgb(0, 0, 0), 10, 20, 0, "Placar: %i" , apple.engolida);
        al_flip_display();
        al_rest(0.1);

    }

    al_destroy_display(janela);
    al_destroy_event_queue(fEventos);
}
