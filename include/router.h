#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include "device.h"
#include "trafficmeter.h"

class Router
{
public:
    Router(const std::string& password, const std::string& user = "admin", const std::string& host = "routerlogin.net", int port = 5000);
    virtual ~Router();

    int login();
    int get_attached_devices(std::vector<Device>* devices);
    int get_attached_devices2(std::vector<Device>* devices);
    int get_traffic_meter(TrafficMeter* tm);
    int start_config();
    int end_config();
    int set_block_device(const std::string& mac, bool allow);

    bool is_logged_in() { return m_is_logged_in; }

private:
    int _make_request(const std::string& action, const std::string& message, std::string* response);

    std::string m_soap_url;
    std::string m_user;
    std::string m_password;
    std::string m_host;
    int m_port;
    bool m_is_logged_in = false;

};

#endif /* ROUTER_H */
