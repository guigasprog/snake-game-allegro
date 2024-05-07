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
    ALLEGRO_BITMAP *objeto;
    int flag = 0;

    Cobra(){
        randomPositionCobra();
        objeto = al_load_bitmap("./png/frame.png");
    }
    void desenhar() {
        int i=0, positionX, positionY;
        for (; i<contador;i++){
            positionX = corpo[i].x;
            positionY = corpo[i].y;
            if(i == 0) {
                al_draw_scaled_bitmap(objeto,2*8, 2*8,8,8,positionX*cellSize,positionY*cellSize,cellSize,cellSize,flag);
            } else {
                al_draw_scaled_bitmap(objeto,3*8, 1*8,8,8,positionX*cellSize,positionY*cellSize,cellSize,cellSize,flag);
            }

        }
        positionX = corpo[i].x;
        positionY = corpo[i].y;
        if(i == contador) al_draw_scaled_bitmap(objeto,0*8,0*8,8,8,positionX*cellSize,positionY*cellSize,cellSize,cellSize,flag);
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
        flag = 90;
    }
    void descerCobra(){
        int i = contador;
        for(;i > 0;i--){
            corpo[i] = corpo[i-1];
        }
        corpo[i].descer();
        flag = 0;
    }
    void esquerdaCobra(){
        int i = contador;
        for(;i > 0;i--){
            corpo[i] = corpo[i-1];
        }
        corpo[i].esquerda();
        flag = 90;
    }
    void direitaCobra(){
        int i = contador;
        for(;i > 0;i--){
            corpo[i] = corpo[i-1];
        }
        corpo[i].direita();
        flag = 240;
    }

    void aumentar(){
        this->contador ++;
    }

    bool bateu(){
        vetor cabeca = corpo[0];
        for(int i=1; i<contador;i++){
            if(cabeca.x == corpo[i].x && cabeca.y == corpo[i].y){
                return true;
            }
        }
        return false;
    }

};



class Comida{

public:
    vetor position;
    int engolida;
    ALLEGRO_BITMAP *objeto;
    int sprite = 8;
    int att=1;

    Comida(){
        objeto = al_load_bitmap("./png/frame.png");
        randomPositionFood();
        this->engolida = 0;
    }
    ~Comida(){
        al_destroy_bitmap(objeto);
    }

    void desenhar(){
        al_draw_scaled_bitmap(objeto,att*sprite,3*sprite,sprite,sprite,position.x *cellSize, position.y * cellSize,cellSize,cellSize,0);
        //al_draw_bitmap_region(objeto,2*sprite,1*sprite,sprite,sprite,position.x *cellSize, position.y * cellSize,0);
        //al_draw_bitmap(objeto,position.x *cellSize, position.y * cellSize,0);
        if (att < 3){
            att += 1;
        }else{
            att =1;
        }
    }

    bool comeu(Cobra cobra){
        if (position.x == cobra.corpo[0].x && position.y == cobra.corpo[0].y){
            return true;
        }
        return false;
    }

    void randomPositionFood(){
        this->position.x = rand() % (cellCount - 1);
        this->position.y = rand() % (cellCount - 1);
    }
    void engolir(){
        this->engolida ++;
    }
};

struct tabuleiro {
    int x;
    int y;

    ALLEGRO_BITMAP *fundo = al_load_bitmap("./png/frame.png");
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
    tabuleiro background;
    ALLEGRO_COLOR comida = al_map_rgb(43, 51,24);
    ALLEGRO_COLOR cobra = al_map_rgb(43, 51,24);


    Comida apple;
    Cobra snake;
    bool gameOver = false;

    int mov;

    while(!gameOver){

        al_wait_for_event_timed(fEventos, &ev, 0.00166);
        for(background.x = cellCount; background.x > -1; background.x--){
            for(background.y = cellCount; background.y > -1; background.y--) {
                al_draw_scaled_bitmap(background.fundo,0*8,3*8,8,8,background.x*cellSize,background.y*cellSize,cellSize,cellSize,0);
            }
        }
        //al_clear_to_color(bg);
        if(apple.comeu(snake)){
            apple.engolir();
            apple.randomPositionFood();
            snake.aumentar();
        }
        if(snake.bateu()){
            gameOver = true;
        }
        snake.desenhar();
        apple.desenhar();

        //MOVE
        if(ev.type == ALLEGRO_EVENT_KEY_UP){
            mov = ev.keyboard.keycode;
            if(mov == ALLEGRO_KEY_W) {
                if(snake.corpo[0].y-1 != snake.corpo[1].y) snake.subirCobra();
            } else if(mov == ALLEGRO_KEY_S) {
                if(snake.corpo[0].y+1 != snake.corpo[1].y) snake.descerCobra();
            } else if(mov == ALLEGRO_KEY_A) {
                if(snake.corpo[0].x-1 != snake.corpo[1].x) snake.esquerdaCobra();
            } else if(mov == ALLEGRO_KEY_D) {
                if(snake.corpo[0].x+1 != snake.corpo[1].x) snake.direitaCobra();
            } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || mov == ALLEGRO_KEY_ESCAPE){
                gameOver = true;
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
