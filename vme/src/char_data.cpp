#include "char_data.h"

size_t char_data::g_world_nochars = 0;

char_data::char_data(uint8_t unit_type, file_index_type *fi)
    : unit_data(unit_type, fi)
    , m_descriptor{nullptr}
    , m_combat{nullptr}
    , m_master{nullptr}
    , m_last_room{nullptr}
    , m_points{}
    , m_followers{nullptr}
    , m_last_attacker{nullptr}
    , m_money{nullptr}
    , m_last_attacker_type{0}
{
    g_world_nochars++;

    // MS2020 memset(&points, 0, sizeof (points));
    // Removed because class constructor already initialize class variables.
}

char_data::~char_data()
{
#ifdef DMSERVER
    if (m_money)
    {
        FREE(m_money);
    }
    if (m_last_attacker)
    {
        FREE(m_last_attacker);
    }
#endif
    g_world_nochars--;
}

const descriptor_data *char_data::getDescriptor() const
{
    return m_descriptor;
}

descriptor_data *char_data::getDescriptor()
{
    return m_descriptor;
}

void char_data::setDescriptor(descriptor_data *value)
{
    m_descriptor = value;
}

const cCombat *char_data::getCombat() const
{
    return m_combat;
}

cCombat *char_data::getCombat()
{
    return m_combat;
}

void char_data::setCombat(cCombat *value)
{
    m_combat = value;
}

const unit_data *char_data::getMaster() const
{
    return m_master;
}

unit_data *char_data::getMaster()
{
    return m_master;
}

unit_data **char_data::getMasterPtr()
{
    return &m_master;
}

void char_data::setMaster(unit_data *value)
{
    m_master = value;
}

const unit_data *char_data::getLastLocation() const
{
    return m_last_room;
}

unit_data *char_data::getLastLocation()
{
    return m_last_room;
}

unit_data **char_data::getLastLocationPtr()
{
    return &m_last_room;
}

void char_data::setLastLocation(unit_data *value)
{
    m_last_room = value;
}

void char_data::readFrom(CByteBuffer &buf, uint8_t unit_version, unit_data *unit, int &error)
{
    return m_points.readFrom(buf, unit_version, unit, error);
}

ubit32 *char_data::getCharacterFlagsPtr()
{
    return m_points.getCharacterFlagsPtr();
}

ubit32 char_data::getCharacterFlags() const
{
    return m_points.getCharacterFlags();
}

void char_data::setAllCharacterFlags(ubit32 value)
{
    m_points.setAllCharacterFlags(value);
}

void char_data::setCharacterFlag(ubit32 value)
{
    m_points.setCharacterFlag(value);
}

void char_data::removeCharacterFlag(ubit32 value)
{
    m_points.removeCharacterFlag(value);
}

void char_data::toggleCharacterFlag(ubit32 value)
{
    m_points.toggleCharacterFlag(value);
}

sbit32 char_data::getPlayerExperience() const
{
    return m_points.getPlayerExperience();
}

sbit32 *char_data::getPlayerExperiencePtr()
{
    return m_points.getPlayerExperiencePtr();
}

void char_data::setPlayerExperience(sbit32 value)
{
    m_points.setPlayerExperience(value);
}

void char_data::increasePlayerExperienceBy(sbit32 value)
{
    m_points.increasePlayerExperienceBy(value);
}

ubit16 char_data::getRace() const
{
    return m_points.getRace();
}

ubit16 *char_data::getRacePtr()
{
    return m_points.getRacePtr();
}

void char_data::setRace(ubit16 value)
{
    m_points.setRace(value);
}

int16_t char_data::getMana() const
{
    return m_points.getMana();
}

int16_t *char_data::getManaPtr()
{
    return m_points.getManaPtr();
}

void char_data::setMana(int16_t value)
{
    m_points.setMana(value);
}

void char_data::decreaseManaBy(int16_t value)
{
    m_points.decreaseManaBy(value);
}

int16_t char_data::getEndurance() const
{
    return m_points.getEndurance();
}

int16_t *char_data::getEndurancePtr()
{
    return m_points.getEndurancePtr();
}

void char_data::setEndurance(int16_t value)
{
    m_points.setEndurance(value);
}

void char_data::decreaseEnduranceBy(int16_t value)
{
    m_points.decreaseEnduranceBy(value);
}

int16_t char_data::getOffensiveBonus() const
{
    return m_points.getOffensiveBonus();
}

void char_data::setOffensiveBonus(int16_t value)
{
    m_points.setOffensiveBonus(value);
}

int16_t *char_data::getOffensiveBonusPtr()
{
    return m_points.getOffensiveBonusPtr();
}

int16_t char_data::getDefensiveBonus() const
{
    return m_points.getDefensiveBonus();
}

void char_data::setDefensiveBonus(int16_t value)
{
    m_points.setDefensiveBonus(value);
}

int16_t *char_data::getDefensiveBonusPtr()
{
    return m_points.getDefensiveBonusPtr();
}

int char_data::getNumberOfMeleeAttacks(int naturalAttacks)
{
    return std::max(1, (naturalAttacks * getSpeedPercentage()) / 100);
}

int16_t char_data::getSpeed() const
{
    return m_points.getSpeed();
}

void char_data::setSpeed(int16_t value)
{
    m_points.setSpeed(value);
}

void char_data::modifySpeedBy(int16_t delta)
{
    m_points.modifySpeedBy(delta);
}

int char_data::getSpeedPercentage()
{
    int16_t s = m_points.getSpeed();

    if (s < SPEED_MIN)
    {
        s = SPEED_MIN;
    }

    if (s == SPEED_DEFAULT)
    {
        return 100;
    }

    if (getUnitType() == UNIT_ST_PC)
    {
        return std::max(std::min(200, (100 * SPEED_DEFAULT) / s), 25);
    }
    return std::max(std::min(300, (100 * SPEED_DEFAULT) / s), 25);
}

uint8_t char_data::getNaturalArmor() const
{
    return m_points.getNaturalArmor();
}

void char_data::setNaturalArmor(uint8_t value)
{
    m_points.setNaturalArmor(value);
}

uint8_t *char_data::getNaturalArmorPtr()
{
    return m_points.getNaturalArmorPtr();
}

uint8_t char_data::getAttackType() const
{
    return m_points.getAttackType();
}

void char_data::setAttackType(uint8_t value)
{
    m_points.setAttackType(value);
}

uint8_t *char_data::getAttackTypePtr()
{
    return m_points.getAttackTypePtr();
}

uint8_t char_data::getSex() const
{
    return m_points.getSex();
}

void char_data::setSex(uint8_t value)
{
    m_points.setSex(value);
}

uint8_t *char_data::getSexPtr()
{
    return m_points.getSexPtr();
}

uint8_t char_data::getLevel() const
{
    return m_points.getLevel();
}

void char_data::setLevel(uint8_t value)
{
    m_points.setLevel(value);
}

uint8_t *char_data::getLevelPtr()
{
    return m_points.getLevelPtr();
}

void char_data::incrementLevel()
{
    m_points.incrementLevel();
}

uint8_t char_data::getPosition() const
{
    return m_points.getPosition();
}

void char_data::setPosition(uint8_t value)
{
    m_points.setPosition(value);
}

uint8_t *char_data::getPositionPtr()
{
    return m_points.getPositionPtr();
}

int16_t char_data::getAbilityAtIndex(size_t index) const
{
    return m_points.getAbilityAtIndex(index);
}

int16_t *char_data::getAbilityAtIndexPtr(size_t index)
{
    return m_points.getAbilityAtIndexPtr(index);
}

int16_t char_data::getSTR() const
{
    return m_points.getSTR();
}

int16_t char_data::getDEX() const
{
    return m_points.getDEX();
}

int16_t char_data::getCON() const
{
    return m_points.getCON();
}

int16_t char_data::getCHA() const
{
    return m_points.getCHA();
}

int16_t char_data::getBRA() const
{
    return m_points.getBRA();
}

int16_t char_data::getMAG() const
{
    return m_points.getMAG();
}

int16_t char_data::getDIV() const
{
    return m_points.getDIV();
}

int16_t char_data::getHPP() const
{
    return m_points.getHPP();
}

void char_data::setSTR(int16_t value)
{
    m_points.setSTR(value);
}

void char_data::setDEX(int16_t value)
{
    m_points.setDEX(value);
}

void char_data::setCON(int16_t value)
{
    m_points.setCON(value);
}

void char_data::setCHA(int16_t value)
{
    m_points.setCHA(value);
}

void char_data::setBRA(int16_t value)
{
    m_points.setBRA(value);
}

void char_data::setMAG(int16_t value)
{
    m_points.setMAG(value);
}

void char_data::setDIV(int16_t value)
{
    m_points.setDIV(value);
}

void char_data::setHPP(int16_t value)
{
    m_points.setHPP(value);
}

void char_data::setAbilityAtIndexTo(size_t index, int16_t value)
{
    m_points.setAbilityAtIndexTo(index, value);
}

void char_data::increaseAbilityAtIndexBy(size_t index, int16_t value)
{
    m_points.increaseAbilityAtIndexBy(index, value);
}

void char_data::decreaseAbilityAtIndexBy(size_t index, int16_t value)
{
    m_points.decreaseAbilityAtIndexBy(index, value);
}

std::array<int16_t, ABIL_TREE_MAX> &char_data::getAbilitiesArray()
{
    return m_points.getAbilitiesArray();
}

const char_follow_type *char_data::getFollowers() const
{
    return m_followers;
}

char_follow_type *char_data::getFollowers()
{
    return m_followers;
}

void char_data::setFollowers(char_follow_type *value)
{
    m_followers = value;
}

const char *char_data::getLastAttacker() const
{
    return m_last_attacker;
}

void char_data::freeLastAttacker()
{
    if (m_last_attacker)
    {
        FREE(m_last_attacker);
    }
}

void char_data::setLastAttacker(char *value)
{
    m_last_attacker = value;
}

const char *char_data::getMoney() const
{
    return m_money;
}

char *char_data::getMoney()
{
    return m_money;
}

char **char_data::getMoneyPtr()
{
    return &m_money;
}

void char_data::freeMoney()
{
    FREE(m_money);
}

void char_data::setMoney(char *value)
{
    m_money = value;
}

uint8_t char_data::getLastAttackerType() const
{
    return m_last_attacker_type;
}

void char_data::setLastAttackerType(uint8_t value)
{
    m_last_attacker_type = value;
}
