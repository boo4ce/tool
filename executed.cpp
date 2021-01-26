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
bool canKill(char pid[23]) {
	char pid1[23];
	strcpy(pid1, pid);
	
	FILE *filer = fopen("C://Tab_tool//abcd.txt", "r");
	char pid2[23];
	while(fscanf(filer,"%s", pid2) != EOF) {
		if(strcmp(pid1, pid2) == 0) {
			fclose(filer);
			return false;
		}
	}
	fclose(filer);
	return true;
}

int main() {	
	FILE *file;
	file = fopen("C://Tab_tool//abc.txt", "r");
	char buffer[255];
		
	if(file == NULL) {
		printf("Error");
	}
	else {
		fgets(buffer, 255, file);
		FILE *filew = fopen("C://Tab_tool//killing.bat", "w");
		
		fprintf(filew, "echo off\n");
		fprintf(filew, "taskkill /f /t");
		
		while(fgets(buffer, 255, file) != NULL) {
			if(canKill(getPID(buffer))) {
				fprintf(filew, " /pid ");
				fprintf(filew, getPID(buffer));
				printf(getPID(buffer));
			}
		}
		
		fprintf(filew, "\ncls\nexit");
		fclose(filew);		
	}
	
	fclose(file);
	
	system("C://Tab_tool//killing.bat");
	remove("C://Tab_tool//killing.bat");
	return 0;	
}
