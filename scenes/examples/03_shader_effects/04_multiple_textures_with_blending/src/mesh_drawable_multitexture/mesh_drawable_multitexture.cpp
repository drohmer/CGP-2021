#include "mesh_drawable_multitexture.hpp"

using namespace cgp;

// Adapt the draw function for a mesh_drawable_multitexture
void draw(mesh_drawable_multitexture const& drawable, scene_environment_basic const& environment)
{
	// Reuse the same draw function than a mesh_drawable, but send an additional uniform for the second texture


	if (drawable.number_triangles == 0) return;

	// Setup shader
	assert_cgp(drawable.shader != 0, "Try to draw mesh_drawable without shader [name:" + drawable.name + "]");
	assert_cgp(drawable.texture != 0, "Try to draw mesh_drawable without texture [name:" + drawable.name + "]");
	glUseProgram(drawable.shader); opengl_check;

	opengl_uniform(drawable.shader, environment);
	opengl_uniform(drawable.shader, drawable.shading);
	opengl_uniform(drawable.shader, "model", drawable.transform.matrix());

	// Set the two textures
	glActiveTexture(GL_TEXTURE0); opengl_check;
	glBindTexture(GL_TEXTURE_2D, drawable.texture); opengl_check;
	opengl_uniform(drawable.shader, "image_texture", 0);  opengl_check;

	glActiveTexture(GL_TEXTURE1); opengl_check; // the additional texture (*)
	glBindTexture(GL_TEXTURE_2D, drawable.texture_2); opengl_check;
	opengl_uniform(drawable.shader, "image_texture_2", 1);  opengl_check; // the second texture is called "image_texture_2" in the shader in this case

	// Standard call function
	assert_cgp(drawable.number_triangles > 0, "Try to draw mesh_drawable with 0 triangles [name:" + drawable.name + "]"); opengl_check;
	glBindVertexArray(drawable.vao);   opengl_check;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.vbo.at("index")); opengl_check;
	glDrawElements(GL_TRIANGLES, GLsizei(drawable.number_triangles * 3), GL_UNSIGNED_INT, nullptr); opengl_check;


	glBindVertexArray(0);

	// Clean the two textures binding to avoid any side effect after this draw
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}