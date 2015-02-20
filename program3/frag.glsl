varying vec3 vCol;

varying vec3 iNor;
varying vec3 lVector;
varying vec3 vPos;

uniform vec3 uLightPos;
uniform vec3 UaColor;
uniform vec3 UdColor;
uniform vec3 UsColor;

uniform float Ushine; // Shiny-ness coefficient
uniform int uShadeModel; // Which shading do we do

void main()
{
   if (uShadeModel == 1) {
      gl_FragColor = vec4(vCol.r, vCol.g, vCol.b, 1.0);
   } else {
      vec3 vVec = vec3(0.0, 0.0, 0.0) - vPos;
      vec3 hVec = normalize( (lVector + vVec) );
      
      vec3 specular = pow(dot(iNor, hVec), Ushine) * UsColor;
      vec3 diffuse = dot(iNor, lVector) * UdColor;
      
      vec3 refl = UaColor + specular + diffuse;
      
	   gl_FragColor = vec4(refl.r, refl.g, refl.b, 1.0);
	}
}
