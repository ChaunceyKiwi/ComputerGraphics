#include "objectWindow.h"

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
    scaleValue = 1;
    shadeMode = 3;

    updateGeometry();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/vertshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/fragshader.glsl");
    m_program->link();
    m_program->bind();

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_norAttr = m_program->attributeLocation("norAttr");

    glEnable(GL_CULL_FACE);
}

void ObjectWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();

    m_modelView.setToIdentity();
    m_modelView.translate(0.1f+xTrans, -0.5f+yTrans, -1.5f+zTrans);

    m_modelView.rotate(-180.0f, 1, 0, 0);
    m_modelView.rotate(180.0f - (xRot / 16.0f), 1, 0, 0);
    m_modelView.rotate(yRot / 16.0f, 0, 1, 0);
    m_modelView.rotate(zRot / 16.0f, 0, 0, 1);

    m_modelView.scale(scaleValue);

    m_program->setUniformValue("mvpMatrix", m_projection * m_modelView);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    m_program->enableAttributeArray(m_posAttr);
    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    m_program->enableAttributeArray(m_colAttr);
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[2]);
    m_program->enableAttributeArray(m_norAttr);
    m_program->setAttributeBuffer(m_norAttr, GL_FLOAT, 0, 4);

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    if(shadeMode == 1 || shadeMode == 3){
        for (int i = 0; i < maxVert+1; i++)
            objColors[i] = vec4(0.0, 1.0, 1.0, 1.0);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(objColors), objColors, GL_STATIC_DRAW);

        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glPointSize(2);
        glDrawArrays(GL_TRIANGLES, 0, maxVert);
    }

    if(shadeMode == 2 || shadeMode == 3){
        for (int i = 0; i < maxVert+1; i++)
            objColors[i] = vec4(0.0, 0.0, 1.0, 1.0);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(objColors), objColors, GL_STATIC_DRAW);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glPointSize(2);
        glDrawArrays(GL_TRIANGLES, 0, maxVert);
    }

    m_program->enableAttributeArray(m_colAttr);
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, 0, 4);
    m_program->release();
}

void ObjectWindow::keyPressEvent(QKeyEvent *event)
{
    int direc = 1;
    switch(event->key())
    {
        case Qt::Key_I: shadeMode = 1;break;
        case Qt::Key_O: shadeMode = 2;break;
        case Qt::Key_P: shadeMode = 3;break;
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

void ObjectWindow::updateGeometry()
{
    int count = 0;
    list<Triangle>::iterator tri;

    for (tri=face.begin(); tri!=face.end(); tri++){

      vec4 p1, p2, p3;
      tri->getVertice(p1,p2,p3);
      vec4 temp = cross(p1 - p2,p2 - p3);

      while(length(temp) < 0.01)
          temp = temp * 10;

      objPoints[count] = p1;
      objPoints[count+1] = p2;
      objPoints[count+2] = p3;

      objNormal[count] = temp;
      objNormal[count+1] = temp;
      objNormal[count+2] = temp;

      count = count + 3;
    }

    // Make all grid lines white
    for (int i = 0; i < maxVert+1; i++)
        objColors[i] = vec4(0.0, 0.0, 1.0, 1.0);

    glGenBuffers(4, &m_vboIds[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objPoints), objPoints, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(objNormal), objNormal, GL_STATIC_DRAW);
}

void ObjectWindow::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ObjectWindow::wheelEvent(QWheelEvent *event)
{
    int orient = event->delta();

    if(orient > 0)
        scaleValue += 0.1;
    else
        scaleValue -= 0.1;
    render();
}

void ObjectWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::RightButton) {
        xRotationChanged(xRot - 8 * dy);
        yRotationChanged(yRot + 8 * dx);
    }

    if(event->buttons() & Qt::LeftButton){
        xTrans += dx*0.001;
        yTrans -= dy*0.001;
        render();
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
