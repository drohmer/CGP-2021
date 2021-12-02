#pragma once

#include "cgp/cgp.hpp"



// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame = false;
	bool wireframe     = false; // Display the wireframe of the implicit surface
	bool plain         = true;  // Display the implicit surface
	bool domain        = true;  // Display the box representing the domain of the marching cube
};


// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	cgp::mesh_drawable global_frame;     // The standard global frame
	cgp::mesh_drawable implicit_surface; // The shape of the implicit surface
	cgp::segments_drawable domain_box;   // A drawable representation of the box domain on the marching cube

	cgp::scene_environment_basic environment; // Standard environment controler
	gui_parameters gui;                       // Standard GUI element storage
	

	
	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





