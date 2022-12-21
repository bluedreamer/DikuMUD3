/*
 $Author: All $
 $RCSfile: protocol.h,v $
 $Date: 2003/10/09 01:12:32 $
 $Revision: 2.2 $
 */
#pragma once

#include "essential.h"
#include "hook.h"

#define TERM_DUMB 0
#define TERM_TTY 1
#define TERM_ANSI 2
#define TERM_VT100 3
#define TERM_INTERNAL 4

struct terminal_setup_type
{
    uint8_t redraw;         ///< Redraw the users prompt?
    uint8_t echo;           ///< Echo chars to user?
    uint8_t width, height;  ///< The colour of his nose
    uint8_t emulation;      ///< TERM_XXX
    uint8_t telnet;         ///< Is telnet used?
    uint8_t colour_convert; ///< Colour conversion (mapping) used
    uint8_t websockets;     ///< Using websockets (HTML)?
};

// These definitions are used by the mplex protocol
#define MULTI_UNIQUE_CHAR '\x01'
#define MULTI_UNIQUE_STR "\x01"

#define MULTI_CONNECT_REQ_CHAR 'A'
#define MULTI_CONNECT_CON_CHAR 'B'
#define MULTI_TERMINATE_CHAR 'C'
#define MULTI_SETUP_CHAR 'D'
#define MULTI_HOST_CHAR 'E'
#define MULTI_TEXT_CHAR 'F'
#define MULTI_PAGE_CHAR 'G'
#define MULTI_PROMPT_CHAR 'H'
#define MULTI_EXCHANGE_CHAR 'I'
#define MULTI_COLOR_CHAR 'J'
#define MULTI_PING_CHAR 'K'
#define MULTI_MPLEX_INFO_CHAR 'L'

#define MULTI_CONNECT_REQ_STR "A"
#define MULTI_CONNECT_CON_STR "B"
#define MULTI_TERMINATE_STR "C"
#define MULTI_SETUP_STR "D"
#define MULTI_HOST_STR "E"
#define MULTI_TEXT_STR "F"
#define MULTI_PAGE_STR "G"
#define MULTI_PROMPT_STR "H"
#define MULTI_EXCHANGE_STR "I"
#define MULTI_COLOR_STR "J"
#define MULTI_PING_STR "K"
#define MULTI_MPLEX_INFO_STR "L"

#define MULTI_EXCHANGE MULTI_UNIQUE_STR MULTI_EXCHANGE_STR "\0\0\0\0"
#define MULTI_COLOR MULTI_UNIQUE_STR MULTI_COLOR_STR "\0\0\0\0"
#define MULTI_CONNECT_REQ MULTI_UNIQUE_STR MULTI_CONNECT_REQ_STR "\0\0\0\0"
#define MULTI_CONNECT_CON MULTI_UNIQUE_STR MULTI_CONNECT_CON_STR
#define MULTI_TERMINATE MULTI_UNIQUE_STR MULTI_TERMINATE_STR "\0\0\0\0"
#define MULTI_SETUP MULTI_UNIQUE_STR MULTI_SETUP_STR
#define MULTI_HOST MULTI_UNIQUE_STR MULTI_HOST_STR "\0\0\0\0"
#define MULTI_PING MULTI_UNIQUE_STR MULTI_PING_STR "\0\0\0\0"
#define MULTI_MPLEX_INFO MULTI_UNIQUE_STR MULTI_MPLEX_INFO_STR "\0\0\0\0"

#define MULTI_TEXT MULTI_UNIQUE_STR MULTI_TXT_STR
#define MULTI_PAGE MULTI_UNIQUE_STR MULTI_TXT_STR
#define MULTI_PROMPT MULTI_UNIQUE_STR MULTI_TXT_STR

#define MULTI_MAX_MUDNAME 256

void protocol_send_ping(cHook *Hook);
void protocol_send_close(cHook *Hook, uint16_t id);
void protocol_send_confirm(cHook *Hook, uint16_t id);
void protocol_send_request(cHook *Hook);
void protocol_send_text(cHook *Hook, const uint16_t id, const char *text, const uint8_t type);
void protocol_send_setup(cHook *Hook, uint16_t id, terminal_setup_type *setup);
void protocol_send_exchange(cHook *Hook, uint16_t id, const char *mudname);
void protocol_send_color(cHook *Hook, uint16_t id, const char *color);
void protocol_send_host(cHook *Hook, uint16_t id, const char *host, uint16_t nPort, uint8_t nLine);
int protocol_parse_incoming(cHook *Hook, uint16_t *pid, uint16_t *plen, char **str, uint8_t *text_type);
void protocol_send_mplex_info(cHook *Hook, uint8_t bWebsockets);
