#include <stdio.h>
#include <string.h>

void main()
{
	char a[20],b[20],c[20],o1[20],o2[20];
	int op1,op2,lc,sa,flag1,flag2;
	FILE *input,*output,*optab,*symtab;
	symtab=fopen("symtab.txt","w");
	fclose(symtab);
	input=fopen("sourcepgm.txt","r");
	output=fopen("intermediate.txt","w");
	printf("SOURCE PROGRAM\nLABEL\tOPCODE\tOPERAND\n");
	fscanf(input,"%s%s%x",a,b,&op1);
	if (strcmp(b,"START")==0)
	{
		printf("%s\t%s\t%x\n",a,b,op1);
		lc=op1;
		sa=op1;
		fprintf(output,"%x\t%s\t%s\t%x",lc,a,b,op1);
	}
	else
	{
		lc=0x0;
	}
	fscanf(input,"%s%s%s",a,b,c);	
	while (!feof(input))
	{
		if (strcmp(b,"END")!=0)
		{
			fprintf(output,"\n%x\t%s\t%s\t%s",lc,a,b,c);
			printf("%s\t%s\t%s\n",a,b,c);
			flag1=0;
			symtab=fopen("symtab.txt","a+");
			fscanf(symtab,"%s%s",o1,o2);
			while (!feof(symtab))
			{
				if (strcmp(o1,a)==0 || a[0]=='-')
				{
					flag1=1;
					break;
				}
				fscanf(symtab,"%s%s",o1,o2);
			}
			if (flag1==0 && a[0]!='-')
			{
				fprintf(symtab,"%s\t%x\n",a,lc);
			}
			else if (a[0]!='-')
				printf("\nDUPLICATE SYMBOL!!\n");
			fclose(symtab);
			flag2=0;
			optab=fopen("optab.txt","r");
			fscanf(optab,"%s%s",o1,o2);
			while (!feof(optab))
			{
				if (strcmp(o1,b)==0)
				{
					lc+=3;
					flag2=1;
					break;
				}
				fscanf(optab,"%s%s",o1,o2);
			}
			fclose(optab);
			if (strcmp(b,"RESW")==0)
			{
				op2=atoi(c);
				lc+=3*op2;
			}
			else if (strcmp(b,"RESB")==0)
			{
				op2=atoi(c);
				lc+=op2;
			}
			else if (strcmp(b,"WORD")==0)
			{
				lc+=3;
			}
			else if (flag2==0)
			{
				printf("INVALID OPERATION CODE");
			}	
			fscanf(input,"%s%s%s",a,b,c);	
		}
		else
		{
			fprintf(output,"\n%x\t%s\t%s\t%s",lc,a,b,c);
			printf("%s\t%s\t%s\n",a,b,c);
			break;
		}
	}
	fclose(input);
	fclose(output);
}
		
