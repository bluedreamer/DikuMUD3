#include "char_point_data.h"

#include "slog.h"
#include "utility.h"
#include "utils.h"

char_point_data::char_point_data()
    : flags{0}          ///< Char flags
    , exp{0}            ///< The experience of the player
    , race{0}           ///< PC/NPC race, Humanoid, Animal, etc.
    , mana{0}           ///< How many mana points are left?
    , endurance{0}      ///< How many endurance points are left?
    , offensive{0}      ///< The OB of a character.
    , defensive{0}      ///< The DB of a character.
    , speed{0}          ///< The default speed for natural combat
    , natural_armour{0} ///< The natural built-in armour (ARM_)
    , attack_type{0}    ///< PC/NPC Attack Type for bare hands (WPN_)
    , dex_reduction{0}  ///< For speed of armour calculations only
    , sex{0}            ///< PC / NPC s sex
    , level{0}          ///< PC / NPC s level
    , position{0}       ///< Standing, sitting, fighting...
{
    memset(abilities.data(), 0, abilities.size());
}

ubit32 char_point_data::getCharacterFlags() const
{
    return flags;
}

ubit32 *char_point_data::getCharacterFlagsPtr()
{
    return &flags;
}

void char_point_data::setAllCharacterFlags(ubit32 value)
{
    flags = value;
}

void char_point_data::setCharacterFlag(ubit32 value)
{
    flags |= value;
}

void char_point_data::removeCharacterFlag(ubit32 value)
{
    flags &= ~value;
}

void char_point_data::toggleCharacterFlag(ubit32 value)
{
    flags ^= value;
}

sbit32 char_point_data::getPlayerExperience() const
{
    return exp;
}

sbit32 *char_point_data::getPlayerExperiencePtr()
{
    return &exp;
}

void char_point_data::setPlayerExperience(sbit32 value)
{
    exp = value;
}

void char_point_data::increasePlayerExperienceBy(sbit32 value)
{
    exp += value;
}

ubit16 char_point_data::getRace() const
{
    return race;
}

ubit16 *char_point_data::getRacePtr()
{
    return &race;
}

void char_point_data::setRace(ubit16 value)
{
    race = value;
}

int16_t char_point_data::getMana() const
{
    return mana;
}

int16_t *char_point_data::getManaPtr()
{
    return &mana;
}

void char_point_data::setMana(int16_t value)
{
    mana = value;
}

void char_point_data::decreaseManaBy(int16_t value)
{
    mana -= value;
}

int16_t char_point_data::getEndurance() const
{
    return endurance;
}

int16_t *char_point_data::getEndurancePtr()
{
    return &endurance;
}

void char_point_data::setEndurance(int16_t value)
{
    endurance = value;
}

void char_point_data::decreaseEnduranceBy(int16_t value)
{
    endurance -= value;
}

int16_t char_point_data::getOffensiveBonus() const
{
    return offensive;
}

void char_point_data::setOffensiveBonus(int16_t value)
{
    offensive = value;
}

int16_t *char_point_data::getOffensiveBonusPtr()
{
    return &offensive;
}

int16_t char_point_data::getDefensiveBonus() const
{
    return defensive;
}

void char_point_data::setDefensiveBonus(int16_t value)
{
    defensive = value;
}

int16_t *char_point_data::getDefensiveBonusPtr()
{
    return &defensive;
}

int16_t char_point_data::getSpeed() const
{
    return speed;
}

///        N1  N2
/// 100% = 1   2
/// 200% = 2   4
/// 300% = 3   6
int char_point_data::getNumberOfMeleeAttacks(int naturalAttacks, bool isPC)
{
    return MAX(1, (naturalAttacks * getSpeedPercentage(isPC)) / 100);
}

/// Calculate the speed percentage. 200% max for players,
/// 300% max for NPCs. 25% is the worst possible (4x slowed)
int char_point_data::getSpeedPercentage(bool isPC)
{
    int16_t s = speed;

    if (s < SPEED_MIN)
        s = SPEED_MIN;

    if (s == SPEED_DEFAULT)
        return 100;

    if (isPC)
        return MAX(MIN(200, (100 * SPEED_DEFAULT) / s), 25);
    else
        return MAX(MIN(300, (100 * SPEED_DEFAULT) / s), 25);
}

/// max values are -8 to +8
/// +1.. increases the speed
/// -1.. decreases the speed
void char_point_data::modifySpeedBy(int16_t delta)
{
    if ((delta > 8) or (delta < -8))
    {
        slog(LOG_ALL, 0, "Attempt to modify speed by an invalid amount %d", delta);
        return;
    }

    speed -= delta;
}

/// Should only be called from raw operations
void char_point_data::setSpeed(int16_t value)
{
    speed = value;
}

uint8_t char_point_data::getNaturalArmor() const
{
    return natural_armour;
}

void char_point_data::setNaturalArmor(uint8_t value)
{
    natural_armour = value;
}

uint8_t *char_point_data::getNaturalArmorPtr()
{
    return &natural_armour;
}

uint8_t char_point_data::getAttackType() const
{
    return attack_type;
}

void char_point_data::setAttackType(uint8_t value)
{
    attack_type = value;
}

uint8_t *char_point_data::getAttackTypePtr()
{
    return &attack_type;
}

uint8_t char_point_data::getSex() const
{
    return sex;
}

void char_point_data::setSex(uint8_t value)
{
    sex = value;
}

uint8_t *char_point_data::getSexPtr()
{
    return &sex;
}

uint8_t char_point_data::getLevel() const
{
    return level;
}

void char_point_data::setLevel(uint8_t value)
{
    level = value;
}

uint8_t *char_point_data::getLevelPtr()
{
    return &level;
}

void char_point_data::incrementLevel()
{
    ++level;
}

uint8_t char_point_data::getPosition() const
{
    return position;
}

void char_point_data::setPosition(uint8_t value)
{
    position = value;
}

uint8_t *char_point_data::getPositionPtr()
{
    return &position;
}

int16_t char_point_data::getAbilityAtIndex(size_t index) const
{
    return abilities[index];
}

int16_t char_point_data::getSTR() const
{
    return abilities[ABIL_STR];
}

int16_t char_point_data::getDEX() const
{
    return abilities[ABIL_DEX];
}

int16_t char_point_data::getCON() const
{
    return abilities[ABIL_CON];
}

int16_t char_point_data::getCHA() const
{
    return abilities[ABIL_CHA];
}

int16_t char_point_data::getBRA() const
{
    return abilities[ABIL_BRA];
}

int16_t char_point_data::getMAG() const
{
    return abilities[ABIL_MAG];
}

int16_t char_point_data::getDIV() const
{
    return abilities[ABIL_DIV];
}

int16_t char_point_data::getHPP() const
{
    return abilities[ABIL_HP];
}

int16_t *char_point_data::getAbilityAtIndexPtr(size_t index)
{
    return &abilities[index];
}

void char_point_data::setAbilityAtIndexTo(size_t index, int16_t value)
{
    abilities[index] = value;
}

void char_point_data::increaseAbilityAtIndexBy(size_t index, int16_t value)
{
    abilities[index] += value;
}

void char_point_data::decreaseAbilityAtIndexBy(size_t index, int16_t value)
{
    abilities[index] -= value;
}

std::array<int16_t, ABIL_TREE_MAX> &char_point_data::getAbilitiesArray()
{
    return abilities;
}

void char_point_data::setSTR(int16_t value)
{
    abilities[ABIL_STR] = value;
}

void char_point_data::setDEX(int16_t value)
{
    abilities[ABIL_DEX] = value;
}

void char_point_data::setCON(int16_t value)
{
    abilities[ABIL_CON] = value;
}

void char_point_data::setCHA(int16_t value)
{
    abilities[ABIL_CHA] = value;
}

void char_point_data::setBRA(int16_t value)
{
    abilities[ABIL_BRA] = value;
}

void char_point_data::setMAG(int16_t value)
{
    abilities[ABIL_MAG] = value;
}

void char_point_data::setDIV(int16_t value)
{
    abilities[ABIL_DIV] = value;
}

void char_point_data::setHPP(int16_t value)
{
    abilities[ABIL_HP] = value;
}

/// @todo unit should not need to be passed, but it looks like there are parent fields in middle of char_point_data in the binary file
void char_point_data::readFrom(CByteBuffer &buf, uint8_t unit_version, unit_data *unit, int &error)
{
    exp = buf.ReadS32(&error);
    flags = buf.ReadU32(&error);

    mana = buf.ReadS16(&error);
    endurance = buf.ReadS16(&error);

    natural_armour = buf.ReadU8(&error);

    if (unit_version <= 74)
    {
        if (unit_version >= 39)
        {
            uint8_t spd = buf.ReadU8(&error); // Ensure correct conversion
            speed = spd;
            if (unit->isPC())
            {
                if (speed < SPEED_MIN)
                {
                    speed = SPEED_DEFAULT;
                }
            }
        }
        else
        {
            speed = SPEED_DEFAULT;
        }
    }
    else // Speed for version 75 and up
    {
        // Speed is fluid, minimum is applied in function, not in storage
        speed = buf.ReadS16(&error);
    }

    attack_type = buf.ReadU16(&error); /// @todo Why is attack_type 8 bit it really should be 16 it looks like

    if (unit_version <= 52)
    {
        unit->setSize(buf.ReadU16(&error));
    }
    race = buf.ReadU16(&error);

    offensive = buf.ReadS16(&error);
    defensive = buf.ReadS16(&error);

    sex = buf.ReadU8(&error);
    level = buf.ReadU8(&error);
    position = buf.ReadU8(&error);

    int j = buf.ReadU8(&error);

    for (int i = 0; i < j; i++)
    {
        if (unit_version < 69)
        {
            abilities[i] = buf.ReadU8(&error);
        }
        else
        {
            abilities[i] = buf.ReadS16(&error);
        }

        if (unit->isPC())
        {
            UPC(unit)->setAbilityLevelAtIndexTo(i, buf.ReadU8(&error));
            if (unit_version < 72)
            {
                error += buf.Skip8();
            }
        }
    }
}
