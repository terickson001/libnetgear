#ifndef TRAFFICMETER_H
#define TRAFFICMETER_H

#include <string>
#include <vector>

class TrafficMeter
{
public:
    TrafficMeter(std::vector<std::string> info);
    TrafficMeter();
    virtual ~TrafficMeter();

    std::string get_conn_time_today() const { return m_conn_time_today; }
    float get_upload_today() const { return m_upload_today; }
    float get_download_today() const { return m_download_today; }

    std::string get_conn_time_yesterday() const { return m_conn_time_yesterday; }
    float get_upload_yesterday() const { return m_upload_yesterday; }
    float get_download_yesterday() const { return m_download_yesterday; }

    std::string get_conn_time_week() const { return m_conn_time_week; }
    float get_upload_week() const { return m_upload_week; }
    float get_avg_upload_week() const { return m_avg_upload_week; }
    float get_download_week() const { return m_download_week; }
    float get_avg_download_week() const { return m_avg_download_week; }

    std::string get_conn_time_month() const { return m_conn_time_month; }
    float get_upload_month() const { return m_upload_month; }
    float get_avg_upload_month() const { return m_avg_upload_month; }
    float get_download_month() const { return m_download_month; }
    float get_avg_download_month() const { return m_avg_download_month; }

    std::string get_conn_time_prev_month() const { return m_conn_time_prev_month; }
    float get_upload_prev_month() const { return m_upload_prev_month; }
    float get_avg_upload_prev_month() const { return m_avg_upload_prev_month; }
    float get_download_prev_month() const { return m_download_prev_month; }
    float get_avg_download_prev_month() const { return m_avg_download_prev_month; }

    friend std::ostream& operator<<(std::ostream& strm, const TrafficMeter& tm);

private:
    std::string m_conn_time_today;
    float m_upload_today;
    float m_download_today;

    std::string m_conn_time_yesterday;
    float m_upload_yesterday;
    float m_download_yesterday;

    std::string m_conn_time_week;
    float m_upload_week;
    float m_avg_upload_week;
    float m_download_week;
    float m_avg_download_week;

    std::string m_conn_time_month;
    float m_upload_month;
    float m_avg_upload_month;
    float m_download_month;
    float m_avg_download_month;

    std::string m_conn_time_prev_month;
    float m_upload_prev_month;
    float m_avg_upload_prev_month;
    float m_download_prev_month;
    float m_avg_download_prev_month;
};

#endif /* TRAFFICMETER_H */
