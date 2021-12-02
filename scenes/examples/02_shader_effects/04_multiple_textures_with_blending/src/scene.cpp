#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Set-up of the multi-texture model
	// ***************************************** //

	/** Load a shader that uses 2 textures */
	GLuint const shader = opengl_load_shader("shaders/multitexture/vert.glsl", "shaders/multitexture/frag.glsl");

	quad.initialize(mesh_primitive_quadrangle(), "quad_multitexture");

	// Set the two textures and the specific shader
	quad.texture   = opengl_load_texture_image("assets/brick.png");
	quad.texture_2 = opengl_load_texture_image("assets/crack.png");

	quad.shader = shader;



	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.look_at({ 0.5f,0.5f,3 }, { 0.5f,0,0 }, { 0,1,0 });
}



void scene_structure::display()
{
	environment.light = environment.camera.position();

	draw(quad, environment);

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
}


