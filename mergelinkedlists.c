#include <stdio.h>
#include <stdlib.h>

typedef struct AnimalType {

	char species[25];
	char genus[25];
	char family[25];
	struct AnimalType *next;

} AnimalType;

void splitLinkedList(AnimalType *top, AnimalType *splitTopPtrs[2]){

	int whichList = 0;	
	AnimalType *tmp = NULL;
	AnimalType *splitBottomPtrs[2] = {NULL, NULL};
	

	splitTopPtrs[0] = top;
	
	if(top != NULL) splitTopPtrs[1] = top->next;
	else splitTopPtrs[1] = NULL;
	
	splitBottomPtrs[0] = splitTopPtrs[0];
	splitBottomPtrs[1] = splitTopPtrs[1]; 
	
	if(top->next != NULL) tmp = top->next->next;
	
	if(splitBottomPtrs[0] != NULL) splitBottomPtrs[0]->next = NULL;
	if(splitBottomPtrs[1] != NULL) splitBottomPtrs[1]->next = NULL;
	
	while(tmp != NULL){
		
		splitBottomPtrs[whichList]->next = tmp;	
		splitBottomPtrs[whichList] = tmp;
		tmp = tmp->next;
		splitBottomPtrs[whichList]->next = NULL;
		
		if(whichList == 0) whichList = 1; 
		else whichList = 0;
	}
}

AnimalType* mergeLinkedList(AnimalType *listTopA, AnimalType *listTopB){
	AnimalType *currentA = listTopA;
	AnimalType *currentB = listTopB;
	
	AnimalType *mergedListTop = NULL;
	AnimalType *mergedListCurrent = NULL;
	
	int whichList = 1;
	
	mergedListTop = currentA;
	// point current to top of merged list
	mergedListCurrent = mergedListTop;
	
	if(currentA != NULL) currentA = currentA->next;
	
	while(currentA != NULL || currentB != NULL){
	
		if(whichList == 1 && currentB != NULL){
		   
		   mergedListCurrent->next = currentB;
		   mergedListCurrent = currentB;
		   currentB = currentB->next;	
			
		}
		
		if(whichList == 0 && currentA != NULL){
			
			mergedListCurrent->next = currentA;
			mergedListCurrent = currentA;
			currentA = currentA->next;
			
		}
		
		if(whichList == 1) whichList = 0; 
		else whichList = 1; 
	}
	return mergedListTop;
}

AnimalType * loadAnimalList(){ 
	
	char line[100];
	AnimalType * newAnimalPtr = NULL;
	AnimalType * lastAnimalInList = NULL;
	AnimalType * firstAnimalInList = NULL;
	
	while (1){	
		
		fgets(line, 100, stdin);
		if (line[0] == '\n')break;
			 
		newAnimalPtr = (AnimalType *) malloc(sizeof(AnimalType)); 
		
		sscanf(line,"%s %s %s", newAnimalPtr->species, newAnimalPtr->genus, newAnimalPtr->family);
		 
		newAnimalPtr->next = NULL;
		
		if (firstAnimalInList != NULL){
			lastAnimalInList->next = newAnimalPtr;	
		} else {
			firstAnimalInList = newAnimalPtr;
		}
		lastAnimalInList = newAnimalPtr;
	}
	return firstAnimalInList;
}


void printAnimalList(AnimalType *animalListTop){
	AnimalType * currentAnimal = animalListTop;
	
	while(currentAnimal != NULL){
		printf("%s %s %s\n", currentAnimal->species, currentAnimal->genus, currentAnimal->family);
		currentAnimal = currentAnimal->next;	}
}


int main(int argc, char *argv[]){

	AnimalType *listOfLists[2];
	AnimalType *myTopOfList1 = NULL;
	AnimalType *myTopOfList2 = NULL;
	AnimalType *mergedList = NULL;
	// steps to build myTopOfList will point to
	 
	printf("List 1. Enter species genus family..\n");
	myTopOfList1 = loadAnimalList();
	
	
	printf("List 2. Enter species genus family..\n");
	myTopOfList2 = loadAnimalList();
	
	mergedList = mergeLinkedList(myTopOfList1, myTopOfList2);
	
	printAnimalList(mergedList);

/*
	splitLinkedList(myTopOfList, listOfLists);
	printf("Here is the first split list:\n");
	printAnimalList(listOfLists[0]);
	printf("================================\n");
	printf("Here is the second split list:\n");
	printAnimalList(listOfLists[1]);
*/
}
