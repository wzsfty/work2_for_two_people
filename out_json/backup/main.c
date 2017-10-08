#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include "cJSON.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct student{
	char *free_time[10];
	char *student_no;
	char *applications_department[10];
	char *s_tag[10];
	int department;
}stu[300];


struct department{
	char *event_schedules[10];
	int member_limit;
	char *department_no;
	char *d_tag[10];
	char *member[300];
}dep[20];

int d_student[21][300];
int  applications_number[21]={0};


void printJson(cJSON * root)//以递归的方式打印json的最内层键值对
{	
	int i;
    for(i=0; i<cJSON_GetArraySize(root); i++)   //遍历最外层json键值对
    {
    	printf("%d\n",cJSON_GetArraySize(root));
        cJSON * item = cJSON_GetArrayItem(root, i);        
        if(cJSON_Object == item->type || cJSON_Array == item->type)      //如果对应键的值仍为cJSON_Object就递归调用printJson
            printJson(item);
        else                                //值不为json对象就直接打印出键和值
        {
            printf("%s->\n", item->string);
//            printf("%s\n", cJSON_Print(item));
        }
    }
}


char *getfileall(char *fname)  
{  
    FILE *fp;  
    char *str;  
    char txt[1000];  
    int filesize;  
    if ((fp=fopen(fname,"r"))==NULL){  
        printf("打开文件%s错误\n",fname);  
        return NULL;  
    }  
  
    fseek(fp,0,SEEK_END);   
  
    filesize = ftell(fp);  
    str=(char *)malloc(filesize);  
    str[0]=0;  
  
    rewind(fp);  
    while((fgets(txt,1000,fp))!=NULL){  
        strcat(str,txt);  
    }  
    fclose(fp);  
    return str;  
}  

int choose_student(){
	
	int i,j,k,m1=0,m2=0,n1=0,n2=0,tag_number[300]={0},t1,t2,d_member=0;
	for(i=1; i<21; i++){
		//标签兴趣匹配数 
//		printf("%d\n",applications_number[i]);
		for(j=1; j<=applications_number[i]; j++)
		{
			while(stu[d_student[i][j]].s_tag[m1] !=NULL){
//				printf("编号：%d\n",d_student[i][j]);
//				printf("%s\n",stu[d_student[i][j]].s_tag[m] );
				while(dep[i-1].d_tag[n1] !=NULL){
//					printf("%s\n",dep[i-1].d_tag[n]);
					if( strcmp(stu[d_student[i][j]].s_tag[m1], dep[i-1].d_tag[n1]) ==0 ){
						tag_number[j]++;						
					}
					
						n1++;
				}
				m1++;
				n1=0;
			}
			m1=0;	
		}
		
		
		int s_number=applications_number[i];
		while(1)
		{
			
		
		//找出标签数最大值 
		int max_number,max=-1;
		for(t1=1;t1<=applications_number[i];t1++)
		{
			if(max<tag_number[t1])
			{
				max = tag_number[t1];
				max_number = t1;
				
			}

		}
		tag_number[max_number] = -1;
		s_number--;
		
		char s_day[5],d_day[5];
		char time[9][3];
		int time2[9];
		int flag,t=0;
		//匹配时间
		while(stu[ d_student[i][max_number] ].free_time[m2] != NULL)
		{
//			printf("%d\n",strlen(stu[ d_student[i][max_number] ].free_time[m2]));
			//提取学生时间
			for(k=0; k<strlen(stu[ d_student[i][max_number] ].free_time[m2]) ; k++)
			{
				if( stu[ d_student[i][max_number] ].free_time[m2][k]=='.' )
				{
					strncpy(s_day,stu[d_student[i][max_number]].free_time[m2],k);
					flag = k;
				}
				
				if( stu[ d_student[i][max_number] ].free_time[m2][k]==':' )
				{
					t++;
					if(t==1)
					{
						if(k-flag==2)
						{
							strncpy(time[1],stu[d_student[i][max_number]].free_time[m2]+flag+1,1);
							time2[1]=atoi(time[1]);
						}
						else
						{
							strncpy(time[1],stu[d_student[i][max_number]].free_time[m2]+flag+1,2);
							time2[1]=atoi(time[1]);
						}
						strncpy(time[2],stu[d_student[i][max_number]].free_time[m2]+k+1,2);
						time2[2]=atoi(time[2]);
					}
					if(t==2)
					{
						if(k-flag==2)
						{
							strncpy(time[3],stu[d_student[i][max_number]].free_time[m2]+flag+1,1);
							time2[3]=atoi(time[3]);
						}
						else
						{		
							strncpy(time[3],stu[d_student[i][max_number]].free_time[m2]+flag+1,2);
							time2[3]=atoi(time[3]);
						}
						strncpy(time[4],stu[d_student[i][max_number]].free_time[m2]+k+1,2);
						time2[4]=atoi(time[4]);
						t=0;
					}					
				}
				
				if(stu[ d_student[i][max_number] ].free_time[m2][k]=='~' )
				{
					flag = k ;
				}
			} 
//			printf("%d %d %d %d \n",time2[1],time2[2],time2[3],time2[4]);
			
			//提取部门时间
			
//			printf("%s",dep[i].event_schedules[n2]); 
			while(dep[i].event_schedules[n2]!= NULL)
			{
				
			
					for(k=0; k<strlen(dep[i].event_schedules[n2]) ; k++)
					{
						if( dep[i].event_schedules[n2][k]=='.' )
						{
							strncpy(d_day,dep[i].event_schedules[n2],k);
							flag = k;
						}
						
						if( dep[i].event_schedules[n2][k]==':' )
						{
							t++;
							if(t==1)
							{
								if(k-flag==2)
								{
									strncpy(time[5],dep[i].event_schedules[n2]+flag+1,1);
									time2[5]=atoi(time[5]);
								}
								else
								{
									strncpy(time[5],dep[i].event_schedules[n2]+flag+1,2);
									time2[5]=atoi(time[5]);
								}
								strncpy(time[6],dep[i].event_schedules[n2]+k+1,2);
								time2[6]=atoi(time[6]);
							}
							if(t==2)
							{
								if(k-flag==2)
								{
									strncpy(time[7],dep[i].event_schedules[n2]+flag+1,1);
									time2[7]=atoi(time[7]);
								}
								else
								{		
									strncpy(time[7],dep[i].event_schedules[n2]+flag+1,2);
									time2[7]=atoi(time[7]);
								}
								strncpy(time[8],dep[i].event_schedules[n2]+k+1,2);
								time2[8]=atoi(time[8]);
								t=0;
							}					
						}
						
						if(dep[i].event_schedules[n2][k]=='~' )
						{
							flag = k ;
						}
					} 
					
//					printf("%d %d %d %d \n",time2[5],time2[6],time2[7],time2[8]);
					if(strcmp(s_day,d_day)==0)
					{
						if(time2[1]*60+time2[2]<= time2[5]*60+time2[6] &&  time2[3]*60+time2[4] <= time2[7]*60+time2[8] )
						{
							dep[i].member[d_member] = stu[d_student[i][max_number]].student_no;
							stu[d_student[i][max_number]].department=1;
							d_member++;
							
						}
					}
				n2++;
			}
			n2=0;
			m2++;
		} 
		m2=0;	
			if(d_member>dep[i].member_limit || s_number<1) 
			break;
		}
		d_member=0;	
	}	
	
}
int main(int argc, char *argv[]) {
	

	
	char *p;  
    char *fname="input_data.txt";  
    p=getfileall(fname);  
//    if (p!=NULL) puts(p);  
	int i = 0,j = 0; 
	
	for(i=0;i<300;i++)
	stu[i].department=0;
	
	cJSON *root_json = cJSON_Parse(p);    //将字符串解析成json结构体
	
    if (NULL == root_json)
    {
        printf("error:%s\n", cJSON_GetErrorPtr());
        cJSON_Delete(root_json);
        return;
    }
	
	//解析json中的 student
	cJSON *js_student = cJSON_GetObjectItem(root_json, "students");  
	int array_size = cJSON_GetArraySize(js_student); 
	 
	cJSON *item,*it, *student_no,*free_time,*applications_department,*s_tags;  
	char *q  = NULL;  
	for(i=0; i< array_size; i++) 
	{  
    	item = cJSON_GetArrayItem(js_student, i);  
    	q = cJSON_PrintUnformatted(item);  
    	it = cJSON_Parse(q);  
    	if(!it)  continue ;  
    	
    	//解析free_time 
	   	cJSON *js_free_time = cJSON_GetObjectItem(it, "free_time");
		int array_size = cJSON_GetArraySize(js_free_time);
//		printf("free_time :\n");
   		for(j=0;j<array_size;j++)
		{
    		free_time = cJSON_GetArrayItem(js_free_time, j); 
//    		printf("%s\n",free_time->valuestring);
			stu[i].free_time[j] = free_time->valuestring;
		}
		//解析 student_no
    	student_no = cJSON_GetObjectItem(it, "student_no");  
//    	printf("student_no :\n");  
//    	printf("%s\n",student_no->valuestring);
		stu[i].student_no = student_no->valuestring;
		

    	//解析applications_department
    	cJSON *js_applications_department = cJSON_GetObjectItem(it, "applications_department");
    	array_size = cJSON_GetArraySize(js_applications_department);
//    	printf("applications_department :\n");
   		for(j=0;j<array_size;j++)
		{
    		applications_department = cJSON_GetArrayItem(js_applications_department, j); 
//    		printf("%s\n",applications_department->valuestring);
			stu[i].applications_department[j] = applications_department->valuestring;
			char *temp = (char *)malloc(sizeof(char)*10) ;
			strcpy(temp,stu[i].applications_department[j]+2);
//			printf("%s",temp);return 0;
			applications_number[atoi(temp)]++; 
			d_student[atoi(temp)][applications_number[atoi(temp)]] = i;
		}
		//解析tags
		cJSON *js_tags = cJSON_GetObjectItem(it, "tags");
		array_size = cJSON_GetArraySize(js_tags);
//		printf("tags :\n");
		for(j=0;j<array_size;j++)
		{
    		s_tags = cJSON_GetArrayItem(js_tags, j); 
//    		printf("%s\n",s_tags->valuestring);
			stu[i].s_tag[j] = s_tags->valuestring;
		}
//		printf("*****************************************************************************************************\n");
  	}  
  	
//  	printf("%s\n",stu[0].s_tag[1]);return 0;
  	//解析json中的department
	cJSON *js_department = cJSON_GetObjectItem(root_json, "departments");  
	array_size = cJSON_GetArraySize(js_department);  
	cJSON *event_schedules,*member_limit,*department_no,*d_tags;  
	for(i=0; i< array_size; i++) 
	{
		item = cJSON_GetArrayItem(js_department, i);  
    	q = cJSON_PrintUnformatted(item);  
    	it = cJSON_Parse(q);  
    	if(!it)  continue ;  
    	
    	//解析 event_schedules
    	cJSON *js_event_schedules = cJSON_GetObjectItem(it, "event_schedules");
    	int array_size = cJSON_GetArraySize(js_event_schedules);
//    	printf("event_schedules :\n");
    	for(j=0;j<array_size;j++)
		{
    		event_schedules = cJSON_GetArrayItem(js_event_schedules, j); 
//    		printf("%s\n",event_schedules->valuestring);
			dep[i].event_schedules[j] = event_schedules->valuestring;
		}
		//解析 member_limit
		member_limit = cJSON_GetObjectItem(it, "member_limit"); 
//		printf("member_limit :\n");  
//    	printf("%d\n",member_limit->valueint);
		dep[i].member_limit = member_limit->valueint;


		//解析department_no
		department_no = cJSON_GetObjectItem(it, "department_no"); 
//		printf("department_no :\n"); 
//		printf("%s\n",department_no->valuestring); 
		dep[i].department_no = department_no->valuestring;
		//解析tags
		cJSON *js_tags = cJSON_GetObjectItem(it, "tags");
		array_size = cJSON_GetArraySize(js_tags);
//		printf("tags :\n");
		for(j=0;j<array_size;j++)
		{
    		d_tags = cJSON_GetArrayItem(js_tags, j); 
//    		printf("%s\n",d_tags->valuestring);
			dep[i].d_tag[j] = d_tags->valuestring;
		}
//		printf("*****************************************************************************************************\n");
	}
//	 	printf("%s\n",dep[0].d_tag[0]);



		
		choose_student();
//		for(i=0;i<300;i++)
//		{
//		if(stu[i].department==1)
//		{
//			printf("%s\n",stu[i].student_no);
//		}
//		}	
		//json 输出 
/*-----------------------------------------------------------------------------------------------------------*/
		cJSON * root = cJSON_CreateObject();
		cJSON * unluck_student = cJSON_CreateArray();
		cJSON * member = cJSON_CreateArray();
		cJSON * unlucky_department = cJSON_CreateArray();
		cJSON * admitted =  cJSON_CreateArray(); 
		for(i=0;i<300;i++)
		{
			if(stu[i].department != 1)
			{
				cJSON_AddItemToArray(unluck_student,cJSON_CreateString(stu[i].student_no));
//				printf("%s\n",stu[i].student_no);
			}
		}
		
		int dep_number=0,temp=0;
		for(i=0;i<20;i++)
		{
			cJSON * next = cJSON_CreateObject();
			cJSON * member = cJSON_CreateArray();
			cJSON * department_no1 = cJSON_CreateObject();
			while(dep[i].member[dep_number] != NULL)
			{
				cJSON_AddItemToArray(member,cJSON_CreateString(dep[i].member[dep_number]));
				dep_number++;
				temp++;
			}
			if(dep_number!=0)
			{	
				
				cJSON_AddItemToObject(next,"member",member);
				cJSON_AddItemToObject(next,"department_no",cJSON_CreateString(dep[i].department_no));
				
			}
			if(dep_number==0)
			{
				cJSON_AddItemToArray(unlucky_department,cJSON_CreateString(dep[i].department_no));
			}
			dep_number = 0;
			cJSON_AddItemToArray(admitted, next);
		}		
		cJSON_AddItemToObject(root,"unluck_student",unluck_student);
		cJSON_AddItemToObject(root,"admitted",admitted);
		cJSON_AddItemToObject(root,"unlucky_department",unlucky_department);
		
//		printf("%d",temp);

		printf("%s\n", cJSON_Print(root));
/*-----------------------------------------------------------------------------------------------------------*/

		
	return 0;
}
