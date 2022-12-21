#include "npc_data.h"

size_t npc_data::g_world_nonpc = 0; // number of chars in the world

npc_data::npc_data(file_index_type *fi)
    : char_data(UNIT_ST_NPC, fi)
    , m_weapons{0}
    , m_spells{0}
    , m_default_pos{POSITION_STANDING}
    , m_flags{0}
{
    g_world_nonpc++;
}

npc_data::~npc_data()
{
    g_world_nonpc--;
}

int16_t npc_data::getWeaponSkillAtIndex(size_t index) const
{
    return m_weapons[index];
}

int16_t *npc_data::getWeaponSkillAtIndexPtr(size_t index)
{
    return &m_weapons[index];
}

std::array<int16_t, WPN_GROUP_MAX> &npc_data::getWeaponSkillArray()
{
    return m_weapons;
}

size_t npc_data::getWeaponsSkillArraySize() const
{
    return m_weapons.size();
}

void npc_data::setWeaponSkillAtIndexTo(size_t index, int16_t value)
{
    m_weapons[index] = value;
}

void npc_data::increaseWeaponSkillAtIndexBy(size_t index, int16_t value)
{
    m_weapons[index] += value;
}

void npc_data::decreaseWeaponSkillAtIndexBy(size_t index, int16_t value)
{
    m_weapons[index] -= value;
}

int16_t npc_data::getSpellSkillAtIndex(size_t index) const
{
    return m_spells[index];
}

int16_t *npc_data::getSpellSkillAtIndexPtr(size_t index)
{
    return &m_spells[index];
}

std::array<int16_t, SPL_GROUP_MAX> &npc_data::getSpellSkillArray()
{
    return m_spells;
}

size_t npc_data::getSpellSkillArraySize() const
{
    return m_spells.size();
}

void npc_data::setSpellSkillAtIndexTo(size_t index, int16_t value)
{
    m_spells[index] = value;
}

void npc_data::increaseSpellSkillAtIndexBy(size_t index, int16_t value)
{
    m_spells[index] += value;
}

void npc_data::decreaseSpellSkillAtIndexBy(size_t index, int16_t value)
{
    m_spells[index] += value;
}

uint8_t npc_data::getDefaultPosition() const
{
    return m_default_pos;
}

uint8_t *npc_data::getDefaultPositionPtr()
{
    return &m_default_pos;
}

void npc_data::setDefaultPosition(uint8_t value)
{
    m_default_pos = value;
}

uint8_t npc_data::getAllNPCFlags() const
{
    return m_flags;
}

uint8_t *npc_data::getAllNPCFlagsPtr()
{
    return &m_flags;
}

void npc_data::setAllNPCFlags(uint8_t value)
{
    m_flags = value;
}
