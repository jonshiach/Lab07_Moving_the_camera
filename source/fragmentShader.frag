#version 330 core

// Interpolated values from the vertex shaders
in vec2 uv;

// Output data
out vec3 colour;

// Values that stay constant for the whole mesh
uniform sampler2D texture1Sampler;

void main ()
{
    // Output colour = colour of the texture at (u, v)
    colour = texture(texture1Sampler, uv).rgb;
}
