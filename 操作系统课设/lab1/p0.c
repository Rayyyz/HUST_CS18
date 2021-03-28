//每隔一秒显示时间
#include <time.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

char s[50];
GtkWidget *label;

void gettime(){
	time_t timep;
	time (&timep);
	sprintf(s,"%s",ctime(&timep));
}

void *thread(void * argc){
	while(1){
		gettime();
        	gtk_label_set_text(GTK_LABEL(label),s);
        	sleep(1);
	}
}


int main( int argc, char *argv[]){
    	pthread_t id;
    	int i,ret;

 	//定义一个组装盒;
    	GtkWidget *vbox; 
    	GtkWidget *window;
    	//初始化GTK
    	gtk_init(&argc, &argv);
    	//生成窗口构件
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), "time");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
	//设置标签
	label = gtk_label_new (s);
	gtk_container_add (GTK_CONTAINER (window), label);
	gtk_widget_show (label);

    	ret=pthread_create(&id,NULL,&thread,NULL);

	/*开始显示窗口*/
	gtk_widget_show(window);
	gtk_main();

	return 0;
}
