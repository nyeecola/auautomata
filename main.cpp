#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include <iostream>
#include <fstream>
#include "backend/gofl.h"

#define FRAME_TIME 0.05

GOFL gofl;
fstream input_file, output_file;

/*
   Draws a grid on the screen using the global variable `gofl` and the #define `MAX_SIZE`.

   @cell_size :: the size of a single cell to be drawn on the screen 
   @offset_x  :: the margin to the left of the grid
   @offset_y  :: the margin to the top of the grid
 */
void draw_grid(int cell_size, int offset_x, int offset_y)
{
    int pos_y = 0;
    int pos_x = 0;
    int cell_color = FL_RED;
    for (int i = 0; i < MAX_SIZE ; i++)
    {
        pos_y = offset_y + i*cell_size;
        for (int j = 0; j < MAX_SIZE; j++)
        {
            pos_x = offset_x + j*cell_size;
            if (gofl.gofl_table[i][j]) cell_color = FL_WHITE;
            else cell_color = FL_RED;
            fl_rectf(pos_x, pos_y, cell_size, cell_size, cell_color);
            fl_color(FL_WHITE);
            fl_line(pos_x, offset_y, pos_x, offset_y + MAX_SIZE*cell_size);
        }
        fl_line(offset_x, pos_y, offset_x + MAX_SIZE*cell_size, pos_y);
    }
    pos_x += cell_size;
    pos_y += cell_size;
    fl_line(pos_x, offset_y, pos_x, offset_y + MAX_SIZE*cell_size);
    fl_line(offset_x, pos_y, offset_x + MAX_SIZE*cell_size, pos_y);
}

/*
   Updates the game and redraws the screen after a periodic delay of `FRAME_TIME` seconds.
 */ 
void update(void *)
{
    gofl.next_step();
    gofl.write_output(output_file);
    Fl::redraw();
    Fl::repeat_timeout(FRAME_TIME, update);
}

/*
   Drawing area, the draw() procedure is called once every frame.
 */
class Drawing : public Fl_Widget {
    void draw() {
        fl_push_clip(x(),y(),w(),h());
        fl_color(FL_DARK3);
        fl_rectf(x(),y(),w(),h());
        fl_push_matrix();
        fl_translate(x(),y());
        draw_grid(11, 11, 12);
        fl_pop_matrix();
        fl_pop_clip();
    }
    public:
    Drawing(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H) {}
};

/*
   Entry point.
 */
int main(int argc, char** argv) {

    // try to open input file
    // also creates an output file (maybe this will change later)
    // TODO: think about this
    {
        input_file.open("./backend/automata.in", ios::in | ios::binary);
        output_file.open("./backend/automata.out", ios::out | ios::binary);

        if (!(input_file.is_open() && output_file.is_open()))
        {
            cout << "Error on file read" << endl;
            exit(1);
        }
    }

    // read values from input_file to start the game of life
    gofl.set_values(input_file);

    // create window and drawing area
    // NOTE: we're using a software renderer
    Fl_Double_Window window(300,300);
    Drawing drawing(0,0,300,300);
    window.end();
    window.show(argc,argv);

    /*
        --------------------------------------------------
        TODO: find out where to put this, not sure yet.
        --------------------------------------------------

        output_file.close();
        input_file.close();
     */

    // schedule a periodic update after a delay of `FRAME_TIME` seconds
    Fl::add_timeout(FRAME_TIME, update);

    return Fl::run();
}
