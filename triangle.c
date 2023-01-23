
#include<stdio.h>



/*Main function to take input from user and print the final conversion output */
int main(void){
    int rows;
    int i;
    int j;
    int k = 0;


    printf("Enter an integer>\n");
    scanf("%d", &rows);

    if(rows < 1){
        printf("Input must be greater or equal to 1");
    }

    for(i = 1; i<=rows;++i){ 
        if(i==1){
            ;}
        else{
            printf("\n");
            }

        for(j = 0; j<=(rows-i); ++j){
            printf(" ");}

        while(k != (2*i-1)){
            printf("*"); 
            k++ ;
            }
        k = 0;
    }
    printf("\n");


    return 0 ;
}