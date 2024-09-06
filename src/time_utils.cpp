#include <NTPClient.h>
#include "time_utils.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0 ,60000);

String getFormattedTime() {
  timeClient.setTimeOffset(7*3600);
  timeClient.update();
  time_t rawTime = timeClient.getEpochTime();
  struct tm * timeInfo;
  timeInfo = localtime(&rawTime);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
  return String(buffer);
}

unsigned long getUnixTimestamp() {
  timeClient.setTimeOffset(0);  
  timeClient.update();
  return timeClient.getEpochTime();
}
