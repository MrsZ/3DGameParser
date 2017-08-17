//#define _CRT_SECURE_NO_WARNINGS
//#include <GLTools.h>	// OpenGL toolkit
//#include <GLMatrixStack.h>
//#include <GLFrame.h>
//#include <GLFrustum.h>
//#include <GLBatch.h>
//#include <GLGeometryTransform.h>
//
//#define FREEGLUT_STATIC
//
//#include <math.h>
//#ifdef __APPLE__
//#include <glut/glut.h>
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>
//#endif
//
//#define bmpFileName "NinjaComp.BMP"
//#define jpegFileName "ttcover.jpeg"
//#define bmpjpegfileName "ppcover.bmp"
//static GLint imagewidth;
//static GLint imageheight;
//static GLint pixellength;
//static GLubyte* pixeldata;
//static GLubyte* jpglpdata;
//GLuint g_textures;				//�洢ͼƬ����
//#include<stdio.h>
//#include<stdlib.h>
//#include <atlimage.h>
//#include < Gdiplus.h>  
//#pragma comment(lib, "Gdiplus.lib")  
//using namespace Gdiplus;
//#include <Objbase.h>  
//#include <Objidl.h>  
//#pragma comment(lib, "Ole32.lib")  
//#pragma comment(lib, "Uuid.lib") 
//void display(void)
//{
//	//glClear(GL_COLOR_BUFFER_BIT);
//	//��������
//	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
//	//glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, jpglpdata);
//	//---------------------------------
//	glFlush();
//	glutSwapBuffers();
//}
//
////������ͨͼƬ
//void LoadGLTextures(CString path)
//{
//	glGenTextures(1, &g_textures);
//	CImage img;
//	img.Load(path); //  ͨ��ͼƬ�ļ�����������
//	int width = img.GetWidth();
//	int height = img.GetHeight();
//	unsigned char *pData = NULL;
//	if (img.GetPitch() < 0) //GetBits�����þ��ǻ�������λ��Ϣ������ָ�룬���λͼ�Ǵ��µ��ϣ� ��ָ�򻺳���ĩ�ˣ�����ָ�򻺳����׶ˡ���img.GetPitch ����������ж����ã�С�� 0 ָ��ĩ��
//		jpglpdata = (unsigned char *)img.GetBits() + (img.GetPitch()*(img.GetHeight() - 1));
//	else
//		jpglpdata = (unsigned char *)img.GetBits();
//	glBindTexture(GL_TEXTURE_2D, g_textures);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, jpglpdata);
//}
//
//int main(int argc, char* argv[])
//{
//	//���ļ�
//	//FILE* pfile = fopen(bmpFileName, "rb");
//	FILE* pfile = fopen(bmpjpegfileName, "rb");
//	if (pfile == 0)	exit(0);
//
//	//LoadGLTextures(jpegFileName);
//
//	//��ȡͼ���С
//	fseek(pfile, 0x0012, SEEK_SET);
//	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
//	fread(&imageheight, sizeof(imageheight), 1, pfile);
//	//�����������ݳ���
//	pixellength = imagewidth * 3;
//	while (pixellength % 4 != 0)pixellength++;
//	pixellength *= imageheight;
//	//��ȡ��������
//	pixeldata = (GLubyte*)malloc(pixellength);
//	if (pixeldata == 0) exit(0);
//	fseek(pfile, 54, SEEK_SET);
//	fread(pixeldata, pixellength, 1, pfile);
//
//	//�ر��ļ�
//	fclose(pfile);
//	//��ʼ��glut����
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(imagewidth, imageheight);
//	glutCreateWindow(bmpFileName);
//	glutDisplayFunc(&display);
//	glutMainLoop();
//	//-------------------------------------
//	free(pixeldata);
//	//free(jpglpdata);
//	return 0;
//}