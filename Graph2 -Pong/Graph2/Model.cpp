#include "Model.h"

Model::Model() {
	//glm::mat4 model = scale * translate * rotate¡¦.
	model = glm::mat4(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0 ,0,0,1);
}

glm::mat4 Model::getMatrix() {
	return model;
}