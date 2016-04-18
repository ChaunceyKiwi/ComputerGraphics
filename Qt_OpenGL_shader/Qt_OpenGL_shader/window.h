#ifndef WINDOW_H
#define WINDOW_H

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

#include "triangle.h"
#define maxVert 100000

class QOpenGLShaderProgram;
extern list<Triangle> face;

class Window : public QOpenGLWindow, protected QOpenGLFunctions
{
  Q_OBJECT

// OpenGL Events
public:
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
  void updateGeometry();

protected slots:
  void teardownGL();
  void update();

private:
  // OpenGL State Information
  QOpenGLBuffer facesVBO1,facesVBO2,pointsVBO,linesVBO;
  QOpenGLVertexArrayObject facesVAO1,facesVAO2,pointsVAO,linesVAO;
  QOpenGLShaderProgram *m_program;

  // used for rotation
  QPoint lastPos;
  int currentFaceNum;
  int xRot, yRot, zRot;

  // draw line or face or both
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

  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

};

#endif // WINDOW_H
