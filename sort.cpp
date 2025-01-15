int partition(int array[], int LB, int UB){
	int up, down;
    int pivot, temp;

	pivot=array[LB];
	up= LB;
	down= UB;

 	while (up<down) {
 		while ((array[up]<=pivot)&&(up<UB)){
   			up++;
 			
			while (array[down]>pivot){
 					down--;
 			}
			if(up<down){
 				temp=array[down];
				array[down]=array[up];
				array[up]=temp;
 			}
 		}
	}
 	array[LB]=array[down];
 	array[down]=pivot;
 	return (down);
}

//Quicksort Part A
void Quicksort(int data[],int LB, int UB){
	int part;
	
	if(LB<UB){
 		part=partition(data,LB,UB);
 		Quicksort(data, LB, part-1); // PART A
		Quicksort(data, part+1, UB); // PART B
 }
} 
