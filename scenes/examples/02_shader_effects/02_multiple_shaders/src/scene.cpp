#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	/** Load 2 different shaders (same vertex shader, but different fragment shader) */
	GLuint const shader_1 = opengl_load_shader("shaders/shader_quad_1/vert.glsl", "shaders/shader_quad_1/frag.glsl");
	GLuint const shader_2 = opengl_load_shader("shaders/shader_quad_2/vert.glsl", "shaders/shader_quad_2/frag.glsl");

	/** Create a unique quad mesh used for two different mesh_drawable */
	mesh quad_mesh = mesh_primitive_quadrangle();

	quad_1.initialize(quad_mesh, "Quad1");
	quad_2.initialize(quad_mesh, "Quad2");
	quad_2.transform.translation = { 0,0,1 };

	// Associate two different shaders to quad_1 and quad_2 (*)
	quad_1.shader = shader_1;
	quad_2.shader = shader_2;


	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
}



void scene_structure::display()
{
	// Display the two quad the same way
	draw(quad_1, environment);
	draw(quad_2, environment);
	/** The visual appearance of the two quads is different as they are associated to different shaders*/


	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);


}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
}


