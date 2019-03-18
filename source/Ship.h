//
//  Ship.h
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#ifndef __Asteroids__Ship__
#define __Asteroids__Ship__

#include "common.h"
#include "Bullet.h"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15

class Ship{

  //Placeholders so everything compiles.  Customize for your ship
	vec2 ship_vert[6];
	vec3 ship_color[6];

	vec2 thruster_vert[6];
	vec3 thruster_color[6];

	vec2 end_vert[4];
	vec3 end_color[4];
    
public:
  //Record of the ship's state
  struct {
    vec2 cur_location;   //Current position of the center
    float angle;         //Rotation angle
    vec2 pointing;       //Vector pointing to the front of the ship
	//This function will be helpful to keep track of the direction the ship
    //is pointing
    mat2 RotateZ2D( const GLfloat theta ){
      GLfloat angle = DegreesToRadians * theta;
      mat2 c;
      c[0][0] = c[1][1] = cos(angle);
      c[1][0] = sin(angle);
      c[0][1] = -c[1][0];
      return c;
    }
	mat2 Translate2D(const GLfloat x, const GLfloat y)
	{
		mat2 c;
		c[0][1] = x;
		c[1][1] = y;
		
		return c;
	}
    vec2 velocity;       //Velocity
    bool thruster_on;    //Boolean if a thruster is on
	bool end_game;       //Boolean if ship hits an asteroid
  } state;
  
  //OpenGL variables for a ship
  struct {
    GLuint vao;           //Vertex array object
    GLuint program;       //shader program
    GLuint buffer;        //Vertex buffer objects
    GLuint vertex_shader, fragment_shader;  //Shaders
    GLint  vpos_location, vcolor_location;   //reference to pos and color in shaders
    GLint  M_location;     //Reference to matrix in shader
  } GLvars;

  //OpenGL variables for thruster
  struct {
	  GLuint vao;           //Vertex array object
	  GLuint program;       //shader program
	  GLuint buffer;        //Vertex buffer objects
	  GLuint vertex_shader, fragment_shader;  //Shaders
	  GLint  vpos_location, vcolor_location;   //reference to pos and color in shaders
	  GLint  M_location;     //Reference to matrix in shader
  } THvars;

  struct {
	  GLuint vao;           //Vertex array object
	  GLuint program;       //shader program
	  GLuint buffer;        //Vertex buffer objects
	  GLuint vertex_shader, fragment_shader;  //Shaders
	  GLint  vpos_location, vcolor_location;   //reference to pos and color in shaders
	  GLint  M_location;     //Reference to matrix in shader

  }Endvars;

public:
  

  Ship();
  
  inline void start_thruster(){ state.thruster_on= true;}
  inline void stop_thruster() { state.thruster_on= false;}
  inline void hitendgame() { state.end_game = true; }
  inline void rotateLeft() {
    //Do something
	  vec2 center = ship_vert[2];
      mat2 L =state.RotateZ2D(-5);
	 //float tx = thruster_vert[0].x;
	 //float ty = thruster_vert[0].y;
	  for (unsigned int i = 0; i <3; i++) {
		//  thruster_vert[i] = L * (thruster_vert[i]+vec2(-tx,-ty))+ vec2(tx,ty);
		 // thruster_vert[i] = state.Translate2D(-tx, -ty)*L *state.Translate2D(tx,ty)* thruster_vert[i];
		  thruster_vert[i] = thruster_vert[i] - center;
		  thruster_vert[i] = L* thruster_vert[i];
		  thruster_vert[i] = thruster_vert[i] + center;
	  }
	  //float sx = ship_vert[2].x;
	  //float sy = ship_vert[2].y;
      for(unsigned int i=0;i <4; i++){
      //ship_vert[i] = L * (ship_vert[i]+vec2(-sx,-sy))-vec2(sx,sy);
		//  ship_vert[i] = state.Translate2D(-sx, -sy)*L *state.Translate2D(tx, ty)* ship_vert[i];
		  ship_vert[i] = ship_vert[i] - center;
		  ship_vert[i] = L * ship_vert[i];
		  ship_vert[i] = ship_vert[i] + center;
      }
	  
  }
  inline void rotateRight(){
    //Do something
	  vec2 center = ship_vert[2];
      mat2 R =state.RotateZ2D(5);
	  for (unsigned int i = 0; i <3; i++) {
		  thruster_vert[i] = thruster_vert[i] - center;
		  thruster_vert[i] = R * thruster_vert[i];
		  thruster_vert[i] = thruster_vert[i] + center;
	  }
      for(unsigned int i=0;i <4; i++){
		  ship_vert[i] = ship_vert[i] - center;
          ship_vert[i] = R * ship_vert[i];
		  ship_vert[i] = ship_vert[i] + center;
      }
	 
  }

 
  void update_state();
  
  void gl_init();  
  
  void draw(mat4 proj);

  Bullet* pew_pew();
 
};


#endif /* defined(__Asteroids__Ship__) */
