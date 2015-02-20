varying vec3 vCol;

varying vec3 iNor;
varying vec3 lVector;
varying vec3 vPos;

attribute vec4 aPos;
attribute vec3 aNor;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

uniform vec3 uLightPos;
uniform vec3 UaColor;
uniform vec3 UdColor;
uniform vec3 UsColor;

uniform float Ushine; // Shiny-ness coefficient
uniform int uShadeModel; // Which shading do we do

uniform int forceNormals;

void main()
{
   iNor = normalize(uViewMatrix * uModelMatrix * vec4(aNor, 0.0)).xyz;
   
   vPos = normalize(uViewMatrix * uModelMatrix * aPos).xyz;
   lVector = normalize(uLightPos - vPos);
   
   if (uShadeModel == 1) {
      vec3 vVec = vec3(0.0, 0.0, 0.0) - vPos;
      vec3 hVec = normalize( (lVector + vVec) );
      
      vec3 specular = pow(dot(iNor, hVec), Ushine) * UsColor;
      vec3 diffuse = dot(iNor, lVector) * UdColor;
      
      vec3 refl = UaColor + specular + diffuse;
      
	   vCol = refl; // = vec4(refl.r, refl.g, refl.b, 1.0);
   } else {
      UaColor;
      UdColor;
      UsColor;
   }
   
   gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPos;
}
