#include<stdio.h>
#include<string.h>
#include "cJSON.h"
#include <time.h>  
#include <stdlib.h>
#include <ctype.h>

char *s1,*s2,*s3;

char* add_s_no(int no)
{
	char *s="0";
	char temp[10];
	itoa(no,temp , 10); 
	static char studentNo[10];
	strcpy(studentNo, s);
	strcat(studentNo, temp);
	return studentNo;
	
}
char* add_d_no(int no)
{	
	char *s;
	if(no < 10)		s="D00";
	else 		s="D0";
	char temp[10];
	itoa(no,temp , 10); 
	static char studentNo[10];
	strcpy(studentNo, s);
	strcat(studentNo, temp);
	return studentNo;
}

int main(){
	
	FILE *fp; 
	fp = fopen( "input_data.txt", "w+" ); 
	
	cJSON * root = cJSON_CreateObject();
	cJSON * student = cJSON_CreateArray();
	cJSON * department = cJSON_CreateArray();
	//学生
	int students=300;
	int s_no=31502000;
	srand((unsigned)time(NULL));
	while(students > 0){	
	cJSON * applications_department_array = cJSON_CreateArray();
	cJSON * s_tags_array = cJSON_CreateArray();
	cJSON * free_time_array = cJSON_CreateArray();
	cJSON * next = cJSON_CreateObject();

	//free_time 	 
	int t1= rand()%4+2;
	int i;
	int free_time_flag[8][21] = {0};
	for(i=0;i<t1;i++){
		int t2=rand()%7+1;
		int t3=rand()%8;
		if(free_time_flag[t2][t3]==1){
			i--;
			continue;
		}
		else free_time_flag[t2][t3]=1;
		switch(t2){
			case 1: s1="Mon." ; break;
			case 2: s1="Tues." ; break;
			case 3: s1="Wed." ; break;
			case 4: s1="Thu." ; break;
			case 5: s1="Fri." ; break;
			case 6: s1="Sat." ; break;
			case 7: s1="Sun." ; break;
		}
		switch(t3){
			case 0: s2="8:00~10:00";break;
			case 1: s2="10:00~12:00";break;
			case 2: s2="12:00~14:00";break;
			case 3: s2="16:00~18:00";break;
			case 4: s2="17:00~19:00";break;
			case 5: s2="18:00~20:00";break;
			case 6: s2="19:00~21:00";break;
			case 7: s2="20:00~22:00";break;
		}
		s3 = (char*)malloc(strlen(s1) + strlen(s2) + 1);
		strcpy(s3, s1);
		strcat(s3, s2);
		cJSON_AddItemToArray(free_time_array, cJSON_CreateString(s3));
	}
	
	//student_no
	char* studentNo = add_s_no(s_no);
	
	//applications_department
	t1 = rand()%4 + 1 ;
	int applications_department_flag[20]={0};
	for(i=0;i<t1;i++){
		int t2=rand()%20+1;
		if(applications_department_flag[t2]==1){
			i--;
			continue;
		}
		else applications_department_flag[t2]=1;
		switch(t2){
			case 1: s1="D001" ;break;
			case 2: s1="D002" ;break;
			case 3: s1="D003" ;break;
			case 4: s1="D004" ;break;
			case 5: s1="D005" ;break;
			case 6: s1="D006" ;break;
			case 7: s1="D007" ;break;
			case 8: s1="D008" ;break;
			case 9: s1="D009" ;break;
			case 10: s1="D0010" ;break;
			case 11: s1="D0011" ;break;
			case 12: s1="D0012" ;break;
			case 13: s1="D0013" ;break;
			case 14: s1="D0014" ;break;
			case 15: s1="D0015" ;break;
			case 16: s1="D0016" ;break;
			case 17: s1="D0017" ;break;
			case 18: s1="D0018" ;break;
			case 19: s1="D0019" ;break;
			case 20: s1="D0020" ;break;
		}
		cJSON_AddItemToArray(applications_department_array, cJSON_CreateString(s1));
	}
	
	//tag
	t1 = rand()%7 + 2 ;	
	int tag_flag[9]={0};
	for(i=0;i<t1;i++){
		int t2=rand()%8+1;
		if(tag_flag[t2]==1){
			i--;
			continue;
		}
		else tag_flag[t2]=1;
		switch(t2){
			case 1: s1="reading" ;break;
			case 2: s1="film" ;break;
			case 3: s1="English" ;break;
			case 4: s1="music" ;break;
			case 5: s1="dance" ;break;
			case 6: s1="basketball" ;break;
			case 7: s1="chess" ;break;
			case 8: s1="programming" ;break;
		}
		cJSON_AddItemToArray(s_tags_array, cJSON_CreateString(s1));
	}
	s_no++;
	students--;
//	printf("%d",students);
	cJSON_AddItemToObject(next,"free_time",free_time_array);
	

	cJSON_AddItemToObject(next,"student_no",cJSON_CreateString(studentNo));
	
	cJSON_AddItemToObject(next,"applications_department",applications_department_array);
	cJSON_AddItemToObject(next,"tags",s_tags_array);
	cJSON_AddItemToArray(student, next);
	

}
	
	//部门

	int departments = 20,d_no=1;
	while(departments--)
{
	cJSON * d_tags_array = cJSON_CreateArray();
	cJSON * event_schedules_array = cJSON_CreateArray();
	cJSON * next =  cJSON_CreateObject();

	
	//event_schedules
	int t1= rand()%4+2;
	int i;
	int event_schedules_flag[8][21] = {0};
	for(i=0;i<t1;i++){
		int t2=rand()%7+1;
		int t3=rand()%5;
		if(event_schedules_flag[t2][t3]==1){
			i--;
			continue;
		}
		else event_schedules_flag[t2][t3]=1;
		switch(t2){
			case 1: s1="Mon." ; break;
			case 2: s1="Tues." ; break;
			case 3: s1="Wed." ; break;
			case 4: s1="Thu." ; break;
			case 5: s1="Fri." ; break;
			case 6: s1="Sat." ; break;
			case 7: s1="Sun." ; break;
		}
		switch(t3){
			case 0: s2="12:00~13:00";break;
			case 1: s2="13:00~14:00";break;
			case 2: s2="18:00~19:00";break;
			case 3: s2="19:00~20:00";break;
			case 4: s2="20:00~21:00";break;
		}
		s3 = (char*)malloc(strlen(s1) + strlen(s2) + 1);
		strcpy(s3, s1);
		strcat(s3, s2);
		cJSON_AddItemToArray(event_schedules_array, cJSON_CreateString(s3));
	}
	//member_limit
	
	
	//department_no
	char *departmentNo = add_d_no(d_no);
	
	//tags
	t1 = rand()%7 + 2 ;
	int tags_flag[9]={0};
	for(i=0;i<t1;i++){
		int t2=rand()%8+1;
		if(tags_flag[t2]==1){
			i--;
			continue;
		}
		else tags_flag[t2]=1;
		switch(t2){
			case 1: s1="reading" ;break;
			case 2: s1="film" ;break;
			case 3: s1="English" ;break;
			case 4: s1="music" ;break;
			case 5: s1="dance" ;break;
			case 6: s1="basketball" ;break;
			case 7: s1="chess" ;break;
			case 8: s1="programming" ;break;
		}
		cJSON_AddItemToArray(d_tags_array, cJSON_CreateString(s1));
	}
	d_no++;

	cJSON_AddItemToObject(next,"event_schedules",event_schedules_array);
	
	t1 = rand()%6 + 10;
	cJSON_AddItemToObject(next,"member_limit",cJSON_CreateNumber(t1));
	cJSON_AddItemToObject(next,"department_no",cJSON_CreateString(departmentNo));


	cJSON_AddItemToObject(next,"tags",d_tags_array);

	cJSON_AddItemToArray(department, next);

}
	cJSON_AddItemToObject(root, "students", student); 
	cJSON_AddItemToObject(root, "departments", department); 
//	printf("%s\n", cJSON_Print(root));
	
	 fprintf( fp, "%s\n", cJSON_Print(root) ); 
	 fclose(fp);
	 return 0;
}
