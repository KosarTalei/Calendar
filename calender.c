#include<stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define MAX_EVENTS 10 //Events Max
#define MAX_DESCRIPTION 100 // 100 Description Max

int shamsiyear,shamsimonth,shamsiday;
int shamsi_now_year,shamsi_now_month,shamsi_now_day;
char key;

typedef struct{

    int shamsiday;
    int shamsimonth;
    int shamsiyear;
    char title_event[MAX_DESCRIPTION];
    char description_event[MAX_DESCRIPTION]; //event description

}event;

event list[MAX_EVENTS];
int task_index = 0;
int event_index =0;
int selection = 0;
char file[FILENAME_MAX];
char temp[20];


int miladi_day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *miladi_month[]={
	" ","\n\n\nJanuary","\n\n\nFebruary","\n\n\nMarch","\n\n\nApril","\n\n\nMay","\n\n\nJune",
    "\n\n\nJuly","\n\n\nAugust","\n\n\nSeptember","\n\n\nOctober","\n\n\nNovember","\n\n\nDecember"
};

int shamsi_day[]={0,31,31,31,31,31,31,30,30,30,30,30,29};
char *shamsi_month[]={
	" ","\n\n\nFarvardin","\n\n\nOrdibehesht","\n\n\nKhordad","\n\n\nTir","\n\n\nMordad","\n\n\nShahrivar",
	"\n\n\nMehr","\n\n\nAban","\n\n\nAzar","\n\n\nDey","\n\n\nBahman","\n\n\nEsfand"    
};

int inputyear(void)
{
	int year;
	printf("Please enter a year : ");
	scanf("%d", &year);
	return year;
}

int determine_miladi_daycode(int year)//starting day of month
{
	int daycode;
	int day1, day2, day3;
	day1 = (year - 1.0)/ 4.0;
	day2 = (year - 1.0)/ 100.0;
	day3 = (year - 1.0)/ 400.0;
	daycode = (year + day1 - day2 + day3) %7;
	return daycode;
}

int determine_miladi_year(int year)//kabise or not
{
	if(year% 4 == 0 && year%100 != 0 || year%400 == 0){//1996,2000:kabise
		miladi_day[2] = 29;//February has 29 days
		return 1;
	}
	else{
		miladi_day[2] = 28;//February has 28 days
		return 0;
	}
}

int determine_shamsi_year(int year){
    int reminder = year/33;
    if(reminder== 1 || 5 || 9 || 13 || 17 || 22 || 26 ||30){//kabise
        shamsi_day[12] = 30;
    }
}

void miladi_calendar(int year, int daycode)
{
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("%s", miladi_month[month]);
		printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		
		for ( day = 1; day <= 1 + daycode * 5; day++ )//first date
		{
			printf(" ");
		}
		
		for ( day = 1; day <= miladi_day[month]; day++ )
		{
			printf("%2d", day );
			
			if ( ( day + daycode ) % 7 > 0 ){// before Sat
				printf("   " );
            }
			else{
				printf("\n " );//next line
            }
		}
		daycode = ( daycode + miladi_day[month] ) % 7;// next month
	}
}

void shamsi_calender(int year,int daycode)//1 farvardin 98-21 march 2019
{
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("%s",shamsi_month[month]);
		printf("\n\n1sh  2sh  3sh  4sh  5sh  jom  sha\n" );
        
		for ( day = 1; day <= 1 + daycode * 5; day++ )//first date
        {
			printf(" ");
		}
		
		for ( day = 1; day <= shamsi_day[month]; day++ )// month
		{
			printf("%2d", day );

			if ( ( day + daycode ) % 7 > 0 ){
				printf("   " );
            }
			else{
				printf("\n " );
            }
		}
		daycode = ( daycode + shamsi_day[month] ) % 7;// next month
	}
}

void print_day(int day)
{
    switch( day % 7 ){
        case 0:
            printf("Friday");  
            break;

        case 1:
            printf("Saturday");
            break;

        case 2:
            printf("Sunday");
            break;

        case 3:
            printf("Monday");
            break;

        case 4:
            printf("Tuesday");
            break;
        
        case 5:
            printf("Wednesday");
            break;
        
        case 6:
            printf("Thursday");
            break;

    }
    return;
}

int now_time_miladi(void){
 
    int now_year,now_month,now_day;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    now_year = tm.tm_year + 1900;
    now_month = tm.tm_mon + 1;
    now_day = tm.tm_mday;
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n",now_year,now_month,now_day,tm.tm_hour,tm.tm_min,tm.tm_sec);
}

int now_time_shamsi(void){
    int now_year,now_month,now_day;//miladi
    int leapyear,shamsi_past_day;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    now_year = tm.tm_year + 1900;
    now_month = tm.tm_mon + 1;
    now_day = tm.tm_mday;
    if(now_year% 4 == 0 && now_year%100 != 0 || now_year%400 == 0){
        leapyear=1;
	}
	else{
        leapyear=0;
	}
    switch (now_month){
        case 1:{
            break;
        }
        case 2:{
            now_day=31+now_day+leapyear;
            break;
        }
        case 3:{
            now_day=31+28+leapyear+now_day;
            break;
        }
        case 4:{
            now_day=31+28+leapyear+31+now_day;
            break;
        }
        case 5:{
            now_day=31+28+leapyear+31+30+now_day;
            break;
        }
        case 6:{
            now_day=31+28+leapyear+31
            +30+31+now_day;
            break;
        }
        case 7:{
            now_day=31+28+leapyear+31+30+31+30+now_day;
            break;
        }
        case 8:{
            now_day=31+28+leapyear+31+30+31+30+31+now_day;
            break;            
        }
        case 9:{
            now_day=31+28+leapyear+31+30+31+30+31+31+now_day;
            break;            
        }
        case 10:{
            now_day=31+28+leapyear+31+30+31+30+31+31+30+now_day;
            break;
        }
        case 11:{
            now_day=31+28+leapyear+31+30+31+30+31+31+30+31+now_day;
            break;
        }
        case 12:{
            now_day=31+28+leapyear+31+30+31+30+31+31+30+31+30+now_day;
            break;
        }
    }
    shamsi_past_day=now_day+286;

    int past_month;
    if(shamsi_past_day<=186){//first six month
        past_month=shamsi_past_day /31;
        shamsi_now_month=past_month+1;
        shamsi_now_day=shamsi_past_day %31;
    }
    if(shamsi_past_day>186){//last six month
        past_month=( shamsi_past_day-(6*31) ) /30;
        shamsi_now_month=past_month+6+1;
        shamsi_now_day=(shamsi_past_day-186) %30;
    }
    shamsi_now_year=now_year - (621+leapyear);
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n",shamsi_now_year,shamsi_now_month,(shamsi_now_day)-1,tm.tm_hour,tm.tm_min,tm.tm_sec);
}

//event
void print_events() {

    puts("+---------EVENT---------+\n"
        "|  1. New Event         |\n"
        "|  2. Delete Event      |\n"
        "|  3. Edit Event        |\n"
        "|  4. Display Schedule  |\n"
        "|  5. Exit              |\n"
        "+-----------------------+\n");
}

event *Eventmemory() {
    event *e = (event*)malloc(sizeof(event));//new event in e memory
    e->shamsiday =0;
    e->shamsimonth =0;
    e->shamsiyear =0;
    strcpy(e->description_event, "");
    return e;
}
event* newEvent(event *e) {

    puts("\n+--- EVENT TITLE ---+");
    printf("%s", "| Enter a title : ");
    fgets(e->title_event, MAX_DESCRIPTION, stdin);

    puts("\n+--- EVENT DESCRIPTION ---+");
    printf("%s", "| Enter a description: ");
    fgets(e->description_event, MAX_DESCRIPTION, stdin);

    puts("+-------------------------+\n");
    e->shamsiyear = shamsiyear;
	e->shamsimonth = shamsimonth;
	e->shamsiday = shamsiday;
    printf("| Event added in %2d / %2d / %2d.\n", e->shamsiyear,e->shamsimonth,e->shamsiday);

    return e;
}
void addEventAtIndex(event list[], const event e, const int i) {

    list[i].shamsiyear = e.shamsiyear;
    list[i].shamsimonth = e.shamsimonth;
    list[i].shamsiday = e.shamsiday;
    strcpy(list[i].title_event, e.title_event);
    strcpy(list[i].description_event, e.description_event);

}

void sort(event list[], const int size) {//swapping struct

    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0 && (list[j - 1].shamsimonth >= list[j].shamsimonth && list[j - 1].shamsiday >= list[j].shamsiday); j--) {
            int tmpshamsimonth = list[j].shamsimonth;
            int tmpshamsiday = list[j].shamsiday;

            char tmpdescription[MAX_DESCRIPTION];
            strcpy(tmpdescription, list[j].description_event);

            char tmptitle_event[MAX_DESCRIPTION];
            strcpy(tmptitle_event, list[j].title_event);

            int tmpshamsimonth1 = list[j - 1].shamsimonth;
            int tmpshamsiday1 = list[j - 1].shamsiday;

            char tmpdescription1[MAX_DESCRIPTION];
            strcpy(tmpdescription1, list[j - 1].description_event);

            char tmptitle_event1[MAX_DESCRIPTION];
            strcpy(tmptitle_event1, list[j-1].title_event);

            list[j].shamsimonth = tmpshamsimonth1;
            list[j].shamsiday = tmpshamsiday1;
            strcpy(list[j].description_event, tmpdescription1);
            strcpy(list[j].title_event, tmptitle_event1);

            list[j - 1].shamsimonth = tmpshamsimonth;
            list[j - 1].shamsiday = tmpshamsiday;
            strcpy(list[j - 1].description_event, tmpdescription);
            strcpy(list[j-1].title_event,tmptitle_event);
        }
    }
}

void sortInsert(event list[], int *size, event e) {// Add event to event list

    addEventAtIndex(list, e, *size); // end of the list
    (*size)++;
    //  Sort
    sort(list, *size);
}

void printEvent(const event e) {

    printf("%s",e.title_event);
    printf("%s",e.description_event);
}
void printEventList(const event list[], const int size,int year,int month,int day) {

    char *line = "+-----------------------------------------------+";
    printf("%s\n",line);
    if (size == 0) {
        puts("\n| You have no events!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if(list[i].shamsiyear==year && list[i].shamsimonth==month && list[i].shamsiday==day){
            printf("| [%d] ", i);
            printEvent(list[i]);
        }
    }
    putchar('\n');
}
void deleteEvent(event list[], int *size) {

    if (*size == 0) { //empty
        puts("\n| Event list already empty.\n");
        return;
    }

    char temp[21];
    int id;
    char *line = "\n+--------------------------------+";
    printf("%s\n|          DELETE EVENT          |%s\n\n", line, line);

    for (int i = 0; i < *size; i++) { //event list
        printf("| [%d] ", i);
        printEvent(list[i]);
    }

    printf("%s", "\n| Enter the ID of an event to delete: ");

    fgets(temp, 21, stdin);
    id = atoi(temp);

    if (id > *size - 1) {
        printf("\n| No event located at %d\n", id);
        return;
    }
    printf("| Event [%d] deleted successfully.\n\n", id);

    if (id != (*size - 1)) { //the last event deleted
        sort(list, *size);
    }
    (*size)--; //size of the list
}

void editevent(event list[], int *size){

    if (*size == 0) { //empty
        puts("\n| Event list already empty.\n");
        return;
    }

    char temp[21];
    int id;
    char *line = "\n+--------------------------------+";
    printf("%s\n|          EDIT EVENT          |%s\n\n", line, line);

    for (int i = 0; i < *size; i++) { //event list
        printf("| [%d] ", i);
        printEvent(list[i]);
    }

    printf("%s", "\n| Enter the ID of an event to edit: ");//delet

    fgets(temp, 21, stdin);
    id = atoi(temp);//convert string to int

    if (id > *size - 1) {
        printf("\n| No event located at %d\n", id);
        return;
    }

    if (id != (*size - 1)) { //the last event deleted
        sort(list, *size);
    }
    (*size)--; //size of the list

    id=id-1;
    sortInsert(list, &(id), *newEvent(&list[id]));//new event
    printf("| Event [%d] edited successfully.\n\n", id);
}
int search(const event e, char searchevent[]){
    
	if (strstr(e.title_event, searchevent) != NULL)
	{
		printf("\n %d//%d//%d: %s, %s", e.shamsiyear, e.shamsimonth, e.shamsiday, e.title_event, e.description_event);
        Sleep(2000);
		return 1;
	}
	else
		return 0;
}
//task
typedef struct{
    int shamsiday;
    int shamsimonth;
    int shamsiyear;
    char title_task[MAX_DESCRIPTION];
    char description_task[MAX_DESCRIPTION];
    char done[100];//DONE OR NOT 
}task;

task list_task[MAX_EVENTS];
void print_tasks(){
    puts("+---------TASK---------+\n"
        "|  1. New Task          |\n"
        "|  2. Delete Task       |\n"
        "|  3. Edit Task         |\n"
        "|  4. Display Schedule  |\n"
        "|  5. Done ?            |\n"
        "|  6. Exit              |\n"
        "+-----------------------+\n");
}

task *Taskmemory() {
    task *t = (task*)malloc(sizeof(task));//new task in e memory
    t->shamsiday =0;
    t->shamsimonth =0;
    t->shamsiyear =0;
    strcpy(t->description_task, "");
    strcpy(t->done, "");
    return t;
}

task* newTask(task *t) {

    puts("\n+--- TASK TITLE ---+");
    printf("%s", "| Enter a title : ");
    fgets(t->title_task, MAX_DESCRIPTION, stdin);

    puts("\n+--- TASK DESCRIPTION ---+");
    printf("%s", "| Enter a description: ");
    fgets(t->description_task, MAX_DESCRIPTION, stdin);

    puts("+-------------------------+\n");
    printf("| Task added in %2d / %2d / %2d.\n",shamsiyear,shamsimonth,shamsiday);

    return t;
}

void addTaskAtIndex(task list[], const task t, const int i) {

    list_task[i].shamsiyear = t.shamsiyear;
    list_task[i].shamsimonth = t.shamsimonth;
    list_task[i].shamsiday = t.shamsiday;
    strcpy(list_task[i].title_task, t.title_task);
    strcpy(list_task[i].description_task, t.description_task);
    strcpy(list_task[i].done, t.done);
}

void sorttask(task list_task[], const int size) {

    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0 && (list_task[j - 1].shamsimonth >= list_task[j].shamsimonth && list_task[j - 1].shamsiday >= list_task[j].shamsiday); j--) {
            int tmpshamsimonth = list_task[j].shamsimonth;
            int tmpshamsiday = list_task[j].shamsiday;

            char tmpdescription[MAX_DESCRIPTION];
            strcpy(tmpdescription, list_task[j].description_task);

            char tmptitle_task[MAX_DESCRIPTION];
            strcpy(tmptitle_task, list_task[j].title_task);

            int tmpshamsimonth1 = list_task[j - 1].shamsimonth;
            int tmpshamsiday1 = list_task[j - 1].shamsiday;

            char tmpdescription1[MAX_DESCRIPTION];
            strcpy(tmpdescription1, list_task[j - 1].description_task);

            char tmptitle_task1[MAX_DESCRIPTION];
            strcpy(tmptitle_task1, list_task[j-1].title_task);

            list_task[j].shamsimonth = tmpshamsimonth1;
            list_task[j].shamsiday = tmpshamsiday1;
            strcpy(list_task[j].description_task, tmpdescription1);
            strcpy(list_task[j].title_task, tmptitle_task1);

            list_task[j - 1].shamsimonth = tmpshamsimonth;
            list_task[j - 1].shamsiday = tmpshamsiday;
            strcpy(list_task[j - 1].description_task, tmpdescription);
            strcpy(list_task[j-1].title_task,tmptitle_task);
        }
    }
}

void sortInsert_task(task list_task[], int *size, task t) {// Add task to event list

    addTaskAtIndex(list_task, t, *size); // end of the list
    (*size)++;
    //  Sort
    sorttask(list_task, *size);
}

void printTask(const task t) {
    
    printf("%s",t.title_task);
    printf("%s",t.description_task);
}
void printdone(const task t){
    printf("%s\n",t.done);//DONE OR NOT
}
void printTaskList(const task list_task[], const int size,int year,int month,int day) {
    char *line = "+-----------------------------------------------+";
    printf("%s\n",line);
    if (size == 0) {
        puts("\n| You have no tasks!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        //if(list_task[i].shamsiyear==year && list_task[i].shamsimonth==month && list_task[i].shamsiday==day){
            printdone(list_task[i]);
            printf("| [%d] ", i);
            printTask(list_task[i]);
        //}
    }
    putchar('\n');
}

void deleteTask(task list_task[], int *size) {

    if (*size == 0) { //empty
        puts("\n| Event list already empty.\n");
        return;
    }

    char temp[21];
    int id;
    char *line = "\n+--------------------------------+";
    printf("%s\n|          DELETE TASK          |%s\n\n", line, line);

    for (int i = 0; i < *size; i++) {
        printf("| [%d] ", i);
        printTask(list_task[i]);
    }

    printf("%s", "\n| Enter the ID of an task to delete: ");

    fgets(temp, 21, stdin);
    id = atoi(temp);

    if (id > *size - 1) {
        printf("\n| No task located at %d\n", id);
        return;
    }
    printf("| Task [%d] deleted successfully.\n\n", id);

    if (id != (*size - 1)) { //the last task deleted
        sorttask(list_task, *size);
    }

    (*size)--; //size of the list
}
void edittask(task list_task[], int *size){

    if (*size == 0) { //empty
        puts("\n| Task list already empty.\n");
        return;
    }

    char temp[21];
    int id;
    char *line = "\n+--------------------------------+";
    printf("%s\n|          DELETE TASK          |%s\n\n", line, line);

    for (int i = 0; i < *size; i++) { 
        printf("| [%d] ", i);
        printTask(list_task[i]);
    }

    printf("%s", "\n| Enter the ID of an task to edit: ");//delet

    fgets(temp, 21, stdin);
    id = atoi(temp);

    if (id > *size - 1) {
        printf("\n| No task located at %d\n", id);
        return;
    }

    if (id != (*size - 1)) { //the last task deleted
        sort(list, *size);
    }
    (*size)--; //size of the list

    id=id-1;
    printf("| Event [%d] edited successfully.\n\n", id);
}

void donetask(task list_task[],int *size){

    if (*size == 0) { //empty
        puts("\n| Task list already empty.\n");
        return;
    }

    char temp[21];
    int id;

    for (int i = 0; i < *size; i++) { //task list
        printf("| [%d] ", i);
        printTask(list_task[i]);
    }

    printf("%s", "\n| Enter the ID of an task that have done: ");

    fgets(temp, 21, stdin);
    id = atoi(temp);

    if (id > *size - 1) {
        printf("\n| No task located at %d\n", id);
        return;
    }
    strcpy(list_task[id].done,"Done!");
    printf("| Task [%d] done successfully.\n\n", id);
}
void saveList(char *filename, event list[],task list_task[], int size,int size1) {

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(f, "%d %d %s", list[i].shamsiyear, list[i].shamsiday, (list[i].description_event));

    }
    for(int i=0 ;i<size1;i++){
        fprintf(f, "%d %d %s", list_task[i].shamsiyear, list_task[i].shamsiday, list_task[i].description_task);
    }

    printf("\n| %d %s successfully saved into \"%s\".\n\n", size, "events and tasks", filename);

    fclose(f);
}

void loadList(char *filename, event list[]) {
    int size = 1024, pos;
    int c;
    char *buffer = (char *)malloc(size);

    FILE *f = fopen(filename, "r");
    if(f) {
        do { // read all lines
            int pos = 0;
            do{ // read one line
                c = fgetc(f);
                if(c != EOF) {//to end
                    buffer[pos++] = (char)c;
                    printf("%s", buffer[pos-1]);
                }
                if(pos >= size - 1) { // increase buffer length - leave room for 0
                    size *=2;
                    buffer = (char*)realloc(buffer, size);
                }
            }while(c != EOF && c != '\n');
            buffer[pos] = 0;

        } while(c != EOF); 
        fclose(f);   
        getche();      
    }
    free(buffer);
}
//
void calender (void){//shamsi
SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE);
    int month, day;
    char *day_code;
    month=shamsimonth - 1;// 1 farvardin 98 5shanbe

    if(shamsimonth <= 6){//firs six month
        day=( (month*6)+shamsiday )%7;
    }
    if(shamsimonth > 6){
        day=( (6*31)+(month-6)*30+shamsiday )%7;
    }
    switch(day){
        case 0:{
            day_code="4Shanbe";
            break;
        }
        case 1:{
            day_code="5Shanbe";
            break;
        }
        case 2:{
            day_code="Jomeh";
            break;
        }
        case 3:{
            day_code="Shanbe";
            break;
        }
        case 4:{
            day_code="1Shanbe";
            break;
        }
        case 5:{
            day_code="2Shanbe";
            break;
        }
        case 6:{
            day_code="3Shanbe";
            break;
        }
    }
    printf("\n\n\t\t %02d / %02d / %02d \n\n\t\t",shamsiyear,shamsimonth,shamsiday);
    printf("\n\t\t    %s\n",day_code);
    printEventList(list, event_index,shamsiyear,shamsimonth,shamsiday);
    printTaskList(list_task, task_index,shamsiyear,shamsimonth,shamsiday);
}

char menu(void){

    putchar('\n');
	printf("Menu\n\n");
    printf("1. Shamsi schedule\n");
	printf("2. Miladi calender in one year\n");
	printf("3. Shamsi calender in one year\n");
    printf("4. Search event date\n");
    Sleep(2000);
    key=getchar();
    while (key == '\n'){
        key=getchar();
    }
    return key;
}

int main(void){
    menu();
    now_time_shamsi();
    shamsiyear=shamsi_now_year;//first time
    shamsimonth=shamsi_now_month;
    shamsiday=shamsi_now_day -1;
    system("cls");
    while(1){
        if(key == '1'){//tasks and events in shamsi calender 
            char press;
            while(press!='M'){

                putchar('\n');
                now_time_shamsi();//shamsi_now_year,shamsi_now_month,shamsi_now_day//TODAY
                calender();//shamsiyear,shamsimonth,shamsiday//CHANGE
                printf("\n");

                printf("+----------------------------------------------+\n");
                printf("\n\t(*) Press N  to go to next day.");
                printf("\n\t(*) Press P to go to previous day.");
                printf("\n\t(*) Press Y to go to next year.");
                printf("\n\t(*) Press E to show event list.");
                printf("\n\t(*) Press T to show task list.");
                printf("\n\t(*) Press S to search or jump to date.");
                printf("\n\t(*) Press M to show menu.");
                printf("\n\t(*) Press F for save to File.");
                printf("\n\t(*) Press L to load File\n.");
                printf("+----------------------------------------------+\n");
                Sleep(3000);
            
                press=getchar();
            
                switch(press){
                    case 'N':{//NEXT DAY
                        if(shamsimonth<=6){//31 days
                            if(shamsiday<31){
                                shamsiday++;
                            }
                            else{
                                shamsimonth++;
                                shamsiday=1;
                            }
                        }
                        else if(shamsimonth>6){//30 days
                            if(shamsiday<30){
                                shamsiday++;
                            }
                            else{
                                shamsimonth++;
                                shamsiday=1;
                            }
                        }   
                        break;
                    }

                    case 'P':{//previous day
                        shamsiday--;
                        if(shamsiday==0){
                            shamsimonth--;
                            if(shamsimonth<=6){
                                shamsiday=31;
                            }
                            else{
                                shamsiday=30;
                            }
                        }
                        break;
                    }

                    case 'M':{
                        menu();
                        break;
                    }
                    case 'S':{//SEARCH BY DATE
                        printf("Enter the year: ");
                        scanf("%d",&shamsiyear);
                        printf("Enter the month: ");
                        scanf("%d",&shamsimonth);
                        printf("Enter the day: ");
                        scanf("%d",&shamsiday);
                        break;
                    }
                    case 'L':{
                        char filename[20];
                        printf("%s", "| Please enter a \"filename.txt\": ");
                        scanf("%s",&filename);
                        loadList(filename, list);
                        break;
                    }
                    case 'Y':{//next year
                        shamsiyear++;
                        determine_shamsi_year(shamsiyear);//kabise year or not
                        break;
                    }
                    case'F':{
                        if ((event_index) + (task_index) == 0) {
                            puts("| You have no schedule!\n");
                        }
                        else {
                            printf("%s", "| Please enter a \"filename.txt\": ");
                            scanf("%20s",&file);
                            //fgets(file, FILENAME_MAX, stdin);
                            strtok(file, "\n");
                            saveList(file, list,list_task, event_index,task_index);
                        }
                        break;
                    }
                    case 'E':{//new-edit-delet-file
                        while (selection != 5) {
                            print_events(); // Print the event menu
                            printf("%s", "| Please select an option: ");
                            Sleep(3000);
                            fgets(temp, 21, stdin);
                            selection = atoi(temp); //string to int
                
                            switch (selection) {
                            
                                case 1:{ // New Event
                                    if (event_index + 1 >MAX_EVENTS) {
                                        printf("| You can have %d events at one time!\n\n",event_index);
                                        break;
                                    }
                                    sortInsert(list, &event_index, *newEvent(&list[event_index]));//memory
                                    break;
                                }
                                case 2:{ // Delete Event
                                    deleteEvent(list, &event_index);
                                    break;
                                }
                                case 3:{//edit event
                                    editevent(list,&event_index);
                                    break;
                                }
                                case 4:{ // Schedule
                                    printEventList(list,event_index,shamsiyear,shamsimonth,shamsiday);
                                    break;
                                }
                            
                                case 5: {// Exit
                                    puts("\n| Thank you!\n");
                                    break;
                                }
                                default: {// Error
                                    puts("\n| Error in selection\n");
                                    break;
                                }
                            }
                        }
                        system("cls");
                        break;
                    }

                    case 'T':{//task:new-edit-delet-DONE
                        while (selection != 6) {//out
                            print_tasks(); // Print the task menu
                            printf("%s", "| Please select an option: ");
                            Sleep(3000);
                            fgets(temp, 21, stdin);
                            selection = atoi(temp); //string to int
                
                            switch (selection) {
                            
                                case 1:{ // New Event
                                    if (task_index + 1 > MAX_EVENTS) {
                                        printf("| You can have %d tasks at one time!\n\n", task_index);
                                        break;
                                    }
                                    sortInsert_task(list_task, &task_index, *newTask(&list_task[task_index]));//memory
                                    break;
                                }
                                case 2:{ // Delete 
                                    deleteTask(list_task, &task_index);
                                    break;
                                }
                                case 3:{//edit
                                    edittask(list_task,&task_index);
                                    break;
                                }
                                case 4:{ // Schedule
                                    printTaskList(list_task,task_index,shamsiyear,shamsimonth,shamsiday);
                                    break;
                                }
                                case 5:{//done
                                    donetask(list_task,&task_index);
                                    break; 
                                }
                                case 6: {// Exit
                                    puts("\n| Thank you!\n");
                                    break;
                                }
                                default: {// Error
                                    puts("\n| Error in selection\n");
                                    break;
                                }
                            }
                        }
                        system("cls");
                    }
                }
                Sleep(1000);
                system("cls");
            }
            menu();
        }

        if(key == '2'){
            int miladi_year, daycode;
            now_time_miladi();
	        miladi_year = inputyear();
	        daycode = determine_miladi_daycode(miladi_year);
	        determine_miladi_year(miladi_year);
	        miladi_calendar(miladi_year, daycode);
	        printf("\n");
            menu();
        }

        if(key == '3'){
            int daycode,shamsi_year,miladi_year;
            now_time_shamsi();
            shamsi_year = inputyear();
            determine_shamsi_year(shamsi_year);//kabise or not
            miladi_year=shamsi_year+621;//convert to miladi year
            daycode =  determine_miladi_daycode(miladi_year);
            shamsi_calender(miladi_year,daycode);
            printf("\n");
            menu();
        }
        else if (key == '4'){//search event title
		    int i;
		    char searchevent[20];
		    printf("enter the title of the event that you search : ");
		    Sleep(1000);
		    scanf("%s", searchevent);

		    int isFound = -1;
		    for (i = 0; i < event_index; i++){
			    isFound += search(list[i], searchevent);
		    }
		    if (isFound == -1){
			    printf("This title of event doesn't exist.");
                Sleep(2000);
		        //getche();
            }
		    system("cls");
		    menu();
	    }
	    else{
		    system("cls");
		    menu();
	    }
    }
}