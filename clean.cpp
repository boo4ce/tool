#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* getPID(char task[255]) {
	int i = 0, j = 0;
	char pid[23] = "";
	
	while(task[i] != ',') i++;
	i+=2;
	
	while(task[i] != '"') {
		pid[j++] = task[i++];
	}
	 
	return pid;
} 

int main() {	
	FILE *file;
	file = fopen("C://Tab_tool//cba.txt", "r");
	char buffer[255];
		
	if(file == NULL) {
		printf("Error");
	}
	else {
		fgets(buffer, 255, file);
		FILE *filew = fopen("C://Tab_tool//abcd.txt", "w");
		
		while(fgets(buffer, 255, file) != NULL) {
			fprintf(filew, getPID(buffer));
			fprintf(filew, " ");
		}
		fclose(filew);
		
	}
	
	fclose(file);
//	remove("cba.txt");
	
	return 0;	
}
