#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//2580 �ϰ� 1100   2584 �°� 0011   258C ��� 1010   2590 �Ұ� 0101
//2596 ���� 0010   2597 ���� 0001   2598 ���� 1000   259D ���� 0100
//2599 ������ 1011   259B ������ 1110    259C ������ 1101    259F ������ 0111
//259A \  1001      259E / 0110
//2588 ȫ  1111    �ո� ��� 0000

//�ж������Լ�ת���ɶ�Ӧ������� 
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

int main(){
	FILE *fp;
	char ch[20];
	char *i;
	char content[7][5];
	static int contentNum[8] = {};
	static int ser[8][8] = {};
	char useless[20];
	char p[10] = "29938";
	int n;
	if((fp = fopen("guanzhi.txt","r")) == NULL){
		exit(1);
	}
	printf("Select Mode(1.one character):"); 
	scanf("%d",&n);//n = 1 ��unicode����
	if(n == 1){
		char inputContent[20];
		char refineContent[50] = "ENCODING ";
		scanf("%s", &inputContent);
		strcat(inputContent, "\n");
		strcat(refineContent, inputContent);
		strcpy(p, refineContent);
	}
	while(!feof(fp)){
		if(fgets(ch,sizeof(ch),fp) != NULL);/*���ж�ȡ�ļ��е��ַ����������ļ�*/
		{
			i = strstr(ch,p);/*�ж��Ƿ����������iָ����ַ�����һ�γ��ֵĵ�ַ*/
			 
			if(i){
				printf("Find character:%s\n",i);
				while(strcmp(useless,"BITMAP")){//BITMAPΪ������־ 
					fscanf(fp, "%s", &useless);
					printf("%s\n",useless);
				}
				for(int i = 0;i < 7;i++){
					fscanf(fp, "%s", &content[i]);
				}
				for(int i = 0;i < 7;i++){
					printf("%s\n", content[i]);
				}
			}
		}
	}
	fseek(fp, 0, SEEK_SET);
	//����ȡ����16�����ļ�תΪ2�����ļ� 
	char mid[100];
	for(int i = 0;i < 7;i++){
		int num1 = (int)content[i][0] > 64? (int)content[i][0] - 55:(int)content[i][0] - 48;
		int num2 = (int)content[i][1] > 64? (int)content[i][1] - 55:(int)content[i][1] - 48;
		printf("%d,%d\n",num1,num2);
		int num3 = num1 * 16 + num2;
		contentNum[i] = atoi(itoa(num3, mid, 2)) / 10;
		printf("%d\n",contentNum[i]);
		for(int j = 0;j < 7;j++){
			ser[i][6-j] = contentNum[i] % 10;
			contentNum[i] /= 10;
		}
	}
	//������� 
	printf("Number-Show:\n");
	for(int i = 0;i < 7;i++){
		for(int j = 0;j < 7;j++){
			printf("%d ",ser[i][j]);
		}
		printf("\n");
	}
	
	//���ݺ���������� 
	for(int i = 0;i < 8;i = i + 2){
		for(int j = 0;j < 8;j = j + 2){
			judg(ser[i][j],ser[i][j+1],ser[i+1][j],ser[i+1][j+1]);
		}
		printf(" +\n");
	}
	
	fclose(fp);
	return 0;
}
//�ο����ӣ�https://blog.csdn.net/onewayZzz/article/details/109106644
