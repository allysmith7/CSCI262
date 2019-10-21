/*
 * mondrian.cpp
 *
 * Author: <your name here>
 *
 * Generate recursive pictures inspired by the art of Piet Mondrian.
 */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "mondrian.h"

using namespace std;

void Mondrian::_paint_recursive(Picture &picture, int left, int top, int right, int bottom) {
    // base case 1 - in case we made a zero width or height rectangle
	cout << "top: " << top << " bottom: " << bottom << " left: " << left << " right: " << right << endl;
	if ((bottom - top < 0) || (right - left < 0)) {
		return;
	}


    // base case 2 - rectangle is less than 35000 pixels
    if ((bottom - top) * (right - left) <= 70000) {
		_color_fill(picture, left, top, right, bottom);
		// adds lines around the box
		_draw_horizontal_line(picture, top, left, right - 1);
		_draw_horizontal_line(picture, bottom, left, right - 1);
		_draw_vertical_line(picture, left, top, bottom - 1);
		_draw_vertical_line(picture, right, top, bottom - 1);
    	return;
    }

    // otherwise, split the rectangle in two at random, paint the two
    // either vertically splits or horizontally splits
	if (bottom - top < right - left) {
		// horizontal
		int offset = (rand()%(right - left));
		_paint_recursive(picture, left, top, left + offset, bottom);
		_paint_recursive(picture, left + offset, top, right, bottom);
	} else {
		// vertical split
		int offset = (rand()%(bottom - top));
		_paint_recursive(picture, left, top, right, top + offset);
		_paint_recursive(picture, left, bottom - offset, right, bottom);
	}
}

void Mondrian::_color_fill(Picture &picture, int left, int top, int right, int bottom) {
    int r, g, b;
	r = g = b =255;

    /**
    int option = rand() % 4;
////     Options:
////     * 0 = white	r = 240, 	g = 240, 	b = 240;
////     * 1 = red		r = 255, 	g = 0, 		b = 0
////     * 2 = blue		r = 0,		g = 0, 		b = 128
////     * 3 = yellow	r = 255, 	g = 215, 	b = 0


    cout << option << endl;

    switch (option) {
    	case 0:
    		// white
    		r = 240;
    		g = 240;
    		b = 240;
    		break;
    	case 1:
    		// red
    		r = 255;
    		g = 0;
    		b = 0;
    		break;
		case 2:
			// blue
			r = 0;
			g = 0;
			b = 128;
			break;
    	case 3:
    		// yellow
    		r = 255;
    		g = 217;
    		b = 0;
    }
    */

	r = rand() % 64;
	g = rand() % 128;
	b = rand() % 255;

	for (int x = left; x <= right; x++) {
        for (int y = top; y <= bottom; y++) {
            picture.set(x, y, r, g, b);
        }
    }
}

// These are done for you to save time in lab
void Mondrian::_draw_horizontal_line(Picture &picture, int y, int left, int right) {
    for (int x = left; x <= right; x++) {
        picture.set(x, y, 0, 0, 0);
    }
}

void Mondrian::_draw_vertical_line(Picture &picture, int x, int top, int bottom) {
    for (int y = top; y <= bottom; y++) {
        picture.set(x, y, 0, 0, 0);
    }
}

void Mondrian::paint(string output_filename, int width, int height) {
    // get a new random seed each time
    srand(time(nullptr));

    // create a white picture
    Picture picture(width, height, 255, 255, 255);

    // put a frame around it
    _draw_horizontal_line(picture, 0, 0, width - 1);
    _draw_horizontal_line(picture, height - 1, 0, width - 1);
    _draw_vertical_line(picture, 0, 0, height - 1);
    _draw_vertical_line(picture, width - 1, 0, height - 1);

    // invoke our computer artist!
    _paint_recursive(picture, 1, 1, width - 2, height - 2);

    // save result
    picture.save(output_filename);
}
