#include <stdio.h>
#include "turtle.h"

void sierpinski (double size);

void sierpinski (double size)
{
    if (size<=32)
    {
        t_forward(size);
        t_turnLeft(120);
        t_forward(size);
        t_turnLeft(120);
        t_forward(size/2);
        t_turnLeft(120);
        t_forward(size/2);
        t_turnRight(120);
        t_forward(size/2);
        t_turnRight(120);
        t_forward(size/2);
        t_turnLeft(120);
        t_forward(size/2);
    }
    else
    {
        sierpinski(size/2);
        t_turnLeft(120);
        t_penUp();
        t_forward(size/2);
        t_penDown();
        sierpinski(size/2);
        t_turnRight(120);
        t_penUp();
        t_forward(size/2);
        t_penDown();
        t_turnRight(120);
        sierpinski(size/2);
        t_penUp();
        t_forward(size/2);
        t_penDown();
    }
}

int main(int argc, char ** argv)
{
    if (t_init(800,600,window)!=0) puts("Init error");
    else {
        t_autoframeOff();
        t_moveSpeed(50);
        t_turnSpeed(0);
        t_moveTo(50,590);
        t_setAngle(90);
        sierpinski(675);
        t_frame();
        t_saveBMP("sierpinski.bmp");
        t_idle();
    }
}
