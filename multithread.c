

//多线程中的互斥和同步
//
//互斥实现：互斥锁            f
//同步实现：条件变量   posix信号量

//互斥锁有两种初始化方式：定义时直接赋值初始化，最后不需要手动释放；   函数接口初始化，最后需要手动释放






#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

int ticket=100;
//pthread_mutex_t=PTHREAD_MUTEX_INITIALIZER
pthread_mutex_t mutex;

void handler(void *arg)
{
	 
	 int id=(int)arg;
	 while(ticket>0)
	 {
	//	int pthread_mutex_lock(pthread_mutex_t *mutex);  阻塞加锁，如果获取不到锁就等待锁被解开
    //	int pthread_mutex_trylock(pthread_mutex_t *mutex);  非阻塞加锁，如果获取不到锁则立即报错返回

         pthread_mutex_lock(&mutex);
	     usleep(100);
		 printf("黄牛[%d]:  gegt a ticket:    %d!!!\n",id,ticket);
		 ticket--;
		 
	//  int pthread_mutex_unlock(pthread_mutex_t *mutex);   加锁之后在任意有可能的地方都要进行解锁，否则会导致其他线程阻塞卡死！
		
		pthread_mutex_unlock(&mutex);
		}
		 printf("all   ticket have  saled!!!");
         pthread_exit(NULL);

}


int main()
{

   //int pthread_mutex_init(pthread_mutex_t *restrict mutex,
   //              const pthread_mutexattr_t *restrict attr);
   
	pthread_mutex_init(&mutex,NULL);                                     //互斥锁的初始化

    pthread_t  tid[4];
	int i=4;
	while(--i != -1)
	{
	    int	ret=pthread_create(&tid[i],NULL,handler,(void*)i);
		if(ret<0)
		{
			perror("create error");
            exit (-1);
		}
		
		}
  
  
   pthread_join(tid[0],NULL);
   pthread_join(tid[1],NULL);
   pthread_join(tid[2],NULL);
   pthread_join(tid[3],NULL);
  
   pthread_mutex_destroy(&mutex);                                                                         //互斥锁的销毁
	
	return 0;
	}


