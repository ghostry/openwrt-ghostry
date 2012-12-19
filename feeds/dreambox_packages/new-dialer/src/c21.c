/* MD5lib.h - md5 library
 */

/* Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All
rights reserved.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

/* The following makes MD default to MD5 if it has not already been
  defined with C compiler flags.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "md5.h"
#include "getPIN.h"
#define MD 5

/* Digests a string and prints the result.
 */
char* MDString (char *string)
 
{
  MD5_CTX context;
  unsigned char digest[16];
  char output1[32];
 static  char output[33]={""};
  unsigned int len = strlen (string);
  int i;
  MD5Init (&context);
  MD5Update (&context, (unsigned char*)string, len);
  MD5Final (digest, &context);

  for (i = 0; i < 16; i++)
 {sprintf(&(output1[2*i]),"%02x",(unsigned char)digest[i]);
  sprintf(&(output1[2*i+1]),"%02x",(unsigned char)(digest[i]<<4));
  }
  for(i=0;i<32;i++)
  output[i]=output1[i];
//  printf("%s",output);
  return output;
}

  
/* Digests a file and prints the result.
 */
char* MDFile (char *filename)
 
{ static char output[33]={""};
  FILE *file;
  MD5_CTX context;
  int len;
  unsigned char buffer[1024], digest[16];
  int i;
  char output1[32];
  if ((file = fopen (filename, "rb")) == NULL)
   { printf ("%s can't be openedn", filename);
    return 0;
   }
  else {
       MD5Init (&context);
     while (len = fread (buffer, 1, 1024, file))
       MD5Update (&context, buffer, len);
    MD5Final (digest, &context);
    fclose (file);
    for (i = 0; i < 16; i++)
     {sprintf(&(output1[2*i]),"%02x",(unsigned char)digest[i]);
        sprintf(&(output1[2*i+1]),"%02x",(unsigned char)(digest[i]<<4));
          }
        for(i=0;i<32;i++)
       output[i]=output1[i];
        return output;
       }
}

char* hmac_md5(char* text,char*  key)
{
        char   digest[16];
        char   output1[32];
         static char output[33]={""};
        MD5_CTX context;
        unsigned char k_ipad[65];    /* inner padding -
                                      * key XORd with ipad
                                      */
        unsigned char k_opad[65];    /* outer padding -
                                      * key XORd with opad
                                      */
        unsigned char tk[16];
        int i;
        int text_len = strlen (text);
        int key_len=strlen(key);
        /* if key is longer than 64 bytes reset it to key=MD5(key) */
        if (key_len > 64) {

                MD5_CTX      tctx;

                MD5Init(&tctx);
                MD5Update(&tctx,(unsigned char*) key, key_len);
                MD5Final(tk, &tctx);

                key = (char*)tk;
                key_len = 16;
        }

        /*
         * the HMAC_MD5 transform looks like:
         *
         * MD5(K XOR opad, MD5(K XOR ipad, text))
         *
         * where K is an n byte key
         * ipad is the byte 0x36 repeated 64 times
         * opad is the byte 0x5c repeated 64 times
         * and text is the data being protected
         */

        /* start out by storing key in pads */
        
        /*bzero( k_ipad, sizeof k_ipad);
          bzero( k_opad, sizeof k_opad);
        */

        for(i=0;i<65;i++)
        k_ipad[i]=(unsigned char)0;
        for(i=0;i<65;i++)
        k_opad[i]=(unsigned char)0;

        /*bcopy( key, k_ipad, key_len);
          bcopy( key, k_opad, key_len);
         */
         for(i=0;i<key_len;i++)
        {k_ipad[i]=(unsigned char)key[i];
         k_opad[i]=(unsigned char)key[i];
         }

        /* XOR key with ipad and opad values */
        for (i=0; i<64; i++) {
                k_ipad[i] ^= 0x36;
                k_opad[i] ^= 0x5c;
        }
        /*
         * perform inner MD5
         */
        MD5Init(&context);                   /* init context for 1st

                                              * pass */
        MD5Update(&context, k_ipad, 64);      /* start with inner pad */
        MD5Update(&context, (unsigned char*)text, text_len); /* then text of datagram 

*/
        MD5Final((unsigned char*)digest, &context);          /* finish up 1st pass */
        /*
         * perform outer MD5
         */
        MD5Init(&context);                   /* init context for 2nd
                                              * pass */
        MD5Update(&context, k_opad, 64);     /* start with outer pad */
        MD5Update(&context,(unsigned char*) digest, 16);     /* then results of 1st
                                              * hash */
        MD5Final((unsigned char*)digest, &context);          /* finish up 2nd pass */
        for (i = 0; i < 16; i++)
        {sprintf(&(output1[2*i]),"%02x",(unsigned char)digest[i]);
         sprintf(&(output1[2*i+1]),"%02x",(unsigned char)(digest[i]<<4));
          }
        for(i=0;i<32;i++)
        output[i]=output1[i]; 
        return output;     
}

int CutStr(char x[],int len)
{
	x[len]=0;
	return 1;
}

/*为嵌入式设备设置的随机数产生式*/
int hexnum2(char dst[])
{
	FILE *fp;
	char x[300],x1[129],md[33];
	unsigned int hex;
	fp=fopen("/dev/urandom","r");
	if(fp==NULL)
		return 0;
	fread(x,128,1,fp);
	x[128]=0;
	fclose(fp);

	strcpy(md,MDString(x));
	CutStr(md,8);
	sscanf(md,"%x",&hex);
	usleep(hex%100000);

	fp=fopen("/dev/urandom","r");
	fread(x1,128,1,fp);
	x1[128]=0;
	fclose(fp);

	strcat(x,x1);
	strcpy(x,MDString(x));
	CutStr(x,8);
	sscanf(x,"%x",&hex);
	while(hex<0x40000000)
	{
		hex+=0x1000000;
	}
	while(hex>0x50000000)
	{
		hex-=0x1000000;
	}
	
	sprintf(dst,"%x",hex);
	return 1;
}

void hexnum(char dst[])
{
	if(!hexnum2(dst))
		sprintf(dst,"%x",time(0));
} 

int UCase(char in[])
{
	int i;
	for(i=0;in[i];i++)
		if(in[i]>='a' && in[i]<='z')
			in[i]-=32;
	return 1;
}

int covacc(char usr[],char pwd[],char dst[])
{
	UCase(usr);
	char str[100],hex[10];
	hexnum(hex);
	strcat(str,"jepyid");
	strcat(str,usr);
	strcat(str,hex);
	strcat(str,pwd);
	strcpy(str,MDString(str));
	CutStr(str,20);
	strcat(dst,"~ghca");
	strcat(dst,hex);
	strcat(dst,"2007");
	strcat(dst,str);
	strcat(dst,usr);
	return 0;
}

int main(int argc,char * argv[])
{
	
	char final[100]="";
	char acc[52],pwd[52];
	switch(argc)
	{
		case 1:
		{
			puts("Welcome!!!");
			puts("Use in this way:");
			printf("%s",argv[0]);
			puts(" account password [mode]");
			puts("1.ghca\n2.shanxun.");
			return -1;
		}break;
		case 2:
		{
			if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0)
			{
				puts("Welcome!!!");
				puts("Use in this way:");
				printf("%s",argv[0]);
				puts(" account password [mode]");
				puts("1.ghca\n2.shanxun.");
				return -1;
			}
			printf("%s\n",argv[1]);
		}break;
		case 3:
		{
			printf("%s\n",argv[1]);
		}break;
		case 4:
		{
			if(strcmp(argv[3],"0")==0)
				printf("%s\n",argv[1]);
			if(strcmp(argv[3],"1")==0)
			{
				strcpy(acc,argv[1]);
				strcpy(pwd,argv[2]);
				covacc(acc,pwd,final);
				printf("%s\n",final);
			}
			if(strcmp(argv[3],"2")==0)
			{
				byte *userName = (byte *)(argv[1]);
				byte PIN[30] = {0};
				getPIN(userName,PIN);
				printf("%s\n",PIN+2);
			}
		}break;
		default:break;;
	}
//	byte *userName1 = "057400000000@ND.XY";
//	byte PIN[30] = {0};
//	getPIN(userName1,PIN);
//	printf("%s",PIN);
	return 0;
}
