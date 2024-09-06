#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <NTPClient.h>
#include <WiFiUdp.h>

extern NTPClient timeClient;

String getFormattedTime();
unsigned long getUnixTimestamp();
#endif // TIMEUTILS_H
