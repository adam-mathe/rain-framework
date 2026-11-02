#version 330 core
layout(location = 0) in vec3 vert_pos;
layout(location = 1) in vec2 uv;

uniform mat4 model, projection;

out vec2 UV;

void main() {
    UV = uv;

    gl_Position = projection * model * vec4(vert_pos, 1.0);
}
