
//
//  Ship.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"
//Ship constructor
Ship::Ship(){
  //Set up initial state here
	state.velocity = vec2(0,0);
	
	
};

//Called everytime an animation tick happens
void Ship::update_state() {
	// Things to do:
if (state.thruster_on==true) {	
	//a = F
	//Force is in the direction the ship is pointing
	float dt = 0.033;
	state.pointing=ship_vert[0]-ship_vert[2];
	vec2 F = state.pointing;
	vec2 accl = F*2;
	//Clamp acceleration at some maximum value
	if (accl.x > 10) { accl.x = 10; }
	if (accl.x < -10) { accl.x = -10; }
	if (accl.y > 10) { accl.y = 10; }
	if (accl.y < -10) { accl.y = -10; }
	//v  = old_velocity + a*dt
	vec2 vel = state.velocity + accl * dt*2;
	// clamp velocity at a maximum value
	if (vel.x > _MAX_SPEED) { vel.x = _MAX_SPEED; }
	if (vel.x < -_MAX_SPEED) { vel.x = -_MAX_SPEED; }
	if (vel.y > _MAX_SPEED) { vel.y = _MAX_SPEED; }
	if (vel.y < -_MAX_SPEED) { vel.y = -_MAX_SPEED; }

        //p  = old_position + v*dt	
		for (unsigned int i = 0; i < 4; i++)
		{
			ship_vert[i] = ship_vert[i] + vel*dt;
			state.velocity = vel;
		}


	for (unsigned int i = 0; i < 3; i++)
	{
		thruster_vert[i] = thruster_vert[i] + vel * dt;
		state.velocity = vel;
	}
}
       

// Dampen the velocity at every timestep to lessen intertia
 if (state.thruster_on==false) {
	//a = F
	//Force is in the direction the ship is pointing
	float dt = 0.033;
 	state.pointing = ship_vert[2] - ship_vert[0];
	//damping
	vec2 vel = state.velocity*_DAMPING;
	// clamp velocity at a maximum value
	if (vel.x > _MAX_SPEED) { vel.x = _MAX_SPEED; }
	if (vel.x < -_MAX_SPEED) { vel.x = -_MAX_SPEED; }
	if (vel.y > _MAX_SPEED) { vel.y = _MAX_SPEED; }
	if (vel.y < -_MAX_SPEED) { vel.y = -_MAX_SPEED; }

	//if (-0.1<vel.x <0.1 && -0.1<vel.y < 0.1) {
	//	vel.x = 0; 
	//    vel.y = 0; }
	
	//p  = old_position + v*dt
    for (unsigned int i = 0; i < 4; i++)
	{
		ship_vert[i] = ship_vert[i] + vel * dt;
		state.velocity = vel;
	}


	for (unsigned int i = 0; i < 3; i++)
	{
		thruster_vert[i] = thruster_vert[i] + vel * dt;
		state.velocity = vel;
	} 

	
}
   // state.velocity = _DAMPING * state.velocity;
	// Wrap the ship position when at the boundary
	//left
	if (ship_vert[0].x < -10 || ship_vert[1].x < -10 || ship_vert[2].x < -10 || ship_vert[3].x < -10) {
		ship_vert[2].x = 9.5;
		ship_vert[0] = vec2(ship_vert[2].x, ship_vert[2].y - 0.5);
		ship_vert[1] = vec2(ship_vert[2].x - 0.25, ship_vert[2].y + 0.25);
		ship_vert[3] = vec2(ship_vert[2].x + 0.25, ship_vert[2].y + 0.25);
		thruster_vert[0] = ship_vert[2];
		thruster_vert[1] = vec2(ship_vert[2].x + 0.125, ship_vert[2].y + 0.25);
		thruster_vert[2] = vec2(ship_vert[2].x - 0.125, ship_vert[2].y + 0.25);
	}
	//right
	if (ship_vert[0].x >10 || ship_vert[1].x >10 || ship_vert[2].x >10 || ship_vert[3].x >10) {
		ship_vert[2].x = -9.5;
		ship_vert[0] = vec2(ship_vert[2].x, ship_vert[2].y - 0.5);
		ship_vert[1] = vec2(ship_vert[2].x - 0.25, ship_vert[2].y + 0.25);
		ship_vert[3] = vec2(ship_vert[2].x + 0.25, ship_vert[2].y + 0.25);
		thruster_vert[0] = ship_vert[2];
		thruster_vert[1] = vec2(ship_vert[2].x + 0.125, ship_vert[2].y + 0.25);
		thruster_vert[2] = vec2(ship_vert[2].x - 0.125, ship_vert[2].y + 0.25);

	}
	//bottom
	if (ship_vert[0].y < -10 || ship_vert[1].y < -10 || ship_vert[2].y < -10 || ship_vert[3].y < -10) {
		ship_vert[2].y = -9.5;
		ship_vert[0] = vec2(ship_vert[2].x, ship_vert[2].y - 0.5);
		ship_vert[1] = vec2(ship_vert[2].x - 0.25, ship_vert[2].y + 0.25);
		ship_vert[3] = vec2(ship_vert[2].x + 0.25, ship_vert[2].y + 0.25);
		thruster_vert[0] = ship_vert[2];
		thruster_vert[1] = vec2(ship_vert[2].x + 0.125, ship_vert[2].y + 0.25);
		thruster_vert[2] = vec2(ship_vert[2].x - 0.125, ship_vert[2].y + 0.25);

	}
	//top
	if (ship_vert[0].y >10 || ship_vert[1].y >10 || ship_vert[2].y >10 || ship_vert[3].y >10) {
		ship_vert[2].y = 9.75;
		ship_vert[0] = vec2(ship_vert[2].x, ship_vert[2].y - 0.5);
		ship_vert[1] = vec2(ship_vert[2].x - 0.25, ship_vert[2].y + 0.25);
		ship_vert[3] = vec2(ship_vert[2].x + 0.25, ship_vert[2].y + 0.25);
		thruster_vert[0] = ship_vert[2];
		thruster_vert[1] = vec2(ship_vert[2].x + 0.125, ship_vert[2].y + 0.25);
		thruster_vert[2] = vec2(ship_vert[2].x - 0.125, ship_vert[2].y + 0.25);
	}

    state.cur_location = ship_vert[0];
	state.pointing = ship_vert[0] - ship_vert[2];
	// Create a vertex array object
	glGenVertexArrays(1, &GLvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(GLvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &GLvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, GLvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(ship_vert) + sizeof(ship_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ship_vert), ship_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(ship_vert), sizeof(ship_color), ship_color);

	glEnableVertexAttribArray(GLvars.vpos_location);
	glEnableVertexAttribArray(GLvars.vcolor_location);

	glVertexAttribPointer(GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ship_vert)));

	glBindVertexArray(0);

	//delete[] pos;

	
	// Create a fire vertex array object
	glGenVertexArrays(1, &THvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(THvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &THvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, THvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(thruster_vert) + sizeof(thruster_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(thruster_vert), thruster_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(thruster_vert), sizeof(thruster_color), thruster_color);

	glEnableVertexAttribArray(THvars.vpos_location);
	glEnableVertexAttribArray(THvars.vcolor_location);

	glVertexAttribPointer(THvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(THvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(thruster_vert)));

	glBindVertexArray(0);


	
}

//Initialize the gl state and variables
void Ship::gl_init(){
  //Ship

  //!!!!!!!!Populate ship_vert and ship_color
	//vec2 ship_vert[4];
	 ship_vert[2]= vec2(0,0);
	 ship_vert[0]= vec2(ship_vert[2].x, ship_vert[2].y -0.5);
     ship_vert[1]= vec2(ship_vert[2].x-0.25, ship_vert[2].y+0.25);
     ship_vert[3]= vec2(ship_vert[2].x+0.25, ship_vert[2].y+0.25);
	
	
	// vec3 ship_color[4];
	 ship_color[0] = vec3(1.0,1.0,1.0);
     ship_color[1] = vec3(1.0,1.0,1.0);
     ship_color[2] = vec3(1.0,1.0,1.0);
     ship_color[3] = vec3(1.0,1.0,1.0);



	// vec2 thruster_vert[3];
	/* thruster_vert[0] = ship_vert[2];
	 thruster_vert[1] = vec2(ship_vert[2].x+0.125,ship_vert[2].y+0.25);
	 thruster_vert[2] = vec2(ship_vert[2].x - 0.125, ship_vert[2].y + 0.25);*/
	
	 thruster_vert[0] = vec2(0,0);
	 thruster_vert[1] = vec2(0.125, 0.25);
	 thruster_vert[2] = vec2(- 0.125, 0.25);


	// vec3 thruster_color[3];
	thruster_color[0] = vec3(0.5,0.0,1.0);
    thruster_color[1] = vec3(0.5,0.0,1.0);
    thruster_color[2] = vec3(0.5,0.0,1.0);
   
	end_vert[0] = vec2(-5, 5);
	end_vert[1] = vec2(5, -5);
	end_vert[2] = vec2(5, 5);
	end_vert[3] = vec2(-5, -5);

	
	end_color[0] = vec3(1, 0, 0);
	end_color[1] = vec3(1, 0, 0);
	end_color[2] = vec3(1, 0, 0);
	end_color[3] = vec3(1, 0, 0);

  std::string vshader = shader_path + "vshader_Ship.glsl";
  std::string fshader = shader_path + "fshader_Ship.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars.vertex_shader);
  check_shader_compilation(vshader, GLvars.vertex_shader);
  
  GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars.fragment_shader);
  check_shader_compilation(fshader, GLvars.fragment_shader);
  
  GLvars.program = glCreateProgram();
  glAttachShader(GLvars.program, GLvars.vertex_shader);
  glAttachShader(GLvars.program, GLvars.fragment_shader);
  
  glLinkProgram(GLvars.program);
  check_program_link(GLvars.program);
  
  glBindFragDataLocation(GLvars.program, 0, "fragColor");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
    //Create GPU buffer to hold vertices and color
    glBufferData( GL_ARRAY_BUFFER, sizeof(ship_vert) + sizeof(ship_color), NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(ship_vert), ship_vert );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(ship_vert), sizeof(ship_color), ship_color );
    
    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location );
    
    glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ship_vert)) );
    
    glBindVertexArray(0);
 

	THvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(THvars.vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(THvars.vertex_shader);
	check_shader_compilation(vshader, THvars.vertex_shader);

	THvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(THvars.fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(THvars.fragment_shader);
	check_shader_compilation(fshader, THvars.fragment_shader);

	THvars.program = glCreateProgram();
	glAttachShader(THvars.program, THvars.vertex_shader);
	glAttachShader(THvars.program, THvars.fragment_shader);

	glLinkProgram(THvars.program);
	check_program_link(THvars.program);

	glBindFragDataLocation(THvars.program, 0, "fragColor");

	THvars.vpos_location = glGetAttribLocation(THvars.program, "vPos");
	THvars.vcolor_location = glGetAttribLocation(THvars.program, "vColor");
	THvars.M_location = glGetUniformLocation(THvars.program, "M");

    // Create a fire vertex array object
    glGenVertexArrays( 1, &THvars.vao );
    //Set GL state to use vertex array object
    glBindVertexArray( THvars.vao );
    
    //Generate buffer to hold our vertex data
    glGenBuffers( 1, &THvars.buffer );
    //Set GL state to use this buffer
    glBindBuffer( GL_ARRAY_BUFFER, THvars.buffer );
    
    //Create GPU buffer to hold vertices and color
    glBufferData( GL_ARRAY_BUFFER, sizeof(thruster_vert) + sizeof(thruster_color), NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(thruster_vert), thruster_vert);
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(thruster_vert), sizeof(thruster_color), thruster_color );
    
    glEnableVertexAttribArray(THvars.vpos_location);
    glEnableVertexAttribArray(THvars.vcolor_location );
    
    glVertexAttribPointer( THvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( THvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(thruster_vert)) );
    
    glBindVertexArray(0);
    
	Endvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Endvars.vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(Endvars.vertex_shader);
	check_shader_compilation(vshader, Endvars.vertex_shader);

	Endvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Endvars.fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(Endvars.fragment_shader);
	check_shader_compilation(fshader, Endvars.fragment_shader);

	Endvars.program = glCreateProgram();
	glAttachShader(Endvars.program, Endvars.vertex_shader);
	glAttachShader(Endvars.program, Endvars.fragment_shader);

	glLinkProgram(Endvars.program);
	check_program_link(Endvars.program);

	glBindFragDataLocation(Endvars.program, 0, "fragColor");

	Endvars.vpos_location = glGetAttribLocation(Endvars.program, "vPos");
	Endvars.vcolor_location = glGetAttribLocation(Endvars.program, "vColor");
	Endvars.M_location = glGetUniformLocation(Endvars.program, "M");

	// Create a fire vertex array object
	glGenVertexArrays(1, &Endvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(Endvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &Endvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, Endvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(end_vert) + sizeof(end_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(end_vert), end_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(end_vert), sizeof(end_color), end_color);

	glEnableVertexAttribArray(Endvars.vpos_location);
	glEnableVertexAttribArray(Endvars.vcolor_location);

	glVertexAttribPointer(Endvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(Endvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(end_vert)));

	glBindVertexArray(0);

}

//Draw a ship
void Ship::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
   
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj );
  
  //Draw something
    glBindVertexArray( GLvars.vao );
    glDrawArrays(GL_LINE_LOOP, 0, 4);
if (state.end_game) {
	glUseProgram(Endvars.program);
	glBindVertexArray(Endvars.vao);


	//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(Endvars.M_location, 1, GL_TRUE, proj);

	//Draw something
	glBindVertexArray(Endvars.vao);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	}
  if(state.thruster_on){
    //Maybe draw something different if the thruster is on
	  glUseProgram(THvars.program);
	  glBindVertexArray(THvars.vao);
	  //If you have a modelview matrix, pass it with proj
	  glUniformMatrix4fv(THvars.M_location, 1, GL_TRUE, proj);
	
	  glBindVertexArray(THvars.vao);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	  //fire bullet
	  glUseProgram(GLvars.program);
	  glBindVertexArray(GLvars.vao);


	  //If you have a modelview matrix, pass it with proj
	  glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj);

	  //Draw something
	  glBindVertexArray(GLvars.vao);
	  glDrawArrays(GL_LINES, 4, 2);
	/*  glUseProgram(GLvars.program);
	  glBindVertexArray(GLvars.vao);


	  //If you have a modelview matrix, pass it with proj
	  glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj);

	  //Draw something
	  glBindVertexArray(GLvars.vao);
	  glDrawArrays(GL_LINE_LOOP, 0, 4);
	  glDrawArrays(GL_TRIANGLE_FAN, 4, 3);*/
  }

  glBindVertexArray(0);
  glUseProgram(0);

}


Bullet* Ship::pew_pew() {
	
	
	vec2  pos = state.cur_location;
	vec2  vel = state.velocity;
	vec2  dir = state.pointing;
	return new Bullet(pos,vel,dir);
	//bullet.push_back(new Bullets());
	
}
