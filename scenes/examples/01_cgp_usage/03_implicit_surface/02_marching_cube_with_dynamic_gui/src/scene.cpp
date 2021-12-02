#include "scene.hpp"

using namespace cgp;

void scene_structure::initialize()
{
	// Helpers
	// ***************************************** //

	// Helper to visualize the box of the domain
	segments_drawable::default_shader = curve_drawable::default_shader;

	// The standard frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.look_at({ 6,3,6 }, { 0,0,0 }, { 0,1,0 });


	// Initialization for the Implicit Surface (*)
	// ***************************************** //

	// Load the shader used to display the implicit surface (only a polygon soup)
	GLuint shader_triangle_soup = opengl_load_shader("shaders/mesh_geometry/vert.glsl", "shaders/mesh_geometry/frag.glsl");
	triangle_soup_drawable::default_shader = shader_triangle_soup;

	// Initialize the field and the implicit surface
	implicit_surface.set_domain(gui.domain.samples, gui.domain.length);
	implicit_surface.update_field(field_function, gui.isovalue);
}

void scene_structure::display()
{
	// Place the light at the camera position
	environment.light = environment.camera.position();
	
	if (gui.display.frame)      // Display the basic frame
		draw(global_frame, environment);

	if (gui.display.surface)    // Display the implicit surface (*)
		draw(implicit_surface.drawable_param.shape, environment);

	if (gui.display.wireframe)  // Display the wireframe of the implicit surface (*)
		draw_wireframe(implicit_surface.drawable_param.shape, environment, { 0,0,0 });

	if (gui.display.domain)     // Display the boundary of the domain (*)
		draw(implicit_surface.drawable_param.domain_box, environment);
}


void scene_structure::display_gui()
{
	// Handle the gui values and the updates using the helper methods (*)
	implicit_surface.gui_update(gui, field_function);
}


