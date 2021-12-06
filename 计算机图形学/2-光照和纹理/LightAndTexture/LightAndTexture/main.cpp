#pragma  warning(disable:4996)   
#include<gl/glut.h>
#include<gl/glaux.h>
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
static float r_earth = 30.0;
static float r_moon = 20.0;

//天体距离
static float d_sun_earth = 200.0;
static float d_earth_moon = 60.0;

//球体面数
static float sphere_slices = 30.0;
static float sphere_stacks = 15.0;

//纹理
GLuint texture_sun;
GLuint texture_earth;
GLuint texture_moon;
GLUquadricObj *quadObj;

//长宽比
static float wh = 1.0 / 1.0;

static bool is_show_track = false;	//显示运行轨道
static float day = 0.0;		//当前天数

//加载位图
bool load_bmp(const char* filename, GLuint &texture)
{
	AUX_RGBImageRec * imageData = NULL;
	imageData = auxDIBImageLoadA(filename);
	if (imageData == NULL) {
		printf("%s图片数据读取失败！\n");
		return false;
	}
	glGenTextures(1, &texture);		//在texture中返回1个当期未使用的值,表示纹理对象的名称
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageData->sizeX, imageData->sizeY, GL_RGB, GL_UNSIGNED_BYTE, imageData->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//纹理过滤函数，需要两遍
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	free(imageData->data);
	free(imageData);
	return true;
}

//初始化函数,启动光源、材质贴图
void initial(void)
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);	//启动深度测试
	glEnable(GL_COLOR_MATERIAL);

	quadObj = gluNewQuadric();
	//读取太阳纹理
	load_bmp("img/sun.bmp", texture_sun);
	//读取地球纹理
	load_bmp("img/earth.bmp", texture_earth);
	//读取月球纹理
	load_bmp("img/moon.bmp", texture_moon);
}

//创建环境光
void light()
{
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	//光源位置，原点
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	//环境光，黑
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);	//漫反射光	，白
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	//镜面光

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

//轨道显示
void show_track(float d)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 100; i++) {
		glVertex3f(d *cos(2 * i*Pi / 100), d*sin(2 * i*Pi / 100), 0.0f);
	}
	glEnd();
}

//太阳
void sun() 
{
	glPushMatrix();
	quadObj = gluNewQuadric();	//创建一个二次曲面物体
	//渲染球体
	glBindTexture(GL_TEXTURE_2D, texture_sun);	//建立一个绑定到目标纹理的有名称的纹理
	gluQuadricTexture(quadObj, GL_TRUE);	//启用该二次曲面的纹理
	gluQuadricDrawStyle(quadObj, GLU_FILL);	//启用面填充
	//太阳材质
	GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的环境光颜色，为0
	GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的漫反射光颜色，为0
	GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色，为0
	GLfloat sun_mat_emission[] = { 1.0f, 0.7f, 0.7f, 1.0f };   //定义材质的辐射广颜色，白光偏红
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	gluSphere(quadObj, r_sun, sphere_slices, sphere_stacks);	//二次曲面

	glPopMatrix();
} 

//地球
void earth() 
{
	glPushMatrix();
	//渲染球体 
	glBindTexture(GL_TEXTURE_2D, texture_earth);	//建立一个绑定到目标纹理的有名称的纹理
	gluQuadricTexture(quadObj, GL_TRUE);	//启用该二次曲面的纹理
	//地球材质
	GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的环境光颜色，为0
	GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的漫反射光颜色，白光
	GLfloat earth_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色，红光
	GLfloat earth_mat_emission[] = { 0.1f, 0.1f, 0.2f, 1.0f };   //定义材质的辐射光颜色，灰光偏蓝
	GLfloat earth_mat_shininess = 50.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	gluSphere(quadObj, r_earth, sphere_slices, sphere_stacks);	//二次曲面
	glPopMatrix();
}

//月球
void moon() 
{
	glPushMatrix();
	//渲染球体
	glBindTexture(GL_TEXTURE_2D, texture_moon);	//建立一个绑定到目标纹理的有名称的纹理
	glEnable(GL_TEXTURE_2D);	//启用二维纹理
	gluQuadricTexture(quadObj, GL_TRUE);	//启用该二次曲面的纹理
	//月球材质
	GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的环境光颜色，为0
	GLfloat moon_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的漫反射光颜色，白色
	GLfloat moon_mat_specular[] = { 0.7f, 0.7f, 1.0f, 1.0f };   //定义材质的镜面反射光颜色，白光偏蓝
	GLfloat moon_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat moon_mat_shininess = 50.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, moon_mat_shininess);

	gluSphere(quadObj, r_moon, sphere_slices, sphere_stacks);	//二次曲面
	glPopMatrix();
}

//展示日地月
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清空深度缓冲

	// 创建透视效果视图      
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, wh, 1.0, 600);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -300, 300, 0, 0, 0, 0, 0, 1);

	//环境
	light();

	//轨道绘制
	if(is_show_track) show_track(d_sun_earth);

	// 绘制红色的太阳，太阳自转约25天
	glPushMatrix();
	glRotatef(fmod(day / sun_per_circle * 360.0, 360.0), 0.0f, 0.0f, 1.0f);	//太阳是自西向东自转,逆时针
	sun();
	glPopMatrix();

	//绘制地球
	//地球公转
	glRotatef(fmod(day / day_per_year * 360.0, 360.0) , 0.0f, 0.0f, 1.0f);	//地球是自西向东公转,逆时针
	glTranslatef(d_sun_earth, 0.0f, 0.0f);
	//地球自转
	glPushMatrix();
	glRotatef(fmod(day / earth_per_circle * 360.0, 360.0), 0.1f, 0.0f, 1.0f);
	earth();
	//地月轨道绘制
	if (is_show_track) show_track(d_earth_moon);
	glPopMatrix();

	// 绘制月亮
	glRotatef(fmod(day / day_per_month *360.0, 360.0), 0.0f , 0.0f, -1.0f);
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	//设定窗口显示模式，RGB颜色模型和双缓存
	glutInitWindowPosition(100, 100);	//设定窗口的初始位置，屏幕左上角为原点，单位为像素
	glutInitWindowSize(600, 600);	//设定窗口的大小
	glutCreateWindow("日地月-贴图与光照");	//创建一个窗口

	printf("操作：\n");
	printf("1. 按'↑'加快速度\n");
	printf("2. 按'↓'减慢速度\n");
	printf("3. 按'←'切换取消/显示天体运行轨迹\n");
	printf("PS:由于地球自转速度1日1转看不明显，此处放大为7天自转一圈，速度减慢为原来的1/7。除此外其余日地月自转公转速度均遵照现实。\n");

	initial();
	glutSpecialFunc(&keyboard);	//键位控制
	glutTimerFunc(25, timer_callback, 1);	//每25ms刷新一次
	glutDisplayFunc(&display);	//将myDisplay指定为当前窗口的显示内容函数
	glutMainLoop();	//使窗口框架运行起来
	return 0;
} 