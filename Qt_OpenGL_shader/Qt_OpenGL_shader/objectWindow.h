#ifndef ObjectWindow_H
#define ObjectWindow_H

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "openglwindow.h"
#include "triangle.h"

#define maxVert 100000
extern list<Triangle> face;

enum vaoIDs{
    faceVAO,
    lineVAO,
    pointVAO,
    maxVAOID
};

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
    void initGeometry(); // initial the mesh
    void updateGeometry(); // update the mesh

    // used for rotation
    QPoint lastPos;
    int currentFaceNum;
    int xRot;
    int yRot;
    int zRot;

    typedef vec4 color4;
    typedef vec4 point4;
    vec4 objPoints[maxVert];
    vec4 objColors[maxVert];
    vec4 objNormal[maxVert];

    // used for translation
    float xTrans;
    float yTrans;
    float zTrans;

    //used for scale
    float scaleValue;

    //used for shade mode
    float shadeMode;

private:

    // VBO
    GLuint vaoIDs[maxVAOID];
    GLuint m_colAttr;
    GLuint m_posAttr;
    GLuint m_norAttr;

    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;

    GLuint m_vboIds[4];
    GLfloat	m_rtri; //rotation matrix
    GLfloat	x_flag,y_flag,z_flag;

    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

};

#endif // ObjectWindow_H
