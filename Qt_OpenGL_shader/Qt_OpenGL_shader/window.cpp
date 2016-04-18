#include "window.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include "vertex.h"

static Vertex facesDataLINE[maxVert];
static Vertex facesDataFILL[maxVert];

Vertex pointsData[100];
Vertex linesData[100];

extern list<Vertex> pointsDataList;
extern list<Vertex> linesDataList;

void Window::initializeGL()
{
  scaleValue = 1;
  shadeMode = 3; // show both line and face
  updateGeometry();

  // Initialize OpenGL Backend
  initializeOpenGLFunctions();
  connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

  // Set global information
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // Create Shader
  m_program = new QOpenGLShaderProgram();
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
  m_program->link();
  m_program->bind();

  // Faces LINE Binding
  {
    // Create Buffer
    facesVBO1.create();
    facesVBO1.bind();
    facesVBO1.setUsagePattern(QOpenGLBuffer::StaticDraw);
    facesVBO1.allocate(facesDataLINE, sizeof(facesDataLINE));

    // Create Vertex Array Object
    facesVAO1.create();
    facesVAO1.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    // Release (unbind) all
    facesVAO1.release();
    facesVBO1.release();
  }

  // Faces FILL Binding
  {
    // Create Buffer
    facesVBO2.create();
    facesVBO2.bind();
    facesVBO2.setUsagePattern(QOpenGLBuffer::StaticDraw);
    facesVBO2.allocate(facesDataFILL, sizeof(facesDataFILL));

    // Create Vertex Array Object
    facesVAO2.create();
    facesVAO2.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    // Release (unbind) all
    facesVAO2.release();
    facesVBO2.release();
  }

  // Points Binding
  {
    // Create Buffer
    pointsVBO.create();
    pointsVBO.bind();
    pointsVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    pointsVBO.allocate(pointsData, sizeof(pointsData));

    // Create Vertex Array Object
    pointsVAO.create();
    pointsVAO.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    // Release (unbind) all
    pointsVAO.release();
    pointsVBO.release();
  }

  // Lines Binding
  {
    // Create Buffer (Do not release until VAO is created)
    linesVBO.create();
    linesVBO.bind();
    linesVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    linesVBO.allocate(linesData, sizeof(linesData));

    // Create Vertex Array Object
    linesVAO.create();
    linesVAO.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    // Release (unbind) all
    linesVAO.release();
    linesVBO.release();
  }

    m_program->release();

}

// update geomerty information here
void Window::updateGeometry()
{
    int count = 0;
    list<Triangle>::iterator tri;
    list<Vertex>::iterator vert;

    for (tri=face.begin(); tri!=face.end(); tri++){
        vec4 p1, p2, p3;
        tri->getVertice(p1,p2,p3);

        vec4 temp = cross(p1 - p2,p2 - p3);

        while(length(temp) < 0.01)
            temp = temp * 10;

        objNormal[count] = temp;
        objNormal[count+1] = temp;
        objNormal[count+2] = temp;

        facesDataLINE[count] =   Vertex( QVector3D( p1.x, p1.y, p1.z), QVector3D(0.0f, 1.0f, 1.0f) );
        facesDataLINE[count+1] = Vertex( QVector3D( p2.x, p2.y, p2.z), QVector3D(0.0f, 1.0f, 1.0f) );
        facesDataLINE[count+2] = Vertex( QVector3D( p3.x, p3.y, p3.z), QVector3D(0.0f, 1.0f, 1.0f) );

        facesDataFILL[count] =   Vertex( QVector3D( p1.x, p1.y, p1.z), QVector3D(0.0f, 0.0f, 1.0f) );
        facesDataFILL[count+1] = Vertex( QVector3D( p2.x, p2.y, p2.z), QVector3D(0.0f, 0.0f, 1.0f) );
        facesDataFILL[count+2] = Vertex( QVector3D( p3.x, p3.y, p3.z), QVector3D(0.0f, 0.0f, 1.0f) );

      count = count + 3;
    }

    count = 0;

    for(vert = linesDataList.begin(); vert != linesDataList.end(); vert++){
        linesData[count++] = *vert;
    }

    count = 0;

    for(vert = pointsDataList.begin(); vert != pointsDataList.end(); vert++){
        pointsData[count++] = *vert;
    }
}

void Window::update()
{
  // Schedule a redraw
  QOpenGLWindow::update();
}

void Window::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);
  m_modelView.setToIdentity();
  m_modelView.translate(xTrans, yTrans, zTrans);
  m_modelView.rotate(-180.0f, 1, 0, 0);
  m_modelView.rotate(180.0f - (xRot / 16.0f), 1, 0, 0);
  m_modelView.rotate(yRot / 16.0f, 0, 1, 0);
  m_modelView.rotate(zRot / 16.0f, 0, 0, 1);
  m_modelView.scale(scaleValue);

  // Render using our shader
  m_program->bind();
  {
    m_program->setUniformValue("mvpMatrix",  m_modelView);

    if(shadeMode == 1 || shadeMode == 3){
        facesVAO1.bind();
        facesVBO1.bind();
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(facesDataFILL) / sizeof(facesDataFILL[0]));
        facesVBO1.release();
        facesVAO1.release();
    }

    if(shadeMode == 2 || shadeMode ==3){
        facesVAO2.bind();
        facesVBO2.bind();
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(facesDataLINE) / sizeof(facesDataLINE[0]));
        facesVBO2.release();
        facesVAO2.release();
    }

    pointsVAO.bind();
    glPointSize(15);
    glDrawArrays(GL_POINTS, 0, sizeof(pointsData) / sizeof(pointsData[0]));
    pointsVAO.release();

    linesVAO.bind();
    glDrawArrays(GL_LINE_STRIP, 0, sizeof(linesData) / sizeof(linesData[0]));
    linesVAO.release();
  }
  m_program->release();
}

void Window::resizeGL(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 0.0f, 5.0f);
}


void Window::teardownGL()
{
  // Actually destroy our OpenGL information
  facesVAO1.destroy();
  facesVBO1.destroy();

  facesVAO2.destroy();
  facesVBO2.destroy();

  linesVAO.destroy();
  linesVBO.destroy();

  pointsVAO.destroy();
  pointsVBO.destroy();
  delete m_program;
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void Window::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}


void Window::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_I: shadeMode = 1; break;
        case Qt::Key_O: shadeMode = 2;break;
        case Qt::Key_P: shadeMode = 3;break;
    }
    QWindow::keyPressEvent(event);
}

void Window::wheelEvent(QWheelEvent *event)
{
    int orient = event->delta();

        if(orient > 0)
            scaleValue += 0.1;
        else
            scaleValue -= 0.1;

        if(scaleValue < 0.1)
            scaleValue = 0.1;
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::RightButton) {
        xRotationChanged(xRot - 8 * dy);
        yRotationChanged(yRot + 8 * dx);
    }

    if(event->buttons() & Qt::LeftButton){
        xTrans += dx*0.0025;
        yTrans -= dy*0.0025;
    }

    lastPos = event->pos();
    paintGL();
}

void Window::xRotationChanged(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
    }
}

void Window::yRotationChanged(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
    }
}

void Window::zRotationChanged(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
    }
}

