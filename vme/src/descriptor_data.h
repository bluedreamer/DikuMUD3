#pragma once

#include "hookmud.h"
#include "snoop_data.h"

#include <ctime>

class unit_data;

class descriptor_data
{
public:
    explicit descriptor_data(cMultiHook *pe);
    ~descriptor_data();

    void CreateBBS();
    void RemoveBBS();

    time_t getLastLogonTime() const;
    void setLastLogonTime(time_t value);

    cMultiHook *getMultiHookPtr();

    uint16_t getMultiHookID() const;

    using FunctionPtr = void (*)(descriptor_data *, char *);
    const FunctionPtr getFunctionPtr() const;
    void callFunctionPtr(descriptor_data *data, char *arg) const;
    void setFunctionPtr(FunctionPtr value);

    int getState() const;
    void setState(int value);
    int postincrementState();

    const char *getHostname() const;
    void setHostname(const char *value);

    uint16_t getMplexPortNum() const;
    void setMplexPortNum(uint16_t value);

    uint8_t getSerialLine() const;
    void setSerialLine(uint8_t value);

    int predecrementLoopWaitCounter();
    void setLoopWaitCounter(int value);

    uint16_t getMinutesPlayerIdle() const;
    void setMinutesPlayerIdle(uint16_t value);
    void incrementMinutesPlayerIdle();

    void clearLocalString();
    const char *getLocalString() const;
    void setLocalString(const char *str);
    void appendLocalString(const char *str);

    using PostEditFunctionPtr = void (*)(descriptor_data *);
    bool hasPostEditFunctionPtr() const;
    void callPostEditFunctionPtr(descriptor_data *data) const;
    void setPostEditFunctionPtr(PostEditFunctionPtr value);

    const unit_data *cgetEditing() const;
    unit_data *getEditing();
    void setEditing(unit_data *value);

    const void *getEditingReference() const;
    void setEditReference(void *value);

    int getPromptMode() const;
    void setPromptMode(int value);

    const char *getLastCommand() const;
    void setLastCommand(const char *value);

    char *getCommandHistory();
    void setCommandHistory(const char *value);

    cQueue &getInputQueue();

    const unit_data *cgetCharacter() const;
    unit_data *getCharacter();
    void setCharacter(unit_data *value);

    const unit_data *cgetOriginalCharacter() const;
    unit_data *getOriginalCharacter();
    void setOriginalCharacter(unit_data *value);

    const snoop_data &cgetSnoopData() const;
    snoop_data &getSnoopData();

    descriptor_data *getNext();
    void setNext(descriptor_data *value);

private:
    time_t logon{0};                        ///< Time of last connect
    cMultiHook *multi{nullptr};             ///< Multi element pointer
    uint16_t id{0};                         ///< The ID for the multi
    FunctionPtr fptr{nullptr};              ///<
    int state{0};                           ///< Locally used in each fptr
    char host[50]{0};                       ///< hostname
    uint16_t nPort{0};                      ///< Mplex port
    uint8_t nLine{0};                       ///< Serial Line
    int wait{0};                            ///< wait for how many loops
    uint16_t timer{0};                      ///< num of hours idleness for mortals
    uint32_t replyid{0};                    ///< Used for 'tell reply'
    char *localstr{nullptr};                ///< For the 'modify-string' system. This string is expanded while editing
    PostEditFunctionPtr postedit{nullptr};  ///<
    unit_data *editing{nullptr};            ///<
    void *editref{nullptr};                 ///< pointer to "where we are editing". when using (volatile) extras + boards
    int prompt_mode{0};                     ///< control of prompt-printing
    char last_cmd[MAX_INPUT_LENGTH + 1]{0}; ///< the last entered cmd_str
    char history[MAX_INPUT_LENGTH + 1]{0};  ///< simple command history
    cQueue qInput;                          ///< q of unprocessed input
    unit_data *character{nullptr};          ///< linked to char
    unit_data *original{nullptr};           ///< original char
    snoop_data snoop;                       ///< to snoop people.
    descriptor_data *next{nullptr};         ///< link to next descriptor
};
