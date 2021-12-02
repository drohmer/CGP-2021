#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Initialize the structure computing the effect (*)
	// ********************************************* //
	GLuint const shader_screen_effect = opengl_load_shader("shaders/screen_effect_convolution/vert.glsl","shaders/screen_effect_convolution/frag.glsl");
	screen_effect.initialize(shader_screen_effect, inputs.window.width, inputs.window.height); 




	// Initialize the shapes of the scene
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");

	camel.initialize(mesh_load_file_obj("assets/camel.obj"));
	camel.transform.scaling = 0.5f;
	camel.transform.translation = { -1.0f, -1.0f, 0.5f };

	cube.initialize(mesh_primitive_cube(), "Cube");
	cube.transform.translation = { -1,1,0 };
	cube.shading.color = { 0.8f, 0.8f, 0.3f };

	cylinder.initialize(mesh_primitive_cylinder(0.2f, { 0,0,-0.5f }, { 0,0,0.5f }), "Cylinder");
	cylinder.transform.translation = { 0.75f,-0.5f, 0 };
	cylinder.shading.color = { 0.7f,0.9f,0.9f };

	environment.camera.look_at({ 3.0f,2.0f,2.0f }, { 0,0,0 }, { 0,0,1 });
}


void scene_structure::display_shapes_first_pass()
{	
	cube.transform.rotation     = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	cylinder.transform.rotation = rotation_transform::from_axis_angle({ -1,1,0 }, timer.t * 0.5f);

	draw(cube, environment);
	draw(cylinder, environment);
	draw(camel, environment);
	if (gui.display_wireframe) {
		draw_wireframe(cube, environment);
		draw_wireframe(cylinder, environment);
		draw_wireframe(camel, environment);
	}

	if (gui.display_frame)
		draw(global_frame, environment);
}

void scene_structure::display()
{
	environment.light = environment.camera.position();
	timer.update();


	// Update the texture size of the FBO if needed
	if (inputs.window.is_resized) 
		screen_effect.update_screen_resize(inputs.window.width, inputs.window.height);


	screen_effect.prepare_render_pass_into_fbo();

	display_shapes_first_pass();



	// Display the quad using the FBO texture, and use the shader applying the filter
	draw_effect(screen_effect);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}

