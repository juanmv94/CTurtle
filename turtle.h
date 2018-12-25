#ifndef TURTLE_H
#define TURTLE_H

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////
//SOME COLOR DEFINITIONS FOR t_turColor AND t_bkgColor//
////////////////////////////////////////////////////////
#define WHITE 255,255,255
#define BLACK 0,0,0
#define GRAY75 191,191,191
#define GRAY50 127,127,127
#define GRAY25 63,63,63
    
#define RED 255,0,0
#define BLUE 0,0,255
#define TURQUOISE 0,255,255
#define GREEN 0,255,0
#define YELLOW 255,255,0
#define ORANGE 255,128,0
#define PINK 255,0,255
#define VIOLET 127,0,127

/**
 * Screen modes: \window or \fullscreen
 */
typedef enum screenMode {window,fullscreen} screenMode;

/**
 * Pen modes:
 * \plot for drawing with turtle color (default),
 * \erase for... guess what,
 * \wtf for random coloured pixels
 */
typedef enum penMode {plot,erase,wtf} penMode;

/**
 * Starts the C Turtle library. You must specify a \screenMode between
 * \window and \fullscreen, and the resolution.
 * If you set an unsupported fullscreen resolution, a diferent supported
 * resolution will be set.
 * Turtle will be placed at the center of the screen with \plot penMode,
 * pen down, default speeds, black color, and automatic frame generation.
 */
int t_init(int width, int heigth, screenMode sm);

/**
 * Closes the C Turtle library. This closes the C Turtle screen.
 */
void t_close();

///////////////
//Pen methods//
///////////////

/**
 * Allows you to move the turtle without drawing
 */
void t_penUp();
/**
 * Puts the pen down again after a \t_penUp() call, so you can
 * continue drawing
 */
void t_penDown();
/**
 * Sets a pen mode:
 * \plot for drawing with turtle color (default),
 * \erase for... guess what,
 * \wtf for random coloured pixels
 */
void t_penMode(penMode pm);
/**
 * Sets the pen size (line/circle thickness)
 */
void t_penSize(double size);
/**
 * Turns the turtle \angle degrees to the right
 */
void t_turnRight(double angle);
/**
 * Turns the turtle \angle degrees to the left
 */
void t_turnLeft(double angle);
/**
 * Sets the turtle \angle in degrees.
 * Turtle looks up at 0º, and angle is clockwise
 */
void t_setAngle(double angle);

/**
 * Moves the turtle forward \n pixels
 * (in its proportion for the different angles).
 * If pen is down (default) turtle will draw a line
 */
void t_forward(double n);
/**
 * Moves the turtle backward \n pixels
 * (in its proportion for the different angles).
 * If pen is down (default) turtle will draw a line
 */
void t_backward(double n);
/**
 * Moves the turtle to the given coordinate.
 * This makes the turtle turn first, and then move forward.
 * If pen is down (default) turtle will draw a line
 */
void t_goTo(double x, double y);
/**
 * This moves the turtle to the given coordinate without drawing
 * (even with pen down) and keeping the current turtle angle.
 */
void t_moveTo(double x, double y);

/**
 * Draws a circle filled with the turtle color with its center at the
 * turtle position, and radius \r (pixels)
 */
void t_circle_filled(double r);
/**
 * Draws a circle with its center at the
 * turtle position, and radius \r (pixels).
 */
void t_circle(double r);

/**
 * Fills with turtle color at the turtle position.
 * It's like the pain bucket from MSPaint.
 */
void t_fill();
/**
 * Clears the screen
 */
void t_clear();

/////////////////////
//Speeds and delays//
/////////////////////

//This is the dafault turn/move speed proportion for \t_speed
#define TURN_SPEED_PROP 5

/**
 * Sets the \speed at which the turtle moves and rotates
 */
void t_speed(double speed);
/**
 * Sets the \speed at which the turtle moves (pixels per frame)
 */
void t_moveSpeed(double speed);
/**
 * Sets the \speed at which the turtle rotates (degrees per frame)
 */
void t_turnSpeed(double speed);

/**
 * This disables the automatic frame generation after each C Turtle event
 * (Color changing, turn completed, move completed,...)
 * Then you can use the \t_frame() function to manually generate frames.
 * Keep in mind that unless turtle speed is set to 0, frames will
 * still be generated with the turtle movement
 */
void t_autoframeOff();
/**
 * This re-enables the automatic frame generation
 * after a \t_autoframeOff() call
 */
void t_autoframeOn();
/**
 * This generates a frame. This call is not necesary
 * unless you set \t_autoframeOff()
 */
void t_frame();
/**
 * Delay for the program in \seconds
 */
void t_wait(double seconds);
/**
 * You can call this at the end of your program to prevent the window to close.
 * The program will stay open until you press ESC or press the close button.
 */
void t_idle();

/**
 * Sets the background color.
 * You can use some of the predefined RGB values in turtle.h
 */
void t_bkgColor(unsigned char backgroundColorRed, unsigned char backgroundColorGreen, unsigned char backgroundColorBlue);
/**
 * Sets the turtle color.
 * You can use some of the predefined RGB values in turtle.h
 */
void t_turColor(unsigned char turtleColorRed, unsigned char turtleColorGreen, unsigned char turtleColorBlue);
/**
 * Sets the turtle color with alpha.
 * You can use some of the predefined RGB values in turtle.h
 * in addition to the alpha layer
 */
void t_turColorAlpha(unsigned char turtleColorRed, unsigned char turtleColorGreen, unsigned char turtleColorBlue, unsigned char turtleColorAlpha);
/**
 * If the turtle is to ugly for you, you can hide it.
 * Turtle will continue working as normal
 */
void t_hideTurtle();
/**
 * Shows the turtle again after \t_hideTurtle()
 */
void t_showTurtle();

/**
 * Saves the current screen to a BMP file
 */
int t_saveBMP(char * filename);
    
#ifdef __cplusplus
}
#endif

#endif /* TURTLE_H */

