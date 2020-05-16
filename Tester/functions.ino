/*
   ------------ ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ------------
   раздел включает функции отрисовки логотипа, дебаг,
   вывод приветствий и проверка состояния датчиков
   вызываются из других функций
*/

// функция отрисовки листа как логотипа в первой позиции (слева посередине)
void drawLeafPosOne() {
  lcd.setCursor(1, 1);
  lcd.print("\2\1");
  lcd.setCursor(1, 2);
  lcd.print("\3\4");
}

// функция отрисовки листа как логотипа во второй позиции (cправа вверху)
void drawLeafPosTwo() {
  lcd.setCursor(18, 0);
  lcd.print("\2\1");
  lcd.setCursor(18, 1);
  lcd.print("\3\4");
}

// функция вывода приветственного сообщения, выводится один раз
void sayHello() {
  drawLeafPosOne();
  lcd.setCursor(6, 0);
  lcd.print("\xc0""\xcd""\xc0""\xcb""\xc8""\xc7""\xc0""\xd2""\xce""\xd0");
  lcd.setCursor(6, 1);
  lcd.print("\xc0""\xd2""\xcc""\xce""\xd1""\xd4""\xc5""\xd0""\xdb""\x20""\xc8");
  lcd.setCursor(5, 2);
  lcd.print("\xce""\xd1""\xc2""\xc5""\xd9""\xc5""\xcd""\xcd""\xce""\xd1""\xd2""\xc8");
  lcd.setCursor(9, 3);
  lcd.print("v.6.3");
  delay(2000);
}

// функция проверки состояния датчиков перед началом работы
void sensTest() {
  lcd.clear();
  drawLeafPosOne();
  lcd.setCursor(4, 0);
  lcd.print("\xcf""\xf0""\xee""\xe2""\xe5""\xf0""\xea""\xe0""\x85");
  if (isnan(dht.readTemperature()) || isnan(dht.readHumidity())) {
    lcd.setCursor(4, 1);
    lcd.print("DHT11 FAILED!");
    for (;;);
  } else {
    lcd.setCursor(4, 1);
    lcd.print("DHT11 OK.");
  }
  if (isnan(bmp.readPressure())) {
    lcd.setCursor(4, 2);
    lcd.print("BMP180 FAILED!");
    for (;;);
  } else {
    lcd.setCursor(4, 2);
    lcd.print("BMP180 OK.");
  }
  // подготовка датчика углекислого газа
  if (!mq135.isCalibrated()) {
    mq135.calibrate();
    lcd.setCursor(4, 3);
    lcd.print("System ready");
    delay(2000);
  }
}

// функция отладки
// выводит только температуру в цельсиях и давление в мм рт столба
void debug() {
  // вывод в порт в зависимости от режима отладки
  switch (DEBUG_MODE) {
    case 0: // порт
      if (isnan(dht.readTemperature()) || isnan(dht.readHumidity()) || isnan(bmp.readPressure())) {
        Serial.println("EEROR 22 - interface sensor data recieving");
        for (;;);
      } else {
        Serial.print(dht.readTemperature());  // температура
        Serial.print("*C  ");
        Serial.print(dht.readHumidity());  // влажность
        Serial.print("%  ");
        Serial.print(bmp.readPressure() / 133.3224);  // давление
        Serial.print("mmHg  ");
        Serial.print(mq135.readCO2());  // углекислый газ
        Serial.print("ppm  ");
        Serial.print(getLight());  // освещенность
        Serial.println("lx");
      }
      break;
    case 1: // плоттер
      if (isnan(dht.readTemperature()) || isnan(dht.readHumidity()) || isnan(bmp.readPressure())) {
        for (;;);
      } else {
        Serial.print(dht.readTemperature());               // температура
        Serial.print(' ');
        Serial.print(dht.readHumidity());                  // влажность
        Serial.print(' ');
        Serial.print(bmp.readPressure() / 133.3224);       // давление
        Serial.print(' ');
        Serial.println(mq135.readCO2());                   // углекислый газ
      }
      break;
    default: Serial.println("ERROR 303 - wrong debug mode"); for (;;);
      break;
  }
}
