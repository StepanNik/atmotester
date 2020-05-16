/*
   ------------ ФУНКЦИЯ ГЛАВНОГО МЕНЮ ------------
   выводит данные с датчиков, является основной страницей
   открывается при включении
*/
void mainMenu() {
  // функции оформления страницы
  drawLeafPosTwo();
  lcd.setCursor(19, 3);
  lcd.print("\x4d");

  // функции вывода значений
  EVERY_MS(100) {
    printTemp();
    printHum();
    printPres();
    printCarb();
  }
}

// вывод температуры на главном меню
void printTemp() {
  float t = dht.readTemperature();
  if (!isnan(t)) {
    lcd.setCursor(0, 0); lcd.print("T = "); lcd.setCursor(4, 0); lcd.print(t); lcd.print("\x20""\xb0""\x43");
  } else {
    lcd.setCursor(0, 0); lcd.print("Temp undef.");
    Serial.println("ERROR 12 - temperature measuring troubles");
  }
}

// вывод влажности на главном меню
void printHum() {
  float h = dht.readHumidity();
  if (!isnan(h)) {
    lcd.setCursor(0, 1); lcd.print("H = "); lcd.setCursor(4, 1); lcd.print(h); lcd.print("\x20""\x25");
  } else {
    lcd.setCursor(0, 1); lcd.print("Hum undef.");
    Serial.println("ERROR 13 - humidity measuring troubles");
  }
}

// вывод давления на главном меню
void printPres() {
  int p = int(bmp.readPressure() / 133.3224);
  if (!isnan(p)) {
    lcd.setCursor(0, 2); lcd.print("P = "); lcd.setCursor(4, 2); lcd.print(p); lcd.print("\x20""\x6d""\x6d""\x48""\x67");
  } else {
    lcd.setCursor(0, 2); lcd.print("Pres undef.");
    Serial.println("ERROR 19 - atmosphere pressure measuring troubles");
  }
}

// вывод концентрации углекислого газа на главном меню
void printCarb() {
  int c = mq135.readCO2();
  lcd.setCursor(0, 3); lcd.print("CO2 = "); lcd.setCursor(6, 3); lcd.print(c); lcd.print("\x20""\x70""\x70""\x6d""\x20");
}
