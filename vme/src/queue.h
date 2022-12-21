/*
 $Author: tperry $
 $RCSfile: queue.h,v $
 $Date: 2001/04/29 03:46:07 $
 $Revision: 2.1 $
 */
#pragma once

#include "essential.h"

// To use, inherit this type into your data structure.
class cQueueElem
{
    friend class cQueue;

public:
    cQueueElem(char *c, int bCopy = TRUE);
    cQueueElem(uint8_t *d, uint32_t n, int bCopy = TRUE);
    ~cQueueElem()
    {
        if (pData)
            FREE(pData);
    }

    uint32_t Bytes() { return nSize; }
    uint8_t *Data() { return pData; }
    void SetNull()
    {
        pData = nullptr;
        nSize = 0;
    }

    cQueueElem *PeekNext() { return pNext; }

private:
    uint8_t *pData;
    uint32_t nSize; ///< Optional number of bytes
    cQueueElem *pNext;
};

class cQueue
{
public:
    cQueue();
    ~cQueue();

    int IsEmpty();
    uint32_t Size();
    uint32_t Bytes();

    void Copy(uint8_t *data, uint32_t nLen);
    void CutCopy(uint8_t *data, uint32_t nLen);
    void Cut(uint32_t nLen);

    void Append(cQueueElem *pe);
    void Prepend(cQueueElem *pe);

    cQueueElem *GetHead();

    const cQueueElem *PeekHead();
    const cQueueElem *PeekTail();

    void Flush();

private:
    cQueueElem *pHead;
    cQueueElem *pTail;
    cQueueElem *pPreTail;

    uint32_t nEntries;
    uint32_t nBytes;
};
