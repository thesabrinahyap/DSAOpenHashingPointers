#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "OpenHashingPointers.h"

#define EMPTY 0
//Helper Functions
List createNode(StudentType S){
	List node = malloc(sizeof(SType));
	node->student = S;
	node->link = NULL;
	
	return node;
}
NameType addName (String fname, String mname, String lname){
	NameType name;
	
	strcpy(name.FName, fname);
	strcpy(name.MName, mname);
	strcpy(name.LName, lname);
	
	return name;
}

void initDictionary (Dictionary *D, int size){
	D->students = malloc(sizeof(List) * size);
	D->count = 0;
	D->max = size;

	int ctr;
	for(ctr = 0;ctr<D->max;++ctr){
		D->students[ctr] = NULL;
	}
}
int hash (String LastName, int size){
	return (toupper(LastName[0])-'A') % size;
}
Date addDate(int day, int month, int year){
	Date d;
	
	d.day = day;
	d.month = month;
	d.year = year;
	
	return d;
}
StudentType addStudent(String ID, NameType Name, char sex,  Date birthdate, String program, int year){
	StudentType s;
	
	strcpy(s.studID, ID);
	s.studName = Name;
	s.sex = sex;
	s.birthDate = birthdate;
	strcpy(s.program, program);
	s.year = year;
	
	return s;
}
bool addElement(Dictionary *D, StudentType S){
	List temp = createNode(S);
	int hashValue = hash(S.studName.LName, D->max); 

	List* trav = &D->students[hashValue];
	while((*trav)!= NULL && strcmp((*trav)->student.studID, S.studID)<0){
		trav = &(*trav)->link;
	}
	temp->link = *trav;
	*trav = temp;
	D->count++;
	
	return true;	
}

bool deleteElement(Dictionary *D, StudentType S){
	
	int hashValue = hash(S.studName.LName, D->max);
	List *trav = &D->students[hashValue], temp;
	
	while((*trav)!= NULL && strcmp((*trav)->student.studID, S.studID)<0){
		trav = &(*trav)->link;
	}
	if((*trav)!= NULL && strcmp((*trav)->student.studID, S.studID)==0){
		temp = *trav;
		*trav = temp->link;
		free(temp);
	}
	
	D->count--;
	return true;
}
bool searchElement(Dictionary D, StudentType S){
	bool flag = false;
	int hashValue = hash(S.studName.LName, D.max);
	List trav = D.students[hashValue];
	
	while(trav != NULL){
		if(strcmp(trav->student.studID, S.studID) == 0){
			flag = true;
			break;
		}
		trav = trav->link;
	}
	return flag;
}
//void displayStudents (Dictionary D){
//	int x = 0;
//	SType *trav;
//	while(x<size){
//		trav = &D.students[x];
//		x++;
//	}
//	
//	printf("\n%10s | %15s | %10s | %10s | %s | %2s | %2s | %4s | %5s | %4s\n", 
//	       "ID NUMBER", "FIRST NAME", "MIDDLE NAME", "LAST NAME", "SEX", 
//		   "BIRTH MONTH", "BIRTH DAY", "BIRTH YEAR", "PROGRAM", "YEAR");
//	printf("-------------------------------------------------------------------------------------------\n");
//	
//	while(trav != NULL){
//		printf("%10s",trav->student.studID);
//		printf("%15s",trav->student.studName.FName);
//		printf("%10s",trav->student.studName.MName);
//		printf("%10s",trav->student.studName.LName);
//		printf("%4c",trav->student.sex);
//		printf("%4d", trav->student.birthDate.month);
//		printf("%4d", trav->student.birthDate.day);
//		printf("%4d", trav->student.birthDate.year);
//		printf("%5s", trav->student.program);
//		printf("%4d", trav->student.year);
//		
//		trav = trav->link;
//		printf("\n");
//	}
//	printf("\n\n");
//}
void visualizeStudents (Dictionary D){
//	String month;
	int x = 0;
	SType *trav;
	printf("\n%5s | %15s | %20s | %10s | %15s | %5s | %4s\n", 
	       "INDEX", "ID NUMBER", "FIRST NAME", "MIDDLE NAME", "LAST NAME","PROGRAM", "YEAR");
		printf("---------------------------------------------------------------------------------------\n");
	while(x<D.max){
		trav = D.students[x];
				while(trav != NULL){
					printf("%5d", x);
					printf("%15s",trav->student.studID);
					printf("%20s",trav->student.studName.FName);
					printf("%10s",trav->student.studName.MName);
					printf("%15s",trav->student.studName.LName);
					printf("%5s", trav->student.program);
					printf("%4d", trav->student.year);
					
					trav = trav->link;
					printf("\n");
				}
		x++;
	}
	
	
	printf("\n\n");
}

