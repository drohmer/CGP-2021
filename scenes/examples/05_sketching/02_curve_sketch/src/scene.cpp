#include "scene.hpp"


using namespace cgp;


void scene_structure::initialize()
{
	environment.projection = camera_projection::orthographic(- 1, 1, -1, 1, -1, 1);
	environment.camera.look_at({ 0.0f,0.0f,0.0f }, { 0,0,-1 }, {0,1,0});
}


void scene_structure::display()
{
	for(int k=0; k<sketch_drawable.size(); ++k)
		draw(sketch_drawable[k], environment);
}




// Compute the 3D position of a position given by its screen coordinates
static vec3 unproject(camera_projection const& P, vec2 p_screen)
{
	// Simple un-project assuming that the viewpoint is an orthogonal projection
	vec4 const p_proj = P.matrix_inverse() * vec4(p_screen, 0.0f, 1.0f);
	return vec3(p_proj.xy(), 0.0f);
}


void scene_structure::mouse_click(cgp::inputs_interaction_parameters const& inputs)
{
	if (inputs.mouse.click.last_action == last_mouse_cursor_action::click_left) 
	{
		// Create new stroke (curve_dynamic_drawable)
		int k_sketch = sketch_drawable.size();
		sketch_drawable.push_back(curve_dynamic_drawable());
		sketch_drawable[k_sketch].initialize("Sketch " + str(k_sketch));

		// Add the new clicked position
		vec3 const p = unproject(environment.projection, inputs.mouse.position.current);
		sketch_drawable[k_sketch].push_back(unproject(environment.projection, inputs.mouse.position.current));
	}
}
void scene_structure::mouse_move(cgp::inputs_interaction_parameters const& inputs)
{
	if (inputs.mouse.click.left) {
		// Add the new clicked position
		int k_sketch = sketch_drawable.size()-1;
		vec3 const p = unproject(environment.projection, inputs.mouse.position.current);
		sketch_drawable[k_sketch].push_back(p);
	}
}

void scene_structure::display_gui()
{

	bool cancel = ImGui::Button("Cancel last stroke");
	if (cancel)
	{
		// remove last stroke
		int const N_stroke = sketch_drawable.size();
		if (N_stroke > 0) {
			sketch_drawable[N_stroke - 1].clear();
			sketch_drawable.resize(N_stroke - 1);
		}
	}
}
