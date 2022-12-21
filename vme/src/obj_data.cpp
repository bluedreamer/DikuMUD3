#include "obj_data.h"

size_t obj_data::g_world_noobjects; // number of objects in the world

obj_data::obj_data(file_index_type *fi)
    : unit_data(UNIT_ST_OBJ, fi)
    , m_value{0}
    , m_cost{0}
    , m_cost_per_day{0}
    , m_flags{0}
    , m_type{ITEM_TRASH}
    , m_equip_pos{0}
    , m_resistance{0}
{
    g_world_noobjects++;
}

obj_data::~obj_data()
{
    g_world_noobjects--;
}

int32_t obj_data::getValueAtIndex(size_t index) const
{
    return m_value.at(index);
}

int32_t *obj_data::getValueAtIndexPtr(size_t index)
{
    return &m_value.at(index);
}

size_t obj_data::getValueArraySize() const
{
    return m_value.size();
}

void obj_data::setValueAtIndexTo(size_t index, int32_t value)
{
    m_value.at(index) = value;
}

uint32_t obj_data::getPriceInGP() const
{
    return m_cost;
}

uint32_t *obj_data::getPriceInGPPtr()
{
    return &m_cost;
}

void obj_data::setPriceInGP(uint32_t value)
{
    m_cost = value;
}

uint32_t obj_data::getPricePerDay() const
{
    return m_cost_per_day;
}

uint32_t *obj_data::getPricePerDayPtr()
{
    return &m_cost_per_day;
}

void obj_data::setPricePerDay(uint32_t value)
{
    m_cost_per_day = value;
}

uint8_t obj_data::getObjectFlags() const
{
    return m_flags;
}

uint8_t *obj_data::getObjectFlagsPtr()
{
    return &m_flags;
}

void obj_data::setObjectFlag(uint8_t value)
{
    m_flags |= value;
}

void obj_data::removeObjectFlag(uint8_t value)
{
    m_flags &= ~value;
}

void obj_data::setAllObjectFlags(uint32_t value)
{
    m_flags = static_cast<uint8_t>(value);
}

uint8_t obj_data::getObjectItemType() const
{
    return m_type;
}

uint8_t *obj_data::getObjectItemTypePtr()
{
    return &m_type;
}

void obj_data::setObjectItemType(uint8_t value)
{
    m_type = value;
}

uint8_t obj_data::getEquipmentPosition() const
{
    return m_equip_pos;
}

void obj_data::setEquipmentPosition(uint8_t value)
{
    m_equip_pos = value;
}

uint8_t obj_data::getMagicResistance() const
{
    return m_resistance;
}

uint8_t *obj_data::getMagicResistancePtr()
{
    return &m_resistance;
}

void obj_data::setMagicResistance(uint8_t value)
{
    m_resistance = value;
}
