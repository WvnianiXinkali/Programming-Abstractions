/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include <cmath>
#include "simpio.h"
#include "console.h"
using namespace std;

void sirpenskiTriangle();
void drawSirpenski(GWindow& window, double startX, double startY, double edgeLenght, int fractalOrder);
void drawTriangle(GWindow& window, double startX, double startY, double edgeLenght);

int main() {
    sirpenskiTriangle();
    return 0;
}

void sirpenskiTriangle(){
	double edgeLength = getReal("Enter edge length of a triangle: ");
	int fractalOrder = getInteger("Enter an order of a triangle: ");
	GWindow window(2*edgeLength,2*edgeLength);// (2*edgeLength, 2*edgeLength)
	window.setColor("GRAY");
	double width = window.getWidth();
      double height = window.getHeight();
	double startX = width / 2 - edgeLength / 2;
	double startY = height / 2 + edgeLength / (2 * sqrt(3.0));
    
	drawSirpenski(window, startX, startY, edgeLength, fractalOrder);
}

void drawSirpenski(GWindow& window, double startX, double startY, double edgeLength, int fractalOrder){ // draws whole system
	if(fractalOrder == 1){
		drawTriangle(window, startX, startY, edgeLength);
	} else {
		drawTriangle(window, startX, startY, edgeLength);
		drawSirpenski(window, startX, startY, edgeLength / 2, fractalOrder - 1);
		drawSirpenski(window, startX + edgeLength / 4, startY - (sqrt(3.0) / 4) * edgeLength, edgeLength / 2, fractalOrder - 1);
		drawSirpenski(window, startX  + edgeLength / 2, startY, edgeLength / 2, fractalOrder - 1);
		
	}
}
void drawTriangle(GWindow& window, double startX, double startY, double edgeLenght){ // draws 1 triangle
	GPoint p1 = window.drawPolarLine(startX, startY, edgeLenght, 60);
	GPoint p2 = window.drawPolarLine(p1, edgeLenght, 300);
	GPoint p3 = window.drawPolarLine(p2, edgeLenght, 180);
}

