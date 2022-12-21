#pragma once

#include "char_data.h"
#include "color.h"
#include "dil.h"
#include "pc_account_data.h"
#include "pc_time_data.h"
#include "protocol.h"

class pc_data : public char_data
{
public:
    static constexpr auto PC_MAX_PASSWORD = 13; ///< Max length of any pc-password
    static constexpr auto PC_MAX_NAME = 15;     ///< 14 Characters + Null
    static size_t g_world_nopc;                 ///< number of chars in the world

public:
    pc_data(file_index_type *fi);
    ~pc_data() override;

    void gstate_tomenu(dilprg *pdontstop);
    void gstate_togame(dilprg *pdontstart);

    void disconnect_game();
    void connect_game();
    void reconnect_game(descriptor_data *d);

    /**
     * @name Terminal related code
     * @{
     */
    terminal_setup_type &getTerminalSetupType();
    /// @}

    /**
     * @name PC time related code
     * @{
     */
    pc_time_data &getPCTimeInformation();
    /// @}

    /**
     * @name Accounting related code
     * @{
     */
    pc_account_data &getPCAccountData();
    /// @}

    /**
     * @name Guild related code
     * @{
     */
    const char *getGuild() const;
    char **getGuildPtr();
    void freeGuild();
    void setGuild(const char *value);
    /// @}

    /**
     * @name Bank related code
     * @{
     */
    const char *getBank() const;
    char **getBankPtr();
    void freeBank();
    void setBank(char *value);
    /// @}

    /**
     * @name Hometown related code
     * @{
     */
    const char *getHometown() const;
    char **getHometownPtr();
    void setHometown(char *value);
    /// @}

    /** @name Prompt String related code
     * @{
     */
    const char *getPromptString() const;
    char **getPromptStringPtr();
    void setPromptString(char *value);
    void freePromptString();
    /// @}

    /**
     * @name Admin related code
     * @{
     */
    extra_list &getAdministrationInformation();
    /// @}

    /**
     * @name Quest related code
     * @{
     */
    extra_list &getQuestInformation();
    /// @}

    /**
     * @name Profession related code
     * @{
     */
    int8_t getProfession() const;
    int8_t *getProfessionPtr();
    void setProfession(int8_t value);
    /// @}

    /**
     * @name Virtual Player level code
     * @{
     */
    uint16_t getVirtualPlayerLevel() const;
    uint16_t *getVirtualPlayerLevelPtr();
    void setVirtualPlayerLevel(uint16_t value);
    void incrementVirtualPlayerLevel();
    /// @}

    /**
     * @name UID for players
     * @{
     */
    int32_t getPlayerUID() const;
    void setPlayerUID(int32_t value);
    /// @}

    /**
     * @name Skill points
     * @{
     */
    int32_t getSkillPoints() const;
    int32_t *getSkillPointsPtr();
    void setSkillPoints(int32_t value);
    void increaseSkillPointsBy(int32_t value);
    /// @}

    /**
     * @name Ability Points
     * @{
     */
    int32_t getAbilityPoints() const;
    int32_t *getAbilityPointsPtr();
    void setAbilityPoints(int32_t value);
    void increaseAbilityPointsBy(int32_t value);
    /// @}

    /**
     * @name Flags
     * @{
     */
    uint16_t getAllPCFlags() const;
    uint16_t *getAllPCFlagsPtr();
    void setPCFlag(uint16_t value);
    void setAllPCFlags(uint16_t value);
    void togglePCFlag(uint16_t value);
    void removePCFlag(uint16_t value);
    /// @}

    /**
     * @name Crimes Committed
     * @{
     */
    uint16_t getNumberOfCrimesCommitted() const;
    uint16_t *getNumberOfCrimesCommittedPtr();
    void setNumberOfCrimesCommitted(uint16_t value);
    /// @}

    /**
     * @name Crack Attempts
     * @{
     */
    uint16_t getNumberOfCrackAttempts() const;
    void setNumberOfCrackAttempts(uint16_t value);
    void incrementNumberOfCrackAttempts();
    /// @}

    /**
     * @name Lifespan
     * @{
     */
    uint16_t getLifespan() const;
    uint16_t *getLifespanPtr();
    void setLifespan(uint16_t value);
    /// @}

    /**
     * @name Spells skills Learned
     * @todo Add range checking to indexes
     * @{
     */
    int16_t getSpellSkillAtIndex(size_t index) const;
    int16_t *getSpellSkillArrayPtr();
    int16_t *getSpellSkillAtIndexPtr(size_t index);
    void setSpellSKillAtIndexTo(size_t index, int16_t value);
    void increaseSpellSkillAtIndexBy(size_t index, int16_t value);
    void decreaseSpellSkillAtIndexBy(size_t index, int16_t value);
    /// @}

    /**
     * @name Spell level
     * @todo Add range checking to indexes
     * @{
     */
    uint8_t getSpellLevelAtIndex(size_t index) const;
    uint8_t *getSpellLevelAtIndexPtr(size_t index);
    uint8_t *getSpellLevelArrayPtr();
    void setSpellLevelAtIndexTo(size_t index, uint8_t value);
    /// @}

    /**
     * @name Skills
     * @todo Add range checking to indexes
     * @{
     */
    int16_t getSkillAtIndex(size_t index) const;
    int16_t *getSkillAtIndexPtr(size_t index);
    int16_t *getSkillArrayPtr();
    void setSkillAtIndexTo(size_t index, int16_t value);
    void increaseSkillAtIndexBy(size_t index, int16_t value);
    void decreaseSkillAtIndexBy(size_t index, int16_t value);
    /// @}

    /**
     * @name Skill Level
     * @todo Add range checking to indexes
     * @{
     */
    uint8_t getSkillLevelAtIndex(size_t index) const;
    uint8_t *getSkillLevelAtIndexPtr(size_t index);
    uint8_t *getSkillLevelArrayPtr();
    void setSkillLevelAtIndexTo(size_t index, uint8_t value);
    /// @}

    /**
     * @name Weapon skill
     * @todo Add range checking to indexes
     * @{
     */
    int16_t getWeaponSkillAtIndex(size_t index) const;
    int16_t *getWeaponSkillArrayPtr();
    int16_t *getWeaponSkillAtIndexPtr(size_t index);
    void setWeaponSkillAtIndexTo(size_t index, int16_t value);
    void increaseWeaponSkillAtIndexBy(size_t index, int16_t value);
    void decreaseWeaponSkillAtIndexBy(size_t index, int16_t value);
    /// @}

    /**
     * @name Weapon Skill Level
     * @todo Add range checking to indexes
     * @{
     */
    uint8_t getWeaponSkillLevelAtIndex(size_t index) const;
    uint8_t *getWeaponSkillLevelAtIndexPtr(size_t index);
    uint8_t *getWeaponSkillLevelArrayPtr();
    void setWeaponSkillLevelAtIndexTo(size_t index, uint8_t value);
    /// @}

    /**
     * @name Ability Level
     * @todo Add range checking to indexes
     * @{
     */
    uint8_t getAbilityLevelAtIndex(size_t index) const;
    uint8_t *getAbilityLevelAtIndexPtr(size_t index);
    uint8_t *getAbilityLevelArrayPtr();
    void setAbilityLevelAtIndexTo(size_t index, uint8_t value);
    /// @}

    /**
     * @name Conditions
     * @todo Add range checking to indexes
     * @{
     */
    int8_t getConditionAtIndex(size_t index) const;
    int8_t *getConditionAtIndexPtr(size_t index);
    void setConditionAtIndexTo(size_t index, int8_t value);
    void increaseConditionAtIndexBy(size_t index, int8_t value);
    void decreaseConditionAtIndexBy(size_t index, int8_t value);
    /// @}

    /**
     * @name Access Level
     * @{
     */
    uint8_t getAccessLevel() const;
    void setAccessLevel(uint8_t value);
    /// @}

    /**
     * @name Passwords
     * @{
     */
    const char *getPassword() const;
    void setPassword(const char *value);
    int readPasswordFrom(CByteBuffer &buf);
    void truncatePassword();
    /// @}

    /**
     * @name Filename
     * @{
     */
    const char *getFilename() const;
    int readFilenameFrom(CByteBuffer &buf);
    void setFilename(const char *value);
    /// @}

    /**
     * @name Last hosts
     * @todo Add range checking to indexes
     * @{
     */
    uint32_t getLastHostAtIndex(size_t index) const;
    void setLastHostAtIndexTo(size_t index, uint32_t value);
    void pushBackLastHost(uint32_t value);
    /// @}

    /**
     * @name Color
     * @{
     */
    const color_type &getColor() const;
    color_type &getColor();
    /// @}
private:
    terminal_setup_type m_setup{0, 0, 0, 0, 0, 0, 0, 0}; ///<
    pc_time_data m_time{};                               ///< PCs time info
    pc_account_data m_account{};                         ///< Accounting
    char *m_guild{nullptr};                              ///< Player's current default guild (guilds in .info)
    char *m_bank{nullptr};                               ///< How much money in bank?
    char *m_hometown{nullptr};                           ///< PCs Hometown (symbolic reference)
    char *m_promptstr{nullptr};                          ///< A PC's Prompt
    extra_list m_info;                                   ///< For saving Admin information
    extra_list m_quest;                                  ///< For saving QUEST information
    int8_t m_profession{-1};                             ///< The player's chosen profession, -1 means unknown
    uint16_t m_vlvl{0};                                  ///< Virtual Level for player
    int32_t m_id{-1};                                    ///< Unique identifier for each player (-1 guest)
    int32_t m_skill_points{0};                           ///< No of practice points left
    int32_t m_ability_points{0};                         ///< No of practice points left
    uint16_t m_flags{0};                                 ///< flags for PC setup (brief, noshout...)
    uint16_t m_nr_of_crimes{0};                          ///< Number of crimes committed
    uint16_t m_crack_attempts{0};                        ///< Number of wrong passwords entered
    uint16_t m_lifespan{0};                              ///< How many year to live....
    int16_t m_spells[SPL_TREE_MAX]{0};                   ///< The spells learned
    uint8_t m_spell_lvl[SPL_TREE_MAX]{0};                ///< Practiced within that level
    int16_t m_skills[SKI_TREE_MAX]{0};                   ///< The skills learned
    uint8_t m_skill_lvl[SKI_TREE_MAX]{0};                ///< The skills practiced within level
    int16_t m_weapons[WPN_TREE_MAX]{0};                  ///< The weapons learned
    uint8_t m_weapon_lvl[WPN_TREE_MAX]{0};               ///< The weapons learned
    uint8_t m_ability_lvl[ABIL_TREE_MAX]{0};             ///< The abilities learned
    int8_t m_conditions[3]{0};                           ///< Drunk full etc.
    uint8_t m_nAccessLevel{0};                           ///< Access Level for BBS use
    char m_pwd[PC_MAX_PASSWORD]{0};                      ///< Needed when loaded w/o descriptor
    char m_filename[PC_MAX_NAME]{0};                     ///< The name on disk...
    uint32_t m_lasthosts[5]{0};                          ///< last 5 different IPs
    color_type m_color;                                  ///< Players default colors
};
