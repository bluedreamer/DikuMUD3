#pragma once

#include "bytestring.h"
#include "destruct.h"
#include "essential.h"
#include "event.h"

class unit_data;

class unit_affected_type : public basedestruct
{
public:
    int16_t getID() const;
    void setID(int16_t value);

    void bread(CByteBuffer *pBuf, int *nError);

    ubit16 getBeat() const;
    void setBeat(ubit16 value);

    int16_t getDuration() const;
    void setDuration(int16_t value);
    void decrementDuration();

    int getDataAtIndex(size_t index) const;
    void setDataAtIndex(size_t index, int value);
    void incrementDataAtIndex(size_t index);
    int readFromIntoDataAtIndex(CByteBuffer &buf, size_t index);

    int16_t getFirstFI() const;
    void setFirstFI(int16_t value);

    int16_t getTickFI() const;
    void setTickFI(int16_t value);

    int16_t getLastFI() const;
    void setLastFI(int16_t value);

    int16_t getApplyFI() const;
    void setApplyFI(int16_t value);

    const eventq_elem *cgetEventQueueElement() const;
    eventq_elem *getEventQueueElement();
    void setEventQueueElement(eventq_elem *value);

    const unit_data *cgetOwner() const;
    unit_data *getOwner();
    void setOwner(unit_data *value);

    unit_affected_type *getNext();
    void setNext(unit_affected_type *value);

    unit_affected_type *getG_Next();
    void setG_Next(unit_affected_type *value);

    unit_affected_type *getG_Previous();
    void setG_Previous(unit_affected_type *value);

    int destruct_classindex();

private:
    int16_t id{0};                          ///<
    ubit16 beat{0};                         ///< Beat in 1/4 of secs, 0 = None
    int16_t duration{0};                    ///< How many beats until end
    sbit32 data[3]{0};                      ///<
    int16_t firstf_i{0};                    ///<
    int16_t tickf_i{0};                     ///<
    int16_t lastf_i{0};                     ///<
    int16_t applyf_i{0};                    ///<
    eventq_elem *event{nullptr};            ///< pointer to eventq for quick removing
    unit_data *owner{nullptr};              ///<
    unit_affected_type *next{nullptr};      ///<
    unit_affected_type *gnext{nullptr};     ///<
    unit_affected_type *gprevious{nullptr}; ///<
};
