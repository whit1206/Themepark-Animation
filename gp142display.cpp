#include "gp142display.h"
#include "gp142.h"
#include "gp142lib.h"
#include <iostream.h>

bool GP142Display::initialized=false;

#ifdef WINDOWS
// Structure used to keep around variables we need for initialization, 
// but the user shouldn't have to see.
struct GP142Globals {
        HINSTANCE hInstance, hPrevInstance;
        LPSTR lpCmdLine;
        int nShowCmd;
};

// Only one item of type Global needs to exist.
static GP142Globals global;

// We need to state that there exists a main() apriori.
void main();

// The following tries to hide as much as possible from the user. I'm not sure if 
// this'll work, but here goes nothing...

// As an aside, if this does work, it's much cleaner than the GP142 approach of 
// utilizing macros to do basically the same thing.

PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
        global.hInstance = hInstance;
        global.hPrevInstance = hPrevInstance;
        global.lpCmdLine = lpCmdLine;
        global.nShowCmd = nShowCmd;

        main();
        return 0;
}

#endif

GP142Display::GP142Display()
        : width(GP142_XMAX*2), height(GP142_YMAX*2)
{
        if (!initialized) 
        {
#ifdef WINDOWS
                GP142_open(global.hInstance, global.hPrevInstance, global.lpCmdLine,
                                        global.nShowCmd);
#else
                GP142_open();
#endif
                GP142_logging(LOG_OFF);
        }
        else
        {
#ifdef WINDOWS
                char result[80];
                GP142_gets("Error: Attempted to instantiate multiple GP142 displays", result);
#else
                cout << "Error: Attempted to instantiate multiple GP142 displays" << endl;
#endif
                exit(-1);
        }
}

GP142Display::~GP142Display()
{
        GP142_close();
}

// Returns the display width
int GP142Display::getWidth( )
{
        return width;
}

// Returns the display height
int GP142Display::getHeight( )
{
        return height;
}

// Returns the maximum possible width
int GP142Display::getMaxWidth( )
{
        return width/2;
}

// Returns the maximum possible height
int GP142Display::getMaxHeight( )
{
        return height/2;
}



// Clears the screen to the specified color
void GP142Display::clear( GP142Color color )
{
        GP142_flush();
        GP142_clear();
        drawRectangle(-width/2, -height/2, width/2, height/2, color, 0);
}

// Pauses for a number of milliseconds
void GP142Display::pause( int time )
{
#ifdef WINDOWS
        Sleep(time);
#elif defined(X11R6)
        usleep((unsigned long)time * 1000);
#endif
}

// Event handling

// handles arbitrary events
        // Get the next event
GP142Event GP142Display::getNextEvent(int& mouseX, int& mouseY, char& keyPress)
{
        int result = GP142_await_event(&mouseX, &mouseY, &keyPress);
        GP142Event event;

        switch(result)
        {
                case GP142_MOUSE: event = Mouse; break;
                case GP142_KBD:   event = Key; break;
                case GP142_PERIODIC: event = Periodic; break;
                case GP142_QUIT: event = Quit; break;
                default: event = Unknown;
        }

        return event;
}

// Sets whether or not to animate
void GP142Display::setAnimation(GP142Periodic newPeriod)
{
        int set;
        switch(newPeriod)
        {
          case Halt: 
	    set = ANI_HALT;
	    break;
	  case SingleStep: 
	    set = ANI_SINGLE_STEP;
	    break;
	  case Run: 
	    set = ANI_RUN;
	    break;
	  case SendQuit: 
	    set = ANI_QUIT;
	    break;
	  default:
	    break;
        }

        GP142_animate(set);
}

// Flushes the output queue of things to write out.
void GP142Display::flush()
{
        GP142_flush();
}



// The following methods allow for writing characters to the screen.

// Write a character at a given x and y coordinate
void GP142Display::write( int x, int y, char c, GP142Color color, int pointSize)
{
        GP142_printfXY((int)color, x, y, pointSize, "%c", c);
}

// Write a string at a given x and y coordinate
// if the string does not fit on the line, it will wrap around the screen
void GP142Display::write( int x, int y, const char *s, GP142Color color, int pointSize )
{
        GP142_printfXY((int)color, x, y, pointSize, "%s", s);
}

// Write an integer at a given x and y coordinate
void GP142Display::write( int x, int y, int i, GP142Color color, int pointSize )
{
        GP142_printfXY((int)color, x, y, pointSize, "%d", i);
}

// The following methods allow for pixel manipulation.

// Draws a pixel
void GP142Display::drawPixel(int x, int y, GP142Color color)
{
        GP142_pixelXY((int)color, x, y);
}

// Draws a line
void GP142Display::drawLine(int x1, int y1, int x2, int y2, GP142Color color,
                                                        int thickness)
{
        GP142_lineXY((int)color, x1, y1, x2, y2, thickness);
}

// Draws a rectangle
void GP142Display::drawRectangle(int x1, int y1, int x2, int y2, GP142Color color,
                                        int thickness)
{
        GP142_rectangleXY((int)color, x1,y1,x2,y2, thickness);
}

// Draws a triangle
void GP142Display::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                                  GP142Color color, int thickness)
{
        GP142_triangleXY((int)color, x1, y1, x2, y2, x3, y3, thickness);
}

// Draws an oval
void GP142Display::drawOval(int x1, int y1, int x2, int y2, 
                          GP142Color color, int thickness)
{
        GP142_ovalXY((int)color, x1, y1, x2, y2, thickness);
}

// Draws a circle
void GP142Display::drawCircle(int x, int y, int radius, GP142Color color)
{
        GP142_circleXY((int)color, x, y, radius);
}

