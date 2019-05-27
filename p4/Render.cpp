#include "Init.h"
#include "Render.h"

int Linienanzahl = 10;
float groesseSonne = 1.0f;
float groessePlanet = 0.3f;
float groesseMond = 0.1f;

void renderAxis(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisSun)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Y_AxisSun.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(Y_AxisSun.vao);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

/*void renderY_AxisMoon(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisMoon)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Y_AxisMoon.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(Y_AxisMoon.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}


void renderY_AxisMoonSlope(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Y_AxisMoonSlope)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Y_AxisMoonSlope.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(Y_AxisMoonSlope.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
*/
void renderWireSphereSonne(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Sonne)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Sonne.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(Sonne.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseSonne, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon1(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon1)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon1.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon1.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon2(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon2)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon2.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon2.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon3(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon3)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon3.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon3.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon4(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon4)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon4.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon4.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon5(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon5)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon5.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon5.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon6(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon6)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon6.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon6.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon7(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon7)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon7.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon7.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon8(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon8)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon8.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon8.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon9(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon9)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon9.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon9.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon10(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon10)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon10.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon10.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon11(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon11)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon11.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon11.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon12(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon12)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon12.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon12.vao);

	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon13(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object moon13)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon13.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon13.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groesseMond, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpherePlanetschief(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object Planetschief)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Planetschief.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(Planetschief.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groessePlanet, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpherePlanetgrade(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object PlanetGrade)
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * PlanetGrade.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(PlanetGrade.vao);


	//glLineWidth(1.0f);
	glutWireSphere(groessePlanet, Linienanzahl, Linienanzahl);
	//größe, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}