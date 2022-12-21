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
    CByteBuffer(uint32_t nSize = 1024);
    virtual ~CByteBuffer();

    // Informative functions

    inline uint32_t GetLength() { return m_nLength; }
    inline uint32_t GetAllocated() { return m_nAllocated; }
    inline uint32_t GetReadPosition() { return m_nReadPos; }
    inline const uint8_t *GetData() { return m_pData; }

    void SetReadPosition(uint32_t nReadPosition);
    void SetLength(uint32_t nLen);
    void SetData(uint8_t *pData, uint32_t nLength);

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
    int FileRead(FILE *f, uint32_t nLength);
    int FileRead(FILE *f, long offset, uint32_t length);
    int FileWrite(FILE *f);

    // Public functions to read from a buffer
    //
    int Read(uint8_t *pBuf, uint32_t nLen);

    int ReadBlock(uint8_t **pData, uint32_t *nLen);

    // The Read8 format drove me a little mad to read, trying this.
    uint8_t ReadU8(int *nError = nullptr);
    int8_t ReadS8(int *nError = nullptr);
    uint16_t ReadU16(int *nError = nullptr);
    int16_t ReadS16(int *nError = nullptr);
    uint32_t ReadU32(int *nError = nullptr);
    int32_t ReadS32(int *nError = nullptr);

    [[deprecated("Replace with ReadU8")]] int Read8(uint8_t *pNum);    ///< @deprecated Replace with @ref ReadU8
    [[deprecated("Replace with ReadU16")]] int Read16(uint16_t *pNum); ///< @deprecated Replace with @ref ReadU16
    [[deprecated("Replace with ReadU32")]] int Read32(uint32_t *pNum); ///< @deprecated Replace with @ref ReadU32
    [[deprecated("Replace with ReadS8")]] int Read8(int8_t *pNum);     ///< @deprecated Replace with @ref ReadS8
    [[deprecated("Replace with ReadS16")]] int Read16(int16_t *pNum);  ///< @deprecated Replace with @ref ReadS16
    [[deprecated("Replace with ReadS32")]] int Read32(int32_t *pNum);  ///< @deprecated Replace with @ref ReadS32
    int ReadFloat(float *pFloat);
    int ReadStringAlloc(char **pStr);
    int ReadStringCopy(char *pStr, uint32_t nSize);
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
    void Append(const uint8_t *pData, uint32_t nLen);

    void Append(CByteBuffer *pBuf);

    void AppendBlock(const uint8_t *pData, uint32_t nLen);

    void Append8(uint8_t i);
    void Append16(uint16_t i);
    void Append32(uint32_t i);
    void AppendFloat(float f);
    void AppendString(const char *pStr);
    void AppendDoubleString(const char *pStr);
    void AppendNames(const char **ppNames, int bOld);

protected:
    void SetSize(uint32_t nSize);
    void IncreaseSize(uint32_t nSize);

private:
    uint32_t m_nReadPos;
    uint32_t m_nLength;
    uint32_t m_nAllocated;
    uint8_t *m_pData;
};

uint8_t bread_ubit8(uint8_t **buf);
uint16_t bread_ubit16(uint8_t **buf);
uint32_t bread_ubit32(uint8_t **buf);
float bread_float(uint8_t **buf);
uint8_t *bread_data(uint8_t **b, uint32_t *len);
void bwrite_data(uint8_t **b, uint8_t *data, uint32_t len);
void bread_strcpy(uint8_t **b, char *str);
char *bread_str_alloc(uint8_t **buf);
char *bread_str_skip(uint8_t **b);
char **bread_nameblock(uint8_t **b, int bOld);

void bwrite_ubit8(uint8_t **b, uint8_t i);
void bwrite_ubit16(uint8_t **b, uint16_t i);
void bwrite_ubit32(uint8_t **b, uint32_t i);
void bwrite_float(uint8_t **b, float f);
void bwrite_string(uint8_t **b, const char *str);
void bwrite_double_string(uint8_t **b, char *str);
void bwrite_nameblock(uint8_t **b, char **nb, int bOld);
void bwrite_intblock(uint8_t **b, int *nb);
