#pragma once

#include "cgp/cgp.hpp"

// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame     = true;
	bool display_wireframe = false;
};



// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	cgp::mesh_drawable global_frame;          // The standard global frame
 	gui_parameters gui;                       // Standard GUI element storage

											  // Standard environment controler with spherical coordinates
	cgp::scene_environment_basic_camera_spherical_coords environment;
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	

	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //
	cgp::mesh_drawable torus; 
	cgp::skybox_drawable skybox;


	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





