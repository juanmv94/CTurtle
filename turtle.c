#include "SDL2/SDL.h"
#include "turtle.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265


typedef enum boolean {false,true} boolean;
typedef enum dir {up,down,left,right} dir;

typedef struct color {
    Uint8 b;
    Uint8 g;
    Uint8 r;
    Uint8 a;
} color;

Uint8 bkg_r=240,bkg_g=240,bkg_b=220;
color turCol= {0,0,0,255};
double penSize=1.75;
boolean lastCircle=false;
boolean autoframe=true;
boolean penDown=true;
boolean tur_visibility=true;
double tur_angle=0;
penMode tur_penMode=plot;
double tur_moveSpeed=4;
double tur_turnSpeed=20;
dir tur_d=up;

int scr_w,scr_h;
double tur_x,tur_y;

SDL_Window * SDLwindow;
SDL_Renderer * renderer;
int bitmapSize;
color * bitmap;
int fillmapSize;
boolean * fillmap;
color tur_raw[384];
SDL_Texture* tur_tex;
SDL_Rect tur_rect;
int bitmap_pitch;
SDL_Texture* bitmap_tex;
//SDL_Surface * turtle;
SDL_Surface *screenShot;

#define IN_LIMITS(X,Y) X<scr_w && X>=0 && Y<scr_h && Y>=0
#define IN_LIMITS2(X,Y) X<(scr_w-1) && X>0 && Y<(scr_h-1) && Y>0

const unsigned int turtleRawData[384] =
{
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000,
    0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000,
    0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF, 0x00FFFFFF,
    0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF,
    0x00FFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00FFFFFF,
    0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
    0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000,
    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
};

double min(double a,double b)
{
    return (a<=b) ? a : b;
}

double max(double a,double b)
{
    return (a>=b) ? a : b;
}

double abs_d(double n)
{
    return (n>=0) ? n : -n;
}

double deg(double rad)
{
    return rad*180/PI;
}

double rad(double deg)
{
    return deg*PI/180;
}

void lockSurface(SDL_Surface * surface)
{
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
}

void unlockSurface(SDL_Surface * surface)
{
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
}

void t_close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free(bitmap);
    SDL_DestroyTexture(bitmap_tex);
    SDL_DestroyTexture(tur_tex);
    SDL_FreeSurface(screenShot);
    SDL_Quit();
}

void frame(boolean update)
{
    SDL_Event event;
    SDL_Delay(10);
    SDL_PollEvent(&event);
    if ((event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_CLOSE) ||
            (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)) {
        t_close();
        exit(0);
    }

    if (update)
    {
        SDL_SetRenderDrawColor(renderer, bkg_r, bkg_g, bkg_b, 255);
        SDL_RenderClear(renderer);

        SDL_UpdateTexture(bitmap_tex,NULL,bitmap,bitmap_pitch);
        SDL_RenderCopy(renderer, bitmap_tex, NULL, NULL);
        if (tur_visibility)
        {
            tur_rect.x=tur_x-6;
            tur_rect.y=tur_y-9;
            SDL_RenderCopyEx(renderer,tur_tex,NULL,&tur_rect,tur_angle,NULL,SDL_FLIP_NONE);
        }
        SDL_RenderPresent(renderer);
    }
}

void t_frame()
{
    frame(true);
}

void frameSpeed(double prop)
{
    static double cont=0;
    if (tur_moveSpeed==0) return;
    if (prop>1 || prop<-1) prop=1/prop;
    double adv=sqrt(1+pow(prop,2));
    cont+=adv;
    if (cont>=tur_moveSpeed)
    {
        cont-=tur_moveSpeed;
        frame(true);
    }
    while (cont>=tur_moveSpeed)
    {
        cont-=tur_moveSpeed;
        frame(false);
    }

}

void t_setAngle(double angle)
{
    double newAngle=fmod(angle,360);
    if (newAngle<=0) newAngle+=360;
//Animation
    if (tur_turnSpeed!=0)
    {
        double dif=tur_angle-newAngle;
        if (dif<0) dif+=360;
        if (dif<=180)
        {
            while (dif>=tur_turnSpeed)
            {
                dif-=tur_turnSpeed;
                tur_angle-=tur_turnSpeed;
                if (tur_angle<=0) tur_angle+=360;
                frame(true);
            }
        }
        else
        {
            while (dif<=(360-tur_turnSpeed))
            {
                dif+=tur_turnSpeed;
                tur_angle=fmod(tur_angle+tur_turnSpeed,360);
                frame(true);
            }
        }
    }
    tur_angle=newAngle;
    if (autoframe) frame(true);
}

void getDirection(boolean inv)
{
    if (tur_angle<=45 || tur_angle>315)
        tur_d=(inv) ? down : up;
    else if (tur_angle<=135 && tur_angle>45)
        tur_d=(inv) ? left : right;
    else if (tur_angle<=225 && tur_angle>135)
        tur_d=(inv) ? up : down;
    else
        tur_d=(inv) ? right : left;
}

void t_turnRight(double angle)
{
    t_setAngle(tur_angle+angle);
}

void t_turnLeft(double angle)
{
    t_setAngle(tur_angle-angle);
}

void t_bkgColor(unsigned char backgroundColorRed, unsigned char backgroundColorGreen, unsigned char backgroundColorBlue)
{
    bkg_r=backgroundColorRed;
    bkg_g=backgroundColorGreen;
    bkg_b=backgroundColorBlue;
    if (autoframe) frame(true);
}

void t_turColorAlpha(unsigned char turtleColorRed, unsigned char turtleColorGreen, unsigned char turtleColorBlue, unsigned char turtleColorAlpha)
{
    turCol.r=turtleColorRed;
    turCol.g=turtleColorGreen;
    turCol.b=turtleColorBlue;
    turCol.a=turtleColorAlpha;
    for (int i=0; i<384; i++)
        if (turtleRawData[i]==0)
            tur_raw[i]=turCol;
    SDL_UpdateTexture(tur_tex,NULL,tur_raw,16*4);
    if (autoframe) frame(true);
    lastCircle=false;
}

void t_turColor(unsigned char turtleColorRed, unsigned char turtleColorGreen, unsigned char turtleColorBlue)
{
    t_turColorAlpha(turtleColorRed, turtleColorGreen, turtleColorBlue, 255);
}

int t_init(int width, int heigth, screenMode sm)
{
    if (SDL_Init(SDL_INIT_VIDEO)) return -1;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_ShowCursor(SDL_DISABLE);
    SDLwindow = SDL_CreateWindow("C Turtle",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, heigth, (sm==fullscreen) ? SDL_WINDOW_FULLSCREEN : 0);
    if (SDLwindow==NULL) return -1;
    SDL_GetWindowSize(SDLwindow,&scr_w,&scr_h);
    tur_rect.h=18;
    tur_rect.w=12;
    tur_x=scr_w/2;
    tur_y=scr_h/2;
    bitmap_pitch=scr_w*sizeof(color);
    bitmapSize=bitmap_pitch*scr_h;
    bitmap=calloc(bitmapSize,1);
    fillmapSize=scr_w*scr_h*sizeof(boolean);
    fillmap=malloc(fillmapSize);
    screenShot=SDL_CreateRGBSurfaceWithFormat(0,scr_w,scr_h,24,SDL_PIXELFORMAT_BGR24);
    renderer = SDL_CreateRenderer(SDLwindow, -1, 0);
    bitmap_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, scr_w, scr_h);
    SDL_SetTextureBlendMode( bitmap_tex, SDL_BLENDMODE_BLEND );
    tur_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 16, 24);
    SDL_SetTextureBlendMode( tur_tex, SDL_BLENDMODE_BLEND );
    memcpy(tur_raw,turtleRawData,384*4);
    t_turColor(0,0,0);
    return 0;
}

void t_wait(double seconds)
{
    Uint32 ini=SDL_GetTicks();
    do {
        frame(false);
    }
    while (((SDL_GetTicks()-ini)*0.001)<seconds);
}

void t_idle()
{
    for (;;) frame(false);
}

int t_saveBMP(char * filename)
{
    lockSurface(screenShot);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_BGR24, screenShot->pixels, screenShot->pitch);
    unlockSurface(screenShot);
    return SDL_SaveBMP(screenShot, filename);
}


color* get_pixel(int x, int y)
{
    return bitmap+(x+y*scr_w);
}


void plot_pixel(int x, int y, color pixel)
{
    if (pixel.a>0 && IN_LIMITS(x,y))
    {
        color* original=get_pixel(x,y);
        switch (tur_penMode)
        {
        case plot:
            original->r = (pixel.r * pixel.a / 255) + (original->r * original->a * (255 - pixel.a) / (255*255));
            original->g = (pixel.g * pixel.a / 255) + (original->g * original->a * (255 - pixel.a) / (255*255));
            original->b = (pixel.b * pixel.a / 255) + (original->b * original->a * (255 - pixel.a) / (255*255));
            original->a = pixel.a + (original->a * (255 - pixel.a) / 255);
            original->r=original->r*255/original->a;
            original->g=original->g*255/original->a;
            original->b=original->b*255/original->a;
            break;
        case erase:
            original->a=(turCol.a >= original->a) ? 0 : original->a-turCol.a;
            break;
        case wtf:
            original->r=rand();
            original->g=rand();
            original->b=rand();
            original->a = pixel.a + (original->a * (255 - pixel.a) / 255);
            break;
        }
    }
}

color pixel_mult_alpha(color pixel, double mult)
{
    pixel.a=mult*pixel.a;
    return pixel;
}

//Xiaolin Wu's line algorithm (uncompleted and left unused)
/*
void hpixel(double x, int y, color pixel)
{
    int inix=floor(x);
    double resto=x-inix;
    plot_pixel(inix,y,pixel_mult_alpha(pixel,1-resto));
    plot_pixel(inix+1,y,pixel_mult_alpha(pixel,resto));
}

void line_v_inc(double x1, double y1, double x2, double y2)
{
    double difx=x2-x1;
    double dify=y2-y1;
    int iniy=floor(y1);
    int endy=ceil(y2);
    hpixel(x1,iniy,pixel_mult_alpha(turCol,1-(y1-iniy)));
    double npix=1;
    for (int i=iniy+1; i<endy; i++)
    {
        hpixel((npix++)/dify*difx+x1,i,turCol);
    }
    hpixel(x2,endy,pixel_mult_alpha(turCol,1-(endy-y2)));
    frame(true);
}
*/

boolean circle_filled_pixel_code(int i, int j, double center_x, double center_y, double r, double rr)
{
    double val=pow(i - center_x, 2) + pow(j - center_y, 2) - rr;
    if (val<= r*2)
    {
        double mult=min(1,(r*2-val)/(r*2));
        plot_pixel(i, j, pixel_mult_alpha(turCol,mult));
        return (mult==1) ? true : false;
    }
    return false;
}

void line_pixel_code(double x1, double y1, double x2, double y2, int i, int j , double w, double h, double prop ,double d, double r, double rr)
{
//Calculamos distancia a recta
    double dist=abs_d((w*(i-x1)+h*(j-y1))/sqrt(pow(w,2)+pow(h,2)));

    double val_lim1=(i-x1)*prop+(j-y1);
    double val_lim2=(i-x2)*prop+(j-y2);
    if (dist<= d)
    {
        if (max(val_lim1,val_lim2)>=0 && min(val_lim1,val_lim2)<=0)
            plot_pixel(i, j, pixel_mult_alpha(turCol,min(1,d-dist)));
        else if (circle_filled_pixel_code(i,j,x2,y2,r,rr)==false && lastCircle==false);
            circle_filled_pixel_code(i,j,x1,y1,r,rr);
    }
}

void t_circle_filled(double r)
{
    double rr = pow(r, 2);
    int r_ceil=ceil(r+1);
    for (int i = tur_x - r_ceil; i <= tur_x + r_ceil; i++)
        for (int j = tur_y - r_ceil; j <= tur_y + r_ceil; j++)
        {
            circle_filled_pixel_code(i,j,tur_x,tur_y,r,rr);
        }
    if (autoframe) frame(true);
}

void t_circle(double r)
{
    double rr = pow(r, 2);
    int r_ceil=ceil(r+penSize/2+1);
    double ps=penSize+1;
    for (int i = tur_x - r_ceil; i <= tur_x + r_ceil; i++)
        for (int j = tur_y - r_ceil; j <= tur_y + r_ceil; j++)
        {
            double val=abs_d(pow(i - tur_x, 2) + pow(j - tur_y, 2) - rr);
            if (val<= r*ps)
                plot_pixel(i, j, pixel_mult_alpha(turCol,min(1,(r*ps-val)/(r*ps))));
        }
    if (autoframe) frame(true);
}

void line(double x1, double y1, double x2, double y2, boolean needTurn)
{
    double d=(penSize+1)/2;
    double r=d-1;
    double rr = pow(r, 2);
    int r_ceil=ceil(d);
    int ji=0;
    double w=(y2-y1);
    double h=-(x2-x1);
    double prop= (w==0) ? -h/0.00001 : -h/w;
    if (needTurn)
    {
        double angle=-deg(atan(prop));
        if (w>=0) angle+=180;
        t_setAngle(angle);
        getDirection(false);
    }
    switch(tur_d) {
    case up:
        for (int j = y1 + r_ceil; j >= y2- r_ceil; j--)
        {
            for (int i = min(x1,x2) - r_ceil; i <= max(x1,x2) + r_ceil; i++)
            {
                line_pixel_code(x1,y1,x2,y2,i,j,w,h,prop,d,r,rr);
            }
            if (j>=y2 && j<=y1)
            {
                tur_x=-prop*(ji++)+x1;
                tur_y=j;
                frameSpeed(prop);
            }
        }
        break;
    case down:
        for (int j = y1- r_ceil; j <= y2 + r_ceil; j++)
        {
            for (int i = min(x1,x2) - r_ceil; i <= max(x1,x2) + r_ceil; i++)
            {
                line_pixel_code(x1,y1,x2,y2,i,j,w,h,prop,d,r,rr);
            }
            if (j>=y1 && j<=y2)
            {
                tur_x=prop*(ji++)+x1;
                tur_y=j;
                frameSpeed(prop);
            }
        }
        break;
    case right:
        for (int i = x1 - r_ceil; i <= x2 + r_ceil; i++)
        {
            for (int j = min(y1,y2)- r_ceil; j <= max(y1,y2) + r_ceil; j++)
            {
                line_pixel_code(x1,y1,x2,y2,i,j,w,h,prop,d,r,rr);
            }
            if (i>=x1 && i<=x2)
            {
                tur_x=i;
                tur_y=(ji++)/prop+y1;
                frameSpeed(prop);
            }
        }
        break;
    case left:
        for (int i = x1 + r_ceil; i >= x2 - r_ceil; i--)
        {
            for (int j = min(y1,y2)- r_ceil; j <= max(y1,y2) + r_ceil; j++)
            {
                line_pixel_code(x1,y1,x2,y2,i,j,w,h,prop,d,r,rr);
            }
            if (i>=x2 && i<=x1)
            {
                tur_x=i;
                tur_y=-(ji++)/prop+y1;
                frameSpeed(prop);
            }
        }
        break;
    }
    tur_x=x2;
    tur_y=y2;
    lastCircle=true;
    if (autoframe) frame(true);
}

void move(double x1, double y1, double x2, double y2, boolean needTurn)
{
    int ji=0;
    double w=(y2-y1);
    double h=-(x2-x1);
    double prop= (w==0) ? -h/0.00001 : -h/w;
    if (needTurn)
    {
        double angle=-deg(atan(prop));
        if (w>=0) angle+=180;
        t_setAngle(angle);
        getDirection(false);
    }
    switch(tur_d) {
    case up:

        for (int j=y1; j>=y2; j--)
        {
            tur_x=-prop*(ji++)+x1;
            tur_y=j;
            frameSpeed(prop);
        }
        break;
    case down:

        for (int j=y1; j<=y2; j++)
        {
            tur_x=prop*(ji++)+x1;
            tur_y=j;
            frameSpeed(prop);
        }
        break;
    case right:

        for(int i=x1; i<=x2; i++)
        {
            tur_x=i;
            tur_y=(ji++)/prop+y1;
            frameSpeed(prop);
        }
        break;
    case left:
        for(int i=x1; i>=x2; i--)
        {
            tur_x=i;
            tur_y=-(ji++)/prop+y1;
            frameSpeed(prop);
        }
        break;
    }
    tur_x=x2;
    tur_y=y2;
    lastCircle=false;
}

void goTo(double x, double y, boolean needTurn)
{
    if (penDown) line(tur_x,tur_y,x,y,needTurn);
    else move(tur_x,tur_y,x,y,needTurn);
}

//Checks if a pixels hasn't been previously filled, and sets it to filled
boolean fillFilled(int x,int y)
{
    boolean* v=fillmap+x+y*scr_w;
    boolean res=*v;
    *v=false;
    return res;
}

void fillAlphaSetColor(color* c)
{
    Uint8 ai=255-c->a;
    c->r=(c->r*c->a+turCol.r*ai)/255;
    c->g=(c->g*c->a+turCol.g*ai)/255;
    c->b=(c->b*c->a+turCol.b*ai)/255;
    c->a=(255*c->a+turCol.a*ai)/255;
}

#define FILLALPHACHECK c->a < turCol.a

void fillAlpha(int x,int y)
{
    color* c=get_pixel(x,y);
    memset(fillmap,true,fillmapSize);
    if(FILLALPHACHECK) {

        int PixelArray[scr_h*scr_w];

        PixelArray[0] = (y << 16) + x;
        int Arraysize = 1;

        fillAlphaSetColor(c);

        while (Arraysize > 0) {
            Arraysize--;
            x = PixelArray[0] & 0xffff;
            y = (PixelArray[0] >> 16) & 0xffff;

            PixelArray[0] = PixelArray[Arraysize];

            if (IN_LIMITS2(x,y)) {
                c=get_pixel(x-1,y);
                if (fillFilled(x-1,y) && FILLALPHACHECK) {
                    fillAlphaSetColor(c);
                    PixelArray[Arraysize] = (y << 16) + x-1;
                    Arraysize++;
                }
                c=get_pixel(x,y-1);
                if (fillFilled(x,y-1) && FILLALPHACHECK) {
                    fillAlphaSetColor(c);
                    PixelArray[Arraysize] = ((y-1) << 16) + x;
                    Arraysize++;
                }
                c=get_pixel(x+1,y);
                if (fillFilled(x+1,y) && FILLALPHACHECK) {
                    fillAlphaSetColor(c);
                    PixelArray[Arraysize] = (y << 16) + x+1;
                    Arraysize++;
                }
                c=get_pixel(x,y+1);
                if (fillFilled(x,y+1) && FILLALPHACHECK) {
                    fillAlphaSetColor(c);
                    PixelArray[Arraysize] = ((y+1) << 16) + x;
                    Arraysize++;
                }
            }
        }
    }
}

void fillColorSetColor(color* c)
{
    Uint8 ai=255-turCol.a;
    c->r=(c->r*ai+turCol.r*turCol.a)/255;
    c->g=(c->g*ai+turCol.g*turCol.a)/255;
    c->b=(c->b*ai+turCol.b*turCol.a)/255;
}

#define FILLCOLORCHECK c->a!=0 && original.r==c->r && original.g==c->g && original.b==c->b

void fillColor(int x,int y,color original)
{
    color* c=get_pixel(x,y);
    memset(fillmap,true,fillmapSize);
    if(FILLCOLORCHECK) {

        int PixelArray[scr_h*scr_w];

        PixelArray[0] = (y << 16) + x;
        int Arraysize = 1;

        fillColorSetColor(c);

        while (Arraysize > 0) {
            Arraysize--;
            x = PixelArray[0] & 0xffff;
            y = (PixelArray[0] >> 16) & 0xffff;

            PixelArray[0] = PixelArray[Arraysize];

            if (IN_LIMITS2(x,y)) {
                c=get_pixel(x-1,y);
                if (fillFilled(x-1,y) && FILLCOLORCHECK) {
                    fillColorSetColor(c);
                    PixelArray[Arraysize] = (y << 16) + x-1;
                    Arraysize++;
                }
                c=get_pixel(x,y-1);
                if (fillFilled(x,y-1) && FILLCOLORCHECK) {
                    fillColorSetColor(c);
                    PixelArray[Arraysize] = ((y-1) << 16) + x;
                    Arraysize++;
                }
                c=get_pixel(x+1,y);
                if (fillFilled(x+1,y) && FILLCOLORCHECK) {
                    fillColorSetColor(c);
                    PixelArray[Arraysize] = (y << 16) + x+1;
                    Arraysize++;
                }
                c=get_pixel(x,y+1);
                if (fillFilled(x,y+1) && FILLCOLORCHECK) {
                    fillColorSetColor(c);
                    PixelArray[Arraysize] = ((y+1) << 16) + x;
                    Arraysize++;
                }
            }
        }
    }
}


void t_fill()
{
    int x=round(tur_x);
    int y=round(tur_y);
    if (IN_LIMITS2(x,y))
    {
        color* c=get_pixel(x,y);
        if (c->r==turCol.r && c->g==turCol.g && c->b==turCol.b) return; //TODO remove
        if (c->a==0)
        {
            fillAlpha(x,y);
        }
        else
        {
            fillColor(x,y,*c);
        }
    }
}

void t_goTo(double x, double y)
{
    goTo(x,y,true);
}

void t_forward(double n)
{
    double radAng=rad(tur_angle);
    getDirection(n<0);
    goTo(tur_x+n*sin(radAng),tur_y-n*cos(radAng),false);
}

void t_backward(double n)
{
    t_forward(-n);
}

void t_penDown()
{
    penDown=true;
}

void t_penUp()
{
    penDown=false;
}

void t_speed(double speed)
{
    double s=(speed<0) ? 0 : speed;
    tur_moveSpeed=s;
    tur_turnSpeed=s*TURN_SPEED_PROP;
}

void t_moveSpeed(double speed)
{
    tur_moveSpeed=(speed<0) ? 0 : speed;
}

void t_turnSpeed(double speed)
{
    tur_turnSpeed=(speed<0) ? 0 : speed;
}

void t_penSize(double size)
{
    penSize=(size<0) ? 0 : size;
    lastCircle=false;
}

void t_penMode(penMode pm)
{
    if (tur_penMode!=pm &&
            pm>=plot &&     //First possible option
            pm<=wtf)    //Last possible option
    {
        tur_penMode=pm;
        lastCircle=false;
    }
}

void t_hideTurtle()
{
    tur_visibility=false;
    if (autoframe) frame(true);
}

void t_showTurtle()
{
    tur_visibility=true;
    if (autoframe) frame(true);
}

void t_autoframeOff()
{
    autoframe=false;
}

void t_autoframeOn()
{
    autoframe=true;
}

void t_moveTo(double x, double y)
{
    tur_x=x;
    tur_y=y;
    lastCircle=false;
    if (autoframe) frame(true);
}

void t_clear()
{
    memset(bitmap,0,bitmapSize);
    if (autoframe) frame(true);
}