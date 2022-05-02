#pragma once

#include "../implementation/buffer_stack.hpp"
#include "../implementation/buffer_stack2.hpp"
#include "../implementation/buffer_stack3.hpp"
#include "../implementation/buffer_stack4.hpp"



namespace cgp
{
    /* ************************************************** */
    /*        Helper type declaraction                    */
    /* ************************************************** */
    template <typename T> using  buffer_stack2 = buffer_stack<T, 2>;
    template <typename T> using  buffer_stack3 = buffer_stack<T, 3>;
    template <typename T> using  buffer_stack4 = buffer_stack<T, 4>;

    using int2 = buffer_stack2<int>;
    using int3 = buffer_stack3<int>;
    using int4 = buffer_stack4<int>;

    using uint2 = buffer_stack2<unsigned int>;
    using uint3 = buffer_stack3<unsigned int>;
    using uint4 = buffer_stack4<unsigned int>;

    using vec2 = buffer_stack2<float>;
    using vec3 = buffer_stack3<float>;
    using vec4 = buffer_stack4<float>;


    std::string type_str(int2 const&);
    std::string type_str(int3 const&);
    std::string type_str(int4 const&);
    std::string type_str(uint2 const&);
    std::string type_str(uint3 const&);
    std::string type_str(uint4 const&);

    std::string type_str(vec2 const&);
    std::string type_str(vec3 const&);
    std::string type_str(vec4 const&);

}