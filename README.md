
# Kutu Hafıza Oyunu

Bu proje, basit ama eğlenceli bir **hafıza oyunu** tasarımıdır. 1 adet NeoPixel LED, 4 buton ve Arduino Nano kullanılarak yapılmıştır. Oyunda LED renkleri sırayla yanar, kullanıcı bu sıralamayı hatırlayıp doğru butonlara basmalıdır. Seviye ilerledikçe sıra uzar, hata yapılırsa can kaybedilir.

## Proje Klasör Yapısı

```
📁 kutu-hafiza-oyunu
├── 📁 donanim
│   ├── kutu_modeli.stl
│   ├── tus_kapagi.stl
│   └── devre_semasi.jpg/png
├── 📁 yazilim
│   └── hafiza-oyunu.ino
├── 📁 gorsel
│   └── calisan_hali.png
└── README.md
```

## Kullanılan Malzemeler

- Arduino Nano
- 1x NeoPixel LED
- 4x Buton
- 3D Baskı kutu ve tuş kapakları
- Breadboard ve jumper kablolar
- Opsiyonel: 220Ω direnç (NeoPixel için)

## Nasıl Çalışır?

1. LED’ler sırayla yanar (örneğin: kırmızı → mavi → sarı).
2. Oyuncu aynı sırayla butonlara basar.
3. Doğru ise seviye artar, yanlış ise can azalır.
4. Tüm canlar biterse oyun sıfırlanır.

## Özelleştirme Önerileri

Aşağıdaki satırları değiştirerek projeyi kendinize göre özelleştirebilirsiniz:

```cpp
uint8_t BRIGHTNESS = 40;         // LED parlaklığı
uint16_t stepShowMs = 260;       // LED yanma süresi
uint16_t stepGapMs = 140;        // LED'ler arası bekleme
int TONES[4] = {262, 330, 392, 523}; // Ses tonları
#define SHOW_EACH_LEVEL 0        // Her seviyede uyarı istiyorsanız 1 yapın
```

Örneğin, oyun daha hızlı ilerlesin isterseniz `stepShowMs` değerini 200 yapabilirsiniz.

## Lisans

MIT Lisansı ile yayınlanmıştır. Eğitimsel amaçlarla kullanabilirsiniz.
