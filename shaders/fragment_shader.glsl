#version 330 core
out vec4 FragColor;
// don't work :D
void main() {
    vec2 fragCoord = gl_FragCoord.xy / vec2(800.0, 600.0);

    float edgeThreshold = 0.005;
    if (fragCoord.x < edgeThreshold || fragCoord.x > 1.0 - edgeThreshold ||
        fragCoord.y < edgeThreshold || fragCoord.y > 1.0 - edgeThreshold) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
}