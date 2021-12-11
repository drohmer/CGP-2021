#pragma once

#include "cgp/cgp.hpp"


// The structure of the custom scene
struct scene_structure {
	
	cgp::scene_environment_basic environment; // Standard environment controler
	cgp::inputs_interaction_parameters inputs; // storage for the current values of the inputs (mouse, keyboard, window dimension) that can be use for interaction purpose

	// Store the curve sketched on screen. 
	//   Each new stroke (continuous click+motion of the mouse) is a new element of the buffer
	cgp::buffer<cgp::curve_dynamic_drawable> sketch_drawable; 



	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop


	// Add new points in the sketch_drawable
	void mouse_move();

	// Add a new stroke in the sketch_drawable
	void mouse_click();


};





