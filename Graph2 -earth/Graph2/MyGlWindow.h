#pragma once
#include <iostream>
#include "GL/gl3w.h"
#include <string>
#include "Loader.h"

#include "Object.h"
#include "Viewer.h"
#include "Model.h"
#include <glm/gtc/type_ptr.hpp> //value_ptrd
#include "ColorCube.h";

class MyGlWindow
{
public:
	MyGlWindow(int w, int h);
	Earth* m_object;
	ColorCube* m_Cube;
	Floor* m_floor;
	Viewer* m_viewer;
	
	void draw();
	void setSize(int w, int h) { m_width = w; m_height = h;}
	void setAspect(float r) { m_viewer->setAspectRatio(r); }
private:
	int m_width;
	int m_height;
	Model* m_model;

	void initialize();
	
};