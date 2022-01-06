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
    CServerConfiguration &operator=(const CServerConfiguration &) = delete;
    CServerConfiguration(CServerConfiguration &&) = delete;
    CServerConfiguration &operator=(CServerConfiguration &&) = delete;
    ~CServerConfiguration() = default;

    static constexpr auto MAX_MPLEX_HOSTS = 10U;

    void Boot(std::string srvcfg);

    [[nodiscard]] bool FromLAN(const char *pFromHost) const;
    [[nodiscard]] bool ValidMplex(const sockaddr_in *isa) const;

    [[nodiscard]] bool isAccounting() const;
    [[nodiscard]] bool isAliasShout() const;
    [[nodiscard]] bool isBBS() const;
    [[nodiscard]] bool isBOB() const;
    [[nodiscard]] bool isLawful() const;
    [[nodiscard]] bool isNoSpecials() const;

    [[nodiscard]] const color_type &getColorType() const;
    [[nodiscard]] const in_addr &getLocalhost() const;
    [[nodiscard]] const in_addr &getSubnetMask() const;
    [[nodiscard]] const std::string &getColorString() const;
    [[nodiscard]] const std::string &getDILFileDir() const;
    [[nodiscard]] const std::string &getEtcDir() const;
    [[nodiscard]] const std::string &getImmortalName() const;
    [[nodiscard]] const std::string &getLibDir() const;
    [[nodiscard]] const std::string &getLogDir() const;
    [[nodiscard]] const std::string &getLogo() const;
    [[nodiscard]] const std::string &getMudName() const;
    [[nodiscard]] const std::string &getPlyDir() const;
    [[nodiscard]] const std::string &getPromptString() const;
    [[nodiscard]] const std::string &getZoneDir() const;
    [[nodiscard]] const std::vector<in_addr> &getMplexHosts() const;
    [[nodiscard]] int getMotherPort() const;
    [[nodiscard]] int getReboot() const;
    [[nodiscard]] int getRentModifier() const;
    [[nodiscard]] int getShout() const;

    [[nodiscard]] std::string getFileInLibDir(const std::string &filename) const;
    [[nodiscard]] std::string getFileInEtcDir(const std::string &filename) const;
    [[nodiscard]] std::string getFileInLogDir(const std::string &filename) const;

private:
    static void checkDirectoryExists(const std::string &name, const std::string &directory);
    static in_addr stringToIPAddress(const std::string &ip_address, const std::string &error_msg);

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
    static std::string parse_match_name(const char **pData, const char *pMatch, std::string default_value);
    static std::vector<std::string> parse_match_namelist(const char **pData, const char *pMatch);
};

extern CServerConfiguration g_cServerConfig;
