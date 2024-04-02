#include <iostream>
#include <allegro.h>
#include <allegro_primitives.h>
#include <conio.h>

using namespace std;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fEventos = NULL;
ALLEGRO_EVENT ev;

struct RETANGULO {
    float x1,y1,w,h,traco;
    ALLEGRO_COLOR cor;

    void desenhaRetangulo(RETANGULO r) {
    if (r.traco == 0){
        al_draw_filled_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor);
    }else{
        al_draw_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor,r.traco);
    }
}
};


void desenhaRetangulo(RETANGULO r) {
    if (r.traco == 0){
        al_draw_filled_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor);
    }else{
        al_draw_rectangle(r.x1,r.y1,r.x1+r.w,r.y1+r.h,r.cor,r.traco);
    }
}

int main(){
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    janela = al_create_display(800, 600);

    int x=0;
    int y=0;

    al_clear_to_color(al_map_rgb(255,255,255));

    RETANGULO r = {600,80,15,15, 10, al_map_rgb(0,255,0)};

    for(y = 0; y < 600; y += 20){
        for(x = 0; x < 800; x+= 20){
         desenhaRetangulo(r);

         r.x1 = x;
        }
        r.y1 = y;
    }
    al_flip_display();

    getch();

    al_clear_to_color(al_map_rgb(255,255,255));

    al_flip_display();
    al_rest(5);
}
