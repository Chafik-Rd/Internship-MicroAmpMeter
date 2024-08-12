/* 
  current = raw / calibrat
  calibrat = กระแสที่มิตเตอร์อ่านได้ / ค่า raw ที่ HX711 อ่านได้
  ค่าความคลาดเคลื่อนประมาณ  20 uA (R(sense) = 50 mA)
  *หมายเหตุ ควรต่ออุปกรณ์ลงบอร์ดก่อน calibrat เพื่อความแม่นยำและลด noise
*/

#include "HX711.h"

#define DT    23 //กำหนดขา GPIO23
#define SCK   22 //กำหนดขา GPIO22
long offsetChannelA = 0.0;   
const double calibration_factor = 1.f;

HX711 scale;

void setup() {

  Serial.begin(115200);
  Serial.println("uA meter");
  scale.begin(DT, SCK);
  scale.set_gain(128);
  offsetChannelA = scale.read_average(32);
  Serial.println(offsetChannelA);
  scale.set_offset(offsetChannelA) ;
  scale.set_scale(calibration_factor) ;

}

void loop() {
  long raw = scale.get_value(); //get_value() = read_average()-offset
  float current = raw;
 
  Serial.print("raw: ");
  Serial.print(raw);
  Serial.print("\t");
  
  //  calibratด้วยค่าเฉลี่ย   //
  Serial.print("current Av: ");
  if((current/329.283)<=1000){
  Serial.print(current/329.283, 2);  
  Serial.print("uA");
  }
  else{
  Serial.print((current/329.283/1000), 2);  
  Serial.print("mA");
  }
  Serial.print("\t");
  
  //  calibratเป็นช่วงๆ   //
  Serial.print("read current: ");
  if (raw >= 1073050) {
    Serial.print((current/343.9262821)/1000);
    Serial.println("mA");
  }  //3120 uA
  if (raw >= 635700 && raw < 1073050) {
    Serial.print((current/423.8)/1000);
    Serial.println("mA");
  }  //1500 uA
  if (raw >= 352000 && raw < 635700) {
    Serial.print((current/345.0980392)/1000);
    Serial.println("mA");
  }  //1020 uA
  if (raw >= 240480 && raw < 352000) {
    Serial.print(current/343.5428571);
    Serial.println("uA");
  }  //700 uA
  if (raw >= 170220 && raw < 240480) {
    Serial.print(current/340.44);
    Serial.println("uA");
  }  //500 uA
  if (raw >= 135540 && raw < 170220) {
    Serial.print(current/338.85);
    Serial.println("uA");
  }  //400 uA
  if (raw >= 100320 && raw < 135540) {
    Serial.print(current/334.4);
    Serial.println("uA");
  }  //300 uA
  if (raw >= 78440 && raw < 100320) {
    Serial.print(current/313.76);
    Serial.println("uA");
  }  //250 uA
  if (raw >= 64860 && raw < 78440) {
    Serial.print(current/324.3);
    Serial.println("uA");
  }  //200 uA
  if (raw >= 47160 && raw < 64860) {
    Serial.print(current/314.4);
    Serial.println("uA");
  }  //150 uA
  if (raw >= 30600 && raw < 47160) {
    Serial.print(current/306);
    Serial.println("uA");
  }  //100 uA
  if (raw >= 23195 && raw < 30600) {
    Serial.print(current/287.7791563);
    Serial.println("uA");
  }  //80.6 uA
    if (raw < 23195) {
    Serial.print(current/264.3884892);
    Serial.println("uA");
  }  //55.6 uA
}
