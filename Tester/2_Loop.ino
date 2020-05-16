void loop() {
  // здесь считываются данные с кнопки, флажок позволяет избежать дребезга
  // страницы зациклены
  if (!digitalRead(BUTT_PIN) == 1 && flag == false) {
    if (new_page < PAGE_NUM - 1) {
      new_page ++;
    } else {
      new_page = 0;
    }
    flag = true;
  }

  // данное условие необходимо для обеспечения работы флажка
  if (!digitalRead(BUTT_PIN) == 0 && flag == true) {
    flag = false;
  }

  // этот блок позволяет избежать мигания экрана
  // здесь смена страницы происходит только при последующем нажатии
  if (new_page != old_page) {
    old_page = new_page;
    lcd.clear();
  }

  // выбор страницы
  switch (new_page) {
    case 0: mainMenu();
      break;
    case 1: luxmeter();
      break;
    case 2: conditions();
      break;
    default: Serial.println("ERROR 404 - total system mistake"); for (;;);
      break;
  }

  // вывод отладочного лога в порт или графиков в плоттер
  if (DEBUG == 1) {
    debug();
  }
}
