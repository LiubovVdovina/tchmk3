//
//  long_number_lib.h
//  r22
//
//  Created by Admin on 03.07.15.
//  long_num_copyright (c) 2015 Admin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>

#define BASIS 1000000000

struct long_number
{
    int size;
    int sign;
    unsigned int* cifers;
};

typedef struct long_number long_number;

struct long_number from_str(char* string);
long_number create_from_int(long long int value);
char* gt_str(struct long_number a);
long_number long_num_copy(long_number from);
long_number deleteNulls(long_number a);
long long int long_num_cmp(long_number A, long_number B);
long_number SumOrSub(long_number left, long_number right);
long_number summarizing(long_number A, long_number B);
long_number substraction(long_number A, long_number B);
long_number chsign(long_number a);
long_number mul(long_number A, long_number B);
long_number divd(long_number A, long_number B, long_number* ostatok);
long_number toLeft(long_number a, int s);
long_number invoke(long_number base, long_number exp);
long_number invoke_module(long_number base, long_number exp, long_number modulus);
long_number binaryRead(char* filename);
int binaryWrite(char* filename, long_number A, int flag_oper);
long_number fileRead(char *fileName);
int fileWrite(char *fileName, long_number A);

class long_class
{
    long_number me;
    
public:
    long_class();
    ~long_class(); /*
    long_class(long_class& rhv);
    long_class(char *string);
    long_class(long long int v);*/

    char *str();
    
    long_class& operator=(const long_class& rhv);
    long_class operator+(long_class &right);
    long_class operator-();
    long_class operator-(long_class &right);
    long_class operator*(long_class &right);
    long_class operator/(long_class &right);
    long_class operator%(long_class &right);
    long_class operator^(long_class &right);
    
    bool operator>(long_class &rhv);
    bool operator<(long_class &rhv);
    bool operator!=(long_class &rhv);
  
    bool fileRead_class(char* filename);
    bool fileWrite_class(char* filename);
    bool binaryRead_class(char* filename);
    bool binaryWrite_class(char* filename, int flag_oper);
    
    friend long_class invoke_module_class(long_class &base, long_class &exp, long_class &mod);
};
