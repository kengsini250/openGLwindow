//uniform vec3 fragColor;
varying vec3 fragColor;

void main()
{
	gl_FragColor = vec4(fragColor,1.0);
}