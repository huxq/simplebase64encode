#include<stdio.h>
#include<stdlib.h>
#include<string.h>


const char base64_map[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

size_t b64_length(size_t len)
{
    int pri = len/3;
    int plus = len%3;
    if(plus)
    {
        pri++;
    }
    return pri*4;
}


void b64_encode(const void * src, size_t len, void * dst)
{
    char *source=(char*)src;
    char *dest=(char*)dst;
    dest[b64_length(len)]='\0';
    if( len > 0 && src != NULL)
    {
        if(len == 0)
        {
            dst = NULL;
        }else
        {
            register unsigned int i = 0, j=0;
            for(i=0,j=0;i<len;i=i+3,j=j+4)
            {

               switch((((len-i)/3)>0 ? 0: len%3))
               {   
                   case 0:
                   dest[j] = base64_map[(source[i]&0xFC)>>2];
                   dest[j+1] = base64_map[((source[i]&0x3)<<4)|
                                         ((source[i+1]&0xF0)>>4)];
                   dest[j+2] = base64_map[((source[i+1]&0x0F)<<2)|
                                         ((source[i+2]&0xC0)>>6)];
                   dest[j+3] = base64_map[(source[i+2]&0x3F)];
                   break;
                   case 1:
                   dest[j] = base64_map[(source[i]&0xFC)>>2];
                   dest[j+1] = base64_map[((source[i]&0x3)<<4)];
                   dest[j+2] = '=';
                   dest[j+3] = '=';
                   break;
                   case 2:
                   dest[j] = base64_map[(source[i]&0xFC)>>2];
                   dest[j+1] = base64_map[((source[i]&0x3)<<4)|
                                         ((source[i+1]&0xF0)>>4)];
                   dest[j+2] = base64_map[((source[i+1]&0x0F)<<2)];
                   dest[j+3] = '=';
                   break;
               }
           
            }
        }
    }
}


int main()
{
    char *dst; 
    char src_string[1024];   
    while(1) {
        printf("\nInput source to convert to base64 encode:");
        scanf("%s",src_string);   
        dst = (char*)malloc( b64_length(strlen(src_string))+1);   
        if(dst == NULL)   
        b64_encode(src_string,strlen(src_string),dst);   
        printf("Encoded string is [%s]\n",dst);   
        free(dst);   
    }   
   
    getchar();   
   

}


