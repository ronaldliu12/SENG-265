
// Ronald Liu V00838627 SENG265 Assignment1 

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LEN 500
//#define MAX_WORDS 100
//#define MAX_WORD_LEN 20

	int width = 0;				// checking width
	int current_width = 0;			// checking current width
	int left = 0;
	int linespacing = 0;
	int formatting = 0;			// checking if FT is off
	char* del = " \n";
	int no_trans = 0;			// checking if no any formatting commands
	int first_word = 0;			// checking if it is the first word of the line
	int special = 0;			// checking if it reaches .FT special case
	

void counting(char* words, int *target){
	int object = 0;
	int i;

	for(i = (int)strlen(words)-1;i>=0;i--){
				
		int x = words[i] - '0';
		int y = x;

		if ( (x >= 0)&&(x <= 9) ){

				int j;
			
				for(j=0; j<((int)strlen(words)-1-i); j++){
				
					y = x*10;
				
				}
			
			object += y;
			
		}
	}

	
	*target = object;
}


void FT(char* words){
					
	if (strncmp(words,"off",3)==0){
		formatting = 0;
	}

	else if (strncmp(words,"on",2)==0){
		formatting = 1;
	}
}

void printing(char* words){
	

	if( (current_width + strlen(words)) > width && formatting==1 ){

		//fprintf(stdout, "[checking]");

		if (linespacing>0){
			fprintf(stdout, "\n");
			int m;
			for (m=0;m<linespacing;m++){
				fprintf(stdout, "\n");
			}
		}else{
			fprintf(stdout, "\n");
		}

		current_width = 0;
		
			if (left>0) {
				int k;
				for (k=0;k<left;k++){
					fprintf(stdout, " ");
					current_width++;
				}
			}

	}

	
	if( current_width==left ){
		fprintf(stdout, "%s", words);
	}	
	else{
		fprintf(stdout, " %s", words);
	}

	current_width += (strlen(words)+1);
	
}

void printing2(char* line){
	
		fprintf(stdout,"%s", line);
}


int checking(char* words){
	
	if ( words[0] > 0 ){
		
		int y = words[0] - '0';

		if ( (y >= 0)&&(y <= 9) ){
			return (int)1;
		}
		else{
			return (int)0;
		}
	}
	return (int)1;
}





int main(int argc, char* argv[]){


	char buffer[MAX_LINE_LEN];
	char copy[MAX_LINE_LEN];
	char copy2[MAX_LINE_LEN];
	char tmp[MAX_LINE_LEN];
	char check[MAX_LINE_LEN];
	char double_check[MAX_LINE_LEN];


	FILE *data = fopen(argv[1], "r");
	FILE *data2 = fopen(argv[1], "r");

		
	   if(data == NULL) {
	      fprintf(stderr, "Error opening file");
	      return(-1);
	   }

	fgets(check, MAX_LINE_LEN, data2);

	while(fgets(buffer, MAX_LINE_LEN, data)!=NULL){
		
			first_word = 0;
			
			//fprintf(stdout, "TESTING[[this is %s ]] ", buffer);
			
			//int length = (int)strlen(buffer);
			//fprintf(stdout, "TESTING[[length:%d ]] ", length);
			
			//fprintf(stdout, "TESTING[[string1:%s]] ", &buffer[length-1]);
			
			//	if ( strncmp(&buffer[length-1],"\n",2)==0 ){
			//		fprintf(stdout, "SUCCESS");
			//	}
				
			
			if (strncmp(buffer,"\n",2)==0 && formatting == 1){
				
				fprintf(stdout, "\n");
				fprintf(stdout, "\n");
				current_width = 0;
				if (linespacing>0){
					int m;
					for (m=0;m<linespacing;m++){
						fprintf(stdout, "\n");
					}
				}
			}
		
		
		
		strncpy(copy, buffer, MAX_LINE_LEN);
		strncpy(copy2, buffer, MAX_LINE_LEN);
		
		char* words = strtok(buffer, del);

		while(words != NULL){
			
			if (current_width ==0 && formatting==1 && strncmp(words,"\n",2)!=0){
				if (left>0) {
					int k;
					for (k=0;k<left;k++){
						fprintf(stdout, " ");
						current_width++;
					}
				}
			}
			

			if (strncmp(words,".LW",3)==0){
				
				no_trans = 1;
				strncpy(tmp, words, MAX_LINE_LEN);
				words = strtok(NULL, del);
				
				if ( checking(words) == 1 ){
				
					formatting = 1;
					counting(words, &width);
					words = strtok(NULL, del);
					
				}else{
					if ( formatting == 1){
						printing(tmp);
						printing(words);
						words = strtok(NULL, del);
					}
				}
			}
			else
			
			if (strncmp(words,".LM",3)==0){
				
				no_trans = 1;
				strncpy(tmp, words, MAX_LINE_LEN);
				words = strtok(NULL, del);
				
				if ( checking(words) == 1 ){
				
					counting(words, &left);
					words = strtok(NULL, del);
					
				}else{
					
					if ( formatting == 1){
						printing(tmp);
						printing(words);
						words = strtok(NULL, del);
					}
				}
			}
			else
				
			if (strncmp(words,".LS",3)==0){

				no_trans = 1;
				strncpy(tmp, words, MAX_LINE_LEN);
				words = strtok(NULL, del);
				
				if ( checking(words) == 1 ){
				
					counting(words, &linespacing);
					words = strtok(NULL, del);
					
				}else{
					
					if ( formatting == 1){
						printing(tmp);
						printing(words);
						words = strtok(NULL, del);
					}
				}
			}
			else

			if (strncmp(words,".FT",3)==0 && first_word == 0){
				
				no_trans = 1;
				strncpy(tmp, words, MAX_LINE_LEN);
				words = strtok(NULL, del);
				FT(words);

				if ( formatting == 0) {

					char* del2 = ".FT";
					words = strtok(NULL, del2);
					special = 1;
					
				}else{
						printing(tmp);
						printing(words);
						words = strtok(NULL, del);


				}
				

				words = strtok(NULL, del);
				

				
			}
			else 
	
			if ( no_trans==1 && words != NULL && formatting ==1 ){

					//fprintf(stdout, "TESTING[%s] ", words);
					printing(words);
					words = strtok(NULL, del);
					first_word = 1;

			}
			else{
				words = strtok(NULL, del);
				first_word = 1;
			}

		
		}
	
		// for cases when without any formatting command
		if ( no_trans == 0 && copy != NULL){
			
			//fprintf(stdout, "haha");
			
			printing2(copy);
		}
		
		// for cases when have LS but FT off
		if ( no_trans == 1 && formatting==0 && special == 0 ){
			
			if (linespacing>0){
				int m;
				for (m=0;m<=linespacing;m++){
					fprintf(stdout, "\n");
				}
			}	
			printing2(copy);
		}
		
		special = 0;
		
		strncpy(double_check, check, MAX_LINE_LEN);
		
		fgets(check, MAX_LINE_LEN, data2);
			
			if ( check != NULL ){

				if (strncmp(check,"\n",2)==0){
					
					if (linespacing>0){
						int m;
						for (m=0;m<linespacing;m++){
							fprintf(stdout, "\n");
						}
					}
				}
			}
		
		
	}
	
	//fprintf(stdout, "TESTING[[this is %s ]] ", copy2);
	
	if ( formatting == 1 && (int)strlen(copy) > 2){
		int length = (int)strlen(copy);
			
			if ( strncmp(&copy[length-1],"\n",2)==0 ){
				fprintf(stdout, "\n");
			}
	
	}
	
	fclose(data2);
	fclose(data);
	return(0);
}


