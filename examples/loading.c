#include <stdio.h>
#include "turtle.h"
int main(int argc, char ** argv)
{
    if (t_init(128,128,window)!=0) puts("Init error");
    else {
        t_hideTurtle();
        t_moveSpeed(0);
        t_turnSpeed(0);
        t_penUp();
        t_forward(48);
        t_turnLeft(90);
        t_penDown();
        t_moveSpeed(10);
        t_bkgColor(WHITE);
        t_autoframeOff();
        for(;;)
        {
            double pensize=1;
            for (int  i=0; i<300; i++)
            {
                int v=(i>255) ? 255 : i;
                t_turColor(v,v,v);
                t_penSize(pensize);
                t_forward(8);
                t_turnLeft(10);
                pensize+=0.10;
            }
        }
    }
}
