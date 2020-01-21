# Wifi Garage Door Controller

This project is to extend your common gate opener so that it can activate using your phone and google assistant.  It is pretty straightforward. **If you want to contribute please feel free to do so**. The complete source code is included in this repo.

**Materials:**
- 1 NodeMCU 1.0
- 1 minibreadboard
- 1 2n2222a transistor
- 1 560 Ohm resistor
- 2  male to male jump wires
- 2 male to female jump wires
- 30 cm  solid copper wire. (Cable must fit on breadboard or the soldering board. Length can vary, it is up to you)
- 1 micro usb cable and power supply adapter for nodeMCU.
- Multimeter.
- Soldering iron
- 1 soldering board (optional)
- 1 plastic case (optional)

**Steps:**

1. Build the sketch according to the schematic (sorry for the informalities, I am no electronics engineer):
![alt_text](https://github.com/hector6298/Wifi-Garage-Door-Controller/blob/master/imgs/circuit.png)

1. Blynk App.
   1. Download the Blynk app on your phone (either iOS or Android). You might as well want to download the app on all phones in your house for everyone to use the garage door controller.
   2. Create an account. If you want to use more phones simply log in on those phones with the same account once the project is finished.
   3. Create a new project.
   4. Choose NodeMCU as the hardware.
   5. Copy the Auth token sent to you by email. We will need it for the code.
   
3. On the Blynk project
   4. Tap on the canvas to open widget box and select button.
   5. Leave the slider on push and select a physical digital pin of your choice. Mine was D2.
   6. Tap on play to run the project. 
   
We will leave it at that for now on the blynk app side.

4. Arduino.

   1. Boards Manager.
      1. Install Arduino IDE and open it (https://www.arduino.cc/en/Main/Software)
      2. Click on Tools>Board>Boards Manager and type esp8266 on search bar.
      3. Download the latest version of the esp8266 package. NodeMCU Board is included in it.
      
   2. Install Blynk libraries.
      1. Click on Sketch>Include Libraries> Manage Libraries and type Blynk on search bar.
      2. Download the latest version of Blynk Libraries.
      
   3. Click on  settings>Tools>Board>NodeMCU 1.0
   4. Programming
      1. Conect your board to the pc using the usb cable.
      2. Open device manager on your PC and find the COM port of your board.
      3. On Arduino IDE go to Tools>Port and select the port where your board is connected.
      4. Click on Files>Examples>BLynk>Boards_Wifi>Esp8266_Standalone.
      5) Add the following to the code outside any function scope, or you can simply download it from this repo. After you finished, press the upload button.
      
 ```C++
const int trigger = 4;
BlynkTimer timer; 

void reconnectBlynk() {
  if (!Blynk.connected()) {

    Serial.println("Lost connection");
    if(Blynk.connect()) {
      Serial.println("Reconnected");
    }
    else {
      Serial.println("Not reconnected");
    }
  }
}

BLYNK_WRITE(V1){
  digitalWrite(trigger,HIGH);
  delay(200);
  digitalWrite(trigger,LOW);
  Blynk.virtualWrite(V1,0);
}
```
**Explanation:** reconnectBlynk() checks if our board is connected to the internet. If not, then it tries to reconnect. BLINK_WRITE() is an overriden function that sets pin D2 **HIGH** as soon as blynk virtual pin V1 is set to 1, which happens when you activate the system through Google Assistant (more on that later). Then after 200ms D2 is set to **LOW** and V1 set to 0. This whole process allows the gate opener to activate.


