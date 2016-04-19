#ifndef ObjectWindow_H
#define ObjectWindow_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QWindow>
#include <QCoreApplication>
#include <QEvent>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "triangle.h"
#include "openglwindow.h"
#define maxVert 100000

class QOpenGLShaderProgram;
extern list<Triangle> face;

class ObjectWindow : public OpenGLWindow
{
  Q_OBJECT

public:
    explicit ObjectWindow(QWindow *parent = 0);
    ~ObjectWindow();

protected:
    void initialize();
    void render();
    void keyPressEvent(QKeyEvent * event);

private:
  // OpenGL State Information
  // face1 for line, face2 for fill
  QOpenGLBuffer facesVBO1,facesVBO2,pointsVBO,linesVBO;
  QOpenGLVertexArrayObject facesVAO1,facesVAO2,pointsVAO,linesVAO;
  QOpenGLShaderProgram *m_program;

  // used for rotation
  QPoint lastPos;
  int currentFaceNum;
  int xRot, yRot, zRot;

  // draw line or face or both
  // 1: lines, 2: faces, 3: lines and face
  int shadeMode;

  // used for translation
  float xTrans, yTrans, zTrans;

  vec4 objPoints[maxVert];
  vec4 objColors[maxVert];
  vec4 objNormal[maxVert];

  //used for scale
  float scaleValue;

  QMatrix4x4 m_modelView, m_projection;

  int MVPmatrix;

  void updateGeometry();
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

};

#endif // WINDOW_H
