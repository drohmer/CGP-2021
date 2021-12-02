#include "scene.hpp"

/** This file contains the custom implementation associated the scene 
*  The (*) indicates elements that are specific to the use of the shader deformation and that should be handled if you want to use this effect in another scene. */

using namespace cgp;

void scene_structure::initialize()
{
	// Specific Shader (*)
	// ***************************************** //
	// Load a new custom shader that computes the deformation
	GLuint const shader_deformation = opengl_load_shader("shaders/deformation/vert.glsl", "shaders/deformation/frag.glsl");                 


	// Create the Shapes
	// ***************************************** //

	// The standard frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");

	// Create the grid to be deformed (*)
	grid.initialize(mesh_primitive_grid({ -1,-1,0 }, { 1,-1,0 }, { 1,1,0 }, { -1,1,0 }, 200, 200), "Grid");
	grid.shader = shader_deformation;
	grid.shading.color = { 0.8f, 0.95f, 1.0f };

}

void scene_structure::display()
{
	timer.update();
	float t = timer.t;

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);
	
	// Displaying the shape deformed by the shader
	environment.update(t);   // update the environment with the new time and light position (*)
	draw(grid, environment); // Display the grid deformed by the shader (*)
	
}

void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
}


