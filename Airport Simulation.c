/*
	PGA Coursework - Airport simulation
	Name    : #######
	ID      : #######
	File(s) : Airport Simulation.c
			  input.txt
	          output.txt
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
 

/* Structure*/
struct takeoff {
	char type;
	char id[8];
	int timeH;
	int timeM;
	int passengers;
	int queue;
	struct takeoff *next;
};

struct landing {
	char type;
	char id[8];
	int timeH;
	int timeM;
	int range;
	int fuel;
	int passengers;
	int queue;
	struct landing *next;
};



/* Functions Prototypes */
void createT(char type[2], char id[8], int timeH[3], int timeM[3], int passengers[4]);
void createL(char type[2], char id[8], int timeH[3], int timeM[3], int range[3], int fuel[3], int passengers[4]);
void status(char id[8]);

void decrement(void);
void increment(void);
void check(void);
void ticktock(void);
void checktime(void);

void read(void);
void print(void);
void write(void);
void printlist(void);
//void enqueue(void);
/////End of function prototype////


/* Global Variables/Definitions */
unsigned int first = 0;
struct takeoff *takeHead;
struct landing *landHead;
struct landing *inHead;
//struct landing *run0; //toberevised
//struct landing *run1; //toberevised

unsigned int timeHstart=22;
unsigned int timeMstart=30;

unsigned int landList=0;
unsigned int takeList=0;
///////End of Globals ////////////


/* Main Program */ //-----------------------------------------------------------
int main(){
	//Nullifying head pointers
	takeHead=NULL;
	landHead=NULL;
	inHead=NULL;
	
   	read(); //reading from input.txt *refer function*
   //	write();
		 
	while (timeHstart!=24){ //timer starts
	
		if (timeMstart<59){
			timeMstart++;
		}else{
			timeHstart++;
			timeMstart=0;
		}
		
		//printf("%d %.2d\n",timeHstart,timeMstart); //timestamps
		ticktock();
		checktime();
		write();
	}  
	
	if (landHead==NULL && takeHead==NULL){
		FILE *output;
		output = fopen("output.txt","a");
		printf("\nProgram ended successfully. No more planes in the list\n");
		fprintf(output,"\nProgram ended successfully. No more planes in the list\n");
		fclose(output);
	}
	return 0;
}
/////End of Main Program///// //-------------------------------------------------




/* Functions create takeoff list*/
void createT(char type[2], char id[8], int timeH[3], int timeM[3], int passengers[4]){
	struct takeoff *newplane;
	newplane = (struct takeoff*)malloc(sizeof(struct takeoff));
	newplane->type=type;
	strncpy(newplane->id,id,8);
	newplane->timeH=timeH;
	newplane->timeM=timeM;
	newplane->queue=0;
	newplane->passengers=passengers;
	takeList++;
	
	if (takeHead==NULL){
		newplane->next=NULL;
		takeHead=newplane;
		return;
	}else{
		struct takeoff *trav=takeHead; //traversing if head occupied
		while (trav->next!=NULL){
			trav=trav->next;
		}
		
		newplane->next=NULL;
		trav->next=newplane; //setting new pointer
		return;
	}
	
}
/////End of function create takeoff list///

/* Functions create landing list*/
void createL(char type[2], char id[8], int timeH[3], int timeM[3], int range[3], int fuel[3], int passengers[4]){
	struct landing *newplane;
	newplane = (struct landing*)malloc(sizeof(struct landing));
	newplane->type=type;
	strncpy(newplane->id,id,8);
	newplane->timeH=timeH;
	newplane->timeM=timeM;
	newplane->range=range;
	newplane->fuel=fuel;
	newplane->queue=0;
	newplane->passengers=passengers;
	landList++;
	
	if (landHead==NULL){
		newplane->next=NULL;
		landHead=newplane;
		return;
	}else{
		struct landing *trav=landHead; //traversing if head occupied
		while (trav->next!=NULL){
			trav=trav->next;
		}
		
		newplane->next=NULL;
		trav->next=newplane; //setting new pointer
		return;
	}
	
}
/////End of function create landing list///

/* Functions Status Request*/
void status(char id[8]){
	
	FILE *writetext;
	writetext=fopen("output.txt","a");
	
	int flagL,flagT;
	//check in landing list
	struct landing *checkS;
			checkS=landHead;
	if (landHead!=NULL){
		
		char idn[8];
		strcpy(idn,id);
		
		char idz[8];
		strcpy(idz,checkS->id);
		
		if (strcmp(idz,idn)==0){
			//	printf("item S found\n");
				printf("\nStatus: %s is in range and will land at %d:%.2d or later",checkS->id,checkS->timeH,checkS->timeM);
				printf("\nStatus: %s has %d minutes of fuel remaining",checkS->id,checkS->fuel);
				
				fprintf(writetext,"\nStatus: %s is in range and will land at %d:%.2d or later",checkS->id,checkS->timeH,checkS->timeM);
				fprintf(writetext,"\nStatus: %s has %d minutes of fuel remaining",checkS->id,checkS->fuel);
				flagL=1;
				return;
			}else{
			//	flagL=0;
			//	printf("\nError: %s is not in the system",checkS->id);
			//	fprintf(writetext,"\nError: %s is not in the system",checkS->id);
			while(checkS->next!=NULL){
				checkS=checkS->next;
			if (strcmp(idz,idn)==0){
			//	printf("item S found\n");
				printf("\nStatus: %s is in range and will land at %d:%.2d or later",checkS->id,checkS->timeH,checkS->timeM);
				printf("\nStatus: %s has %d minutes of fuel remaining",checkS->id,checkS->fuel);
				
				fprintf(writetext,"\nStatus: %s is in range and will land at %d:%.2d or later",checkS->id,checkS->timeH,checkS->timeM);
				fprintf(writetext,"\nStatus: %s has %d minutes of fuel remaining",checkS->id,checkS->fuel);
				flagL=1;
				return;
			}else{
				flagL=0;
			//	printf("\nError: %s is not in the system",checkS->id);
			//	fprintf(writetext,"\nError: %s is not in the system",checkS->id);
			}
		}
			}
		
	}
	
	
	//check in takeoff list
	struct takeoff *checkT;
	checkT=takeHead;
	if (takeHead!=NULL){
		
		
		char idm[8];
		strcpy(idm,id);
		
		char idy[8];
		strcpy(idy,checkT->id);

		if (strcmp(idy,idm)==0){
				printf("\nStatus: %s is queued to take off on runaway 1",checkT->id);
				fprintf(writetext,"\nStatus: %s is queued to take off on runaway 1",checkT->id);
				flagT=1;
				return;
			}else{
			//	printf("\nError: %s is not in the system",checkT->id);
			//	fprintf(writetext,"\nError: %s is not in the system",checkT->id);
			//	flagT=0;
				while(checkT->next!=NULL){
			checkT=checkT->next;
			if (strcmp(idy,idm)==0){
				printf("\nStatus: %s is queued to take off on runaway 1",checkT->id);
				fprintf(writetext,"\nStatus: %s is queued to take off on runaway 1",checkT->id);
				flagT=1;
			return;
			}else{
			//	printf("\nError: %s is not in the system",checkT->id);
			//	fprintf(writetext,"\nError: %s is not in the system",checkT->id);
				flagT=0;
			}
			}

	
		}
		
	}
		 

fclose(writetext);
}
/////End of function status request///

/* Functions decrement*/
void decrement(void){
	//>>>>this function decrement 2: (a) fuel (b) inrange
			struct landing *travD;
			travD=landHead;
	if (landHead!=NULL){	
 			landHead->fuel--;
 			landHead->range--;
			while(travD->next!=NULL){
				travD=travD->next;
				travD->fuel--;
				travD->range--;
				check();
			}
	}
		
}
/////End of function decrement///

/* Functions increment*/
void increment(void){
	//>>>this function increment time waited for (T)takeoff and (L)landing
			struct landing *travD;
			travD=landHead;
	if (landHead!=NULL){
 			landHead->queue++;
			while(travD->next!=NULL){
				travD=travD->next;
				travD->queue++;
				check();
			}
	}
	
			struct takeoff *travT;
			travT=takeHead;
	if (takeHead!=NULL){
			travT->queue++;
			while(travT->next!=NULL){
				travT=travT->next;
				travT->queue++;
				check();
			}	
	} 
	

}
/////End of function increment///

/* Functions check*/
void check(void){ 
	FILE *output1;
	output1 = fopen("output.txt","a");
	//>>>> this function checks for 2: (a) range (b) fuel [EMERGENCY CASE] (c) queue/time
		
	// landing queue
	struct landing *travL;
	travL=landHead;
	if (landHead!=NULL){ //do nothing if empty
	
			if (landHead->fuel==0 ^ landHead->range==0  ){
				printf("\n(E) Plane %s has landed at %d:%.2d on run0\n",landHead->id,timeHstart,timeMstart);
				printf("(E) Plane %s expected to land at %d:%.2d\n",landHead->id,landHead->timeH,landHead->timeM);
				
				fprintf(output1,"Plane %s with %d passengers made emergency landing at %d:%.2d\n",landHead->id,landHead->passengers,landHead->timeH,landHead->timeM);
				
					if (landHead->fuel==0){
						printf("Plane %s with %d passenger made emergency landing due to out of fuel\n",landHead->id,landHead->passengers);
						fprintf(output1,"Plane %s with %d passengers made emergency landing due to out of fuel\n",landHead->id,landHead->passengers);
			
					}else{
						printf("(E) Plane %s already in range\n",landHead->id);
						fprintf(output1,"(E) Plane %s already in range\n",landHead->id);
					}
				struct landing *tmp;
				tmp=landHead;
				landHead=NULL;
				free(tmp);
				fclose(output1);
				return;
			}
			
			while (travL->next->next!=NULL){
				travL=travL->next;
				if ( travL->next->fuel==0^travL->next->range==0 ){
				printf("\n(E) Plane %s has landed at %d:%.2d on run0\n",travL->next->id,timeHstart,timeMstart);
				printf("(E) Plane %s expected to land at %d:%.2d\n",travL->next->id,travL->next->timeH,travL->next->timeM);
			 
				fprintf(output1,"Plane %s with %d passengers made emergency landing at %d:%.2d\n",travL->next->id,travL->next->passengers,travL->next->timeH,travL->next->timeM);
				
			
				if (travL->next->fuel==0){
					printf("(E) Plane %s out of fuel\n",travL->next->id);
					fprintf(output1,"Plane %s with %d passengers made emergency landing due to out of fuel\n",travL->next->id,travL->next->passengers);
			
				}else{
					printf("(E) Plane %s already in range\n",travL->next->id);
					fprintf(output1,"(E) Plane %s already in range\n",travL->next->id);
				}
				
				struct landing *tmp2;
				tmp2=travL->next;
				travL->next=travL->next->next;
				free(tmp2);
	  		 	fclose(output1);
	  		 	return;
				}
			}
		
			
			
				//return;
				
		
	}
	//no emergency takeoff needed....
fclose(output1);	
}
/////End of function checkrange///

/* Functions ticktock*/   
void ticktock(void){ 
	//>>>> function that runs every minute
	
	if (landHead==NULL && takeHead==NULL){  //terminator: no more plane(s) in the list
		printf("\nProgram ended successfully. No more planes in the list\n");
		timeHstart=24;
	}else if(timeHstart==24){               //terminator: timeout
		printf("\nProgram ended successfully. Timeout\n");
	}else{
		decrement();
		increment();	
	}
}
/////End of function ticktock///

/* Functions checktime*/
void checktime(void){
	//landing list
	if (landHead==NULL){ 			  //case 0 item
		//do nothing
	}else if ( landHead->timeH==timeHstart && landHead->timeM==timeMstart) { 
									  //case 1 or more item
			printf("\nPlane %s has landed at %d:%.2d on Runaway 0\n",landHead->id,timeHstart,timeMstart);
			//write();
			struct landing *tmp;
			tmp=landHead;
			landHead=landHead->next;
			free(tmp);
	}
	
	//takeoff list
	if (takeHead==NULL){ 			  //case 0 item
		//do nothing
	}else if ( takeHead->timeH==timeHstart && takeHead->timeM==timeMstart) { 
									  //case 1 or more item
			printf("\nPlane %s has taken off at %d:%.2d on Runaway 1\n",takeHead->id,timeHstart,timeMstart);
			//write();
			struct takeoff *tmp2;
			tmp2=takeHead;
			takeHead=takeHead->next;
			free(tmp2);		
	}
	
	if (landHead==NULL && takeHead==NULL){
		timeHstart=24;
	}
}
/////End of function checktime///

/* Functions read*/
void read(void){
	FILE *inputfile;
	char line[27];
	inputfile = fopen("input.txt","r");
	
	if (inputfile != NULL){ //reading if the file exist
		while (fgets(line,27,inputfile)!=NULL){
			printf("%s",line);
			
			//determining either its (T)takeoff or (L)landing
			if (line[0]==84){ //case T
			 	//printf("T found\n");  
			 	char type[2]={line[0]};
			 	char id[8]= {line[2],line[3],line[4],line[5],line[6],line[7],line[8]};
			 	char idn[8];  
			 	strncpy(idn,id,8);
			 	char timeH[3]={line[10],line[11]};
			 	char timeM[3]={line[13],line[14]};
			 	char passengers[4]={line[16],line[17],line[18]};
			 	
			 	createT(84,idn,atoi(timeH),atoi(timeM),atoi(passengers));
			 	
			 	
			}else if (line[0]==76){  //case L
				//printf("\nL found\n"); //test
				char type[2]={line[0]};
			 	char id[8]= {line[2],line[3],line[4],line[5],line[6],line[7],line[8]};
			 	char idn[8];  
			 	strncpy(idn,id,8);
			 	char timeH[3]={line[10],line[11]};
			 	char timeM[3]={line[13],line[14]};
			 	char range[3]={line[16],line[17]};
			 	char fuel[3]={line[19],line[20]};
			 	char passengers[4]={line[22],line[23],line[24]};
			 	
			 	createL(76,idn,atoi(timeH),atoi(timeM),atoi(range),atoi(fuel),atoi(passengers));
			 	
			}else{ 					  //case else: S
			//	printf("\nS found\n"); //test
				char id[8]= {line[2],line[3],line[4],line[5],line[6],line[7],line[8]};
				char idn[8];  
			 strncpy(idn,id,8);
				status(idn);				
			}
		}
		print();
		fclose(inputfile);
    }
    
   
}
/////End of function read///

/* Functions print*/
void print(void){
	FILE *output;
	output = fopen("output.txt","a");
	
	//takeoff planes
	if (takeHead!=NULL){
		struct takeoff *trav;
		trav=takeHead;
		fprintf(output,"\nTYPE: %c Plane ID: %s TIME: %d.%.2d Passengers: %d -Enlisted",trav->type,trav->id,trav->timeH,trav->timeM,trav->passengers);
		//status(trav->id);
		while (trav->next!=NULL){
			trav=trav->next;
			fprintf(output,"\nTYPE: %c Plane ID: %s TIME: %d.%.2d Passengers: %d -Enlisted",trav->type,trav->id,trav->timeH,trav->timeM,trav->passengers);
		//	status(trav->id);			
		}
	}
	
	//landing planes
	if (landHead!=NULL){
		struct landing *travL;
		travL=landHead;
		fprintf(output,"\nTYPE: %c Plane ID: %s TIME: %d.%.2d InRange: %d Fuel unit: %d Passengers: %d -Enlisted",travL->type,travL->id,travL->timeH,travL->timeM,travL->range,travL->fuel,travL->passengers);
	//	status(travL->id);
		while (travL->next!=NULL){
			travL=travL->next;
			fprintf(output,"\nTYPE: %c Plane ID: %s TIME: %d.%.2d InRange: %d Fuel unit: %d Passengers: %d -Enlisted",travL->type,travL->id,travL->timeH,travL->timeM,travL->range,travL->fuel,travL->passengers);
		//	status(travL->id);
		}
	}
	printlist();
	fprintf(output,"\n\nAt start of time %d:%.2d\n",timeHstart,timeMstart);
	fclose(output);
	
}
/////End of function print///

 
/* Functions write*/
void write(void){
	
	//writing to file
	FILE *output;
	output = fopen("output.txt","a");
	
	fputs("\n\n---------------------------------------\n",output);
	fprintf(output,"%d %.2d\n\n",timeHstart,timeMstart); //timestamps
	
	fputs("Runaway 0\n",output);
	fputs("\tLanding queue:\n",output);  
		struct landing *ptr1;
		ptr1=landHead;
	if (landHead!=NULL){
		fputs("\n",output);
		fprintf(output,"\t\t%s in queue for %d minute(s)\n",ptr1->id,ptr1->queue);
		fprintf(output,"\t\t%d minute(s) of fuel remaining\n",ptr1->fuel);
		while (ptr1->next!=NULL){
			fputs("\n",output);
			fprintf(output,"\t\t%s in queue for %d minute(s)\n",ptr1->id,ptr1->queue);
			fprintf(output,"\t\t%d minute(s) of fuel remaining\n",ptr1->fuel);
			ptr1=ptr1->next;
		}
	}else{
		fputs("\t\t<empty>\n",output);
	}
	
	
	fputs("\n\nRunaway 1\n",output);
	fputs("\tTakeoff queue:\n",output);
		struct takeoff *ptr;
		ptr=takeHead;  
	if (takeHead!=NULL){
		fputs("\n",output);
		fprintf(output,"\t\t%s in queue for %d minute(s)\n",ptr->id,ptr->queue);
		while (ptr->next!=NULL){
			ptr=ptr->next;
			fputs("\n",output);
			fprintf(output,"\t\t%s in queue for %d minute(s)\n",ptr->id,ptr->queue);
		}	
	}else if (takeHead==NULL){
		fputs("\t\t<empty>\n",output);
	}
 
	fclose(output);
	
	//writing to console
	puts("\n\n---------------------------------------");
	printf("%d %.2d\n\n",timeHstart,timeMstart); //timestamps
	
	puts("Runaway 0\n");
	puts("\tLanding queue:\n");  
		struct landing *ptr2;
		ptr2=landHead;
	if (landHead!=NULL){
		puts("\n");
		printf("\t\t%s in queue for %d minute(s)\n",ptr2->id,ptr2->queue);
		printf("\t\t%d minute(s) of fuel remaining\n",ptr2->fuel);
		while (ptr2->next!=NULL){
			ptr2=ptr2->next;
			puts("\n");
			printf("\t\t%s in queue for %d minute(s)\n",ptr2->id,ptr2->queue);
			printf("\t\t%d minute(s) of fuel remaining\n",ptr2->fuel);
		}
	}else{
		puts("\t\t<empty>\n");
	}
	
	
	puts("\n\nRunaway 1\n");
	puts("\tTakeoff queue:\n"); 
		struct takeoff *ptr3;
		ptr3=takeHead; 
	if (takeHead!=NULL){
		puts("\n");
		printf("\t\t%s in queue for %d minute(s)\n",ptr3->id,ptr3->queue);
		while (ptr3->next!=NULL){
			puts("\n");
			ptr3=ptr3->next;
			printf("\t\t%s in queue for %d minute(s)\n",ptr3->id,ptr3->queue);
		}
	}else{
		puts("\t\t<empty>\n");
	}
}
/////End of function write///


/* Functions printlist*/
void printlist(void){
	if (landHead !=NULL && takeHead!=NULL){
		struct landing *ptrL;
		ptrL=landHead;
		status(ptrL->id);
		while (ptrL->next!=NULL){
			ptrL=ptrL->next;
			status(ptrL->id);
		}
		
		struct takeoff *ptrT;
		ptrT=takeHead;
		status(ptrT->id);
		while (ptrT->next!=NULL){
			ptrT=ptrT->next;
			status(ptrT->id);
		}
	}else{
		printf("\n Error: empty list!\n");
		FILE *err;
		err=fopen("output.txt","a");
		fprintf(err,"\nError: empty list!\n");
		fclose(err);
	}
}
/////End of function printlist///
 

//--------------------------------------------------------------
/* Functions x*/
/////End of function x///
//--------------------------------------------------------------



/* Functions enqueue 
void enqueue(void){
	/*  this function enqueue planes from takeoff list and landing list into run0/run1    
	
	//starts with sorting the planes in the list ASCENDING order of time
	struct takeoff *travT;
	travT=takeHead;
	int temp=23; 
	
	struct takeoff *temp;		//creates temporary node to store in between
	temp = (struct takeoff*)malloc(sizeof(struct takeoff));
	
	do {
		if (travT->timeH>temp) 
	}while();
	
} 
/////End of function enqueue///
  */
  
  
 /* Functions enqueue  
 void enqueue(void){
 	int tempH=23;
	
	struct landing *travL;
	struct takeoff *travT; 
	
	if (landHead==NULL && takeHead ==NULL){		//case BOTH list EMPTY
		printf("\nError: Empty List(s)\n");
		return;
	}else if(landHead==NULL && takeHead !=NULL){//case ONLY Takeoff list Exist
		travT=takeHead;
		while (travT->next!=NULL){
			struct landing *plane; //creating a new node
			plane = (struct landing*)malloc(sizeof(struct landing));
			plane->id=travT->id;
			plane->type=travT->type;
			plane->timeH=travT->timeH;
			plane->timeM=travT->timeM;
			plane->passengers=travT->passengers;
			
			if (travT->timeH<temp){ //if smaller, insert at beginning
				if (run0==NULL){ //case run0 is empty
					plane->next=NULL;
					run0=plane;
				}else{  //case run0 isnt empty
					plane->next=run0;
					run0=plane;
				}
				temp=travT->timeH; 
			}else{ 					//if bigger, insert at the end
				if (run0==NULL){
					
				}
			}
			travT=travT->next; //trav to next!!
		}
		return;
	}else if(landHead!=NULL && takeHead ==NULL){//case ONLY Landing list Exist
		return;
	}else{										//case BOTH list exist
		return;
	}
	
	
 	
 } 
 */
/////End of function enqueue///




