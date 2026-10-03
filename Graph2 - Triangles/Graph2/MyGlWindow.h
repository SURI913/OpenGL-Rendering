#pragma once
#include <iostream>
#include "GL/gl3w.h"
#include <string>
#include "Loader.h"

class MyGlWindow
{
public:
	MyGlWindow(int w, int h);
	void draw();
private:
	int m_width;
	int m_height;

	void setupBuffer();
};