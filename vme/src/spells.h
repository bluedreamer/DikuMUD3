/*
 $Author: tperry $
 $RCSfile: spells.h,v $
 $Date: 2003/01/30 04:08:58 $
 $Revision: 2.2 $
 */
#pragma once

#include "dil.h"
#include "spelldef.h"

int spell_perform(int spell_no,
                  int spell_type,
                  unit_data *caster,
                  unit_data *medium,
                  unit_data *target,
                  const char *argument,
                  char *pEffect = nullptr,
                  int bonus = 0);

bool spell_legal_type(int spl, int type);
bool spell_legal_target(int spl, unit_data *c, unit_data *t);

struct spell_args
{
    unit_data *caster, *medium, *target;
    const char *arg;
    int hm;
    char *pEffect;
};

struct spell_info_type
{
    uint8_t acttype;
    char *tochar;
    char *tovict;
    char *torest;
    char *toself;
    char *toselfroom;

    void (*spell_pointer)(spell_args *sa);
    uint8_t minimum_position; ///< Position for caster
    int16_t usesmana;         ///< Amount of mana used by a spell
    int8_t beats;             ///< Heartbeats until ready for next
    uint16_t targets;         ///< See below for use with TAR_XXX
    uint8_t media;            ///< found in spells/potions/...
    uint8_t cast_type;        ///< Resist, self check, etc?
    uint16_t demi_power;      ///< Power used by demis (0..5)
    uint8_t offensive;        ///< Is this an offensive spell?
    uint8_t realm;            ///< Essence, Channeling, Mentalism?
    uint8_t shield;           ///< Shield method SHIELD_M_XXX

    diltemplate *tmpl; ///< Perhaps a DIL template...
};

#define SPL_MAG_REQ(spell) (spl_requirement[spell].abilities[ABIL_MAG])

#define SPL_DIV_REQ(spell) (spl_requirement[spell].abilities[ABIL_DIV])

#define SPL_POW_REQ(spell) MIN(SPL_MAG_REQ(spell), SPL_DIV_REQ(spell))
