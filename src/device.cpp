#include "device.h"
#include <stdexcept>
#include <iostream>

/* Not sure if these first 2 constructors are really necessary if I am only using the third */
/* Disclaimer: I am not a C programmer */
Device::Device(int device_number, const std::string& ipv4, const std::string& name,
        const std::string& mac, const std::string& connection_type, int linkspeed,
        int signal_strength, bool allow_or_block) 
{
    m_device_number = device_number;
    m_ipv4 = m_ipv4;
    m_name = name;
    m_mac = mac;
    m_connection_type = connection_type;
    m_linkspeed = linkspeed;
    m_signal_strength = signal_strength;
    m_allow_or_block = allow_or_block;
}

Device::Device(int device_number, const std::string& ipv4, const std::string& name,
        const std::string& mac, const std::string& connection_type, const std::string& ssid,
        int linkspeed, int signal_strength, bool allow_or_block, int device_type, float upload,
        float download, int qos_priority) 
{
    m_device_number = m_device_number;
    m_ipv4 = ipv4;
    m_name = name;
    m_mac = mac;
    m_connection_type = connection_type;
    m_ssid = ssid;
    m_linkspeed = linkspeed;
    m_signal_strength = signal_strength;
    m_allow_or_block = allow_or_block;
    m_device_type = device_type;
    m_upload = upload;
    m_download = download;
    m_qos_priority = qos_priority;
}

/* Is this constructor a bad idea? It seems like a bad idea... */
/* Disclaimer: I am still not a C programmer */
Device::Device(std::vector<std::string> attributes)
{
    if (attributes.size() == 5)
    {
        m_device_number = std::stoi(attributes[0]);
        m_ipv4 = attributes[1];
        m_name = attributes[2];
        m_mac = attributes[3];
        m_connection_type = "N/A";
        m_linkspeed = -1;
        m_signal_strength = -1;
        m_allow_or_block = attributes[4] == "Allow";

        m_ssid = "-1";
        m_device_type = -1;
        m_upload = -1.0;
        m_download = -1.0;
        m_qos_priority = -1;
        m_name_userset = false;
        m_device_type_userset = false;
        m_schedule = false;
    }
    else if (attributes.size() == 8)
    {
        m_device_number = std::stoi(attributes[0]);
        m_ipv4 = attributes[1];
        m_name = attributes[2];
        m_mac = attributes[3];
        m_connection_type = attributes[4];
        m_linkspeed = std::stoi(attributes[5]);
        m_signal_strength = std::stoi(attributes[6]);
        m_allow_or_block = attributes[7] == "Allow";

        m_ssid = "-1";
        m_device_type = -1;
        m_upload = -1.0;
        m_download = -1.0;
        m_qos_priority = -1;
        m_name_userset = false;
        m_device_type_userset = false;
        m_schedule = false;
    }
    else if (attributes.size() == 15)
    {
        m_device_number = -1;
        m_ipv4 = attributes[0];
        m_name = attributes[1];
        m_name_userset = attributes[2] == "true";
        m_mac = attributes[3];
        m_connection_type = attributes[4];
        m_ssid = attributes[5];
        m_linkspeed = std::stoi(attributes[6]);
        m_signal_strength = std::stoi(attributes[7]);
        m_allow_or_block = attributes[8] == "Allow";
        m_schedule = attributes[9] == "true";
        m_device_type = std::stoi(attributes[10]);
        m_device_type_userset = attributes[11] == "true";
        m_upload = std::stof(attributes[12]);
        m_download = std::stof(attributes[13]);
        m_qos_priority = std::stoi(attributes[14]);
    }
    else
    {
        std::cout << std::endl;
        for (int i = 0; i < attributes.size(); i++)
            std::cout << attributes[i] << std::endl;
        throw std::invalid_argument("Expected 5/8/15 device attributes, got " + std::to_string(attributes.size()));
    }
}

Device::~Device() 
{

}

std::ostream& operator<<(std::ostream& strm, const Device& device) {
    strm << device.m_name                 << ":"                                                                              << std::endl;
    strm << "  IP: "                    << (device.m_ipv4 != "-1" ? device.m_ipv4 : "N/A")                                    << std::endl;
    strm << "  User Set Name?: "        << (device.m_name_userset ? "True" : "False")                                         << std::endl;
    strm << "  MAC: "                   << (device.m_mac != "-1" ? device.m_mac : "N/A")                                      << std::endl;
    strm << "  Connection Type: "       << (device.m_connection_type != "-1" ? device.m_connection_type : "N/A")              << std::endl;
    strm << "  SSID: "                  << (device.m_ssid != "-1" ? device.m_ssid : "N/A")                                    << std::endl;
    strm << "  Link Speed: "            << (device.m_linkspeed >= 0 ? std::to_string(device.m_linkspeed) : "N/A")             << std::endl;
    strm << "  Signal Strength: "       << (device.m_signal_strength >= 0 ? std::to_string(device.m_signal_strength) : "N/A") << std::endl;
    strm << "  Allowed?: "              << (device.m_allow_or_block ? "True" : "False")                                       << std::endl;
    strm << "  Allowed?: "              << (device.m_schedule ? "True" : "False")                                             << std::endl;
    strm << "  Device Type: "           << (device.m_device_type >= 0 ? std::to_string(device.m_device_type) : "N/A")         << std::endl;
    strm << "  User Set Device Type?: " << (device.m_device_type_userset ? "True" : "False")                                  << std::endl;
    strm << "  Download Speed: "        << (device.m_download >= 0.0 ? std::to_string(device.m_download) : "N/A")             << std::endl;
    strm << "  Upload Speed: "          << (device.m_upload >= 0.0 ? std::to_string(device.m_upload) : "N/A")                 << std::endl;
    strm << "  QOS Priority: "          << (device.m_qos_priority >= 0 ? std::to_string(device.m_qos_priority) : "N/A");
    return strm;
}
