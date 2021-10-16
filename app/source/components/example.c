#include <SPI.h>
#include "BluetoothSerial.h"

#define BUFFER_MAX 2000

const int pin_DRDYB = D2;  // data ready
const int pin_SS    = D10; // CSB
boolean SerialBT_Connection = false;
int32_t ECGBuffer[BUFFER_MAX];
uint16_t bufferPointer = 0;

BluetoothSerial SerialBT;

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    digitalWrite(LED_BUILTIN, HIGH);
    SerialBT_Connection = true;
  }

  if (event == ESP_SPP_CLOSE_EVT ) {
    digitalWrite(LED_BUILTIN, LOW);
    SerialBT_Connection = false;
    ESP.restart();
  }
}

void setup() {
  pinMode(pin_DRDYB, INPUT);
  pinMode(pin_SS,   OUTPUT);
  Serial.begin(9600); // (less than 115200 will decimate the signal -> de facto LPF)
  SerialBT.begin("ADS1293 ECG Monitor");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("The device started, now you can pair it with bluetooth!");
  SerialBT.println("The device started");
  SerialBT.register_callback(callback);
  SPI.begin();
  setup_ECG();
}

int32_t ecgVal;

void loop() { 
  if (digitalRead(pin_DRDYB) == false) {
    byte x1 = readRegister(0x37);//37
    byte x2 = readRegister(0x38);//38
    byte x3 = readRegister(0x39);//39

    // 3 8-bit registers combination on a 24 bit number
    ecgVal = x1;
    ecgVal = (ecgVal << 8) | x2;
    ecgVal = (ecgVal << 8) | x3;

    //Serial.println(ecgVal);
    ECGBuffer[bufferPointer] = ecgVal;
    bufferPointer++;
  }
  if (bufferPointer == BUFFER_MAX) {
    if (SerialBT_Connection) {
      SerialBT.write((const uint8_t *)ECGBuffer, sizeof(ECGBuffer));
    }
    bufferPointer = 0;
  }
}

void setup_ECG() { // datasheet ads1293
  //  //Follow the next steps to configure the device for this example, starting from default registers values.
  //  //1. Set address 0x01 = 0x11: Connect channel 1â€™️s INP to IN2 and INN to IN1.
  //  writeRegister(0x01, 0x11);
  //  //2. Set address 0x02 = 0x19: Connect channel 2â€™️s INP to IN3 and INN to IN1.
  //  writeRegister(0x02, 0x19);
  //  //3. Set address 0x0A = 0x07: Enable the common-mode detector on input pins IN1, IN2 and IN3.
  //  writeRegister(0x0A, 0x07);
  //  //4. Set address 0x0C = 0x04: Connect the output of the RLD amplifier internally to pin IN4.
  //  writeRegister(0x0C, 0x04);
  //  //5. Set address 0x12 = 0x04: Use external crystal and feed the internal oscillator's output to the digital.
  //  writeRegister(0x12, 0x04);
  //  //6. Set address 0x14 = 0x24: Shuts down unused channel 3â€™️s signal path.
  //  writeRegister(0x14, 0x24);
  //  //7. Set address 0x21 = 0x02: Configures the R2 decimation rate as 5 for all channels.
  //  writeRegister(0x21, 0x02);
  //  //8. Set address 0x22 = 0x02: Configures the R3 decimation rate as 6 for channel 1.
  //  writeRegister(0x22, 0x02);
  //  //9. Set address 0x23 = 0x02: Configures the R3 decimation rate as 6 for channel 2.
  //  writeRegister(0x23, 0x02);
  //  //10. Set address 0x27 = 0x08: Configures the DRDYB source to channel 1 ECG (or fastest channel).
  //  writeRegister(0x27, 0x08);
  //  //11. Set address 0x2F = 0x30: Enables channel 1 ECG and channel 2 ECG for loop read-back mode.
  //  writeRegister(0x2F, 0x30);
  //  //12. Set address 0x00 = 0x01: Starts data conversion.
  //  writeRegister(0x00, 0x01);

  //1. Set address 0x01 = 0x11: Connect channel 1â€™️s INP to IN2 and INN to IN1.
  writeRegister(0x01, 0x11);
  //2. Set address 0x02 = 0x19: Connect channel 2â€™️s INP to IN3 and INN to IN1.
  writeRegister(0x02, 0x19);
  //3. Set address 0x0A = 0x07: Enable the common-mode detector on input pins IN1, IN2 and IN3.
  writeRegister(0x0A, 0x07);
  //4. Set address 0x0C = 0x04: Connect the output of the RLD amplifier internally to pin IN4.
  writeRegister(0x0C, 0x04);
  //5. Set address 0x12 = 0x04: Use external crystal and feed the internal oscillator's output to the digital.
  writeRegister(0x12, 0x04);
  //5A. Set address 0x13 = 0x38: Use 204.8khz clock frequency for all 3 channels
  writeRegister(0x13, 0x38);
  //6. Set address 0x14 = 0x24: Shuts down unused channel 3â€™️s signal path.
  writeRegister(0x14, 0x24);
  //7. Set address 0x21 = 0x01: Configures the R2 decimation rate as 4 for all channels.
  writeRegister(0x21, 0x01);
  //8. Set address 0x22 = 0x01: Configures the R3 decimation rate as 4 for channel 1.
  writeRegister(0x22, 0x01);
  //9. Set address 0x23 = 0x01: Configures the R3 decimation rate as 4 for channel 2.
  writeRegister(0x23, 0x01);
  //9A. Set address 0x25 = 0x07: Configures the R1 decimation rate as 2 for all channels.
  //writeRegister(0x25, 0x07);
  //10. Set address 0x27 = 0x08: Configures the DRDYB source to channel 1 ECG (or fastest channel).
  writeRegister(0x27, 0x08);
  //10. Set address 0x27 = 0x01: Reconfigures the DRDYB source to channel 1 PACE .
  //writeRegister(0x27, 0x01);
  //11. Set address 0x2F = 0x30: Enables channel 1 ECG and channel 2 ECG for loop read-back mode.
  writeRegister(0x2F, 0x30);
  //11. Set address 0x2F = 0x32: Enables channel 1 PACE, channel 1 ECG, and channel 2 ECG for loop read-back mode
  //writeRegister(0x2F, 0x32);
  //12. Set address 0x00 = 0x01: Starts data conversion.
  writeRegister(0x00, 0x01);
}

byte readRegister(byte reg) {
  byte data;
  reg |= 1 << 7;
  digitalWrite(pin_SS, LOW);
  SPI.transfer(reg);
  data = SPI.transfer(0);
  digitalWrite(pin_SS, HIGH);
  return data;
}

void writeRegister(byte reg, byte data) {
  reg &= ~(1 << 7);
  digitalWrite(pin_SS, LOW);
  SPI.transfer(reg);
  SPI.transfer(data);
  digitalWrite(pin_SS, HIGH);
}