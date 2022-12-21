/*
 $Author: tperry $
 $RCSfile: utility.h,v $
 $Date: 2001/04/29 03:46:07 $
 $Revision: 2.1 $
 */
#pragma once

#include "essential.h"

#include <string>

#ifdef MIN
    #undef MIN
#endif

#ifdef MAX
    #undef MAX
#endif

/* in game log stuff below */
#define MAXLOG 10

class log_buffer
{
public:
    log_buffer() = default;
    void setString(std::string str) { m_str = std::move(str); }
    void setLevel(log_level level) { m_level = level; }
    void setWizInvLevel(uint8_t level) { m_wizinv_level = level; }

    const std::string &getString() const { return m_str; }
    log_level getLevel() const { return m_level; }
    uint8_t getWizInvLevel() const { return m_wizinv_level; }

    void clearString() { m_str.clear(); }

private:
    std::string m_str{};
    log_level m_level{};
    uint8_t m_wizinv_level{};
};

/**
 * For the printing of obj_type information, as used by the identify spell and
 * wstat command.  Look in act_stat.c for details.
 */
struct obj_type_t
{
    const char *fmt;
    uint8_t v[5];
};

int is_in(int a, int from, int to);
int MIN(int a, int b);
int MAX(int a, int b);

int number(int from, int to);
int dice(int number, int size);

const char *sprintbit(std::string &dest, uint32_t vektor, const char *names[]);
char *sprinttype(char *buf, int type, const char *names[]);

extern log_buffer g_log_buf[];
extern FILE *g_log_file_fd;
