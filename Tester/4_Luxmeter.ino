/*
   ------------ ФУНКЦИЯ ЛЮКСМЕТРА ------------
   выводит уровень освещенности, в случае использования отличных
   датчиков освещённости (аналоговых!)
   есть вывод примеров эквивалентного уровня освещенности
*/

void luxmeter() {
  // функции оформления страницы
  drawLeafPosTwo();
  lcd.setCursor(19, 3);
  lcd.print("\x4c");

  lcd.setCursor(3, 0);
  lcd.print("\xce""\xd1""\xc2""\xc5""\xd9""\xc5""\xcd""\xcd""\xce""\xd1""\xd2""\xdc");
  lcd.setCursor(0, 2);
  lcd.print("\xdd""\xca""\xc2""\xc8""\xc2""\xc0""\xcb""\xc5""\xcd""\xd2""\xcd""\xce""\x3a");

  // вывод значений на экран каждые 75 секунд
  EVERY_MS(100) {
    printLight();
  }
}

// функция вывода освещённости
void printLight() {
  int ul;
  float l;
  unsigned long filter_timer;

  light.read();
  if (millis() - filter_timer > FILTER_STEP) {
    filter_timer = millis();
    ul = light.getLightLux();
    ul *= LUX_CORRECTION_COEFFICIENT;
    l = ul * FILTER_COEF + l * (1 - FILTER_COEF); // фильтр
  }
  lcd.setCursor(0, 1); lcd.print("L = "); lcd.setCursor(4, 1); lcd.print(l); lcd.print("\x20""\x6c""\x78""\x20""\x20""\x20");

  // выбор примера эквивалентной освещенности
  lcd.setCursor(1, 3);
  if (l < 4) {
    lcd.print("\xcf""\xce""\xcb""\xcd""\xc0""\xdf""\x20""\xd2""\xc5""\xcc""\xcd""\xce""\xd2""\xc0""\x20""\x20""\x20");
  } else if (l >= 4 && l < 40) {
    lcd.print("\xd2""\xc5""\xcc""\xcd""\xc0""\xdf""\x20""\xca""\xce""\xcc""\xcd""\xc0""\xd2""\xc0""\x20""\x20""\x20");
  } else if (l >= 40 && l < 90) {
    lcd.print("\xd1""\xc2""\xc5""\xd2""\xcb""\xc0""\xdf""\x20""\xca""\xce""\xcc""\xcd""\xc0""\xd2""\xc0""\x20""\x20");
  } else if (l >= 90 && l < 275) {
    lcd.print("\xcf""\xc0""\xd1""\xcc""\xd3""\xd0""\xcd""\xdb""\xc9""\x20""\xc4""\xc5""\xcd""\xdc""\x20""\x20""\x20");
  } else if (l >= 275 && l < 500) {
    lcd.print("\xca""\xcb""\xc0""\xd1""\xd1""\x20""\xc8""\xcb""\xc8""\x20""\xce""\xd4""\xc8""\xd1""\x20""\x20""\x20");
  } else if (l >= 500 && l < 1000) {
    lcd.print("\xd2""\xc2""\x20""\xd1""\xd2""\xd3""\xc4""\xc8""\xdf""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
  } else if (l >= 1000) {
    lcd.print("\xd1""\xce""\xcb""\xcd""\xc5""\xd7""\xcd""\xdb""\xc9""\x20""\xc4""\xc5""\xcd""\xdc""\x20""\x20""\x20");
  }
}

// функция, возвращающая отфильтрованнное значение освещенности
int getLight() {
  int ul;
  float l;
  unsigned long filter_timer;

  light.read();
  if (millis() - filter_timer > FILTER_STEP) {
    filter_timer = millis();
    ul = light.getLightLux();
    ul *= LUX_CORRECTION_COEFFICIENT;
    l = ul * FILTER_COEF + l * (1 - FILTER_COEF); // фильтр
  }
  return (l);
}
