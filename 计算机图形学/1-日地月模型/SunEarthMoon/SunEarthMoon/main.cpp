#include<gl/GLUT.H>
#include<stdio.h>
#include<math.h>
#include<time.h>

#define Pi 3.14159

//一年的天数
static float day_per_year = 360.0; //地球自转角度
//一月的天数
static float day_per_month = 30.0;	 //月球自转和公转角度
//地球自转的天数
static float earth_per_circle = 7.0;	//一天转一圈完全看不出来，这里假设要7天，放慢7倍
//太阳自转的天数
static float sun_per_circle = 27.0;

//天体半径
static float r_sun = 70.0;
static float r_earth = 25.0;
static float r_moon = 15.0;

//天体距离
static float d_sun_earth = 200.0;
static float d_earth_moon = 50.0;

//球体面数
static float sphere_slices = 30.0;
static float sphere_stacks = 30.0;

//纹理
GLuint texture_object;


static bool is_show_rotate = true;	//显示自转情况
static bool is_show_wiresphere = true;	//显示球体经纬线
static bool is_show_track = true;	//显示运行轨道
static float day = 0.0;		//当前天数

//初始化函数,启动光源、材质贴图
void initial(void)
{
	glEnable(GL_DEPTH_TEST);	//启动深度测试
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glMatrixMode(GL_PROJECTION);	//OpenGL按照三维方式来处理图像

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

//显示自转情况
void show_self_rotate(float r)
{
	glTranslatef(-r, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(r*0.05, 12, 12);//渲染球体
}

//显示球体的经纬线
void show_wire_sphere(float r)
{
	glColor3f(0.6f, 0.6f, 0.6f);
	glutWireSphere(r*1.01, sphere_slices, sphere_stacks);
}

//轨道显示
void show_track(float d)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < 100; i++) {
		glVertex3f(d *cos(2 * i*Pi / 100), d*sin(2 * i*Pi / 100), 0.0f);
	}
	glEnd();
}

//太阳
void sun()
{
	glPushMatrix();
	//渲染球体
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(r_sun, sphere_slices, sphere_stacks);
	//渲染经纬线
	if (is_show_wiresphere) show_wire_sphere(r_sun);
	//自转情况
	if (is_show_rotate) show_self_rotate(r_sun);
	glPopMatrix();
}

//地球
void earth()
{
	glPushMatrix();
	//渲染球体
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(r_earth, sphere_slices, sphere_stacks);
	//渲染经纬线
	if (is_show_wiresphere) show_wire_sphere(r_earth);
	//显示自转情况
	if (is_show_rotate) show_self_rotate(r_earth);
	glPopMatrix();
}

//月球
void moon()
{
	glPushMatrix();
	//渲染球体
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(r_moon, sphere_slices, sphere_stacks);
	//渲染经纬线
	if (is_show_wiresphere) show_wire_sphere(r_moon);
	//显示自转情况
	if (is_show_rotate) show_self_rotate(r_moon);
	glPopMatrix();
}

//展示日地月
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清空深度缓冲
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -300, 300, 0, 0, 0, 0, 0, 1);

	//轨道绘制
	if (is_show_track) show_track(d_sun_earth);

	// 绘制红色的太阳，太阳自转约25天
	glPushMatrix();
	glRotatef(fmod(day / sun_per_circle * 360.0, 360.0), 0.0f, 0.0f, 1.0f);	//太阳是自西向东自转,逆时针
	sun();
	glPopMatrix();

	// 绘制蓝色的地球，地球自转为1天，日地公转约365天
	//地球公转
	glRotatef(fmod(day / day_per_year * 360.0, 360.0), 0.0f, 0.0f, 1.0f);	//地球是自西向东公转,逆时针
	glTranslatef(d_sun_earth, 0.0f, 0.0f);
	//地球自转
	glPushMatrix();
	glRotatef(fmod(day / earth_per_circle * 360.0, 360.0), 0.1f, 0.0f, 1.0f);
	earth();
	glutSolidSphere(r_earth, sphere_slices, sphere_stacks);
	//地月轨道绘制
	if (is_show_track) show_track(d_earth_moon);
	glPopMatrix();

	// 绘制黄色的月亮
	glRotatef(fmod(day / day_per_month * 360.0, 360.0), 0.0f, 0.0f, -1.0f);
	glTranslatef(d_earth_moon, 0.0f, 0.0f);
	moon();

	glFlush();
	glutSwapBuffers();
}

//动态绘制
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
	glutInit(&argc, argv);	//使用glut库需要进行初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	//设定窗口显示模式，RGB颜色模型和双缓存
	glutInitWindowPosition(100, 100);	//设定窗口的初始位置，屏幕左上角为原点，单位为像素
	glutInitWindowSize(600, 600);	//设定窗口的大小
	glutCreateWindow("日地月-球体动态模型");	//创建一个窗口

	printf("操作：\n");
	printf("1. 按'↑'切换取消/显示白色旋转标记，查看日地月自转情况\n");
	printf("2. 按'↓'切换取消/显示球体经纬线\n");
	printf("3. 按'←'切换取消/显示天体运行轨迹\n");
	printf("PS:由于地球自转速度1日1转看不明显，此处放大为7天自转一圈，速度减慢为原来的1/7。除此外其余日地月自转公转速度均遵照现实。\n");

	initial();
	glutSpecialFunc(&keyboard);	//esc退出
	glutTimerFunc(25, timer_callback, 1);	//每25ms刷新一次
	glutDisplayFunc(&display);	//将myDisplay指定为当前窗口的显示内容函数
	glutMainLoop();	//使窗口框架运行起来
	return 0;
}