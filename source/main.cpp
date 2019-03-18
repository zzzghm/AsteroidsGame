#include "common.h"

using namespace Angel;

Ship ship;
//Asteroid asteroid;
std::vector < Asteroid * > asteroid; 
std::vector < Bullet * > bullets;
std::vector < AsteroidSmall * > asteroidsmall;


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}



static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	  ship.rotateLeft();
  if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
      ship.rotateRight();
  if (key == GLFW_KEY_SPACE){
    if(action == GLFW_PRESS){
      ship.start_thruster();
    }
    if(action == GLFW_RELEASE){
      ship.stop_thruster();
    }
  } 
    //!!!!!!!!Fire bullet
  if (key == GLFW_KEY_Z &&action == GLFW_PRESS) {
	  Bullet * b = ship.pew_pew();
	  b->gl_init();
	  bullets.push_back(b);
	  }
	 
  

  
}

void init(){
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  ship.gl_init();
  for (unsigned int i = 0; i < 20; i++) {
	  Asteroid * a = new Asteroid;
	  a->gl_init();
	  asteroid.push_back(a);
  }
 
  for (unsigned int i = 0; i < bullets.size(); i++) {
	  bullets[i]->gl_init();}
}

//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > 0.033){
    glfwSetTime(0.0);
	ship.update_state();
	for (unsigned int i = 0; i < asteroid.size(); i++) {
		asteroid[i]->update_state();
	}
	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets[i]->update_state();
	}

	//collision test, if a bullet hits an asteroid
	// hit the big asteroid, remove it and replace with 3 smaller version
	for (unsigned int i = 0; i < bullets.size(); i++) {
		for (unsigned int j = 0; j < asteroid.size(); j++) {
			bool flag = asteroid[j]->PointInPolygon(bullets[i]);
			if (flag==true) {
				//return three small asteroids
				for (unsigned int k = 0; k < 3; k++) {
					AsteroidSmall * asmall = asteroid[j]->new_Asteroid();
					asmall->gl_init();
					asteroidsmall.push_back(asmall);
				}
				//remove the big asteroid
				delete asteroid[j];
				
				//remove the bullte
				delete bullets[i];
			}
		}
	}	
	for (unsigned int i = 0; i < asteroidsmall.size(); i++) {
		asteroidsmall[i]->update_state();
	}

	// hit the small asteroid, remove it
	for (unsigned int i = 0; i < bullets.size(); i++) {
		for (unsigned int j = 0; j < asteroidsmall.size(); j++) {
			bool flag = asteroidsmall[j]->PointInPolygon(bullets[i]);
			if (flag == true) {
				//remove small asteroid
				delete asteroidsmall[j];	
				//remove the bullet
				delete bullets[i];
			}	    
		}
		
	}

	// collision test, if the ship hits a big asteroid, game over
	for (unsigned int i = 0; i < asteroid.size(); i++) {
		bool flag = asteroid[i]->ShipHitAsteroid(ship);
		if (flag == true) {
			//display a red 'X' in the center
			ship.hitendgame();
			//freeze ship
			ship.state.velocity = 0;
			//freeze asteroid
			for (unsigned int i = 0; i < asteroid.size(); i++) {
				asteroid[i]->Astate.velocity = 0;
			}
			//freeze small asteroid
			for (unsigned int i = 0; i < asteroidsmall.size(); i++) {
				asteroidsmall[i]->ASstate.velocity = 0;
			}
			//freeze bullets
			for (unsigned int i = 0; i < bullets.size(); i++) {
				bullets[i]->Bstate.vel = 0;
			}
		}
	}
	// collision test, if the ship hits a small asteroid, game over
	for (unsigned int i = 0; i < asteroidsmall.size(); i++) {
		bool flag = asteroidsmall[i]->ShipHitAsteroid(ship);
		if (flag == true) {
			//display a red 'X' in the center
			ship.hitendgame();
			//freeze ship
			ship.state.velocity = 0;
			//freeze asteroid
			for (unsigned int i = 0; i < asteroid.size(); i++) {
				asteroid[i]->Astate.velocity = 0;
			}
			//freeze small asteroid
			for (unsigned int i = 0; i < asteroidsmall.size(); i++) {
				asteroidsmall[i]->ASstate.velocity = 0;
			}
			//freeze bullets
			for (unsigned int i = 0; i < bullets.size(); i++) {
				bullets[i]->Bstate.vel = 0;
			}
		}
	}

  }
}

int main(void)
{
  GLFWwindow* window;
  
  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, 10);
  
  
  window = glfwCreateWindow(1024, 768, "Asteroids!", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  init();


  while (!glfwWindowShouldClose(window)){
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //Pick a coordinate system that makes the most sense to you
    //(left, right, top, bottom)
    mat4 proj = Ortho2D(-10.0, 10.0, 10.0, -10.0);
	
    animate();



    glClear(GL_COLOR_BUFFER_BIT);
	for (unsigned int i = 0; i < asteroid.size(); i++) {
		asteroid[i]->draw(proj);
	}
	ship.draw(proj);
	for (unsigned int i = 0; i < bullets.size(); i++) {
		bullets[i]->draw(proj);
	}
	for (unsigned int i = 0; i < asteroidsmall.size(); i++) {
		asteroidsmall[i]->draw(proj);
	}
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
