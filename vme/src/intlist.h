/*
 $Author: tperry $
 $RCSfile: intlist.h,v $
 $Date: 2002/05/22 01:35:59 $
 $Revision: 2.2 $
 */
#pragma once

#include "bytestring.h"
#include "essential.h"

#include <string>

class cintlist
{
public:
    cintlist();
    ~cintlist();
    void operator=(cintlist *cint);
    void CopyList(cintlist *cint);
    void Free();
    cintlist *Duplicate();
    void Replace(int idx, int val);
    char *catnames();
    std::string json();
    int Value(int idx);
    int32_t *ValuePtr(int idx);
    void Remove(int idx);
    void AppendBuffer(CByteBuffer *pBuf);
    int ReadBuffer(CByteBuffer *pBuf);
    void Append(int val);
    void Prepend(int val);
    void Insert(int val, int loc);
    void bread(uint8_t **b);
    inline int32_t Length() { return length; }

private:
    int *intlist;
    int32_t length;
};
