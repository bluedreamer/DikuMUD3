#pragma once
#include "essential.h"

#include <cstring>
#include <forward_list>
#include <string>

class unit_data;
class zone_type;

/* A linked sorted list of all units within a zone file */
class file_index_type
{
public:
    file_index_type(zone_type *zone, const char *name, uint8_t type);
    ~file_index_type() = default;                                 ///< Default dtor
    file_index_type(const file_index_type &) = delete;            ///< Delete copy ctor
    file_index_type &operator=(const file_index_type &) = delete; ///< Delete assignment
    file_index_type(file_index_type &&) = delete;                 ///< Delete move ctor
    file_index_type &operator=(file_index_type &&) = delete;      ///< Delete move assignment

    [[nodiscard]] unit_data *find_symbolic_instance();
    [[nodiscard]] unit_data *find_symbolic_instance_ref(unit_data *ref, uint16_t bitvector);

    [[nodiscard]] const char *getName() const;
    [[nodiscard]] zone_type *getZone() const;
    [[nodiscard]] long getFilepos() const;
    [[nodiscard]] uint32_t getLength() const;
    [[nodiscard]] uint32_t getCRC() const;
    [[nodiscard]] int16_t getNumInZone() const;
    [[nodiscard]] uint16_t getNumInMem() const;
    [[nodiscard]] uint16_t getRoomNum() const;
    [[nodiscard]] uint8_t getType() const;

    [[nodiscard]] bool Empty() const;
    [[nodiscard]] unit_data *Front() const;
    [[nodiscard]] std::forward_list<unit_data *>::iterator Begin();
    [[nodiscard]] std::forward_list<unit_data *>::iterator End();
    void PushFront(unit_data *value);
    void Remove(unit_data *value);

    void IncrementNumInMemory();
    void DecrementNumInMemory();

    void IncrementNumInZone();

    /**
     * @param value Name to set
     * @param to_lower If true convert to lower case
     */
    void setCRC(uint32_t value);
    void setNumInZone(int16_t value);
    void setLength(uint32_t value);
    void setFilepos(long value);
    void setRoomNum(uint16_t value);

private:
    std::forward_list<unit_data *> m_fi_unit_list; ///< This list of units that match this file_index
    std::string m_name{};                          ///< Unique within this list
    zone_type *m_zone{nullptr};                    ///< Pointer to owner of structure
    long m_filepos{0};                             ///< Byte offset into file
    uint32_t m_length{0};                          ///< No of bytes to read
    uint32_t m_crc{0};                             ///< CRC check for compressed items
    int16_t m_no_in_zone{0};                       ///< Updated in zone reset for reset
    uint16_t m_no_in_mem{0};                       ///< Number of these in the game
    uint16_t m_room_no{0};                         ///< The number of the room
    uint8_t m_type{0};                             ///< Room/Obj/Char or other?
};
