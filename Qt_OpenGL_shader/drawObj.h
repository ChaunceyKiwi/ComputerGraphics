#ifndef POLYGONWINDOW_H
#define POLYGONWINDOW_H

#include <QOpenGLShaderProgram>
#include "openglwindow.h"

class PolygonWindow : public OpenGLWindow
{
    Q_OBJECT
public:
    explicit PolygonWindow(QWindow *parent = 0);
    ~PolygonWindow();
protected:
    void initialize();
    void render();
    void keyPressEvent(QKeyEvent * event);
private:
    void initGeometry();
    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;

    float xTrans;
    float yTrans;
    float zTrans;
private:
    QOpenGLShaderProgram *m_program;
    GLuint m_colAttr;
    GLuint m_posAttr;

    GLuint m_vboIds[4];
    GLfloat	m_rtri;
    GLfloat	x_flag,y_flag,z_flag;
    GLfloat	m_rquad;

    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // POLYGONWINDOW_H
