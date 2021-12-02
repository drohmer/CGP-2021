#include "scene.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::y;
	environment.camera.look_at({ 3.0f,2.0f,2.0f }, { 0,0,0 });

	plane.initialize(mesh_primitive_quadrangle({ -2,-0.6f,-2 }, { 2,-0.6f,-2 },{2,-0.6f,2},{-2,-0.6f,2}), "Plane");
	cube.initialize(mesh_primitive_cube(), "Cube");
	cube.shading.color = { 1,1,0.5f };
	cube.transform.translation = { -1,0,1 };

	cylinder.initialize(mesh_primitive_cylinder(0.2f, { 0,0,-0.5f },{0,0,0.5f}), "Cylinder");
	cylinder.shading.color = { 0.8f,0.95f,1.0f };
	cylinder.transform.translation = { 0.5f,0,-0.5f };

}




void scene_structure::display()
{

	// Basic elements of the scene
	environment.light = environment.camera.position();
	if (gui.display_frame)
		draw(global_frame, environment);

	timer.update();

	draw(plane, environment);

	cube.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, std::cos(timer.t));
	draw(cube, environment);

	if (gui.display_wireframe) {
		draw_wireframe(plane, environment);
		draw_wireframe(cube, environment);
	}
	
	cylinder.transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, gui.cylinder_angle);
	draw(cylinder, environment);
	draw_wireframe(cylinder, environment);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
	ImGui::SliderFloat("Cylinder.x", &cylinder.transform.translation.z, -2.0f, 1.0f);
	ImGui::SliderFloat("Cylinder.angle", &gui.cylinder_angle, 0.0f, 2*Pi);
}


