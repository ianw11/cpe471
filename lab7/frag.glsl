varying vec3 vCol;

varying vec3 iNor;
varying vec3 iLight;

uniform vec3 ambient;

uniform int doDumbWay;

void main()
{
   if (doDumbWay == 0) {
      // Do dot product
      float dotProd = dot(normalize(iNor), normalize(iLight));
      float coef = 0.0 > dotProd ? 0.0 : dotProd;
      
      gl_FragColor = (coef * vec4(vCol.r, vCol.g, vCol.b, 1.0)) + vec4((.15 * ambient), 1.0);
   } else {
	   gl_FragColor = vec4(vCol.r, vCol.g, vCol.b, 1.0);
	}
}
