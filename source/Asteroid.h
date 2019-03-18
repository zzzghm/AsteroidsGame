//
//  
//  Asteroid.h
//
//  Created by Brian Summa on 6/5/15.
//

#ifndef __Asteroids__Asteroid__
#define __Asteroids__Asteroid__

#include "common.h"
#include "AsteroidSmall.h"
#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15

class Asteroid {

	//Placeholders so everything compiles.  Customize for your ship
	vec2 asteroid_vert[8];
	vec3 asteroid_color[8];

	
public:
	//Record of the ship's state
	struct {
		vec2 cur_location;   //Current position of the center
		float angle;         //Rotation angle
		vec2 pointing;       //Vector pointing to the front of the ship
							 //This function will be helpful to keep track of the direction the ship
							 //is pointing
		mat2 RotateZ2D(const GLfloat theta) {
			GLfloat angle = DegreesToRadians * theta;
			mat2 c;
			c[0][0] = c[1][1] = cos(angle);
			c[1][0] = sin(angle);
			c[0][1] = -c[1][0];
			return c;
		}
		
		mat2 R = RotateZ2D(0.5);
		
		vec2 velocity;       //Velocity
		bool thruster_on;    //Boolean if a thruster is on
	} Astate;

	//OpenGL variables for a ship
	struct {
		GLuint vao;           //Vertex array object
		GLuint program;       //shader program
		GLuint buffer;        //Vertex buffer objects
		GLuint vertex_shader, fragment_shader;  //Shaders
		GLint  vpos_location, vcolor_location;   //reference to pos and color in shaders
		GLint  M_location;     //Reference to matrix in shader
	} ASvars;


public:


	Asteroid();

	inline void start_thruster() { Astate.thruster_on = true; }
	inline void stop_thruster() { Astate.thruster_on = false; }

	inline void rotateLeft() {
		//Do something
	}
	inline void rotateRight() {
		//Do something
	}

	void update_state();

	void gl_init();

	void draw(mat4 proj);

	AsteroidSmall* new_Asteroid();

	bool Asteroid::PointInPolygon(Bullet *b);

	bool Asteroid::ShipHitAsteroid(Ship s);
};


#endif /* defined(__Asteroids__Asteroid__) */

