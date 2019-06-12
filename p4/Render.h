#pragma once

#include "Init.h"

void renderSphere(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object a_Sphere);
///////////////////////////////////////////////////////////////////////////////
// Stellt ein Koordinatensystem dar
// Zeichne Achse f�r die Sonne
void renderAxisSun(glm::mat4x4 a_view, glm::mat4x4 a_projection, cg::GLSLProgram a_program);
// Zeichne Achse f�r den geneigten Planeten
void renderAxisPlanetSlope(glm::mat4x4 a_view, glm::mat4x4 a_projection, cg::GLSLProgram a_program);
// Initialisiere Achse f�r den geraden Planeten
void renderAxisPlanetStraight(glm::mat4x4 a_view, glm::mat4x4 a_projection, cg::GLSLProgram a_program);