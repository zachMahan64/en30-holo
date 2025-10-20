# The Galaxy Boy (galaxy-run-handheld)
### By Zach Mahan, Puqi Luo, & Ivan Outkine, created for the 5-week Brown ENGN0030 Design Module
![Final Protype](docs/images/final_prototype.png)

### Technical-Perspective Overview
   The Galaxy Boy employs an ESP32 microcontroller with an LCD1602 to run an interactive embedded videogam, *Galaxy Run*. It uses realtime polling of GPIO pins for input handling and custom bit-map sprites targetting the esp32 dev module on Arduino IDE. The body of the device is 3D printed using a model designed in Solidworks.

### Design-Perspective Overview
   The Galaxy Boy is inspired from the Nintendo Game Boy. We have designed it to be an ultra-portable, on-the-go gaming machine. It consists of a 3D printed tablet with an embedded 16x2 LCD screen and two buttons—A and B—that control the game. The game, titled Galaxy Run, can be described as an endless runner: the user controls a spaceship that must navigate past dangerous chunks of space dust and meteors, with the difficulty increasing as time goes on. Galaxy Run also keeps track of a score, the number of frames the user has survived for, to encourage longer playtimes in order to achieve a higher score. The software also has an easy-to-use reset function when the game is lost, meaning that it is easy to play over and over.

### Documentation
- [Final Presentation](docs/pdfs/Week5Presentation.pdf)
- [Final Report](/docs/pdfs/Week5Report.pdf)
- [References](/docs/references.md)
