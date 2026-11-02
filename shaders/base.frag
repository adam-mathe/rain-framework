#version 330 core
out vec4 color;

in vec2 UV;

uniform sampler2D tex;

void main() {
    color = vec4(0.5, 0.0, 0.5, 1.0) * texture(tex, UV);
}
