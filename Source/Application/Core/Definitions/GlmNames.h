#pragma once

#include <Application/Core/Definitions/Definitions.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Math
{
    constexpr float32 Pi = 3.14159265358979323846f;

    using namespace glm;

    template<Arithmetic T>
    using Quat = glm::tquat<T>;

    template<Arithmetic T>
    using Vec2 = glm::tvec2<T>;

    template<Arithmetic T>
    using Vec3 = glm::tvec3<T>;

    template<Arithmetic T>
    using Vec4 = glm::tvec4<T>;

    template<Arithmetic T>
    using Mat2 = glm::tmat2x2<T>;

    template<Arithmetic T>
    using Mat3 = glm::tmat3x3<T>;

    template<Arithmetic T>
    using Mat4 = glm::tmat4x4<T>;

    using Quatf = Quat<float32>;
    using Quatd = Quat<float64>;

    using Vec2uc = Vec2<uint8>;
    using Vec3uc = Vec3<uint8>;
    using Vec4uc = Vec4<uint8>;

    using Vec2f = Vec2<float32>;
    using Vec3f = Vec3<float32>;
    using Vec4f = Vec4<float32>;

    using Vec2d = Vec2<float64>;
    using Vec3d = Vec3<float64>;
    using Vec4d = Vec4<float64>;

    using Vec2i = Vec2<int32>;
    using Vec3i = Vec3<int32>;
    using Vec4i = Vec4<int32>;

    using Vec2u = Vec2<uint32>;
    using Vec3u = Vec3<uint32>;
    using Vec4u = Vec4<uint32>;

    using Mat2f = Mat2<float32>;
    using Mat3f = Mat3<float32>;
    using Mat4f = Mat4<float32>;

    using Mat2d = Mat2<float64>;
    using Mat3d = Mat3<float64>;
    using Mat4d = Mat4<float64>;
} // namespace Math