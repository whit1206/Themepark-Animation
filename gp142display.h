#ifndef __GP142_DISPLAY_H__
#define __GP142_DISPLAY_H__

// GP142Display: Display that's been retrofitted to work with the
// C-centric GP142 libraries.

// Written by Shuichi Koga
// Sun May 16, 1999

// note: no support is given for this code, either by CSE143 or by
// me, Shuichi. If you ask really nicely and bring lots of cookies,
// I might be tempted into checking for errors. Otherwise....

// GP142Display Model: Under GP142, the center of the screen is considered
// to be position (0,0), so that is preserved under this display (see the
// GP142 docs for details).

// Colors
enum GP142Color 
{ Black, White, Red, Green, Blue, Yellow, Magenta, Cyan,
  Purple, NavyBlue, DustyPlum, IceBlue, Turquoise, Orange,
  Brown, Pink, Chalk, Gold, Peach, ForestGreen, SeaGreen,
  Olive, MedGray, LightGray, MaxColors };

// Events that this display can understand
enum GP142Event
{ Unknown, Mouse, Key, Periodic, Quit };

// Control over how quickly periodic events occur
enum GP142Periodic
{ Halt, SingleStep, Run, SendQuit };

// The actual display abstraction. Note that we do not support all of 
// the methods that are given as part of GP142.

class GP142Display
{
public:
        GP142Display();
        ~GP142Display();

        // Returns the display width
        int getWidth( );

        // Returns the display height
        int getHeight( );

        // Returns the maximum possible width
        int getMaxWidth();

        // Returns the maximum possible height
        int getMaxHeight();

        // Clears the screen to the specified color
        void clear( GP142Color color=Black );

        // Pauses for a number of milliseconds
        void pause( int time );

        // The following methods allow for control over input that one can get

        // Get the next event
        GP142Event getNextEvent(int& mouseX, int& mouseY, char& keyPress);

        // Sets whether or not to animate
        void setAnimation(GP142Periodic newPeriod);

        // Flushes the output queue of things to write out.
        void flush();


        // The following methods allow for writing characters to the screen.

        // Write a character at a given x and y coordinate
        void write( int x, int y, char c, GP142Color color=White, int pointSize=8);

        // Write a string at a given x and y coordinate
        // if the string does not fit on the line, it will wrap around the screen
        void write( int x, int y, const char *s, GP142Color color=White, int pointSize=8 );

        // Write an integer at a given x and y coordinate
        void write( int x, int y, int i, GP142Color color=White, int pointSize=8 );

        // The following methods allow for pixel manipulation.

        // Draws a pixel
        void drawPixel(int x, int y, GP142Color color=White);

        // Draws a line
        void drawLine(int x1, int y1, int x2, int y2, GP142Color color=White,
                                  int thickness=1);

        // Draws a rectangle
        void drawRectangle(int x1, int y1, int x2, int y2, GP142Color color=White,
                                                int thickness=1);

        // Draws a triangle
        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                                          GP142Color color=White, int thickness=1);

        // Draws an oval
        void drawOval(int x1, int y1, int x2, int y2, 
                                  GP142Color color=White, int thickness=1);

        // Draws a circle
        void drawCircle(int x, int y, int radius, GP142Color color=White);


private:
        int width, height; // width and height of the screen
        static bool initialized; // make sure only one GP142Display is ever made.
};


#endif