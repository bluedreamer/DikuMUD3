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

    uint32_t getCreditLimit() const;
    void setCreditLimit(uint32_t value);

    uint32_t getTotalCredit() const;
    void increaseTotalCreditBy(uint32_t value);
    void reduceTotalCreditBy(uint32_t value);
    void setTotalCredit(uint32_t value);

    int16_t getLastFourDigitsofCreditCard();
    void setLastFourDigitsofCreditCard(int16_t value);

    uint8_t getCrackAttempts() const;
    void setCrackAttempts(uint8_t value);

    uint8_t getDiscountPercentage() const;
    void setDiscountPercentage(uint8_t value);

    const uint32_t &getFlatRateExpirationDate() const;
    void incFlatRateExpirationDate(uint32_t value);
    void setFlatRateExpirationDate(uint32_t value);

private:
    float credit{0.0f};       ///< How many coin units are left on account?
    uint32_t credit_limit{0}; ///< In coin units (i.e. cents / oerer)
    uint32_t total_credit{0}; ///< Accumulated credit to date (coin units)
    int16_t last4{-1};        ///< The last four digits of his credit card, or -1
    uint8_t cracks{0};        ///< Crack-attempts on CC last4
    uint8_t discount{0};      ///< 0 - 100% discount
    uint32_t flatrate{0};     ///< The expiration date of a flat rate service
};
