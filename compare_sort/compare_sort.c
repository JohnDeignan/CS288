/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];	
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define OK 1
#define NOK 0
#define NELM 100		/* default 100 elements */
#define N 1048576		/* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
//#define N 33554432

void selection_sort();
void swap();

void mrg();
void merge();
void merge_sort();

void int_radix_sort();
void float_radix_sort();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();

int n, lst[N], buf[N];

int main(int argc,char **argv) {
  if (argc>1) n = atoi(argv[1]);
  else n = NELM;
  init_lst(lst,n);

  clock_t t;
  t=clock();
  selection_sort(lst,n);
  t=clock()-t;
  double total_t= ((double)t)/CLOCKS_PER_SEC;
  printf("Total time taken: %f\n", total_t);
  t=clock();
  mrg(lst,buf,n);
  t=clock()-t;
  total_t= ((double)t)/CLOCKS_PER_SEC;
  printf("Total time taken: %f\n", total_t);
  t=clock();
  int_radix_sort(lst,n);
  t=clock()-t;
  total_t= ((double)t)/CLOCKS_PER_SEC;
  printf("Total time taken: %f\n", total_t);
  //  gettimeofday(&tv_e, NULL); 
  
  
  return 0;
}

void selection_sort(int lst[],int n){
  int i;
  int j;
  int temp[n];
  memcpy(temp, lst, n);

  printf("|------------ Selection Sort --------------|\n");
  printf("Before:\n");
  for(i=0;i<n;i++) {printf("%i, ", temp[i]);}
  printf("\n");
  
  for(i=0;i<n;i++){
    int min = i;
    for(j=i;j<n;j++){
      if(temp[min]>temp[j])
        min=j;
    }
    int sp=temp[i];
    temp[i]=temp[min];
    temp[min]=sp;
  }
  printf("Sorted List: \n");
  for(i=0;i<n;i++) {printf("%i, ", temp[i]);}
  printf("\n");
  
}

void mrg(int lst[], int tmp[], int n){
  int i;
  printf("|------------ Merge Sort --------------|\n");
  printf("Before:\n");
  for(i=0;i<n;i++) {printf("%i, ", lst[i]);}
  printf("\n");
  
  merge_sort(lst, tmp, 0, n-1);

  printf("Sorted List: \n");
  for(i=0;i<n;i++) {printf("%i, ", lst[i]);}
  printf("\n");
}

void merge_sort(int lst[], int tmp[], int left, int right){
  if(left < right){
    int mid = (right + left) / 2;
    merge_sort(lst, tmp, left, mid);
    merge_sort(lst, tmp, mid+1, right);
    merge(lst, tmp, left, mid, right);
  }
}

void merge(int lst[], int tmp[], int left, int mid, int right){
  int i=left;
  int j=mid+1;
  int k=0;

  while(i <= mid && j <= right){
    if(lst[i]<lst[j]) tmp[k++]=lst[i++];
    else tmp[k++]=lst[j++];
  }
  while(i<=mid)
    tmp[k++]=lst[i++];
  while(j<=right)
    tmp[k++]=lst[j++];
  for(i=left, j=0; i<=right; i++, j++)
    lst[i]=tmp[j];
}

void int_radix_sort(int lst[], int n){
  int i = 0;
  int j = 0;
  int k = 1;
  int m = 10;
  int run = 1;
  int buckets[10][n];
  int count[10];
  int temp[n];
  memcpy(temp, lst, n);

  printf("|------------ Radix Sort --------------|\n");
  printf("Before:\n");
  for(i=0;i<n;i++) {printf("%i, ", temp[i]);}
  printf("\n");

  while(count[0] != n){
    for(j=0; j<10; j++){
	count[j]=0;
    }
    for (i=0; i<n; i++){
      int curr = temp[i] % m;
      int put = (int)(curr / k);
      count[put]++;
      buckets[put][count[put]-1]=temp[i];
    }
    k=k*10;
    m=m*10;
    
    int ind=0;
    for(i=0; i<10; i++){
      for(j=0; j<=(count[i]-1); j++){
	temp[ind]=buckets[i][j];
	ind++;
      }
    }
    run++;
  }

  printf("Sorted List: \n");
  for(i=0;i<n;i++) {printf("%i, ", temp[i]);}
  printf("\n");
  printf("Total iterations: %i\nTotal buckets: 10\n", run);
}

void init_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    l[i] = rand();
  }
}
