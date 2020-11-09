// ÄNDRA FÖLJANDE UPPGIFTER TILL DET SOM DU VILL ANVÄNDA

#define DEVICE_ID "W.O.O.B.S"
#define TEMPERATURE_ALERT 25
#define SIMULATED_DATA false
#define INTERVAL 10000


static char *ssid = "AndroidAP";
static char *pass = "52105210";

// Pin layout configuration

#define WATERSENSOR 2 


// EEPROM address configuration
#define EEPROM_SIZE 512

// SSID and SSID password's length should < 32 bytes
// http://serverfault.com/a/45509
#define SSID_LEN 32
#define PASS_LEN 32
#define CONNECTION_STRING_LEN 256

#define MESSAGE_MAX_LEN 256
