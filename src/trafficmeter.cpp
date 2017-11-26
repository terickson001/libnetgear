#include "trafficmeter.h"
#include <iomanip>
#include <sstream>

TrafficMeter::TrafficMeter(std::vector<std::string> info) 
{
    m_conn_time_today      = info[0];
    m_conn_time_yesterday  = info[3];
    m_conn_time_week       = info[6];
    m_conn_time_month      = info[9];
    m_conn_time_prev_month = info[12];

    m_upload_today      = stof(info[1]);
    m_upload_yesterday  = stof(info[4]);

    std::string::size_type pos;
    pos = info[7].find('/');
    m_upload_week       = stof(info[7].substr(0, pos));
    pos = info[10].find('/');
    m_upload_month      = stof(info[10].substr(0, pos));
    pos = info[13].find('/');
    m_upload_prev_month = stof(info[13].substr(0, pos));

    pos = info[7].find('/');
    m_avg_upload_week       = stof(info[7].substr(pos+1));
    pos = info[10].find('/');
    m_avg_upload_month      = stof(info[10].substr(pos+1));
    pos = info[13].find('/');
    m_avg_upload_prev_month = stof(info[13].substr(pos+1));


    m_download_today      = stof(info[2]);
    m_download_yesterday  = stof(info[5]);

    pos = info[8].find('/');
    m_download_week       = stof(info[8].substr(0, pos));
    pos = info[11].find('/');
    m_download_month      = stof(info[11].substr(0, pos));
    pos = info[14].find('/');
    m_download_prev_month = stof(info[14].substr(0, pos));

    pos = info[8].find('/');
    m_avg_download_week       = stof(info[8].substr(pos+1));
    pos = info[11].find('/');
    m_avg_download_month      = stof(info[11].substr(pos+1));
    pos = info[14].find('/');
    m_avg_download_prev_month = stof(info[14].substr(pos+1));
}

TrafficMeter::TrafficMeter() {}

TrafficMeter::~TrafficMeter() 
{

}

std::ostream& operator<<(std::ostream& strm, const TrafficMeter& tm)
{
    std::stringstream upload_week, download_week,
                      upload_month, download_month,
                      upload_prev_month, download_prev_month;

    upload_week         << tm.m_upload_week         << "/" << tm.m_avg_upload_week;
    download_week       << tm.m_download_week       << "/" << tm.m_avg_download_week;

    upload_month        << tm.m_upload_month        << "/" << tm.m_avg_upload_month;
    download_month      << tm.m_download_month      << "/" << tm.m_avg_download_month;

    upload_prev_month   << tm.m_upload_prev_month   << "/" << tm.m_avg_upload_prev_month;
    download_prev_month << tm.m_download_prev_month << "/" << tm.m_avg_download_prev_month;

    strm << std::setw(14) << " "             << std::setw(16) << "Connection Time"         << std::setw(20) << "Upload/Avg."           << std::setw(20) << "Download/avg."         << std::endl;
    strm << std::setw(14) << "Today: "       << std::setw(16) << tm.m_conn_time_today      << std::setw(20) << tm.m_upload_today       << std::setw(20) << tm.m_download_today     << std::endl; 
    strm << std::setw(14) << "Yesterday: "   << std::setw(16) << tm.m_conn_time_yesterday  << std::setw(20) << tm.m_upload_yesterday   << std::setw(20) << tm.m_download_yesterday << std::endl;
    strm << std::setw(14) << "Week: "        << std::setw(16) << tm.m_conn_time_week       << std::setw(20) << upload_week.str()       << std::setw(20) << download_week.str()     << std::endl;
    strm << std::setw(14) << "Month: "       << std::setw(16) << tm.m_conn_time_month      << std::setw(20) << upload_month.str()      << std::setw(20) << download_month.str()    << std::endl;
    strm << std::setw(14) << "Prev. Month: " << std::setw(16) << tm.m_conn_time_prev_month << std::setw(20) << upload_prev_month.str() << std::setw(20) << download_prev_month.str();
    return strm;

}
