attribute vec4 position;
attribute vec4 colorIn;

uniform highp mat4 modelView;
//uniform mat4 projection;

varying vec4 colorOut;

void main()
{
    gl_Position = modelView * position;
    gl_PointSize = 5.0;
    colorOut = colorIn;
}
