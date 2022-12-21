/*
 $Author: tperry $
 $RCSfile: dilpar.h,v $
 $Date: 2002/06/09 23:27:41 $
 $Revision: 2.1 $
 */
#pragma once

#include "dil.h"
#include "essential.h"

#define DIL_VERSION "v5.10"

#define SYMSIZE 40

/* This is for the compiler */

#define CODESIZE 16768 /* maximum expression size */

struct exptype
{
    uint8_t dsl;       ///< static/dynamic/lvalue, type, req type
    DilVarType_e typ;  ///< static/dynamic/lvalue, type, req type
    DilVarType_e rtyp; ///< static/dynamic/lvalue, type, req type
    uint8_t boolean;   ///< if expression contains boolean op
    sbit32 num;        ///< static value INT or field type
    uint8_t *code;     ///< code / static value SP
    uint8_t *codep;    ///< code write pointer
};

struct dilref
{
    char *zname;        ///< func/proc name
    char *name;         ///< zone name
    DilVarType_e rtnt;  ///< return type
    uint8_t argc;       ///< number of arguments (min 1)
    DilVarType_e *argt; ///< argument types
    char **argv;        ///< argument names
};
