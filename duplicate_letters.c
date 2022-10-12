
#include<stdio.h>
#include<string.h>

int main(void){


    char word[15]; 
    int i,j, len;

    // Getting the word from the user
    printf("Enter a word>\n");
    scanf("%s", word);
    
    len = strlen(word);
    
    // Count to make sure there is at least one duplicate letter in word
   
    int overall_count = 0;
    // Double for loop over all letters in the word
    for (i = 0; i < len; i++)  
    {  
        int count = 1;
        for (j = i+1; j < len; j++){
        	// Checking if the letter is the same as the next letter
            if(word[i] == word[j]){
            	// If it is, we increment the count and replace that letter with 
            	// -1 so it doesn't get added twice
                count+=1;
                word[j] = -1;
            }
        }

        if(count > 1 && word[i] != -1 && word[i] != ' '){
            overall_count++;
            // Printing the duplicate letter and its number of occurences
            printf("Duplicate letter: %c, ", word[i]);
            printf("Occurrences: %d\n", count);
        }
    }  

     if(overall_count == 0) {
            printf("No duplicates found\n");
        }

    return 0;
    }
