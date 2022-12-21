#pragma once

#include "bytestring.h"
#include "vme.h"

#include <array>

class unit_data;

class char_point_data
{
public:
    char_point_data();
    /*~char_point_data(void); not needed yet all base types they destroy themselves*/

    /**
     *
     * @param buf Buffer to read from
     * @param unit_version Version number of data object
     * @param unit We have to pass this in because there data in the middle that doesn't belong to char_point_data
     * @param error Error count
     */
    void readFrom(CByteBuffer &buf, uint8_t unit_version, unit_data *unit, int &error);

    ubit32 getCharacterFlags() const;
    ubit32 *getCharacterFlagsPtr();
    void setAllCharacterFlags(ubit32 value);
    void setCharacterFlag(ubit32 value);
    void removeCharacterFlag(ubit32 value);
    void toggleCharacterFlag(ubit32 value);

    sbit32 getPlayerExperience() const;
    sbit32 *getPlayerExperiencePtr();
    void setPlayerExperience(sbit32 value);
    void increasePlayerExperienceBy(sbit32 value);

    ubit16 getRace() const;
    ubit16 *getRacePtr();
    void setRace(ubit16 value);

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

    int16_t getSpeed() const;
    void setSpeed(int16_t value);
    void modifySpeedBy(int16_t delta);

private:
    /// @todo moving this up to char_data where it should be - will be deleted after
    int getNumberOfMeleeAttacks(int naturalAttacks, bool isPC);
    int getSpeedPercentage(bool isPC);

public:
    uint8_t getNaturalArmor() const;
    void setNaturalArmor(uint8_t value);
    uint8_t *getNaturalArmorPtr();

    uint8_t getAttackType() const;
    void setAttackType(uint8_t value);
    uint8_t *getAttackTypePtr();

    uint8_t getSex() const;
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

private:
    ubit32 flags{0};                                 ///< Char flags
    sbit32 exp{0};                                   ///< The experience of the player
    ubit16 race{0};                                  ///< PC/NPC race, Humanoid, Animal, etc.
    int16_t mana{0};                                 ///< How many mana points are left?
    int16_t endurance{0};                            ///< How many endurance points are left?
    int16_t offensive{0};                            ///< The OB of a character.
    int16_t defensive{0};                            ///< The DB of a character.
    int16_t speed{0};                                ///< The speed for combat
    uint8_t natural_armour{0};                       ///< The natural built-in armour (ARM_)
    uint8_t attack_type{0};                          ///< PC/NPC Attack Type for bare hands (WPN_)
    uint8_t dex_reduction{0};                        ///< For speed of armour calculations only
    uint8_t sex{0};                                  ///< PC / NPC s sex
    uint8_t level{0};                                ///< PC / NPC s level
    uint8_t position{0};                             ///< Standing, sitting, fighting...
    std::array<int16_t, ABIL_TREE_MAX> abilities{0}; ///< Str/dex etc.
};
