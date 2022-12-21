#pragma once

#include "constants.h"
#include "essential.h"
#include "extra.h"
#include "file_index_type.h"
#include "namelist.h"
#include "unit_affected_type.h"
#include "unit_dil_affected_type.h"
#include "unit_fptr.h"
#include "weather.h"
#include "zone_type.h"

/**
 * Creates a new unit of the specified type
 * @param type One of UNIT_ST_ROOM, UNIT_ST_OBJ, UNIT_ST_PC, UNIT_ST_NPC
 * @return new'ed pointer to clasee
 */
unit_data *new_unit_data(uint8_t type, file_index_type *fi);

class unit_data : public basedestruct
{
public:
    static constexpr int16_t MinAlignment = -1000; ///< Minimum possible value for alignment
    static constexpr int16_t MaxAlignment = 1000;  ///< Maximum possible value for alignment
    static constexpr const char *NO_NAME = "NO-NAME";
    static constexpr const char *NO_ZONE = "NO-ZONE";

public:
    /**
     * @name Constructors/Destructor
     * @{
     */

    /**
     * @param unit_type One of UNIT_ST_NPC, UNIT_ST_PC, UNIT_ST_ROOM, UNIT_ST_OBJ
     */
    explicit unit_data(uint8_t unit_type, file_index_type *fi);

    unit_data(const unit_data &) = delete;            ///< Delete copy ctor
    unit_data(unit_data &&) = delete;                 ///< Delete move ctor
    unit_data &operator=(const unit_data &) = delete; ///< Delete assignment
    unit_data &operator=(unit_data &&) = delete;      ///< Delete move assignment
    ~unit_data() override;
    /// @}

    unit_data *copy();

    /**
     * @name What type is this object related code
     * @{
     */
    uint8_t getUnitType() const;
    bool isRoom() const { return m_status == UNIT_ST_ROOM; }
    bool isObj() const { return m_status == UNIT_ST_OBJ; }
    bool isNPC() const { return m_status == UNIT_ST_NPC; }
    bool isPC() const { return m_status == UNIT_ST_PC; }
    bool isChar() const { return isPC() || isNPC(); }
    ///@}

    /**
     * Is functions
     * @{
     */
    bool isTransparent() const { return !isBuried() && isUnitFlagSet(UNIT_FL_TRANS) && !isClosed(); }
    bool isClosed() const { return isOpenFlagSet(EX_CLOSED); }
    bool isBuried() const { return isUnitFlagSet(UNIT_FL_BURIED); }
    bool isGood() const { return m_alignment >= 350; }
    bool isEvil() const { return m_alignment <= -350; }
    bool isNeutral() const { return !isGood() && !isEvil(); }
    bool isOutside() const { return !m_outside->isUnitFlagSet(UNIT_FL_INDOORS); }
    bool isWornOn(ubit32 part) const { return IS_SET(m_manipulate, part); }
    bool isDark() const { return getTotalLightValue() < 0; }
    bool isLight() const { return getTotalLightValue() >= 0; }
    ///@}

    int8_t getOutsideLight() const { return !isUnitFlagSet(UNIT_FL_INDOORS) ? g_time_light[g_sunlight] : 0; }
    int getTotalLightValue() const { return m_light + getOutsideLight() + (m_outside ? m_outside->m_light : 0); }

    unit_data *inRoom();
    /**
     * @return Characters sex or neutral if not a character
     */
    virtual uint8_t getSex() const { return SEX_NEUTRAL; }

    /**
     * @name Name related code
     * @{
     */
    cNamelist &getNames();
    const cNamelist &getNames() const;
    /// @}

    /**
     * @name Function Pointer related code
     * @{
     */
    unit_fptr *getFunctionPointer();
    void setFunctionPointer(unit_fptr *value);
    /// @}

    /**
     * @name Unit affected type related code
     * @{
     */
    unit_affected_type *getUnitAffected();
    void setUnitAffected(unit_affected_type *value);
    /// @}

    /**
     * @name File index related code
     * @{
     */
    file_index_type *getFileIndex();
    const file_index_type *getFileIndex() const;

    void setFileIndex(file_index_type *fi);

    [[nodiscard]] const char *getFileIndexZoneName() const
    {
        if (m_fi)
        {
            return m_fi->getZone()->getName().c_str();
        }
        return NO_ZONE;
    }

    [[nodiscard]] const char *getFileIndexName() const
    {
        if (m_fi)
        {
            return m_fi->getName();
        }
        return NO_NAME;
    }

    [[nodiscard]] std::string getFileIndexSymName() const
    {
        std::string retval{getFileIndexName()};
        retval += '@';
        retval += getFileIndexZoneName();
        return retval;
    }
    /// @}

    /**
     * @name Key related code
     * @{
     */
    const char *getKey() const;
    char **getKeyPtr();
    void setKey(char *value);
    /// @}

    /**
     * @name Contains / Contained related code
     * @{
     */
    unit_data *getUnitIn();
    const unit_data *getUnitIn() const;
    void setUnitIn(unit_data *value);

    const unit_data *getUnitContains() const;
    unit_data *getUnitContains();
    void setUnitContains(unit_data *value);
    /// @}

    /**
     * @name Linked List related code
     * @{
     */
    const unit_data *getNext() const;
    unit_data *getNext();
    void setNext(unit_data *value);

    unit_data *getGlobalNext();
    const unit_data *getGlobalNext() const;
    void setGlobalNext(unit_data *value);

    unit_data *getGlobalPrevious();
    const unit_data *getGlobalPrevious() const;
    void setGlobalPrevious(unit_data *value);
    /// @}

    /**
     * @name Flag related code
     * @{
     */
    ubit32 getManipulate() const;
    ubit32 *getManipulatePtr();
    void setAllManipulateFlags(ubit32 value);
    void setManipulateFlag(ubit32 value);

    uint16_t getUnitFlags() const;
    uint16_t *getUnitFlagsPtr();
    void setAllUnitFlags(uint16_t value);
    void setUnitFlag(uint16_t value);
    void removeUnitFlag(uint16_t value);
    bool isUnitFlagSet(int flag) const { return IS_SET(m_flags, flag); }
    /// @}

    /**
     * @name Weight related code
     * @{
     */
    int32_t getBaseWeight() const;
    void setBaseWeight(int32_t value);

    int32_t getWeight() const;
    void reduceWeightBy(int32_t value);
    void increaseWeightBy(int32_t value);
    void setWeight(int32_t value);

    int32_t getContainingWeight() const { return m_weight - m_base_weight; }
    /// @}

    /**
     * @name Capacity related code
     * @{
     */
    int16_t getCapacity() const;
    int16_t *getCapacityPtr();
    void setCapacity(int16_t value);
    /// @}

    /**
     * @name Size related code
     * @{
     */
    uint16_t getSize() const;
    uint16_t *getSizePtr();
    void setSize(uint16_t value);
    void increaseSizeBy(uint16_t value);
    /// @}

    /**
     * @name Open object related code
     * @{
     */
    uint8_t getOpenFlags() const;
    uint8_t *getOpenFlagsPtr();
    void setAllOpenFlags(uint8_t value);
    void setOpenFlag(uint8_t value);
    bool isOpenFlagSet(uint8_t flag) const { return IS_SET(m_open_flags, flag); }

    uint8_t getOpenDifficulty() const;
    uint8_t *getOpenDifficultyPtr();
    void setOpenDifficulty(uint8_t value);
    /// @}

    /**
     * @name Light related code
     * @{
     */
    int16_t getNumberOfActiveLightSources() const;
    void changeNumberOfActiveLightSourcesBy(int16_t value);
    void setNumberOfActiveLightSources(int16_t value);

    int16_t getLightOutput() const;
    void setLightOutput(int16_t value);
    void changeLightOutputBy(int16_t value);

    int16_t getTransparentLightOutput() const;
    void setTransparentLightOutput(int16_t value);
    void changeTransparentLightOutputBy(int16_t value);
    ///@}

    /**
     * @name
     * @{
     */
    uint8_t getNumberOfCharactersInsideUnit() const;
    void decrementNumberOfCharactersInsideUnit();
    void incrementNumberOfCharactersInsideUnit();
    void setNumberOfCharactersInsideUnit(uint8_t value);
    /// @}

    /**
     * @name
     * @{
     */
    uint8_t getLevelOfWizardInvisibility() const;
    uint8_t *getLevelOfWizardInvisibilityPtr();
    void setLevelOfWizardInvisibility(uint8_t value);
    /// @}

    /**
     * @name Hitpoint related code
     * Code for Max and Current hitpoints
     * @{
     */
    int32_t getMaximumHitpoints() const;
    int32_t *getMaximumHitpointsPtr();
    void setMaximumHitpoints(int32_t value);

    int32_t getCurrentHitpoints() const;
    int32_t *getCurrentHitpointsPtr();
    void setCurrentHitpoints(int32_t value);
    void changeCurrentHitpointsBy(int32_t value);
    ///@}

    /**
     * @name Alignment related code
     * @{
     */
    int16_t getAlignment() const;
    int16_t *getAlignmentPtr();

    /**
     * Modify alignment by value - negative numbers are subtracted, positive added.
     *
     * If the change exceeds alignment limits, alignment is set to either min or max
     * value and false is returned.
     *
     * eg current alignment = -900 and value = -200
     * result alignment = -1000 and false is returned.
     *
     * @param value Amount to vary alignment by.
     */
    void changeAlignmentBy(int64_t value);

    /**
     * Set alignment to value
     *
     * For VME
     *
     * If the change exceeds alignment limits, alignment is set to either min or max
     * value and false is returned.
     * eg. current alignment = -900 and value = -200
     * result alignment = -1000 and false is returned.
     *
     * For VMC (`#define VMC` is set)
     *
     * If the change exceeds alignment limits, alignment is set to 0 and dmc_error is called
     *
     * @param value Amount to set alignment to.
     * @return true if the change was accepted as is, false if the change overflowed limits and was truncated
     */
    bool setAlignment(int64_t value);
    ///@}

    /**
     * @name Name / Description related code
     * @{
     */
    const std::string &getTitle() const;
    std::string *getTitlePtr();
    void setTitle(std::string value);

    const std::string &getDescriptionOfOutside() const;
    std::string *getDescriptionOfOutsidePtr();
    void setDescriptionOfOutside(std::string value);

    const std::string &getDescriptionOfInside() const;
    std::string *getDescriptionOfInsidePtr();
    void setDescriptionOfInside(std::string value);
    /// @}

    /**
     * @name
     * @{
     */
    const extra_list &getExtraList() const;
    extra_list &getExtraList();
    /// @}

    int destruct_classindex();
    std::string json();

private:
    cNamelist m_names;                       ///< Name Keyword list for get, enter, etc.
    unit_fptr *m_func{nullptr};              ///< Function pointer type
    unit_affected_type *m_affected{nullptr}; ///<
    file_index_type *m_fi{nullptr};          ///< Unit file-index
    char *m_key{nullptr};                    ///< Pointer to fileindex to Unit which is the key
    unit_data *m_outside{nullptr};           ///< Pointer out of the unit, ie. from an object out to the char carrying it
    unit_data *m_inside{nullptr};            ///< Linked list of chars,rooms & objs
    unit_data *m_next{nullptr};              ///< For next unit in 'inside' linked list
    unit_data *m_gnext{nullptr};             ///< global l-list of objects, chars & rooms
    unit_data *m_gprevious{nullptr};         ///< global l-list of objects, chars & rooms
    ubit32 m_manipulate{0};                  ///< WEAR_XXX macros
    uint16_t m_flags{0};                     ///< Invisible, can_bury, burried...
    int32_t m_base_weight{0};                ///< The "empty" weight of a room/char/obj (lbs)
    int32_t m_weight{0};                     ///< Current weight of a room/obj/char
    int16_t m_capacity{0};                   ///< Capacity of obj/char/room, -1 => any
    uint16_t m_size{0};                      ///< (cm) MOBs height, weapons size, ropes length
    uint8_t m_status{0};                     ///< IS_ROOM, IS_OBJ, IS_PC, IS_NPC
    uint8_t m_open_flags{0};                 ///< In general OPEN will mean can "enter"?
    uint8_t m_open_diff{0};                  ///< Open difficulty
    int16_t m_light{0};                      ///< Number of active light sources in unit
    int16_t m_bright{0};                     ///< How much the unit shines
    int16_t m_illum{0};                      ///< how much bright is by transparency
    uint8_t m_chars{0};                      ///< How many chars is inside the unit
    uint8_t m_minv{0};                       ///< Level of wizard invisible
    int32_t m_max_hp{0};                     ///< The maximum number of hitpoints
    int32_t m_hp{0};                         ///< The actual amount of hitpoints left
    int16_t m_alignment{0};                  ///< +-1000 for alignments
    std::string m_title;                     ///< Room title, Char title, Obj "the barrel", NPC "the Beastly Fido"
    std::string m_out_descr;                 ///< The outside description of a unit
    std::string m_in_descr;                  ///< The inside description of a unit
    extra_list m_extra;                      ///< All the look 'at' stuff
};
