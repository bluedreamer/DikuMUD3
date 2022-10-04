#include "sha512.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

sha512::sha512()
    : context(EVP_MD_CTX_create())
{
    if (EVP_DigestInit_ex(context, EVP_sha3_512(), nullptr) == 0)
    {
        throw std::logic_error("EVP_DigestInit_ex() failed");
    }
}

sha512::~sha512()
{
    EVP_MD_CTX_destroy(context);
    EVP_cleanup();
}

void sha512::generate(const std::string &filename)
{
    if (checksum_calculated)
    {
        throw std::logic_error("Checksum already calculated");
    }

    const size_t blocksize = 32768;
    std::array<unsigned char, blocksize> data_block{};
    auto filesize = std::filesystem::file_size(filename);
    std::ifstream in(filename, std::ios::binary);

    while (filesize >= blocksize)
    {
        in.read(reinterpret_cast<char *>(data_block.data()), blocksize);
        if (EVP_DigestUpdate(context, data_block.data(), blocksize) == 0)
        {
            throw std::logic_error("EVP_DigestUpdate() failed");
        }
        filesize -= blocksize;
    }

    if (filesize > 0)
    {
        in.read(reinterpret_cast<char *>(data_block.data()), filesize);
        if (EVP_DigestUpdate(context, data_block.data(), filesize) == 0)
        {
            throw std::logic_error("EVP_DigestUpdate() failed");
        }
    }

    unsigned int digest_filesize = std::filesystem::file_size(filename);
    if (EVP_DigestFinal(context, checksum.data(), &digest_filesize) == 0)
    {
        throw std::logic_error("EVP_DigestFinal() failed");
    }

    std::ostringstream os;
    for (auto ch : checksum)
    {
        os << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned int>(ch);
    }
    checksum_string = os.str();

    checksum_calculated = true;
}

std::array<unsigned char, EVP_MAX_MD_SIZE> sha512::getChecksum() const
{
    if (!checksum_calculated)
    {
        throw std::logic_error("No checksum calculated yet!");
    }
    return checksum;
}

const std::string &sha512::getChecksumString() const
{
    if (!checksum_calculated)
    {
        throw std::logic_error("No checksum calculated yet!");
    }

    return checksum_string;
}
