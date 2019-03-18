//
//  
//  Asteroids.cpp
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"


//Asteroid constructor
Asteroid::Asteroid() {
	//Set up initial state here
	Astate.velocity= (vec2(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX)) * 3 - vec2(1.5, 1.5);
	//Astate.velocity = vec2(-1,1);
	
	
};

//Called everytime an animation tick happens
void Asteroid::update_state() {
	float dt = 0.033;
	//vec2 di = normalize(vec2(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX)-vec2(0.5,0.5));
	vec2 intvel = Astate.velocity;
		for (unsigned int i = 0; i <  7; i++) {
			//rotate slowly over time
			vec2 center = asteroid_vert[0];
			asteroid_vert[i] = asteroid_vert[i] - center;
			asteroid_vert[i] = Astate.R * asteroid_vert[i];
			asteroid_vert[i] = asteroid_vert[i] + center;
			//constant velocity at a random direction	
				//asteroid_vert[i] = asteroid_vert[i] + di * Astate.velocity*dt;
			asteroid_vert[i] = asteroid_vert[i] + intvel*dt;
		}
	

    
	
		// Wrap the asteroid position when at the boundary
		//left
		for (unsigned int i = 0; i < 7; i++) {
			if (asteroid_vert[i].x < -10) {
				asteroid_vert[0].x = -9.75;
				asteroid_vert[1] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[2] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y + 0.25);
				asteroid_vert[3] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[4] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y - 0.125);
				asteroid_vert[5] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y - 0.25);
				asteroid_vert[6] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y - 0.125);
				Astate.velocity.x = -Astate.velocity.x;
			}
		}
		//right
		for (unsigned int i = 0; i < 7; i++) {
			if (asteroid_vert[i].x > 10) {
				asteroid_vert[0].x = 9.75;
				asteroid_vert[1] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[2] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y + 0.25);
				asteroid_vert[3] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[4] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y - 0.125);
				asteroid_vert[5] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y - 0.25);
				asteroid_vert[6] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y - 0.125);
				Astate.velocity.x = -Astate.velocity.x;
			}
		}
		//bottom
		for (unsigned int i = 0; i < 7; i++) {
			if (asteroid_vert[i].y < -10) {
				asteroid_vert[0].y = -9.75;
				asteroid_vert[1] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[2] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y + 0.25);
				asteroid_vert[3] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[4] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y - 0.125);
				asteroid_vert[5] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y - 0.25);
				asteroid_vert[6] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y - 0.125);
				Astate.velocity.y = -Astate.velocity.y;
			}
		}
		//top
		for (unsigned int i = 0; i < 7; i++) {
			if (asteroid_vert[i].y > 10) {
				asteroid_vert[0].y = 9.75;
				asteroid_vert[1] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[2] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y + 0.25);
				asteroid_vert[3] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y + 0.125);
				asteroid_vert[4] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y - 0.125);
				asteroid_vert[5] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y - 0.25);
				asteroid_vert[6] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y - 0.125);
				Astate.velocity.y = -Astate.velocity.y;
			}
		}
	
	// Create a vertex array object                                                                                                                
	glGenVertexArrays(1, &ASvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(ASvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &ASvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, ASvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroid_vert) + sizeof(asteroid_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(asteroid_vert), asteroid_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(asteroid_vert), sizeof(asteroid_color), asteroid_color);

	glEnableVertexAttribArray(ASvars.vpos_location);
	glEnableVertexAttribArray(ASvars.vcolor_location);

	glVertexAttribPointer(ASvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(ASvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(asteroid_vert)));

	glBindVertexArray(0);

	Astate.cur_location = asteroid_vert[0];
}

//Initialize the gl state and variables
void Asteroid::gl_init() {
	//Asteroid
	//!!!!!!!!Populate asteroid_vert and asteroid_color
	asteroid_vert[0] = (vec2(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX)) * 16 - vec2(8, 8);
	asteroid_vert[1] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y + 0.125);
	asteroid_vert[2] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y + 0.25);
	asteroid_vert[3] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y + 0.125);
	asteroid_vert[4] = vec2(asteroid_vert[0].x - 0.25, asteroid_vert[0].y - 0.125);
	asteroid_vert[5] = vec2(asteroid_vert[0].x + 0.125, asteroid_vert[0].y - 0.25);
	asteroid_vert[6] = vec2(asteroid_vert[0].x + 0.25, asteroid_vert[0].y - 0.125);


	for (int i = 0; i < 7; i++) {
		asteroid_color[i] = vec3(1.0, 1.0, 1.0);
	}
	
	std::string vshader = shader_path + "vshader_Asteroid.glsl";
	std::string fshader = shader_path + "fshader_Asteroid.glsl";

	GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
	GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

	ASvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ASvars.vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
	glCompileShader(ASvars.vertex_shader);
	check_shader_compilation(vshader, ASvars.vertex_shader);

	ASvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ASvars.fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
	glCompileShader(ASvars.fragment_shader);
	check_shader_compilation(fshader, ASvars.fragment_shader);

	ASvars.program = glCreateProgram();
	glAttachShader(ASvars.program, ASvars.vertex_shader);
	glAttachShader(ASvars.program, ASvars.fragment_shader);

	glLinkProgram(ASvars.program);
	check_program_link(ASvars.program);

	glBindFragDataLocation(ASvars.program, 0, "fragColor");

	ASvars.vpos_location = glGetAttribLocation(ASvars.program, "vPos");
	ASvars.vcolor_location = glGetAttribLocation(ASvars.program, "vColor");
	ASvars.M_location = glGetUniformLocation(ASvars.program, "M");

	//draw asteroid
	// Create a vertex array object
	glGenVertexArrays(1, &ASvars.vao);
	//Set GL state to use vertex array object
	glBindVertexArray(ASvars.vao);

	//Generate buffer to hold our vertex data
	glGenBuffers(1, &ASvars.buffer);
	//Set GL state to use this buffer
	glBindBuffer(GL_ARRAY_BUFFER, ASvars.buffer);

	//Create GPU buffer to hold vertices and color
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroid_vert) + sizeof(asteroid_color), NULL, GL_STATIC_DRAW);
	//First part of array holds vertices
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(asteroid_vert), asteroid_vert);
	//Second part of array hold colors (offset by sizeof(triangle))
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(asteroid_vert), sizeof(asteroid_color), asteroid_color);

	glEnableVertexAttribArray(ASvars.vpos_location);
	glEnableVertexAttribArray(ASvars.vcolor_location);

	glVertexAttribPointer(ASvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(ASvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(asteroid_vert)));

	glBindVertexArray(0);

}

//Draw a asteroid
void Asteroid::draw(mat4 proj) {

	glUseProgram(ASvars.program);
	glBindVertexArray(ASvars.vao);

	//If you have a modelview matrix, pass it with proj
	glUniformMatrix4fv(ASvars.M_location, 1, GL_TRUE, proj);

	//Draw something
	glBindVertexArray(ASvars.vao);

	//glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
	glDrawArrays(GL_LINE_LOOP, 0, 7);

	glBindVertexArray(0);
	glUseProgram(0);

}
AsteroidSmall* Asteroid::new_Asteroid() {
	vec2 pos = Astate.cur_location;

	return new AsteroidSmall(pos);
}

//bullet hits asteroid
bool Asteroid::PointInPolygon(Bullet *b) {
	int i, j, nvert = 6;
	bool flag = false;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((asteroid_vert[i].y >= b->Bstate.pos.y) != (asteroid_vert[j].y >= b->Bstate.pos.y)) &&
			(b->Bstate.pos.x <= (asteroid_vert[j].x - asteroid_vert[i].x) * (b->Bstate.pos.y - asteroid_vert[i].y) / (asteroid_vert[j].y - asteroid_vert[i].y) + asteroid_vert[i].x)
			)
			flag = !flag;
	}
	return flag;
}

//ship hits asteroid
bool Asteroid::ShipHitAsteroid(Ship s) {
	int i, j, nvert = 6;
	bool flag = false;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		//test the top vertex/point in ship, if the point is in the asteroid polygon
		if (((asteroid_vert[i].y >= s.state.cur_location.y) != (asteroid_vert[j].y >= s.state.cur_location.y)) &&
			(s.state.cur_location.x <= (asteroid_vert[j].x - asteroid_vert[i].x) * (s.state.cur_location.y - asteroid_vert[i].y) / (asteroid_vert[j].y - asteroid_vert[i].y) + asteroid_vert[i].x)) {
			flag = !flag;
		}
		
				
	}
	return flag;
}