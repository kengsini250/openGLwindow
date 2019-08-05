#ifndef OPENGL_H
#define OPENGL_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Compatibility>

#include <QOpenGLBuffer> 
#include <QOpenGLShaderProgram>

#include <QTimer>

class OpenGL : public QOpenGLWindow , protected QOpenGLFunctions_4_5_Compatibility
{
    Q_OBJECT
public:

	OpenGL(QWindow* parent = 0);
	~OpenGL();

protected:

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

private:
	QTimer* timer;

	QOpenGLShaderProgram* glsl;
	QOpenGLBuffer* vbo;

	int f1 = 1, f2 = 0, f3 = 0;

	GLint vertexLocation, fragmentLocation;
};

#endif // OPENGL_H
