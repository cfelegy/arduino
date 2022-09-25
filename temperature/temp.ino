#include <LiquidCrystal.h>
#include <SimpleDHT.h>

#define DELAY 100
#define DHT_PIN 9

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SimpleDHT11 dht11(DHT_PIN);

int dhtCooldown;

void setup() {
    lcd.begin(16, 2);
    lcd.print("################");
    lcd.setCursor(0, 1);
    lcd.print("=INITIALIZING...");
    delay(200);
    dhtCooldown = 0;
}

void loop() {
    if (dhtCooldown-- == 0) {
        lcd.home();
        lcd.print("                ");
        lcd.print("### Sampling ###");
        float temp = 0, humidity = 0;
        int err = SimpleDHTErrSuccess;
        if ((err = dht11.read2(&temp, &humidity, NULL)) != SimpleDHTErrSuccess) {
            lcd.print("!! err=");
            lcd.print(SimpleDHTErrCode(err));
            lcd.setCursor(0, 1);
            lcd.print(SimpleDHTErrDuration(err));
        } else {
            temp = 32 + (temp * 9 / 5);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print(temp);
            lcd.print("*F ");
            lcd.print(humidity);
            lcd.print(" %H");
        }

        dhtCooldown = 15; // 15 * 100 = 1500ms
    }

    
    delay(DELAY);
}
