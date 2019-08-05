attribute vec3 Pos;
attribute vec3 fragPos;

varying vec3 fragColor;

void main()
{
	gl_Position = vec4(Pos,1.0);
	fragColor = fragPos;
}