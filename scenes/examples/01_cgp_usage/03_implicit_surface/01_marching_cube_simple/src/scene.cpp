#include "scene.hpp"
#include "implicit_surface/implicit_surface.hpp"

using namespace cgp;

void scene_structure::initialize()
{
	// Create the Implicit Surface
	// ***************************************** //

	// Number of voxels
	int3 const samples = { 50, 50, 50 };
	// Dimension of the domain
	vec3 const length = { 5,3,3 };
	// Isovalue for the marching cube
	float isovalue = 0.5f;

	// Initialize the spatial domain and the field
	spatial_domain_grid_3D domain = spatial_domain_grid_3D::from_center_length({ 0,0,0 }, length, samples);
	grid_3D<float> field = compute_scalar_field(domain);

	// Compute the mesh using marching cube 
	mesh m = marching_cube(field, domain, isovalue);
	implicit_surface.initialize(m, "Implicit surface");


	// Helpers
	// ***************************************** //

	// Helper to visualize the box of the domain
	segments_drawable::default_shader = curve_drawable::default_shader;
	domain_box = spatial_domain_grid_drawable(domain);

	// The standard frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");

	environment.camera.look_at({ 6,3,6 }, { 0,0,0 }, { 0,1,0 });
}

void scene_structure::display()
{
	// Place the light at the camera position
	environment.light = environment.camera.position();

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);
	
	if (gui.plain)    // Display the implicit surface
		draw(implicit_surface, environment);
	
	if(gui.wireframe) // Display the wireframe of the implicit surface
		draw_wireframe(implicit_surface, environment, { 0,0,0 });

	if(gui.domain)    // Display the boundary of the domain
		draw(domain_box, environment);
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame",     &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.wireframe);
	ImGui::Checkbox("Plain",     &gui.plain);
	ImGui::Checkbox("Domain",    &gui.domain);
}


