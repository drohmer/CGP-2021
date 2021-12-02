#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.look_at({ 3.0f,2.0f,2.0f }, { 0,0,0 }, { 0,0,1 });


	// Initialize the shapes of the scene
	// ***************************************** //

	cube.initialize(mesh_primitive_cube(), "Cube");
	cube.transform.translation = { -1,1,0 };
	cube.shading.color = { 0.8f, 0.8f, 0.3f };

	cylinder.initialize(mesh_primitive_cylinder(0.2f, { 0,0,-0.5f }, { 0,0,0.5f }), "Cylinder");
	cylinder.transform.translation = { 0.75f,-0.5f, 0 };
	cylinder.shading.color = { 0.7f,0.9f,0.9f };
}



void scene_structure::display()
{
	// Basics common elements
	// ***************************************** //

	environment.light = environment.camera.position();
	
	if (gui.display_frame)
		draw(global_frame, environment);

	
	// Handle elements of the scene
	// ***************************************** //
	timer.update(); // update the timer to the current elapsed time
	cube.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);           // set a rotation for the cube that depends on time
	cylinder.transform.rotation = rotation_transform::from_axis_angle({ -1,1,0 }, timer.t*0.5f); // set a rotation for the cylinder that depends on time

	// Display the elements
	draw(cube, environment);
	draw(cylinder, environment);
	if (gui.display_wireframe) {
		draw_wireframe(cube, environment);
		draw_wireframe(cylinder, environment);
	}
	
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}


