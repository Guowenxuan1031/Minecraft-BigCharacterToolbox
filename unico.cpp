#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//2580 上半 1100   2584 下半 0011   258C 左半 1010   2590 右半 0101
//2596 左下 0010   2597 右下 0001   2598 左上 1000   259D 右上 0100
//2599 除右上 1011   259B 除右下 1110    259C 除左下 1101    259F 除左上 0111
//259A \  1001      259E / 0110
//2588 全  1111    空格 半格 0000

//判断内容以及转换成对应符号输出 
int judg(int n11,int n12,int n21,int n22){
	char shape[16][10] = {"\u2580","\u2584","\u258C "," \u2590","\u2596 "," \u2597","\u2598 "," \u259D","\u2599","\u259B","\u259C","\u259F","\u259A","\u259E","\u2588","  "};
	int shapeNum[16] = {1100,11,1010,101,10,1,1000,100,1011,1110,1101,111,1001,110,1111,0};
	int num = n11 * 1000 + n12 * 100 + n21 * 10 + n22;
	for(int i = 0;i < 16;i++){
		if(num == shapeNum[i]){
			printf("%s",shape[i]);
			return 0;
		}
	}
}

int judg(int n11,int n12,int n21,int n22,int m){
	char shape[16][10] = {"\\\\u2580","\\\\u2584","\\\\u258C "," \\\\u2590","\\\\u2596 "," \\\\u2597","\\\\u2598 "," \\\\u259D","\\\\u2599","\\\\u259B","\\\\u259C","\\\\u259F","\\\\u259A","\\\\u259E","\\\\u2588","  "};
	int shapeNum[16] = {1100,11,1010,101,10,1,1000,100,1011,1110,1101,111,1001,110,1111,0};
	int num = n11 * 1000 + n12 * 100 + n21 * 10 + n22;
	for(int i = 0;i < 16;i++){
		if(num == shapeNum[i]){
			printf("%s",shape[i]);
			return 0;
		}
	}
}



int main(){
	system("chcp 65001");
	FILE *fp;
	char ch[20];
	
	char content[7][5] = {};
	static int contentNum[8] = {0};
	static int ser[8][8] = {0};
	char useless[20];
	char p[20] = "29938";
	
	int uniInt[1000] = {};
	int n = 1;
	int multiNum = 0;
	int highNum = 0;
	if((fp = fopen("guanzhi.txt","r")) == NULL){
		exit(1);
	}
	while(1){
		fseek(fp, 0, SEEK_SET);
		strcpy(ch, "");
		memset(content, 0, sizeof content);
		memset(contentNum, 0, sizeof contentNum);
		memset(ser, 0, sizeof ser);
		memset(useless, 0, sizeof useless);
//		for(int i = 0;i < 8;i++){for(int j = 0;j < 8;j++){printf("%d",ser[i][j]);}} 
		
		if(n == 1){
			printf("\n\n(1.one number)\n");
			printf("(2.number + unicoudes)\n");
			printf("(3.characters-do not more than 1000 characters)\n");
			printf("(4.generate command)\n");
			printf("(0.quit)\n");
			printf("Select Mode:");
			scanf("%d",&n);//n = 1 单unicode输入
		}
		if(n == 1){
			char inputContent[20] = {};
			char refineContent[50] = "ENCODING ";
			printf("input number:");
			scanf("%s", &inputContent);
			strcat(inputContent, "\n");
			strcat(refineContent, inputContent);
			strcpy(p, refineContent);
		}else if(n == 0){
			exit(1);
		}else if(n == 2 || n == 3 || n == 4){
			if(multiNum == 0){
				if(n == 3 || n == 4) system("unicodeChange.exe");
				printf("input number plus unicodes:");
				scanf("%d",&multiNum);
				highNum = multiNum;
				for(int i = 0;i < multiNum;i++){
					int j;
					scanf("%x",&j);
					printf("%d\n",j);
					uniInt[i] = j;
				}
			}
			if(multiNum != 0){
				if(multiNum > 0){
					char inputContent[20] = {};
					char refineContent[50] = "ENCODING ";
					itoa(uniInt[highNum - multiNum], inputContent, 10);
					strcat(inputContent, "\n");
					strcat(refineContent, inputContent);
					strcpy(p, refineContent);
					multiNum--;
				}
				if(multiNum == 0){
					n = 1;
					memset(uniInt, 0, sizeof uniInt);
				}
			}
		}
		while(!feof(fp)){
			if(fgets(ch,sizeof(ch),fp) != NULL);/*按行读取文件中的字符，遍历整文件*/
			{
				char *in = strstr(ch,p);/*判断是否包含，包含i指向该字符串第一次出现的地址*/
				if(!in){
					in = strstr(ch,"65311");
				}
				if(in){
					printf("Find character:%s\n",in);
					while(strcmp(useless,"BITMAP")){//BITMAP为结束标志 
						fscanf(fp, "%s", &useless);
//						printf("--%s\n",useless);
					}
					for(int i = 0;i < 7;i++){
						fscanf(fp, "%s", &content[i]);
//						printf("%s\n",content[i]);
						if(!strcmp(content[i],"ENDCHAR")){
							char blank[5] = {0};
							strcpy(content[i],blank);
//							printf("%s",content[i]);
							break;
						}
					}
					fseek(fp, 0, SEEK_SET);
					break;
				}
			}
		}
		
		//将获取到的16进制文件转为2进制文件 
		char mid[100];
		for(int i = 0;i < 7;i++){
			int num1 = (int)content[i][0] > 64? (int)content[i][0] - 55:(int)content[i][0] - 48;
			int num2 = (int)content[i][1] > 64? (int)content[i][1] - 55:(int)content[i][1] - 48;
			int num3 = num1 * 16 + num2;
			contentNum[i] = atoi(itoa(num3, mid, 2)) / 10;
			for(int j = 0;j < 7;j++){
				ser[i][6-j] = contentNum[i] % 10;
				contentNum[i] /= 10;
			}
		}
		
		//输出数字 
//		printf("Number-Show:\n");
//		for(int i = 0;i < 7;i++){
//			for(int j = 0;j < 7;j++){
//				printf("%d ",ser[i][j]);
//			}
//			printf("\n");
//		}
		
		//根据函数输出符号 
		if(n != 4){
			for(int i = 0;i < 8;i = i + 2){
				for(int j = 0;j < 8;j = j + 2){
					judg(ser[i][j],ser[i][j+1],ser[i+1][j],ser[i+1][j+1]);
				}
				printf(" +\n");
			}
		}else if(n == 4){
			printf("/give @p minecraft:oak_sign{BlockEntityTag:{");
			for(int i = 0;i < 8;i = i + 2){
				printf("Text");
				printf("%d",(i + 2) / 2);
				printf(":'{\"text\":\"");
				for(int j = 0;j < 8;j = j + 2){
					judg(ser[i][j],ser[i][j+1],ser[i+1][j],ser[i+1][j+1],1);
				}
				if(i < 6) printf("\"}',");
			}
			printf("\"}'},display:{Name:'{\"text\":\"Custom Sign");
			printf("%d",highNum - multiNum);
			printf("\"}'}}\n");
		}
	}
	fclose(fp);
	return 0;
}
//参考链接：https://blog.csdn.net/onewayZzz/article/details/109106644
