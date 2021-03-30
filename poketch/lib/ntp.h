#ifndef _NTP_SET_
#define _NTP_DET_
#include <M5Core2.h>
#include <time.h>

const char *ntpServer = "ntp.jst.mfeed.ad.jp"; // NTP server
const long gmtOffset_sec = 9 * 3600;           // Time offset 9hr
const int daylightOffset_sec = 0;              // No summer time
RTC_DateTypeDef RTC_DateStruct;                // Data
RTC_TimeTypeDef RTC_TimeStruct;                // Time

struct tm timeinfo;

void getTimeFromNTP()
{
  // To get Time from NTP server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  while (!getLocalTime(&timeinfo))
  {
    delay(1000);
  }
}

void setNTP2RTC()
{
  // timeSet
  getTimeFromNTP();
  getLocalTime(&timeinfo);
  // read RTC
  M5.Rtc.GetTime(&RTC_TimeStruct);
  M5.Rtc.GetDate(&RTC_DateStruct);
  // --- to over write date&time
  RTC_DateStruct.Year = timeinfo.tm_year + 1900;
  RTC_DateStruct.Month = timeinfo.tm_mon + 1;
  RTC_DateStruct.Date = timeinfo.tm_mday;
  RTC_DateStruct.WeekDay = timeinfo.tm_wday;
  M5.Rtc.SetDate(&RTC_DateStruct);
  RTC_TimeStruct.Hours = timeinfo.tm_hour;
  RTC_TimeStruct.Minutes = timeinfo.tm_min;
  RTC_TimeStruct.Seconds = timeinfo.tm_sec;
  M5.Rtc.SetTime(&RTC_TimeStruct);
}
#endif