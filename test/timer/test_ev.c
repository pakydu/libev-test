#if ! EV_MULTIPLICITY
#define EV_MULTIPLICITY 1
#endif
#include<stdio.h>
#include <ev.h>
#include <stdio.h>
#include <pthread.h>

// 定时器回调函数
static void timer_callback(EV_P_ ev_timer *w, int revents) {
    printf("Timer ticked!, loop %p, revents=%d\n", loop, revents);
    // 重新启动定时器
    //ev_timer_again(EV_A_ w);
}

static void timer_callback2(EV_P_ ev_timer *w, int revents) {
	static int count = 0;
    printf("Timer2 ticked!, loop %p, revents=%d\n", loop, revents);
	count++;
	if (count > 5) {
		ev_timer_stop(loop, w);
	}	
    // 重新启动定时器
    //ev_timer_again(EV_A_ w);
}

void *thread_func(void *arg) {
	struct ev_loop *loop = arg;
	ev_run(loop, 0);

}

int main() {
	#if 0
    // 初始化libev事件循环
	//use default loop
    //EV_DEFAULT;

	//use default loop by ower
	//struct ev_loop *loop = ev_default_loop(0);

	//use create loop which can define the module: select/poll/epoll
	struct ev_loop *loop = ev_loop_new(EVBACKEND_SELECT); // 指定后端模型（如select/poll/epoll）

    // 创建一个定时器watcher
    ev_timer my_timer;
    // 设置定时器的回调函数和超时时间（1秒）, 循环timer
    ev_timer_init(&my_timer, timer_callback, 1.0, 1);

    // 启动定时器watcher
	//use default loop
	//ev_timer_start(EV_DEFAULT_ &my_timer);

	//use define loop
    ev_timer_start(loop, &my_timer);

    // 进入事件循环
	//use default loop
    //ev_run(EV_DEFAULT,0);

	//use define loop
	ev_run(loop, 0);
	#else
	ev_timer timer1, timer2;
	struct ev_loop *loop1 = ev_loop_new(0);
	struct ev_loop *loop2 = ev_loop_new(0);

	ev_timer_init(&timer1, timer_callback, 5.0, 1);
	ev_timer_start(loop1, &timer1);

	ev_timer_init(&timer2, timer_callback2, 2.0, 1);
	//ev_timer_start(loop2, &timer2);
	ev_timer_start(loop1,&timer2);

	//pthread_t tid1;
	//pthread_create(&tid1, NULL, thread_func, loop2);

	ev_run(loop1, 0);
	//pthread_join(tid1, NULL);
	//ev_run(loop2, 0);

	ev_loop_destroy(loop1);
	ev_loop_destroy(loop2);
	#endif

    return 0;
}