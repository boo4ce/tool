#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<windows.h>

using namespace std;
string cmd_getTask = "";
string cmd_closeTask = "";
string uninstall = "";
string start_path = "C:\\ProgramData\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup";
string run_path = "%systemroot%";
string current_path = "";

void getExePath() 
{
	char buffer[MAX_PATH];
	GetModuleFileName( NULL, buffer, MAX_PATH );
	string f = string(buffer);
	current_path = f.substr(0, string(buffer).find_last_of( "\\/" ));
}

void setupCMD() {
	cmd_getTask += "echo off \ncls\nTASKLIST /fi \"session ne 0\" /fo csv > C:\\Tab_tool\\cba.txt\n";
	cmd_getTask += "echo Waiting...!!\nSTART /wait C:\\Tab_tool\\clean.exe\nBREAK\n";
	cmd_getTask += "cls\necho Done!!\nTIMEOUT /T 1\nexit";
	
	//----
	cmd_closeTask += "echo off\ncls\n";
	cmd_closeTask += "if _%2_==__ (\n";
	cmd_closeTask += "if _%1_==_-a_ TASKLIST /fi \"session ne 0\" /fo csv > C:\\Tab_tool\\abc.txt & goto :execute\n";
	cmd_closeTask += "if _%1_==_-r_ TASKLIST /fi \"session ne 0\" /fi \"status eq running\" /fo csv > C:\\Tab_tool\\abc.txt & goto :execute\n";
	cmd_closeTask += "if _%1_==_-nr_ TASKLIST /fi \"session ne 0\" /fi \"status eq not responding\" /fo csv > C:\\Tab_tool\\abc.txt & goto :execute\n";
	cmd_closeTask += "if _%1_==_-s_ TASKLIST /fi \"session ne 0\" /fi \"status eq suspended\" /fo csv > C:\\Tab_tool\\abc.txt & goto :execute\n";
	cmd_closeTask += "if _%1_==_/?_ (\n";
	cmd_closeTask += "   echo ct [-flag]\n";
	cmd_closeTask += "   echo     -a   close all tab\n";
	cmd_closeTask += "   echo     -r   close all running tab\n";
	cmd_closeTask += "   echo     -nr  close all not responding tab\n";
	cmd_closeTask += "   echo     -s   close all suspended tab\n";
	cmd_closeTask += "   echo     Ex: ct -a\n";
	cmd_closeTask += "   goto :helpp\n))\n";
	cmd_closeTask += "echo ct /? to help\n";
	cmd_closeTask += "goto :help\n";
	cmd_closeTask += ":execute\n";
	cmd_closeTask += "echo Waiting..!!\nSTART /wait C:\\Tab_tool\\executed.exe\ncls \necho Done..!!\nTIMEOUT /T 3\n";
	cmd_closeTask += ":helpp\ntitle C:\\WINDOWS\\system32\\CMD.exe\n";	

	//----
	uninstall += "@echo off\n";
	uninstall += "if _%1_==_payload_  goto :payload\n";
	uninstall += ":getadmin\n";
//	uninstall += "echo %~nx0: elevating self\n";
	uninstall += "set vbs=%temp%\getadmin.vbs\n";
	uninstall += "echo Set UAC = CreateObject^(\"Shell.Application\"^) >> \"%vbs%\"\n";
	uninstall += "echo UAC.ShellExecute \"%~s0\", \"payload %~sdp0 %*\", \"\", \"runas\", 1 >> \"%vbs%\"\n";
	uninstall += "\"%temp%\getadmin.vbs\"\n";
	uninstall += "del \"%temp%\getadmin.vbs\"\n";
	uninstall += "goto :eof\n";
	uninstall += ":payload\n";
	
	uninstall += "rd /s /q C:\\Tab_tool\n";
	uninstall += "del " + start_path + "\\defaultTask.bat\n";
	uninstall += "del " + run_path + "\\ct.bat\n";
	uninstall += "timeout /t 2\n";
	uninstall += "del " + run_path + "\\uninstall_ct.bat\n";
}
void setupUni() {
	ofstream of;
	of.open(".\\uninstall_ct.bat", ios::out);
	of << uninstall;
	of.close();	
}

void setupStartup() {
	ofstream of;
	of.open(".\\defaultTask.bat", ios::out);
	of << cmd_getTask;
	of.close();	
}

void setupFileBat() {
	ofstream of;
	of.open(".\\ct.bat", ios::out);
	of << cmd_closeTask;
	of.close();
}

void createNeededFile() {
	FILE *file;
	file = fopen("C:\\Tab_tool\\abc.txt", "w");
	file = fopen("C:\\Tab_tool\\abcd.txt", "w");
	file = fopen("C:\\Tab_tool\\cba.txt", "w");
	fclose(file);
	
	return;
}

void createFolder() {
	
	system("if not exist C:\\Tab_tool mkdir C:\\Tab_tool");
	system("attrib +h C:\\Tab_tool");	
	return;
}

void moveExe() {
	system("copy .\\clean.exe C:\\Tab_tool");	
	system("copy .\\executed.exe C:\\Tab_tool");
}

void run_CMD_as_Admin(string cmd_request) {
	string cmd = "@echo off\n";
	cmd += "if _%1_==_payload_  goto :payload\n";
	cmd += ":getadmin\n";
//	cmd += "echo %~nx0: elevating self\n";
	cmd += "set vbs=%temp%\getadmin.vbs\n";
	cmd += "echo Set UAC = CreateObject^(\"Shell.Application\"^) >> \"%vbs%\"\n";
	cmd += "echo UAC.ShellExecute \"%~s0\", \"payload %~sdp0 %*\", \"\", \"runas\", 1 >> \"%vbs%\"\n";
	cmd += "\"%temp%\getadmin.vbs\"\n";
	cmd += "del \"%temp%\getadmin.vbs\"\n";
	cmd += "goto :eof\n";
	cmd += ":payload\n";

	cmd += cmd_request;

	ofstream of;
	of.open(".\\ueafjksgnasff.bat", ios::out);
	of << cmd;
	of.close();
	
	system(".\\ueafjksgnasff.bat");
//	remove(".\\ueafjksgnasff.bat");
	
	return;
}

void setupBat() {
	string cmd_request = "";
	cmd_request += "move " + current_path + "\\defaultTask.bat " + start_path + "\n";
	cmd_request += "move " + current_path + "\\ct.bat " + run_path + "\n";
	cmd_request += "move " + current_path + "\\uninstall_ct.bat " + run_path + "\n";
	
	run_CMD_as_Admin(cmd_request);
}

int main() {
	system("echo off");
		
	getExePath();
	createFolder();
	
	moveExe();
	setupCMD();
	setupFileBat();
	setupStartup();
	setupUni();
	
	createNeededFile();
	
	Sleep(2000);	
	system(".\\defaultTask.bat");
	
	setupBat();
	
	system("echo \"Waiting for done\"");
	system("Timeout /t 2");
	system("exit");
	
	Sleep(2000);
	
	remove(".\\ueafjksgnasff.bat");
	remove(".\\ct.bat");
	remove(".\\defaultTask.bat");
	
	return 0;
}
