
# 🧠 Kutu Hafıza Oyunu

Kendi LED ve butonlardan oluşan sade ama eğlenceli bir hafıza oyunu yapmak ister misiniz? Bu projede ihtiyacınız olan her şey mevcut: Kodlar, 3D baskı dosyaları, devre şeması ve örnek video!

## 🎮 Oyun Nasıl Çalışır?

- 8 adet NeoPixel LED, 4 buton ve 1 buzzer kullanarak klasik "sıra tekrar et" mantığında bir hafıza oyunu oluşturduk.
- Her seviye giderek zorlaşır ve hata yaparsanız canınız azalır.
- Işık ve ses efektleriyle hem görsel hem işitsel olarak sizi uyarır.

## 🧩 Donanım Gereksinimleri

- 1x Arduino Nano
- 1x NeoPixel (8 LED’li tek şerit)
- 4x Buton
- 1x Buzzer
- 1x Breadboard ve bağlantı kabloları
- Direnç (opsiyonel)

## 🔧 Dosya Yapısı

```
📁 kutu-hafiza-oyunu
├── 📁 donanim
│   ├── kutu_modeli.stl
│   ├── tus_kapagi.stl
│   └── devre_semasi.jpg
├── 📁 yazilim
│   └── hafiza-oyunu.ino
├── 📁 gorsel
│   └── calisan_hali.png
└── README.md
```

## 📺 Tanıtım ve Yapım Videosu

Projeyi nasıl yaptığımı detaylıca anlattığım videoyu buradan izleyebilirsiniz:

🔗 [YouTube Videosu – Kutu Hafıza Oyunu](https://youtube.com/link-gelecek)

## 🛠️ Kendi Versiyonunu Yapmak İstersen...

Bu projeyi özelleştirmek isteyenler için bazı ipuçları:

| Özelleştirme        | Nasıl Yapılır                                      |
|---------------------|----------------------------------------------------|
| 🔊 Farklı sesler     | `TONES[]` dizisini değiştirin                      |
| 💡 Farklı renkler    | `COLORS[]` içinde RGB değerlerini ayarlayın        |
| 🔁 Level başında uyarı | `SHOW_EACH_LEVEL` değerini `1` yapın              |
| 🎨 Daha fazla LED    | `NUM_LEDS` ve `playStep()` içinde LED ayarlarını güncelleyin |
| 🎮 Buton sayısını artırmak | Kodun `BTN_PINS[]` ve `readButton()` fonksiyonları uyarlanmalı |

## 🧪 Devre Şeması

📷 Aşağıdaki görselde projenin basit devre bağlantısını görebilirsiniz:  
_(dosya: `donanim/devre_semasi.png`)_
