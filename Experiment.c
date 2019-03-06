#include "BTree.h"

int main(int args, char** argv){
	int order = atoi(argv[1]);	
	int i,s=0,found=0;	
	long int value=0;
	char * line = NULL;

	clock_t start, end;
	long elapsed = 0;
	double timeTaken,avg=0,sum=0,min=100000,max=0;
	struct timespec t1,t0;

        size_t len = 0,sz;
        ssize_t read;
	

	FILE *fp, *fm, *fs;
	
	fp = fopen("Input.txt", "r");
	if(fp == NULL){
		printf("Couldn't open file");
		return 1;
	}

	fm = fopen("Result.m", "a");
	if(fm == NULL){
		printf("Couldn't open file\n");
			return 1;
	}

	fs = fopen("SearchInput.txt","r");
	if(fs == NULL){
		printf("Couldn't open file\n");
			return 1;
	}

	
		BTree *root = CreateBTree(2*order+1);
		s=0;
		while ((read = getline(&line, &len, fp)) != -1) {
			sscanf(line,"%d",&value);		
			root = InsertIntoBTree(root, value);
			s++;
		}
		s=0;
		sum = max=avg=0;
		min=100000;
		while ((read = getline(&line, &len, fs)) != -1) {
			sscanf(line,"%d",&value);
			//start = clock();	
			clock_gettime(CLOCK_REALTIME,&t0);
			found = SearchInBTree(root, value);
			clock_gettime(CLOCK_REALTIME,&t1);			
			//end = clock();
			//timeTaken = (double) (end - start);
			timeTaken = (t1.tv_sec - t0.tv_sec)*1000000000 +(t1.tv_nsec - t0.tv_nsec);
			sum +=timeTaken;
			if(timeTaken > max)
				max = timeTaken;
			if(timeTaken < min)
				min = timeTaken;
			s++;
		}
		avg = sum/(double)s;
		printf("m=%d, Avg=%lf, min=%lf, max=%lf\n",order,avg,min,max);
		fprintf(fm, "%d\t%lf\t%lf\t%lf\n",order,min,max,avg);
		if(root!=NULL){
			DeleteBTree(root);
			root=NULL;
		}
	rewind(fp);
	rewind(fs);
	fclose(fp);
	fclose(fm);
	fclose(fs);
	return 0;
}
