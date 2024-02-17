// update 2024 Feb 03 by kev
// X add fitur atur power roda (TIDAK BISA KARENA ARDUINO TIDAK BISA SAVE DATA)
// V add fitur mode kecepatan

#include <SoftwareSerial.h>
#define rxPin 2  // deklarasi pin rx ke bluetooth
#define txPin 3  // dirangkai secara menyilang ke pin bluetooth 
// rx arduino -> tx bluetooth, dan sebaliknya
SoftwareSerial bluetooth(rxPin, txPin);
#define kanan_maju 5
#define kanan_mundur 6
#define kiri_maju 10  //deklarasi pin untuk kontrol kecepatan motor
#define kiri_mundur 11

#define handling 7  // deklarasi pin untuk kontrol motor handling
#define solenoid 8     // deklarasi pin untuk kontrol solenoid

char bt; // deklarasi variabel untuk menyimpan data dari bluetooth menggunakan tipe data char

int power_kanan_maju_default = 255;
int power_kanan_mundur_default = 255;
int power_kiri_maju_default = 255;
int power_kiri_mundur_default = 255;
int mode_kecepatan = 1;

int power_kanan_maju = 0;
int power_kanan_mundur = 0;
int power_kiri_maju = 0;
int power_kiri_mundur = 0;

void setup() {
    Serial.begin(9600); // memulai komunikasi serial dengan komputer
    bluetooth.begin(9600);
    pinMode(kanan_maju, OUTPUT);
    pinMode(kanan_mundur, OUTPUT);
    pinMode(kiri_maju, OUTPUT);
    pinMode(kiri_mundur, OUTPUT);
    pinMode(handling, OUTPUT);
    pinMode(solenoid, OUTPUT);

    digitalWrite(kanan_maju, 0);
    digitalWrite(kanan_mundur, 0);
    digitalWrite(kiri_maju, 0);
    digitalWrite(kiri_mundur, 0);
    digitalWrite(handling, 1);
    digitalWrite(solenoid, 1);
}

void pinalti() {
    digitalWrite(kanan_maju, 1);
    digitalWrite(kanan_mundur, 0);
    analogWrite(kanan_maju, power_kanan_maju);

    digitalWrite(kiri_maju, 1);
    digitalWrite(kiri_mundur, 0);
    analogWrite(kiri_maju, power_kiri_maju);

    digitalWrite(handling, 0);
}

void maju() {
    digitalWrite(kanan_maju, 1);
    digitalWrite(kanan_mundur, 0);
    analogWrite(kanan_maju, power_kanan_maju);

    digitalWrite(kiri_maju, 1);
    digitalWrite(kiri_mundur, 0);
    analogWrite(kiri_maju, power_kiri_maju);
}

void mundur() {
    digitalWrite(kanan_maju, 0);
    digitalWrite(kanan_mundur, 1);
    analogWrite(kanan_mundur, power_kanan_mundur);

    digitalWrite(kiri_maju, 0);
    digitalWrite(kiri_mundur, 1);
    analogWrite(kiri_mundur, power_kiri_mundur);

    digitalWrite(handling, 0);
}

void putarkiri() {
    digitalWrite(kanan_maju, 1);
    digitalWrite(kanan_mundur, 0);
    analogWrite(kanan_maju, 255);

    digitalWrite(kiri_maju, 0);
    digitalWrite(kiri_mundur, 1);
    analogWrite(kiri_mundur, 255);

    digitalWrite(handling, 0);
}

void putarkanan() {
    digitalWrite(kanan_maju, 0);
    digitalWrite(kanan_mundur, 1);
    analogWrite(kanan_mundur, 255);

    digitalWrite(kiri_maju, 1);
    digitalWrite(kiri_mundur, 0);
    analogWrite(kiri_maju, 255);

    digitalWrite(handling, 0);
}

void serongkiri() {
    digitalWrite(kanan_maju, 1);
    digitalWrite(kanan_mundur, 0);
    analogWrite(kanan_maju, 255);

    digitalWrite(kiri_maju, 1);
    digitalWrite(kiri_mundur, 0);
    analogWrite(kiri_maju, 75);
}

void serongkanan() {
    digitalWrite(kanan_maju, 1);
    digitalWrite(kanan_mundur, 0);
    analogWrite(kanan_maju, 75);

    digitalWrite(kiri_maju, 1);
    digitalWrite(kiri_mundur, 0);
    analogWrite(kiri_maju, 255);
}

void belakangkiri() {
    digitalWrite(handling, 0);
    digitalWrite(kanan_maju, 0);
    digitalWrite(kanan_mundur, 1);
    analogWrite(kanan_mundur, 255);

    digitalWrite(kiri_maju, 0);
    digitalWrite(kiri_mundur, 1);
    analogWrite(kiri_mundur, 75);
}

void belakangkanan() {
    digitalWrite(handling, 0);
    digitalWrite(kanan_maju, 0);
    digitalWrite(kanan_mundur, 1);
    analogWrite(kanan_mundur, 75);

    digitalWrite(kiri_maju, 0);
    digitalWrite(kiri_mundur, 1);
    analogWrite(kiri_mundur, 255);
}

void diam() {
    digitalWrite(kanan_maju, 0);
    digitalWrite(kanan_mundur, 0);
    digitalWrite(kiri_maju, 0);
    digitalWrite(kiri_mundur, 0);
    digitalWrite(solenoid, 1);
    digitalWrite(handling, 1);
}

void loop() {
    // Mode Kecepatan Roda
    if (mode_kecepatan == 1) {
        // membuat nilai variabel jadi 0
        power_kanan_maju -= power_kanan_maju;
        power_kanan_mundur -= power_kiri_mundur;
        power_kiri_maju -= power_kiri_maju;
        power_kiri_mundur -= power_kiri_mundur;
        // membuat nilai variabel sesuai mode 
        power_kanan_maju += power_kanan_maju_default;
        power_kanan_mundur += power_kanan_mundur_default;
        power_kiri_maju += power_kiri_maju_default;
        power_kiri_mundur += power_kiri_mundur_default;
    } else if (mode_kecepatan == 2) {
        // membuat nilai variabel jadi 0
        power_kanan_maju -= power_kanan_maju;
        power_kanan_mundur -= power_kiri_mundur;
        power_kiri_maju -= power_kiri_maju;
        power_kiri_mundur -= power_kiri_mundur;
        // membuat nilai variabel sesuai mode 
        power_kanan_maju += power_kanan_maju_default - 55;
        power_kanan_mundur += power_kanan_mundur_default - 55;
        power_kiri_maju += power_kiri_maju_default - 55;
        power_kiri_mundur += power_kiri_mundur_default - 55;
    } else if (mode_kecepatan == 3) {
        // membuat nilai variabel jadi 0
        power_kanan_maju -= power_kanan_maju;
        power_kanan_mundur -= power_kiri_mundur;
        power_kiri_maju -= power_kiri_maju;
        power_kiri_mundur -= power_kiri_mundur;
        // membuat nilai variabel sesuai mode 
        power_kanan_maju += power_kanan_maju_default - 155;
        power_kanan_mundur += power_kanan_mundur_default - 155;
        power_kiri_maju += power_kiri_maju_default - 155;
        power_kiri_mundur += power_kiri_mundur_default - 155;
    }

    if (bluetooth.available()) {
        bt = bluetooth.read();
        Serial.print("data: ");
        Serial.println(bt);

        if (bt == '1') {
            maju();
        } else if (bt == '5') {
            mundur();
        } else if (bt == '3') {
            putarkiri();
        } else if (bt == '7') {
            putarkanan();
        } else if (bt == '2') {
            serongkiri();
        } else if (bt == '8') {
            serongkanan();
        } else if (bt == '4') {
            belakangkiri();
        } else if (bt == '6') {
            belakangkanan();
        } else if (bt == 'X') {
            digitalWrite(solenoid, 0);
        } else if (bt == 'Y') {
            digitalWrite(handling, 0);
        } else if (bt == 'A') {
            Serial.println(mode_kecepatan);
            Serial.println(power_kanan_maju);
            mode_kecepatan += 1;
            if (mode_kecepatan > 3) {
                mode_kecepatan = 1;
            }
        } else if (bt == 'C') {
          pinalti();
        }
        else {
            diam();
        }
    }
}