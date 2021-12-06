#pragma  warning(disable:4996)   
#include<gl/glut.h>
#include<gl/glaux.h>
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
static float r_earth = 30.0;
static float r_moon = 20.0;

//�������
static float d_sun_earth = 200.0;
static float d_earth_moon = 60.0;

//��������
static float sphere_slices = 30.0;
static float sphere_stacks = 15.0;

//����
GLuint texture_sun;
GLuint texture_earth;
GLuint texture_moon;
GLUquadricObj *quadObj;

//�����
static float wh = 1.0 / 1.0;

static bool is_show_track = false;	//��ʾ���й��
static float day = 0.0;		//��ǰ����

//����λͼ
bool load_bmp(const char* filename, GLuint &texture)
{
	AUX_RGBImageRec * imageData = NULL;
	imageData = auxDIBImageLoadA(filename);
	if (imageData == NULL) {
		printf("%sͼƬ���ݶ�ȡʧ�ܣ�\n");
		return false;
	}
	glGenTextures(1, &texture);		//��texture�з���1������δʹ�õ�ֵ,��ʾ������������
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageData->sizeX, imageData->sizeY, GL_RGB, GL_UNSIGNED_BYTE, imageData->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//������˺�������Ҫ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	free(imageData->data);
	free(imageData);
	return true;
}

//��ʼ������,������Դ��������ͼ
void initial(void)
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);	//������Ȳ���
	glEnable(GL_COLOR_MATERIAL);

	quadObj = gluNewQuadric();
	//��ȡ̫������
	load_bmp("img/sun.bmp", texture_sun);
	//��ȡ��������
	load_bmp("img/earth.bmp", texture_earth);
	//��ȡ��������
	load_bmp("img/moon.bmp", texture_moon);
}

//����������
void light()
{
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	//��Դλ�ã�ԭ��
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	//�����⣬��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	//�������	����
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	//�����

}

void keyboard(GLint key, GLint x, GLint y)
{
	switch (key) 
	{
		case GLUT_KEY_UP:
			day_per_year = day_per_year *0.9;
			day_per_month = day_per_month *0.9;
			earth_per_circle = earth_per_circle *0.9;
			sun_per_circle = sun_per_circle *0.9;
			break;
		case GLUT_KEY_DOWN:
			day_per_year = day_per_year *1.1;
			day_per_month = day_per_month *1.1;
			earth_per_circle = earth_per_circle *1.1;
			sun_per_circle = sun_per_circle *1.1;
			break;
		case GLUT_KEY_LEFT:
			is_show_track = !is_show_track;
			break;
		default:
			break;
	}
}

//�����ʾ
void show_track(float d)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 100; i++) {
		glVertex3f(d *cos(2 * i*Pi / 100), d*sin(2 * i*Pi / 100), 0.0f);
	}
	glEnd();
}

//̫��
void sun() 
{
	glPushMatrix();
	quadObj = gluNewQuadric();	//����һ��������������
	//��Ⱦ����
	glBindTexture(GL_TEXTURE_2D, texture_sun);	//����һ���󶨵�Ŀ������������Ƶ�����
	gluQuadricTexture(quadObj, GL_TRUE);	//���øö������������
	gluQuadricDrawStyle(quadObj, GLU_FILL);	//���������
	//̫������
	GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //������ʵĻ�������ɫ��Ϊ0
	GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //������ʵ����������ɫ��Ϊ0
	GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵľ��淴�����ɫ��Ϊ0
	GLfloat sun_mat_emission[] = { 1.0f, 0.7f, 0.7f, 1.0f };   //������ʵķ������ɫ���׹�ƫ��
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	gluSphere(quadObj, r_sun, sphere_slices, sphere_stacks);	//��������

	glPopMatrix();
} 

//����
void earth() 
{
	glPushMatrix();
	//��Ⱦ���� 
	glBindTexture(GL_TEXTURE_2D, texture_earth);	//����һ���󶨵�Ŀ������������Ƶ�����
	gluQuadricTexture(quadObj, GL_TRUE);	//���øö������������
	//�������
	GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //������ʵĻ�������ɫ��Ϊ0
	GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //������ʵ����������ɫ���׹�
	GLfloat earth_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };   //������ʵľ��淴�����ɫ�����
	GLfloat earth_mat_emission[] = { 0.1f, 0.1f, 0.2f, 1.0f };   //������ʵķ������ɫ���ҹ�ƫ��
	GLfloat earth_mat_shininess = 50.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	gluSphere(quadObj, r_earth, sphere_slices, sphere_stacks);	//��������
	glPopMatrix();
}

//����
void moon() 
{
	glPushMatrix();
	//��Ⱦ����
	glBindTexture(GL_TEXTURE_2D, texture_moon);	//����һ���󶨵�Ŀ������������Ƶ�����
	glEnable(GL_TEXTURE_2D);	//���ö�ά����
	gluQuadricTexture(quadObj, GL_TRUE);	//���øö������������
	//�������
	GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //������ʵĻ�������ɫ��Ϊ0
	GLfloat moon_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //������ʵ����������ɫ����ɫ
	GLfloat moon_mat_specular[] = { 0.7f, 0.7f, 1.0f, 1.0f };   //������ʵľ��淴�����ɫ���׹�ƫ��
	GLfloat moon_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵķ������ɫ��Ϊ0
	GLfloat moon_mat_shininess = 50.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, moon_mat_shininess);

	gluSphere(quadObj, r_moon, sphere_slices, sphere_stacks);	//��������
	glPopMatrix();
}

//չʾ�յ���
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//�����Ȼ���

	// ����͸��Ч����ͼ      
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, wh, 1.0, 600);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -300, 300, 0, 0, 0, 0, 0, 1);

	//����
	light();

	//�������
	if(is_show_track) show_track(d_sun_earth);

	// ���ƺ�ɫ��̫����̫����תԼ25��
	glPushMatrix();
	glRotatef(fmod(day / sun_per_circle * 360.0, 360.0), 0.0f, 0.0f, 1.0f);	//̫������������ת,��ʱ��
	sun();
	glPopMatrix();

	//���Ƶ���
	//����ת
	glRotatef(fmod(day / day_per_year * 360.0, 360.0) , 0.0f, 0.0f, 1.0f);	//�����������򶫹�ת,��ʱ��
	glTranslatef(d_sun_earth, 0.0f, 0.0f);
	//������ת
	glPushMatrix();
	glRotatef(fmod(day / earth_per_circle * 360.0, 360.0), 0.1f, 0.0f, 1.0f);
	earth();
	//���¹������
	if (is_show_track) show_track(d_earth_moon);
	glPopMatrix();

	// ��������
	glRotatef(fmod(day / day_per_month *360.0, 360.0), 0.0f , 0.0f, -1.0f);
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	//�趨������ʾģʽ��RGB��ɫģ�ͺ�˫����
	glutInitWindowPosition(100, 100);	//�趨���ڵĳ�ʼλ�ã���Ļ���Ͻ�Ϊԭ�㣬��λΪ����
	glutInitWindowSize(600, 600);	//�趨���ڵĴ�С
	glutCreateWindow("�յ���-��ͼ�����");	//����һ������

	printf("������\n");
	printf("1. ��'��'�ӿ��ٶ�\n");
	printf("2. ��'��'�����ٶ�\n");
	printf("3. ��'��'�л�ȡ��/��ʾ�������й켣\n");
	printf("PS:���ڵ�����ת�ٶ�1��1ת�������ԣ��˴��Ŵ�Ϊ7����תһȦ���ٶȼ���Ϊԭ����1/7�������������յ�����ת��ת�ٶȾ�������ʵ��\n");

	initial();
	glutSpecialFunc(&keyboard);	//��λ����
	glutTimerFunc(25, timer_callback, 1);	//ÿ25msˢ��һ��
	glutDisplayFunc(&display);	//��myDisplayָ��Ϊ��ǰ���ڵ���ʾ���ݺ���
	glutMainLoop();	//ʹ���ڿ����������
	return 0;
} 