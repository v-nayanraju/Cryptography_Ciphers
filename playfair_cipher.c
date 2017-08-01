#include <stdio.h>
#include <string.h>
char key[11],pltxt[101],enc[101],arr[5][5];
int h[26]={0},h1[26][2] = {0,0,0,0};

void main(){
	int i=0,j=0,k,n_k,spaces=0;
	printf("Give a Key word(upto 10 chars only alphabets all smalls) : ");
	scanf("%s",key);
	n_k = strlen(key);


	//// entering letters of key word in key array
	for(k=0;k<n_k;k++){
		if(!h[key[k]-'a']){
			arr[i][j] = key[k];
			j++;
			if(j>=5){
				j=0;
				i++;
			}
			h[key[k]-'a']++;
			if(key[k]=='i' || key[k]=='j'){
				h['j'-'a'] = 1;
				h['i'-'a'] = 1;
			}
		}
	}


	//// entering remaining letters in key array
	for(k='a';k<='z';k++){
		if(!h[k-'a']){
			arr[i][j] = (char)k;
			j++;
			if(j>=5){
				j=0;
				i++;
			}
			h[k-'a']++;
			if((char)k == 'i' || (char)k=='j'){
				h['j'-'a'] = 1;
				h['i'-'a'] = 1;
			}
		}
	}
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			h1[arr[i][j]-'a'][0]=i;
			h1[arr[i][j]-'a'][1]=j;
			if(arr[i][j]=='i' || arr[i][j]=='j'){
				h1['i'-'a'][0]=i;
				h1['i'-'a'][1]=j;
				h1['j'-'a'][0]=i;
				h1['j'-'a'][1]=j;
			}
			printf("%c ",arr[i][j]);
		}
		printf("\n");
	}


	printf("Input the PlainText : \n");
	scanf(" %[^\n]s",pltxt);
	int space[100];
	for(i = 0; pltxt[i]!=(char)(10); i++){
		if(pltxt[i]==' '){
			space[spaces]=i;
			//printf("%d  ",i);
			spaces++;
		}
	  	pltxt[i] = tolower(pltxt[i]);
	}
	//printf("%s\n",pltxt);

	//// Encrypting the text
	printf("The Encrypted text is : \n");
	j=0;
	int r1,r2,c1,c2,R1,R2,C1,C2;
	char ch1,ch2;
	int n = strlen(pltxt);
	if(pltxt[n-1]==' ') n--;
	for(i=0;i<n;i+=2){
		if(pltxt[i]==' ') i++;
		ch1 = pltxt[i];
		r1 = h1[pltxt[i]-'a'][0]; c1 = h1[pltxt[i]-'a'][1];
		if(i+1>=strlen(pltxt)){
			printf("%c",arr[r1][c1] );
			break;
		}
		if(pltxt[i+1]==' ') i++;
		if(i+1>=strlen(pltxt)){
			printf("%c",arr[r1][c1] );
			break;
		}
		r2 = h1[pltxt[i+1]-'a'][0]; c2 = h1[pltxt[i+1]-'a'][1];
		if(r1==r2){
			R1 =r1; R2 = r2;
			C1 = (c1+1)%5; C2 = (c2+1)%5;
		}
		else if(c1==c2){
			C1 = c1; C2 = c2;
			R1 = (r1+1)%5; R2 = (r2+1)%5;
		}
		else{
			R1 = r2;C1 = c1;
			R2 = r1;C2 = c2;
		}
		enc[j] = arr[R1][C1];
		j++;
		enc[j] = arr[R2][C2];
		j++;
	}
	i=0;j=0;k=0;
	for(i=0;i<strlen(enc);i++){
		if(j==space[k]){
			printf(" ");
			k++; j++;
		}
		printf("%c",enc[i] );
		j++;
	}
}
