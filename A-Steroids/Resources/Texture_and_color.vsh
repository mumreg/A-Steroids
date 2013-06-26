attribute vec4 position;
attribute vec2 texCoordIn;
attribute vec4 colorIn;

uniform mat4 modelView;
uniform mat4 projection;

varying vec4 colorOut;
varying vec2 texCoordOut;

void main()
{
    gl_Position = projection * modelView * position;
    colorOut = colorIn;
    texCoordOut = texCoordIn;
}
