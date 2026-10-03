#pragma once
#include "glm/glm.hpp"

class  Model
{
public:
	 Model();
	glm::mat4 getMatrix();

private:
	glm::mat4 model;
};

