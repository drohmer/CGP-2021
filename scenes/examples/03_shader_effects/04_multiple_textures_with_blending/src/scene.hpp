#pragma once

#include "cgp/cgp.hpp"
#include "mesh_drawable_multitexture/mesh_drawable_multitexture.hpp"

// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame = true;
};



// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	cgp::mesh_drawable global_frame;          // The standard global frame
	cgp::scene_environment_basic environment; // Standard environment controler
	gui_parameters gui;                       // Standard GUI element storage
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	// Use a slightly-modified mesh_drawable structure that stores 2 texture ID
	mesh_drawable_multitexture quad; 

	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





