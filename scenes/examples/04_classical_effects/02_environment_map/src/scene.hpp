#pragma once

#include "cgp/cgp.hpp"
#include "environment_map/environment_map.hpp"


enum shapes_enum { shape_sphere, shape_cylinder, shape_torus, shape_camel };

// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame     = true;
	bool display_wireframe = false;
	shapes_enum display_shape = shape_torus;
};




// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	cgp::mesh_drawable global_frame;          // The standard global frame
 	gui_parameters gui;                       // Standard GUI element storage
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)

											  // Standard environment controler with spherical coordinates
	scene_environment_with_environment_map environment;
	

	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //
	std::map<shapes_enum, cgp::mesh_drawable> shape;
	//cgp::mesh_drawable torus;    // The shape with the environment map 
	cgp::skybox_drawable skybox; // The skybox surrounding all the shapes


	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





