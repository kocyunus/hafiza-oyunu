#include <Adafruit_NeoPixel.h>

/* -------------------------------------------------
   BUTON RENK → PIN
   Kırmızı = D2, Yeşil = D3, Mavi = D4, Sarı = D5
   NeoPixel DIN = D6, Buzzer = D8
   ------------------------------------------------- */
#define BTN_RED     2
#define BTN_GREEN   3
#define BTN_BLUE    4
#define BTN_YELLOW  5

#define LED_PIN     6
#define NUM_LEDS    8
#define BUZZER_PIN  8

// Eğer her level öncesinde de uyarı istiyorsan 1 yap:
#define SHOW_EACH_LEVEL 0

// Renk indeksleri
enum { RED=0, GREEN=1, BLUE=2, YELLOW=3 };

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Görsel & ses ayarları
uint8_t  BRIGHTNESS    = 40;   // Kamera için 20–50 ideal
uint16_t stepShowMs    = 260;  // Dizi oynatma hızı
uint16_t stepGapMs     = 140;
uint16_t pressFlashMs  = 160;

// Oyun dizi ayarları
const uint8_t MAX_SEQ = 64;
uint8_t seq[MAX_SEQ];
uint8_t level = 1;
int lives = 3;
bool firstRun = true; // Oyun ilk kez başlarken uyarı için

// Renkler ve tonlar
uint32_t COLORS[4];
int TONES[4] = {262, 330, 392, 523}; // C4, E4, G4, C5

// PIN dizisi (renk sırasına göre)
const uint8_t BTN_PINS[4] = { BTN_RED, BTN_GREEN, BTN_BLUE, BTN_YELLOW };

// ------------ Yardımcılar ------------
void toneBeep(int f, int d){ tone(BUZZER_PIN, f, d); delay(d); noTone(BUZZER_PIN); }
void fillColor(uint32_t c){ for(int i=0;i<NUM_LEDS;i++) strip.setPixelColor(i,c); strip.show(); }
void allOff(){ strip.clear(); strip.show(); }

// Başlangıç ışık şovu + “başla” sinyali
void preGameLightShow(){
  // Kısa bir chase (ileri-geri)
  for(int r=0; r<2; r++){
    for(int i=0; i<NUM_LEDS; i++){
      strip.clear();
      strip.setPixelColor(i, strip.Color(0, 40, 40)); // camgöbeği
      strip.show();
      delay(60);
    }
    for(int i=NUM_LEDS-2; i>=1; i--){
      strip.clear();
      strip.setPixelColor(i, strip.Color(40, 0, 40)); // eflatun
      strip.show();
      delay(60);
    }
  }

  // 1 saniye karanlık
  allOff(); 
  delay(1000);

  // “Başla” işareti: kısa beyaz flaş + bip
  fillColor(strip.Color(80,80,80));
  toneBeep(880, 180);
  allOff();
  delay(150);
}

// Başarı / Hata animasyonları
void successAnim(){
  for(int k=0;k<2;k++){
    fillColor(strip.Color(0,80,0)); toneBeep(880,120);
    allOff(); delay(60);
  }
}
void failAnim(){
  for(int i=0;i<3;i++){ fillColor(strip.Color(80,0,0)); toneBeep(196,120); allOff(); delay(80); }
}

void playStep(uint8_t colorIdx){
  fillColor(COLORS[colorIdx]);
  toneBeep(TONES[colorIdx], stepShowMs-20);
  allOff(); delay(stepGapMs);
}

void playSequence(uint8_t upto){
  // Her level öncesi uyarı istersen:
  #if SHOW_EACH_LEVEL
    allOff(); delay(1000);
    fillColor(strip.Color(60,60,60));
    toneBeep(880,150);
    allOff(); delay(120);
  #endif
  for(uint8_t i=0;i<upto;i++) playStep(seq[i]);
}

int readButton(){ // 0..3 veya -1
  for(int i=0;i<4;i++){
    if(digitalRead(BTN_PINS[i])==LOW){
      // Basılı anı göster (INPUT_PULLUP → LOW = basılı)
      fillColor(COLORS[i]); toneBeep(TONES[i], pressFlashMs);
      while(digitalRead(BTN_PINS[i])==LOW) delay(1); // bırakma bekle
      allOff(); delay(80);
      return i;
    }
  }
  return -1;
}

void newStep(){ seq[level-1] = random(0,4); }

void resetGame(){
  level = 1; lives = 3;
  randomSeed(analogRead(A0));
  newStep();
  firstRun = true; // Bir dahaki başlangıçta uyarıyı tekrar oynat
}

void setup(){
  for(int i=0;i<4;i++) pinMode(BTN_PINS[i], INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  // Renkleri (buton renkleriyle uyumlu)
  COLORS[RED]    = strip.Color(80, 0, 0);   // Kırmızı
  COLORS[GREEN]  = strip.Color(0, 80, 0);   // Yeşil
  COLORS[BLUE]   = strip.Color(0, 0, 80);   // Mavi
  COLORS[YELLOW] = strip.Color(80, 50, 0);  // Sarımsı

  // Oyun başlamadan önce ışık şovu + başlangıç sinyali
  preGameLightShow();

  resetGame();
}

void loop(){
  // İlk kez oyuna girerken bir daha uyarı istiyorsan (setup içindeki yeterli ise gerek yok)
  if(firstRun){
    // (İstersen buraya sadece kısa bip+flash da koyabilirsin)
    firstRun = false;
  }

  // Dizi oynat
  playSequence(level);

  // Kullanıcıdan aynı sırayı bekle
  for(uint8_t i=0;i<level; i++){
    int b = -1;
    while((b = readButton())==-1) { /* bekle */ }
    if(b != seq[i]){
      lives--;
      failAnim();
      if(lives<=0){ resetGame(); delay(400); return; }
      // Aynı level tekrar
      delay(250);
      return;
    }
  }

  // Level başarı
  successAnim();
  level++;
  if(level>MAX_SEQ) level = MAX_SEQ;
  newStep();
  delay(300);
}
