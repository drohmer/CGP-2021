#include "shadow_map.hpp"

using namespace cgp;





void shadow_map_structure::initialize()
{
	// Load the shaders used to compute and render the shadow map
	shader_shadow_render = opengl_load_shader("shaders/shadow_map/use_shadows/vert.glsl", "shaders/shadow_map/use_shadows/frag.glsl");
	shader_shadow_map = opengl_load_shader("shaders/shadow_map/generate_depth_map/vert.glsl", "shaders/shadow_map/generate_depth_map/frag.glsl");
	
	// Size of the shadow map texture
	width_shadow_map  = 2048;
	height_shadow_map = 2048;

	// Initialize texture
	opengl_check;
    glGenTextures(1, &texture_shadow_map);
    glBindTexture(GL_TEXTURE_2D, texture_shadow_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width_shadow_map, height_shadow_map, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Initialize FBO, and attach the texture
	glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_shadow_map, 0);

	// Indicate that no color will be rendered
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

	// Clear current FBO to avoid side effects
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	opengl_check;


}

void shadow_map_structure::start_first_pass_shadow_rendering()
{
	// Set output to FBO
	glViewport(0, 0, width_shadow_map, height_shadow_map);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo); opengl_check;
	glClear(GL_DEPTH_BUFFER_BIT); opengl_check;

}
void shadow_map_structure::end_first_pass_shadow_rendering(int window_width, int window_height)
{
	// Clear previous FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0); opengl_check;

	// Set to standard screen output
	glViewport(0, 0, window_width, window_height); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); opengl_check;
}

void shadow_map_structure::draw_with_shadow(mesh_drawable const& drawable, scene_environment_shadow_map const& scene)
{
	// Setup shader
	assert_cgp(drawable.texture!=0, "Try to draw mesh_drawable without texture");

	// Force the shader used to display the shadow map
	glUseProgram(shader_shadow_render); opengl_check;

	// Send uniforms for this shader
	opengl_uniform_shadow(shader_shadow_render, scene);
	opengl_uniform(shader_shadow_render, drawable.shading);
	opengl_uniform(shader_shadow_render, "model", drawable.transform.matrix());

	// Set texture of the shape at index 0
	glActiveTexture(GL_TEXTURE0); opengl_check;
	glBindTexture(GL_TEXTURE_2D, drawable.texture); opengl_check;
	opengl_uniform(shader_shadow_render, "image_texture", 0);  opengl_check;

	// Set shadow map texture at index 1
	glActiveTexture(GL_TEXTURE1); opengl_check;
	glBindTexture(GL_TEXTURE_2D, texture_shadow_map); opengl_check;
	opengl_uniform(shader_shadow_render, "shadow_texture", 1);  opengl_check;
		
	// Call draw function
	assert_cgp(drawable.number_triangles>0, "Try to draw mesh_drawable with 0 triangles"); opengl_check;
	glBindVertexArray(drawable.vao);   opengl_check;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.vbo.at("index")); opengl_check;
	glDrawElements(GL_TRIANGLES, GLsizei(drawable.number_triangles*3), GL_UNSIGNED_INT, nullptr); opengl_check;

	// Clean buffers
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void shadow_map_structure::draw_shadow_map(mesh_drawable const& drawable, scene_environment_shadow_map const& current_scene)
{
	
	GLuint shader = shader_shadow_map;
	glUseProgram(shader); opengl_check;

	// Send uniforms for this shader
	opengl_uniform(shader, "projection", current_scene.light_projection.matrix());
	opengl_uniform(shader, "light", current_scene.light_view.matrix_view());
	opengl_uniform(shader, "model", drawable.transform.matrix());
		
	// Call draw function
	assert_cgp(drawable.number_triangles>0, "Try to draw mesh_drawable with 0 triangles"); opengl_check;
	glBindVertexArray(drawable.vao);   opengl_check;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.vbo.at("index")); opengl_check;
	glDrawElements(GL_TRIANGLES, GLsizei(drawable.number_triangles*3), GL_UNSIGNED_INT, nullptr); opengl_check;

	// Clean buffers
	glBindVertexArray(0);
}




scene_environment_shadow_map::scene_environment_shadow_map()
{
	background_color = { 1,1,1 };
	camera.look_at({ 7.0f, 4.0f, 7.0f }, { 0,0,0 });
	projection = camera_projection::perspective(50.0f * Pi / 180, 1.0f, 0.1f, 500.0f);
	light = { 1.0f,6.0f,2.0f };
	light_view.look_at(light, { 0,0,0 });
	light_projection = camera_projection::orthographic(-10, 10, -10, 10, 0, 30); // orthographic projection for simplicity
}

// Default version of the uniform parameters for standard shader without shadow (uses positional light)
void opengl_uniform(GLuint shader, scene_environment_shadow_map const& environment)
{
	opengl_uniform(shader, "projection", environment.projection.matrix());
	opengl_uniform(shader, "view", environment.camera.matrix_view());
	opengl_uniform(shader, "light", environment.light);
}
// Specific version for the shaders using the oriented light to work with shadows
void opengl_uniform_shadow(GLuint shader, scene_environment_shadow_map const& environment)
{
	opengl_uniform(shader, "projection", environment.projection.matrix());
	opengl_uniform(shader, "view", environment.camera.matrix_view());
	opengl_uniform(shader, "light", environment.light_view.matrix_view());
	opengl_uniform(shader, "projection_light", environment.light_projection.matrix());
}