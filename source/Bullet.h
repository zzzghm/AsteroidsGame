#pragma once
//
//  Bullet.h
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#ifndef __Asteroids__Bullet__
#define __Asteroids__Bullet__

#include "common.h"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15



class Bullet{


		vec2 bullet_vert[4];
		vec3 bullet_color[4];
	
public:
	struct {
		vec2 pos;   //Current position 
		vec2 vel;       //Velocity
		vec2 dir;
		bool fire_on;    //Boolean if a fire is on
	} Bstate;
	//OpenGL variables for a ship
	struct {
		GLuint vao;           //Vertex array object
		GLuint program;       //shader program
		GLuint buffer;        //Vertex buffer objects
		GLuint vertex_shader, fragment_shader;  //Shaders
		GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
		GLint M_location;     //Reference to matrix in shader
	} BLvars;

   
public:
	Bullet(vec2 pos, vec2 vel, vec2 dir);

	inline void start_fire() { Bstate.fire_on = true; }
	inline void stop_fire() { Bstate.fire_on = false; }

	inline void rotateLeft() {
		//Do something
	}
	inline void rotateRight() {
		//Do something
	}



	void update_state();

	void gl_init();

	void draw(mat4 proj);
	
};


#endif /* defined(__Asteroids__Bullet__) */