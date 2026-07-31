# Multitool ESP Screen

Firmware multitool para placas Waveshare con pantalla IPS 1.47".  
Cada hardware vive en su carpeta y comparte la **misma arquitectura de módulos**.

## Hardware

| Carpeta | Placa | Display | Entrada |
|---|---|---|---|
| `esp32-s3/` | [ESP32-S3-LCD-1.47B](https://www.waveshare.com/wiki/ESP32-S3-LCD-1.47B) | ST7789 + TFT_eSPI | BOTÓN BOOT |
| `esp32-c6/` | [ESP32-C6-Touch-LCD-1.47](https://docs.waveshare.com/ESP32-C6-Touch-LCD-1.47) | JD9853 + Arduino_GFX | Touch (AXS5106L) |

## Primeros pasos

1. Instalar [PlatformIO](https://platformio.org/) (CLI o extensión VS Code / Cursor).
2. Copiar WiFi secrets en cada board:

```bash
cp esp32-c6/include/secrets.h.example esp32-c6/include/secrets.h
cp esp32-s3/include/secrets.h.example esp32-s3/include/secrets.h
# editar SSID / password
```

3. Build + flash:

```bash
cd esp32-c6 && pio run -t upload   # placa touch
# o
cd esp32-s3 && pio run -t upload
```

4. Monitor serial (115200): `pio device monitor`

## Herramientas (estado actual)

Navegación entre herramientas con **swipe ↑/↓** (C6) o **BOOT click corto** (S3).  
Todas corren en **background** aunque no se muestren.

| # | Herramienta | Qué hace |
|---|---|---|
| 1 | **Weather** | Clima Córdoba vía Open-Meteo (temp, humedad, viento, icono). Refresh ~10 min. |
| 2 | **Stopwatch** | Cronómetro Start / Pause / Reset. UI parcial ~30 fps. |
| 3 | **Timer** | Cuenta atrás: presets 1/3/5/8/10 min + custom. Al llegar a 0: alerta verde/rojo, overtime `+MM:SS`, luz (backlight C6 / NeoPixel S3). |

### Controles

| Board | Cambiar herramienta | Start/Pause | Reset/Cancel |
|---|---|---|---|
| ESP32-C6 Touch | Swipe ↑ / ↓ | Tap botones | Tap botones |
| ESP32-S3 | BOOT corto | BOOT largo | BOOT doble click |

## Arquitectura de módulos

```text
esp32-xxx/
├── src/
│   ├── main.cpp        # setup / loop
│   ├── app.cpp         # orquestación, tools, background ticks, redraw
│   ├── display.cpp     # LCD + backlight
│   ├── input.cpp       # touch gestures (C6) o BOOT (S3)
│   ├── wifi.cpp        # WiFi STA
│   ├── weather.cpp     # API Open-Meteo
│   ├── stopwatch.cpp   # cronómetro
│   ├── countdown.cpp   # timer + overtime / alerta
│   ├── rgb_led.cpp     # alerta luminosa
│   └── ui.cpp          # pantallas por herramienta
├── include/            # headers + secrets.h.example
├── lib/                # libs locales (C6: driver touch AXS5106L)
├── docs/               # wiki / schematic / ejemplos de referencia
├── assets/             # icons / fonts (futuro)
├── screenshoots/
└── platformio.ini
```

- **Herramienta** (`weather`, `stopwatch`, `countdown`, …): lógica + estado. Sin UI compleja.
- **UI** (`ui.cpp`): pantallas y hit-test de botones.
- **Infra** (`display`, `wifi`, `input`, `rgb_led`): compartida.
- **app**: herramienta activa, refrescos, navegación, background.

Futuro (stubs / docs): `battery`, `gps`, `imu`.

## Notas por board

### ESP32-C6 Touch
- Display: **JD9853** (no ST7789 puro). Init oficial Waveshare + Arduino_GFX.
- Touch: poll I2C continuo (como el firmware factory); swipe vertical/horizontal.
- **Sin WS2812** en el esquemático (GPIO8 = BOOT). La alerta del timer pulsa el **backlight**.
- Docs locales: `esp32-c6/docs/`. Demo oficial Waveshare puede vivir en `ESP32-C6-Touch-LCD-1.47-Demo/` (gitignored; referencia local).

### ESP32-S3
- Display: ST7789 + TFT_eSPI.
- RGB LED WS2812 en **GPIO38** (parpadea verde/rojo con la alerta del timer).

## Secrets

`include/secrets.h` **no se commitea**. Usar `secrets.h.example` como plantilla.
