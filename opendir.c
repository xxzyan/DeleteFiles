#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
int delete_file(const char* path)
{

	char file_src[251];
	struct dirent* pde  = NULL;
	struct stat st;
	int cnt=0;

	DIR* dirp = opendir(path);
	if(dirp == 	NULL)
	{
		//perror("opendir");
		return;
	}

	getcwd(file_src,sizeof(file_src));//改变当前工作目录
	chdir(path);//改变当前工作目录

	while(pde = readdir(dirp))
	{
		printf("%s\n",pde->d_name);
		if(0 ==stat(pde->d_name,&st))
		{
			if(S_ISDIR(st.st_mode))	//判断是否为目录
			{
				//是一个目录
				//if(strcmp(pde->d_name, ".") != 0 && strcmp(pde->d_name, "..") != 0)
				if(strcmp(pde->d_name, ".")!=0 && strcmp(pde->d_name,"..")!=0)
				{
					cnt +=delete_file(pde->d_name);
				}
			}

			else
			{
				//是一个文件
				char* p = pde->d_name + strlen(pde->d_name)-5;
				if(strcasecmp(p+1,".mp4")==0||strcasecmp(p,".rmvb")==0||strcasecmp(p+1,".flv")==0 ||strcasecmp(p+1,".avi")==0 ||strcasecmp(p+1,".wmv")==0)
				{
					unlink(pde->d_name);
					++cnt;
				}

			}
		}	


	}
	chdir(file_src);
	closedir(dirp);
	return cnt;
}


int main()
{
	
	printf("%d部小视频已经消失\n", delete_file("/home/xxzy/code"));


	return 0;
}