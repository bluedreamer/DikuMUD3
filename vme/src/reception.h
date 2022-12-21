#pragma once

#include "essential.h"
#include "interpreter.h"

const char *ContentsFileName(const char *);
unit_data *restore_all_unit(const char *filename, unit_data *udest);
int diff(char *ref, uint32_t reflen, char *obj, int objlen, char *dif, int diflen, uint32_t crc);
int patch(char *ref, uint32_t reflen, char *dif, int diflen, char *res, int reslen, uint32_t crc);
uint32_t rent_calc(unit_data *ch, time_t savetime);
void reception_boot();
int save_contents(const char *pFileName, unit_data *unit, int fast, int bContainer);
void store_all_unit(unit_data *u, const char *fname, int svcont);
void do_rent(unit_data *, char *, const command_info *);
void load_contents(const char *pFileName, unit_data *unit);

extern file_index_type *g_slime_fi;
