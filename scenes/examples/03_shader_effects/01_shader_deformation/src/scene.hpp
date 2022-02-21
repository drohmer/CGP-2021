#pragma once

/** This file contains the custom function signature and structure associated the scene 
*  The (*) indicates elements that are specific to the use of the shader_deformation  */

#include "cgp/cgp.hpp"
#include "deformation/deformation.hpp" 


// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame = true;
};


// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	scene_environment_with_shader_deformation environment; // The specific scene environment associated to the deforming shader (*)
	
	cgp::mesh_drawable global_frame;    // The standard global frame
	cgp::mesh_drawable grid;            // The grid that is deformed by the shader


	cgp::timer_basic timer; // A basic timer for the procedural deformation of the shape
	gui_parameters gui;     // The standard GUI element storage
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	

	
	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





