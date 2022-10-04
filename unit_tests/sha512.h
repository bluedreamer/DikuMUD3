#pragma once
#include <openssl/evp.h>
#include <openssl/opensslv.h>

#include <array>
#include <string>

class sha512
{
public:
    sha512();
    ~sha512();

    void generate(const std::string &filename);

    [[nodiscard]] std::array<unsigned char, EVP_MAX_MD_SIZE> getChecksum() const;
    [[nodiscard]] const std::string &getChecksumString() const;

private:
    bool checksum_calculated{false};
    EVP_MD_CTX *context{nullptr};
    std::array<unsigned char, EVP_MAX_MD_SIZE> checksum{};
    std::string checksum_string;
};
