#pragma once

#include "cgp/cgp.hpp"


struct scene_environment_shadow_map {
	// Color of the background of the scene
	cgp::vec3 background_color;

	// The position/orientation of a camera that can rotates freely around a specific position
	cgp::camera_spherical_coordinates camera;

	// A projection structure (perspective or orthogonal projection)
	cgp::camera_projection projection;

	// The position of a light
	cgp::vec3 light; // position of the light (provided for compatibility with default shaders)
	cgp::camera_spherical_coordinates light_view;
	cgp::camera_projection light_projection;

	scene_environment_shadow_map();
};
void opengl_uniform(GLuint shader, scene_environment_shadow_map const& current_scene);
void opengl_uniform_shadow(GLuint shader, scene_environment_shadow_map const& current_scene);


struct shadow_map_structure
{
	GLuint shader_shadow_map;    // Shader used to compute the shadow - depth map from the light viewpoint
	GLuint shader_shadow_render; // Shader used to render the 3D shapes with shadows once the shadow map is computed

	GLuint fbo;                // FBO used to render the shadow map as a texture
	GLuint texture_shadow_map; // Texture of the shadow map
	int width_shadow_map;
	int height_shadow_map;
	

	void initialize(); // Initialize shaders and FBO - must be called in the initialization step before any rendering
	void start_first_pass_shadow_rendering();  // Render objects in the shadow map after this line using draw_shadow_map()
	void end_first_pass_shadow_rendering(int window_width, int window_height);    // Render objects receiving shadows after this line using draw_with_shadow()

	void draw_shadow_map(cgp::mesh_drawable const& drawable, scene_environment_shadow_map const& scene);
	void draw_with_shadow(cgp::mesh_drawable const& drawable, scene_environment_shadow_map const& current_scene);
};






