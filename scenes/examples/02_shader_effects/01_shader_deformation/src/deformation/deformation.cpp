#include "deformation.hpp"

using namespace cgp;

void opengl_uniform(GLuint shader, scene_environment_with_shader_deformation const& environment)
{
	// Send the default uniforms from the basic scene_environment
	opengl_uniform(shader, scene_environment_basic(environment));

	// Send the light and time as uniforms 
	opengl_uniform(shader, "light", environment.light, false);
	opengl_uniform(shader, "time", environment.t, false);
	// Note: the 3rd parameter is set to false so that there is no warning if the environment is used with a shader that doesn't expect light and time uniform variable.
}


void scene_environment_with_shader_deformation::update(float current_time)
{
	t = current_time;          // set the current time
	light = camera.position(); // replace the light at the camera position
}