#define MAXBUFF 80 //максимальная длина сообщения в разделяемой памяти 共享内存的最大信息长度
#define PERM 0666 //права доступа к разделяемой памяти 共享内存访问权

typedef struct mem	//структура данных в разделяемой памяти 共享内存的数据结构
{
	int segment;
	char buff[MAXBUFF];
}Message;

//ожидание начала выполнения клиента 等待客户端开始执行
static struct sembuf proc_wait[1] = {1, -1, 0};

//уведомление сервера о том, что клиент начал работу 通知服务器客户端已开始工作
static struct sembuf proc_start[1] = {1, 1, 0};

//блокирование разделяемой памяти 共享内存锁定
static struct sembuf mem_lock[2] = {0, 0, 0, 0, 1, 0};

//освобождение ресурса 释放资源
static struct sembuf mem_unlock[1] = {0, -1, 0};
