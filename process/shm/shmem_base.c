
/*shmadd.c*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 2048

int main()
{
	int shmid;
	char *shmadd;

	key_t key;

	/*���ݲ�ͬ��·���͹ؼ���ʾ������׼��key*/
	if ((key = ftok(".", 'a')) == -1)
	{
		perror("ftok");
		exit(1);
	}
	
	/* ���������ڴ� */
	if ((shmid = shmget(key, BUFSZ, IPC_CREAT|0666)) < 0)
	{
		perror("shmget");
		exit(1);
	}
	else
	{
		printf("Create shared-memory: %d\n",shmid);
	}
	
	/* ��ʾ�����ڴ���� */
	system("ipcs -m");
	
	/*ӳ�乲���ڴ�*/
	if ((shmadd = shmat(shmid, 0, 0)) < (char *)0)
	{
		perror("shmat");
		exit(1);
	}
	else
	{
		printf("Attach shared-memory\n");
	}
	
	system("ipcs -m");
	
	/* ��������ڴ�ӳ�� */
	if ((shmdt(shmadd)) < 0)
	{
		perror("shmdt");
		exit(1);
	}
	else
	{
		printf("Deattach shared-memory\n");
	}
	
  	system("ipcs -m");
	
  	/* ɾ�������ڴ� */
  	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror("shmctl(IPC_RMID)\n");
		exit(1);
	}
	else
	{
		printf("Delete shared-memory\n");
	}
	
	system("ipcs -m");
  	exit(0);
}