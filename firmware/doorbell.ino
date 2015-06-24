#include "HttpClient/HttpClient.h"
#include "application.h"

unsigned int nextTime = 0;    // Next time to contact the server
HttpClient http;

// Test LED setup code
int relay = D0;  // This pin is connected to the relay.
int boardLED = D7; // This pin is connectd to an onboard LED

http_header_t headers[] = {
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup() {
    pinMode(relay, OUTPUT);
    pinMode(boardLED, OUTPUT);
    digitalWrite(relay, LOW);
    digitalWrite(boardLED, LOW);
}

void loop() {
    // Wait until it's time to check in with the server again
    if (nextTime > millis()) {
        return;
    }

    request.ip = {140,239,148,14};
    request.port = 80;
    request.path = "/";

    // Get request
    http.get(request, response, headers);

    if(response.body == "1"){
        digitalWrite(relay, HIGH);   // Set relay pin to high
        digitalWrite(boardLED, HIGH); // Turn on the board LED for debugging 
        delay(500);               // Delay for 500mS
        digitalWrite(relay, LOW);    // Set relay pin to low
        digitalWrite(boardLED, LOW); // Turn on the board LED
    }

    nextTime = millis() + 4000; // Reset timer to wait 4 seconds before the next server check-in
}