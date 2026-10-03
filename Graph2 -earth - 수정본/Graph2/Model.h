#pragma once
#include "glm/glm.hpp"

class  Model
{
public:
	 Model();
	 glm::mat4 GetFloorMatrix();
	 glm::mat4 GetOBJMatrix();

private:
	glm::mat4 floor_model;
	glm::mat4 obj_model;
};

