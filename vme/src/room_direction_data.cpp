#include "room_direction_data.h"

room_direction_data::room_direction_data()
{
    key = nullptr;
    to_room = nullptr;
    exit_info = 0;
    difficulty = 0;
}

room_direction_data::~room_direction_data()
{
}

const cNamelist &room_direction_data::getOpenName() const
{
    return open_name;
}

cNamelist &room_direction_data::getOpenName()
{
    return open_name;
}

const char *room_direction_data::getKey() const
{
    return key;
}

char **room_direction_data::getKeyPtr()
{
    return &key;
}

void room_direction_data::setKey(char *value)
{
    FREE(key);
    key = value;
}

const unit_data *room_direction_data::getToRoom() const
{
    return to_room;
}

unit_data *room_direction_data::getToRoom()
{
    return to_room;
}

void room_direction_data::setToRoom(unit_data *value)
{
    to_room = value;
}

uint8_t room_direction_data::getSkillDifficulty() const
{
    return difficulty;
}

void room_direction_data::setSkillDifficulty(uint8_t value)
{
    difficulty = value;
}

uint8_t *room_direction_data::getSkillDifficultyPtr()
{
    return &difficulty;
}

uint8_t room_direction_data::getDoorFlags() const
{
    return exit_info;
}

bool room_direction_data::isDoorFlagSet(uint8_t value) const
{
    return exit_info & value;
}

void room_direction_data::setDoorFlags(uint8_t value)
{
    exit_info = value;
}
uint8_t *room_direction_data::getDoorFlagsPtr()
{
    return &exit_info;
}
