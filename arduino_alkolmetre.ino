const int MQ3_PIN = A0;

// Durum LED'leri
const int YESIL_LED = 8;
const int SARI_LED = 9;
const int KIRMIZI_LED = 10;

// Buton ve ölçüm LED'i
const int BUTON = 2;
const int OLCUM_LED = 7;

// Süreler
const unsigned long BASLANGIC_BEKLEME = 1000; // 1 saniye
const unsigned long OLCUM_SURESI = 5000;      // 5 saniye

// Referans
int referans = 0;

// Başlangıç eşikleri
const int UYARI_ESIGI = 100;
const int YUKSEK_ESIK = 250;


// ========================================
// SETUP
// ========================================

void setup() {

  Serial.begin(9600);

  pinMode(BUTON, INPUT_PULLUP);

  pinMode(OLCUM_LED, OUTPUT);

  pinMode(YESIL_LED, OUTPUT);
  pinMode(SARI_LED, OUTPUT);
  pinMode(KIRMIZI_LED, OUTPUT);

  digitalWrite(OLCUM_LED, LOW);
  digitalWrite(YESIL_LED, LOW);
  digitalWrite(SARI_LED, LOW);
  digitalWrite(KIRMIZI_LED, LOW);

  Serial.println();
  Serial.println("================================");
  Serial.println("       NEFES ALKOL TESTI");
  Serial.println("================================");
  Serial.println();

  Serial.println("MQ-3 sensoru isitiliyor...");
  Serial.println("Lutfen bekleyin.");

  // MQ-3 başlangıç ısınması
  delay(30000);

  Serial.println();
  Serial.println("Referans degeri olculuyor.");
  Serial.println("Sensoru ufurmeyin.");

  referans = ortalamaOlc();

  Serial.print("Referans Degeri: ");
  Serial.println(referans);

  Serial.println();
  Serial.println("================================");
  Serial.println(" SISTEM HAZIR");
  Serial.println(" Test icin butona basin.");
  Serial.println("================================");
}


// ========================================
// LOOP
// ========================================

void loop() {

  if (digitalRead(BUTON) == LOW) {

    delay(50);

    if (digitalRead(BUTON) == LOW) {

      olcumBaslat();

      // Buton bırakılana kadar bekle
      while (digitalRead(BUTON) == LOW) {
        delay(10);
      }

      delay(200);
    }
  }
}


// ========================================
// ÖLÇÜM
// ========================================

void olcumBaslat() {

  Serial.println();
  Serial.println("================================");
  Serial.println("       TEST BASLATILIYOR");
  Serial.println("================================");

  Serial.println();
  Serial.println("Butona basildi.");
  Serial.println("1 saniye sonra uflemeye baslayin...");
  Serial.println();


  // ====================================
  // 1 SANİYE BEKLE
  // ====================================

  digitalWrite(OLCUM_LED, LOW);

  delay(BASLANGIC_BEKLEME);


  // ====================================
  // ÖLÇÜM BAŞLIYOR
  // ====================================

  digitalWrite(OLCUM_LED, HIGH);

  Serial.println("********************************");
  Serial.println("       SIMDI UFLEYIN!");
  Serial.println("********************************");
  Serial.println();


  unsigned long baslangic = millis();

  long toplam = 0;
  int sayac = 0;

  int maksimumDeger = 0;


  // ====================================
  // 5 SANİYE ÖLÇÜM
  // ====================================

  while (millis() - baslangic < OLCUM_SURESI) {

    int sensorDegeri = analogRead(MQ3_PIN);

    toplam += sensorDegeri;
    sayac++;

    if (sensorDegeri > maksimumDeger) {
      maksimumDeger = sensorDegeri;
    }

    Serial.print("Anlik MQ-3: ");
    Serial.println(sensorDegeri);

    delay(100);
  }


  // ====================================
  // ÖLÇÜM BİTTİ
  // ====================================

  digitalWrite(OLCUM_LED, LOW);

  Serial.println();
  Serial.println("********************************");
  Serial.println("       UFLEME BITTI");
  Serial.println("       OLCUM TAMAMLANDI");
  Serial.println("********************************");
  Serial.println();


  // Ortalama
  int ortalama = toplam / sayac;

  // Referansa göre değişim
  int fark = ortalama - referans;

  if (fark < 0) {
    fark = 0;
  }


  // Göreceli seviye
  int alkolSeviyesi = map(
    fark,
    0,
    YUKSEK_ESIK * 2,
    0,
    100
  );

  alkolSeviyesi = constrain(
    alkolSeviyesi,
    0,
    100
  );


  // ====================================
  // SONUÇ
  // ====================================

  Serial.println("================================");
  Serial.println("          TEST SONUCU");
  Serial.println("================================");

  Serial.print("Referans Degeri : ");
  Serial.println(referans);

  Serial.print("Ortalama Deger  : ");
  Serial.println(ortalama);

  Serial.print("Maksimum Deger  : ");
  Serial.println(maksimumDeger);

  Serial.print("Degisim         : ");
  Serial.println(fark);

  Serial.print("Alkol Seviyesi  : ");
  Serial.print(alkolSeviyesi);
  Serial.println(" / 100");

  Serial.println();


  // ====================================
  // DURUM LED'LERİ
  // ====================================

  if (fark < UYARI_ESIGI) {

    digitalWrite(YESIL_LED, HIGH);
    digitalWrite(SARI_LED, LOW);
    digitalWrite(KIRMIZI_LED, LOW);

    Serial.println("DURUM: NORMAL");
  }

  else if (fark < YUKSEK_ESIK) {

    digitalWrite(YESIL_LED, LOW);
    digitalWrite(SARI_LED, HIGH);
    digitalWrite(KIRMIZI_LED, LOW);

    Serial.println("DURUM: UYARI");
  }

  else {

    digitalWrite(YESIL_LED, LOW);
    digitalWrite(SARI_LED, LOW);
    digitalWrite(KIRMIZI_LED, HIGH);

    Serial.println("DURUM: YUKSEK ALKOL ALGILANDI");
  }

  Serial.println("================================");
  Serial.println();
  Serial.println("Yeni test icin butona basin.");
}


// ========================================
// ORTALAMA ÖLÇÜM
// ========================================

int ortalamaOlc() {

  long toplam = 0;

  for (int i = 0; i < 10; i++) {

    toplam += analogRead(MQ3_PIN);

    delay(100);
  }

  return toplam / 10;
}