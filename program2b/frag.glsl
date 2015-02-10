varying vec3 vCol;

uniform int colorType;

varying vec3 unitNormal;
varying vec3 unitView;

uniform mat4 MV;

void main()
{
   if (colorType == 0) {
      gl_FragColor = vec4(0, 0, 0, 1.0);
   } else if (colorType == 1) {
	   gl_FragColor = vec4(vCol.r, vCol.g, vCol.b, 1.0);
	} else if (colorType == 2) {
	   gl_FragColor = vec4(1, 1, 1, .2);
	} else if (colorType == 3) {
	   float dot = unitNormal.x * unitView.x + unitNormal.y * unitView.y + unitNormal.z * unitView.z;
	   
	   if (dot < 0.2) {
	      discard;
	   } else {
	      gl_FragColor = vec4(1, 1, 1, .3);
	   }
	}
}
