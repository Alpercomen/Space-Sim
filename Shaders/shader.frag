#version 330 core

in float vHeight;
out vec4 FragColor;

void main()
{
    // Remap height from [-1, 1] to [0, 1]
    float height = vHeight * 0.5 + 0.5;

    // Example gradient colors
    vec3 bottomColor = vec3(0.03, 0.07, 0.16); // dark blue
    vec3 topColor = vec3(0.45, 0.59, 0.81);    // light blue

    vec3 finalColor = mix(bottomColor, topColor, height);
    FragColor = vec4(finalColor, 1.0);
}