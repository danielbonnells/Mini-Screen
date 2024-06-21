#include "getFeed.h"
#include "drawDisplay.h"
#include <string>
#include <WiFiClientSecure.h>

// Your Domain name with URL path or IP address with path
const char *serverName = "www.llenno.com";

//  the following variables are unsigned longs because the time, measured in
//  milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
// unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

// void loopCall()
// {
//     // Send an HTTP POST request every 10 minutes
//     if ((millis() - lastTime) > timerDelay)
//     {

//         String mtaData = httpGETRequest(serverName);
//         Serial.println(mtaData);
//         JSONVar myObject = JSON.parse(mtaData);

//         // JSON.typeof(jsonVar) can be used to get the type of the var
//         if (JSON.typeof(myObject) == "undefined")
//         {
//             Serial.println("Parsing input failed!");
//             return;
//         }

//         Serial.print("JSON object = ");
//         Serial.println(myObject);

//         // myObject.keys() can be used to get an array of all the keys in the object
//         JSONVar keys = myObject.keys();

//         for (int i = 0; i < keys.length(); i++)
//         {
//             JSONVar value = myObject[keys[i]];
//             Serial.print(keys[i]);
//             Serial.print(" = ");
//             Serial.println(value);
//         }

//         lastTime = millis();
//     }
// }

const char *test_root_ca = "-----BEGIN CERTIFICATE-----\n"
"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n"
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"
"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n"
"WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n"
"ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n"
"MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n"
"h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n"
"0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n"
"A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n"
"T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n"
"B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n"
"B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n"
"KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n"
"OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n"
"jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n"
"qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n"
"rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n"
"HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n"
"hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n"
"ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n"
"3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n"
"NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n"
"ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n"
"TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n"
"jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n"
"oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n"
"4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n"
"mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n"
"emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n"
"-----END CERTIFICATE-----\n";

// String httpGETRequestOld(const char *serverName)
// {

//     String c = "";
//     WiFiClientSecure client;

//     client.setCACert(test_root_ca);

//     Serial.println("\nStarting connection to server...");

//     if (!client.connect(serverName, 443))
//         Serial.println("Connection failed!");
//     else
//     {
//         Serial.println("Connected to server!");
//         // Make a HTTP request:
//         client.println("GET /api/Stop/G33S?route=G HTTP/1.0");
//         client.println("Host: llenno.com");
//         client.println("Connection: close");
//         client.println();

//         while (client.connected())
//         {
//             String line = client.readStringUntil('\n');
//             Serial.println(line);
//             //String line = client.readString();
//             //oledDrawText(line);
//             //delay(1000);
//             if (line == "\r")
//             {
//                 Serial.println("headers received");
//                 break;
//             }
//         }
//         //if there are incoming bytes available
//         //from the server, read them and print them:
//         while (client.available()) {
//           c = client.readString();

//           //oledDrawText(c);
//           //delay(1000);
//           //Serial.print(c);
//         }

//         client.stop();
//     }

   

//     return c;
// }

const char *httpGETRequest(String endpoint, String stopName, String direction)
{
    String response = "";
    WiFiClientSecure client;

    client.setCACert(test_root_ca);

    Serial.println("\nStarting connection to server...");

    if (!client.connect(serverName, 443))
    {
        Serial.println("Connection failed!");
        return ""; // Return empty string if connection fails
    }
    else
    {
        Serial.println("Connected to server!");
        // Make a HTTP request:
        //https://llenno.com/api/ESP32?stopName=Grand Central-42 St&direction=BOTH
        String uri = "/api/" + endpoint + "?stopName=" + stopName + "&direction=" + direction;
        client.println("GET " + uri + " HTTP/1.0");
        Serial.println("GET " + uri + " HTTP/1.0");
        client.println("Host: llenno.com");
        client.println("Connection: close");
        client.println();

        while (client.connected())
        {
            String line = client.readStringUntil('\n');
            Serial.println(line);
            // If empty line is encountered, it means headers are received
            if (line == "\r")
            {
                Serial.println("headers received");
                break;
            }
        }

        // Read response from server and append to the response string
        while (client.available())
        {
            response += client.readString();
        }

        client.stop();
    }

    // Convert String to const char *
    char *cstr = new char[response.length() + 1];
    strcpy(cstr, response.c_str());

    return cstr;
}

// const char *httpGETRequest(const char *serverName, String routeId, String stopId) {
//     String content = "";  // Variable to store the content of the response
//     static bool requestSent = false;  // Static variable to track if the request has been sent
//     static WiFiClientSecure client;  // Static variable to keep the client connection open between function calls

//     // Check if the request has been sent and the client is still connected
//     if (requestSent && !client.connected()) {
//         // If the request has been sent and the client is not connected anymore, return the content
//         requestSent = false;  // Reset the requestSent flag
//         return content.c_str();
//     }

//     // If the request hasn't been sent yet or the client is still connected, proceed with the request
//     if (!requestSent) {
//         // Set CA certificate
//         client.setCACert(test_root_ca);

//         // Connect to the server
//         Serial.println("\nStarting connection to server...");
//         if (!client.connect(serverName, 443)) {
//             Serial.println("Connection failed!");
//             return ""; // Return empty string if connection fails
//         }
//         Serial.println("Connected to server!");

//         // Make a HTTP request
//         String endpoint = "/api/Stop/" + stopId + "?route=" + routeId;
//         client.println("GET " + endpoint + " HTTP/1.0");
//         Serial.println("GET " + endpoint + " HTTP/1.0");
//         client.println("Host: " + String(serverName));
//         client.println("Connection: close");
//         client.println();

//         // Set requestSent flag to true
//         requestSent = true;
//     }

//     // Read response from server and append to the content string
//     while (client.available()) {
//         content += client.readStringUntil('\n');
//     }

//     // Return the content of the response
//     return content.c_str();
// }