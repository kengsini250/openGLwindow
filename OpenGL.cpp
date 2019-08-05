#include "OpenGL.h"

static GLfloat v[] = {
	0.0f,	1.0f,		0.0f,
	1.0f,	-1.0f,		0.0f,
	-1.0f,	-1.0f,		0.0f
};

static GLfloat vv[] = {
	0.0f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,
	0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,
	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f
};


GLfloat color[] = {
	1.0f,	0.0f,	0.0f,
	0.0f,	1.0f,	0.0f,
	0.0f,	0.0f,	1.0f
};


OpenGL::OpenGL(QWindow* parent)
	: QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, parent)
{
	setWidth(1024);
	setHeight(768);
}

OpenGL::~OpenGL()
{
	delete glsl;
}

void OpenGL::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, 0);
/*
	//vbo
	vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vbo->create();
	vbo->bind();
	vbo->allocate(vv, sizeof(vv));
	vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
*/
	//shader:
	glsl = new QOpenGLShaderProgram;
	glsl->addShaderFromSourceFile(QOpenGLShader::Vertex, "VertexShader.vert");
	glsl->addShaderFromSourceFile(QOpenGLShader::Fragment, "FragmentShader.frag");
	glsl->link();
	glsl->bind();	

	vertexLocation = glsl->attributeLocation("Pos");
	//glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(void*)0);//使用已绑定的vbo
	//glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, v);//不用vbo
	//glsl->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));//使用已绑定的vbo
	//glsl->enableAttributeArray(vertexLocation);

	fragmentLocation = glsl->attributeLocation("fragPos");
	//glVertexAttribPointer(fragmentLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));//使用已绑定的vbo
	//glVertexAttribPointer(fragmentLocation, 3, GL_FLOAT, GL_FALSE, 0, color);//不用vbo
	//glsl->setAttributeBuffer(fragmentLocation, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));//使用已绑定的vbo
	//glsl->enableAttributeArray(fragmentLocation);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(22);
}

void OpenGL::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void OpenGL::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if ((color[0] >= 0) && (f1))
	{
		color[0] -= 0.1f;
		color[4] -= 0.1f;
		color[8] -= 0.1f;

		color[1] += 0.1f;		
		color[5] += 0.1f;
		color[6] += 0.1f;
	}
	else
	{
		f1 = 0;
		f2 = 1;
	}

	if ((color[1] >= 0) && (f2))
	{
		color[1] -= 0.1f;
		color[5] -= 0.1f;
		color[6] -= 0.1f;

		color[2] += 0.1f;
		color[3] += 0.1f;		
		color[7] += 0.1f;
	}
	else
	{
		f2 = 0;
		f3 = 1;
	}

	if ((color[2] >= 0) && (f3))
	{
		color[2] -= 0.1f;
		color[3] -= 0.1f;
		color[7] -= 0.1f;

		color[0] += 0.1f;		
		color[4] += 0.1f;		
		color[8] += 0.1f;
	}
	else
	{
		f3 = 0;
		f1 = 1;
	}

	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, v);
	glVertexAttribPointer(fragmentLocation, 3, GL_FLOAT, GL_FALSE, 0, color);
	glsl->enableAttributeArray(vertexLocation);
	glsl->enableAttributeArray(fragmentLocation);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glsl->disableAttributeArray(vertexLocation);
}


