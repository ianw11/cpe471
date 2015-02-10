attribute vec4 aPos;
attribute vec3 aNor;
uniform mat4 P;
uniform mat4 MV;
varying vec3 vCol;

varying vec3 unitView;
varying vec3 unitNormal;

void main()
{
	gl_Position = P * MV * aPos;
	vCol = 0.5*(aNor + 1.0);
	
	vec4 tempNormal = vec4(vCol, 1.0);
	vec4 something = tempNormal * MV;
	float normalLen = sqrt(pow(something.x, 2.0) + pow(something.y, 2.0) + pow(something.z, 2.0));
	unitNormal = vec3(something.x / normalLen, something.y / normalLen, something.z / normalLen);
	
	unitView = vec3(0, 0, 1);
}
