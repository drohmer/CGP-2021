#pragma once

#include "cgp/cgp.hpp"

struct scene_environment_with_environment_map : cgp::scene_environment_basic_camera_spherical_coords
{
	using cgp::scene_environment_basic_camera_spherical_coords::scene_environment_basic_camera_spherical_coords;

	// Add to the standard scene the ID of the environment map texture
	GLuint environment_map_texture = 0;
};


void draw(cgp::mesh_drawable const& drawable, scene_environment_with_environment_map const& environment);
