#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct clientData
{
	int acctnum;
	char lastname[15];
	char firstname[10];
	double balance;
};

int main(void)
{ 
	FILE *pRead, *pWrite;
	FILE *cfPtr;
	int cnt = 0;
	struct clientData client = { 0,"","" ,0.0 };

	pRead = fopen("D://credit.txt", "r");
	if (pRead == NULL)
		return 0;
	pWrite = fopen("D://credit_bin.txt", "wb");
	if (pWrite == NULL)
	{
		fclose(pRead);
		return 0;
	}

	while (!feof(pRead))
	{
		fscanf(pRead, "%d%s%s%lf", &client.acctnum, client.lastname, client.firstname, &client.balance);
		fwrite(&client, sizeof(struct clientData), 1, pWrite);
		printf("%-6d%-16s%-11s%10.2f\n", client.acctnum,client.lastname,client.firstname,client.balance);
	}

	fclose(pRead);
	fclose(pWrite);
	printf("以讀取文字檔的ASCII資料，並轉成二進位檔案\n\n");
	system("pause");
	printf("\n讀取二進位資料檔案，並格式化輸出如下 : \n");

	if ((cfPtr = fopen("D://credit_bin.txt", "rb")) == NULL)
		printf("File could not be opened.\n");
	else
	{
		printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

		cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);

		while(cnt>0)
		{
			printf("%-6d%-16s%-11s%10.2f\n", client.acctnum, client.lastname, client.firstname, client.balance);
			cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);
		}
		fclose(cfPtr);
	}

	system("pause");
	return 0;
}