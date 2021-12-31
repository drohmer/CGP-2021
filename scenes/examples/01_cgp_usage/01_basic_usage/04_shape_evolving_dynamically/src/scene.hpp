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
	cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	gui_parameters gui;                       // Standard GUI element storage
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //
	cgp::timer_basic timer;

	// We keep two elements in memory:
	//  - The mesh structure whose buffers can be modified at every frame
	//  - The mesh_drawable structure (as usual) that is displayed and dynamically updated from the mesh.
	cgp::mesh mesh_shape;
	cgp::mesh_drawable drawable;
	


	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





