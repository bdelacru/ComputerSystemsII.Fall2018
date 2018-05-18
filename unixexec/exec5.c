int main()
{
int ret = fork();

if(ret ==0) {
	printf("Child runs\n");
	execl("./xrunme","xrunme","dog",NULL);
	printf("Child done\n");
}
else {
	wait(NULL);
	printf("Parent done\n");
	}
}

