/*
 $Author: All $
 $RCSfile: config.h,v $
 $Date: 2004/01/09 20:34:23 $
 $Revision: 2.4 $
 */
#pragma once

#ifdef _WINDOWS
    #include <winsock.h>
#else
    #include <arpa/inet.h>
#endif
#include <map>
#include <vector>
#include "fight.h"
#include "common.h"
#include "color.h"

class CServerConfiguration
{
public:
    CServerConfiguration() = default;
    CServerConfiguration(const CServerConfiguration &) = delete;
    auto operator=(const CServerConfiguration &) -> CServerConfiguration & = delete;
    CServerConfiguration(CServerConfiguration &&) = delete;
    auto operator=(CServerConfiguration &&) -> CServerConfiguration & = delete;
    ~CServerConfiguration() = default;

    static constexpr auto MAX_MPLEX_HOSTS = 10U;

    void Boot(std::string srvcfg);

    [[nodiscard]] auto FromLAN(const char *pFromHost) const -> bool;
    [[nodiscard]] auto ValidMplex(const sockaddr_in *isa) const -> bool;

    [[nodiscard]] auto isAccounting() const -> bool;
    [[nodiscard]] auto isAliasShout() const -> bool;
    [[nodiscard]] auto isBBS() const -> bool;
    [[nodiscard]] auto isBOB() const -> bool;
    [[nodiscard]] auto isLawful() const -> bool;
    [[nodiscard]] auto isNoSpecials() const -> bool;

    [[nodiscard]] auto getColorString() const -> const std::string &;
    [[nodiscard]] auto getColorType() const -> const color_type &;
    [[nodiscard]] auto getDILFileDir() const -> const std::string &;
    [[nodiscard]] auto getEtcDir() const -> const std::string &;
    [[nodiscard]] auto getImmortalName() const -> const std::string &;
    [[nodiscard]] auto getLibDir() const -> const std::string &;
    [[nodiscard]] auto getLocalhost() const -> const in_addr &;
    [[nodiscard]] auto getLogDir() const -> const std::string &;
    [[nodiscard]] auto getLogo() const -> const std::string &;
    [[nodiscard]] auto getMotherPort() const -> int;
    [[nodiscard]] auto getMplexHosts() const -> const std::vector<in_addr> &;
    [[nodiscard]] auto getMudName() const -> const std::string &;
    [[nodiscard]] auto getPlyDir() const -> const std::string &;
    [[nodiscard]] auto getPromptString() const -> const std::string &;
    [[nodiscard]] auto getReboot() const -> int;
    [[nodiscard]] auto getRentModifier() const -> int;
    [[nodiscard]] auto getShout() const -> int;
    [[nodiscard]] auto getSubnetMask() const -> const in_addr &;
    [[nodiscard]] auto getZoneDir() const -> const std::string &;

    [[nodiscard]] auto getFileInEtcDir(const std::string &filename) const -> std::string;
    [[nodiscard]] auto getFileInLibDir(const std::string &filename) const -> std::string;
    [[nodiscard]] auto getFileInLogDir(const std::string &filename) const -> std::string;

private:
    static void checkDirectoryExists(const std::string &name, const std::string &directory);
    static auto stringToIPAddress(const std::string &ip_address, const std::string &error_msg) -> in_addr;

    int m_nMotherPort{4999};                             // TCP port number
    int m_nRentModifier{10};                             //
    bool m_bAccounting{false};                           //
    bool m_bAliasShout{true};                            //
    bool m_bBBS{false};                                  //
    bool m_bLawful{false};                               // Unused apart from unit_tests so far
    bool m_bNoSpecials{false};                           //
    bool m_bBOB{false};                                  //
    int m_nShout{1};                                     // Unused apart from unit_tests so far
    int m_hReboot{0};                                    // Hour 0-23 to reboot server on
    color_type color{};                                  //
    in_addr m_sSubnetMask{};                             // Unused apart from unit_tests so far
    in_addr m_sLocalhost{};                              // Unused apart from unit_tests so far
    std::vector<in_addr> m_aMplexHosts{MAX_MPLEX_HOSTS}; // Unused apart from unit_tests so far
    std::string m_promptstr{};                           // Unused apart from unit_tests so far
    std::string m_libdir{};                              // The lib directory
    std::string m_plydir{};                              // The player directory
    std::string m_etcdir{};                              // The etc directory
    std::string m_logdir{};                              // The log directory
    std::string m_zondir{};                              // The zone directory
    std::string m_dilfiledir{};                          // The dil file director
    std::string m_mudname{};                             // The mud name
    std::string m_pLogo{};                               // Intro screen
    std::string m_pColor{};                              //
    std::string m_pImmortName{};                         // Name of the Immortal of the mud
private:
    static auto parse_match_name(const char **pData, const char *pMatch, std::string default_value) -> std::string;
    static auto parse_match_namelist(const char **pData, const char *pMatch) -> std::vector<std::string>;
};

extern CServerConfiguration g_cServerConfig;
