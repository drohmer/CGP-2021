#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	/** Load a shader that makes fully transparent fragments when alpha-channel of the texture is small */
	GLuint const shader_with_transparency = opengl_load_shader("shaders/transparency/vert.glsl","shaders/transparency/frag.glsl");

	trunk.initialize(mesh_load_file_obj("assets/trunk.obj"), "Trunk");
	trunk.texture = opengl_load_texture_image("assets/trunk.png");

	branches.initialize(mesh_load_file_obj("assets/branches.obj"), "Branches");
	branches.shading.color = { 0.45f, 0.41f, 0.34f }; // branches do not have textures

	foliage.initialize(mesh_load_file_obj("assets/foliage.obj"), "Foliage");
	foliage.texture = opengl_load_texture_image("assets/pine.png");
	foliage.shader = shader_with_transparency;     // set the shader handling transparency for the foliage
	foliage.shading.phong = { 0.4f, 0.6f, 0, 1 };  // remove specular effect for the billboard


	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.look_at({ 5,3,0 }, { 0,1.5,0 }, { 0,1,0 });
}



void scene_structure::display()
{
	environment.light = environment.camera.position();

	draw(trunk, environment);
	draw(branches, environment);

	if (gui.display_pines)
		draw(foliage, environment);

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Pines", &gui.display_pines);
}


