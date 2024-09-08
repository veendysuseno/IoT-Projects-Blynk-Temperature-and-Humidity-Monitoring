/* IoT Projects Blynk Temperature and Humidity Monitoring */

#define BLYNK_PRINT Serial
#include &lt;ESP8266WiFi.h&gt;
#include &lt;BlynkSimpleEsp8266.h&gt;
#include &lt;DHT.h&gt;

char auth[] = "XXXX";           // masukkan kode autentikasi disini
char ssid[] = "Veendy-Suseno";  //nama wifi
char pass[] = "Admin12345";     //password

#define DHTPIN 2
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor(){
    float h = dht.readHumidity();
    float t = dht.readTemperature(); 
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    Blynk.virtualWrite(V5, h);
    Blynk.virtualWrite(V6, t);
}

void setup(){
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(1000L, sendSensor);
}

void loop(){
    Blynk.run();
    timer.run();
}