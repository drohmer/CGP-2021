#pragma once

#include "cgp/cgp.hpp"
#include "shadow_map.hpp"


// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame     = true;
	bool display_wireframe = false;
	bool animated_shapes = true;
	bool animated_light = true;
};




// The structure of the custom scene
struct scene_structure {
	

	
	// ***************************************************** //	
	// Specific elements related to the shadow map effect
	// ***************************************************** //	
	// 
	// Specific environment that take into account a camera-like light for rendering the shadow map
	scene_environment_shadow_map environment; 

	// The structure handling the rendering for the shadow map
	shadow_map_structure shadow_map;


	// ***************************************************** //
	// Standard elements and shapes of the scene
	// ***************************************************** //	


	cgp::inputs_interaction_parameters inputs;
	cgp::mesh_drawable global_frame;
	gui_parameters gui;

	cgp::timer_basic timer;

	cgp::mesh_drawable sphere_light; //used to display the position of the light
	cgp::mesh_drawable sphere;
	cgp::mesh_drawable ground;
	cgp::mesh_drawable cube;
	cgp::mesh_drawable quad;

	void initialize();
	void display();
	void display_gui();

};





