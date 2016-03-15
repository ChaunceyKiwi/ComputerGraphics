#include "ObjectWindow.h"
#include "include/Angel.h"
#define maxVert 100000

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

vec4 objPoints[maxVert];
vec4 objColors[maxVert];

extern int numOfVert;
extern int numOfFace;
extern float vert[15000][3];
extern int face[30000][3];

ObjectWindow::ObjectWindow(QWindow *parent) :
    OpenGLWindow(parent), m_program(NULL), m_rtri(0.0f)
{
}

ObjectWindow::~ObjectWindow()
{
    glDeleteBuffers(4, &m_vboIds[0]);
}

void ObjectWindow::initialize()
{
    xRot = yRot = zRot = 0;
    xTrans = yTrans = zTrans = 0;
    currentFaceNum = 0;
    initGeometry();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

void ObjectWindow::render()
{
    updateGeometry();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();

    m_modelView.setToIdentity();
    m_modelView.translate(0.1f+xTrans, -0.5f+yTrans, -1.5f+zTrans);
    m_modelView.rotate(-180.0f, 1, 0, 0);
    m_modelView.rotate(180.0f - (xRot / 16.0f), 1, 0, 0);
    m_modelView.rotate(yRot / 16.0f, 0, 1, 0);
    m_modelView.rotate(zRot / 16.0f, 0, 0, 1);

    m_program->setUniformValue("mvpMatrix", m_projection * m_modelView);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    m_program->enableAttributeArray(m_posAttr);
    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    m_program->enableAttributeArray(m_colAttr);
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, 0, 4);

    for (int i = 0; i < maxVert+1; i++)
        objColors[i] = vec4(0.0, 1.0, 1.0, 1.0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objColors), objColors, GL_STATIC_DRAW);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, maxVert);

    for (int i = 0; i < maxVert+1; i++)
        objColors[i] = vec4(0.0, 0.0, 1.0, 1.0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objColors), objColors, GL_STATIC_DRAW);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, maxVert);

    m_program->enableAttributeArray(m_colAttr);
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, 0, 4);
    m_program->release();
}

void ObjectWindow::keyPressEvent(QKeyEvent *event)
{
    int direc = 1;
    switch(event->key())
    {
        case Qt::Key_Right: xTrans += 0.1f;break;
        case Qt::Key_Left:  xTrans -= 0.1f;break;
        case Qt::Key_Up:    yTrans += 0.1f;break;
        case Qt::Key_Down:  yTrans -= 0.1f;break;
        case Qt::Key_O:     zTrans += 0.1f;break;
        case Qt::Key_P:     zTrans -= 0.1f;break;
        case Qt::Key_Space:
        if(currentFaceNum < maxVert/3){
          currentFaceNum += 1000;
          updateGeometry();
        }
        break;
    }
    m_rtri += 10.0f * direc;
    QWindow::keyPressEvent(event);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void ObjectWindow::initGeometry()
{
//    getTriangles(vert,face,numOfVert,numOfFace);
//    currentFaceNum = 1000;

    int count = 0;
    for(int i = 0;i < numOfFace;i++){
          int ind1 = face[i][0]-1;
          int ind2 = face[i][1]-1;
          int ind3 = face[i][2]-1;

          vec4 p1 = vec4(vert[ind1][0],vert[ind1][1],vert[ind1][2],1);
          vec4 p2 = vec4(vert[ind2][0],vert[ind2][1],vert[ind2][2],1);
          vec4 p3 = vec4(vert[ind3][0],vert[ind3][1],vert[ind3][2],1);

          objPoints[count] = p1;
          objPoints[count+1] = p2;
          objPoints[count+2] = p3;
          count = count + 3;
      }
    // Make all grid lines white
    for (int i = 0; i < maxVert+1; i++)
          objColors[i] = vec4(0.0, 0.0, 1.0, 1.0);

    glGenBuffers(4, &m_vboIds[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objPoints), objPoints, GL_STATIC_DRAW);
}

void ObjectWindow::updateGeometry()
{
    int count = 0;
    for(int i = 0;i < numOfFace;i++){
          int ind1 = face[i][0]-1;
          int ind2 = face[i][1]-1;
          int ind3 = face[i][2]-1;

          vec4 p1 = vec4(vert[ind1][0],vert[ind1][1],vert[ind1][2],1);
          vec4 p2 = vec4(vert[ind2][0],vert[ind2][1],vert[ind2][2],1);
          vec4 p3 = vec4(vert[ind3][0],vert[ind3][1],vert[ind3][2],1);

          objPoints[count] = p1;
          objPoints[count+1] = p2;
          objPoints[count+2] = p3;
          count = count + 3;
      }
        // Make all grid lines white
        for (int i = 0; i < maxVert+1; i++)
            objColors[i] = vec4(0.0, 0.0, 1.0, 1.0);

    glGenBuffers(4, &m_vboIds[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objPoints), objPoints, GL_STATIC_DRAW);
}

void ObjectWindow::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ObjectWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        xRotationChanged(xRot + 8 * dy);
        yRotationChanged(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        xRotationChanged(xRot + 8 * dy);
        zRotationChanged(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

void ObjectWindow::xRotationChanged(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        render();
    }
}

void ObjectWindow::yRotationChanged(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        render();
    }
}

void ObjectWindow::zRotationChanged(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        render();
    }
}
