#include "include/Angel.h"
#include "include/imageloader.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
typedef Angel::vec2  texture2;


const int NumVertices = 6;

point4 points[NumVertices];
color4 colors[NumVertices];
texture2 texture[NumVertices];

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 )
};

GLuint  model_view;  // model-view matrix uniform shader variable location

int Index = 0;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

GLuint textureId; //The id of the texture buffer
GLuint texId;

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    Image* grassimage = loadBMP("/Users/KiwiDc/Desktop/bmp/bricks.bmp");
    
    textureId = loadTexture(grassimage);
    
    delete grassimage;
}


// OpenGL initialization
void init()
{
    points[0] = vertices[0];
    texture[0] = vec2(0.0, 0.0);
    
    points[1] = vertices[1];
    texture[1] = vec2(0.0, 1.0);
    
    points[2] = vertices[2];
    texture[2] = vec2(1.0, 1.0);
    
    points[3] = vertices[0];
    texture[3] = vec2(0.0, 0.0);
    
    points[4] = vertices[3];
    texture[4] = vec2(1.0, 0.0);
    
    points[5] = vertices[2];
    texture[5] = vec2(1.0, 1.0);
    
    

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(texture),NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(texture), texture );
    
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "/Users/KiwiDc/WorkSpace/XcodeSpace/textureMapping/textureMapping/vshader.glsl", "/Users/KiwiDc/WorkSpace/XcodeSpace/textureMapping/textureMapping/fshader.glsl" );
    glUseProgram( program );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
    
    GLuint texCoordID = glGetAttribLocation( program, "s_vTexCoord");
    glEnableVertexAttribArray( texCoordID );
    glVertexAttribPointer( texCoordID, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));
    
    model_view = glGetUniformLocation( program, "model_view" );
    texId = glGetUniformLocation( program, "texture_s" );
    glUniform1i(texId, 0);
    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    mat4  mv;
    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );
    
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    
    glutPostRedisplay();
    glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
        case 033: // Escape Key
        case 'q': case 'Q':
            exit( EXIT_SUCCESS );
            break;
    }
    
    glutPostRedisplay();
}


void reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
}


int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Color Cube" );
    
    init();
    initRendering();
    
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    
    glutMainLoop();
    return 0;
}
