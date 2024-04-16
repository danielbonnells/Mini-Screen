#ifndef GET_FEED_H
#define GET_FEED_H

#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char *httpGETRequest(String endpoint, String routeId, String stopId);

#endif