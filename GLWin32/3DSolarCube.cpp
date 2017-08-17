//#include <windows.h>    
//#include <gl/gl.h>    
//#include <gl/glu.h>    
//
//#define WIN32_LEAN_AND_MEAN  
//
//#pragma comment(lib, "openGL32.lib")  
//#pragma comment(lib, "glu32.lib")  
//float angle = 0.0f;
//HDC g_HDC;
//float legAngle[2] = { 0.0f,0.0f };
//float armAngle[2] = { 0.0f,0.0f };
//float ambientLight[] = { 0.1f,0.3f,0.8f,1.0f };  //������  
//float diffuseLight[] = { 0.25f,0.25f,0.25f,1.0f }; //ɢ���  
//float lightPosition[] = { 0.0f,0.0f,1.0f,0.0f }; //��Դλ��  
//												 //���ʱ���  
//float matAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
//float matDiff[] = { 1.0f,1.0f,1.0f,1.0f };
////��ʼ��  
//void Initialize()
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   //������ɫΪ��ɫ  
//	glShadeModel(GL_SMOOTH);     //ʹ��ƽ����������  
//	glEnable(GL_DEPTH_TEST);     //�޳�������  
//	glEnable(GL_CULL_FACE);      //���������α���  
//	glFrontFace(GL_CCW);      //�������ʱ�뷽��Ϊ����  
//	glEnable(GL_LIGHTING);      //���ù���  
//								//ΪLIGHT0��������  
//	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
//	//���ڿ�ʼ��ЭLIGHT0  
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //���û��������  
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //����ɢ������  
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //���ù�Դ�ڳ����е�λ��  
//													  //���ù�  
//	glEnable(GL_LIGHT0);
//}
////���Ƶ�λ������  
//void DrawCube(float xPos, float yPos, float zPos)
//{
//	glPushMatrix();
//	glTranslatef(xPos, yPos, zPos);
//	glBegin(GL_QUADS);    //����  
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	glEnd();
//	glBegin(GL_QUADS);    //����  
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	glEnd();
//	glBegin(GL_QUADS);    //ǰ��  
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	glEnd();
//	glBegin(GL_QUADS);    //����  
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	glEnd();
//	glBegin(GL_QUADS);    //����  
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	glEnd();
//	glBegin(GL_QUADS);    //����  
//	glNormal3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	glEnd();
//	glPopMatrix();
//}
////�������Ļ���  
//void Render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������ɫ/��Ȼ���  
//	glLoadIdentity();     //��λ��ת�Ƕȼ�����  
//	angle = angle + 0.1f;     //������ת�Ƕȼ�����  
//	if (angle >= 360.0f)     //�������תһ��,��λ������  
//		angle = 0.0f;
//	glTranslatef(0.0f, 0.0f, -3.0f);
//	glRotatef(angle, 1.0f, 0.0f, 0.0f);
//	glRotatef(angle, 0.0f, 1.0f, 0.0f);
//	glRotatef(angle, 0.0f, 0.0f, 1.0f);
//	DrawCube(0.0f, 0.0f, 0.0f);
//	glFlush();
//	SwapBuffers(g_HDC);     //����ǰ�󻺴�  
//}
////Ϊ�豸�����������ظ�ʽ�ĺ���  
//void SetupPixelFormat(HDC hDC)
//{
//	int nPixelFormat;
//	static PIXELFORMATDESCRIPTOR pfd =
//	{
//		sizeof(PIXELFORMATDESCRIPTOR),
//		1,
//		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
//		PFD_TYPE_RGBA,
//		32,
//		0,0,0,0,0,0,
//		0,
//		0,
//		0,
//		0,0,0,0,
//		16,
//		0,
//		0,
//		PFD_MAIN_PLANE,
//		0,
//		0,0,0
//	};
//	nPixelFormat = ChoosePixelFormat(hDC, &pfd);
//	SetPixelFormat(hDC, nPixelFormat, &pfd);
//}
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	static HGLRC hRC;
//	static HDC hDC;
//	int width, height;
//	switch (message)
//	{
//	case WM_CREATE:
//		hDC = GetDC(hwnd);
//		g_HDC = hDC;
//		SetupPixelFormat(hDC);
//		hRC = wglCreateContext(hDC);
//		wglMakeCurrent(hDC, hRC);
//		return 0;
//		break;
//
//	case WM_CLOSE:
//		wglMakeCurrent(hDC, NULL);
//		wglDeleteContext(hRC);
//		PostQuitMessage(0);
//		return 0;
//		break;
//
//	case WM_SIZE:
//		height = HIWORD(lParam);
//		width = LOWORD(lParam);
//		if (height == 0)
//			height = 1;
//		glViewport(0, 0, width, height);
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluPerspective(54.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//		return 0;
//		break;
//	default:
//		break;
//	}
//	return (DefWindowProc(hwnd, message, wParam, lParam));
//}
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//{
//	WNDCLASSEX windowClass;
//	HWND hwnd;
//	MSG msg;
//	bool done;
//	int width = 800;
//	int height = 600;
//	int bits = 32;
//	windowClass.cbSize = sizeof(WNDCLASSEX);
//	windowClass.style = CS_HREDRAW | CS_VREDRAW;
//	windowClass.lpfnWndProc = WndProc;
//	windowClass.cbClsExtra = 0;
//	windowClass.cbWndExtra = 0;
//	windowClass.hInstance = hInstance;
//	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	windowClass.hbrBackground = NULL;
//	windowClass.lpszMenuName = NULL;
//	windowClass.lpszClassName = L"MyClass";
//	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
//	if (!RegisterClassEx(&windowClass))
//		return 0;
//	hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
//		L"MyClass",
//		L"OpenGL Cube",
//		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
//		0, 0,
//		800, 600,
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//	if (!hwnd)
//		return 0;
//	ShowWindow(hwnd, SW_SHOW);
//	UpdateWindow(hwnd);
//	Initialize();  //��ʼ�����ƻ���  
//	done = false;
//	while (!done)
//	{
//		PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);
//		if (msg.message == WM_QUIT)
//		{
//			done = true;
//		}
//		else
//		{
//			Render();
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//	return msg.wParam;
//}