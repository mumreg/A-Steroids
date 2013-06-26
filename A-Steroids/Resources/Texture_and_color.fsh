varying lowp vec4 colorOut;
varying lowp vec2 texCoordOut;

uniform sampler2D texture;

void main()
{
	gl_FragColor = colorOut * texture2D(texture, texCoordOut);
}