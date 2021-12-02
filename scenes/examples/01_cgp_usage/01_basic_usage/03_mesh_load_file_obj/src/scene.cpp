#include "scene.hpp"


using namespace cgp;


void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //

	// The standard frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.look_at({ 5,-3,2.5f }, { 0,0,0 }, { 0,0,1 });


	// Load of obj mesh file
	// ***************************************** //
	
	// mesh_load_file_obj parse an obj file and returns a mesh structure 
	mesh mesh_camel = mesh_load_file_obj("assets/camel.obj");
	camel.initialize(mesh_camel, "camel");

	// If the mesh has uv coordinates (must be defined in the file), then we can use a texture image (corresponding to the uv-coordinates)
	stegosaurus.initialize(mesh_load_file_obj("assets/stegosaurus.obj"));
	stegosaurus.texture = opengl_load_texture_image("assets/stegosaurus.jpg");

	// Place the shape in space
	stegosaurus.transform.translation = { 1.5f,0,0 };
	camel.transform.translation = { -1,0,0 };


	/* Notes:
	*
	* - The mesh_load_file_obj follows a simple approach assuming the file contains a single object and returns a single mesh structure.
	* - If you need to store multiple shapes (with multiple textures, etc.) you should either
	*       - split it into several obj files
	*       - or use an external parser library such as tinyobjloader for instance.
	* - .mtl files are not read - so you need to set your shading and texture file manually
	*/

}

void scene_structure::display()
{
	// Place the light at the camera position
	environment.light = environment.camera.position();
	
	if (gui.display_frame)      // Display the basic frame
		draw(global_frame, environment);

	// Display the loaded shapes
	draw(camel, environment);
	draw(stegosaurus, environment);

	if (gui.display_wireframe) {
		draw_wireframe(camel, environment);
		draw_wireframe(stegosaurus, environment);
	}
}


void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame",     &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}
