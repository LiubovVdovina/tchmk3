//
//  long_number_lib.cpp
//  r22
//
//  Created by Admin on 03.07.15.
//  long_num_copyright (c) 2015 Admin. All rights reserved.
//

#include "long_number_lib.h"
int hlv[4];
int r = 0;

long_class::long_class()
{
    this->me = create_from_int(0);
}
/*
long_class::long_class(long_class& rhv)
{
    this->me = long_num_copy(rhv.me);
}

long_class::long_class(char *string)
{
    this->me = from_str(string);
}

long_class::long_class(long long int v)
{
    this->me = create_from_int(v);
}
*/
long_class::~long_class()
{
    if (this->me.cifers != NULL)
    {
        free(this->me.cifers);
    }
}

long_class& long_class::operator=(const long_class& rhv)
{
    if (this->me.cifers != NULL)
    {
        free(this->me.cifers);
    }
    this->me = long_num_copy(rhv.me);
    return *this;
}

char * long_class::str()
{
    return gt_str(this->me);
}

long_class long_class::operator+(long_class &right)
{
    long_class res;
    res.me = SumOrSub(this->me, right.me);
    return res;
}

long_class long_class::operator-()
{
    long_class res;
    res.me = chsign(this->me);
    return res;
}

long_class long_class::operator-(long_class &right)
{
    long_class res,tmp;
    tmp.me = chsign(this->me);
    res.me = SumOrSub(tmp.me, right.me);
    return res;
}

long_class long_class::operator*(long_class &right)
{
    long_class res;
    res.me = mul(this->me, right.me);
    return res;
}

long_class long_class::operator/(long_class &right)
{
    long_class ost;
    long_class res;
    res.me = divd(this->me, right.me, &ost.me);
    return res;
}

long_class long_class::operator%(long_class &right)
{
    long_class ost;
    long_class res;
    res.me = divd(this->me, right.me, &ost.me);
    return ost;
}

long_class long_class::operator^(long_class &right)
{
    long_class res;
    res.me = invoke(this->me, right.me);
    return res;
}

bool long_class::fileRead_class(char* filename)
{
    long_class res;
    res.me = fileRead(filename);
    if (res.me.cifers == NULL)
    {
        return false;
    }
    else
    {
        *this = res;
        return true;
    }
}

bool long_class::binaryRead_class(char* filename)
{
    long_class res;
    res.me = binaryRead(filename);
    if (res.me.cifers == NULL)
    {
        return false;
    }
    else
    {
        *this = res;
        return true;
    }
}

bool long_class::fileWrite_class(char* filename)
{
    int res;
    res = fileWrite(filename, this->me);
    if (res != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool long_class::binaryWrite_class(char* filename, int flag_oper)
{
    return binaryWrite(filename, this->me, flag_oper) == 0;
}

bool long_class::operator>(long_class &rhv)
{
    int res;
    res = long_num_cmp(this->me, rhv.me);
    if (res > 0)
        return true;
    else
        return false;
}

bool long_class::operator<(long_class &rhv)
{
    return long_num_cmp(this->me, rhv.me) < 0;
}

bool long_class::operator!=(long_class &rhv)
{
    int res;
    res = long_num_cmp(this->me, rhv.me);
    if (res != 0)
        return true;
    else
        return false;
}

long_class invoke_module_class(long_class &base, long_class &exp, long_class &mod)
{
    long_class res;
    res.me = invoke_module(base.me, exp.me, mod.me);
    return res;
}


struct long_number from_str(char* string)
{
    int strSize = strlen(string);
    int strSign = 0;
    if (string[0] == '-')
    {
        strSize--;
        strSign = 1;
    }
    
    char* pStr = string + strSize + strSign;
    
    struct long_number res;
    res.size = ((strSize + strSign + 8) / 9); // ÔÓ˜ÂÏÛ 8
    res.sign = strSign;
    res.cifers = (unsigned int*)malloc((res.size)*sizeof(unsigned int));
    
    int i;
    for (i = 0; i < (strSize + strSign) / 9; i++)
    {
        pStr -= 9;
        char splStr[10];
        memcpy(splStr, pStr, 9);
        splStr[9] = '\0';
        
        unsigned int digitI = atol(splStr);
        
        res.cifers[i] = digitI;
    }
    
    char ost[10];
    memset(ost, 0, 10);
    memcpy(ost, string + strSign, pStr - string - strSign);
    if (strlen(ost) > 0)
    {
        unsigned int lastDigit = atol(ost);
        res.cifers[res.size - 1] = lastDigit;
    }
    
    res = deleteNulls(res);
    return res;
}

long_number create_from_int(long long int value)
{
    long_number res;
    res.cifers = (unsigned int*)malloc((3)*sizeof(unsigned int));
    res.size = 0;
    res.sign = 0;
    
    if (value < 0)
    {
        res.sign = 1;
        value = -value;
    }
    do
    {
        res.size++;
        res.cifers[res.size - 1] = value % BASIS;
        value = value / BASIS;
    } while (value);
    
    return res;
}

char* gt_str(long_number a)
{
    char* strBuffer = (char*)malloc((a.size * 9 + 1 + a.sign) * sizeof(char));
    char* pString = strBuffer + a.size * 9 + a.sign;
    *pString = '\0';
    
    int i;
    for (i = 0; i < a.size; i++)
    {
        char splStr[10];
        sprintf(splStr, "%09u", a.cifers[i]);
        
        pString -= 9;
        memcpy(pString, splStr, 9);
    }
    
    while (*pString == '0' && *(pString + 1))
        pString++;
    
    if (a.sign)
    {
        pString--;
        *pString = '-';
    }
    
    char* string = (char*)malloc((strlen(pString) + 1) * sizeof(char));
    strcpy(string, pString);
    free(strBuffer);
    
    return string;
}

long_number long_num_copy(long_number from)
{
    long_number cpy;
    cpy.size = from.size;
    cpy.cifers = (unsigned int*)malloc((cpy.size)*sizeof(unsigned int));
    memcpy(cpy.cifers, from.cifers, cpy.size * sizeof(unsigned int));
    cpy.sign = from.sign;
    return cpy;
}

long_number deleteNulls(long_number a)
{
    while ((a.size > 1) && a.cifers && a.cifers[a.size - 1] == 0)
        a.size--;
    
    if (a.size == 1 && a.cifers[0] == 0)
        a.sign = 0;
    
    return a;
}

long long int long_num_cmp(long_number A, long_number B)
{

    int aSign = 1;
    if (A.sign == 1)
        aSign = -1;
    
    if (A.sign != B.sign)
        return aSign;
    
    if (A.size > B.size)
        return aSign;
    
    if (A.size < B.size)
        return -aSign;
    
    int i = A.size - 1;
    
    while (A.cifers[i] == B.cifers[i] && i > 0)
        i--;
    
    return ((long long int) A.cifers[i] - (long long int)B.cifers[i]) * aSign;
}

long_number toLeft(long_number a, int s)
{
    
    unsigned int* newDig = (unsigned int*)malloc((a.size + s)*sizeof(unsigned int));
    
    memset(newDig, 0, s * sizeof(unsigned int));
    
    memcpy(newDig + s, a.cifers, a.size * sizeof(unsigned int));
    free(a.cifers);
    a.cifers = newDig;
    a.size += s;
    
    return a;
}

long_number SumOrSub(long_number left, long_number right)
{
    long_number A = left, B = right;
    A.sign = 0;
    B.sign = 0;
    if (long_num_cmp(A, B) > 0)
    {
        A.sign = left.sign;
        B.sign = right.sign;
    }
    else
    {
        A = right;
        B = left;
    }
    
    if (A.sign == B.sign)
        return summarizing(A, B);
    else
        return substraction(A, B);
}

long_number summarizing(long_number A, long_number B)
{
    
    long_number res;
    res.sign = 0;
    res.size = A.size + 1;
    res.cifers = (unsigned int*)malloc((A.size + 1)*sizeof(unsigned int));
    
    unsigned int carry = 0;
    int i;
    for (i = 0; i < A.size; i++)
    {
        unsigned int tmp = A.cifers[i] + carry;
        if (i < B.size)
            tmp += B.cifers[i];
        
        res.cifers[i] = tmp % BASIS;
        carry = tmp / BASIS;
    }
    
    res.cifers[A.size] = carry;
    res.sign = A.sign;
    res = deleteNulls(res);
    return res;
}

long_number substraction(long_number A, long_number B)
{
  
    long_number res;
    res.sign = 0;
    res.size = A.size;
    res.cifers = (unsigned int*)malloc((A.size)*sizeof(unsigned int));
    
    unsigned int carry = 0;
    int i;
    for (i = 0; i < A.size; i++)
    {
        int tmp = A.cifers[i] - carry;
        if (i < B.size)
            tmp -= B.cifers[i];
        
        carry = 0;
        if (tmp < 0)
        {
            carry = 1;
            tmp += BASIS;
        }
        res.cifers[i] = tmp;
    }
    
    res.sign = A.sign;
    res = deleteNulls(res);
    return res;
}

long_number chsign(long_number a)
{
    
    long_number res = long_num_copy(a);
    res.sign = !a.sign;
    res = deleteNulls(res);
    return res;
}

long_number mul(long_number A, long_number B)
{
    long_number res;
    res.size = A.size + B.size;
    res.cifers = (unsigned int*)malloc((res.size)*sizeof(unsigned int));
    memset(res.cifers, 0, res.size * sizeof(unsigned int));
    unsigned int carry = 0;
    int i;
    for (i = 0; i < B.size; i++)
    {
        carry = 0;
        int j;
        for (j = 0; j < A.size; j++)
        {
            unsigned long long int tmp = (unsigned long long int) B.cifers[i] * (unsigned long long int) A.cifers[j]
            + carry + (unsigned long long int) res.cifers[i + j];
            carry = tmp / BASIS;
            res.cifers[i + j] = tmp % BASIS;
        }
        res.cifers[i + A.size] = carry;
    }
    
    res.sign = (A.sign != B.sign);
    res = deleteNulls(res);
    return res;
}

long_number divd(long_number A, long_number B, long_number* ostatok)
{
    *ostatok = long_num_copy(A);
    ostatok->sign = 0;
    
    long_number divider = long_num_copy(B);
    divider.sign = 0;
    
    if (1 == divider.size)
    {
        if (divider.cifers[0] == 0)
        {
            ostatok->size = 0;
            ostatok->sign = 0;
            ostatok->cifers = NULL;
            
            long_number a;
            a.size = 0;
            a.sign = 0;
            a.cifers = NULL;
            
            free(divider.cifers);
            return a;
        }
    }
    
    if (long_num_cmp(*ostatok, divider) < 0)
    {
       
        ostatok->sign = A.sign;
        long_number res;
        res.sign = 0;
        res.size = 1;
        res.cifers = (unsigned int*)malloc((res.size)*sizeof(unsigned int));
        res.cifers[0] = 0;
        free(divider.cifers);
        return res;
    }
    
    
    if (divider.size == 1)
    {
        long_number res;
        res.size = A.size;
        res.cifers = (unsigned int*)malloc((res.size)*sizeof(unsigned int));
        
        unsigned long long int carry = 0;
        int i;
        for (i = A.size - 1; i >= 0; i--)
        {
            unsigned long long int temp = carry;
            temp *= BASIS;
            temp += A.cifers[i];
            res.cifers[i] = temp / divider.cifers[0];
            carry = (unsigned long long int)  temp - (unsigned long long int) res.cifers[i] * (unsigned long long int) divider.cifers[0];
        }
        ostatok->sign = (A.sign != B.sign);
        if (ostatok->size > 0)
            free(ostatok->cifers);
        
        ostatok->size = 1;
        ostatok->cifers = (unsigned int*)malloc((1)*sizeof(unsigned int));
        
        ostatok->cifers[0] = carry;
        *ostatok = deleteNulls(*ostatok);
        res.sign = (A.sign != B.sign);
        res = deleteNulls(res);
        free(divider.cifers);
        return res;
    }
    
    
    long_number res;
    res.sign = 0;
    res.size = A.size - B.size + 1;
    res.cifers = (unsigned int*)malloc((res.size)*sizeof(unsigned int));
    
    int i;
    for (i = A.size - B.size + 1; i != 0; i--)
    {
        long long int qGuessMax = BASIS;
        long long int qGuessMin = 0;
        long long int qGuess = qGuessMax;
        
        while (qGuessMax - qGuessMin > 1)
        {
            qGuess = (qGuessMax + qGuessMin) / 2;
            
          
            long_number qGuesslong_number = create_from_int(qGuess);
            long_number tmp = mul(divider, qGuesslong_number);
            free(qGuesslong_number.cifers);
            tmp = toLeft(tmp, i - 1);
            
            if (long_num_cmp(tmp, *ostatok) > 0)
                qGuessMax = qGuess;
            else
                qGuessMin = qGuess;
            
            free(tmp.cifers);
        }
        
        long_number qGuessMinlong_number = create_from_int(qGuessMin);
        long_number tmp = mul(divider, qGuessMinlong_number);
        free(qGuessMinlong_number.cifers);
        tmp = toLeft(tmp, i - 1);
       
        long_number tmpRem = long_num_copy(*ostatok);
        long_number minusTmp = chsign(tmp);
        free(ostatok->cifers);
        *ostatok = SumOrSub(tmpRem, minusTmp);
        free(tmpRem.cifers);
        free(minusTmp.cifers);
        free(tmp.cifers);
        
        res.cifers[i - 1] = qGuessMin;
    }
    
    res.sign = (A.sign != B.sign);
    ostatok->sign = (A.sign != B.sign);
    *ostatok = deleteNulls(*ostatok);
    res = deleteNulls(res);
    
    free(divider.cifers);
    return res;
}

long_number invoke(long_number base, long_number exp)
{
    
    long_number res = create_from_int(1);
    long_number zero = create_from_int(0);
    long_number i = long_num_copy(exp);
    long_number minusOne = create_from_int(-1); // -1
    
    while (long_num_cmp(i, zero) > 0)
    {
        long_number tmp = mul(res, base);
        free(res.cifers);
        res = tmp;
        
        tmp = SumOrSub(i, minusOne);
        free(i.cifers);
        i = tmp;
    }
    
    // Ó˜Ë˘‡ÂÏ Ô‡ÏˇÚ¸
    free(i.cifers);
    free(zero.cifers);
    free(minusOne.cifers);
    
    return res;
}

long_number invoke_module(long_number base, long_number exp, long_number modulus)
{
  
    long_number res = create_from_int(1);
    long_number zero = create_from_int(0);
    long_number i = long_num_copy(exp);
    long_number minusOne = create_from_int(-1); // -1
    
    
    while (long_num_cmp(i, zero) > 0)
    {
        long_number tmp = mul(res, base);
        long_number modRem;
        long_number tmp2 = divd(tmp, modulus, &modRem);
        free(tmp2.cifers);
        free(tmp.cifers);
        free(res.cifers);
        res = modRem;
        
        tmp = SumOrSub(i, minusOne);
        free(i.cifers);
        i = tmp;
    }
    
    free(i.cifers);
    free(zero.cifers);
    free(minusOne.cifers);
    
    return res;
}

long_number binaryRead(char* filename)
{
    
    FILE* pfSource = fopen(filename, "r+b");
    if (!pfSource)
    {
        printf("An error in reading input file\n");
        long_number res;
        res.size = 0;
        res.sign = 0;
        res.cifers = NULL;
        return res;
    }
    
    fseek(pfSource, 0, SEEK_END);
    int fileSize = ftell(pfSource);
    hlv[r] = fileSize; r++;
    fseek(pfSource, 0, SEEK_SET);
    
  
    unsigned char* fileContent = (unsigned char*)malloc(fileSize);
    fread((char*)fileContent, sizeof(unsigned char), fileSize, pfSource);
    fclose(pfSource);
    
    long_number pow256 = create_from_int(1);
    long_number res = create_from_int(0);
    long_number b256 = create_from_int(256);
    
    int i;
    for (i = 0; i < fileSize; i++)
    {
        long_number fi = create_from_int(fileContent[i]);
        long_number tmp = mul(fi, pow256);
        free(fi.cifers);
        
        long_number tmp2 = SumOrSub(res, tmp);
        free(tmp.cifers);
        free(res.cifers);
        res = tmp2;
        
        tmp = mul(pow256, b256);
        free(pow256.cifers);
        pow256 = tmp;
    }
    
    free(fileContent);
    free(pow256.cifers);
    free(b256.cifers);
    printf("Number was succesfully read from file\n");
    return res;
}

int binaryWrite(char* filename, long_number A, int flag_oper)
{
    
    FILE* pfDestination = fopen(filename, "w+b");
    if (!pfDestination)
    {
        printf("Can't open output file");
        return 1;
    }
    
    struct long_number tmp = long_num_copy(A);
    tmp.sign = 0;
    long_number zero = create_from_int(0);
    long_number b256 = create_from_int(256);
    
    hlv[2] = 0;
    while (long_num_cmp(tmp, zero) != 0)
    {
        long_number ostatok;
        
        // tmp = tmp / 256
        long_number tmp2 = divd(tmp, b256, &ostatok);
        free(tmp.cifers);
        tmp = tmp2;
        
     
        unsigned char ost = ostatok.cifers[0];
        fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
        free(ostatok.cifers);
        hlv[2]++;
    }
    
    if (flag_oper == 4)
    {
        for (int i = tmp.size; i < hlv[0] - hlv[1] - hlv[2] + 1; i++)
        {
            unsigned char ost = NULL;
            fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
        }
    }
    
    if (flag_oper == 3)
    {
        printf("hlv[0] = %d, hlv[1] = %d, hlv[2] = %d\n", hlv[0],hlv[1],hlv[2]);
        for (int i = tmp.size; i < hlv[0] + hlv[1] - hlv[2] + 1; i++)
        {
            unsigned char ost = NULL;
            fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
        }
    }
    
    
    if (flag_oper == 1)
    {
        int carries = 0;
        if (hlv[0] > hlv[1])
            carries = hlv[0]-hlv[2] +2;
        else
            carries = hlv[1]-hlv[2] +2;
        
        for (int i = tmp.size; i < carries; i++)
        {
            unsigned char ost = NULL;
            fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
        }
    }
    
    if (flag_oper == 2)
    {
        
        for (int i = tmp.size; i < 16; i++)
        {
            unsigned char ost = NULL;
            fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
        }
    }

    
    free(tmp.cifers);
    free(b256.cifers);
    free(zero.cifers);
    
    fclose(pfDestination);
    printf("Number was succesfully written to file\n");
    return 0;
}

long_number fileRead(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (!fp)
    {
        printf("An error in reading input file\n");
        long_number res;
        res.size = 0;
        res.sign = 0;
        res.cifers = NULL;
        return res;
    }
    
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    
    char* fileContent = (char*)malloc(fileSize + 1);
    fscanf(fp, "%s", fileContent);
    fileContent[fileSize] = '\0';
    fclose(fp);
    long_number res = from_str(fileContent);
    free(fileContent);
    printf("Number was succesfully read from file\n");
    return res;
}

int fileWrite(char *fileName, long_number A)
{
    FILE *fp = fopen(fileName, "w");
    if (!fp)
    {
        printf("Can't open output file");
        return 1;
    }
    
    char *res = gt_str(A);
    
    fprintf(fp, "%s", res);
    fclose(fp);
    free(res);
    printf("Number was succesfully written to file\n");
    return 0;
}