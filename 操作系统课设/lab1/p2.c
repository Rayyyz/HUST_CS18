//每隔一秒1-10循环显示
#include <time.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

char s[1000];
GtkWidget *label;

void *thread(void * argc){
	int i;
	for(i=0;i<=10000;i++){
		sleep(1);
		i = i % 10;
		sprintf(s,"%d",i);
		gtk_label_set_text(GTK_LABEL(label),s);
	}
}


int main( int argc, char *argv[])
{
    	pthread_t id;
    	int i,ret;
    	ret=pthread_create(&id,NULL,&thread,NULL);

 	//定义一个组装盒;
    	GtkWidget *vbox; 
    	GtkWidget *window;
    	//初始化GTK
    	gtk_init(&argc, &argv);
    	//生成窗口构件
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), "loop");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
	//设置标签
	label = gtk_label_new (s);
	gtk_container_add (GTK_CONTAINER (window), label);
	gtk_widget_show (label);


	/*开始显示窗口*/
	gtk_widget_show(window);
	gtk_main();

	return 0;
}
