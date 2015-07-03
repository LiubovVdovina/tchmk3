%module long_number_lib
%{
/* Includes the header in the wrapped code */
#include "long_number_lib.h"
%}

/* Parse the header file to generate wrappers */
%include "long_number_lib.h"
