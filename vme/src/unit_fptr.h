#pragma once

#include "bytestring.h"
#include "destruct.h"
#include "essential.h"
#include "event.h"
#include "vme.h"

class unit_fptr : public basedestruct
{
public:
    unit_fptr();
    ~unit_fptr();

    uint16_t getFunctionPointerIndex() const;
    void readFunctionPointerIndexFrom(CByteBuffer &buf, int &nError);
    void setFunctionPointerIndex(uint16_t value);

    uint8_t getFunctionPriority() const;
    void readFunctionPriorityFrom(CByteBuffer &buf, int &nError);
    void setFunctionPriority(uint8_t value);

    uint16_t getHeartBeat() const;
    uint16_t *getHeartBeatPtr();
    void readHeartBeatFrom(CByteBuffer &buf, int &nError);
    void setHeartBeat(uint16_t value);

    bool isActivateOnEventFlagSet(uint16_t value);
    void setActivateOnEventFlag(uint16_t value);
    void setAllActivateOnEventFlags(uint16_t value);
    void removeActivateOnEventFlag(uint16_t value);
    void readActivateOnEventFlagsFrom(CByteBuffer &buf, int &nError);
    uint16_t getAllActivateOnEventFlags() const;

    void *getData();
    void freeData();
    void setData(void *value);
    void readDataFrom(CByteBuffer &buf);

    unit_fptr *getNext();
    void setNext(unit_fptr *value);

    eventq_elem *getEventQueue();
    void setEventQueue(eventq_elem *value);

    int destruct_classindex();

private:
    uint16_t index{0};                  ///< Index to function pointer array
    uint8_t priority{FN_PRI_CHORES};    ///< Order to insert ftpr on unit (2020)
    uint16_t heart_beat{PULSE_SEC * 5}; ///< in 1/4 of a sec
    uint16_t flags{0};                  ///< When to override next function (boolean)
    void *data{nullptr};                ///< Pointer to data local for this unit
    unit_fptr *next{nullptr};           ///< Next in linked list
    eventq_elem *event{nullptr};        ///< pointer to eventq for quick removing
};
