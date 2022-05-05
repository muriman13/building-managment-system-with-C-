#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct appartament {
int appnumber;
int numberofrooms;
int oldpeople;
int children;
char familyname [25];
char date [15];
int rent;
}appartament;

appartament **appartaments;


void print();
void memory_allcoation();
void add_new_resident(f);
void max_of_3floors();
void taxes();
void write_to_file(char name[]);
void read_from_file(char name[]);
void read_sizeof_block (char name[]);
void write_sizeof_block(char name[]);
void where(int f);
FILE * f;
FILE * sizee;


int count =0,blocktax=0;
int a=5,b=5;
int location =0;
char blockname [25]= "";
char sizeofblock [25] = "s";
int decide;
int temp1=0,temp2=0;
int main()
{
printf("\n1.create a block\n2. print residents\n3.kick out an resident\n4.calculate block tax\n5.best elevator possition\n6. save to file\n7. load from file\n8. add new resident if its free\n9. check who lives where\n10. close the program and clean\n");

    while (1){
            printf("what do you want to do : ");
                        scanf("%d", &decide);
        switch (decide){

    case 1:
        printf("enter floors and appartments per floor: ");
        scanf("%d%d",&a,&b);
        memory_allcoation(a,b);
        print(a,b);
        break;

    case 2:

        print(a,b);
        break;

    case 3:
        printf("enter room number: ");
        moveout(0);
        break;

    case 4:

        taxes();
        break;

    case 5:

        max_of_3floors();
        break;

    case 6:
        printf("enter block name: ");
        scanf("%s", blockname);
        write_to_file(blockname);
        strcat(sizeofblock,blockname);
        sizee = fopen(sizeofblock,"wb");
        if (sizee == NULL) {
    perror("Failed: ");
    return 1;
}
        fwrite(&a, sizeof(int), 1, sizee);
        fwrite(&b, sizeof(int), 1, sizee);
        sizeofblock[1]='\0';
        fclose(sizee);
        break;

    case 7:
        printf("enter block name: ");
        scanf("%s", blockname);
        strcat(sizeofblock,blockname);
        sizee = fopen(sizeofblock,"rb");
        if (sizee == NULL) {
    perror("Failed: ");
    return 1;
}
        fread(&a, sizeof(int), 1, sizee);
        fread(&b, sizeof(int), 1, sizee);
        fclose(sizee);
        read_from_file(blockname);
        sizeofblock[1]='\0';

        break;

    case 8:

        add_new_resident(0);
        break;
    case 9:
        printf("who lives at spesific appartment");
        where(0);
        clean();
        break;
    case 10:

        clean();
        return 0;
 default :
        break;

    }


}
return 0;
}

void print (int g, int h){
    int i, j;
    for (i = 0; i <  g; i++){
            printf("\n floor number %d:   ", i);
      for (j = 0; j < h; j++){
         printf("%d,%d   ", appartaments[i][j].oldpeople,appartaments[i][j].children);
      }
    }
        printf("\n");


}

void memory_allcoation(int g, int h){
time_t t;
srand((unsigned) time(&t));
appartaments=malloc(sizeof(appartament*)*g);  // zadelqm pamet za broy elemnti raven na broq na etajite
for(int e=0;e<g;e++){
appartaments[e]=malloc(sizeof(appartament)*h);
// zadelqm pamet za h broy elementi za vseki etaj
}


int i, j;
    for (i = 0; i <  g; i++){
      for (j = 0; j < h; j++){
          if(appartaments == NULL){
        printf("No memory alocated ");
        exit(1);
    }
         appartaments[i] [j].oldpeople= rand() % 5; // prosto si slagam random broy old people za testove
         appartaments[i] [j].children= rand() % 3;
         strcpy(appartaments[i] [j].familyname,"asd");
         strcpy(appartaments[i] [j].date,"12.12.2020");
         count+=1;
      }
    }

}



void add_new_resident(int f){
    int i,j;
int young,old,rent;
char fname [25];
char date [12];
printf("enter room to place people: ");
scanf("%d",&f);
if(appartaments[f/a][f%a].oldpeople>0){
    printf("the appartmant is taken.\n");
}
else {
        printf("enter number of old people: ");
    scanf("%d",&old);
if(old!=0){
    printf("enter number of ypung people: ");
    scanf("%d",&young);
}
    printf("family name: ");
    scanf("%s",fname);
    printf("date: ");
    scanf("%s",date);
    if(old==0){
            printf("no rent here");
        rent=0;
    }
    else{
    printf("rent:");
    scanf("%d",&rent);
    }

appartaments[f/a][f%a].children=young;
appartaments[f/a][f%a].oldpeople=old;
strcpy(appartaments[f/a][f%a].familyname,fname);
strcpy(appartaments[f/a][f%a].date,date);
appartaments[f/a][f%a].rent=rent;
 print(a,b);
}
      }


void taxes(){
    int i, j;
    for (i = 0; i <  a; i++){
      for (j = 0; j < b; j++){

         if (i<2){
        blocktax += appartaments[i][j].children + appartaments[i][j].oldpeople*3;
         }
         else {
            blocktax += appartaments[i] [j].children*3 + appartaments[i] [j].oldpeople*5;
         }
      }
    }
    printf("\n block taxs is : %d\n", blocktax);
    blocktax =0;
}

void max_of_3floors (){

    int i, j;
    int sum_of_floor=0;
    int counter=1;
    int max=0;
    int floor = 0;
    int temp=0;
    int tax=0;
    for (i = 1; i <  a-1; i++){
      for (j = 0; j < b; j++){
        tax += appartaments[i] [j].oldpeople + appartaments[i] [j].children + appartaments[(i-1)] [j].oldpeople+ appartaments[i-1] [j].children + appartaments[(i+1)] [j].oldpeople + appartaments[i+1] [j].children;
      }
      temp +=tax;
      if(max<temp){
        max = temp;
        floor = i;
      }

      temp=0;
      tax=0;
    }
    printf("\n max of near floors: %d \n elevator should stay on floor:  %d \n  ", max, floor);
    temp=0;
    tax=0;
    max=0;
}


void write_to_file(char name[])
{
int i,j;
f = fopen(name,"wb");
if (f == NULL) {
    perror("Failed: ");
    return 1;
}
for (i = 0; i <  a; i++){
      for (j = 0; j < b; j++){
fwrite(&appartaments[i][j], sizeof(struct appartament), 1, f);
      }
}

fclose(f);
}

void read_from_file(char name[])
{
int i,j;
f = fopen(name,"rb");
if (f == NULL) {
    perror("Failed: ");
    return 1;
}
appartaments=malloc(sizeof(appartament*)*b);
for(int e=0;e<a;e++) appartaments[e]=malloc(sizeof(appartament)*a);
for (i = 0; i <  a; i++){
      for (j = 0; j < b; j++){
fread(&appartaments[i][j], sizeof(struct appartament), 1, f);
printf("%d,%d   ", appartaments[i][j].oldpeople,appartaments[i][j].children);
      }
       printf("\n");
}
fclose(f);
}


void moveout(int f){
    scanf("%d",&f);
appartaments[f/a][f%a].oldpeople=0;
appartaments[f/a][f%a].children=0;
}

void where(int f){
    scanf("%d",&f);
    if(appartaments[f/a][f%a].oldpeople!=0){
printf("\nold people : %d\n",appartaments[f/a][f%a].oldpeople);
printf("young people: %d\n",appartaments[f/a][f%a].children);
printf("family name: %s\n",appartaments[f/a][f%a].familyname);
printf("date of entrance: %s\n",appartaments[f/a][f%a].date);
    }
    else{
        printf("appartament is empty \n");
    }
}

void clean (){
free(appartaments);
}





