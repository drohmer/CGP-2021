#include "scene.hpp"

/** This file contains the custom implementation associated the scene 
*  The (*) indicates elements that are specific to the use of the multiple_lights and that should be handled if you want to use this effect in another scene. */

using namespace cgp;

void scene_structure::initialize()
{
	// Specific Shader (*)
	// ***************************************** //
	// Load a new custom shader that take into account spotlights (note the new shader file in shader/ directory)
	// Make sure you load an set this shader for the shapes that need to be illuminated
	GLuint const shader_lights = opengl_load_shader("shaders/mesh_lights/vert.glsl", "shaders/mesh_lights/frag.glsl");                 
	mesh_drawable::default_shader = shader_lights;   // set this shader as the default one for all new shapes declared after this line 


	// Create the surrounding shapes
	// ***************************************** //

	// The standard frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");

	// A central cube
	cube.initialize(mesh_primitive_cube(), "Cube");
	cube.transform.translation = { -2,0,0.5f };
	cube.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, pi / 4.0f);

	// The ground
	ground.initialize(mesh_primitive_quadrangle({ -30,-30,0 }, { -30,30,0 }, { 30,30,0 }, { 30,-30,0 }), "Quad");

	// The lights displayed as spheres using this helper initializer (*)-optionnal
	light_drawable.initialize(shader_lights);


	// Environment parameters
	// ***************************************** //

	// The background color is set to match the color of the fog defined in the shader (*)
	environment.background_color = { 0.7f, 0.7f, 0.7f }; 


	// Initialize the camera
	environment.projection = camera_projection::perspective(50.0f *pi/180, 1.0f, 0.1f, 500.0f);
	environment.camera.distance_to_center = 10.0f;
	environment.camera.look_at({ 3,1,2 }, { 0,0,0.5 }, { 0,0,1 });
}

void scene_structure::display()
{
	timer.update();
	float t = timer.t;

	// Update the position and color of the lights
	compute_light_position(t, environment);

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);

	// Display the elements of the scene
	draw(cube, environment);
	draw(ground, environment);
	draw(light_drawable, environment); // this is a helper function from multiple_lights (display all the spotlights as spheres) (*)-optionnal
}

void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	display_gui_falloff(environment); // helper function from multiple_lights (*)-optionnal
}


