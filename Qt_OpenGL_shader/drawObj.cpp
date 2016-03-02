#include "drawObj.h"
#include "include/Angel.h"
#include "tryhead.h"
#define maxVert 150000

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[NumVertices];
color4 colors[NumVertices];

vec4 gridpoints[maxVert];
vec4 gridcolours[maxVert];

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5, -0.5, -0.5, 1.0 ),
    point4( -0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5, -0.5, -0.5, 1.0 )
};

// RGBA olors
color4 vertex_colors[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    color4( 1.0, 1.0, 1.0, 1.0 ),  // white
    color4( 0.0, 1.0, 1.0, 1.0 )   // cyan
};

int Index = 0;

void quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

void colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

PolygonWindow::PolygonWindow(QWindow *parent) :
    OpenGLWindow(parent), m_program(NULL), m_rtri(0.0f), m_rquad(0.0f)
{
}

PolygonWindow::~PolygonWindow()
{
    glDeleteBuffers(4, &m_vboIds[0]);
}

void PolygonWindow::initialize()
{
    initGeometry();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepthf(1.0f);
    glDepthFunc(GL_LEQUAL);

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/vertshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/fragshader.glsl");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    glEnable(GL_CULL_FACE);
}

void PolygonWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();

    m_modelView.setToIdentity();
    m_modelView.translate(0.0f, -0.5f, -3.0f);
    m_modelView.rotate(m_rtri, x_flag, y_flag, z_flag);
    m_program->setUniformValue("mvpMatrix", m_projection * m_modelView);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    m_program->enableAttributeArray(m_posAttr);
    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    m_program->enableAttributeArray(m_colAttr);
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, 0, 4);
    glDrawArrays(GL_TRIANGLES, 0, maxVert);

    m_program->release();
}

void PolygonWindow::keyPressEvent(QKeyEvent *event)
{
    int direc = 1;
    x_flag = y_flag = z_flag = 0.0f;
    switch(event->key())
    {
        case Qt::Key_Q:x_flag =  1.0f;direc = 1;break;
        case Qt::Key_W:x_flag =  1.0f;direc = -1;break;

        case Qt::Key_A:y_flag =  1.0f;direc = 1;break;
        case Qt::Key_S:y_flag =  1.0f;direc = -1;break;

        case Qt::Key_Z:z_flag =  1.0f;direc = 1;break;
        case Qt::Key_X:z_flag =  1.0f;direc = -1;break;
    }
    m_rtri += 10.0f * direc;
    QWindow::keyPressEvent(event);
}

void PolygonWindow::initGeometry()
{
    int numOfVert;
    int numOfFace;
    float vert[15000][3];
    int face[30000][3];
    getTriangles(vert,face,numOfVert,numOfFace);
    int i = 14602;

    int count = 0;
    for(int i = 0;i < numOfFace;i++){
          int ind1 = face[i][0]-1;
          int ind2 = face[i][1]-1;
          int ind3 = face[i][2]-1;

          vec4 p1 = vec4(vert[ind1][0],vert[ind1][1],vert[ind1][2],1);
          vec4 p2 = vec4(vert[ind2][0],vert[ind2][1],vert[ind2][2],1);
          vec4 p3 = vec4(vert[ind3][0],vert[ind3][1],vert[ind3][2],1);

          gridpoints[count] = p1;
          gridpoints[count+1] = p2;
          gridpoints[count+2] = p3;
          count = count + 3;
      }
        // Make all grid lines white
        for (int i = 0; i < maxVert+1; i++)
            gridcolours[i] = vec4(0.0, 1.0, 1.0, 1.0);

    glGenBuffers(4, &m_vboIds[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gridpoints), gridpoints, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gridcolours), gridcolours, GL_STATIC_DRAW);
}
