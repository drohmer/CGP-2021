#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Set the second scene with the orthographic project (*)
	//*****************************************************
	environment_ortho.projection = camera_projection::orthographic(-1, 1, -1, 1, -1, 1);
	environment_ortho.camera.distance_to_center = 2.5f;
	environment_ortho.light = { 0,0,1 };
	environment_ortho.camera.look_at({ 0,0,3 }, { 0,0,0 }, { 0,1,0 });


	// Set up of the perspective camera
	// ***************************************** //
	environment.camera.look_at({ 3,1,2 }, { 0,0,0.5 }, { 0,0,1 });


	// Initialize the shapes of the scene
	// ***************************************** //

	// Create two basic objects
	quad.initialize(mesh_primitive_quadrangle({ -0.5f,0.7f,0 }, { 0.5f,0.7f,0 }, { 0.5f,1.0f,0 }, { -0.5f,1.0f,0 }), "Quad");
	quad.texture = opengl_load_texture_image("assets/text.png");

	cube.initialize(mesh_primitive_cube({ 0,0,0 }, 0.2f), "Cube");
	cube.transform.translation = { 0.75f,0.8f,0.0f };
	cube.texture = opengl_load_texture_image("assets/wood.jpg");

	global_frame.initialize(mesh_primitive_frame(), "Frame");
}



void scene_structure::display()
{
	timer.update();
	cube.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1.1f * pi / 2.0f) * rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);

	if (gui.display_frame)
		draw(global_frame, environment); // display the global frame only in perspective view

	// Display the two objects using the two scenes (using different camera and projection)
	// ***********************************************************************************
	//
	// Scene has the default user-controled camera and a perspective projection
	draw(quad, environment);
	draw(cube, environment);
	//
	// Scene_orthographic has a fixed camera and an orthographic projection (*)
	draw(quad, environment_ortho);
	draw(cube, environment_ortho);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
}


