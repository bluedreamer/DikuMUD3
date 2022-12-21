#pragma once

#include "char_follow_type.h"
#include "char_point_data.h"
#include "combat.h"
#include "descriptor_data.h"
#include "unit_data.h"

class char_data : public unit_data
{
public:
    static size_t g_world_nochars; // number of chars in the world

public:
    explicit char_data(uint8_t unit_type, file_index_type *fi);
    virtual ~char_data();

    /**
     * @name Descriptor related code
     * @{
     */
    const descriptor_data *getDescriptor() const;
    descriptor_data *getDescriptor();
    void setDescriptor(descriptor_data *value);
    ///@}

    /**
     * @name Combat related code
     * @{
     */
    const cCombat *getCombat() const;
    cCombat *getCombat();
    void setCombat(cCombat *value);
    ///@}

    /**
     * @name Master related code
     * @{
     */
    const unit_data *getMaster() const;
    unit_data *getMaster();
    unit_data **getMasterPtr();
    void setMaster(unit_data *value);
    ///@}

    /**
     * @name Last Location related code
     * @{
     */
    const unit_data *getLastLocation() const;
    unit_data *getLastLocation();
    unit_data **getLastLocationPtr();
    void setLastLocation(unit_data *value);
    ///@}

    /**
     * @name Character points related functions
     * @todo This is basically char_point_data's public interface - so in future char_point_data can be just removed
     * @{
     */
    void readFrom(CByteBuffer &buf, uint8_t unit_version, unit_data *unit, int &error);

    uint32_t *getCharacterFlagsPtr();
    uint32_t getCharacterFlags() const;
    void setAllCharacterFlags(uint32_t value);
    void setCharacterFlag(uint32_t value);
    void removeCharacterFlag(uint32_t value);
    void toggleCharacterFlag(uint32_t value);

    int32_t getPlayerExperience() const;
    int32_t *getPlayerExperiencePtr();
    void setPlayerExperience(int32_t value);
    void increasePlayerExperienceBy(int32_t value);

    uint16_t getRace() const;
    uint16_t *getRacePtr();
    void setRace(uint16_t value);

    int16_t getMana() const;
    int16_t *getManaPtr();
    void setMana(int16_t value);
    void decreaseManaBy(int16_t value);

    int16_t getEndurance() const;
    int16_t *getEndurancePtr();
    void setEndurance(int16_t value);
    void decreaseEnduranceBy(int16_t value);

    int16_t getOffensiveBonus() const;
    void setOffensiveBonus(int16_t value);
    int16_t *getOffensiveBonusPtr();

    int16_t getDefensiveBonus() const;
    void setDefensiveBonus(int16_t value);
    int16_t *getDefensiveBonusPtr();

    int getNumberOfMeleeAttacks(int naturalAttacks);

    int16_t getSpeed() const;
    void setSpeed(int16_t value);
    void modifySpeedBy(int16_t delta);
    /**
     * Calculate the speed percentage. 200% max for players, 300% max for NPCs. 25% is the worst possible (4x slowed)
     * @return speed percentage
     */
    int getSpeedPercentage();

    uint8_t getNaturalArmor() const;
    void setNaturalArmor(uint8_t value);
    uint8_t *getNaturalArmorPtr();

    uint8_t getAttackType() const;
    void setAttackType(uint8_t value);
    uint8_t *getAttackTypePtr();

    virtual uint8_t getSex() const;
    void setSex(uint8_t value);
    uint8_t *getSexPtr();

    uint8_t getLevel() const;
    void setLevel(uint8_t value);
    uint8_t *getLevelPtr();
    void incrementLevel();

    uint8_t getPosition() const;
    void setPosition(uint8_t value);
    uint8_t *getPositionPtr();

    int16_t getAbilityAtIndex(size_t index) const;
    int16_t *getAbilityAtIndexPtr(size_t index);
    int16_t getSTR() const;
    int16_t getDEX() const;
    int16_t getCON() const;
    int16_t getCHA() const;
    int16_t getBRA() const;
    int16_t getMAG() const;
    int16_t getDIV() const;
    int16_t getHPP() const;
    void setSTR(int16_t value);
    void setDEX(int16_t value);
    void setCON(int16_t value);
    void setCHA(int16_t value);
    void setBRA(int16_t value);
    void setMAG(int16_t value);
    void setDIV(int16_t value);
    void setHPP(int16_t value);
    void setAbilityAtIndexTo(size_t index, int16_t value);
    void increaseAbilityAtIndexBy(size_t index, int16_t value);
    void decreaseAbilityAtIndexBy(size_t index, int16_t value);
    std::array<int16_t, ABIL_TREE_MAX> &getAbilitiesArray();
    /// @}

    /**
     * @name Follower related code
     * @{
     */
    const char_follow_type *getFollowers() const;
    char_follow_type *getFollowers();
    void setFollowers(char_follow_type *value);
    /// @}

    /**
     * @name
     * @{
     */
    const char *getLastAttacker() const;
    void freeLastAttacker();
    void setLastAttacker(char *value);
    ///@}

    /**
     * @name Money related functions
     * @{
     */
    const char *getMoney() const;
    char *getMoney();
    char **getMoneyPtr();
    void freeMoney();
    void setMoney(char *value);
    ///@}

    /**
     * @name Last Attacker type functions
     * @{
     */
    uint8_t getLastAttackerType() const;
    void setLastAttackerType(uint8_t value);
    ///@}
private:
    descriptor_data *m_descriptor{nullptr}; ///<
    cCombat *m_combat{nullptr};             ///<
    unit_data *m_master{nullptr};           ///< Must be a char
    unit_data *m_last_room{nullptr};        ///< Last location of character
    char_point_data m_points;               ///<
    char_follow_type *m_followers{nullptr}; ///<
    char *m_last_attacker{nullptr};         ///< Last attacker of character
    char *m_money{nullptr};                 ///<  Money transfer from db-files.
    uint8_t m_last_attacker_type{0};        ///< Last attacker type of character
};
