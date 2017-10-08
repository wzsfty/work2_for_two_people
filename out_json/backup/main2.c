#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include "cJSON.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



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

int main(int argc, char *argv[]) {
	char *p;  
    char *fname="input_data.txt";  
    p=getfileall(fname);  
//    if (p!=NULL) puts(p);  
	
	
	cJSON *root = cJSON_Parse(p);    //将字符串解析成json结构体
if(!root) {  
    printf("get root faild !\n");  
    return -1;  
}  
cJSON *js_list = cJSON_GetObjectItem(root, "student");  
if(!js_list) {  
    printf("no list!\n");  
    return -1;  
}  

int array_size = cJSON_GetArraySize(js_list);  
printf("array size is %d\n",array_size);  
cJSON *item,*it, *student_no, *tags;  
int i,j;
for(i=0; i< array_size; i++) {  
    item = cJSON_GetArrayItem(js_list, i);  
    if(!item) {  
        //TODO...  
    }  
    char *t = cJSON_PrintUnformatted(item);  
    it = cJSON_Parse(t);  
    if(!it)  
        continue ;  
    
    cJSON *items;int k;
    items = cJSON_GetObjectItem(it, "free_time"); 
    int size = cJSON_GetArraySize(items); 
	printf("free_time size is %d\n",size);  
    for(k=0;k<size;k++){
    	 item = cJSON_GetArrayItem(items, k);  
    printf("%s\n",item->valuestring);  	
	}
	
	student_no = cJSON_GetObjectItem(it, "student_no");  
    printf("student_no is %s\n",student_no->valuestring);  
    
	
	items = cJSON_GetObjectItem(it, "applications_department"); 
    size = cJSON_GetArraySize(items); 
	printf("applications_department size is %d\n",size);  
    for(k=0;k<size;k++){
    	 item = cJSON_GetArrayItem(items, k);  
    printf("%s\n",item->valuestring);  	
	}
	
    items = cJSON_GetObjectItem(it, "tags"); 
    size = cJSON_GetArraySize(items); 
	printf("tags size is %d\n",size);  
    for(k=0;k<size;k++){
    	 item = cJSON_GetArrayItem(items, k);  
    printf("%s\n",item->valuestring);  	
	}

}  





	



	return 0;
}
