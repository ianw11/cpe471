attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

varying vec3 vColor;
varying vec2 vTexCoord;

uniform int isGround;

void main() {
  vec4 vPosition;

  /* First model transforms */
  gl_Position = uProjMatrix*uViewMatrix*uModelMatrix*vec4(aPosition, 1);

  /* a color that could be blended - or be shading */
   if (isGround == 0) {
      vColor = vec3(0.4, 0.1, 0.4);
   } else {
      vColor = vec3(0.6, 0.6, 0.1);
   }
  /* pass through the texture coordinates to be interpolated */
  vTexCoord = aTexCoord;
}
