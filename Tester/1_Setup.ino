void setup() {
  Serial.begin(9600);

  // настройка режимов работы пинов
  pinMode(BUTT_PIN, INPUT_PULLUP);

  lcd.init(); // включение экрана
  lcd.noBacklight(); // включение подсветки
  lcd.command(0b101010);  // переключение страницы знакогенератора

  // создание символов для рисования логотипа
  lcd.createChar(1, ru);
  lcd.createChar(2, lu);
  lcd.createChar(3, ld);
  lcd.createChar(4, rd);

  // инициализация интерфейсных датчиков
  dht.begin();
  bmp.begin();

  sayHello(); // вывод приветствия
  sensTest(); // вывод экрана проверки датчиков

  lcd.clear();  // очистка экрана перед началом основного цикла  работы
}
