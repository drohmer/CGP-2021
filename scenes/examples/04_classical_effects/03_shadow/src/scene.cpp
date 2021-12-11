#include "scene.hpp"


using namespace cgp;



void scene_structure::initialize()
{
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	ground.initialize(mesh_primitive_quadrangle({ -10,-0.5f,-10 }, { -10, -0.5f,10 }, { 10, -0.5f,10 }, { 10,-0.5f,-10 }), "Ground");
	sphere.initialize(mesh_primitive_sphere(), "Sphere");
	cube.initialize(mesh_primitive_cube(), "Cube");
	cube.transform.translation = { 1,2,0 };
	sphere_light.initialize(mesh_primitive_sphere(0.1f));
	sphere_light.shading.color = { 1,1,0 };
	sphere_light.shading.phong = { 1,0,0,1 };

	// The shadow map paramters must be initialized before their use
	shadow_map.initialize();
}



void scene_structure::display()
{
	// Deal with animation
	timer.update();
	float t = timer.t;
	if (gui.animated_shapes) {
		sphere.transform.translation = { 2.0f * std::cos(t), 1.0f, -2.0f };
		cube.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, t);
	}

	if (gui.animated_light) {
		environment.light = { 6 * cos(0.5 * t), 6.0f , 6 * sin(0.5 * t) };
		environment.light_view.look_at(environment.light, { 0,0,0 });
		sphere_light.transform.translation = environment.light;
	}


	// First pass: Draw all shapes that cast shadows
	//   Set the FBO to compute the shadow map
	shadow_map.start_first_pass_shadow_rendering(); 
	{
		shadow_map.draw_shadow_map(sphere, environment);
		if (gui.display_frame)
			shadow_map.draw_shadow_map(global_frame, environment);
		shadow_map.draw_shadow_map(cube, environment);
	}
	shadow_map.end_first_pass_shadow_rendering(inputs.window.width, inputs.window.height); // after this line, the output takes place on the screen


	// Second pass: Draw all shapes that receives shadows
	{
		if (gui.display_frame)
			shadow_map.draw_with_shadow(global_frame, environment);
		shadow_map.draw_with_shadow(ground, environment);
		shadow_map.draw_with_shadow(sphere, environment);
		shadow_map.draw_with_shadow(cube, environment);
	}


	// The shape can still be displayed using the default shaders (without shadow effect)
	if (gui.display_wireframe) {
		draw_wireframe(ground, environment);
		draw_wireframe(sphere, environment);
		draw_wireframe(cube, environment);
	}
	draw(sphere_light, environment); // note that the sphere_light should not cast shadow itself




}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
	ImGui::Checkbox("Animated Shape", &gui.animated_shapes);
	ImGui::Checkbox("Animated Light", &gui.animated_light);
}

