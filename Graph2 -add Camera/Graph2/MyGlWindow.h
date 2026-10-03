#pragma once
#include <iostream>
#include "GL/gl3w.h"
#include <string>
#include "Loader.h"

#include "ColorCube.h"
#include "Viewer.h"
#include "Model.h"
#include <glm/gtc/type_ptr.hpp> //value_ptrd

class MyGlWindow
{
public:
	MyGlWindow(int w, int h);
	ColorCube* m_cube;
	Viewer* m_viewer;
	
	void draw();
	void setSize(int w, int h) { m_width = w; m_height = h;}
	void setAspect(float r) { m_viewer->setAspectRatio(r); }
private:
	int m_width;
	int m_height;
	Model m_model;

	void initialize();
	
};