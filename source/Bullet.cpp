//
//  Bullet.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"
//Bullet constructor
Bullet::Bullet(vec2 pos, vec2 vel, vec2 dir) {
	Bstate.pos = pos;
	Bstate.vel = vel;
	Bstate.dir = dir;
};




//Called everytime an animation tick happens
void Bullet::update_state() {
	float dt = 0.033;
	float magnitude_vel = sqrt(Bstate.vel.x*Bstate.vel.x+ Bstate.vel.y*Bstate.vel.y);
	for (unsigned int i = 0; i < 4; i++) {
		bullet_vert[i] = bullet_vert[i]+ Bstate.dir*dt*magnitude_vel*6;
	}
	Bstate.pos = bullet_vert[0];

	// Create a vertex array object
	glGenVertexArrays(1, &BLvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(BLvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &BLvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, BLvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_vert) + sizeof(bullet_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bullet_vert), bullet_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bullet_vert), sizeof(bullet_color), bullet_color);

	glEnableVertexAttribArray(BLvars.vpos_location);
	glEnableVertexAttribArray(BLvars.vcolor_location);

	glVertexAttribPointer(BLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(BLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(bullet_vert)));

	glBindVertexArray(0);

}

//Initialize the gl state and variables
void Bullet::gl_init() {
	//Bullet
	//!!!!!!!!Populate bullet_vert and bullet_color
	bullet_vert[0] = Bstate.pos;
	bullet_vert[1] = vec2(bullet_vert[0].x + 0.05, bullet_vert[0].y - 0.05);
	bullet_vert[2] = vec2(bullet_vert[0].x, bullet_vert[0].y - 0.1);
	bullet_vert[3] = vec2(bullet_vert[0].x - 0.05, bullet_vert[0].y - 0.05);

	bullet_color[0] = vec3((1, 1, 1));
	bullet_color[1] = vec3((1, 1, 1));
	bullet_color[2] = vec3((1, 1, 1));
	bullet_color[3] = vec3((1, 1, 1));

	std::string vshader = shader_path + "vshader_Bullet.glsl";
	std::string fshader = shader_path + "fshader_Bullet.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	BLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(BLvars.vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(BLvars.vertex_shader);
	check_shader_compilation(vshader, BLvars.vertex_shader);

	BLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(BLvars.fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(BLvars.fragment_shader);
	check_shader_compilation(fshader, BLvars.fragment_shader);

	BLvars.program = glCreateProgram();
	glAttachShader(BLvars.program, BLvars.vertex_shader);
	glAttachShader(BLvars.program, BLvars.fragment_shader);

	glLinkProgram(BLvars.program);
	check_program_link(BLvars.program);

	glBindFragDataLocation(BLvars.program, 0, "fragColor");

	BLvars.vpos_location = glGetAttribLocation(BLvars.program, "vPos");
	BLvars.vcolor_location = glGetAttribLocation(BLvars.program, "vColor");
	BLvars.M_location = glGetUniformLocation(BLvars.program, "M");

	// Create a vertex array object
	glGenVertexArrays(1, &BLvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(BLvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &BLvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, BLvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_vert) + sizeof(bullet_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bullet_vert), bullet_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bullet_vert), sizeof(bullet_color), bullet_color);

	glEnableVertexAttribArray(BLvars.vpos_location);
	glEnableVertexAttribArray(BLvars.vcolor_location);

	glVertexAttribPointer(BLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(BLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(bullet_vert)));

	glBindVertexArray(0);


}


//Draw a ship
void Bullet::draw(mat4 proj) {

	glUseProgram(BLvars.program);
	glBindVertexArray(BLvars.vao);

	//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(BLvars.M_location, 1, GL_TRUE, proj);

	//Draw something
	glBindVertexArray(BLvars.vao);
	//glDrawArrays(GL_POINTS, 0, 1);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	/*if (Bstate.fire_on) {
		//Maybe draw something different if the thruster is on
		glBindVertexArray(BLvars.vao);
		glDrawArrays(GL_POINTS, 0, 4);
	}*/

	glBindVertexArray(0);
	glUseProgram(0);

}
