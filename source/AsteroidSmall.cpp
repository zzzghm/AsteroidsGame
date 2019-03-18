//
//  
//  Asteroids.cpp
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"


//Asteroid AsteroidSmallconstructor
AsteroidSmall::AsteroidSmall(vec2 pos) {
	//Set up initial state here
	ASstate.velocity = (vec2(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX))*2-vec2(1,1);
	ASstate.loc = pos;


};

//Called everytime an animation tick happens
void AsteroidSmall::update_state() {
	float dt = 0.033;
	//vec2 di = normalize(vec2(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX)-vec2(0.5,0.5));

	vec2 intvel = ASstate.velocity;
		for (unsigned int i = 0; i <  7; i++) {
			//rotate slowly over time
			vec2 center = asteroidsmall_vert[0];
			asteroidsmall_vert[i] = asteroidsmall_vert[i] - center;
			asteroidsmall_vert[i] = ASstate.R * asteroidsmall_vert[i];
			asteroidsmall_vert[i] = asteroidsmall_vert[i] + center;
			//constant velocity at a random direction	
			//asteroid_vert[i] = asteroid_vert[i] + di * Astate.velocity*dt;
			
			asteroidsmall_vert[i] = asteroidsmall_vert[i] + intvel * dt;
		}

		// Wrap the asteroid position when at the boundary
		//left
		for (unsigned int i = 0; i < 7; i++) {
			if (asteroidsmall_vert[i].x < -10) {
				asteroidsmall_vert[0].x = -9.75;
				asteroidsmall_vert[1] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[2] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y + 0.1);
				asteroidsmall_vert[3] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[4] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y - 0.05);
				asteroidsmall_vert[5] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y - 0.1);
				asteroidsmall_vert[6] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y - 0.05);
				ASstate.velocity.x = -ASstate.velocity.x;
			}
		}
		//right
		for (unsigned int i = 0; i <  7; i++) {
			if (asteroidsmall_vert[i].x > 10) {
				asteroidsmall_vert[0].x = 9.75;
				asteroidsmall_vert[1] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[2] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y + 0.1);
				asteroidsmall_vert[3] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[4] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y - 0.05);
				asteroidsmall_vert[5] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y - 0.1);
				asteroidsmall_vert[6] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y - 0.05);
				ASstate.velocity.x = -ASstate.velocity.x;
			}
		}
		
		//bottom
		for (unsigned int i = 0; i <  7; i++) {
			if (asteroidsmall_vert[i].y < -10) {
				asteroidsmall_vert[0].y = -9.75;
				asteroidsmall_vert[1] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[2] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y + 0.1);
				asteroidsmall_vert[3] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[4] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y - 0.05);
				asteroidsmall_vert[5] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y - 0.1);
				asteroidsmall_vert[6] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y - 0.05);
				ASstate.velocity.y = -ASstate.velocity.y;
			}
		}
		
		//top
		for (unsigned int i = 0; i <  7; i++) {
			if (asteroidsmall_vert[i].y > 10) {
				asteroidsmall_vert[0].y = 9.75;
				asteroidsmall_vert[1] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[2] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y + 0.1);
				asteroidsmall_vert[3] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y + 0.05);
				asteroidsmall_vert[4] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y - 0.05);
				asteroidsmall_vert[5] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y - 0.1);
				asteroidsmall_vert[6] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y - 0.05);
				ASstate.velocity.y = -ASstate.velocity.y;
			}
		}
		
	

	// Create a vertex array object                                                                                                                
	glGenVertexArrays(1, &ASSvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(ASSvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &ASSvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, ASSvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroidsmall_vert) + sizeof(asteroidsmall_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(asteroidsmall_vert), asteroidsmall_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(asteroidsmall_vert), sizeof(asteroidsmall_color), asteroidsmall_color);

	glEnableVertexAttribArray(ASSvars.vpos_location);
	glEnableVertexAttribArray(ASSvars.vcolor_location);

	glVertexAttribPointer(ASSvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(ASSvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(asteroidsmall_vert)));

	glBindVertexArray(0);

	ASstate.cur_location = asteroidsmall_vert[0];
}

//Initialize the gl state and variables
void AsteroidSmall::gl_init() {
	//Asteroid
	//!!!!!!!!Populate asteroid_vert and asteroid_color
	asteroidsmall_vert[0]= ASstate.loc;
	asteroidsmall_vert[1] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y + 0.05);
	asteroidsmall_vert[2] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y + 0.1);
	asteroidsmall_vert[3] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y + 0.05);
	asteroidsmall_vert[4] = vec2(asteroidsmall_vert[0].x - 0.1, asteroidsmall_vert[0].y - 0.05);
	asteroidsmall_vert[5] = vec2(asteroidsmall_vert[0].x + 0.05, asteroidsmall_vert[0].y - 0.1);
	asteroidsmall_vert[6] = vec2(asteroidsmall_vert[0].x + 0.1, asteroidsmall_vert[0].y - 0.05);
	

	for (int i = 0; i < 7; i++) {
		asteroidsmall_color[i] = vec3(1.0, 1.0, 1.0);
	}

	std::string vshader = shader_path + "vshader_Asteroid.glsl";
	std::string fshader = shader_path + "fshader_Asteroid.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	ASSvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ASSvars.vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(ASSvars.vertex_shader);
	check_shader_compilation(vshader, ASSvars.vertex_shader);

	ASSvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ASSvars.fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(ASSvars.fragment_shader);
	check_shader_compilation(fshader, ASSvars.fragment_shader);

	ASSvars.program = glCreateProgram();
	glAttachShader(ASSvars.program, ASSvars.vertex_shader);
	glAttachShader(ASSvars.program, ASSvars.fragment_shader);

	glLinkProgram(ASSvars.program);
	check_program_link(ASSvars.program);

	glBindFragDataLocation(ASSvars.program, 0, "fragColor");

	ASSvars.vpos_location = glGetAttribLocation(ASSvars.program, "vPos");
	ASSvars.vcolor_location = glGetAttribLocation(ASSvars.program, "vColor");
	ASSvars.M_location = glGetUniformLocation(ASSvars.program, "M");

	//draw asteroid
	// Create a vertex array object
	glGenVertexArrays(1, &ASSvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(ASSvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &ASSvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, ASSvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroidsmall_vert) + sizeof(asteroidsmall_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(asteroidsmall_vert), asteroidsmall_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(asteroidsmall_vert), sizeof(asteroidsmall_color), asteroidsmall_color);

	glEnableVertexAttribArray(ASSvars.vpos_location);
	glEnableVertexAttribArray(ASSvars.vcolor_location);

	glVertexAttribPointer(ASSvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(ASSvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(asteroidsmall_vert)));

	glBindVertexArray(0);

}

//Draw a asteroid
void AsteroidSmall::draw(mat4 proj) {

	glUseProgram(ASSvars.program);
	glBindVertexArray(ASSvars.vao);

	//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(ASSvars.M_location, 1, GL_TRUE, proj);

	//Draw something
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
	glDrawArrays(GL_LINE_LOOP, 0, 7);


	glBindVertexArray(0);
	glUseProgram(0);

}

//bullet hits asteroid
bool AsteroidSmall::PointInPolygon(Bullet *b) {
	int i, j, nvert = 6;
	bool flag = false;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((asteroidsmall_vert[i].y >= b->Bstate.pos.y) != (asteroidsmall_vert[j].y >= b->Bstate.pos.y)) &&
			(b->Bstate.pos.x <= (asteroidsmall_vert[j].x - asteroidsmall_vert[i].x) * (b->Bstate.pos.y - asteroidsmall_vert[i].y) / (asteroidsmall_vert[j].y - asteroidsmall_vert[i].y) + asteroidsmall_vert[i].x)
			)
			flag = !flag;
	}
	return flag;
}

//ship hits asteroid
bool AsteroidSmall::ShipHitAsteroid(Ship s) {
	int i, j, nvert = 6;
	bool flag = false;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((asteroidsmall_vert[i].y >= s.state.cur_location.y) != (asteroidsmall_vert[j].y >= s.state.cur_location.y)) &&
			(s.state.cur_location.x <= (asteroidsmall_vert[j].x - asteroidsmall_vert[i].x) * (s.state.cur_location.y - asteroidsmall_vert[i].y) / (asteroidsmall_vert[j].y - asteroidsmall_vert[i].y) + asteroidsmall_vert[i].x)
			)
			flag = !flag;
	}
	return flag;
}