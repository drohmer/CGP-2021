#pragma once

#include "cgp/cgp.hpp"
#include "cgp/helper_common_scene/helper_common_scene.hpp"

/** Scene environment that adds the following uniform parameters to be sent to the shader in shaders/deformation/
*/
struct scene_environment_with_shader_deformation : cgp::scene_environment_basic
{
	cgp::vec3 light; // position of the light
	float t;         // The time is sent to the shader to compute a procedural deformation

	void update(float t); // function to be called in the scene display - update the time t and the light position
};

// Send the uniform parameters of the scene with light - Function automatically called when using draw([mesh_drawable], scene_environment_with_multiple_lights);
void opengl_uniform(GLuint shader, scene_environment_with_shader_deformation const& environment);


