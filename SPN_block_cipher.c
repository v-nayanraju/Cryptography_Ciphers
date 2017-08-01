#include <stdio.h>
#include <string.h>

void toBinary(int binary[], int *index, unsigned n)
{
    if (n > 1)
    	toBinary(binary, index, n/2);
    binary[*index]=n % 2;
    (*index)++;
}

int toAscii(int binary[], int i){
	int j,sum=0,mult=1;
	for(j=i+7;j>=i;j--){
		sum+=(binary[j]*mult);
		mult*=2;
	}
	return sum;
}

void Substitute1(int binary[], int block, int ind)
{
	int  temp;
	ind=block*16+ind;
	temp=binary[ind+3];
	binary[ind+3]=binary[ind+2];
	binary[ind+2]=binary[ind+1];
	binary[ind+1]=binary[ind];
	binary[ind]=temp;
}

void Substitute2(int binary[], int block, int ind)
{
	int temp;
	ind=block*16+ind;
	temp=binary[ind+3];
	binary[ind+3]=binary[ind];
	binary[ind]=binary[ind+1];
	binary[ind+1]=binary[ind+2];
	binary[ind+2]=temp;
}

void permute(int binary[], int length)
{
	int temp, i;
	temp=binary[length-1];
	for (i=length-1; i>0; i--)
		binary[i]=binary[i-1];
	binary[0]=temp;
}

int main()
{
	char pltxt[500];
	int binary[100000], index, i, blocks, rem, key[32]={0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1,0,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1}, rkey[16];
	index=0;
	printf("Input the PlainText : \n");
	scanf("%[^\n]s", pltxt);
	for (i=0; i<strlen(pltxt); i++)
	{
		binary[index]=0;
		index++;
		toBinary(binary, &index, pltxt[i]);
	}

	printf("\nPlain text in bit form :\n");
	for (i=0; i<index; i++)
		printf("%d", binary[i]);

	int round;
	for(round=1;round<=5;round++){


		printf("\n\nROUND - %d\nGenerating round Key from Given key for round %d : \n",round,round);
		for (i=0; i<16; i++){
			rkey[i]=key[i+(round-1)*4];
			printf("%d", rkey[i]);
		}


		printf("\nRound %d - XOR between input and round key : \n",round);
		for (i=0; i<index; i++)
		{
		    binary[i]= (binary[i]^rkey[i%16]);
		}
		for (i=0; i<index; i++)
			printf("%d", binary[i]);
		blocks=index/16;
		rem=index%16;


		printf("\nRound %d - Substitutiong...\n",round);
		for (i=0; i<blocks; i++)
		{
			Substitute1(binary, i, 0);
			Substitute2(binary, i, 4);
			Substitute1(binary, i, 8);
			Substitute2(binary, i, 12);
		}
		for (i=0; i<rem; i++)
		{
			if (i%2==0)
				Substitute1(binary, blocks, i*4);
			else
				Substitute2(binary, blocks, i*4);
		}
		for (i=0; i<index; i++)
			printf("%d", binary[i]);


		printf("\nRound %d - Permuting ...\n",round);
		permute(binary, index);
		for (i=0; i<index; i++)
			printf("%d", binary[i]);


		printf("\nRound %d - Binary Cipher String is : \n",round);
		for (i=0; i<index; i++)
			printf("%d", binary[i]);
	    printf("\n");


	    printf("Round %d - Cipher String : \n",round);
		for(i=0;i<index; i+=8){
			printf("%c",(char)(toAscii(binary,i)));
		}
		printf("\n\n");
	}
}
