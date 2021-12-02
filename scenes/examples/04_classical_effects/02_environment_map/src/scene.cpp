#include "scene.hpp"

using namespace cgp;


void scene_structure::initialize()
{
	// Initialize the Skybox (*)
	// ***************************************** //
	skybox.initialize("assets/skybox/");         // indicate a path where to load the 6 texture images

	// Set the environment map (*)
	// ***************************************** //
	// Load the shader for the environment map
	GLuint const shader_environment_map = opengl_load_shader("shaders/environment_map/vert.glsl", "shaders/environment_map/frag.glsl");
	// Set the same skybox texture to the environment
	environment.environment_map_texture = skybox.texture; 


	// Initialize the shapes of the scene
	// ***************************************** //
	
	// Shapes with environment map are associated to the shader "shader_environment_map"
	shape[shape_torus].initialize(mesh_primitive_torus(1.5f, 0.5f, { 0,0,0 }, { 0,1,0 }, 80, 25), "Torus", shader_environment_map);
	shape[shape_sphere].initialize(mesh_primitive_sphere(), "Sphere", shader_environment_map);
	shape[shape_cylinder].initialize(mesh_primitive_cylinder(0.8f, { -2,0,0 }, { 2,0,0 }, 20, 40, true), "Cylinder", shader_environment_map);
	shape[shape_camel].initialize(mesh_load_file_obj("assets/camel.obj"), "Camel", shader_environment_map);
	shape[shape_camel].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, pi / 2.0f) * rotation_transform::from_axis_angle({ 1,0,0 }, -pi / 2.0f);

	// Shapes without environment map can be associated to the sandard "mesh" shader
	global_frame.initialize(mesh_primitive_frame(), "Frame");

}



void scene_structure::display()
{
	// Display the skybox as the first shape
	draw(skybox, environment);

	// Display the shape with environment map
	draw(shape[gui.display_shape], environment);
	if (gui.display_wireframe)
		draw_wireframe(shape[gui.display_shape], environment);


	if (gui.display_frame)
		draw(global_frame, environment);
	environment.light = environment.camera.position();
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);

	// Select the shape to be displayed
	ImGui::Text("Surface to display:");
	int* ptr_shape_display = reinterpret_cast<int*>(&gui.display_shape);
	ImGui::RadioButton("Sphere", ptr_shape_display, shape_sphere); ImGui::SameLine();
	ImGui::RadioButton("Cylinder", ptr_shape_display, shape_cylinder); ImGui::SameLine();
	ImGui::RadioButton("Torus", ptr_shape_display, shape_torus); ImGui::SameLine();
	ImGui::RadioButton("Camel", ptr_shape_display, shape_camel);
}
