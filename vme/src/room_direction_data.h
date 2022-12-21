#pragma once

#include "namelist.h"

class unit_data;

class room_direction_data
{
public:
    room_direction_data();
    ~room_direction_data();

    const cNamelist &getOpenName() const;
    cNamelist &getOpenName();

    const char *getKey() const;
    char **getKeyPtr();
    void setKey(char *value);

    const unit_data *getToRoom() const;
    unit_data *getToRoom();
    void setToRoom(unit_data *value);

    uint8_t getSkillDifficulty() const;
    uint8_t *getSkillDifficultyPtr();
    void setSkillDifficulty(uint8_t value);

    uint8_t getDoorFlags() const;
    bool isDoorFlagSet(uint8_t value) const;
    void setDoorFlags(uint8_t value);
    uint8_t *getDoorFlagsPtr();

private:
    cNamelist open_name;         ///< For Open & Enter
    char *key{nullptr};          ///<
    unit_data *to_room{nullptr}; ///<
    uint8_t difficulty{0};       ///< Skill needed for swim, climb, search, pick-lock
    int weight{0};               ///< Used for shortest path algorithm
    uint8_t exit_info{0};        ///< Door info flags
};
