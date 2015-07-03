#include "curl.h"
#include "curl_mgr.h"

#define POSTURL "http://www.xiami.com/member/login"  
#define POSTFIELDS "email=myemail@163.com&password=mypassword&autologin=1&submit=µÇ Â¼&type="  
#define FILENAME "curlposttest.log"


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);   

bool curlmgr_post()
{
	CURL *curl;  
	CURLcode res;   
    FILE *fptr;   
    struct curl_slist *http_header = NULL;   
  
    if ((fptr = fopen(FILENAME, "w")) == NULL) {   
        fprintf(stderr, "fopen file error: %s\n", FILENAME);   
        exit(1);   
    }  
	
	curl = curl_easy_init();  
	
	curl_easy_setopt(curl, CURLOPT_PROXY, "localhost:8888"); 
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);
/*
    curl_easy_setopt(curl, CURLOPT_URL, POSTURL);  
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTFIELDS);  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);  
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fptr);  
    curl_easy_setopt(curl, CURLOPT_POST, 1);  
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);  
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);  
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "curlposttest.cookie");  
    res = curl_easy_perform(curl);  
    */
	
	CURLcode code;
    CURLFORMcode formCode;
    long retcode = 0;
    long flen;
    char *slen;
	struct curl_httppost *post=NULL;
	struct curl_httppost *last=NULL;
	curl_easy_setopt(curl,CURLOPT_URL,"http://salmon.test.ucweb.local/api/mock/upload/1");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);  
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fptr);  
 
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "key",CURLFORM_COPYCONTENTS, "mykey",CURLFORM_END);
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "parentId", CURLFORM_COPYCONTENTS, "-1",CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "Filename", CURLFORM_FILE, "c:\\a.txt" , CURLFORM_END);   
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "fileLength",CURLFORM_COPYCONTENTS, "20",CURLFORM_END);
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "file",CURLFORM_COPYCONTENTS, "file",CURLFORM_END);
    curl_formadd(&post, &last, CURLFORM_COPYNAME, "submit",CURLFORM_COPYCONTENTS, "submit",CURLFORM_END);
             
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
         
    code=curl_easy_perform(curl);
	
	curl_easy_cleanup(curl);

	return true;
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {   
    FILE *fptr = (FILE*)userp;   
    return fwrite(buffer, size, nmemb, fptr);   
}  

