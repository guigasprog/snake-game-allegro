#include <iostream>
#include <allegro.h>
#include <allegro_primitives.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fEventos = NULL;
ALLEGRO_EVENT ev;

struct RETANGULO {
    float x1,y1,w,h,traco;
    ALLEGRO_COLOR cor;
};


void desenhaRetangulo(RETANGULO r) {
    if (r.traco == 0){
        al_draw_filled_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor);
    }else{
        al_draw_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor,r.traco);
    }
}

bool colideRetangulo(RETANGULO r1, RETANGULO r2){
    if ( r2.x1+r2.w > r1.x1 &&
         r1.x1+r1.w > r2.x1 &&
         r2.y1+r2.h > r1.y1 &&
         r1.y1+r1.h > r2.y1   ){
        return true;
    } else {
        return false;
    }
}


int main(){

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    int x=800;
    int y=600;

    janela = al_create_display(x, y);
    fEventos = al_create_event_queue();

    al_register_event_source(fEventos, al_get_keyboard_event_source());


    ALLEGRO_COLOR cor_grama = al_map_rgb(1,200,0);
    ALLEGRO_COLOR cor_cobra = al_map_rgb(241, 94,255);
    ALLEGRO_COLOR cor_maca = al_map_rgb(255,0,0);

    int xm = rand() % x;
    int ym = rand() % y;

    RETANGULO cCobra = {float(x/2),float(y/2),30,30,0,cor_cobra};
    RETANGULO maca = {xm, ym, 30, 30, 0, cor_maca};

    bool tecla[4] = {true,false,false,false}; // 0w/1a/2s/3d
    bool gameover = false;
    while(!gameover){

        al_wait_for_event_timed(fEventos, &ev, 0.3);
        al_clear_to_color(cor_grama);
        desenhaRetangulo(maca);
        desenhaRetangulo(cCobra);
        al_flip_display();

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_W && !tecla[2]){
                tecla[0] = true;
                tecla[1] = false;
                tecla[2] = false;
                tecla[3] = false;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_S && !tecla[0]){
                tecla[0] = false;
                tecla[1] = false;
                tecla[2] = true;
                tecla[3] = false;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_A && !tecla[3]){
                tecla[0] = false;
                tecla[1] = true;
                tecla[2] = false;
                tecla[3] = false;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_D && !tecla[1]){
                tecla[0] = false;
                tecla[1] = false;
                tecla[2] = false;
                tecla[3] = true;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_C){
                gameover = true;
            }
        }
        if(tecla[0]){
            cCobra.y1 -= 15;
        }
        if(tecla[1]){
            cCobra.x1 -= 15;
        }
        if(tecla[2]){
            cCobra.y1 += 15;
        }
        if(tecla[3]){
            cCobra.x1 += 15;
        }
        if (cCobra.x1 < 0 || cCobra.x1 > x || cCobra.y1 < 0 || cCobra.y1> y){
            gameover = true;
        }

    }
    al_flip_display();
    al_rest(5);
}
