//
//  main.c
//  format
//
//  Created by Waleed Khan on 10/20/16.
//  Copyright © 2016 Waleed. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <intToDecASCII.h>

char**input;
char type;


//Makes sure that the bit is correct length and only 1s and 0s, and that the type is valid
int checkInput(){
    
    if (strlen(input[1])!=32){
        fprintf(stderr,"ERROR: the input bit sequence is not 32 characters long\n");
        return 0;
    }
    if (strlen(input[2])!=5 && strlen(input[2])!=3){
        fprintf(stderr,"ERROR: the type must be either float or int\n");
    }
    
    int n;
    char *c=input[1];
    for (n=0;n<strlen(c);n++){
        if (c[n]!='1' && c[n]!='0'){
            fprintf(stderr,"ERROR: There is a non-binary character in the bit sequence\n");
            return -1;
        }
    }
    
    char *outputType=input[2];

    if (strlen(outputType)==5 && (outputType[0]=='f' && outputType[1]=='l' && outputType[2]=='o' && outputType[3]=='a' && outputType[4]=='t')){
        type='f';
    }
    else if (strlen(outputType)==3 && (outputType[0]=='i' && outputType[1]=='n' && outputType[2]=='t')) {
        type='i';
    }
    else{
        fprintf(stderr,"ERROR: Not a valid type\n");
        return -1;
    }
    
    
    return 0;
}

int posToDec(char* bitSeq){
    int power=0;
    int total=0;
    int a;
    int b;
    
    //Multiplies each value from lowest to highest value by 2 to the power of the place in the sequence, right to left
    for (a=strlen(bitSeq)-1;a>0;a--){
        b=0;
        if (bitSeq[a]=='1'){
            b=1;
        }
        total+=b*(pow(2,power));
        power++;
    }
    return total;
}

int negToDec(char* bitSeq){
    
    int total=0;
    int a;
    
    //Flips the bit sequence's 1s and 0s
    for (a=1;a<strlen(bitSeq);a++){
        
        if (bitSeq[a]=='1'){
            bitSeq[a]='0';
        }
        else{
            bitSeq[a]='1';
        }
    }
    
    a=strlen(bitSeq)-1;
    int carryOver=1;
    
    //Adds 1 to the bit sequence
    while (a>0 && carryOver==1){
        
        if (bitSeq[a]=='0'){
            bitSeq[a]='1';
            carryOver=0;
        }
        else {
            bitSeq[a]='0';
        }
        a--;
    }
    
    //Now convert it to an integers
    total=posToDec(bitSeq);
    
    //Make sure it is negative, then return
    total=total*-1;
    return total;
}
static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
    int			p10;
    
    if ( x == 0.0 )
    {
        *digit = '0';			// digit is always '0'
        *pow10 = 0;
        *remainder = 0.0;
    }
    else
    {
        *pow10 = 0;			// start with 10^0
        while ( x >= 10.0 )		// reduce
        {
            x /= 10.0;		// large values get smaller
            *pow10 += 1;
        }
        while ( x < 1.0 )		// increase
        {
            x *= 10.0;		// small values get larger
            *pow10 -= 1;
        }
        *digit = '0';
        do {				// 10.0 > x >= 1.0
            x -= 1.0;
            *digit += 1;		// digit is always non-'0'zero
        } while ( x >= 1.0 );
        p10 = 0;
        while ( p10 > *pow10 )		// leading digit is now removed from x
        {
            x /= 10;
            p10 -= 1;
        }
        while ( p10 < *pow10 )
        {
            x *= 10;
            p10 += 1;
        }
        *remainder = x;
    }
}

//Takes the int pow and puts it into a char array that can later be appended
char* intToDecASCII(int power, char*exp){
    exp[1]=power-'0';
    
    int a=power;
    int length=0;
    if(a==0){
        length++;
    }
    if (a<0){
        length++;
    }
    while (a!=0){
        a/=10;
        length++;
    }
    
    char *c=malloc(sizeof(char)*length);
    sprintf(c,"%d",power);
    return c;
}

static void
append( char * s, char c )
{
    char		buf[2];
    
    buf[0] = c;
    buf[1] = '\0';
    strcat( s, buf );
}

union Number {
    int	i;
    float	f;
};

void
floatToASCII( float x, char * output )
{
    char		c;
    int		pow10, p10, plast;
    int		i;
    float		remainder;
    char		exponent[10];
    union Number	a;
    unsigned int	biasedExp;
    unsigned int	mantissa;
    int		sign;
    
    a.f = x;
    biasedExp = a.i >> 23 & 0x000000ff;
    mantissa = a.i & 0x007fffff;
    sign = a.i >> 31;
    
    if ( biasedExp == 0xff )
    {
        if ( mantissa == 0 )
        {
            if ( sign != 0 )
            {
                strcpy( output, "-inf" );
                return;
            }
            else
            {
                strcpy( output, "+inf" );
                return;
            }
        }
        else
        {
            if ( sign != 0 )
            {
                strcpy( output, "-NaN" );
                return;
            }
            else
            {
                strcpy( output, "+NaN" );
                return;
            }
        }
    }
    output[0] ='\0';
    if ( x < 0.0 )
    {
        append( output, '-' );
        x = -x;					// make x positive
    }
    get_float_digit( x, &c, &pow10, &remainder );
    append( output, c );
    append( output, '.' );
    x = remainder;
    plast = p10 = pow10;			// pow10 set by get_float_digit()
    for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
    {
        get_float_digit( x, &c, &p10, &remainder );
        if ( (plast - p10) > 1 )
        {
            append( output, '0' );	// fill in zero to next nonzero digit
            plast -= 1;
        }
        else
        {
            append( output, c );
            x = remainder;
            plast = p10;
        }
    }
    if ( pow10 < 0 )		// negative exponent
    {
        exponent[0] = 'e';
        char *c=intToDecASCII( pow10, exponent+1);
        strcat(exponent,c);
    }
    else if ( pow10 < 10 )		// positive single-digit exponent
    {
        exponent[0] = 'e';
        
        char *c=intToDecASCII( pow10, exponent+3);
        strcat(exponent,c);
    }
    else				// positive multi-digit exponent
    {
        exponent[0] = 'e';
        char *c=intToDecASCII( pow10, exponent+2);
        strcat(exponent,c);
    }
     
    strcat( output, exponent );
}


int expToDec(char* bitSeq){
    int power=0;
    int total=0;
    int a;
    int b;
    
    //Multiplies each value from lowest to highest value by 2 to the power of the place in the sequence, right to left, starting at 0
    for (a=strlen(bitSeq)-1;a>=0;a--){
        b=0;
        if (bitSeq[a]=='1'){
            b=1;
        }
        total+=b*(pow(2,power));
        power++;
    }
    return total;
}

float mantissaToFloat(char *bitSeq){
    float mantissa=0.0;
    int power=-1;
    int a=0;
    for (a=9;a<strlen(bitSeq);a++){
        if (bitSeq[a]=='1'){
            mantissa+=pow(2,power);
        }
        power--;
    }
    return mantissa;
}

float binToFloat(char *bitSeq){
    char *exponent=malloc(8*sizeof(char));
    int a=0;
    for (a=1;a<9;a++){
        exponent[a-1]=bitSeq[a];
    }
    int exp=expToDec(exponent)-127;
    free(exponent);
    
    float mantissa=mantissaToFloat(bitSeq);
    mantissa+=1;
    mantissa*=pow(2,exp);
    return mantissa;
}

int checkIfZero(){
    if (strcmp(input[1],"00000000000000000000000000000000")==0){
        printf("0.0e0\n");
        return -1;
    }
    return 0;
}

int checkIfNegZero(){
    if (strcmp(input[1],"10000000000000000000000000000000")==0){
        printf("-0.0e0\n");
        return- 1;
    }
    return 0;
}

int checkIfInf(){
    if (strcmp(input[1],"01111111100000000000000000000000")==0){
        printf("pinf\n");
        return- 1;
    }
    
    return 0;
}

int checkIfNegInf(){
    if (strcmp(input[1],"11111111100000000000000000000000")==0){
        printf("ninf\n");
        return- 1;
    }
    return 0;
}

int Nan(){
    if (strcmp(input[1],"01111111111111111111111111111111")==0){
        printf("NaN\n");
        return- 1;
    }
    return 0;
}

int main(int argc, char ** argv) {
    input=argv;
    if (argc!=3){
        fprintf(stderr,"ERROR: the input is not in the form of an input bit sequence then type\n");
        return 0;
    }
    if (checkInput()==-1){
        return 0;
    }
    
    char *bitSeq=input[1];
    
    //if it is a positive integer
    if (type=='i' && bitSeq[0]=='0'){
        int dec=posToDec(bitSeq);
        printf("%d\n",dec);
        return 0;
    }
    //if it is a negative integer
    else if (type=='i' && bitSeq[0]=='1'){
        int dec=negToDec(bitSeq);
        printf("%d\n",dec);
    }
    //if it is a positive float
    else if (type=='f' && bitSeq[0]=='0'){
        
        if(checkIfZero()==-1){
            return 0;
        }
        if (checkIfInf()==-1){
            return 0;
        }
        
        
        float fl=binToFloat(bitSeq);
        
        char *output=malloc(32);
        floatToASCII(fl,output);
        printf("%s\n",output);
        free(output);
    }
    //if it is negative float
    else if (type=='f' && bitSeq[0]=='1'){
        
        if (checkIfNegZero()==-1){
            return 0;
        }
        if (checkIfNegInf()==-1){
            return 0;
        }
        
        float fl=binToFloat(bitSeq);
        fl=fl*-1;
        
        char *output=malloc(32);
        floatToASCII(fl,output);
        printf("%s\n",output);
        free(output);
    }
    
    
    return 0;
}
