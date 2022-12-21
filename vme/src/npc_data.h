#pragma once

#include "char_data.h"

#include <array>

class npc_data : public char_data
{
public:
    static size_t g_world_nonpc; // number of chars in the world
public:
    npc_data(file_index_type *fi);
    ~npc_data() override;

    /**
     * @name Weapons
     * @todo Add range checking to indexes
     * @{
     */
    int16_t getWeaponSkillAtIndex(size_t index) const;
    int16_t *getWeaponSkillAtIndexPtr(size_t index);
    std::array<int16_t, WPN_GROUP_MAX> &getWeaponSkillArray();
    size_t getWeaponsSkillArraySize() const;
    void setWeaponSkillAtIndexTo(size_t index, int16_t value);
    void increaseWeaponSkillAtIndexBy(size_t index, int16_t value);
    void decreaseWeaponSkillAtIndexBy(size_t index, int16_t value);
    /// @}

    /**
     * Spells
     * @todo Add range checking to indexes
     * @{
     */
    int16_t getSpellSkillAtIndex(size_t index) const;
    int16_t *getSpellSkillAtIndexPtr(size_t index);
    std::array<int16_t, SPL_GROUP_MAX> &getSpellSkillArray();
    size_t getSpellSkillArraySize() const;
    void setSpellSkillAtIndexTo(size_t index, int16_t value);
    void increaseSpellSkillAtIndexBy(size_t index, int16_t value);
    void decreaseSpellSkillAtIndexBy(size_t index, int16_t value);
    /// @}

    /**
     * @name Default Position
     * @{
     */
    uint8_t getDefaultPosition() const;
    uint8_t *getDefaultPositionPtr();
    void setDefaultPosition(uint8_t value);
    /// @}

    /**
     * @name NPC Flags
     * @{
     */
    uint8_t getAllNPCFlags() const;
    uint8_t *getAllNPCFlagsPtr();
    void setAllNPCFlags(uint8_t value);
    /// @}
private:
    std::array<int16_t, WPN_GROUP_MAX> m_weapons{0}; ///<
    std::array<int16_t, SPL_GROUP_MAX> m_spells{0};  ///<
    uint8_t m_default_pos{POSITION_STANDING};        ///< Default position for NPC
    uint8_t m_flags{0};                              ///< flags for NPC behavior
};
