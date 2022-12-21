/*
 $Author: All $
 $RCSfile: namelist.h,v $
 $Date: 2004/09/18 19:52:56 $
 $Revision: 2.6 $
 */
#pragma once

#include "bytestring.h"

#include <string>

class cNamelist
{
public:
    cNamelist();
    cNamelist(const char **list);
    ~cNamelist();
    void operator=(cNamelist *cn);
    void operator=(const char **);
    void Free();
    void CopyList(const char **list);
    void CopyList(cNamelist *);

    void AppendBuffer(CByteBuffer *pBuf);
    int ReadBuffer(CByteBuffer *pBuf, int unit_version);
    void bread(uint8_t **b);
    void bwrite(uint8_t **b);

    char *catnames();
    std::string json();

    void Remove(uint32_t idx);
    void RemoveName(const char *name);

    void Substitute(uint32_t idx, const char *newname);
    const char *Name(uint32_t idx = 0) const;
    std::string *InstanceName(uint32_t idx = 0);

    void AppendNameTrim(const char *name);
    void AppendName(const char *name);
    void PrependName(const char *name);
    void InsertName(const char *name, uint32_t loc);

    cNamelist *Duplicate();

    const int IsNameIdx(const char *name);
    const int IsNameRawIdx(const char *name);
    const char *IsNameRaw(const char *name);
    const char *IsNameRaw(const char *name) const;
    const char *IsNameRawAbbrev(const char *name);
    const char *IsNameRawAbbrev(const char *name) const;
    const char *IsName(const char *name);

    const char *StrStrRaw(const char *name);
    const char *StrStr(const char *name);

    inline uint32_t Length() { return length; }

private:
    std::string **namelist;
    uint32_t length;
};
