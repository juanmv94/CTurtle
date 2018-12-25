#include <stdio.h>
#include "turtle.h"

void fern(int size, int sign);

void fern(int size, int sign)
{
    if (size<1) return;
    t_penSize(size/4);
    t_forward(size);
    t_turnRight(70*sign);
    fern(size/2,sign*-1);
    t_penSize(size/4);
    t_turnLeft(70*sign);
    t_forward(size);
    t_turnLeft(70*sign);
    fern(size/2,sign);
    t_penSize(size/4);
    t_turnRight(77*sign);
    fern(size-1,sign);
    t_turnRight(173*sign);
    t_penUp();
    t_forward(size*2);
    t_penDown();
    t_turnLeft(180);
}

int main(int argc, char ** argv)
{
    if (t_init(640,480,window)!=0) puts("Init error");
    else {
        t_autoframeOff();
        t_moveSpeed(200);
        t_turnSpeed(0);
        t_penUp();
        t_goTo(192,450);
        t_setAngle(0);
        t_penDown();
        t_turColor(0,60,0);
        fern(25,1);
        t_frame();
        t_saveBMP("fern.bmp");
        t_idle();
    }
}
