/*
 $Author: tperry $
 $RCSfile: bytestring.cpp,v $
 $Date: 2002/06/09 23:27:39 $
 $Revision: 2.2 $
 */

#include "bytestring.h"

#include "essential.h"
#include "textutil.h"

#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

/* =================================================================== */
/* =================================================================== */

CByteBuffer::CByteBuffer(uint32_t nSize)
{
    assert(nSize > 0);
    m_nLength = 0;
    m_nReadPos = 0;
    m_nAllocated = nSize;
    CREATE(m_pData, uint8_t, nSize);

    assert(m_pData != nullptr);
    *m_pData = 0;
}

CByteBuffer::~CByteBuffer()
{
    FREE(m_pData);
}

void CByteBuffer::SetReadPosition(uint32_t nReadPosition)
{
    m_nReadPos = nReadPosition;
}

void CByteBuffer::SetLength(uint32_t nLen)
{
    m_nLength = nLen;
}

void CByteBuffer::SetSize(uint32_t nSize)
{
    assert(nSize > 0);
    RECREATE(m_pData, uint8_t, nSize);
    assert(m_pData);
    m_nAllocated = nSize;
}

void CByteBuffer::SetData(uint8_t *pData, uint32_t nSize)
{
    assert(nSize > 0);

    if (m_pData)
        FREE(m_pData);
    Clear();

    m_pData = pData;
    assert(m_pData);

    m_nAllocated = nSize;
    m_nLength = nSize;
}

void CByteBuffer::IncreaseSize(uint32_t nAdd)
{
    if (nAdd > m_nAllocated)
    {
        m_nAllocated += nAdd + 128;
    }
    else
    {
        m_nAllocated *= 2;
    }

    SetSize(m_nAllocated);
}

// Returns number of bytes read
int CByteBuffer::FileRead(FILE *f, uint32_t nLength)
{
    Clear();

    if (m_nAllocated < nLength)
    {
        IncreaseSize(nLength - m_nAllocated + 1);
    }

    int n = fread(m_pData, 1, nLength, f);

    if (n > 0)
    {
        m_nLength = n;
    }

    return n;
}

int CByteBuffer::FileWrite(FILE *f)
{
    if (m_nLength > 0)
    {
        return fwrite(m_pData, 1, m_nLength, f);
    }
    else
    {
        return 0;
    }
}

// Returns number of bytes read or -1 on unable to position
int CByteBuffer::FileRead(FILE *f, long nOffset, uint32_t nLength)
{
    Clear();

    if (m_nAllocated < nLength)
    {
        IncreaseSize(nLength - m_nAllocated + 1);
    }

    if (fseek(f, nOffset, SEEK_SET))
    {
        return -1;
    }

    int n = fread(m_pData, 1, nLength, f);

    if (n > 0)
    {
        m_nLength = nLength;
    }

    return n;
}

/// @returns 0 if OK, return 1 if not OK
int CByteBuffer::Read(uint8_t *pBuf, uint32_t nLen)
{
    if (m_nReadPos + nLen > m_nLength)
    {
        return 1;
    }

    memcpy(pBuf, m_pData + m_nReadPos, nLen);
    m_nReadPos += nLen;

    return 0;
}

uint8_t CByteBuffer::ReadU8(int *nError)
{
    uint8_t n = 0;

    if (Read((uint8_t *)&n, sizeof(uint8_t)))
    {
        if (nError)
        {
            (*nError)++;
        }
    }

    return n;
}

int8_t CByteBuffer::ReadS8(int *nError)
{
    int8_t n = 0;

    if (Read((uint8_t *)&n, sizeof(int8_t)))
    {
        if (nError)
        {
            (*nError)++;
        }
    }

    return n;
}

uint16_t CByteBuffer::ReadU16(int *nError)
{
    uint16_t n = 0;

    if (Read((uint8_t *)&n, sizeof(uint16_t)))
    {
        if (nError)
        {
            (*nError)++;
        }
    }

    return n;
}

int16_t CByteBuffer::ReadS16(int *nError)
{
    int16_t n = 0;

    if (Read((uint8_t *)&n, sizeof(int16_t)))
    {
        if (nError)
        {
            (*nError)++;
        }
    }

    return n;
}

uint32_t CByteBuffer::ReadU32(int *nError)
{
    uint32_t n = 0;

    if (Read((uint8_t *)&n, sizeof(uint32_t)))
    {
        if (nError)
        {
            (*nError)++;
        }
    }

    return n;
}

int32_t CByteBuffer::ReadS32(int *nError)
{
    int32_t n = 0;

    if (Read((uint8_t *)&n, sizeof(int32_t)))
    {
        if (nError)
        {
            (*nError)++;
        }
    }

    return n;
}

int CByteBuffer::Read8(uint8_t *pNum)
{
    return Read(pNum, sizeof(uint8_t));
}

int CByteBuffer::Read8(int8_t *pNum)
{
    return Read((uint8_t *)pNum, sizeof(uint8_t));
}

int CByteBuffer::Read16(uint16_t *pNum)
{
    return Read((uint8_t *)pNum, sizeof(uint16_t));
}

int CByteBuffer::Read16(int16_t *pNum)
{
    return Read((uint8_t *)pNum, sizeof(int16_t));
}

int CByteBuffer::Read32(uint32_t *pNum)
{
    return Read((uint8_t *)pNum, sizeof(uint32_t));
}

int CByteBuffer::Read32(int32_t *pNum)
{
    return Read((uint8_t *)pNum, sizeof(int32_t));
}

int CByteBuffer::ReadFloat(float *pFloat)
{
    return Read((uint8_t *)pFloat, sizeof(float));
}

int CByteBuffer::ReadStringCopy(char *pStr, uint32_t nMaxSize)
{
    uint32_t nLen = 1 + strlen((char *)m_pData + m_nReadPos);

    if (nLen > nMaxSize)
    {
        pStr[0] = 0;
        return 1;
    }

    return Read((uint8_t *)pStr, nLen);
}

int CByteBuffer::ReadStringAlloc(char **ppStr)
{
    int nLen = 1 + strlen((char *)m_pData + m_nReadPos);

    if (nLen == 1)
    {
        *ppStr = nullptr;
        return Skip8();
    }

    *ppStr = (char *)malloc(nLen);

    assert(*ppStr);

    return Read((uint8_t *)*ppStr, nLen);
}

int CByteBuffer::ReadNames(char ***pppStr, int bOld)
{
    char *c = nullptr;
    *pppStr = create_namelist();
    assert(*pppStr);

    if (bOld)
    {
        for (;;)
        {
            if (SkipString(&c))
            {
                return 1;
            }

            if (*c)
            {
                *pppStr = add_name(c, *pppStr);
            }
            else
            {
                break;
            }
        }
    }
    else // New xxx
    {
        int l = 0;
        int Corrupt = 0;
        char buf[MAX_STRING_LENGTH];

        l = ReadS32(&Corrupt);

        int i = 0;

        for (i = 0; i < l; i++)
        {
            Corrupt += ReadStringCopy(buf, sizeof(buf) - 1);
            *pppStr = add_name(buf, *pppStr);
        }

        return Corrupt;
    }
    return 0;
}

int CByteBuffer::ReadIntList(int **ilist)
{
    int32_t len = 0;
    int corrupt = 0;
    int c = 0;
    int i = 0;
    int *intlist = nullptr;
    intlist = *ilist;

    len = ReadS32(&corrupt);

    if (corrupt)
    {
        return 1;
    }

    CREATE(intlist, int, len + 1);
    intlist[0] = len;
    for (i = 1; i <= len; i++)
    {
        c = ReadS32(&corrupt);
        if (corrupt)
        {
            assert(FALSE);
        }

        intlist[i] = c;
    }
    *ilist = intlist;
    return 0;
}

int CByteBuffer::ReadBlock(uint8_t **ppData, uint32_t *pnLen)
{
    int corrupt = 0;
    *ppData = nullptr;

    *pnLen = ReadS32(&corrupt);
    if (corrupt)
    {
        return 1;
    }

    *ppData = (uint8_t *)malloc(*pnLen);

    if (ppData == nullptr)
    {
        return 1;
    }

    return Read(*ppData, *pnLen);
}

int CByteBuffer::Skip(int nLen)
{
    if (m_nReadPos + nLen > m_nLength)
    {
        return 1;
    }

    m_nReadPos += nLen;

    return 0;
}

int CByteBuffer::Skip8()
{
    return Skip(sizeof(uint8_t));
}

int CByteBuffer::Skip16()
{
    return Skip(sizeof(uint16_t));
}

int CByteBuffer::Skip32()
{
    return Skip(sizeof(uint32_t));
}

int CByteBuffer::SkipFloat()
{
    return Skip(sizeof(float));
}

int CByteBuffer::SkipString(char **ppStr)
{
    if (ppStr)
    {
        *ppStr = (char *)m_pData + m_nReadPos;
    }

    return Skip(1 + strlen((char *)m_pData + m_nReadPos));
}

int CByteBuffer::SkipNames()
{
    char *c = nullptr;
    unsigned int len = 0;
    unsigned int i = 0;
    int corrupt = 0;

    len = ReadS32(&corrupt);

    if (corrupt)
    {
        assert(FALSE);
    }

    for (i = 0; i < len; i++)
    {
        SkipString(&c);
    }

    return 0;
}

int CByteBuffer::SkipVals()
{
    unsigned int len = 0;
    unsigned int i = 0;
    int corrupt = 0;

    len = ReadS32(&corrupt);

    if (corrupt)
    {
        assert(FALSE);
    }

    for (i = 0; i < len; i++)
    {
        if (Skip32())
        {
            return 1;
        }
    }

    return 0;
}

void CByteBuffer::Append(const uint8_t *pData, uint32_t nLen)
{
    if (nLen + m_nLength > m_nAllocated)
    {
        IncreaseSize(nLen);
    }

    memcpy(m_pData + m_nLength, pData, nLen);

    m_nLength += nLen;
}

void CByteBuffer::Append(CByteBuffer *pBuf)
{
    Append(pBuf->GetData(), pBuf->GetLength());
}

void CByteBuffer::Append8(uint8_t i)
{
    Append(&i, sizeof(i));
}

void CByteBuffer::Append16(uint16_t i)
{
    Append((uint8_t *)&i, sizeof(i));
}

void CByteBuffer::Append32(uint32_t i)
{
    Append((uint8_t *)&i, sizeof(i));
}

void CByteBuffer::AppendFloat(float f)
{
    Append((uint8_t *)&f, sizeof(f));
}

void CByteBuffer::AppendBlock(const uint8_t *pData, uint32_t nLen)
{
    Append32(nLen);
    Append(pData, nLen);
}

void CByteBuffer::AppendString(const char *pStr)
{
    if (pStr)
    {
        Append((uint8_t *)pStr, strlen(pStr) + 1);
    }
    else
    {
        AppendString("");
    }
}

void CByteBuffer::AppendDoubleString(const char *pStr)
{
    if (pStr)
    {
        AppendString(pStr);
        TAIL(pStr);
        AppendString(pStr + 1);
    }
    else
    {
        AppendString("");
        AppendString("");
    }
}

void CByteBuffer::AppendNames(const char **ppNames, int bOld)
{
    if (bOld)
    {
        if (ppNames)
        {
            for (; (const char *)*ppNames && **ppNames; ppNames++)
            {
                AppendString(*ppNames);
            }
        }
        AppendString("");
    }
    else // New xxx
    {
        int l = len_namelist(ppNames);

        Append32(l);

        int i = 0;
        for (i = 0; i < l; i++)
        {
            AppendString(ppNames[i]);
        }
    }
}

/* =================================================================== */
/* =================================================================== */

uint8_t bread_ubit8(uint8_t **b)
{
    uint8_t i = 0;

    memcpy((uint8_t *)&i, *b, sizeof(uint8_t));
    *b += sizeof(uint8_t);

    return i;
}

uint16_t bread_ubit16(uint8_t **b)
{
    uint16_t i = 0;

    memcpy((uint8_t *)&i, *b, sizeof(uint16_t));
    *b += sizeof(uint16_t);

    return i;
}

uint32_t bread_ubit32(uint8_t **b)
{
    uint32_t i = 0;

    memcpy((uint8_t *)&i, *b, sizeof(uint32_t));
    *b += sizeof(uint32_t);

    return i;
}

float bread_float(uint8_t **b)
{
    float f = NAN;

    memcpy((uint8_t *)&f, *b, sizeof(float));
    *b += sizeof(float);

    return f;
}

uint8_t *bread_data(uint8_t **b, uint32_t *plen)
{
    uint32_t len = 0;
    uint8_t *data = nullptr;

    data = nullptr;
    len = bread_ubit32(b);
    if (plen)
    {
        *plen = len;
    }

    if (len > 0)
    {
        CREATE(data, uint8_t, len);
        memcpy(data, *b, len);
        *b += len;
    }

    return data;
}

/**
 * Stored: as Null terminated string
 * Copy string from **b into *str
 */
void bread_strcpy(uint8_t **b, char *str)
{
    for (; (*str++ = **b); (*b)++)
    {
        ;
    }
    (*b)++;
}

/**
 * Stored: as Null terminated string
 *  Will allocate space for string, if the read
 *  string is one or more characters, and return
 *  pointer to allocated string (or 0)
 */
char *bread_str_alloc(uint8_t **b)
{
    if (**b)
    {
        char *c = nullptr;
        char *t = nullptr;
        t = (char *)*b;

        c = str_dup(t);

        *b += strlen(c) + 1;
        return c;
    }

    (*b)++;
    return nullptr;
}

/**
 * @returns pointer to the string and skips past the end to next
 * point in buffer
 */
char *bread_str_skip(uint8_t **b)
{
    char *o = (char *)*b;

    TAIL(*b);
    (*b)++;

    return o;
}

/**
 * Stored: As 'N' strings followed by the empty
 * string ("")
 * @returns * to nameblock, nameblock may be
 * but is never null ({""}).
 */
char **bread_nameblock(uint8_t **b, int bOld)
{
    char buf[MAX_STRING_LENGTH];
    char **nb = nullptr;

    nb = create_namelist();

    if (bOld)
    {
        for (;;)
        {
            bread_strcpy(b, buf);
            if (*buf)
            {
                nb = add_name(buf, nb);
            }
            else
            {
                break;
            }
        }
    }
    else // New xxx
    {
        int l = 0;

        l = bread_ubit32(b);

        int i = 0;

        for (i = 0; i < l; i++)
        {
            bread_strcpy(b, buf);
            nb = add_name(buf, nb);
        }
    }
    return nb;
}

void bwrite_ubit8(uint8_t **b, uint8_t i)
{
    **b = i;
    *b += sizeof(uint8_t);
}

void bwrite_ubit16(uint8_t **b, uint16_t i)
{
    memcpy(*b, (uint8_t *)&i, sizeof(uint16_t));
    *b += sizeof(uint16_t);
}

void bwrite_ubit32(uint8_t **b, uint32_t i)
{
    memcpy(*b, (uint8_t *)&i, sizeof(uint32_t));
    *b += sizeof(uint32_t);
}

void bwrite_sbit32(uint8_t **b, int32_t i)
{
    int x = 0;
    x = i;
    memcpy(*b, (uint8_t *)&x, sizeof(int32_t));
    fprintf(stderr, "Sbit32 out %d\n", x);
    *b += sizeof(int32_t);
}

void bwrite_float(uint8_t **b, float f)
{
    memcpy(*b, (uint8_t *)&f, sizeof(float));
    *b += sizeof(float);
}

void bwrite_data(uint8_t **b, uint8_t *data, uint32_t len)
{
    bwrite_ubit32(b, len);
    if (len > 0)
    {
        memcpy(*b, data, len);
        *b += len;
    }
}

/**
 * String is stored as Null terminated string
 * Space is NOT allocated if string is 0 length
 * but NIL is returned
 */
void bwrite_string(uint8_t **b, const char *str)
{
    if (str)
    {
        for (; *str; str++, (*b)++)
        {
            **b = *str;
        }

        **b = '\0';
        *b += 1;
    }
    else
    {
        **b = '\0';
        *b += 1;
    }
}

/**
 * Write a string of the format:  ssss\0ssss\0
 */
void bwrite_double_string(uint8_t **b, char *str)
{
    int i = 0;

    if (str)
    {
        for (i = 0; i < 2; str++, (*b)++, (*str ? 0 : i++))
        {
            **b = *str;
        }

        **b = '\0';
        *b += 1;
    }
    else
    {
        bwrite_string(b, "");
        bwrite_string(b, "");
    }
}

/**
 * Stored: As 'N' strings followed by the empty string ("")
 */
void bwrite_nameblock(uint8_t **b, char **nb, int bOld)
{
    if (bOld)
    {
        if (nb)
        {
            for (; *nb && **nb; nb++)
            {
                bwrite_string(b, *nb);
            }
        }

        bwrite_string(b, "");
    }
    else // New method xxx
    {
        int l = 0;

        l = len_namelist((const char **)nb);
        bwrite_ubit32(b, l);

        for (int i = 0; i < l; i++)
        {
            bwrite_string(b, nb[i]);
        }
    }
}

/**
 * number of ints, followed by ints
 */
void bwrite_intblock(uint8_t **b, int *ib)
{
    int i = 0;
    i = ib[0];
    if (i > 0)
    {
        memcpy(*b, ib, i * sizeof(int32_t));
        *b += i * sizeof(int32_t);
    }
    else
    {
        bwrite_ubit32(b, 0);
    }
    /*	  bwrite_sbit32(b,ib[0]);
        fprintf(stderr, "intlist Len %d\n", ib[0]);
         for (i=1; i<=ib[0]; i++) {
        fprintf(stderr, "intlist %d=%d\n", i, ib[i]);
           bwrite_sbit32(b,ib[i]);
          }*/
}
