#include "cgp/cgp.hpp"
#include <iostream>
#include <list>


using namespace cgp;

// Definition of structs
// ****************************** //

struct gui_parameters {
	bool display_frame     = true;
	bool display_wireframe = false;
};


struct scene_environment
{
	vec3 background_color;
	camera_around_center camera;
	camera_projection projection;
	vec3 light;
};

// Functions headers
// ****************************** //

// Callback functions
void window_size_callback(GLFWwindow* window, int width, int height);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
void keyboard_callback(GLFWwindow* window, int key, int, int action, int mods);

// Scene setup functions
void initialize_data();
void display_gui();
void display();


// Global variables
// ****************************** //

// General environment and GUI
gui_parameters gui;                   // Parameters stored when manipulating the GUI
inputs_interaction_parameters inputs; // A storage for the current values of the inputs (mouse, keyboard, window dimension) that can be use for interaction purpose
scene_environment environment;        // Store the environment of the scene (camera, light, etc)

// The shape displayed in the scene
mesh_drawable global_frame;
mesh_drawable cube;
mesh_drawable cylinder;

timer_fps fps_record; // Timer used for the fps count
timer_basic timer;    // Timer used for the animation




int main(int, char* argv[])
{
	std::cout << "Run " << argv[0] << std::endl;

	// Create a window
	int const width = 1280, height = 1024;              // Set the window size
	GLFWwindow* window = create_window(width, height);  // Creation using GLFW
	std::cout << opengl_info_display() << std::endl;;   // Display debug information on command line

	// Initialize ImGui
	imgui_init(window);

	// Set the callback functions for the inputs
	glfwSetKeyCallback(window, keyboard_callback);            // Event called when a keyboard touch is pressed/released
	glfwSetMouseButtonCallback(window, mouse_click_callback); // Event called when a button of the mouse is clicked/released
	glfwSetCursorPosCallback(window, mouse_move_callback);    // Event called when the mouse is moved
	glfwSetWindowSizeCallback(window, window_size_callback);  // Event called when the window is rescaled 

	
	std::cout<<"Initialize data ..."<<std::endl;
	initialize_data();
	fps_record.start();

	std::cout<<"Start animation loop ..."<<std::endl;
	while (!glfwWindowShouldClose(window))
	{
		// Reset the screen for a new frame
		// ***************************************** //

		glViewport(0, 0, inputs.window.width, inputs.window.height);

		glClearColor(environment.background_color.x, environment.background_color.y, environment.background_color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		fps_record.update();
		if (fps_record.event) {
			std::string const title = "CGP Display - " + str(fps_record.fps) + " fps";
			glfwSetWindowTitle(window, title.c_str());
		}

		imgui_create_frame();
		ImGui::Begin("GUI", NULL, ImGuiWindowFlags_AlwaysAutoResize);
		inputs.mouse.on_gui = ImGui::GetIO().WantCaptureMouse;

		environment.projection.update_aspect_ratio(inputs.window.aspect_ratio());

		// Display the content
		// ***************************************** //
		display_gui();
		display();



		// End of the frame
		// ***************************************** //
		ImGui::End();
		imgui_render_frame(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	imgui_cleanup();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void initialize_data()
{
	// Initialise the shaders
	// ***************************************** //

	//   - Shader used to display meshes
	GLuint const shader_mesh = opengl_load_shader("shaders/mesh/vert.glsl", "shaders/mesh/frag.glsl");
	//   - Shader used to display constant color (ex. for curves)
	GLuint const shader_uniform_color = opengl_load_shader("shaders/single_color/vert.glsl", "shaders/single_color/frag.glsl");

	// Set standard mesh shader for mesh_drawable
	mesh_drawable::default_shader = shader_mesh;
	// Set default white texture
	mesh_drawable::default_texture = opengl_load_texture_image(image_raw{ 1,1,image_color_type::rgba,{255,255,255,255} });

	// Set standard uniform color for curve_drawable
	curve_drawable::default_shader = shader_uniform_color;

	
	// Environment setup
	// ***************************************** //

	// Initialize the projection matrix as perspective
	//  the parameters are perspective(field-of-view, aspect ratio, depth-min, depth-max)
	environment.projection = camera_projection::perspective(50.0f*Pi/180, 1.0f, 0.1f, 500.0f);

	// Initialize the initial position of the camer
	environment.camera.look_at({ 3.0f,2.0f,2.0f }, { 0,0,0 }, { 0,0,1 });

	// Background color of the display
	environment.background_color = { 1,1,1 };

	// Initialize the standard Global Frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");


	// Initialize the shapes of the scene
	// ***************************************** //

	cube.initialize(mesh_primitive_cube(), "Cube");
	cube.transform.translation = { -1,1,0 };
	cube.shading.color = { 0.8f, 0.8f, 0.3f };

	cylinder.initialize(mesh_primitive_cylinder(0.2f, { 0,0,-0.5f }, { 0,0,0.5f }), "Cylinder");
	cylinder.transform.translation = { 0.75f,-0.5f, 0 };
	cylinder.shading.color = { 0.7f,0.9f,0.9f };

}

void display()
{
	// Basics common elements
	// ***************************************** //

	environment.light = environment.camera.position();

	if (gui.display_frame)
		draw(global_frame, environment);


	// Handle elements of the scene
	// ***************************************** //
	timer.update(); // update the timer to the current elapsed time
	cube.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);             // set a rotation for the cube that depends on time
	cylinder.transform.rotation = rotation_transform::from_axis_angle({ -1,1,0 }, timer.t * 0.5f); // set a rotation for the cylinder that depends on time

	// Display the elements
	draw(cube, environment);
	draw(cylinder, environment);
	if (gui.display_wireframe) {
		draw_wireframe(cube, environment);
		draw_wireframe(cylinder, environment);
	}
}


// Function used to display the buttons/sliders, etc of the Graphic User Interface
void display_gui()
{
	ImGui::Checkbox("Frame",     &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}


// This function is called everytime the window is resized
void window_size_callback(GLFWwindow* , int width, int height)
{
	inputs.window = { width, height };
}


// This function is called everytime the mouse is moved
void mouse_move_callback(GLFWwindow* /*window*/, double xpos, double ypos)
{
	inputs.mouse_position_update({ xpos, ypos });

	vec2 const& p1 = inputs.mouse.position.current;
	vec2 const& p0 = inputs.mouse.position.previous;

	bool const event_valid = !inputs.mouse.on_gui;
	bool const click_left  = inputs.mouse.click.left;
	bool const click_right = inputs.mouse.click.right;
	bool const ctrl = inputs.keyboard.ctrl;

	if (event_valid) { // If the mouse cursor is not on the ImGui area

		if (click_left && !ctrl)     // Rotation of the camera around its center
			environment.camera.manipulator_rotate_trackball(p0, p1);
		else if (click_left && ctrl) // Translate/Pan the camera in the viewspace plane
			environment.camera.manipulator_translate_in_plane(p1 - p0);
		else if (click_right)        // Move the camera closer/further with respect to its center
			environment.camera.manipulator_scale_distance_to_center((p1 - p0).y);
	}
}

// This function is called everytime a mouse button is clicked/released
void mouse_click_callback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
{
	inputs.mouse.click.update_from_glfw_click(button, action);
}

// This function is called everytime a keyboard touch is pressed/released
void keyboard_callback(GLFWwindow* /*window*/, int key, int, int action, int /*mods*/)
{
	inputs.keyboard.update_from_glfw_key(key, action);
}

// This function is used to send the uniform parameters associated to the current environment
void opengl_uniform(GLuint shader, scene_environment const& current_environment)
{
	opengl_uniform(shader, "projection", current_environment.projection.matrix());
	opengl_uniform(shader, "view", current_environment.camera.matrix_view());
	opengl_uniform(shader, "light", current_environment.light, false);
}



