# Wage_Timer

# 💖 Wage Timer

This is a cute and simple wage timer built using **SDL2**, **SDL_ttf**, and **SDL_image** in C++. It lets you track how much money you're earning in real time!


![ezgif com-video-to-gif-converter (3)](https://github.com/user-attachments/assets/79a25a24-fbef-4cf5-8d21-a3a70a6a0b10)



## 🎀 Features

- Input your hourly wage using a keyboard input window
- Displays a live timer in `HH:MM:SS` format
- Shows your earned wage in real time
- Real-world date and time shown in the corner
- Light pink aesthetic with cute hearts and stars 🌸
- Pixel font support for a retro feel (make sure `pixel.ttf` is in the same folder)

## 📦 Requirements

- SDL2
- SDL2_ttf
- SDL2_image

You can install these via [Homebrew](https://brew.sh/) on macOS:

```bash
brew install sdl2 sdl2_ttf sdl2_image
```
##🔧 Build & Run
```bash
g++ main.cpp -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_image -o wage_timer
./wage_timer
```
### 📁 Make sure your working directory contains:

- `main.cpp`
- `pixel.ttf` (or any `.ttf` font you'd like to use)

