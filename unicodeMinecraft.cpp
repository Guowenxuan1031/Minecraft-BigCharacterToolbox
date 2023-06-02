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

int judg(int n[2][4],int m,FILE *fpc,FILE *fpa){
	char shape[16][10] = {"\u2580","\u2584","\u258C "," \u2590","\u2596 "," \u2597","\u2598 "," \u259D","\u2599","\u259B","\u259C","\u259F","\u259A","\u259E","\u2588","   "};
	int shapeNum[16] = {1100,11,1010,101,10,1,1000,100,1011,1110,1101,111,1001,110,1111,0};
	int num = n[0][0] * 1000 + n[0][1] * 100 + n[0][2] * 10 + n[0][3];
	int num1 = n[1][0] * 1000 + n[1][1] * 100 + n[1][2] * 10 + n[1][3];
	for(int i = 0;i < 16;i++){
		if(num == shapeNum[i] && (m == 1 || m == 2)){
			printf("%s",shape[i]);
			fprintf(fpc, "%s",shape[i]);
			fprintf(fpa, "%s",shape[i]);
		}
		if(m == 3){
			if(num1 == shapeNum[i]){
				printf("%s",shape[i]);
				fprintf(fpc, "%s",shape[i]);
				fprintf(fpa, "%s",shape[i]);
			}
		}
	}
	return 0;
}

int main(){
	system("chcp 65001");
	FILE *fp;//character
	FILE *fpc;//command
	FILE *fpa;//alternative
	int uniInt[1000] = {};
	int choose = 1;//one or two in sign
	int choose1 = 1;//direction
	bool judgeText = 1;
	int chaNum = 1;//block num in a line
	static int ser[8][8] = {0};
	static int ser1[8][8] = {0};
	char ch[20];
	char content[7][5] = {};
	static int contentNum[8] = {0};
	char useless[20];
	char p[20] = "29938";
	int multiNum = 0,highNum = 0;
	int ynum = -1;
	int xnum = 0;
	int znum = 0;
	
	if((fp = fopen("guanzhi.txt","r")) == NULL){
		exit(1);
	}
	while(1){
		strcpy(ch, "");
		memset(content, 0, sizeof content);
		memset(contentNum, 0, sizeof contentNum);
		memset(useless, 0, sizeof useless);
		if(!multiNum){
			printf("\n\n0.quit   1.one in sign   2.two in sign:");
			scanf("%d",&choose);
			if(choose == 0) exit(0);
			printf("1.x   2.z    3.-x   4.-z(if not alternative input 1):");
			scanf("%d",&choose1);
			printf("a board in a line(if not alternative input 10):");
			scanf("%d",&chaNum);
			system("unicodeChange.exe");
			printf("copy the upper things:\n");
			scanf("%d",&multiNum);
			highNum = multiNum;
			for(int i = 0;i < multiNum;i++){
				int j;
				scanf("%x",&j);
				uniInt[i] = j;
			}
			fpc = fopen("command.txt","w");
			fclose(fpc);
			fpa = fopen("alternative.txt","w");
			fclose(fpa);
			ynum = -1;xnum = 0;znum = 0;
		}//输入choose,choose1,写入uniint 
		
		if(multiNum != 0){
			char inputContent[20] = {};
			char refineContent[50] = "ENCODING ";
			itoa(uniInt[highNum - multiNum], inputContent, 10);
			strcat(inputContent, "\n");
			strcat(refineContent, inputContent);
			strcpy(p, refineContent);
			multiNum--;//从uniint中读取并转为搜索文件 
		}else{
			memset(uniInt, 0, sizeof uniInt);
		}
		
		while(!feof(fp)){
			if(fgets(ch,sizeof(ch),fp) != NULL);/*按行读取文件中的字符，遍历整文件*/
			{
				char *in = strstr(ch,p);/*判断是否包含，包含i指向该字符串第一次出现的地址*/
				if(in){
					printf("Find character:%s\n",in);
					while(strcmp(useless,"BITMAP")){//BITMAP为结束标志 
						fscanf(fp, "%s", &useless);
						printf("%s\n", useless);
					}
					for(int i = 0;i < 7;i++){
						fscanf(fp, "%s", &content[i]);
						if(!strcmp(content[i],"ENDCHAR")){
							printf("YES!!");
							for(int j = i;j < 7;j++){
								memset(content[j], 0, sizeof content[j]);
								content[j][0] = '3';
							}
							break;
						}//搜索文件，写入content 
					}
					fseek(fp, 0, SEEK_SET);
					break;
				}
			}
		}
		
		//将content获取到的16进制文件转为2进制文件 
		char mid[100];
		for(int i = 0;i < 7;i++){
			int num1 = (int)content[i][0] > 64? (int)content[i][0] - 55:(int)content[i][0] - 48;
			int num2 = (int)content[i][1] > 64? (int)content[i][1] - 55:(int)content[i][1] - 48;
			int num3 = num1 * 16 + num2;
			contentNum[i] = atoi(itoa(num3, mid, 2)) / 10;
			for(int j = 0;j < 7;j++){
				if(judgeText) ser[i][6-j] = contentNum[i] % 10;
				else ser1[i][6-j] = contentNum[i] % 10;
				contentNum[i] /= 10;
			}
		}
		
		//输出数字 
		printf("Number-Show:\n");
		for(int i = 0;i < 7;i++){
			for(int j = 0;j < 7;j++){
				printf("%d ",ser[i][j]);
			}
			printf("\n");
		}
		
		//输出代码等 
		if(choose == 1 || (choose == 2 && !judgeText)){
			fpc = fopen("command.txt","a+");
			fpa = fopen("alternative.txt","a+");
			
			printf("/give @p minecraft:oak_sign{BlockEntityTag:{GlowingText:1b,Color:\"white\",");
			fprintf(fpc, "/give @p minecraft:oak_sign{BlockEntityTag:{GlowingText:1b,Color:\"white\",");
			fprintf(fpa, "/data merge block ~%d ~%d ~%d {",xnum,ynum,znum);
			int serNum[2][4];
			for(int i = 0;i < 8;i = i + 2){
				printf("Text%d:'{\"text\":\"",(i + 2) / 2);
				fprintf(fpc, "Text%d:'{\"text\":\"",(i + 2) / 2);
				fprintf(fpa, "Text%d:'{\"text\":\"",(i + 2) / 2);
				for(int j = 0;j < 8;j = j + 2){
					for(int k = 0;k < 4;k++){
						serNum[0][k] = ser[i+(k>1?1:0)][j+k%2];
						serNum[1][k] = ser1[i+(k>1?1:0)][j+k%2];
					}
	//				serNum[0][(i%4)*2+j] = ser[i][j];
	//				serNum[1][(i%4)*2+j] = ser1[i][j];
					if(choose == 1) judg(serNum,1,fpc,fpa);
					if(choose == 2) judg(serNum,2,fpc,fpa);
				}
				for(int j = 0;j < 8;j = j + 2){
					for(int k = 0;k < 4;k++){
						serNum[0][k] = ser[i+(k>1?1:0)][j+k%2];
						serNum[1][k] = ser1[i+(k>1?1:0)][j+k%2];
					}
	//				serNum[0][(i%4)*2+j] = ser[i][j];
	//				serNum[1][(i%4)*2+j] = ser1[i][j];
					if(choose == 2) judg(serNum,3,fpc,fpa);
				}
				if(i < 6){
					printf("\"}',");
					fprintf(fpc, "\"}',");
					fprintf(fpa, "\"}',");
				}
			}
			printf("\"}'},display:{Name:'{\"text\":\"Custom Sign%d\"}'}}\n",highNum - multiNum);
			fprintf(fpc, "\"}'},display:{Name:'{\"text\":\"Custom Sign%d\"}'}}\n",highNum - multiNum);
			fprintf(fpa, "\"}'}\n");
			fclose(fpc);
			fclose(fpa);
			memset(ser, 0, sizeof ser);
			memset(ser1, 0 ,sizeof ser1);
			if(choose1 == 1) xnum + 1 < chaNum?xnum++:(xnum = 0,ynum--);
			else if(choose1 == 2) znum + 1 < chaNum?znum++:(znum = 0,ynum--);
			else if(choose1 == 3) xnum - 1 > (-chaNum)?xnum--:(xnum = 0,ynum--);
			else if(choose1 == 4) znum - 1 > (-chaNum)?znum--:(znum = 0,ynum--);
		}
		
		if(choose == 2) judgeText = !judgeText;

	}
	return 0;
}
