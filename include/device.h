#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>

class Device
{
public:
    Device(int device_number, const std::string& ipv4, const std::string& name,
            const std::string& mac, const std::string& connection_type, int linkspeed,
            int signal_strength, bool allow_or_block);
    Device(int device_number, const std::string& ipv4, const std::string& name,
            const std::string& mac, const std::string& connection_type, const std::string& ssid,
            int linkspeed, int signal_strength, bool allow_or_block,
            int device_type, float upload, float download, int qos_priority);
    Device(std::vector<std::string> attributes);
    virtual ~Device();

    int get_device_number() const { return m_device_number; }
    std::string get_ipv4() const { return m_ipv4; }
    std::string get_name() const { return m_name; }
    std::string get_mac() const { return m_mac; }
    std::string get_connection_type() const { return m_connection_type; }
    std::string get_ssid() const { return m_ssid; }
    int get_linkspeed() const { return m_linkspeed; }
    int get_signal_strength() const { return m_signal_strength; }
    bool get_allow_or_block() const { return m_allow_or_block; }
    int get_device_type() const { return m_device_type; }
    float get_upload() const { return m_upload; }
    float get_download() const { return m_download; }
    int get_qos_priority() const { return m_qos_priority; }
    bool get_name_userset() const { return m_name_userset; }
    bool get_device_type_userset() const { return m_device_type_userset; }
    bool get_schedule() const { return m_schedule; }

    friend std::ostream& operator<<(std::ostream& strm, const Device& device);
    
private:
    int m_device_number;
    std::string m_ipv4;
    std::string m_name;
    std::string m_mac;
    std::string m_connection_type;
    std::string m_ssid;
    int m_linkspeed;
    int m_signal_strength;
    bool m_allow_or_block;
    int m_device_type;
    float m_upload;
    float m_download;
    int m_qos_priority;

    bool m_name_userset;
    bool m_device_type_userset;
    bool m_schedule;
};

#endif /* DEVICE_H */
