/*
 $Author: All $
 $RCSfile: config.cpp,v $
 $Date: 2004/09/18 19:52:56 $
 $Revision: 2.5 $
 */

#ifdef _WINDOWS
    #include <winsock2.h>
    #include <io.h>
#endif

#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <filesystem>
#include "essential.h"
#include "utility.h"
#include "config.h"
#include "files.h"
#include "textutil.h"
#include "db.h"
#include "str_parse.h"
#include "color.h"
#include "values.h"
#include "structs.h"

CServerConfiguration g_cServerConfig;

int CServerConfiguration::FromLAN(char *pFromHost)
{
    struct in_addr sTmp;

#ifdef _WINDOWS
    if (inet_addr(pFromHost) == INADDR_NONE)
    {
        slog(LOG_ALL, 0, "Localhost invalid.");
        return FALSE;
    }
#else
    if (inet_aton(pFromHost, &sTmp) == 0)
    {
        slog(LOG_ALL, 0, "Localhost [%s] invalid.", pFromHost);
        return FALSE;
    }
#endif

    return ((m_sSubnetMask.s_addr & m_sLocalhost.s_addr) == (m_sSubnetMask.s_addr & sTmp.s_addr));
}

int CServerConfiguration::ValidMplex(struct sockaddr_in *isa)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        if (isa->sin_addr.s_addr == m_aMplexHosts[i].s_addr)
            return TRUE;
    }

    return FALSE;
}

void CServerConfiguration::Boot(char *srvcfg)
{
    char Buf[2 * MAX_STRING_LENGTH];
    char *c, *d;
    int i;
#ifdef _WINDOWS
    struct _stat statbuf;
#else
    struct stat statbuf;

#endif

    slog(LOG_OFF, 0, "Booting server.");

    if (!file_exists(srvcfg))
    {
        slog(LOG_ALL, 0, "Could not find server configuration file. %s", srvcfg);
        exit(0);
    }

    config_file_to_string(srvcfg, Buf, sizeof(Buf));

    c = Buf;

    d = parse_match_name((const char **)&c, "mudname");
    if (d == NULL)
        d = str_dup("No Mud server name in server.cfg");
    slog(LOG_ALL, 0, "The Mud Name is %s.", d);
    if (strlen(d) > 49)
        d[50] = '\0';

    m_mudname = d;

    d = parse_match_name((const char **)&c, "immortal_name");
    if (d == NULL)
        d = str_dup("immortal");
    if (strlen(d) > PC_MAX_NAME)
        d[PC_MAX_NAME] = '\0';

    m_pImmortName = d;

    d = parse_match_name((const char **)&c, "libdir");
    if (d == nullptr)
    {
        m_libdir = "../lib/";
    }
    else
    {
        m_libdir = d;
    }
    checkDirectoryExists("lib", m_libdir);

    d = parse_match_name((const char **)&c, "etcdir");
    if (d == nullptr)
    {
        m_etcdir = "../etc/";
    }
    else
    {
        m_etcdir = d;
    }
    checkDirectoryExists("etc", m_etcdir);

    d = parse_match_name((const char **)&c, "logdir");
    if (d == nullptr)
    {
        m_logdir = "../log/";
    }
    else
    {
        m_logdir = d;
    }
    checkDirectoryExists("log", m_logdir);

    d = parse_match_name((const char **)&c, "zondir");
    if (d == NULL)
    {
        m_zondir = "../zone/";
    }
    else
    {
        m_zondir = d;
    }
    checkDirectoryExists("zone", m_zondir);
    m_zondir = d;

    d = parse_match_name((const char **)&c, "plydir");
    if (d == nullptr)
    {
        m_plydir = "../lib/ply/";
    }
    else
    {
        m_plydir = d;
    }
    checkDirectoryExists("player", m_plydir);

    d = parse_match_name((const char **)&c, "dil_file_dir");
    if (d == NULL)
        d = str_dup("../lib/file/");

#ifdef _WINDOWS
    _stat(d, &statbuf);
    if (!IS_SET(statbuf.st_mode, _S_IFDIR))
#else
    stat(d, &statbuf);
    if (!S_ISDIR(statbuf.st_mode))
#endif
    {
        slog(LOG_ALL, 0, "The dil file directory %s does not exist.", d);
        exit(0);
    }
    slog(LOG_ALL, 0, "The dil file directory is %s.", d);
    m_dilfiledir = d;
    if (parse_match_num((const char **)&c, "Port", &i))
    {
        m_nMotherPort = i;
    }

    if (!is_in(m_nMotherPort, 2000, 8000))
    {
        slog(LOG_ALL, 0, "Mother port not in [2000..8000].");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "auto_reboot_hour", &i))
    {
        m_hReboot = i;
    }

    if (!((m_hReboot >= 0) && (m_hReboot <= 24)))
    {
        m_hReboot = 0;
        slog(LOG_ALL, 0, "Auto Reboot Set to an invaild hour, disabling.");
    }

    if (parse_match_num((const char **)&c, "Rent", &i))
    {
        m_nRentModifier = i;
    }

    if (!is_in(m_nRentModifier, 0, 100))
    {
        slog(LOG_ALL, 0, "Rent modifier not in [0..100].");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "BOB", &i))
    {
        m_bBOB = i;
    }

    if (!is_in(m_bBOB, 0, 1))
    {
        slog(LOG_ALL, 0, "BOB not 0 or 1");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "Alias Shout", &i))
    {
        m_bAliasShout = i;
    }

    if (!is_in(m_bAliasShout, 0, 1))
    {
        slog(LOG_ALL, 0, "Alias Shout not 0 or 1");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "No Specials", &i))
    {
        m_bNoSpecials = i;
    }

    if (!is_in(m_bNoSpecials, 0, 1))
    {
        slog(LOG_ALL, 0, "Specials not 0 or 1");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "Lawful", &i))
    {
        m_bLawful = i;
    }

    if (!is_in(m_bLawful, 0, 1))
    {
        slog(LOG_ALL, 0, "Lawful not 0 or 1");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "BBS", &i))
    {
        m_bBBS = i;
    }

    if (!is_in(m_bBBS, 0, 1))
    {
        slog(LOG_ALL, 0, "BBS not 0 or 1");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "Accounting", &i))
    {
        m_bAccounting = i;
    }

    if (!is_in(m_bAccounting, 0, 1))
    {
        slog(LOG_ALL, 0, "Accounting not 0 or 1");
        exit(0);
    }

    if (parse_match_num((const char **)&c, "Shout", &i))
    {
        m_nShout = i;
    }

    if (!is_in(m_nShout, 0, 255))
    {
        slog(LOG_ALL, 0, "Shout level not [0..255]");
        exit(0);
    }

    d = parse_match_name((const char **)&c, "subnetmask");

    if (d == NULL)
        d = str_dup("255.255.255.255");

#ifdef _WINDOWS
    if (m_sSubnetMask.S_un.S_addr = inet_addr(d) == INADDR_NONE)
    {
        slog(LOG_ALL, 0, "SubnetMask invalid.");
        exit(0);
    }

#else
    if (inet_aton(d, &m_sSubnetMask) == 0)
    {
        slog(LOG_ALL, 0, "SubnetMask invalid.");
        exit(0);
    }
#endif

    d = parse_match_name((const char **)&c, "localhost");

    if (d == NULL)
        d = str_dup("127.0.0.1");

#ifdef _WINDOWS

    if (m_sLocalhost.S_un.S_addr = inet_addr(d) == INADDR_NONE)
        if (inet_addr(d) == INADDR_NONE)
        {
            slog(LOG_ALL, 0, "Localhost invalid.");
            exit(0);
        }

#else

    if (inet_aton(d, &m_sLocalhost) == 0)
    {
        slog(LOG_ALL, 0, "Localhost [%s] invalid.", d);
        exit(0);
    }

#endif
    char **ppNames;

    ppNames = parse_match_namelist((const char **)&c, "mplex hosts");

    if (ppNames == NULL)
    {
        slog(LOG_ALL, 0, "Mplex hosts must be specified.");
        exit(0);
    }

    int l = 0;

    while (ppNames[l])
        l++;

    if (l < 1)
    {
        slog(LOG_ALL, 0, "Mplex hosts must have at least one entry.");
        exit(0);
    }

    if (l > 10)
    {
        slog(LOG_ALL, 0, "10 is maximum number of mplex hosts.");
        exit(0);
    }

    for (i = 0; i < 10; i++)
    {
        if (i < l)
        {
#ifdef _WINDOWS
            if (m_aMplexHosts[i].S_un.S_addr = inet_addr(ppNames[i]) == INADDR_NONE)
            {
                slog(LOG_ALL, 0, "SubnetMask invalid.");
                exit(0);
            }

#else
            if (inet_aton(ppNames[i], &m_aMplexHosts[i]) == 0)
            {
                slog(LOG_ALL, 0, "Mplex host invalid IP.");
                exit(0);
            }
#endif
        }
        else
            m_aMplexHosts[i] = m_aMplexHosts[i - 1];
    }

    d = parse_match_name((const char **)&c, "promptstr");
    m_promptstr = d;

    slog(LOG_OFF, 0, "Reading info and configuration files.");

    slog(LOG_OFF, 0, "Reading in etc / colors.");
    touch_file(getFileInEtcDir(COLOR_FILE));
    m_pColor = read_info_file(getFileInEtcDir(COLOR_FILE), m_pColor);
    color.create(m_pColor);

    slog(LOG_OFF, 0, "Reading in etc / logo.");
    touch_file(getFileInEtcDir(LOGO_FILE));
    m_pLogo = read_info_file(getFileInEtcDir(LOGO_FILE), m_pLogo);
}

int CServerConfiguration::getMotherPort() const
{
    return m_nMotherPort;
}

int CServerConfiguration::getRentModifier() const
{
    return m_nRentModifier;
}

bool CServerConfiguration::isAccounting() const
{
    return m_bAccounting;
}

bool CServerConfiguration::isAliasShout() const
{
    return m_bAliasShout;
}

bool CServerConfiguration::isBBS() const
{
    return m_bBBS;
}

bool CServerConfiguration::isLawful() const
{
    return m_bLawful;
}

bool CServerConfiguration::isNoSpecials() const
{
    return m_bNoSpecials;
}

bool CServerConfiguration::isBOB() const
{
    return m_bBOB;
}

int CServerConfiguration::getShout() const
{
    return m_nShout;
}

int CServerConfiguration::getReboot() const
{
    return m_hReboot;
}

const color_type &CServerConfiguration::getColor() const
{
    return color;
}

const in_addr &CServerConfiguration::getSubnetMask() const
{
    return m_sSubnetMask;
}

const in_addr &CServerConfiguration::getLocalhost() const
{
    return m_sLocalhost;
}

const std::string &CServerConfiguration::getLibDir() const
{
    return m_libdir;
}

const std::string &CServerConfiguration::getFileInLibDir(const std::string &filename)
{
    return getOrAddFileInMap(filename, m_libdir, m_libdir_filenames);
}

const std::string &CServerConfiguration::getOrAddFileInMap(const std::string &filename, const std::string &directory, filemap_t &map)
{
    auto i = map.find(filename);
    if (i == map.end())
    {
        auto result = map.emplace(filename, directory + filename);

        if (result.second)
        {
            return result.first->second;
        }
        else
        {
            throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + ": Failed to cache path [" + directory + filename + "]");
        }
    }

    return i->second;
}

void CServerConfiguration::checkDirectoryExists(const std::string &name, const std::string &directory) const
{
    if (!(std::filesystem::exists(directory) && std::filesystem::is_directory(directory)))
    {
        slog(LOG_ALL, 0, "The %s directory %s does not exist.", name.c_str(), directory.c_str());
        exit(0);
    }
    slog(LOG_ALL, 0, "The %s directory is %s.", name.c_str(), directory.c_str());
}

const std::string &CServerConfiguration::getPlyDir() const
{
    return m_plydir;
}

const std::string &CServerConfiguration::getEtcDir() const
{
    return m_etcdir;
}

const std::string &CServerConfiguration::getFileInEtcDir(const std::string &filename) const
{
    return getOrAddFileInMap(filename, m_etcdir, m_etcdir_filenames);
}

const std::string &CServerConfiguration::getLogDir() const
{
    return m_logdir;
}

const std::string &CServerConfiguration::getFileInLogDir(const std::string &filename) const
{
    return getOrAddFileInMap(filename, m_logdir, m_logdir_filenames);
}

const std::string &CServerConfiguration::getZoneDir() const
{
    return m_zondir;
}
