#pragma once

#include <iostream>

namespace linear
{
    struct vec4
    {
        float x,y,z,w;
    };

    struct vec3
    {
        float x,y,z;

        vec3(float xx, float yy, float zz)
        {
            x = xx;
            y = yy;
            z = zz;
        }
    };

    struct mat4
    {
        linear::vec4 c[4] = {};
    };

    inline linear::mat4 identity()
    {
        linear::mat4 r;

        r.c[0].x = 1.0f;
        r.c[1].y = 1.0f;
        r.c[2].z = 1.0f;
        r.c[3].w = 1.0f;

        return r;
    };

    inline void translate(linear::mat4& m, const linear::vec3 pos)
    {
        m.c[3].x += pos.x;
        m.c[3].y += pos.y;
        m.c[3].z += pos.z;
    }

    inline void scale(linear::mat4& m, const linear::vec3 scale)
    {
        m.c[0].x *= scale.x;
        m.c[1].y *= scale.y;
        m.c[2].z *= scale.z;
    }

    inline void ortho(float r, float t)
    {

    }

    inline void print_mat4(const linear::mat4& m)
    {
        for(int i = 0; i < 4; i++)
        {
            const linear::vec4 *col = &m.c[i];

            std::cout << "PRINTING COLUMN #" << i << " " << col->x << "," << col->y << "," << col->z << "," << col->w << "\n";
        }
    }

    inline linear::mat4 MatMultiply(const linear::mat4& a, const linear::mat4& b)
    {
        linear::mat4 r;

        // First row
        r.c[0].x = (a.c[0].x * b.c[0].x) + (a.c[1].x * b.c[0].y) + (a.c[2].x * b.c[0].z) + (a.c[3].x * b.c[0].w);
        r.c[1].x = (a.c[0].x * b.c[1].x) + (a.c[1].x * b.c[1].y) + (a.c[2].x * b.c[1].z) + (a.c[3].x * b.c[1].w);
        r.c[2].x = (a.c[0].x * b.c[2].x) + (a.c[1].x * b.c[2].y) + (a.c[2].x * b.c[2].z) + (a.c[3].x * b.c[2].w);
        r.c[3].x = (a.c[0].x * b.c[3].x) + (a.c[1].x * b.c[3].y) + (a.c[2].x * b.c[3].z) + (a.c[3].x * b.c[3].w);

        // Second row
        r.c[0].y = (a.c[0].y * b.c[0].x) + (a.c[1].y * b.c[0].y) + (a.c[2].y * b.c[0].z) + (a.c[3].y * b.c[0].w);
        r.c[1].y = (a.c[0].y * b.c[1].x) + (a.c[1].y * b.c[1].y) + (a.c[2].y * b.c[1].z) + (a.c[3].y * b.c[1].w);
        r.c[2].y = (a.c[0].y * b.c[2].x) + (a.c[1].y * b.c[2].y) + (a.c[2].y * b.c[2].z) + (a.c[3].y * b.c[2].w);
        r.c[3].y = (a.c[0].y * b.c[3].x) + (a.c[1].y * b.c[3].y) + (a.c[2].y * b.c[3].z) + (a.c[3].y * b.c[3].w);

        // Third row
        r.c[0].z = (a.c[0].z * b.c[0].x) + (a.c[1].z * b.c[0].y) + (a.c[2].z * b.c[0].z) + (a.c[3].z * b.c[0].w);
        r.c[1].z = (a.c[0].z * b.c[1].x) + (a.c[1].z * b.c[1].y) + (a.c[2].z * b.c[1].z) + (a.c[3].z * b.c[1].w);
        r.c[2].z = (a.c[0].z * b.c[2].x) + (a.c[1].z * b.c[2].y) + (a.c[2].z * b.c[2].z) + (a.c[3].z * b.c[2].w);
        r.c[3].z = (a.c[0].z * b.c[3].x) + (a.c[1].z * b.c[3].y) + (a.c[2].z * b.c[3].z) + (a.c[3].z * b.c[3].w);

        // Fourth row
        r.c[0].w = (a.c[0].w * b.c[0].x) + (a.c[1].w * b.c[0].y) + (a.c[2].w * b.c[0].z) + (a.c[3].w * b.c[0].w);
        r.c[1].w = (a.c[0].w * b.c[1].x) + (a.c[1].w * b.c[1].y) + (a.c[2].w * b.c[1].z) + (a.c[3].w * b.c[1].w);
        r.c[2].w = (a.c[0].w * b.c[2].x) + (a.c[1].w * b.c[2].y) + (a.c[2].w * b.c[2].z) + (a.c[3].w * b.c[2].w);
        r.c[3].w = (a.c[0].w * b.c[3].x) + (a.c[1].w * b.c[3].y) + (a.c[2].w * b.c[3].z) + (a.c[3].w * b.c[3].w);

        return r;
    }
}
