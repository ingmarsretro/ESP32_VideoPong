# ESP32 PAL Pong - Vectorgameboard V1.0

Dieses Projekt ist eine klassische Pong-Umsetzung für den **ESP32**, die ein echtes **PAL-Videosignal** (Composite/FBAS) direkt über einen GPIO erzeugt. Ursprünglich als Demonstration für einen FH-Tag entwickelt, nutzt der Code das volle Potenzial des eigens dafür entwickelten **Vectorgameboards**.

## 🚀 Das Vectorgameboard V1.0
Passend zu dieser Software wurde eine dedizierte Platine entwickelt, die den ESP32 aufnimmt und alle notwendigen Komponenten "on-board" vereint:

*   **All-in-One Design:** Integrierte Potentiometer, Taster sowie Buchsen für Video- und Audio-Out.
*   **Audio-System:** Ein kleiner Lautsprecher samt Verstärker ist direkt auf dem Board verbaut.
*   **Dual-Mode Hardware:** Das Board ist sowohl für Composite-Video (PAL/NTSC) als auch für **ESP Vector Software** (X-Y-Modus für Oszilloskope) ausgelegt.
*   **Externer DAC:** Für die hochpräzise Vektordarstellung ist ein externer DAC verbaut.
*   **Open Hardware:** Details zu den Verbindungen, der Bestückung und dem Design finden sich in den **Schaltplänen** und **Eagle-Layouts** in diesem Repository.

## 📺 Software-Features
*   **PAL-Ausgabe:** Erzeugung eines Composite-Signals auf **PIN 25**.
*   **Spielmodi:** Wahl zwischen Singleplayer (gegen KI) und lokalem Multiplayer (1vs1).
*   **Steuerung:** Analoges Paddle-Feeling durch die Nutzung der On-Board Potentiometer.
*   **Grafik:** Integration von Bitmaps (Avatar/Logo) und Text via Bitluni-Library.
*   **Sound:** Akustisches Feedback bei Ballkontakt, Punktgewinn und Spielende.

## ⚠️ Wichtige Kompilier-Hinweise
Da die Video-Generierung extrem zeitkritisch ist, müssen zwingend folgende Library-Versionen verwendet werden. **Versionen der 3.x.x Schiene sind aktuell nicht kompatibel!**

| Komponente | Version |
| :--- | :--- |
| **ESP32 by Espressif Systems** | `2.0.0` |
| **Arduino ESP32 Boards** | `2.0.11` |
| **bitluni ESP32Lib** | `0.3.1` |

*Hinweis: Beim Kompilieren auftretende Warnungen können ignoriert werden.*

## 🛠 Hardware-Belegung (Pinout)
| Komponente | GPIO | Beschreibung |
| :--- | :--- | :--- |
| **Video Out** | 25 | Composite Signal |
| **Buzzer/Audio** | 27 | Soundausgabe (interner Verstärker) |
| **Poti 1** | 35 | Player 1 (Links) |
| **Poti 2** | 34 | Player 2 (Rechts) |
| **Button 1** | 32 | Modus wechseln |
| **Button 2** | 33 | Start / Aktion |

## 📜 Credits
*   **Hardware & Software:** ingmarsretro (Stand: Feb. 2026)
*   **Video Library:** Ein Dank geht an [bitluni](https://github.com) für die Bereitstellung der `ESP32Lib`.

---
*Viel Spaß beim Retrogaming auf dem Oszilloskop oder Röhrenfernseher!*


# ESP32 PAL Pong - Vectorgameboard V1.0

This project is a classic Pong implementation for the **ESP32**, generating a real **PAL composite video signal** (FBAS) directly via GPIO. originally developed as a demonstration for a university tech-day, this code utilizes the full potential of the custom-designed **Vectorgameboard**.

## 🚀 The Vectorgameboard V1.0
To support this software, a dedicated PCB was developed that houses the ESP32 and integrates all necessary components on-board:

*   **All-in-One Design:** Includes on-board potentiometers, buttons, and dedicated jacks for Video and Audio Out.
*   **Audio System:** Features a built-in small speaker and an integrated amplifier for immediate sound feedback.
*   **Dual-Mode Hardware:** The board is designed for both Composite Video (PAL/NTSC) and **ESP Vector Software** (X-Y mode for oscilloscopes).
*   **External DAC:** A dedicated external DAC is included for high-precision vector rendering on analog screens.
*   **Open Hardware:** Detailed schematics and **Eagle layouts** are available within this repository.

## 📺 Software Features
*   **PAL Output:** Generates a composite signal on **PIN 25**.
*   **Game Modes:** Toggle between Singleplayer (vs. AI) and local Multiplayer (1vs1).
*   **Precision Control:** Authentic analog paddle feeling using the on-board potentiometers.
*   **Graphics:** Integration of custom bitmaps (avatar/logo) and text overlays via the Bitluni library.
*   **Sound:** Haptic audio feedback for ball collisions, scoring, and game-over states.

## ⚠️ Critical Compilation Notes
Video generation on the ESP32 is extremely time-sensitive. To compile successfully, you **must** use the following library versions. **Versions 3.x.x are currently not compatible!**

| Component | Version |
| :--- | :--- |
| **ESP32 by Espressif Systems** | `2.0.0` |
| **Arduino ESP32 Boards** | `2.0.11` |
| **bitluni ESP32Lib** | `0.3.1` |

*Note: You can safely ignore compiler warnings during the build process.*

## 🛠 Hardware Pinout
| Component | GPIO | Description |
| :--- | :--- | :--- |
| **Video Out** | 25 | Composite Signal |
| **Buzzer/Audio** | 27 | Audio Output (Internal Amp) |
| **Pot 1** | 35 | Player 1 (Left) |
| **Pot 2** | 34 | Player 2 (Right) |
| **Button 1** | 32 | Change Mode |
| **Button 2** | 33 | Start / Action |

## 📜 Credits
*   **Hardware & Software:** ingmarsretro (Released: Feb. 2026)
*   **Video Library:** Special thanks to [bitluni](https://github.com) for the excellent `ESP32Lib`.

---
*Have fun retrogaming on your CRT TV or Oscilloscope!*
