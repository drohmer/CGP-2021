#include "scene.hpp"


using namespace cgp;

// Function called at each frame
void dynamic_update(mesh& mesh_shape, mesh_drawable& drawable, float t)
{
	// 1- Update the mesh as your wish
	int N = mesh_shape.position.size();
	for (int k = 0; k < N; ++k) {
		// Changing the positions
		vec3& p = mesh_shape.position[k];
		p.z = 0.1f*std::cos(4 * Pi*p.x - t);

		// The colors can be changed too
		vec3& c = mesh_shape.color[k]; 
		c.x = std::abs(std::cos(t+p.y*2*Pi));
	}

	// 2- Don't forget to update the shape normals after modifying the position
	mesh_shape.compute_normal();

	// 3- Update the buffers of the corresponding mesh_drawable
	drawable.update_position(mesh_shape.position);
	drawable.update_color(mesh_shape.color);
	drawable.update_normal(mesh_shape.normal);

	// Note: Using mesh_drawable.update() calls glBufferSubData
	//  This is more efficient that re-allocating a new mesh_drawable
}


void scene_structure::initialize()
{
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::z;
	environment.camera.look_at({ 2,2,1 }, { 0.5f,0.5f,0 });


	// Initialization (note that the mesh structure is a variable of the class)
	int N = 100;
	mesh_shape = mesh_primitive_grid({ 0,0,0 }, { 1,0,0 }, { 1,1,0 }, { 0,1,0 }, N, N);
	drawable.initialize(mesh_shape, "Dynamic surface");
}

void scene_structure::display()
{
	// Place the light at the camera position
	environment.light = environment.camera.position();
	timer.update();
	
	if (gui.display_frame)      // Display the basic frame
		draw(global_frame, environment);

	// Call of the update
	dynamic_update(mesh_shape, drawable, timer.t);

	// Standard Display
	draw(drawable, environment);

	if (gui.display_wireframe)
		draw_wireframe(drawable, environment);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame",     &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}
