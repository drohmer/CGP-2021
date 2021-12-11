#include "scene.hpp"


using namespace cgp;


void scene_structure::initialize()
{
	environment.projection = camera_projection::orthographic(- 1, 1, -1, 1, -1, 1);
	environment.camera.look_at({ 0.0f,0.0f,0.0f }, { 0,0,-1 }, {0,1,0});
	environment.light = { 0,0,1 };

	sphere.initialize(mesh_primitive_sphere(0.01f), "Sphere");
}


void scene_structure::display()
{
	for (int k = 0; k < points.size(); ++k) {
		sphere.transform.translation = points[k];
		draw(sphere, environment);
	}
}




// Compute the 3D position of a position given by its screen coordinates
static vec3 unproject(camera_projection const& P, vec2 p_screen)
{
	// Simple un-project assuming that the viewpoint is an orthogonal projection
	vec4 const p_proj = P.matrix_inverse() * vec4(p_screen, 0.0f, 1.0f);
	return vec3(p_proj.xy(), 0.0f);
}


void scene_structure::mouse_click()
{
	if (inputs.mouse.click.last_action == last_mouse_cursor_action::click_left) 
	{
		// Add the new clicked position
		vec3 const p = unproject(environment.projection, inputs.mouse.position.current);
		points.push_back(unproject(environment.projection, inputs.mouse.position.current));
	}
}

void scene_structure::display_gui()
{
	// no gui in this example
}
