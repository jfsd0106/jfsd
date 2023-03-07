#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
int main()
{
	int map[8][8]={
		{1,1,1,1,1,1,1,1},
		{1,1,1,4,4,1,1,1},
		{1,1,1,0,4,1,1,1},
		{1,1,0,0,3,4,1,1},
		{1,1,0,3,0,0,1,1},
		{1,0,0,1,3,3,0,1},
		{1,0,0,2,0,0,0,1},
		{1,1,1,1,1,1,1,1}};
	int x=6,y=3,cnt=0;
	for(;;)
	{
		system("clear");
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				switch(map[i][j])
				{
					case 0:printf("  ");break;
					case 1:printf("# ");break;
					case 2:printf("@ ");break;
					case 3:printf("$ ");break;
					case 4:printf("O ");break;
					case 6:printf("@ ");break;
					case 7:printf("$ ");break;
				}
			}
			puts("");
		}
		if(map[1][3]==7 && map[1][4]==7 && map[2][4]==7 && map[3][5]==7)
		{
			printf("成功过关！共用%d步",cnt);
			break;
		}
		switch(getch())
		{
			case 183:
			if(map[x-1][y]==0 || map[x-1][y]==4)
			{
				map[x-1][y]+=2;
				map[x--][y]-=2;
			}
			else if((map[x-1][y]==3 || map[x-1][y]==7) && (map[x-2][y]==0 || map[x-2][y]==4))
			{
				map[x-1][y]-=1;
				map[x-2][y]+=3;
				map[x--][y]-=2;
			}
			cnt++;
			break;
			case 184:
			if(map[x+1][y]==0 || map[x+1][y]==4)
			{
				map[x+1][y]+=2;
				map[x++][y]-=2;
			}
			else if((map[x+1][y]==3 || map[x+1][y]==7) && (map[x+2][y]==0 || map[x+2][y]==4))
			{
				map[x+1][y]-=1;
				map[x+2][y]+=3;
				map[x++][y]-=2;
			}
			cnt++;
			break;
			case 186:
			if(map[x][y-1]==0 || map[x][y-1]==4)
			{
				map[x][y-1]+=2;
				map[x][y--]-=2;
			}
			else if((map[x][y-1]==3 || map[x][y-1]==7) && (map[x][y-2]==0 || map[x][y-2]==4))
			{
				map[x][y-1]-=1;
				map[x][y-2]+=3;
				map[x][y--]-=2;
			}
			cnt++;
			break;
			case 185:
			if(map[x][y+1]==0 || map[x][y+1]==4)
			{
				map[x][y+1]+=2;
				map[x][y++]-=2;
			}
			else if((map[x][y+1]==3 || map[x][y+1]==7) && (map[x][y+2]==0 || map[x][y+2]==4))
			{
				map[x][y+1]-=1;
				map[x][y+2]+=3;
				map[x][y++]-=2;
			}
			cnt++;
			break;
		}
	}
}

