#include <stdio.h>
int main()
{
	int i,j,x,y,count=0;
	char flag=' ';
	char a[15][15];
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			a[i][j]='*';
		}
	}
	for(;;)
	{
		system("clear");
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				printf("%c ",a[i][j]);
			}
			printf("\n");
		}
		if(flag=='@')
		{
			printf("黑方胜利！\n");
			break;
		}
		if(flag=='$')
		{
			printf("白方胜利！\n");
			break;
		}
		if(count%2==0)
		{
			printf("黑方落子\n");
			scanf("%d %d",&x,&y);
			for(;;)
			{
				if(x>15||y>15)
				{
					printf("落子越界，请重新落子\n");
					scanf("%d %d",&x,&y);
				}
				else if(a[x-1][y-1]!='*')
				{
					printf("该处已有棋子，请重新落子\n");
					scanf("%d %d",&x,&y);
				}
				else
				{
					a[x-1][y-1]='@';
					count++;
					break;
				}
			}
		}
		else
		{
			printf("白方落子\n");
			scanf("%d %d",&x,&y);
			for(;;)
			{
				if(x>15||y>15)
				{
					printf("落子越界，请重新落子\n");
					scanf("%d %d",&x,&y);
				}
				else if(a[x-1][y-1]!='*')
				{
					printf("该处已有棋子，请重新落子\n");
					scanf("%d %d",&x,&y);
				}
				else
				{
					a[x-1][y-1]='$';
					count++;
					break;
				}
			}
		}
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(a[i][j]==a[i][j+1] && a[i][j+1]==a[i][j+2] && 
				   a[i][j+2]==a[i][j+3] && a[i][j+3]==a[i][j+4]
				   && a[i][j]!='*')
				{
					flag=a[i][j];
				}
			}
		}
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(a[i][j]==a[i+1][j] && a[i+1][j]==a[i+2][j] && 
				   a[i+2][j]==a[i+3][j] && a[i+3][j]==a[i+4][j]
				   && a[i][j]!='*')
				{
					flag=a[i][j];
				}
			}
		}
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(a[i][j]==a[i+1][j+1] && a[i+1][j+1]==a[i+2][j+2] && 
				   a[i+2][j+2]==a[i+3][j+3] && a[i+3][j+3]==a[i+4][j+4]
				   && a[i][j]!='*')
				{
					flag=a[i][j];
				}
			}
		}
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(a[i][j]==a[i+1][j-1] && a[i+1][j-1]==a[i+2][j-2] && 
				   a[i+2][j-2]==a[i+3][j-3] && a[i+3][j-3]==a[i+4][j-4]
				   && a[i][j]!='*')
				{
					flag=a[i][j];
				}
			}
		}
	}
}
