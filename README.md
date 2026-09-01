# 🍺 Arduino MQ-3 Breathalyzer

**Arduino Uno ve MQ-3 sensörü kullanılarak geliştirilmiş, nefeste etanol varlığını algılayan DIY alkolmetre projesi.**

Bu proje, buton kontrollü bir ölçüm sistemi kullanır. Butona basıldıktan 1 saniye sonra ölçüm LED'i yanar ve kullanıcıdan sensöre üflemesi beklenir. Sistem belirlenen süre boyunca MQ-3 sensöründen veri toplar ve sonucu LED'ler ile gösterir.

> ⚠️ **Uyarı:** Bu proje eğitim ve hobi amaçlıdır. MQ-3 sensörü profesyonel bir alkolmetre değildir ve ölçülen değerler gerçek BAC (Blood Alcohol Concentration), promil veya kan alkol oranı olarak değerlendirilmemelidir. Proje sürüş veya güvenlik kararı vermek için kullanılmamalıdır.

---

## 🇹🇷 Türkçe

### 📌 Proje Hakkında

Arduino Uno ile MQ-3 gaz sensörünü birleştirerek basit bir **nefes alkol algılama sistemi** oluşturulmuştur.

Sistem:

1. Kullanıcı butona basar.
2. Sistem 1 saniye bekler.
3. Ölçüm LED'i yanar.
4. Kullanıcı sensöre üfler.
5. MQ-3 yaklaşık 5 saniye boyunca ölçüm yapar.
6. Ölçüm LED'i söner.
7. Ölçüm sonucu hesaplanır.
8. Sonuç yeşil, sarı veya kırmızı LED ile gösterilir.
9. Arduino seri bağlantı üzerinden ölçüm verilerini bilgisayara gönderebilir.

### ⚙️ Kullanılan Malzemeler

* Arduino Uno
* MQ-3 Alkol / Etanol Sensörü
* Breadboard
* Push Button
* Yeşil LED
* Sarı LED
* Kırmızı LED
* Ölçüm LED'i
* 220–330 Ω dirençler
* Jumper kablolar
* USB veya uygun harici güç kaynağı

### 🔌 Pin Bağlantıları

| Bileşen     | Arduino Uno |
| ----------- | ----------- |
| MQ-3 VCC    | 5V          |
| MQ-3 GND    | GND         |
| MQ-3 AO     | A0          |
| Buton       | D2          |
| Ölçüm LED'i | D7          |
| Yeşil LED   | D8          |
| Sarı LED    | D9          |
| Kırmızı LED | D10         |

Her normal LED için seri olarak **220–330 Ω direnç** kullanılmalıdır.

### 🧠 Çalışma Mantığı

```text
                BUTON
                  │
                  ▼
             1 saniye bekle
                  │
                  ▼
           🔵 Ölçüm LED'i
                YANAR
                  │
                  ▼
             👤 ÜFLEME
                  │
                  ▼
                MQ-3
                  │
                  ▼
             Arduino A0
                  │
                  ▼
           Ortalama hesapla
                  │
                  ▼
        Referans ile karşılaştır
                  │
          ┌───────┼───────┐
          ▼       ▼       ▼
         🟢      🟡      🔴
       Normal    Uyarı   Yüksek
```

### 💡 LED Durumları

| LED                   | Durum                          |
| --------------------- | ------------------------------ |
| 🔵 Mavi / Ölçüm LED'i | Ölçüm devam ediyor             |
| 🟢 Yeşil              | Normal / düşük göreceli seviye |
| 🟡 Sarı               | Uyarı seviyesi                 |
| 🔴 Kırmızı            | Yüksek etanol algılama         |

### 🖥️ Seri Monitör

Arduino USB üzerinden bilgisayara bağlandığında ölçüm verileri **9600 baud** ile Serial Monitor üzerinden takip edilebilir.

Örnek:

```text
================================
       NEFES ALKOL TESTI
================================

Referans Degeri : 185

Sistem hazir!
Test icin butona basin.

Butona basildi.
1 saniye sonra uflemeye baslayin...

********************************
       SIMDI UFLEYIN!
********************************

Anlik MQ-3: 215
Anlik MQ-3: 248
Anlik MQ-3: 291
Anlik MQ-3: 327

********************************
       UFLEME BITTI
       OLCUM TAMAMLANDI
********************************

================================
          TEST SONUCU
================================

Referans Degeri : 185
Ortalama Deger  : 270
Maksimum Deger  : 327
Degisim         : 85

Alkol Seviyesi  : 17 / 100

DURUM: NORMAL
```

### 📊 Ölçüm Değeri Hakkında

MQ-3, Arduino'nun analog girişinde yaklaşık **0–1023** arasında ham bir değer üretir.

Projede sensörün üfleme öncesindeki değeri **referans değer** olarak alınır ve üfleme sırasında oluşan değişim hesaplanır.

Gösterilen:

```text
Alkol Seviyesi: 0–100
```

değeri **gerçek alkol yüzdesi değildir**.

Bu değer yalnızca projenin eğitim amaçlı **göreceli etanol algılama seviyesidir**.

### 🔧 Kalibrasyon

MQ-3 sensörlerinin değerleri ortam koşullarına ve sensörün durumuna göre değişebilir.

Bu nedenle aşağıdaki eşikler başlangıç değerleridir:

```cpp
const int UYARI_ESIGI = 100;
const int YUKSEK_ESIK = 250;
```

Gerçek sensör değerleri gözlemlendikten sonra bu eşikler projeye göre yeniden ayarlanabilir.

### 🚀 Gelecekte Eklenebilecek Özellikler

* [ ] OLED ekran
* [ ] LCD ekran
* [ ] Daha gelişmiş MQ-3 kalibrasyonu
* [ ] Ölçüm geçmişi
* [ ] SD kart ile veri kaydı
* [ ] Bluetooth bağlantısı
* [ ] Mobil uygulama
* [ ] 3D baskı cihaz kasası
* [ ] Daha kontrollü hava kanalı / ağızlık
* [ ] Ölçüm grafikleri
* [ ] Buzzer ile sesli uyarı

### 📁 Proje Yapısı

```text
arduino-mq3-breathalyzer/
│
├── breathalyzer/
│   └── breathalyzer.ino
│
├── README.md
└── LICENSE
```

### ⚠️ Güvenlik ve Sorumluluk

Bu proje **eğitim, elektronik ve Arduino geliştirme amacıyla hazırlanmıştır**.

MQ-3 sensörünün çıktısı:

* Gerçek BAC değeri değildir.
* Promil ölçümü değildir.
* Tıbbi ölçüm değildir.
* Profesyonel alkolmetre yerine geçmez.
* Araç kullanma kararı vermek için kullanılmamalıdır.

Gerçek ve güvenilir BAC ölçümü için profesyonel olarak kalibre edilmiş cihazlar kullanılmalıdır.

---

# 🇬🇧 English

## 📌 About the Project

This project is a DIY **breath ethanol detection system** built with an Arduino Uno and an MQ-3 alcohol sensor.

The system uses a push button to start a measurement cycle. One second after pressing the button, the measurement LED turns on and the user blows toward the MQ-3 sensor. The Arduino collects sensor readings for approximately five seconds, processes the measurements, and indicates the relative detection level using three LEDs.

### 🔄 Measurement Process

1. Press the measurement button.
2. Wait for 1 second.
3. The measurement LED turns on.
4. Blow toward the MQ-3 sensor.
5. The sensor is sampled for approximately 5 seconds.
6. The measurement LED turns off.
7. The Arduino processes the readings.
8. A relative detection level is calculated.
9. Green, yellow, or red LED indicates the result.

### ⚙️ Components

* Arduino Uno
* MQ-3 Alcohol / Ethanol Sensor
* Breadboard
* Push Button
* Green LED
* Yellow LED
* Red LED
* Measurement LED
* 220–330 Ω resistors
* Jumper wires
* USB or suitable external power supply

### 🔌 Pinout

| Component       | Arduino Uno |
| --------------- | ----------- |
| MQ-3 VCC        | 5V          |
| MQ-3 GND        | GND         |
| MQ-3 AO         | A0          |
| Push Button     | D2          |
| Measurement LED | D7          |
| Green LED       | D8          |
| Yellow LED      | D9          |
| Red LED         | D10         |

Use a **220–330 Ω resistor in series with each standard LED**.

### 🧠 How It Works

```text
              PUSH BUTTON
                   │
                   ▼
              Wait 1 second
                   │
                   ▼
          🔵 Measurement LED
                 ON
                   │
                   ▼
               BLOW
                   │
                   ▼
                 MQ-3
                   │
                   ▼
              Arduino A0
                   │
                   ▼
            Process readings
                   │
                   ▼
          ┌────────┼────────┐
          ▼        ▼        ▼
         🟢       🟡       🔴
       Normal   Warning    High
```

### 🖥️ Serial Monitor

The Arduino can send measurement data to a computer through USB.

Serial communication:

```text
9600 baud
```

Example:

```text
Raw MQ-3 value: 327
Baseline: 185
Difference: 142

Relative level: 28 / 100

Status: WARNING
```

### 📊 About the Measurement

The MQ-3 provides an analog sensor reading rather than a direct BAC measurement.

The Arduino reads an approximate **0–1023 raw analog value** and compares the breath measurement against a baseline recorded before the test.

The displayed:

```text
Relative level: 0–100
```

is **not a real alcohol percentage or BAC value**.

It represents a relative ethanol detection level intended for demonstration and educational purposes.

### 🔧 Calibration

MQ-3 readings can vary depending on:

* Sensor warm-up time
* Temperature
* Humidity
* Airflow
* Sensor age
* Distance from the sensor
* Breath intensity

Therefore, the following values are only starting thresholds:

```cpp
const int UYARI_ESIGI = 100;
const int YUKSEK_ESIK = 250;
```

These values should be adjusted based on the behavior of the individual sensor.

### 🚀 Future Improvements

* [ ] OLED display
* [ ] LCD display
* [ ] Improved MQ-3 calibration
* [ ] Measurement history
* [ ] SD card data logging
* [ ] Bluetooth connectivity
* [ ] Mobile application
* [ ] 3D-printed enclosure
* [ ] Controlled airflow / mouthpiece
* [ ] Measurement graphs
* [ ] Buzzer alerts

### 📁 Project Structure

```text
arduino-mq3-breathalyzer/
│
├── breathalyzer/
│   └── breathalyzer.ino
│
├── README.md
└── LICENSE
```

### ⚠️ Disclaimer

This project is intended **for educational and hobby purposes only**.

The MQ-3 sensor output:

* Is not a medical measurement.
* Is not a reliable BAC measurement.
* Is not a professional breathalyzer reading.
* Must not be used to determine whether someone is safe to drive.
* Must not be used for legal, medical, or safety-critical decisions.

For reliable BAC measurement, use a professionally calibrated breathalyzer designed for that purpose.

---

## 📜 License

This project is provided for educational and personal development purposes. You may modify and improve the project according to the terms of the license included in the repository.
