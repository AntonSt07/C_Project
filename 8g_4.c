#include <stdio.h>
#include <string.h>

#define maxbrp 20
int countSt = 0;
typedef struct{
    char name[30];
    int num;
    int marks[maxbrp];
    int maxMarks;
    float avr;
} Tstudent;

void mywrite(char *filename);
void myread(char *filename);
void myadd(char *filename);
void schoolership(char *filename);
void myexam(char *filename);
void mydelete(char *filename);
void myredact(char *filename);//redaktirane na zpis

int main(void)
{
    int op;
    char filename[80];
    printf("\nFile name:");
    scanf("%s",filename);
    do{
    printf("\n1. Zapis");
    printf("\n2. Read");
    printf("\n3. Add");
    printf("\n4. Change file");
    printf("\n5. See who will get scholarship");
    printf("\n6. Edit information of student");
    printf("\n7. Delete student info");
    printf("\n8. See who will have corrective exam");
    //printf("\n6. See who will have corrective exam");
    printf("\n9. Exit\n");
    scanf("%d",&op);
    switch(op)
    {
        case 1: mywrite(filename);break;
        case 2: myread(filename); break;
        case 3: myadd(filename); break;
        case 4: printf("Filename:"); scanf("%s",filename);break;
        case 5: schoolership(filename); break;
        case 6: myredact(filename); break;
        case 7: mydelete(filename); break;
        case 8: myexam(filename); break;
        //case 6: myexam(filename); break;
        case 9: printf("\n5.");break;
        default: printf("\nIncorrect choice!");break;
    }


    }while(op!=9);
}


void mywrite(char *filename)
{
    int count=0;
    FILE *f;
    Tstudent s;
    int i;
    char *p;
    int n = 0;
    char yes='y';
    if(f=fopen(filename,"r"))
    {
        fclose(f);
        printf("File exists! Overwrite? y/n:");
        getchar();
        scanf("%c",&yes);
    }
    if(yes!='y')return;

    if(f=fopen(filename,"w"))
    {
        do
        {
            printf("Num (0-end):");scanf("%d",&s.num);
            if(s.num==0)break;
            else countSt++;//IMPORTANT
            
            getchar();
            printf("Name: ");
            fgets(s.name,29,stdin);
            if(p=strchr(s.name,'\n'))*p='\0';
            s.avr=0;
            for(i=0;i<maxbrp;i++)
            {
                printf("Mark (0-end):");scanf("%d",&s.marks[i]);
                if(s.marks[i]==0)break;
                s.avr+=s.marks[i];

            
            }
            if(i)s.avr=s.avr/i;
            fwrite(&s,sizeof(s),1,f);
            count++;
        }while(1);

        fclose(f);
    }
    else printf("Error opening file for writing!");

}

void myread(char *filename){
    FILE *f;//FILE- tip danni ot 
    Tstudent s;
    int i;
    if(f=fopen(filename,"r"))
    {
        while(!feof(f))
        {
            if(fread(&s,sizeof(s),1,f))
            {
              
                printf("\n%2d %-30s",s.num,s.name);
                for(i = 0;i < maxbrp;i++){
                  if(s.marks[i] == 0){
                    break;
                  }
                  printf("%2d",s.marks[i]);
                }
                printf("%6.2f",s.avr);
              
            }
        }
        fclose(f);
    }
    else printf("Error opening file for reading!");

}



void myadd(char *filename)
{
  int count = 0;
    FILE *f;
    Tstudent s;
    int i;
    char *p;

    if(f=fopen(filename,"r+"))
    {
    while(!feof(f))
    {
        fread(&s,sizeof(s),1,f);
    }

    do
    {
        printf("Num (0-end):");scanf("%d",&s.num);
        if(s.num==0)break;
        getchar();
        printf("Name: ");
        fgets(s.name,29,stdin);
        if(p=strchr(s.name,'\n'))*p='\0';
        s.avr=0;
        for(i=0;i<maxbrp;i++)
        {
        printf("Mark (0-end):");scanf("%d",&s.marks[i]);
        if(s.marks[i]==0)break;
        s.avr+=s.marks[i];
        //arr[]
        }
        if(i)s.avr=s.avr/i;
        fwrite(&s,sizeof(s),1,f);
    }while(1);

    fclose(f);
    }
    else printf("Error opening file for reading!");
}


void schoolership(char *filename){
    FILE *f;
    Tstudent s;
    int i;
    if(f=fopen(filename,"r"))
    {
        while(!feof(f))
        {
            if(fread(&s,sizeof(s),1,f))
            {
              if(s.avr >= 5.50){
                printf("\n%s", s.name);
              } 
            }
        }
        fclose(f);
    }
    else printf("Error opening file for reading!");
}


void myexam(char *filename){
    FILE *f;
    Tstudent s;
    int i;
    if(f=fopen(filename,"r"))
    {
        while(!feof(f))
        {
            if(fread(&s,sizeof(s),1,f))
            {
                int br2 = 0;
                printf("\n%2d %-30s",s.num,s.name);
                for(i=0;i<maxbrp;i++)
                {
                    if(s.marks[i]==0)break;
                    if(s.marks[i] == 2){
                        br2++;
                        break;
                    }
                    if(br2){
                        printf("\n%2d %-30s",s.num,s.name);
                        for(i=0;i<maxbrp;i++)
                        {
                            if(s.marks[i]==0)break;
                            printf("%2d", s.marks[i]);
                        }
                        printf("%6.2f",s.avr);
                    }
                }
            }
        }
        fclose(f);
    }
    else printf("Error opening file for reading!");
}

void mydelete(char *filename){
    FILE *f, *fpom;
int num;
Tstudent s;

printf("Num:");scanf("%d",&num);

if(!(f=fopen(filename,"r")))
{printf("ERROR");return;}

if(!(fpom=fopen("temp.tmp","w")))
{fclose(f);printf("ERROR");return;}


while(!feof(f))
{
if(fread(&s,sizeof(s),1,f))
if(s.num!=num)
fwrite(&s,sizeof(s),1,fpom);
}
fclose(f);fclose(fpom);

if(!(f=fopen(filename,"w")))
{printf("ERROR");return;}

if(!(fpom=fopen("temp.tmp","r")))
{fclose(f);printf("ERROR");return;}

while(!feof(fpom))
{
if(fread(&s,sizeof(s),1,fpom))
fwrite(&s,sizeof(s),1,f);
}
fclose(f);fclose(fpom);

}

void myredact(char *filename){
    FILE *f, *fpom;
int num, i =0;
char *p;
Tstudent s;

printf("Num:");scanf("%d",&num);

if(!(f=fopen(filename,"r")))
{printf("ERROR");return;}

if(!(fpom=fopen("temp.tmp","w")))
{fclose(f);printf("ERROR");return;}


while(!feof(f))
{
if(fread(&s,sizeof(s),1,f))
if(s.num!=num)
fwrite(&s,sizeof(s),1,fpom);
}
fclose(f);fclose(fpom);

if(!(f=fopen(filename,"w")))
{printf("ERROR");return;}

if(!(fpom=fopen("temp.tmp","r")))
{fclose(f);printf("ERROR");return;}

while(!feof(fpom))
{
if(fread(&s,sizeof(s),1,fpom))
fwrite(&s,sizeof(s),1,f);
}
fclose(f);fclose(fpom);
    
    



    if(f=fopen(filename,"r+"))
    {
    while(!feof(f))
    {
        fread(&s,sizeof(s),1,f);
    }

    do
    {
        printf("Num (0-end):");scanf("%d",&s.num);
        if(s.num==0)break;
        getchar();
        printf("Name: ");
        fgets(s.name,29,stdin);
        if(p=strchr(s.name,'\n'))*p='\0';
        s.avr=0;
        for(i=0;i<maxbrp;i++)
        {
        printf("Mark (0-end):");scanf("%d",&s.marks[i]);
        if(s.marks[i]==0)break;
        s.avr+=s.marks[i];
        }
        if(i)s.avr=s.avr/i;
        fwrite(&s,sizeof(s),1,f);
    }while(1);

    fclose(f);
    }
    else printf("Error opening file for reading!");
}
