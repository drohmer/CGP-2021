#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Initialize the skybox (*)
	// ***************************************** //
	skybox.initialize("assets/skybox/");         // indicate a path where to load the 6 texture images


	// Basic set-up
	// ***************************************** //
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	torus.initialize(mesh_primitive_torus(), "Torus");
	torus.transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, Pi/2);
}



void scene_structure::display()
{
	// Display of the skybox (*)
	// ***************************************** //
	draw(skybox, environment); 
	// Note: The skybox must be drawn before the other shapes 
	//   Skybox is displayed without writing in the z-buffer.
	//   In displaying it first, the cube appears beyond any other shape.



	// Other elements of the scene
	// ***************************************** //
	environment.light = environment.camera.position();
	
	if (gui.display_frame)
		draw(global_frame, environment);

	draw(torus, environment);
	if (gui.display_wireframe)
		draw_wireframe(torus, environment);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}
