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

	glMatrixMode(GL_MODELVIEW); // reset modelview matrix
	glLoadIdentity();


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
   
        // Apply some transformations 
        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 
         
		//glTranslatef(0,0,-10); //pish back 10 units from camera
		gluLookAt(	0,0,100,// camera position
					0,0,0, //look at this point
					0,1,1); //camera up

		static float ang=0.0;
		glRotatef(ang,1,0,0); //spin about x-axis
		glRotatef(ang*2,0,1,0);//spin about y-axis
		

		ang+=0.01f;

		Draw_Cuboid(20,35,50);

		glTranslatef(0,40,0);//move everyting after this line by 40 units along y-axis
		glRotatef(ang*5,0,0,1); //spin about z-axis

		Draw_Cuboid(10,10,10);

		   
        // Finally, display rendered frame on screen 
        App.display(); 
    } 
   
    return EXIT_SUCCESS; 
}

//Draw a cube at the origin
void Draw_Cuboid(float width,float height,float depth){
		// points of a cube
	static GLfloat points[][3]={	{1.0f,1.0f,1.0f},
									{1.0f,1.0f,0.0f},
									{0.0f,1.0f,0.0f},
									{0.0f,1.0f,1.0f},
									{1.0f,0.0f,1.0f},
									{1.0f,0.0f,0.0f},
									{0.0f,0.0f,0.0f},
									{0.0f,0.0f,1.0f}};

		//GLfloat normal[3];
		glPushMatrix();	
		glScalef(width,height,depth);
		glTranslatef(-0.5,-0.5,-0.5);
		glBegin(GL_QUADS);
		//top 
		
		//NormalVector(points[0],points[1],points[2],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,1.0,1.0);
		glVertex3fv(points[0]); glVertex3fv(points[1]); glVertex3fv(points[2]); glVertex3fv(points[3]);
		
		//front
		//NormalVector(points[0],points[3],points[7],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,0.0,1.0);
		glVertex3fv(points[0]); glVertex3fv(points[3]); glVertex3fv(points[7]); glVertex3fv(points[4]);

		//back
		//NormalVector(points[1],points[5],points[6],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,1.0,0.0);
		glVertex3fv(points[1]); glVertex3fv(points[5]); glVertex3fv(points[6]); glVertex3fv(points[2]);

		//left
		//NormalVector(points[3],points[2],points[6],normal);
		//glNormal3fv(normal);
		glColor3d(0.0,1.0,0.0);
		glVertex3fv(points[3]); glVertex3fv(points[2]); glVertex3fv(points[6]); glVertex3fv(points[7]);

		//right
		//NormalVector(points[1],points[0],points[4],normal);
		//glNormal3fv(normal);
		glColor3d(0.0,0.0,1.0);
		glVertex3fv(points[1]); glVertex3fv(points[0]); glVertex3fv(points[4]); glVertex3fv(points[5]);

		//bottom
		//NormalVector(points[4],points[7],points[6],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,0.0,0.0);
		glVertex3fv(points[4]); glVertex3fv(points[7]); glVertex3fv(points[6]); glVertex3fv(points[5]);

	glEnd();
	glPopMatrix();
}