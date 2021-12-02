#pragma once

#include "cgp/cgp.hpp"


// Create a mesh_drawable_multitexture in reusing the mesh_drawable structure and adding an extra texture ID
struct mesh_drawable_multitexture : cgp::mesh_drawable {

	using mesh_drawable::mesh_drawable; // reuse the same constructor
	GLuint texture_2 = 0; // add a second texture
};


// Adapt the draw function for a mesh_drawable_multitexture
void draw(mesh_drawable_multitexture const& drawable, cgp::scene_environment_basic const& environment);