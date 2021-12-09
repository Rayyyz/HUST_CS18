#include<gl/GLUT.H>
#include<stdio.h>
#include<math.h>
#include<time.h>

#define Pi 3.14159

//һ�������
static float day_per_year = 360.0; //������ת�Ƕ�
//һ�µ�����
static float day_per_month = 30.0;	 //������ת�͹�ת�Ƕ�
//������ת������
static float earth_per_circle = 7.0;	//һ��תһȦ��ȫ�����������������Ҫ7�죬����7��
//̫����ת������
static float sun_per_circle = 27.0;

//����뾶
static float r_sun = 70.0;
static float r_earth = 25.0;
static float r_moon = 15.0;

//�������
static float d_sun_earth = 200.0;
static float d_earth_moon = 50.0;

//��������
static float sphere_slices = 30.0;
static float sphere_stacks = 30.0;

//����
GLuint texture_object;


static bool is_show_rotate = true;	//��ʾ��ת���
static bool is_show_wiresphere = true;	//��ʾ���徭γ��
static bool is_show_track = true;	//��ʾ���й��
static float day = 0.0;		//��ǰ����

//��ʼ������,������Դ��������ͼ
void initial(void)
{
	glEnable(GL_DEPTH_TEST);	//������Ȳ���
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glMatrixMode(GL_PROJECTION);	//OpenGL������ά��ʽ������ͼ��

}

void keyboard(GLint key, GLint x, GLint y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		is_show_rotate = !is_show_rotate;
		break;
	case GLUT_KEY_DOWN:
		is_show_wiresphere = !is_show_wiresphere;
		break;
	case GLUT_KEY_LEFT:
		is_show_track = !is_show_track;
		break;
	default:
		break;
	}
}

//��ʾ��ת���
void show_self_rotate(float r)
{
	glTranslatef(-r, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(r*0.05, 12, 12);//��Ⱦ����
}

//��ʾ����ľ�γ��
void show_wire_sphere(float r)
{
	glColor3f(0.6f, 0.6f, 0.6f);
	glutWireSphere(r*1.01, sphere_slices, sphere_stacks);
}

//�����ʾ
void show_track(float d)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < 100; i++) {
		glVertex3f(d *cos(2 * i*Pi / 100), d*sin(2 * i*Pi / 100), 0.0f);
	}
	glEnd();
}

//̫��
void sun()
{
	glPushMatrix();
	//��Ⱦ����
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(r_sun, sphere_slices, sphere_stacks);
	//��Ⱦ��γ��
	if (is_show_wiresphere) show_wire_sphere(r_sun);
	//��ת���
	if (is_show_rotate) show_self_rotate(r_sun);
	glPopMatrix();
}

//����
void earth()
{
	glPushMatrix();
	//��Ⱦ����
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(r_earth, sphere_slices, sphere_stacks);
	//��Ⱦ��γ��
	if (is_show_wiresphere) show_wire_sphere(r_earth);
	//��ʾ��ת���
	if (is_show_rotate) show_self_rotate(r_earth);
	glPopMatrix();
}

//����
void moon()
{
	glPushMatrix();
	//��Ⱦ����
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(r_moon, sphere_slices, sphere_stacks);
	//��Ⱦ��γ��
	if (is_show_wiresphere) show_wire_sphere(r_moon);
	//��ʾ��ת���
	if (is_show_rotate) show_self_rotate(r_moon);
	glPopMatrix();
}

//չʾ�յ���
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//�����Ȼ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -300, 300, 0, 0, 0, 0, 0, 1);

	//�������
	if (is_show_track) show_track(d_sun_earth);

	// ���ƺ�ɫ��̫����̫����תԼ25��
	glPushMatrix();
	glRotatef(fmod(day / sun_per_circle * 360.0, 360.0), 0.0f, 0.0f, 1.0f);	//̫������������ת,��ʱ��
	sun();
	glPopMatrix();

	// ������ɫ�ĵ��򣬵�����תΪ1�죬�յع�תԼ365��
	//����ת
	glRotatef(fmod(day / day_per_year * 360.0, 360.0), 0.0f, 0.0f, 1.0f);	//�����������򶫹�ת,��ʱ��
	glTranslatef(d_sun_earth, 0.0f, 0.0f);
	//������ת
	glPushMatrix();
	glRotatef(fmod(day / earth_per_circle * 360.0, 360.0), 0.1f, 0.0f, 1.0f);
	earth();
	glutSolidSphere(r_earth, sphere_slices, sphere_stacks);
	//���¹������
	if (is_show_track) show_track(d_earth_moon);
	glPopMatrix();

	// ���ƻ�ɫ������
	glRotatef(fmod(day / day_per_month * 360.0, 360.0), 0.0f, 0.0f, -1.0f);
	glTranslatef(d_earth_moon, 0.0f, 0.0f);
	moon();

	glFlush();
	glutSwapBuffers();
}

//��̬����
void timer_callback(int value) {
	day++;
	if (day >= day_per_year) {
		day = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(25, timer_callback, 1);
}


int main(int argc, char * argv[])
{
	glutInit(&argc, argv);	//ʹ��glut����Ҫ���г�ʼ��
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	//�趨������ʾģʽ��RGB��ɫģ�ͺ�˫����
	glutInitWindowPosition(100, 100);	//�趨���ڵĳ�ʼλ�ã���Ļ���Ͻ�Ϊԭ�㣬��λΪ����
	glutInitWindowSize(600, 600);	//�趨���ڵĴ�С
	glutCreateWindow("�յ���-���嶯̬ģ��");	//����һ������

	printf("������\n");
	printf("1. ��'��'�л�ȡ��/��ʾ��ɫ��ת��ǣ��鿴�յ�����ת���\n");
	printf("2. ��'��'�л�ȡ��/��ʾ���徭γ��\n");
	printf("3. ��'��'�л�ȡ��/��ʾ�������й켣\n");
	printf("PS:���ڵ�����ת�ٶ�1��1ת�������ԣ��˴��Ŵ�Ϊ7����תһȦ���ٶȼ���Ϊԭ����1/7�������������յ�����ת��ת�ٶȾ�������ʵ��\n");

	initial();
	glutSpecialFunc(&keyboard);	//esc�˳�
	glutTimerFunc(25, timer_callback, 1);	//ÿ25msˢ��һ��
	glutDisplayFunc(&display);	//��myDisplayָ��Ϊ��ǰ���ڵ���ʾ���ݺ���
	glutMainLoop();	//ʹ���ڿ����������
	return 0;
}