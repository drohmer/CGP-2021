#pragma once

#include "cgp/containers/matrix_stack/matrix_stack_fwd.hpp"
#include "cgp/containers/buffer_stack/buffer_stack_fwd.hpp"



namespace cgp
{
    using vec2 = buffer_stack<float, 2>;
    using vec3 = buffer_stack<float, 3>;
    using vec4 = buffer_stack<float, 4>;

    using mat2 = matrix_stack<float, 2, 2>;
    using mat3 = matrix_stack<float, 3, 3>;
    using mat4 = matrix_stack<float, 4, 4>;
}