# altimeter-clock
часы-высотомер

!(часы-высотомер, вид 1)[https://github.com/DIY-Elecron1cs/altimeter-clock/blob/main/images/%D1%80%D0%B5%D0%B7%D1%83%D0%BB%D1%8C%D1%82%D0%B0%D1%82%20(%D1%81%D0%B1%D0%BE%D0%BA%D1%83).jpg?raw=true]


## управление
### основные режимы
- Кнопками ВПРАВО/ВЛЕВО можно переключать между основными режимами ("TIME" и "METEO").
- Кнопкой ВВЕРХ вызывается режим энергосбережения. В нём отображаются только часы.
- Выйти из режима энергосбережения можно с помощью кнопок ВНИЗ/ВЛЕВО/ВПРАВО.
- Кнопкой ВНИЗ вызывается полная заливка дисплея белым (фонарик).
- Выйти из режима фонарика можно с помощью кнопок ВВЕРХ/ВЛЕВО/ВПРАВО.

- Нажатие на кнопку ОК вызывает главные настройки (режим SETTINGS).
### в режиме SETTINGS
- Кнопками ВНИЗ/ВВЕРХ осуществляется перемещение по основным параметрам.
- В первом пункте меню находится настройка РЕЖИМ. С помощью кнопок ВЛЕВО/ВПРАВО можно менять режим на значения "РУЧН." или "КОМБ." (соответственно "ручной" и "комбинированный"). В режиме "РУЧН." управление по главному меню осуществляется вручную, а в режиме "КОМБ." – экраны "TIME" и "METEO" меняются каждые 3 секунды.
- Во втором пункте находится настройка режима по умолчанию ("TIME" или "METEO"). Меняется кнопками ВЛЕВО/ВПРАВО. Выбранный режим отображается при включении.
- Строка КОРРЕКТ позволяет линейно корректировать высоту в МНУМ (метрах над уровнем моря), так же кнопками ВЛЕВО/ВПРАВО.

#### выход из SETTINGS и сохранение настроек
- Выйти из режима SETTINGS можно двумя способами: EXIT и EXIT+SAVE (предпоследний и последний пункт меню). Для выхода нужно на одном из этих пунктов нажать ВЛЕВО или ВПРАВО.
- Выход с помощью EXIT просто выходит из настроек, и настройки сбрасываюся при выключении.
- При выходе с помощью EXIT+SAVE данные сохраняются в энергонезависимой памяти (EEPROM).

## компоненты (модули)
- Arduino NANO
- DS3231 (модуль часов реального времени)
- BME280 (датчик температуры/влажности/давления)
- TP4056 (зарядник для литиевых аккумуляторов)
- Mini DC-DC Step Up Converter Board Module (гуглить именно так, какого-то определённого названия у него нет)
