#include "HX711.h"
#include <HT1621.h>
HX711 scale;                   

HT1621 lcd;

float calibration_factor = -3.84; // калибровка датчика
float units;
float ounces;

byte i, j, a, b, c;



void setup() 
{
  
  lcd.begin(13,12,7); //инициализация дисплея

  lcd.clear();  //очистка дисплея

  pinMode(8,INPUT);

  scale.begin(A2, A1);  //инициализация тензодатчика
   Serial.begin(9600);

   scale.set_scale();
   scale.tare();  // сбрасываем датчик

}

void loop()
{

  bool butState = digitalRead(8);

  if (butState == 1)
   {
    scale.tare();
  }

  delay(1);




   scale.set_scale(calibration_factor); // применяем калибровку
   Serial.print("Reading: ");
   units = scale.get_units(), 10; // выполняем замеры 10 раз
   if (units < 0)
   {
       units = 0.00;
   }
   ounces = units * 0.035274; // переводим усредненные значения в граммы
  lcd.print(ounces);  //выводим значение на экран
   Serial.print(ounces);
   Serial.println(" грамм"); 
   Serial.print(" коэффицент калибровки: ");
   Serial.println(calibration_factor);

   if (Serial.available())
   {
       char temp = Serial.read();
       if (temp == '+' || temp == 'a') //отладка коэффицента калибровки
          calibration_factor += 0.01;
       else if (temp == '-' || temp == 'z')
          calibration_factor -= 0.01;
  }
}