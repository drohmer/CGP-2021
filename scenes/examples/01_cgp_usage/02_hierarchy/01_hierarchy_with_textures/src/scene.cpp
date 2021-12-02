#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Create the hierarchy
	// ***************************************** //
	

	/** Examples of hierarchy with elements associated to different textures
	* Note that the shapes can be procedural primitives, or even external mesh files (like the wings)
	*/

	mesh_drawable body; 
	body.initialize(mesh_primitive_ellipsoid({ 1.0f, 1.0f, 1.5f }), "body");
	body.texture = opengl_load_texture_image("assets/body.png"); // associate a texture-image to each element
	
	mesh_drawable head; 
	head.initialize(mesh_primitive_sphere(0.9f),"head");
	head.texture = opengl_load_texture_image("assets/head.png");

	mesh_drawable wing_L; 
	wing_L.initialize(mesh_load_file_obj("assets/wing.obj"), "wing_L");
	wing_L.texture = opengl_load_texture_image("assets/wing.png");

	mesh_drawable wing_R; 
	wing_R.initialize(mesh_load_file_obj("assets/wing.obj"), "wing_R");
	wing_R.texture = opengl_load_texture_image("assets/wing.png");
	wing_R.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, pi);

	mesh_drawable eye_L; 
	eye_L.initialize(mesh_primitive_sphere(0.2f), "eye_R");
	eye_L.shading.color = { 0.2f,0.2f,0.2f };

	mesh_drawable eye_R; 
	eye_R.initialize(mesh_primitive_sphere(0.2f), "eye_L");
	eye_R.shading.color = { 0.2f,0.2f,0.2f };
	// Note: the eye is displayed with a single color and doesn't need a texture image (it has a default white image associated to it).


	// Generat the hierarchy
	hierarchy.add(body);
	hierarchy.add(head, "body", { 0,0,1.8 });
	hierarchy.add(eye_R, "head", { 0.4f,0.3f,0.6f });
	hierarchy.add(eye_L, "head", { -0.4f,0.3f,0.6f });
	hierarchy.add(wing_L, "body", { 0,1.03f,0 });
	hierarchy.add(wing_R, "body", { 0,1.03f,0 });


	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.look_at({ 10,6,6 }, { 0,0,0 }, { 0,1,0 });
}



void scene_structure::display()
{
	// Place the light at the camera position
	environment.light = environment.camera.position();
	
	if (gui.display_frame)      // Display the basic frame
		draw(global_frame, environment);


	// Update the animation using local transformation
	timer.update();
	float const t = timer.t;
	hierarchy["body"].transform.translation = { 0,0.2f * std::cos(5 * t),0 };
	hierarchy["wing_L"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, pi / 8.0f * (1 + std::cos(20 * t)));
	hierarchy["wing_R"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,-1 }, pi / 8.0f * (1 + std::cos(20 * t)));
	hierarchy["head"].transform.translation = vec3{ 0,0,1.8 } + vec3{ 0,0,0.1f * std::cos(2.5 * t) };
	hierarchy["head"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, pi / 8.0f * std::cos(5 * t));

	// Update the global coordinate transformation
	hierarchy.update_local_to_global_coordinates();
	
	draw(hierarchy, environment);

	if (gui.display_wireframe)
		draw_wireframe(hierarchy, environment);

}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame",     &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}


