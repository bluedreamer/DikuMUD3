/*
 $Author: tperry $
 $RCSfile: bytestring.h,v $
 $Date: 2001/04/29 03:46:05 $
 $Revision: 2.1 $
 */
#pragma once

#include "essential.h"

class CByteBuffer
{
public:
    CByteBuffer(ubit32 nSize = 1024);
    virtual ~CByteBuffer();

    // Informative functions

    inline ubit32 GetLength() { return m_nLength; }
    inline ubit32 GetAllocated() { return m_nAllocated; }
    inline ubit32 GetReadPosition() { return m_nReadPos; }
    inline const uint8_t *GetData() { return m_pData; }

    void SetReadPosition(ubit32 nReadPosition);
    void SetLength(ubit32 nLen);
    void SetData(uint8_t *pData, ubit32 nLength);

    inline void Rewind() { m_nReadPos = 0; }
    inline void Clear()
    {
        m_nReadPos = 0;
        m_nLength = 0;
        assert(m_nAllocated > 0);
        *m_pData = 0;
    }

    // Public
    //
    int FileRead(FILE *f, ubit32 nLength);
    int FileRead(FILE *f, long offset, ubit32 length);
    int FileWrite(FILE *f);

    // Public functions to read from a buffer
    //
    int Read(uint8_t *pBuf, ubit32 nLen);

    int ReadBlock(uint8_t **pData, ubit32 *nLen);

    // The Read8 format drove me a little mad to read, trying this.
    uint8_t ReadU8(int *nError = nullptr);
    int8_t ReadS8(int *nError = nullptr);
    ubit16 ReadU16(int *nError = nullptr);
    int16_t ReadS16(int *nError = nullptr);
    ubit32 ReadU32(int *nError = nullptr);
    sbit32 ReadS32(int *nError = nullptr);

    [[deprecated("Replace with ReadU8")]] int Read8(uint8_t *pNum);   ///< @deprecated Replace with @ref ReadU8
    [[deprecated("Replace with ReadU16")]] int Read16(ubit16 *pNum);  ///< @deprecated Replace with @ref ReadU16
    [[deprecated("Replace with ReadU32")]] int Read32(ubit32 *pNum);  ///< @deprecated Replace with @ref ReadU32
    [[deprecated("Replace with ReadS8")]] int Read8(int8_t *pNum);    ///< @deprecated Replace with @ref ReadS8
    [[deprecated("Replace with ReadS16")]] int Read16(int16_t *pNum); ///< @deprecated Replace with @ref ReadS16
    [[deprecated("Replace with ReadS32")]] int Read32(sbit32 *pNum);  ///< @deprecated Replace with @ref ReadS32
    int ReadFloat(float *pFloat);
    int ReadStringAlloc(char **pStr);
    int ReadStringCopy(char *pStr, ubit32 nSize);
    int ReadNames(char ***pppStr, int bOld);
    int ReadIntList(int **ilist);

    int Skip(int n);
    int Skip8();
    int Skip16();
    int Skip32();
    int SkipFloat();
    int SkipString(char **ppStr = nullptr);
    int SkipNames();
    int SkipVals();

    // Public functions to write to a buffer
    //
    void Append(const uint8_t *pData, ubit32 nLen);

    void Append(CByteBuffer *pBuf);

    void AppendBlock(const uint8_t *pData, ubit32 nLen);

    void Append8(uint8_t i);
    void Append16(ubit16 i);
    void Append32(ubit32 i);
    void AppendFloat(float f);
    void AppendString(const char *pStr);
    void AppendDoubleString(const char *pStr);
    void AppendNames(const char **ppNames, int bOld);

protected:
    void SetSize(ubit32 nSize);
    void IncreaseSize(ubit32 nSize);

private:
    ubit32 m_nReadPos;
    ubit32 m_nLength;
    ubit32 m_nAllocated;
    uint8_t *m_pData;
};

uint8_t bread_ubit8(uint8_t **buf);
ubit16 bread_ubit16(uint8_t **buf);
ubit32 bread_ubit32(uint8_t **buf);
float bread_float(uint8_t **buf);
uint8_t *bread_data(uint8_t **b, ubit32 *len);
void bwrite_data(uint8_t **b, uint8_t *data, ubit32 len);
void bread_strcpy(uint8_t **b, char *str);
char *bread_str_alloc(uint8_t **buf);
char *bread_str_skip(uint8_t **b);
char **bread_nameblock(uint8_t **b, int bOld);

void bwrite_ubit8(uint8_t **b, uint8_t i);
void bwrite_ubit16(uint8_t **b, ubit16 i);
void bwrite_ubit32(uint8_t **b, ubit32 i);
void bwrite_float(uint8_t **b, float f);
void bwrite_string(uint8_t **b, const char *str);
void bwrite_double_string(uint8_t **b, char *str);
void bwrite_nameblock(uint8_t **b, char **nb, int bOld);
void bwrite_intblock(uint8_t **b, int *nb);
