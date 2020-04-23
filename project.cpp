#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <windows.h>
#include "TextTable.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

bool login();
string print(string txt);
string printl(string txt);
void cls();
void centerTxt(string txt);
void centerTxtInput(string txt, int inputLength);
void drawLine();
void createFile(vector<string> profile, vector<string> sched);
void createFileList();
string mainMenu();
string searchMenu();
bool search();
string logout();
vector<string> readFileLineByLine(string filename);
bool loginInfo(string unpw);
int totalRows(string filename);
vector<string> seglist(string txt, char a);
void addData(string fileName, string data);
TextTable showCourseTable();
TextTable showRoomTable();
TextTable showProgramTable();
TextTable showTimeTable();
TextTable showDayTable();
TextTable showYearLevelTable();

string ToString(int i);
vector <string> dates = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
vector <string> yearLvl = {"1st Year", "2nd Year", "3rd Year", "4th Year", "5th Year"};
bool showStudentData(string a, string file1);
int consoleWidth = 0;

int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string getpass(const char *prompt, bool show_asterisk=true)
{
  const char BACKSPACE=127;
  const char RETURN=10;

  string password;
  unsigned char ch=0;

  cout <<prompt;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}


void createFile(vector<string> profile, vector<string> sched){
	ofstream myfile;
	myfile.open("Sched.html");
	myfile << "<!DOCTYPE html> <html> <head>   <title>CICS Schedule</title>   <style type=\"text/css\">   body{     font-family: \"Calibri Light\";   }   .space{     padding: 5px;   }     table{       border-collapse: collapse;       border-style: none;     }      .header{       text-align: center;     }   </style> </head> <body>   <center>     <table class=\"header\">       <tr>         <td rowspan=\"5\" class=\"space\"><img src=\"bsu.png\" width=\"100px\" height=\"100px\"></td>         <td >Republic of the Philippines</td>         <td rowspan=\"5\" class=\"space\"><img src=\"cics.jpg\" width=\"100px\" height=\"100px\"></td>       </tr>       <tr>         <td><B>BATANGAS STATE UNIVERSITY</B></td>       </tr>       <tr>         <td>College Of Informatics and Computing Sciences</td>       </tr>       <tr>         <td>Batangas City</td>       </tr>       <tr>         <td>AY 2018-2019, FIRST SEMESTER</td>       </tr>     </table>   </center>   <br>   <center><table border=1 width=\"80%\">     <tr>       <td class=\"space\" align=\"right\" style=\"padding-right: 10px\">Name:</td>       <td class=\"space\"><b>";
	myfile << profile[1] <<"</b></td>       <td class=\"space\" align=\"right\" style=\"padding-right: 10px\">SR Code: </td>       <td class=\"space\"><b>";
	myfile << profile[0]<<"</b></td>     </tr>     <tr>       <td class=\"space\" align=\"right\" style=\"padding-right: 10px\">Program: </td>       <td class=\"space\" ><b>";
	myfile << profile[2]<<"</b></td>       <td  class=\"space\" align=\"right\" style=\"padding-right: 10px\">Year Level: </td>       <td class=\"space\" ><b>";
	myfile << profile[3]<<"</b></td>     </tr>     <tr>       <td  class=\"space\" align=\"right\" style=\"padding-right: 10px\">College: </td>       <td  class=\"space\" colspan=\"3\"><b>College of Informatics and Computing Sciences</b></td>     </tr>   </table> </center><br> ";
	myfile << "<center>   <table  border=1 width=\"80%\">     <tr>       <td class=\"space\" ><b>Code</b></td>       <td class=\"space\" ><b>Course Title</b></td>       <td class=\"space\" ><b>Schedule (Day/Time/Room)</b></td>     </tr>     ";
	for(int i = 0; i < sched.size(); i++)
		{
			vector<string> subjs = seglist(sched[i],';'); //scheds
			myfile << "<tr>  ";
			myfile << "     <td class=\"space\" >";
			myfile << subjs[0]<<"</td>       <td class=\"space\" >"<<subjs[1]<<"</td>       <td class=\"space\" >"<<subjs[2]<<"</td> ";
			myfile << "</tr>  ";		
		}
	
	myfile << "</table></center>   </body> </html> ";
	myfile.close();
}

void createFileList(){
	ofstream myfile;
	myfile.open("masterList.html");
	vector<string> profile = readFileLineByLine("sched.txt");

	myfile << "<!DOCTYPE html> <html> <head>   <title>CICS Student List</title>   <style type=\"text/css\">   body{     font-family: \"Calibri Light\";   }   .space{     padding: 5px;   }     table{       border-collapse: collapse;       border-style: none;     }      .header{       text-align: center;     }   </style> </head> <body>   <center>     <table class=\"header\">       <tr>         <td rowspan=\"5\" class=\"space\"><img src=\"bsu.png\" width=\"100px\" height=\"100px\"></td>         <td >Republic of the Philippines</td>         <td rowspan=\"5\" class=\"space\"><img src=\"cics.jpg\" width=\"100px\" height=\"100px\"></td>       </tr>       <tr>         <td><B>BATANGAS STATE UNIVERSITY</B></td>       </tr>       <tr>         <td>College Of Informatics and Computing Sciences</td>       </tr>       <tr>         <td>Batangas City</td>       </tr>       <tr>         <td>AY 2018-2019, FIRST SEMESTER</td>       </tr>     </table> ";
	myfile << "<br><center><b>MASTER LIST OF STUDENTS</b></center><br>";
	myfile << "<center>   <table  border=1 width=\"80%\">     <tr>       <td class=\"space\" ><b>No.</b></td>       <td class=\"space\" ><b>SR Code</b></td><td class=\"space\" ><b>Name</b></td><td class=\"space\" ><b>Program</b></td><td class=\"space\" ><b>Year Level</b></td>       </tr>     ";
	for(int i = 0; i < profile.size(); i++)
		{
			vector<string> result1 = seglist(profile[i],'|');
			vector<string> subjs = seglist(result1[0],';'); //scheds
			myfile << "<tr>  ";
			myfile <<" <td class=\"space\">"<< i+1<< "</td>"  << "     <td class=\"space\" >";
			myfile << subjs[0]<<"</td>       <td class=\"space\" >"<<subjs[1]<<"</td>       <td class=\"space\" >"<<subjs[2]<<"</td>       <td class=\"space\" >"<<subjs[3]<<"</td>";
			myfile << "</tr>  ";		
		}
	
	myfile << "</table></center>   </body> </html> ";
	myfile.close();
}


int main(int argc, char const *argv[])
{
	LOGIN:
		int a = 1;
		centerTxt("Please Login First\n");
		drawLine();
		while(a == 1){ 
			a = login();
		}

	MAINMENU:
		string b = "0";
		while(b == "0"){
			b = mainMenu();
		}

	SEARCHMENU:
		if (b == "1")
		{
			string search1 = "0";
			while(search1 == "0"){
				search1 = searchMenu();
			}
			if (search1 == "1")
			{
				bool searchTxt = search();
				if(searchTxt == true){
					goto MAINMENU;
				}
			}else{
				goto MAINMENU;
			}
		}
	
	VIEWRECORDS:
		if(b == "2"){
			VIEWRECORD:
			cls();
			centerTxt("Student List\n");
			drawLine();
			vector<string> students1 = readFileLineByLine("sched.txt");
			TextTable t( '-', '|', '+' );
			t.add(" # ");
			t.add( " SR Code " );
			t.add( " Name " );
			t.add( " Program " );
			t.add(" Year ");
			t.endOfRow();
			for(int i = 0; i < students1.size(); i++)
			{
				vector<string> result1 = seglist(students1[i],'|');
				vector<string> result2 = seglist(result1[0],';'); //name
				t.add(ToString(i+1));
				t.add(result2[0]);
				t.add(result2[1]);
				t.add(result2[2]);
				t.add(result2[3]);
				t.endOfRow();
			}
			
			t.setAlignment( 2, TextTable::Alignment::LEFT);
			cout << t<<endl;
			drawLine();
			string choicee;
			centerTxt("What do you want to do?\n");
			centerTxt("1. Print List    \n");
			centerTxt("2. Select Student\n");
			centerTxt("3. Back to Menu  \n");
			centerTxtInput(">> ", 3);
			cin >> choicee;
			if(choicee == "1"){
				createFileList();
				LPCTSTR helpFile = "masterList.html";
    			ShellExecute(NULL, "open", helpFile, NULL, NULL, SW_SHOWNORMAL);

			}else if(choicee == "2"){
				int selectedStudent;
				drawLine();
				centerTxt("Select Student Number\n");
				drawLine();
				centerTxtInput(">> ", 3);
				cin >> selectedStudent;
				vector<string> d1 = seglist(students1[selectedStudent-1], '|');
				vector<string> d2 = seglist(d1[0], ';'); //profile part	
				showStudentData(d2[0].substr(0,8), "sched.txt");
				PRINTTHIS:
				drawLine();
				centerTxt("Do you want to print this record?\n");
				centerTxt("1. Yes         \n");
				centerTxt("2. No          \n");			
				string ans;
				centerTxtInput(">> ", 3);
				cin >> ans;
				if(ans == "1"){
					vector<string> result3 = seglist(d1[1], '=');
					createFile(d2, result3);
					LPCTSTR helpFile = "Sched.html";
    				ShellExecute(NULL, "open", helpFile, NULL, NULL, SW_SHOWNORMAL);
				}else if(ans == "2"){
					goto MAINMENU;
				}else{
					goto PRINTTHIS;
				}
				
			}else if(choicee == "3"){
				goto MAINMENU;
			}
			else{
				goto VIEWRECORD;
			}
			goto MAINMENU;

		}
	
	ADDSTUDENTS:
		if(b == "3"){
			ADDSTUDENT:
			cls();
			
			string dataToSave;

			centerTxt("Add Students\n");
			drawLine();
			string Name;
			string srcode;
			int program;
			centerTxtInput("SR Code:      ",8);
			getline(cin >> ws, srcode);
			centerTxtInput("Name:         ",8);
			getline(cin >> ws, Name);
			cls();
			
			centerTxt("Choose Program (#)\n");
			drawLine();
			showProgramTable();
			centerTxtInput(">> ", 5);
			cin >> program;

			int yearLevel;
			cls();
			
			centerTxt("Choose Year Level (#)\n");
			drawLine();
			showYearLevelTable();
			centerTxtInput(">> ", 5);
			cin >> yearLevel;


			//array from files			
			vector <string> _course = readFileLineByLine("courses.txt");
			vector <string> _rooms = readFileLineByLine("rooms.txt");
			vector <string> _times = readFileLineByLine("time.txt");
			vector <string> _programs = readFileLineByLine("programs.txt");
			
			dataToSave.append(srcode).append(";").append(Name).append(";").append(_programs[program-1]).append(";");
			dataToSave.append(yearLvl[yearLevel-1]).append("|");
			cls();
			
			int numberOfSubjects = 0;
			centerTxt("Enter number of subjects to enroll\n");
			drawLine();
			centerTxtInput(">> ", 5);
			cin >> numberOfSubjects;
			string sched[numberOfSubjects];
			cls();
			
			
			for(int i = 0; i < numberOfSubjects; i++)
			{
				centerTxt("Select a course (#)\n");
				drawLine();
				showCourseTable();
				centerTxtInput("Select a Subject >> ", 8);
				int crs; //index for course
				cin >> crs;
				cls();

				sched[i].append(_course[crs-1]).append(";");

				bool wantMore = true;
				while(wantMore){
					centerTxt("Select Day (#)\n");
					drawLine();
					showDayTable();
					int _b;
					centerTxtInput(">> ", 5);
					cin >> _b;
					cls();
					sched[i] = sched[i].append(dates[_b-1]);
					
					centerTxt("Select Time\n");
					drawLine();
					showTimeTable();
					int d, e;
					centerTxtInput("From:  >> ", 3);
					cin >> d;
					sched[i] = sched[i].append(" ").append(_times[d-1]).append("-");
					centerTxtInput("To:    >> ", 3);
					cin >> e;
					sched[i] = sched[i].append(_times[e-1]).append(" ");
					cls();
					
					centerTxt("Select Room (#)\n");
					drawLine();
					showRoomTable();
					int f;
					centerTxtInput(">> ", 5);
					cin >> f;
					sched[i] = sched[i].append(_rooms[f-1]).append(", ");
					cls();
					
					MORESCHED:
					string moresubjs;
					centerTxt("Add more schedule for this subject? (1. Yes, 2. No)\n");
					drawLine();
					centerTxtInput(">> ", 3);
					cin >> moresubjs;
					cls();
					if(moresubjs == "1"){
						wantMore = true;
					}else if(moresubjs == "2"){
						wantMore = false;
					}else{
						goto MORESCHED;
					}
				}
				sched[i].append("=");
				dataToSave.append(sched[i]);
			}

			//cout << dataToSave << endl;
			centerTxt("Student Data\n");
			drawLine();
			addData("temporary.txt", dataToSave);
			
			showStudentData(srcode.substr(0, 8), "temporary.txt");
			QUEST1:
			centerTxt("Save student data?\n");
			drawLine();
			centerTxt("1. Yes\n");
			centerTxt("2. No \n");
			centerTxtInput(">> ", 3);
			string _save;
			cin >> _save;
			if(_save == "1"){
				addData("sched.txt", dataToSave);
				centerTxt("Data Saved!\n");
				drawLine();
				PRINTNOW:
				centerTxt("Do you want to print it now?\n");
				centerTxt("1. Yes\n");
				centerTxt("2. No \n");
				centerTxtInput(">> ", 3);
				string qprint;
				cin >> qprint;
				if(qprint == "1"){
					LPCTSTR helpFile = "Sched.html";
    				ShellExecute(NULL, "open", helpFile, NULL, NULL, SW_SHOWNORMAL);
				}else if(qprint == "2"){
					goto MAINMENU;
				}else{
					goto PRINTNOW;
				}
			}else if(_save == "2"){
				goto MAINMENU;
			}else{
				goto QUEST1;
			}
			centerTxt("Press any key to go back to main menu...\n");
			drawLine();
			centerTxtInput(">> ", 3);
			goto MAINMENU;
		}

	ADDCOURSES:	
		if (b == "4") {
			ADDCOURSE:
			cls();
			showCourseTable();
			drawLine();
			centerTxt("Add Courses\n");
			drawLine();
			string courseCode;
			string courseName;
			centerTxtInput("Course Code:  ",8);
			getline(cin >> ws, courseCode);
			centerTxtInput("Course Title: ",8);
			getline(cin >> ws, courseName);
			drawLine();
			SAVECOURSE:
			centerTxt("Save course?\n");
			centerTxt("1. Yes\n");
			centerTxt("2. No \n");
			string ans;
			centerTxtInput(">> ", 3);
			cin >> ans;
			
			if(ans == "1"){
				addData("courses.txt", courseCode.append(";").append(courseName));
				cls();
				showCourseTable();
				drawLine();
				centerTxt("Data Saved!\n");
				drawLine();

				ADD_COURSE_AGAIN:
				centerTxt("Add again?\n");
				centerTxt("1. Yes\n");
				centerTxt("2. No \n");
				string ans1;
				centerTxtInput(">> ", 3);
				cin >> ans1;
				if(ans1 == "1"){
					goto ADDCOURSE;
				}else if(ans1 == "2"){
					goto MAINMENU;
				}else{
					goto ADD_COURSE_AGAIN;
				}
			}else if(ans == "2"){
				goto MAINMENU;
			}
			else{
				goto SAVECOURSE;
			}
		}
	
	ADDPOGRAMS:	
		if (b == "5") {
			ADDPROGRAM:
			cls();
			showProgramTable();
			drawLine();
			centerTxt("Add Programs\n");
			drawLine();
			string program;
			centerTxtInput("Program:  ",8);
			getline(cin >> ws, program);
			drawLine();
			SAVEPROGRAM:
			centerTxt("Save program?\n");
			centerTxt("1. Yes\n");
			centerTxt("2. No \n");
			string ans;
			centerTxtInput(">> ", 3);
			cin >> ans;
			
			if(ans == "1"){
				addData("programs.txt", program);
				cls();
				showProgramTable();
				drawLine();
				centerTxt("Data Saved!\n");
				drawLine();

				ADD_PROGRAM_AGAIN:
				centerTxt("Add again?\n");
				centerTxt("1. Yes\n");
				centerTxt("2. No \n");
				string ans1;
				centerTxtInput(">> ", 3);
				cin >> ans1;
				if(ans1 == "1"){
					goto ADDPROGRAM;
				}else if(ans1 == "2"){
					goto MAINMENU;
				}else{
					goto ADD_PROGRAM_AGAIN;
				}
			}else if(ans == "2"){
				goto MAINMENU;
			}
			else{
				goto SAVEPROGRAM;
			}
		}
	
	ADDROOMS:	
		if (b == "6") {
			ADDROOM:
			cls();
			showRoomTable();
			drawLine();
			centerTxt("Add Rooms\n");
			drawLine();
			string room;
			centerTxtInput("Room:  ",8);
			getline(cin >> ws, room);
			drawLine();
			SAVEROOM:
			centerTxt("Save room?\n");
			centerTxt("1. Yes\n");
			centerTxt("2. No \n");
			string ans;
			centerTxtInput(">> ", 3);
			cin >> ans;
			
			if(ans == "1"){
				addData("rooms.txt", room);
				cls();
				showRoomTable();
				drawLine();
				centerTxt("Data Saved!\n");
				drawLine();

				ADD_ROOM_AGAIN:
				centerTxt("Add again?\n");
				centerTxt("1. Yes\n");
				centerTxt("2. No \n");
				string ans1;
				centerTxtInput(">> ", 3);
				cin >> ans1;
				if(ans1 == "1"){
					goto ADDROOM;
				}else if(ans1 == "2"){
					goto MAINMENU;
				}else{
					goto ADD_ROOM_AGAIN;
				}
			}else if(ans == "2"){
				goto MAINMENU;
			}
			else{
				goto SAVEROOM;
			}
		}
	
	ADDTIMES:	
		if (b == "7") {
			ADDTIME:
			cls();
			showTimeTable();
			drawLine();
			centerTxt("Add Times\n");
			drawLine();
			string time;
			centerTxtInput("Time:  ",8);
			getline(cin >> ws, time);
			drawLine();
			SAVETIME:
			centerTxt("Save time?\n");
			centerTxt("1. Yes\n");
			centerTxt("2. No \n");
			string ans;
			centerTxtInput(">> ", 3);
			cin >> ans;
			
			if(ans == "1"){
				addData("time.txt", time);
				cls();
				showTimeTable();
				drawLine();
				centerTxt("Data Saved!\n");
				drawLine();

				ADD_TIME_AGAIN:
				centerTxt("Add again?\n");
				centerTxt("1. Yes\n");
				centerTxt("2. No \n");
				string ans1;
				centerTxtInput(">> ", 3);
				cin >> ans1;
				if(ans1 == "1"){
					goto ADDTIME;
				}else if(ans1 == "2"){
					goto MAINMENU;
				}else{
					goto ADD_TIME_AGAIN;
				}
			}else if(ans == "2"){
				goto MAINMENU;
			}
			else{
				goto SAVETIME;
			}
		}	
		

	EXIT:
		if (b == "8")
		{
			string logout1 = "0";
			while(logout1 == "0"){
				logout1 = logout();
			}
			if (logout1 == "1")
			{
				cls();
				printl("Loging out...");
			}else if (logout1 == "2")
			{
				goto MAINMENU;
			}
			else{
				goto EXIT;
			}

		}
	return 0;
}

bool login(){
	string username, password;
	centerTxt("Username:\n\n");
	centerTxtInput(">>  ",6);
	getline(cin, username);
	printl("");
	centerTxt("Password:\n\n");
	centerTxtInput(">>  ",6);
	password=getpass("",true);

	string unpw = username.append(";").append(password);
	if (loginInfo(unpw) == true)
	{
		return false;
	}else{
		cls();
		centerTxt("Login Failed. Please try again.\n");
		drawLine();
		return true;
	}
}

string print(string txt){
	cout << txt;
	return txt;
}

string printl(string txt){
	cout << txt << endl;
	return txt;
}

void cls(){
	cout << "\033[2J\033[1;1H";
}

void centerTxt(string txt){
	CONSOLE_SCREEN_BUFFER_INFO sbInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
	int width = sbInfo.dwSize.X;
	int txtsize = txt.length();
	int ws = width/2- txtsize/2;
	for (int i = 0; i < ws; ++i)
	{
		print(" ");
	}
	print(txt);
	consoleWidth = width;
}

void centerTxtInput(string txt, int inputLength){
	CONSOLE_SCREEN_BUFFER_INFO sbInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
	int width = sbInfo.dwSize.X;
	int txtsize = txt.length();
	int ws = width/2- txtsize/2;
	for (int i = 0; i < ws- inputLength; ++i)
	{
		print(" ");
	}
	print(txt);
}

void drawLine(){
	for (int i = 0; i < consoleWidth; ++i)
		{
			print("-");
		}
		print("\n");
}

string mainMenu(){
	cls();
	centerTxt("Press a number to continue\n");
	drawLine();
	centerTxt("1.\tSearch Student\n\n");
	centerTxt("2.\tView Records  \n\n");
	centerTxt("3.\tAdd Student   \n\n");
	centerTxt("4.\tAdd Courses   \n\n");
	centerTxt("5.\tAdd Programs  \n\n");
	centerTxt("6.\tAdd Rooms     \n\n");
	centerTxt("7.\tAdd Time      \n\n");
	centerTxt("8.\tExit          \n\n");
	drawLine();
	string a;
	centerTxtInput(">> ", 5);
	cin >> a;
	if (a == "1")
	{
		return "1";
	}else if (a == "2")
	{
		return "2";
	}else if (a == "3")
	{
		return "3";
	}else if (a== "4")
	{
		return "4";
	}else if(a == "5"){
		return "5";
	}else if(a == "6"){
		return "6";
	}else if(a == "7"){
		return "7";
	}else if(a == "8"){
		return "8";
	}
	else{
		return "0";
	}

}

string searchMenu(){
	cls();
	centerTxt("Press a number to continue\n");
	drawLine();
	centerTxt("1.\tSearch Student\n\n");
	centerTxt("2.\tBack to Menu  \n\n");
	drawLine();
	string a;
	centerTxtInput(">> ", 5);
	cin >> a;
	if (a == "1")
	{
		return "1";
	}else if (a == "2")
	{
		return "2";
	}else
	{
		return "0";
	}
}

bool search(){
	SRCODESEARCH:
	cls();
	centerTxt("Search\n");
	drawLine();
	string a;
	centerTxtInput("SR Code: ", 8);
	cin >> a;
	drawLine();

	vector<string> srcode = readFileLineByLine("sched.txt"); //full data
	vector<string> srcode1; //srcode only for comparison
	for (int i = 0; i < srcode.size(); ++i)
	{
		srcode1.push_back(srcode[i].substr(0, 8));
	}
	

	auto it = find(srcode1.begin(), srcode1.end(), a.substr(0, 8));
	if (it == srcode1.end())
	{
		printl("No match found.");
	} else
	{
		int index = distance(srcode1.begin(), it);
		vector<string> result1 = seglist(srcode[index],'|');
		vector<string> result2 = seglist(result1[0],';'); //name
		TextTable t( '=', '|', '+' );
		t.add( " SR Code " );
		t.add( " Name " );
		t.add( " Program " );
		t.add(" Year ");
		t.endOfRow();
		for(int i = 0; i < result2.size(); i++)
		{
			t.add(result2[i]);
		}
		t.endOfRow();
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;

		vector<string> result3 = seglist(result1[1],'='); //scheds
		

		TextTable t1( '-', '|', '+' );
		t1.add( " Course Code " );
		t1.add( " Course Title " );
		t1.add( " Schedule (Day/Time/Room) " );
		t1.endOfRow();
		for(int i = 0; i < result3.size(); i++)
		{
			vector<string> subjs = seglist(result3[i],';'); //scheds
			for(int j = 0; j < subjs.size(); j++)
			{
				t1.add(subjs[j]);
			}
			t1.endOfRow();			
		}
		t1.setAlignment( 2, TextTable::Alignment::RIGHT );
   		cout << t1;
		createFile(result2, result3);
	}
	drawLine();

	SEARCHAGAIN:
	centerTxt("Search Again?\n");
	centerTxt("1.\tYes           \n");
	centerTxt("2.\tNo            \n");
	centerTxt("3.\tPrint Schedule\n");
	string ans;
	centerTxtInput(">> ", 5);
	cin>>ans;
	
	if (ans == "1") {
		goto SRCODESEARCH;
	}else if(ans == "2"){
		return true;
	}else if (ans == "3") {
		LPCTSTR helpFile = "Sched.html";
    	ShellExecute(NULL, "open", helpFile, NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		goto SEARCHAGAIN;
	}

}

string logout(){
	cls();
	centerTxt("Logout\n");
	drawLine();
	centerTxt("Logout your account?\n\n");
	centerTxt("1.\tYes           \n\n");
	centerTxt("2.\tNo            \n\n");
	drawLine();
	string a;
	centerTxtInput(">> ", 5);
	cin >> a;
	if (a == "1")
	{
		return "1";
	}else if (a == "2")
	{
		return "2";
	}else
	{
		return "0";
	}
}

vector<string> readFileLineByLine(string filename){
	ifstream file;
    file.open(filename);
    vector<string> line;
    string element;

    if (file.is_open()) {
        int i = 0;
        while (getline(file, element)) {
            line.push_back(element);
        }
    }

    file.close();
    return line;
}

bool loginInfo(string unpw){
	ifstream file;
    file.open("login.txt");
    string line[1000];
    string element;

    if (file.is_open()) {
        int i = 0;
        while (file >> element) {
            line[i++] = element;
        }
    }

    file.close();
    bool exists = find(begin(line), end(line), unpw) != end(line);
    return exists;
}

int totalRows(string filename){
	    ifstream file;
    string line;
    file.open(filename);
	int i = 1;   
    while (getline (file, line)){
        i++;
    }
    return i;
}

vector<string> seglist(string txt, char a){
	stringstream test(txt);
	string segment;
	vector<string> seglist1;

	while(getline(test, segment, a))
	{
	   seglist1.push_back(segment);
	}
	return seglist1;
}

void addData(string fileName, string data){
	ofstream outfile;
	outfile.open(fileName, std::ios_base::app);
	outfile << data << endl; 
}

TextTable showCourseTable(){
	vector<string> result = readFileLineByLine("courses.txt"); //full data
	TextTable t( '=', '|', '+' );
		t.add( " # " );
		t.add( " Course Code " );
		t.add( " Course Title " );
		t.endOfRow();
		
	for(int i = 0; i < result.size(); i++){
		vector<string> result2 = seglist(result[i],';'); 
		t.add(ToString(i+1));
		t.add(result2[0]);
		t.add(result2[1]);
		t.endOfRow(); 
	}
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;
		return t;
}

TextTable showRoomTable(){
	vector<string> result = readFileLineByLine("rooms.txt"); //full data
	TextTable t( '=', '|', '+' );
		t.add( " # " );
		t.add( " Room " );
		t.endOfRow();
		
	for(int i = 0; i < result.size(); i++){ 
		t.add(ToString(i+1));
		t.add(result[i]);
		t.endOfRow(); 
	}
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;
		return t;
}

TextTable showProgramTable(){
	vector<string> result = readFileLineByLine("programs.txt"); //full data
	TextTable t( '=', '|', '+' );
		t.add( " # " );
		t.add( " Program " );
		t.endOfRow();
		
	for(int i = 0; i < result.size(); i++){ 
		t.add(ToString(i+1));
		t.add(result[i]);
		t.endOfRow(); 
	}
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;
		return t;
}

TextTable showTimeTable(){
	vector<string> result = readFileLineByLine("time.txt"); //full data
	TextTable t( '=', '|', '+' );
		t.add( " # " );
		t.add( " Time " );
		t.endOfRow();
		
	for(int i = 0; i < result.size(); i++){ 
		t.add(ToString(i+1));
		t.add(result[i]);
		t.endOfRow(); 
	}
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;
		return t;
}

TextTable showDayTable(){
	vector<string> result = dates; //full data
	TextTable t( '=', '|', '+' );
		t.add( " # " );
		t.add( " Day " );
		t.endOfRow();
		
	for(int i = 0; i < result.size(); i++){ 
		t.add(ToString(i+1));
		t.add(result[i]);
		t.endOfRow(); 
	}
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;
		return t;
}

TextTable showYearLevelTable(){
	vector<string> result = yearLvl; //full data
	TextTable t( '=', '|', '+' );
		t.add( " # " );
		t.add( " Year Level " );
		t.endOfRow();
		
	for(int i = 0; i < result.size(); i++){ 
		t.add(ToString(i+1));
		t.add(result[i]);
		t.endOfRow(); 
	}
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;
		return t;
}




string ToString(int i){
	stringstream ss; 
	ss << i ;
	string newString = ss.str();
	return newString;
}

bool showStudentData(string a, string file1){
	vector<string> srcode = readFileLineByLine(file1); //full data
	vector<string> srcode1; //srcode only for comparison
	for (int i = 0; i < srcode.size(); ++i)
	{
		srcode1.push_back(srcode[i].substr(0, 8));
	}
	

	auto it = find(srcode1.begin(), srcode1.end(), a);
	if (it == srcode1.end())
	{
		printl("No match found.");
	} else
	{
		int index = distance(srcode1.begin(), it);
		vector<string> result1 = seglist(srcode[index],'|');
		vector<string> result2 = seglist(result1[0],';'); //name
		TextTable t( '=', '|', '+' );
		t.add( " SR Code " );
		t.add( " Name " );
		t.add( " Program " );
		t.add(" Year ");
		t.endOfRow();
		for(int i = 0; i < result2.size(); i++)
		{
			t.add(result2[i]);
		}
		t.endOfRow();
		t.setAlignment( 2, TextTable::Alignment::LEFT);
   		cout << t<<endl;

		vector<string> result3 = seglist(result1[1],'='); //scheds
		

		TextTable t1( '-', '|', '+' );
		t1.add( " Course Code " );
		t1.add( " Course Title " );
		t1.add( " Schedule (Day/Time/Room) " );
		t1.endOfRow();
		for(int i = 0; i < result3.size(); i++)
		{
			vector<string> subjs = seglist(result3[i],';'); //scheds
			for(int j = 0; j < subjs.size(); j++)
			{
				t1.add(subjs[j]);
			}
			t1.endOfRow();			
		}
		t1.setAlignment( 2, TextTable::Alignment::RIGHT );
   		cout << t1;
		createFile(result2, result3);
	}
	drawLine();
}

