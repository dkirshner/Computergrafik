#pragma once

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

//

//void renderY_AxisSun(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
//void renderY_AxisMoon(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderAxis(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);

void renderWireSphereSonne(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpherePlanetschief(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpherePlanetgrade(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon1(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon2(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon3(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon4(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon5(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon6(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon7(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon8(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon9(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon10(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon11(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon12(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
void renderWireSpheremoon13(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun);
