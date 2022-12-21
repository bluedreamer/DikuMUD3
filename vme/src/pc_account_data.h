#pragma once

#include "bytestring.h"

class pc_account_data
{
public:
    pc_account_data() = default;

    void readFrom(CByteBuffer &buf, uint8_t unit_version, int &error);

    void writeTo(CByteBuffer &buf);
    float getAccountBalance() const;
    void setAccountBalance(float value);
    void reduceAccountBalanceBy(float value);
    void increaseAccountBalanceBy(float value);

    ubit32 getCreditLimit() const;
    void setCreditLimit(ubit32 value);

    ubit32 getTotalCredit() const;
    void increaseTotalCreditBy(ubit32 value);
    void reduceTotalCreditBy(ubit32 value);
    void setTotalCredit(ubit32 value);

    sbit16 getLastFourDigitsofCreditCard();
    void setLastFourDigitsofCreditCard(sbit16 value);

    uint8_t getCrackAttempts() const;
    void setCrackAttempts(uint8_t value);

    uint8_t getDiscountPercentage() const;
    void setDiscountPercentage(uint8_t value);

    const ubit32 &getFlatRateExpirationDate() const;
    void incFlatRateExpirationDate(ubit32 value);
    void setFlatRateExpirationDate(ubit32 value);

private:
    float credit{0.0f};     ///< How many coin units are left on account?
    ubit32 credit_limit{0}; ///< In coin units (i.e. cents / oerer)
    ubit32 total_credit{0}; ///< Accumulated credit to date (coin units)
    sbit16 last4{-1};       ///< The last four digits of his credit card, or -1
    uint8_t cracks{0};      ///< Crack-attempts on CC last4
    uint8_t discount{0};    ///< 0 - 100% discount
    ubit32 flatrate{0};     ///< The expiration date of a flat rate service
};
