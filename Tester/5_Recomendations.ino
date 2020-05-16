/*
   ------------ ФУНКЦИЯ АНАЛИЗА УСЛОВИЙ ------------
   выводит рекомендации по улучшению состояния помещения
*/
void conditions() {
  // функции оформления страницы
  drawLeafPosTwo();
  lcd.setCursor(19, 3);
  lcd.print("\x43");

  analyzeTemp();
  analyzeHum();
  analyzeCarb();
  analyzeLight();
}

// обработка данных термометра
void analyzeTemp() {
  lcd.setCursor(0, 0);
  if (dht.readTemperature() < MIN_TEMP) {
    // низкая температура
    lcd.print("\xcd""\xe8""\xe7""\xea""\x2e""\xd2""\xe5""\xec""\xef""\xe5""\xf0""\xe0""\xf2""\xf3""\xf0""\xe0""\x20""\x20");
  } else if (dht.readTemperature() >= MIN_TEMP && dht.readTemperature() <= MAX_TEMP) {
    // нормальная температура
    lcd.print("\xcd""\xee""\xf0""\xec""\x2e""\xd2""\xe5""\xec""\xef""\xe5""\xf0""\xe0""\xf2""\xf3""\xf0""\xe0""\x20""\x20");
  } else if (dht.readTemperature() > MAX_TEMP) {
    // высокая температура
    lcd.print("\xc2""\xfb""\xf1""\xee""\xea""\x2e""\xd2""\xe5""\xec""\xef""\xe5""\xf0""\xe0""\xf2""\xf3""\xf0""\xe0""\x20");
  }
}

// обработка данных гигрометра
void analyzeHum() {
  lcd.setCursor(0, 1);
  if (dht.readHumidity() < MIN_HUM) {
    // низкая влажность
    lcd.print("\xcd""\xe8""\xe7""\xea""\x2e""\xc2""\xeb""\xe0""\xe6""\xed""\xee""\xf1""\xf2""\xfc""\x20""\x20""\x20""\x20");
  } else if (dht.readHumidity() >= MIN_HUM && dht.readHumidity() <= MAX_HUM) {
    // нормальная влажность
    lcd.print("\xcd""\xee""\xf0""\xec""\x2e""\xc2""\xeb""\xe0""\xe6""\xed""\xee""\xf1""\xf2""\xfc""\x20""\x20""\x20""\x20");
  } else if (dht.readHumidity() > MAX_HUM) {
    // высокая влажность
    lcd.print("\xc2""\xfb""\xf1""\xee""\xea""\x2e""\xc2""\xeb""\xe0""\xe6""\xed""\xee""\xf1""\xf2""\xfc""\x20""\x20""\x20");
  }
}

// обработка данных карбоксиметра
void analyzeCarb() {
  lcd.setCursor(0, 2);
  if (mq135.readCO2() < MIN_CARB) {
    // низкая концентрация углекислого газа
    lcd.print("\xd1""\xce""\x32""\x20""\xed""\xe8""\xe6""\xe5""\x20""\xed""\xee""\xf0""\xec""\xfb""\x20""\x20""\x20""\x20""\x20");
  } else if (mq135.readCO2() >= MIN_CARB && mq135.readCO2() < MID_CARB) {
    // нормальная концентрация углекислого газа
    lcd.print("\xd1""\xce""\x32""\x20""\xe2""\x20""\xed""\xee""\xf0""\xec""\xe5""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
  } else if (mq135.readCO2() >= MID_CARB && mq135.readCO2() < MAX_CARB) {
    // незначительно превышенная концентрация углекислого газа
    lcd.print("\xd1""\xce""\x32""\x20""\xef""\xf0""\xe5""\xe2""\xfb""\xf8""\xe5""\xed""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
  } else if (mq135.readCO2() >= MAX_CARB) {
    // сильно превышенная концентрация углекислого газа
    lcd.print("\xd1""\xce""\x32""\x20""\xf1""\xe8""\xeb""\xfc""\xed""\xee""\x20""\xef""\xf0""\xe5""\xe2""\xfb""\xf8""\xe5""\xed");
  }
}

// обработка данных люксометра
void analyzeLight() {
  lcd.setCursor(0, 3);
  if (getLight() < MIN_LIGHT) {
    // низкая освещенность
    lcd.print("\xcd""\xe8""\xe7""\xea""\x2e""\xce""\xf1""\xe2""\xe5""\xf9""\xb8""\xed""\xed""\xee""\xf1""\xf2""\xfc""\x20");
  } else if (getLight() >= MIN_LIGHT) {
    // нормальная освещенность
    lcd.print("\xcd""\xee""\xf0""\xec""\x2e""\xce""\xf1""\xe2""\xe5""\xf9""\xb8""\xed""\xed""\xee""\xf1""\xf2""\xfc""\x20");
  }
}
