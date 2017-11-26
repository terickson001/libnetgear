#include "router.h"

const std::string ACTION_LOGIN = "urn:NETGEAR-ROUTER:service:ParentalControl:1#Authenticate";
const std::string ACTION_GET_ATTACHED_DEVICES = "urn:NETGEAR-ROUTER:service:DeviceInfo:1#GetAttachDevice";
const std::string ACTION_GET_ATTACHED_DEVICES2 = "urn:NETGEAR-ROUTER:service:DeviceInfo:1#GetAttachDevice2";
const std::string ACTION_GET_TRAFFIC_METER = "urn:NETGEAR-ROUTER:service:DeviceConfig:1#GetTrafficMeterStatistics";

const std::string ACTION_CONFIGURATION_STARTED = "urn:NETGEAR-ROUTER:service:DeviceConfig:1#ConfigurationStarted";
const std::string ACTION_CONFIGURATION_FINISHED = "urn:NETGEAR-ROUTER:service:DeviceConfig:1#ConfigurationFinished";
const std::string ACTION_SET_BLOCK_DEVICE = "urn:NETGEAR-ROUTER:service:DeviceConfig:1#SetBlockDeviceByMac";

const std::string REGEX_ATTACHED_DEVICES = "<NewAttachDevice>(.*)</NewAttachDevice>";

// Until we know how to generate it, give the one we captured
const std::string SESSION_ID = "A7D88AE69687E58D9A00";

const std::string SOAP_LOGIN = "<?xml version=\"1.0\" encoding=\"utf-8\" ?> \
<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"> \
<SOAP-ENV:Header> \
<SessionID xsi:type=\"xsd:string\" \
  xmlns:xsi=\"http://www.w3.org/1999/XMLSchema-instance\">%s</SessionID> \
</SOAP-ENV:Header> \
<SOAP-ENV:Body> \
<Authenticate> \
  <NewUsername>%s</NewUsername> \
  <NewPassword>%s</NewPassword> \
</Authenticate> \
</SOAP-ENV:Body> \
</SOAP-ENV:Envelope> \
";

const std::string SOAP_ATTACHED_DEVICES = "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?> \
<SOAP-ENV:Envelope xmlns:SOAPSDK1=\"http://www.w3.org/2001/XMLSchema\" \
  xmlns:SOAPSDK2=\"http://www.w3.org/2001/XMLSchema-instance\" \
  xmlns:SOAPSDK3=\"http://schemas.xmlsoap.org/soap/encoding/\" \
  xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"> \
<SOAP-ENV:Header> \
<SessionID>%s</SessionID> \
</SOAP-ENV:Header> \
<SOAP-ENV:Body> \
<M1:GetAttachDevice xmlns:M1=\"urn:NETGEAR-ROUTER:service:DeviceInfo:1\"> \
</M1:GetAttachDevice> \
</SOAP-ENV:Body> \
</SOAP-ENV:Envelope> \
";
const std::string SOAP_ATTACHED_DEVICES2 = "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?> \
<SOAP-ENV:Envelope xmlns:SOAPSDK1=\"http://www.w3.org/2001/XMLSchema\" \
  xmlns:SOAPSDK2=\"http://www.w3.org/2001/XMLSchema-instance\" \
  xmlns:SOAPSDK3=\"http://schemas.xmlsoap.org/soap/encoding/\" \
  xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"> \
<SOAP-ENV:Header> \
<SessionID>%s</SessionID> \
</SOAP-ENV:Header> \
<SOAP-ENV:Body> \
<M1:GetAttachDevice2 xmlns:M1=\"urn:NETGEAR-ROUTER:service:DeviceInfo:1\"> \
</M1:GetAttachDevice2> \
</SOAP-ENV:Body> \
</SOAP-ENV:Envelope> \
";

const std::string SOAP_TRAFFIC_METER = " \
<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?> \
<SOAP-ENV:Envelope xmlns:SOAPSDK1=\"http://www.w3.org/2001/XMLSchema\" \
  xmlns:SOAPSDK2=\"http://www.w3.org/2001/XMLSchema-instance\" \
  xmlns:SOAPSDK3=\"http://schemas.xmlsoap.org/soap/encoding/\" \
  xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"> \
<SOAP-ENV:Header> \
<SessionID>%s</SessionID> \
</SOAP-ENV:Header> \
<SOAP-ENV:Body> \
<M1:GetTrafficMeterStatistics\\ \
xmlns:M1=\"urn:NETGEAR-ROUTER:service:DeviceConfig:1\"></M1:GetTrafficMeterStatistics> \
</SOAP-ENV:Body> \
</SOAP-ENV:Envelope> \
";

const std::string SOAP_CONFIGURATION_STARTED = " \
<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?> \
<SOAP-ENV:Envelope xmlns:SOAPSDK1=\"http://www.w3.org/2001/XMLSchema\" \
  xmlns:SOAPSDK2=\"http://www.w3.org/2001/XMLSchema-instance\" \
  xmlns:SOAPSDK3=\"http://schemas.xmlsoap.org/soap/encoding/\" \
  xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"> \
<SOAP-ENV:Header> \
<SessionID>%s</SessionID> \
</SOAP-ENV:Header> \
<SOAP-ENV:Body> \
<M1:ConfigurationStarted xmlns:M1=\"urn:NETGEAR-ROUTER:service:DeviceConfig:1\"> \
<NewSessionID>%s</NewSessionID> \
</M1:ConfigurationStarted> \
</SOAP-ENV:Body> \
</SOAP-ENV:Envelope> \
";
const std::string SOAP_CONFIGURATION_FINISHED = " \
<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?> \
<SOAP-ENV:Envelope xmlns:SOAPSDK1=\"http://www.w3.org/2001/XMLSchema\" \
  xmlns:SOAPSDK2=\"http://www.w3.org/2001/XMLSchema-instance\" \
  xmlns:SOAPSDK3=\"http://schemas.xmlsoap.org/soap/encoding/\" \
  xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"> \
<SOAP-ENV:Header> \
<SessionID>%s</SessionID> \
</SOAP-ENV:Header> \
<SOAP-ENV:Body> \
<M1:ConfigurationFinished xmlns:M1=\"urn:NETGEAR-ROUTER:service:DeviceConfig:1\"> \
<NewStatus>ChangesApplied</NewStatus> \
</M1:ConfigurationFinished> \
</SOAP-ENV:Body> \
</SOAP-ENV:Envelope> \
";
const std::string SOAP_SET_BLOCK_DEVICE = " \
<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?> \
<SOAP-ENV:Envelope xmlns:SOAPSDK1=\"http://www.w3.org/2001/XMLSchema\" \
  xmlns:SOAPSDK2=\"http://www.w3.org/2001/XMLSchema-instance\" \
  xmlns:SOAPSDK3=\"http://schemas.xmlsoap.org/soap/encoding/\" \
  xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\"> \
<SOAP-ENV:Header> \
<SessionID>%s</SessionID> \
</SOAP-ENV:Header> \
<SOAP-ENV:Body> \
<M1:SetBlockDeviceByMAC xmlns:M1=\"urn:NETGEAR-ROUTER:service:DeviceConfig:1\"> \
<NewAllowOrBlock>%s</NewAllowOrBlock> \
<NewMACAddress>%s</NewMACAddress> \
</M1:SetBlockDeviceByMAC> \
</SOAP-ENV:Body> \
</SOAP-ENV:Envelope> \
";

const std::string UNKNOWN_DEVICE_DECODED = "<unknown>";
const std::string UNKNOWN_DEVICE_ENCODED = "&lt;unknown&gt;";

#include <sstream>
#include <regex>
#include <iomanip>

#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Exception.hpp>


Router::Router(const std::string& password, const std::string& user, const std::string& host, int port)
{
    m_password = password;
    m_user = user;
    m_port = port;
    m_host = host;
    m_soap_url = "http://" + host + ":" + std::to_string(port) + "/soap/server_sa/";
}

Router::~Router()
{

}

int Router::login()
{
    char* message;
    asprintf(&message, SOAP_LOGIN.c_str(), SESSION_ID.c_str(), m_user.c_str(), m_password.c_str());
    std::string response;
    int status = _make_request(ACTION_LOGIN, message, &response);
    free(message);

    m_is_logged_in = status >= 200 && status < 300;
    return status;
}

int Router::get_attached_devices(std::vector<Device>* devices)
{
    char* message;
    asprintf(&message, SOAP_ATTACHED_DEVICES.c_str(), SESSION_ID.c_str());
    std::string response;
    int status = _make_request(ACTION_GET_ATTACHED_DEVICES, message, &response);
    free(message);

    std::string::size_type n = 0;
    while ( ( n = response.find( UNKNOWN_DEVICE_ENCODED, n ) ) != std::string::npos )
    {
        response.replace(n, UNKNOWN_DEVICE_ENCODED.size(), UNKNOWN_DEVICE_DECODED);
        n += UNKNOWN_DEVICE_DECODED.size();
    }

    std::regex alldevices("<NewAttachDevice>(.*)</NewAttachDevice>");
    std::regex empty_attr(";;");

    std::smatch matches;
    if (std::regex_search(response, matches, alldevices))
        response = std::regex_replace(matches[1].str(), empty_attr, ";-1;");
    else
        std::cerr << "Error parsing response" << std::endl;

    std::replace(response.begin(), response.end(), '@', ' ');
    std::stringstream ss(response);
    std::string curr_attributes;
    ss >> curr_attributes; // Dump the first value (The number of devices)

    std::stringstream attr_stream;
    std::string curr_attribute;

    std::vector<std::string> attributes;
    while (ss >> curr_attributes)
    {
        std::replace(curr_attributes.begin(), curr_attributes.end(), ';', ' ');
        attr_stream = std::stringstream(curr_attributes);
        while (attr_stream >> curr_attribute)
            attributes.push_back(curr_attribute);

        devices->push_back(Device(attributes));
        attributes = std::vector<std::string>();
    }

    return status;
}

int Router::get_attached_devices2(std::vector<Device>* devices)
{
    char* message;
    asprintf(&message, SOAP_ATTACHED_DEVICES2.c_str(), SESSION_ID);
    std::string response;
    int status = _make_request(ACTION_GET_ATTACHED_DEVICES2, message, &response);
    free(message);


    std::regex device("<Device>([\\s\\S]*?)</Device>");
    /* ex: <IP>192.168.1.1</IP> */
    std::regex attr("<\\w+>(.*)</\\w+>");

    std::smatch device_match, attr_match;
    std::string device_string;
    std::vector<std::string> attributes;
    while (std::regex_search(response, device_match, device))
    {
        device_string = device_match[1].str();
        while(std::regex_search(device_string, attr_match, attr))
        {
            attributes.push_back(attr_match[1].str().empty() ? "-1" : attr_match[1].str());
            device_string = attr_match.suffix();
        }
        response = device_match.suffix();
        devices->push_back(Device(attributes));
        attributes = std::vector<std::string>();
    }

    return status;
}

int Router::get_traffic_meter(TrafficMeter* tm)
{
    char* message;
    asprintf(&message, SOAP_TRAFFIC_METER.c_str(), SESSION_ID);
    std::string response;
    int status = _make_request(ACTION_GET_TRAFFIC_METER, message, &response);
    free(message);

    std::regex traffic_meter("<m:GetTrafficMeterStatisticsResponse[\\s\\S]*?>([\\s\\S]*?)</m:GetTrafficMeterStatisticsResponse>");
    /* ex: <IP>192.168.1.1</IP> */
    std::regex attr("<\\w+>(.*)</\\w+>");

    std::smatch traffic_meter_match, attr_match;
    std::string traffic_meter_string;
    std::vector<std::string> attributes;
    if (std::regex_search(response, traffic_meter_match, traffic_meter))
    {
        traffic_meter_string = traffic_meter_match[1].str();
        while(std::regex_search(traffic_meter_string, attr_match, attr))
        {
            attributes.push_back(attr_match[1].str().empty() ? "N/A" : attr_match[1].str());
            traffic_meter_string = attr_match.suffix();
        }
        response = traffic_meter_match.suffix();
    } else 
    {
        std::cerr << "Error parsing response:\n" << response << std::endl;
    }

    // std::stringstream detail_stream;
    // detail_stream << std::setw(14) << " "             << std::setw(16) << "Connection Time" << std::setw(15) << "Upload/Avg."  << std::setw(15) << "Download/avg." << std::endl;
    // detail_stream << std::setw(14) << "Today: "       << std::setw(16) << attributes[0]     << std::setw(15) << attributes[1]  << std::setw(15) << attributes[2]   << std::endl;
    // detail_stream << std::setw(14) << "Yesterday: "   << std::setw(16) << attributes[3]     << std::setw(15) << attributes[4]  << std::setw(15) << attributes[5]   << std::endl;
    // detail_stream << std::setw(14) << "Week: "        << std::setw(16) << attributes[6]     << std::setw(15) << attributes[7]  << std::setw(15) << attributes[8]   << std::endl;
    // detail_stream << std::setw(14) << "Month: "       << std::setw(16) << attributes[9]     << std::setw(15) << attributes[10] << std::setw(15) << attributes[11]  << std::endl;
    // detail_stream << std::setw(14) << "Prev. Month: " << std::setw(16) << attributes[12]    << std::setw(15) << attributes[13] << std::setw(15) << attributes[14];

    // (*details) = detail_stream.str();
    (*tm) = TrafficMeter(attributes);

    return status;
}

int Router::start_config()
{
    char* message;
    asprintf(&message, SOAP_CONFIGURATION_STARTED.c_str(), SESSION_ID, SESSION_ID);
    std::string response;
    int status = _make_request(ACTION_CONFIGURATION_STARTED, message, &response);
    free(message);

    return status;
}

int Router::end_config()
{
    char* message;
    asprintf(&message, SOAP_CONFIGURATION_FINISHED.c_str(), SESSION_ID, SESSION_ID);
    std::string response;
    int status = _make_request(ACTION_CONFIGURATION_FINISHED, message, &response);
    free(message);

    return status;

}

int Router::set_block_device(const std::string& mac, bool allow)
{
    std::string allow_or_block = allow ? "Allow" : "Block";
    char* message;
    asprintf(&message, SOAP_SET_BLOCK_DEVICE.c_str(), SESSION_ID, allow_or_block, mac);
    std::string response;
    int status = _make_request(ACTION_SET_BLOCK_DEVICE, message, &response);
    free(message);

    return status;
}

int Router::_make_request(const std::string& action, const std::string& message, std::string* response)
{
    std::stringstream response_stream;
    int status;
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        request.setOpt(new curlpp::options::Url(m_soap_url));
        request.setOpt(new curlpp::options::WriteStream(&response_stream));

        std::list<std::string> header;
        header.push_back("SOAPAction: " + action);

        request.setOpt(new curlpp::options::HttpHeader(header));

        request.setOpt(new curlpp::options::PostFields(message.c_str()));
        request.setOpt(new curlpp::options::PostFieldSize(message.length()+1));

        request.perform();
        status = curlpp::infos::ResponseCode::get(request);
        *response = response_stream.str();
    }
    catch (curlpp::LogicError& e) {
        std::cout << e.what() << std::endl;
    }
    catch (curlpp::RuntimeError& e) {
        std::cout << e.what() << std::endl;
    }
    return status;

}
