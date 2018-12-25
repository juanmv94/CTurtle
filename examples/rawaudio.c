#include <stdio.h>
#include "turtle.h"

unsigned char getsample(FILE* f)
{
    unsigned char c;
    if (fread(&c,1,1,f)==0) t_idle();
    return c;
}

int main(int argc, char ** argv)
{
    if (t_init(640,480,window)!=0) puts("Init error");
    else {
        FILE * rawaudio=fopen("rawaudio.raw","rb");
        if (rawaudio==NULL) puts("File error");
        else {
            t_speed(0);
            t_hideTurtle();
            t_autoframeOff();
            for (;;)
            {
                t_frame();
                t_clear();
                t_turColorAlpha(BLUE,100);
                t_moveTo(20,256);
                t_goTo(620,256);
                t_turColor(BLACK);
                t_moveTo(20,384-getsample(rawaudio));
                for (int i=0;i<600;i++)
                    t_goTo(20+i,384-getsample(rawaudio));
            }
        }
    }
}