#include "polygonwindow.h"

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
}

void PolygonWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();

    m_modelView.setToIdentity();
    m_modelView.translate(-1.5f, 0.5f, -6.0f);
    m_modelView.rotate(m_rtri, x_flag, y_flag, z_flag);
    m_program->setUniformValue("mvpMatrix", m_projection * m_modelView);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    m_program->enableAttributeArray(m_posAttr);
    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    m_program->enableAttributeArray(m_colAttr);
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 12);

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
    glGenBuffers(4, &m_vboIds[0]);
    GLfloat triangleVertices[] = {
       -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

         0.0f, 1.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 1.0f,

         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    GLfloat triangleColors[] = {
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,

        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,

        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,

        1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColors), triangleColors, GL_STATIC_DRAW);

    GLfloat quadVertices[] = {
        1.0f, 1.0f, 0.0f,
       -1.0f, 1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
       -1.0f,-1.0f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    GLfloat quadColors[] = {
        0.5f,0.5f,1.0f,
        0.5f,0.5f,1.0f,
        0.5f,0.5f,1.0f,
        0.5f,0.5f,1.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadColors), quadColors, GL_STATIC_DRAW);
}
