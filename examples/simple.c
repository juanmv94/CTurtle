#include <stdio.h>
#include "turtle.h"

int main(int argc, char ** argv)
{
    if (t_init(640,480,window)!=0) puts("Init error");
    else {
        //We draw a red square
        t_turColor(RED);
        t_forward(200);
        t_turnRight(90);
        t_forward(200);
        t_turnRight(90);
        t_forward(200);
        t_turnRight(90);
        t_forward(200);
        
        //We move into the square and fill it blue
        t_penUp();
        t_turnRight(135);
        t_forward(60);
        t_turColor(BLUE);
        t_fill();
        
        //We draw an alpha green circle
        t_turColorAlpha(GREEN,120);
        t_wait(1);
        t_circle_filled(100);
        t_wait(1);
        
        //We hide the turtle and animate the background color
        //from black rbg(0,0,0) to white rgb(255,55,255);
        t_hideTurtle();
        t_wait(1);
        for (int i=0;i<256;i++)
            t_bkgColor(i,i,i);
        
        //We prevent the program to close
        t_idle();
    }
}
