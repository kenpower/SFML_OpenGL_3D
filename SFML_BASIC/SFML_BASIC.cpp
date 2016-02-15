//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
  
 
 
  
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
void Draw_Cuboid(float,float,float);


int main() 
{ 
    // Create the main window 
    sf::RenderWindow App(sf::VideoMode(600, 600, 32), "SFML OpenGL"); 
    int width=600,height=600;
    // Create a clock for measuring time elapsed     
    sf::Clock Clock; 
      
    //prepare OpenGL surface for HSR 
    glClearDepth(1.f); 
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
   
    //// Setup a perspective projection & Camera position 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
     
    //set up a 3D Perspective View volume
    gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar 
 
    //set up a  orthographic projection same size as window
    //this means the vertex coordinates are in pixel space
    //glOrtho(0,800,0,600,0,100); // use pixel coordinates
    
	
	
   
	//glMatrixMode(GL_PROJECTION); // reset projection matrix
	//glLoadIdentity();

	//calculate new prespective and aspect ratio
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	GLfloat materialAmbDiff[] = {0.9f, 0.1f, 0.0f, 1.0f}; // create an array of RGBA values
 
 
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbDiff); 
    // set the diffuse & ambient reflection colour for the front of faces

	GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // create an array of RGBA values (White)
	GLfloat materialShininess[] = {128.0f}; // select value between 0-128, 128=shiniest
 
 
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); // set the colour of specular reflection
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess); // set shininess of the material


	glMatrixMode(GL_MODELVIEW); // reset modelview matrix
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	GLfloat light_color[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[]={0.0, 15.0, 0.0, 1.0};
 
 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color); // set color of diffuse component
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color); // set color of specular component
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT_MODEL_LOCAL_VIEWER);
	

 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);   // set position


	sf::Shader shader;
	if(!shader.loadFromFile("vertex.glsl","pixel.glsl")){
		char c;
		std::cin >>c;
        exit(1);
    }


    // Start game loop 
    while (App.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (App.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                App.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                App.close(); 
             
    
        } 
           
        //Prepare for drawing 
        // Clear color and depth buffer 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
		sf::Shader::bind(&shader);
        // Apply some transformations 
        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 
         
		//glTranslatef(0,0,-20); //push back 10 units from camera
		gluLookAt(	0,0,20,// camera position
					0,0,0, //look at this point
					0,1,1); //camera up

		static float ang=0.0;
		glRotatef(ang,1,0,0); //spin about x-axis
		//glRotatef(ang*2,0,1,0);//spin about y-axis
		

		ang+=0.01f;

		glNormal3d(0,1,0);
		double grid=0.5;
		glBegin(GL_TRIANGLES);
		for(double i=-10;i<10;i+=grid){
			for(double j=-10;j<10;j+=grid){
				glVertex3d(i,		0,	j);
				glVertex3d(i+grid,	0,	j);
				glVertex3d(i,		0,	j+grid);

				glVertex3d(i+grid,	0,	j);
				glVertex3d(i,		0,	j+grid);
				glVertex3d(i+grid,	0,	j+grid);

			
			}
		}


		glEnd();
		   
        // Finally, display rendered frame on screen 
        App.display(); 
    } 
   
    return EXIT_SUCCESS; 
}
		