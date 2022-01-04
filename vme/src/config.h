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
#include "fight.h"
#include "common.h"
#include "color.h"

class CServerConfiguration
{
public:
    CServerConfiguration() = default;

    void Boot(char *srvcfg);

    int FromLAN(char *pFromHost);
    int ValidMplex(struct sockaddr_in *isa);

    [[nodiscard]] int getMotherPort() const;
    [[nodiscard]] int getRentModifier() const;
    [[nodiscard]] bool isAccounting() const;
    [[nodiscard]] bool isAliasShout() const;
    [[nodiscard]] bool isBBS() const;
    [[nodiscard]] bool isLawful() const;
    [[nodiscard]] bool isNoSpecials() const;
    [[nodiscard]] bool isBOB() const;
    [[nodiscard]] int getShout() const;
    [[nodiscard]] int getReboot() const;
    [[nodiscard]] const color_type &getColor() const;
    [[nodiscard]] const in_addr &getSubnetMask() const;
    [[nodiscard]] const in_addr &getLocalhost() const;

public:
private:
    int m_nMotherPort{4999};     //
    int m_nRentModifier{10};     //
    bool m_bAccounting{false};   //
    bool m_bAliasShout{true};    //
    bool m_bBBS{false};          //
    bool m_bLawful{false};       // Unused apart from unit_tests so far
    bool m_bNoSpecials{false};   //
    bool m_bBOB{false};          //
    int m_nShout{1};             // Unused apart from unit_tests so far
    int m_hReboot{0};            //
    color_type color{};          //
    in_addr m_sSubnetMask{};     // Unused apart from unit_tests so far
    in_addr m_sLocalhost{};      // Unused apart from unit_tests so far
    in_addr m_aMplexHosts[10]{}; // Unused apart from unit_tests so far
    char *m_promptstr{nullptr};  // Unused apart from unit_tests so far

public:
    char *m_libdir{nullptr}; /* The lib directory, etc */
    char *m_plydir{nullptr};
    char *m_etcdir{nullptr};
    char *m_logdir{nullptr};
    char *m_zondir{nullptr};
    char *m_dilfiledir{nullptr};
    char *m_mudname{nullptr}; /* The mud name */
    char *m_pLogo{nullptr};   /* Intro screen                    */
    char *m_pColor{nullptr};
    char *m_pImmortName{nullptr}; /*Name of the Immortal of the mud */
};

extern CServerConfiguration g_cServerConfig;
