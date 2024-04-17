#include <iostream>
#include <allegro.h>
#include <allegro_primitives.h>
#include <allegro_image.h>
#include <keyboard.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fEventos = NULL;
ALLEGRO_EVENT ev;

int cellSize = 30;
int cellCount = 20;

class Comida {
public:
    int positionX;
    int positionY;
    //bool engolida = true;
    ALLEGRO_BITMAP *objeto;

    Comida(){
        objeto = al_load_bitmap("./png/apple.png");
        aletorioPosition();
    }
    ~Comida(){
        al_destroy_bitmap(objeto);
    }

    void desenhar(){
        //aletorioPosition();
        //this->engolida = false;
        al_draw_bitmap(objeto,positionX *cellSize, positionY * cellSize,1);
    }

    void aletorioPosition(){
        this->positionX = rand() % (cellCount - 1);
        this->positionY = rand() % (cellCount - 1);
    }
};


/*void desenhaRetangulo(RETANGULO r) {
    if (r.traco == 0){
        al_draw_filled_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor);
    }else{
        al_draw_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor,r.traco);
    }
}
*/

/*bool colideRetangulo(RETANGULO r1, RETANGULO r2){
    if ( r2.x1+r2.w > r1.x1 &&
         r1.x1+r1.w > r2.x1 &&
         r2.y1+r2.h > r1.y1 &&
         r1.y1+r1.h > r2.y1   ){
        return true;
    } else {
        return false;
    }
}
*/


int main(){

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

    janela = al_create_display(cellSize * cellCount, cellSize * cellCount);
    al_set_window_position(janela, 100,100);
    al_set_window_title(janela, "RETRO SNAKE");
    al_set_display_icon(janela, al_load_bitmap("./png/apple.png"));


    float time = (1.0 / 60.0);
    ALLEGRO_TIMER *timer = al_create_timer(time);

    fEventos = al_create_event_queue();
    al_register_event_source(fEventos, al_get_display_event_source(janela));
    al_register_event_source(fEventos, al_get_timer_event_source(timer));
    al_register_event_source(fEventos, al_get_keyboard_event_source());

    //ALLEGRO_BITMAP *maca = al_load_bitmap("./png/apple.png");
    //ALLEGRO_BITMAP *bg = al_load_bitmap("./png/background.png");


    ALLEGRO_COLOR bg = al_map_rgb(173,204,96);
    ALLEGRO_COLOR comida = al_map_rgb(43, 51,24);
    ALLEGRO_COLOR cobra = al_map_rgb(43, 51,24);




    Comida comi = Comida();
    while(true){

        al_wait_for_event_timed(fEventos, &ev, 0.06);
        al_clear_to_color(bg);
        comi.desenhar();
        al_flip_display();
        /*desenhaRetangulo(cCobra);
        al_flip_display();
        */
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            break;
        }
        /*else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                    if(ev.keyboard.keycode == ALLEGRO_KEY_W && true){
                        cCobra.y1 -= 30;
                    }else if(ev.keyboard.keycode == ALLEGRO_KEY_S && true ){
                        cCobra.y1 += 30;
                    }else if(ev.keyboard.keycode == ALLEGRO_KEY_A && true){
                        cCobra.x1 -= 30;
                    }else if(ev.keyboard.keycode == ALLEGRO_KEY_D && true){
                        cCobra.x1 += 30;
                    }else if(ev.keyboard.keycode == ALLEGRO_KEY_C){
                        break;
                    }
        }
        if (cCobra.x1 < 0 || cCobra.x1 > x || cCobra.y1 < 0 || cCobra.y1> y){
            break;
        }
        */
    }

    //al_destroy_bitmap(maca);
    //al_destroy_bitmap(bg);
    al_destroy_display(janela);
    al_destroy_event_queue(fEventos);
}
