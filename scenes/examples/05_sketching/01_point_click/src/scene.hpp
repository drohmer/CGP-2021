#pragma once

#include "cgp/cgp.hpp"


// The structure of the custom scene
struct scene_structure {
	
	cgp::scene_environment_basic environment; // Standard environment controler
	cgp::inputs_interaction_parameters inputs; // User inputs (mouse, keyboard, etc)
	
	cgp::buffer<cgp::vec3> points; // Stores every clicked position
	cgp::mesh_drawable sphere; // Sphere used to display the clicked points



	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui();


	// Add a new clicked point
	void mouse_click();


};





