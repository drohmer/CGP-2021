# Example codes

Various examples of usage of CGP elements, as well as additional OpenGL effects implemented in the CGP context.

* [Basic test scene of CGP](00_cgp_example/)

## CGP Usage

Direct use of CGP structures to achieve various effects.

* [CGP initialization (no 3D)](01_cgp_usage/01_basic_usage/00_cgp_init/)
* [Basic 3D scene in a single file](01_cgp_usage/01_basic_usage/01_default_scene_single_raw_file/)
* [Basic 3D scene with standard file organization](01_cgp_usage/01_basic_usage/02_default_scene_with_scene_helper/)
* [Load an external mesh (.obj)](01_cgp_usage/01_basic_usage/03_mesh_load_file_obj/)
* [Dynamical shape update](01_cgp_usage/01_basic_usage/04_shape_evolving_dynamically/)

* [Hierarchical animated shape with textures](01_cgp_usage/02_hierarchy/01_hierarchy_with_textures/)

* [Simple call to Marching Cube](01_cgp_usage/03_implicit_surface/01_marching_cube_simple)
* [Dynamically updated Marching Cube](01_cgp_usage/03_implicit_surface/02_marching_cube_with_dynamic_gui)

## Camera

Extending the camera toward additional behavior.

* [Flying mode](02_camera/01_camera_fly_mode/)
* [Multiple cameras](02_camera/02_multiple_scene_and_cameras/)

## Shader effects

Using custom shaders beyond the default mesh display with Phong shading.

* [Computing deformation in a shader](03_shader_effects/01_shader_deformation/)
* [Use of multiple shaders](03_shader_effects/02_multiple_shaders/)
* [Transparency in textures](03_shader_effects/03_transparent_billboards/)
* [Multi-texturing](03_shader_effects/04_multiple_textures_with_blending/)
* [Multiple lights and fog](03_shader_effects/05_multiple_lights/)
* [Multipass and framebuffer](03_shader_effects/06_framebuffer_multipass/)


## Classical effects

Additional standard OpenGL effects implemented in the CGP context.

* [Skybox](04_classical_effects/01_skybox/)
* [Environmental map](04_classical_effects/02_environment_map/)
* [Shadow map](04_classical_effects/03_shadow/)

## Sketching

Example of direct drawings on screen

* [Point click](05_sketching/01_point_click/)
* [Curve sketch](05_sketching/02_curve_sketch/)
