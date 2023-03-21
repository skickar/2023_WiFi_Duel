# 2023_WiFi_Duel
2023 update to the Wi-Fi Duel

Shoot em up wifi game

RSA Wi-Fi Duel Game

To use this game:

1) Connect two D1 Mini boards together via i2c

2) Flash the AP sketch to one board, the Reciever sketch to the other using. You can either use Arduino for the .INO files, or https://hakcat-tech.github.io/esp-web-flasher/ for the .BIN files.

3) Connect the board flashed with the AP sketch, open a serial monitor in Arduino with baud rate 115200

4) Send the command: "ap -ssid "NetworkName" -password "NetworkPassword" -channel 11" over serial (make sure to change the NetworkName and NetworkPassword

5) Check the output, if you see "Connected" then handshakes are being generated. If you see "error", try sending again
