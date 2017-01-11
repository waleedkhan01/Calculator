//
//
//  calc.c
//
//  Created by Waleed Khan
//  Copyright © 2016 Waleed. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

char ** input;
char type;
int negOutput=0;

//Makes sure that the input is in a proper basic form
int checkIfValidForm(){
    
    char *c=input[1];
    
    //If the first operator is valid
    if ( (c[0]!='+' && c[0]!='-') || strlen(c)>1){
        
        fprintf(stderr,"ERROR: Not a valid beginning of input\n");
        return -1;
    }
    
    //if the first number is valid
    c=input[2];
    
    if ((c[0]!='b' && c[0]!='o' && c[0]!='x' && c[0]!='d' && c[0]!='-') || strlen(c)<2){
        fprintf(stderr,"ERROR: Not a valid beginning for number 1\n");
        return -1;
    }
    else if (c[0]=='-'){
        if ((c[1]!='b' && c[1]!='o' && c[1]!='x' && c[1]!='d') || strlen(c)<3){
            fprintf(stderr,"ERROR: Not a valid beginning for number 1\n");
            return -1;
        }
    }
    
    //if the second number is valid
    c=input[3];
    if ((c[0]!='b' && c[0]!='o' && c[0]!='x' && c[0]!='d' && c[0]!='-') || strlen(c)<2){
        fprintf(stderr,"ERROR: Not a valid beginning for number 1\n");
        return -1;
    }
    else if (c[0]=='-'){
        if ((c[1]!='b' && c[1]!='o' && c[1]!='x' && c[1]!='d') || strlen(c)<3){
            fprintf(stderr,"ERROR: Not a valid beginning for number 1\n");
            return -1;
        }
    }
        
    //if the output is valid
    c=input[4];
    if ((c[0]!='b' && c[0]!='o' && c[0]!='x' && c[0]!='d') || strlen(c)>1){
        fprintf(stderr,"ERROR: Not a valid ouput form\n");
        return -1;
    }
    
    return 0;
}

//Finds type of the given index in the array and sets it
void setType(int index){
 
    char *c = input[index];
    
    if (c[0]=='-'){
        type=c[1];
    }
    else{
        type=c[0];
    }
}

//Makes sure each number in the input is a valid number for its type
int checkIfValidNumber(int index){
    
    char *c=input[index];
    
    if (type=='d'){
        
        int a;
        for (a=1;a<strlen(c);a++){
            if (a==1 && c[0]=='-'){
                a++;
            }
            if (c[a]>'9' || c[a]<'0'){
                
                fprintf(stderr,"ERROR: There is a non-decimal character in Number %d\n",index-1);
                return -1;
            }
        }
    }
    
    if (type=='b'){
        
        int a;
        for (a=1;a<strlen(c);a++){
            if (a==1 && c[0]=='-'){
                a++;
            }
            if (c[a]!='0' && c[a]!='1'){
                fprintf(stderr,"ERROR: There is a non-binary character in Number %d\n",index-1);
                return -1;
            }
        }
    }
    
    if (type=='o'){
        
        int a;
        for (a=1;a<strlen(c);a++){
            if (a==1 && c[0]=='-'){
                a++;
            }
            if (c[a]<'0' || c[a]>'7'){
                fprintf(stderr,"ERROR: There is a non-octal character in Number %d\n",index-1);
                return -1;
            }
        }
    }
    
    if (type=='x'){
        
        int a;
        for (a=1;a<strlen(c);a++){
            if (a==1 && c[0]=='-'){
                a++;
            }
            if ((c[a]<'a' || c[a]>'f') && (c[a]<'0' || c[a]>'9') && (c[a]<'A' || c[a]>'F')){
                fprintf(stderr,"ERROR: There is a non-hex character in Number %d\n",index-1);
                return -1;
            }
            
        }
        
    }
    
    
    return 0;
}

//Takes the respective index and converts the number into an integer
long int convertToInt(int index){

    char *c=input[index];
    int power=strlen(c)-2;
    if (c[0]=='-'){
        power--;
    }
    
    if (type=='d'){
        
        long int total=0;
        int a;
        for (a=1;a<strlen(c);a++){
            if (c[0]=='-' && a==1){
                a++;
            }
            total+=(c[a]-'0')*pow(10,power);
            power--;
        }
        return total;
    }
    
    if (type=='b'){
        
        long int total=0;
        int a;
        for (a=1;a<strlen(c);a++){
            if (c[0]=='-' && a==1){
                a++;
            }
            total+=(c[a]-'0')*(pow(2,power));
            power--;
        }
        return total;
    }
    
    if (type=='o'){
        
        long int total=0;
        int a;
        for (a=1;a<strlen(c);a++){
            if (c[0]=='-' && a==1){
                a++;
            }
            total+=(c[a]-'0')*pow(8,power);
            power--;
        }
        return total;
    }

    if (type=='x'){
        
        long int total=0;
        int a;
        for (a=1;a<strlen(c);a++){
            if (c[0]=='-' && a==1){
                a++;
            }
            
            if (c[a]>='0'&&c[a]<='9'){
                total+=(c[a]-'0')*pow(8,power);
                power--;
            }
            else if ((c[a]>='a' && c[a]<='f') || (c[a]>='A' && c[a]<='F')){
                int letterValue=0;
                if (c[a]=='a' || c[a]=='A'){
                    letterValue=10;
                }
                else if (c[a]=='b' || c[a]=='B'){
                    letterValue=11;
                }
                else if (c[a]=='c' || c[a]=='C'){
                    letterValue=12;
                }
                else if (c[a]=='d' || c[a]=='D'){
                    letterValue=13;
                }
                else if (c[a]=='e' || c[a]=='E'){
                    letterValue=14;
                }
                else if (c[a]=='f' || c[a]=='F'){
                    letterValue=15;
                }
                total+= letterValue*pow(16,power);
                power--;
            }
        }
        return total;
    }
    return 0;
}

//Adds or subtracts the second number depending on the operation entered in the input
long int calculate(long int num1, long int num2){
    
    char *c=input[1];
    
    char *number1=input[2];
    char *number2=input[3];
    
    if (number1[0]=='-'){
        num1=num1*-1;
    }
    
    if (number2[0]=='-'){
        num2=num2*-1;
    }
    
    if (c[0]=='+'){
        long int sum=num1+num2;
        return sum;
    }
    else if (c[0]=='-'){
        long int difference=num1-num2;
        return difference;
    }
    
    return 0;
}

//Converts a decimal a binary in an integer
long int decToBinary(long int dec) {
    
    if (dec==0){
        return 0;
    }
    
    long int num,binaryNumber=0,incr=1;
    
    while(dec!=0) {
        num = dec%2;
        dec = dec/2;
        binaryNumber= binaryNumber + (incr*num);
        incr = incr*10;
    }
    return binaryNumber;
}

//Converts a decimal to an octal in an integer
long int decToOctal(long int dec) {
    
    if (dec==0){
        return 0;
    }
    
    long int num,octalNumber=0,incr=1;
    
    while(dec!=0) {
        num = dec%8;
        dec = dec/8;
        octalNumber = octalNumber + (incr*num);
        incr = incr*10;
    }
    return octalNumber;
}

//Converts a decimal to a hex in a a char array
char* decToHex(long int dec){
    
    if (dec==0){
        return 0;
    }
    
    char *hexNumber=malloc(sizeof(char)*32);
    long int num;
    int index=0;
    
    while(dec!=0) {
        num = dec % 16;
        
        //converts integers into their respective chars
        if(num < 10){
            num = num + 48;
        }
        //If the integer is 9-15, then it is given its hex letter
        else if (num<16){
                num = num + 55;
        }
        hexNumber[index]= num;
        dec = dec / 16;
        index++;
    }
    return hexNumber;
}

//Reverses a string for hexadecimal, where the answer is written backwards
void reverseString(char *c)
{
    int length = strlen(c);
    int front;
    int end=length-1;
    int temp;
    
    for (front=0;front<length/2; front++)
    {
        temp = c[front];
        c[front] = c[end];
        c[end] = temp;
        end--;
    }
}

//Runs respective functions and does checks to convert the total into the output form needed
char * convertToOutput(long int total){
    char *c = input[4];
    
    if (total<0){
        total=total*-1;
        negOutput=1;
    }
    
    int length=1+(int)log10(total);
    
    
    if (total==0){
        
        char *output=(malloc(sizeof(char)));
        output[0]='0';
        printf("returning %s\n",output);
        return output;
    }
    if (c[0]=='d'){
        
        char *output=malloc(sizeof(char)*length);
        sprintf(output,"%ld",total);
        return output;
    }
    
    if (c[0]=='b'){
        long int newTotal=decToBinary(total);
        length=1+(int)log10(newTotal);
        char *output=malloc(sizeof(char)*length);
        sprintf(output,"%li",newTotal);
        return output;
    }
    
    if (c[0]=='o'){
        long int newTotal=decToOctal(total);
        length=1+(int)(log10(newTotal));
        char*output=malloc(sizeof(char)*length);
        sprintf(output,"%li",newTotal);
        return output;
        
    }
    if (c[0]=='x'){
        
        char *output=malloc(sizeof(char)*32);
        output=decToHex(total);
        reverseString(output);
        return output;
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    if (argc!=5){
        fprintf(stderr,"ERROR: Not a valid input form\n");
        return 0;
    }
    else{
        
        input=(char**)argv;
        
        //See if input is in a correct form
        if (checkIfValidForm()==-1){
            
            return 0;
        }
        
        //Find the type for the first number in the input
        setType(2);
        
        //If the number 1 is valid for the type it is supposed to be
        if (checkIfValidNumber(2)==-1){
            return 0;
        }
        
        //Converts the input into an integer
        long int num1=convertToInt(2);
        
        
        //Find the type for the second number in the input
        setType(3);
        
        if (checkIfValidNumber(3)==-1){
            return 0;
        }
        
       
        long int num2=convertToInt(3);
        
        
        long int total=calculate(num1,num2);
        
        char *output=convertToOutput(total);
        char *returnType=input[4];
        
        if (negOutput!=0){
            printf("%c",'-');
        }
        printf("%c%s\n",returnType[0],output);
        free(output);
    }
    
    
    return 0;
    
    
}
