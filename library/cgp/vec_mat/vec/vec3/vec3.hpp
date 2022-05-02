#pragma once

#include "cgp/containers/buffer_stack/buffer_stack.hpp"

// vec3 is an alias on buffer_stack<float, 3>
// Its implementation can be found in file cgp/containers/buffer_stack/buffer_stack3.hpp

// A vec3 struct can be used as
//   struct vec3 { float x, y, z; }
//   (with additional functions handled as a buffer_stack)

