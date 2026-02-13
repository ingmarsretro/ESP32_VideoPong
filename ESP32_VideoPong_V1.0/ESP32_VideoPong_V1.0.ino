// ESP32 PAL Videogame for Vectorgameboard V1.0
// Softwareversion V1 beta by ingmarsretro Feb.2026
// Videolibrary from: BITLUNI thanks for the great work
// the esp-32 controller generates composite videosignal on PIN25

// this code was written for a demonstration at the fh-day
// the ESPBoard i used is ESP32 WROOM board
// in the IDE select "ESP32 Dev Module"  240MHz, PSRAM disabled,
// but i will it go on with it ... 

// important; to successfully compile the code you need library verions:
// you can ignore the warnings
// esp32 by Espressif Systems  2.0.0 (not compatible with 3.x.x)
// Arduino ESP32 Boards 2.0.11
// bitluni ESP32Lib 0.3.1

#include "esp_pm.h"
#include "CompositeGraphics.h"
#include "CompositeOutput.h"
#include "Image.h"
#include "avatar.h" 
#include "font6x8.h"
#include <soc/rtc.h>

// --- PINASSIGNMENT ---
const int BUZZER_PIN = 27; 
const int BUTTON_PIN = 32;  // Modus wechseln
const int BUTTON_PIN2 = 33; // Start / Aktion
const int POTI_PIN = 35;    // Poti Player 1 (Links)
const int POTI_PIN2 = 34;   // Poti Player 2 (Rechts)

// --- KONSTANTEN ---
const int XRES = 324;
const int YRES = 268;

enum State { START, PLAYING, WON };
State gameState = START;
bool twoPlayerMode = false;

CompositeGraphics graphics(XRES, YRES);
CompositeOutput composite(CompositeOutput::PAL, XRES * 2, YRES * 2);
Font<CompositeGraphics> font(6, 8, font6x8::pixels);
Image<CompositeGraphics> avatar0(avatar::xres, avatar::yres, avatar::pixels);

float ballX = XRES / 2, ballY = YRES / 2;
float ballDX = 2.5, ballDY = 1.8;
int ballSize = 8;
int paddleW = 6, paddleH = 40;

float paddle1Y = YRES / 2 - 20;
float paddle2Y = YRES / 2 - 20;
int score1 = 0, score2 = 0;

void esp32_tone(int freq, int duration) {
  ledcSetup(0, freq, 10);
  ledcAttachPin(BUZZER_PIN, 0);
  ledcWriteTone(0, freq);
  delay(duration);
  ledcWriteTone(0, 0);
}

void playSound(int type) {
  switch(type) {
    case 1: esp32_tone(1000, 30); break; 
    case 2: esp32_tone(150, 400); break; 
    case 3: esp32_tone(800, 200); break; 
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  
  esp_pm_lock_handle_t powerManagementLock;
  esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "compositeCorePerformanceLock", &powerManagementLock);
  esp_pm_lock_acquire(powerManagementLock);

  composite.init();
  graphics.init();
  graphics.setFont(font);
  xTaskCreatePinnedToCore(compositeCore, "compositeCoreTask", 2048, NULL, 1, NULL, 0);
}

void compositeCore(void *data) {
  while (true) {
    composite.sendFrameHalfResolution(&graphics.frame);
  }
}

void updatePhysics() {
  paddle1Y = (analogRead(POTI_PIN) / 4095.0) * (YRES - paddleH);
  if (twoPlayerMode) {
    paddle2Y = (analogRead(POTI_PIN2) / 4095.0) * (YRES - paddleH);
  } else {
    float target = ballY - (paddleH / 2);
    paddle2Y += (target - paddle2Y) * 0.15; 
  }
  ballX += ballDX;
  ballY += ballDY;
  if (ballY <= 0 || ballY >= YRES - ballSize) ballDY *= -1;
  if (ballX <= 15 + paddleW && ballX >= 15) {
    if (ballY + ballSize >= paddle1Y && ballY <= paddle1Y + paddleH) {
      ballDX = abs(ballDX) * 1.05; 
      ballX = 15 + paddleW + 1;
      playSound(1);
    }
  }
  if (ballX >= XRES - 15 - paddleW - ballSize && ballX <= XRES - 15) {
    if (ballY + ballSize >= paddle2Y && ballY <= paddle2Y + paddleH) {
      ballDX = -abs(ballDX) * 1.05;
      ballX = XRES - 15 - paddleW - ballSize - 1;
      playSound(1);
    }
  }
  if (ballX < 0) { score2++; ballX = XRES/2; ballDX = 2.5; playSound(2); }
  if (ballX > XRES) { score1++; ballX = XRES/2; ballDX = -2.5; playSound(2); }
  if (score1 >= 10 || score2 >= 10) { gameState = WON; playSound(3); }
}

void drawStartScreen() {
  graphics.begin(0);
  graphics.setCursor(XRES / 2 - 55, 60);
  graphics.print((char*)"INGMARSRETRO VIDEO-PONG");
  graphics.setCursor(XRES / 2 - 65, 120);
  if (twoPlayerMode) graphics.print((char*)"SPIEL: SPIELER VS SPIELER");
  else               graphics.print((char*)"SPIEL: SPIELER VS COMPUTER");
  graphics.setCursor(XRES / 2 - 80, 180);
  graphics.print((char*)"BUTTON 2: SPIELMODUS");
  graphics.setCursor(XRES / 2 - 80, 190);
  graphics.print((char*)"BUTTON 1: START");
  graphics.end();
  if (digitalRead(BUTTON_PIN) == LOW) { twoPlayerMode = !twoPlayerMode; delay(250); }
  if (digitalRead(BUTTON_PIN2) == LOW) { score1 = 0; score2 = 0; gameState = PLAYING; delay(200); }
}

void drawGame() {
  graphics.begin(0);
  updatePhysics();
  graphics.setCursor(XRES / 2 - 30, 10);
  graphics.print(score1); 
  graphics.print((char*)" : "); 
  graphics.print(score2);
  graphics.fillRect(15, (int)paddle1Y, paddleW, paddleH, 50);
  graphics.fillRect(XRES - 15 - paddleW, (int)paddle2Y, paddleW, paddleH, 50);
  graphics.fillRect((int)ballX, (int)ballY, ballSize, ballSize, 63);
  for(int i=0; i<YRES; i+=15) graphics.line(XRES/2, i, XRES/2, i+7, 20);
  graphics.end();
}

void drawWinScreen() {
  graphics.begin(0);
  avatar0.draw(graphics, (XRES/2)-(avatar::xres/2), 0); // Bild "avatar" darstellen
  graphics.setCursor(XRES / 2 - 40, YRES - 10);
  
  // PRINT WINNER
  if (score1 >= 10) {
    graphics.print((char*)"PLAYER 1 SIEGT!");
  } else {
    graphics.print((char*)"PLAYER 2 SIEGT!");
  }
  
  graphics.setCursor(XRES / 2 - 50, YRES - 30);
  graphics.print((char*)"START NEUSTART");
  graphics.end();

  if (digitalRead(BUTTON_PIN2) == LOW) {
    gameState = START;
    delay(200);
  }
}

void loop() {
  switch (gameState) {
    case START:   drawStartScreen(); break;
    case PLAYING: drawGame();        break;
    case WON:     drawWinScreen();   break;
  }
}

