# Watchdog Timer (TWDT)

Проєкт для **ESP32-S3 DevKitM-1** на PlatformIO демонструє роботу task watchdog (TWDT) разом із кнопкою, фоторезистором (LDR) і світлодіодом. Кнопка вмикає світлодіод за умови, що навколишнє освітлення відповідає порогу. Тривале утримання кнопки навмисно блокує основний цикл, щоб watchdog виявив зависання та перезапустив плату.

## Як це працює

- Плата опитує LDR кожні 10 мс і згладжує покази ковзним середнім із 4 вимірювань.
- Стан LDR стає активним, коли усереднене значення ADC менше `2100`.
- Кнопка опитується кожні 50 мс. Її стан стає активним після утримання щонайменше 1 секунду та до 4 секунд включно.
- Світлодіод світиться, лише коли активні і кнопка, і LDR.
- Після утримання кнопки 4 секунди або довше програма входить у нескінченний цикл. Оскільки в ньому не обслуговується watchdog, очікується перезапуск приблизно через 5 секунд.
- У послідовний порт на швидкості 115200 бод виводяться причина перезапуску та діагностичні повідомлення.

## Підключення

За замовчуванням GPIO задані в [`include/config.h`](include/config.h):

| Компонент | GPIO | Налаштування |
| --- | ---: | --- |
| Світлодіод | 17 | Вихід |
| LDR | 2 | Аналоговий вхід ADC |
| Кнопка | 18 | Цифровий вхід з внутрішнім `INPUT_PULLDOWN` |

Підключіть кнопку між GPIO 18 та 3.3 V. LDR потрібно під'єднати як частину подільника напруги, а його вихід — до GPIO 2. Переконайтеся, що напруга на ADC не перевищує допустиму для ESP32-S3. Полярність та номінали подільника визначають, як саме змінюється ADC-показ зі збільшенням освітленості; налаштуйте `LDR_THRESHOLD` відповідно до свого сенсора та схеми. Світлодіод під'єднуйте через струмообмежувальний резистор.

Перед використанням перевірте, що обрані GPIO доступні на вашій версії плати та не задіяні іншими компонентами. Номери контактів можна змінити у `include/config.h`.

## Потрібне

- ESP32-S3 DevKitM-1
- PlatformIO Core або розширення PlatformIO для VS Code
- Arduino framework для ESP32 (PlatformIO встановить залежності середовища)
- Кнопка, LDR із подільником напруги та світлодіод із резистором

## Збірка та завантаження

У корені проєкту виконайте:

```sh
pio run
pio run --target upload
pio device monitor --baud 115200
```

Якщо автоматично обрано не той послідовний порт, вкажіть його явно, наприклад:

```sh
pio run --target upload --upload-port /dev/ttyUSB0
pio device monitor --port /dev/ttyUSB0 --baud 115200
```

Ім'я порту залежить від операційної системи та підключеного пристрою.

## Конфігурація

Параметри плати та середовища PlatformIO визначені в [`platformio.ini`](platformio.ini). Ключові параметри логіки містяться в [`include/config.h`](include/config.h): GPIO `LED`, `LDR`, `BTN`, розмір фільтра `N`, періоди опитування, інтервали натискання та поріг `LDR_THRESHOLD`.

TWDT ініціалізується з таймаутом 5 секунд у `src/main.cpp`. Тест із зависанням є навмисною поведінкою цього прикладу: не утримуйте кнопку понад 4 секунди, якщо не хочете спровокувати watchdog-перезапуск.


## Serial Monitor

load:0x403cc700,len:0x2a0c
entry 0x403c98d0
Watchdog initialized: 5 seconds
reset reason: 6
adc raw value 1319 adc filtered 1305 errors 0
Button State: 0 LDR State: 1
adc raw value 1515 adc filtered 1359 errors 0
adc raw value 0 adc filtered 1033 errors 0
adc raw value 1496 adc filtered 1082 errors 0
adc raw value 89 adc filtered 775 errors 0
adc raw value 1146 adc filtered 682 errors 0
adc raw value 358 adc filtered 772 errors 0
adc raw value 665 adc filtered 564 errors 0
adc raw value 739 adc filtered 727 errors 0
adc raw value 0 adc filtered 440 errors 0
adc raw value 1244 adc filtered 662 errors 0
adc raw value 0 adc filtered 495 errors 0
adc raw value 1581 adc filtered 706 errors 0
adc raw value 0 adc filtered 706 errors 0
adc raw value 1369 adc filtered 737 errors 0
adc raw value 231 adc filtered 795 errors 0
adc raw value 855 adc filtered 613 errors 0
adc raw value 553 adc filtered 752 errors 0
adc raw value 315 adc filtered 488 errors 0
Button State: 0 LDR State: 1
adc raw value 1051 adc filtered 693 errors 0
adc raw value 0 adc filtered 479 errors 0
adc raw value 1458 adc filtered 706 errors 0
adc raw value 0 adc filtered 627 errors 0
adc raw value 1565 adc filtered 755 errors 0
adc raw value 91 adc filtered 778 errors 0
adc raw value 1135 adc filtered 697 errors 0
adc raw value 371 adc filtered 790 errors 0
adc raw value 605 adc filtered 550 errors 0
adc raw value 749 adc filtered 715 errors 0
adc raw value 0 adc filtered 431 errors 0
adc raw value 1333 adc filtered 671 errors 0
adc raw value 0 adc filtered 520 errors 0
adc raw value 1597 adc filtered 732 errors 0
adc raw value 0 adc filtered 732 errors 0
adc raw value 1343 adc filtered 735 errors 0
adc raw value 227 adc filtered 791 errors 0
adc raw value 851 adc filtered 605 errors 0
Button State: 0 LDR State: 1
adc raw value 543 adc filtered 741 errors 0
adc raw value 303 adc filtered 481 errors 0
adc raw value 975 adc filtered 668 errors 0
adc raw value 0 adc filtered 455 errors 0
adc raw value 1373 adc filtered 662 errors 0
adc raw value 0 adc filtered 587 errors 0
adc raw value 1532 adc filtered 726 errors 0
adc raw value 73 adc filtered 744 errors 0
adc raw value 1161 adc filtered 691 errors 0
adc raw value 355 adc filtered 780 errors 0
adc raw value 645 adc filtered 558 errors 0
adc raw value 723 adc filtered 721 errors 0
adc raw value 0 adc filtered 430 errors 0
adc raw value 1303 adc filtered 667 errors 0
adc raw value 0 adc filtered 506 errors 0
adc raw value 1619 adc filtered 730 errors 0
adc raw value 0 adc filtered 730 errors 0
adc raw value 1404 adc filtered 755 errors 0
Button State: 0 LDR State: 1
adc raw value 206 adc filtered 807 errors 0
adc raw value 931 adc filtered 635 errors 0
adc raw value 504 adc filtered 761 errors 0
adc raw value 341 adc filtered 495 errors 0
adc raw value 1035 adc filtered 702 errors 0
adc raw value 0 adc filtered 470 errors 0
adc raw value 1479 adc filtered 713 errors 0
adc raw value 0 adc filtered 628 errors 0
adc raw value 1595 adc filtered 768 errors 0
adc raw value 71 adc filtered 786 errors 0
adc raw value 1179 adc filtered 711 errors 0
adc raw value 334 adc filtered 794 errors 0
adc raw value 715 adc filtered 574 errors 0
adc raw value 727 adc filtered 738 errors 0
adc raw value 13 adc filtered 447 errors 0
adc raw value 1365 adc filtered 705 errors 0
adc raw value 0 adc filtered 526 errors 0
adc raw value 1645 adc filtered 755 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 752 errors 0
adc raw value 1467 adc filtered 778 errors 0
adc raw value 187 adc filtered 824 errors 0
adc raw value 1004 adc filtered 664 errors 0
adc raw value 479 adc filtered 784 errors 0
adc raw value 419 adc filtered 522 errors 0
adc raw value 1047 adc filtered 737 errors 0
adc raw value 0 adc filtered 486 errors 0
adc raw value 1544 adc filtered 752 errors 0
adc raw value 0 adc filtered 647 errors 0
adc raw value 1598 adc filtered 785 errors 0
adc raw value 58 adc filtered 800 errors 0
adc raw value 1166 adc filtered 705 errors 0
adc raw value 338 adc filtered 790 errors 0
adc raw value 740 adc filtered 575 errors 0
adc raw value 743 adc filtered 746 errors 0
adc raw value 16 adc filtered 459 errors 0
adc raw value 1383 adc filtered 720 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 535 errors 0
adc raw value 1707 adc filtered 776 errors 0
adc raw value 0 adc filtered 772 errors 0
adc raw value 1461 adc filtered 792 errors 0
adc raw value 188 adc filtered 839 errors 0
adc raw value 1015 adc filtered 666 errors 0
adc raw value 507 adc filtered 792 errors 0
adc raw value 421 adc filtered 532 errors 0
adc raw value 991 adc filtered 733 errors 0
adc raw value 0 adc filtered 479 errors 0
adc raw value 1497 adc filtered 727 errors 0
adc raw value 0 adc filtered 622 errors 0
adc raw value 1561 adc filtered 764 errors 0
adc raw value 62 adc filtered 780 errors 0
adc raw value 1167 adc filtered 697 errors 0
adc raw value 349 adc filtered 784 errors 0
adc raw value 728 adc filtered 576 errors 0
adc raw value 701 adc filtered 736 errors 0
adc raw value 37 adc filtered 453 errors 0
Button State: 0 LDR State: 1
adc raw value 1267 adc filtered 683 errors 0
adc raw value 0 adc filtered 501 errors 0
adc raw value 1528 adc filtered 708 errors 0
adc raw value 0 adc filtered 698 errors 0
adc raw value 1341 adc filtered 717 errors 0
adc raw value 209 adc filtered 769 errors 0
adc raw value 906 adc filtered 614 errors 0
adc raw value 486 adc filtered 735 errors 0
adc raw value 367 adc filtered 492 errors 0
adc raw value 883 adc filtered 660 errors 0
adc raw value 0 adc filtered 434 errors 0
adc raw value 1355 adc filtered 651 errors 0
adc raw value 0 adc filtered 559 errors 0
adc raw value 1436 adc filtered 697 errors 0
adc raw value 57 adc filtered 712 errors 0
adc raw value 1163 adc filtered 664 errors 0
adc raw value 443 adc filtered 774 errors 0
adc raw value 723 adc filtered 596 errors 0
Button State: 0 LDR State: 1
adc raw value 905 adc filtered 808 errors 0
adc raw value 164 adc filtered 558 errors 0
adc raw value 1311 adc filtered 775 errors 0
adc raw value 0 adc filtered 595 errors 0
adc raw value 1421 adc filtered 724 errors 0
adc raw value 51 adc filtered 695 errors 0
adc raw value 1054 adc filtered 631 errors 0
adc raw value 530 adc filtered 764 errors 0
adc raw value 445 adc filtered 520 errors 0
adc raw value 909 adc filtered 734 errors 0
adc raw value 0 adc filtered 471 errors 0
adc raw value 1097 adc filtered 612 errors 0
adc raw value 0 adc filtered 501 errors 0
adc raw value 1159 adc filtered 564 errors 0
adc raw value 0 adc filtered 564 errors 0
adc raw value 1103 adc filtered 565 errors 0
adc raw value 218 adc filtered 620 errors 0
adc raw value 647 adc filtered 492 errors 0
Button State: 0 LDR State: 1
adc raw value 530 adc filtered 624 errors 0
adc raw value 239 adc filtered 408 errors 0
adc raw value 777 adc filtered 548 errors 0
adc raw value 0 adc filtered 386 errors 0
adc raw value 1193 adc filtered 552 errors 0
adc raw value 0 adc filtered 492 errors 0
adc raw value 1335 adc filtered 632 errors 0
adc raw value 0 adc filtered 632 errors 0
adc raw value 1167 adc filtered 625 errors 0
adc raw value 355 adc filtered 714 errors 0
adc raw value 847 adc filtered 592 errors 0
adc raw value 605 adc filtered 743 errors 0
adc raw value 436 adc filtered 560 errors 0
adc raw value 968 adc filtered 714 errors 0
adc raw value 0 adc filtered 502 errors 0
adc raw value 1373 adc filtered 694 errors 0
adc raw value 0 adc filtered 585 errors 0
adc raw value 1517 adc filtered 722 errors 0
Button State: 0 LDR State: 1
adc raw value 87 adc filtered 744 errors 0
adc raw value 1233 adc filtered 709 errors 0
adc raw value 392 adc filtered 807 errors 0
adc raw value 824 adc filtered 634 errors 0
adc raw value 729 adc filtered 794 errors 0
adc raw value 377 adc filtered 580 errors 0
adc raw value 1613 adc filtered 885 errors 0
adc raw value 2 adc filtered 680 errors 0
adc raw value 1785 adc filtered 944 errors 0
adc raw value 9 adc filtered 852 errors 0
adc raw value 1637 adc filtered 858 errors 0
adc raw value 329 adc filtered 940 errors 0
adc raw value 1267 adc filtered 810 errors 0
adc raw value 617 adc filtered 962 errors 0
adc raw value 739 adc filtered 738 errors 0
adc raw value 1021 adc filtered 911 errors 0
adc raw value 0 adc filtered 594 errors 0
adc raw value 1451 adc filtered 802 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 618 errors 0
adc raw value 1804 adc filtered 813 errors 0
adc raw value 27 adc filtered 820 errors 0
adc raw value 1453 adc filtered 821 errors 0
adc raw value 295 adc filtered 894 errors 0
adc raw value 1049 adc filtered 706 errors 0
adc raw value 661 adc filtered 864 errors 0
adc raw value 357 adc filtered 590 errors 0
adc raw value 1166 adc filtered 808 errors 0
adc raw value 0 adc filtered 546 errors 0
adc raw value 1421 adc filtered 736 errors 0
adc raw value 0 adc filtered 646 errors 0
adc raw value 1343 adc filtered 691 errors 0
adc raw value 181 adc filtered 736 errors 0
adc raw value 887 adc filtered 602 errors 0
adc raw value 465 adc filtered 719 errors 0
adc raw value 380 adc filtered 478 errors 0
adc raw value 845 adc filtered 644 errors 0
adc raw value 0 adc filtered 422 errors 0
Button State: 0 LDR State: 1
adc raw value 1316 adc filtered 635 errors 0
adc raw value 0 adc filtered 540 errors 0
adc raw value 1507 adc filtered 705 errors 0
adc raw value 47 adc filtered 717 errors 0
adc raw value 1143 adc filtered 674 errors 0
adc raw value 307 adc filtered 751 errors 0
adc raw value 637 adc filtered 533 errors 0
adc raw value 621 adc filtered 677 errors 0
adc raw value 55 adc filtered 405 errors 0
adc raw value 1169 adc filtered 620 errors 0
adc raw value 0 adc filtered 461 errors 0
adc raw value 1423 adc filtered 661 errors 0
adc raw value 0 adc filtered 648 errors 0
adc raw value 1383 adc filtered 701 errors 0
adc raw value 169 adc filtered 743 errors 0
adc raw value 982 adc filtered 633 errors 0
adc raw value 445 adc filtered 744 errors 0
adc raw value 499 adc filtered 523 errors 0
Button State: 0 LDR State: 1
adc raw value 867 adc filtered 698 errors 0
adc raw value 0 adc filtered 452 errors 0
adc raw value 1327 adc filtered 673 errors 0
adc raw value 0 adc filtered 548 errors 0
adc raw value 1609 adc filtered 734 errors 0
adc raw value 26 adc filtered 740 errors 0
adc raw value 1385 adc filtered 755 errors 0
adc raw value 265 adc filtered 821 errors 0
adc raw value 908 adc filtered 646 errors 0
adc raw value 601 adc filtered 789 errors 0
adc raw value 275 adc filtered 512 errors 0
adc raw value 1211 adc filtered 748 errors 0
adc raw value 0 adc filtered 521 errors 0
adc raw value 1691 adc filtered 794 errors 0
adc raw value 0 adc filtered 725 errors 0
adc raw value 1695 adc filtered 846 errors 0
adc raw value 125 adc filtered 877 errors 0
adc raw value 1251 adc filtered 767 errors 0
Button State: 0 LDR State: 1
adc raw value 410 adc filtered 870 errors 0
adc raw value 710 adc filtered 624 errors 0
adc raw value 907 adc filtered 819 errors 0
adc raw value 0 adc filtered 506 errors 0
adc raw value 1480 adc filtered 774 errors 0
adc raw value 0 adc filtered 596 errors 0
adc raw value 1810 adc filtered 822 errors 0
adc raw value 10 adc filtered 825 errors 0
adc raw value 1503 adc filtered 830 errors 0
adc raw value 264 adc filtered 896 errors 0
adc raw value 1053 adc filtered 707 errors 0
adc raw value 620 adc filtered 860 errors 0
adc raw value 360 adc filtered 574 errors 0
adc raw value 1255 adc filtered 822 errors 0
adc raw value 0 adc filtered 558 errors 0
adc raw value 1660 adc filtered 818 errors 0
adc raw value 0 adc filtered 728 errors 0
adc raw value 1673 adc filtered 833 errors 0
Button State: 0 LDR State: 1
adc raw value 121 adc filtered 863 errors 0
adc raw value 1255 adc filtered 762 errors 0
adc raw value 393 adc filtered 860 errors 0
adc raw value 732 adc filtered 625 errors 0
adc raw value 855 adc filtered 808 errors 0
adc raw value 0 adc filtered 495 errors 0
adc raw value 1455 adc filtered 760 errors 0
adc raw value 0 adc filtered 577 errors 0
adc raw value 1749 adc filtered 801 errors 0
adc raw value 0 adc filtered 801 errors 0
adc raw value 1490 adc filtered 809 errors 0
adc raw value 243 adc filtered 870 errors 0
adc raw value 1063 adc filtered 699 errors 0
adc raw value 606 adc filtered 850 errors 0
adc raw value 381 adc filtered 573 errors 0
adc raw value 1252 adc filtered 825 errors 0
adc raw value 0 adc filtered 559 errors 0
adc raw value 1715 adc filtered 837 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 741 errors 0
adc raw value 1704 adc filtered 854 errors 0
adc raw value 109 adc filtered 882 errors 0
adc raw value 1290 adc filtered 775 errors 0
adc raw value 393 adc filtered 874 errors 0
adc raw value 797 adc filtered 647 errors 0
adc raw value 854 adc filtered 833 errors 0
adc raw value 0 adc filtered 511 errors 0
adc raw value 1493 adc filtered 786 errors 0
adc raw value 0 adc filtered 586 errors 0
adc raw value 1849 adc filtered 835 errors 0
adc raw value 0 adc filtered 835 errors 0
adc raw value 1593 adc filtered 860 errors 0
adc raw value 261 adc filtered 925 errors 0
adc raw value 1159 adc filtered 753 errors 0
adc raw value 617 adc filtered 907 errors 0
adc raw value 447 adc filtered 621 errors 0
adc raw value 1289 adc filtered 878 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 588 errors 0
adc raw value 1780 adc filtered 879 errors 0
adc raw value 0 adc filtered 767 errors 0
adc raw value 1763 adc filtered 885 errors 0
adc raw value 123 adc filtered 916 errors 0
adc raw value 1316 adc filtered 800 errors 0
adc raw value 413 adc filtered 903 errors 0
adc raw value 861 adc filtered 678 errors 0
adc raw value 890 adc filtered 870 errors 0
adc raw value 0 adc filtered 541 errors 0
adc raw value 1581 adc filtered 833 errors 0
adc raw value 0 adc filtered 617 errors 0
adc raw value 1885 adc filtered 866 errors 0
adc raw value 5 adc filtered 867 errors 0
adc raw value 1560 adc filtered 862 errors 0
adc raw value 249 adc filtered 924 errors 0
adc raw value 1152 adc filtered 741 errors 0
adc raw value 607 adc filtered 892 errors 0
adc raw value 509 adc filtered 629 errors 0
Button State: 0 LDR State: 1
adc raw value 1315 adc filtered 895 errors 0
adc raw value 0 adc filtered 607 errors 0
adc raw value 1862 adc filtered 921 errors 0
adc raw value 0 adc filtered 794 errors 0
adc raw value 1837 adc filtered 924 errors 0
adc raw value 125 adc filtered 956 errors 0
adc raw value 1443 adc filtered 851 errors 0
adc raw value 425 adc filtered 957 errors 0
adc raw value 909 adc filtered 725 errors 0
adc raw value 905 adc filtered 920 errors 0
adc raw value 25 adc filtered 566 errors 0
adc raw value 1610 adc filtered 862 errors 0
adc raw value 0 adc filtered 635 errors 0
adc raw value 1992 adc filtered 906 errors 0
adc raw value 10 adc filtered 903 errors 0
adc raw value 1635 adc filtered 909 errors 0
adc raw value 296 adc filtered 983 errors 0
adc raw value 1226 adc filtered 791 errors 0
Button State: 0 LDR State: 1
adc raw value 692 adc filtered 962 errors 0
adc raw value 594 adc filtered 702 errors 0
adc raw value 1319 adc filtered 957 errors 0
adc raw value 0 adc filtered 651 errors 0
adc raw value 1893 adc filtered 951 errors 0
adc raw value 0 adc filtered 803 errors 0
adc raw value 1833 adc filtered 931 errors 0
adc raw value 88 adc filtered 953 errors 0
adc raw value 1415 adc filtered 834 errors 0
adc raw value 381 adc filtered 929 errors 0
adc raw value 867 adc filtered 687 errors 0
adc raw value 855 adc filtered 879 errors 0
adc raw value 20 adc filtered 530 errors 0
adc raw value 1528 adc filtered 817 errors 0
adc raw value 0 adc filtered 600 errors 0
adc raw value 1982 adc filtered 882 errors 0
adc raw value 0 adc filtered 877 errors 0
adc raw value 1707 adc filtered 922 errors 0
Button State: 0 LDR State: 1
adc raw value 232 adc filtered 980 errors 0
adc raw value 1251 adc filtered 797 errors 0
adc raw value 589 adc filtered 944 errors 0
adc raw value 554 adc filtered 656 errors 0
adc raw value 1246 adc filtered 910 errors 0
adc raw value 0 adc filtered 597 errors 0
adc raw value 1834 adc filtered 908 errors 0
adc raw value 0 adc filtered 770 errors 0
adc raw value 1847 adc filtered 920 errors 0
adc raw value 92 adc filtered 943 errors 0
adc raw value 1446 adc filtered 846 errors 0
adc raw value 365 adc filtered 937 errors 0
adc raw value 975 adc filtered 719 errors 0
adc raw value 815 adc filtered 900 errors 0
adc raw value 79 adc filtered 558 errors 0
adc raw value 1597 adc filtered 866 errors 0
adc raw value 0 adc filtered 622 errors 0
adc raw value 1975 adc filtered 912 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 893 errors 0
adc raw value 1720 adc filtered 923 errors 0
adc raw value 217 adc filtered 978 errors 0
adc raw value 1255 adc filtered 798 errors 0
adc raw value 572 adc filtered 941 errors 0
adc raw value 635 adc filtered 669 errors 0
adc raw value 1229 adc filtered 922 errors 0
adc raw value 0 adc filtered 609 errors 0
adc raw value 1845 adc filtered 927 errors 0
adc raw value 0 adc filtered 768 errors 0
adc raw value 1864 adc filtered 927 errors 0
adc raw value 83 adc filtered 948 errors 0
adc raw value 1495 adc filtered 860 errors 0
adc raw value 371 adc filtered 953 errors 0
adc raw value 955 adc filtered 726 errors 0
adc raw value 783 adc filtered 901 errors 0
adc raw value 143 adc filtered 563 errors 0
adc raw value 1519 adc filtered 850 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 611 errors 0
adc raw value 1892 adc filtered 888 errors 0
adc raw value 0 adc filtered 852 errors 0
adc raw value 1637 adc filtered 882 errors 0
adc raw value 223 adc filtered 938 errors 0
adc raw value 1275 adc filtered 783 errors 0
adc raw value 542 adc filtered 919 errors 0
adc raw value 632 adc filtered 668 errors 0
adc raw value 1166 adc filtered 903 errors 0
adc raw value 0 adc filtered 585 errors 0
adc raw value 1659 adc filtered 864 errors 0
adc raw value 0 adc filtered 706 errors 0
adc raw value 1751 adc filtered 852 errors 0
adc raw value 73 adc filtered 870 errors 0
adc raw value 1430 adc filtered 813 errors 0
adc raw value 354 adc filtered 902 errors 0
adc raw value 915 adc filtered 693 errors 0
adc raw value 787 adc filtered 871 errors 0
adc raw value 165 adc filtered 555 errors 0
Button State: 0 LDR State: 1
adc raw value 1447 adc filtered 828 errors 0
adc raw value 0 adc filtered 599 errors 0
adc raw value 1865 adc filtered 869 errors 0
adc raw value 0 adc filtered 828 errors 0
adc raw value 1719 adc filtered 896 errors 0
adc raw value 219 adc filtered 950 errors 0
adc raw value 1297 adc filtered 808 errors 0
adc raw value 536 adc filtered 942 errors 0
adc raw value 665 adc filtered 679 errors 0
adc raw value 1173 adc filtered 917 errors 0
adc raw value 0 adc filtered 593 errors 0
adc raw value 1725 adc filtered 890 errors 0
adc raw value 0 adc filtered 724 errors 0
adc raw value 1811 adc filtered 884 errors 0
adc raw value 83 adc filtered 904 errors 0
adc raw value 1447 adc filtered 835 errors 0
adc raw value 363 adc filtered 926 errors 0
adc raw value 917 adc filtered 702 errors 0
Button State: 0 LDR State: 1
adc raw value 791 adc filtered 879 errors 0
adc raw value 189 adc filtered 565 errors 0
adc raw value 1448 adc filtered 836 errors 0
adc raw value 0 adc filtered 607 errors 0
adc raw value 1854 adc filtered 872 errors 0
adc raw value 0 adc filtered 825 errors 0
adc raw value 1691 adc filtered 886 errors 0
adc raw value 231 adc filtered 944 errors 0
adc raw value 1305 adc filtered 806 errors 0
adc raw value 559 adc filtered 946 errors 0
adc raw value 716 adc filtered 702 errors 0
adc raw value 1166 adc filtered 936 errors 0
adc raw value 0 adc filtered 610 errors 0
adc raw value 1708 adc filtered 897 errors 0
adc raw value 0 adc filtered 718 errors 0
adc raw value 1831 adc filtered 884 errors 0
adc raw value 83 adc filtered 905 errors 0
adc raw value 1502 adc filtered 854 errors 0
Button State: 0 LDR State: 1
adc raw value 359 adc filtered 943 errors 0
adc raw value 1016 adc filtered 740 errors 0
adc raw value 781 adc filtered 914 errors 0
adc raw value 232 adc filtered 597 errors 0
adc raw value 1461 adc filtered 872 errors 0
adc raw value 0 adc filtered 618 errors 0
adc raw value 1832 adc filtered 881 errors 0
adc raw value 0 adc filtered 823 errors 0
adc raw value 1645 adc filtered 869 errors 0
adc raw value 218 adc filtered 923 errors 0
adc raw value 1271 adc filtered 783 errors 0
adc raw value 541 adc filtered 918 errors 0
adc raw value 678 adc filtered 677 errors 0
adc raw value 1165 adc filtered 913 errors 0
adc raw value 0 adc filtered 596 errors 0
adc raw value 1739 adc filtered 895 errors 0
adc raw value 0 adc filtered 726 errors 0
adc raw value 1849 adc filtered 897 errors 0
Button State: 0 LDR State: 1
adc raw value 75 adc filtered 915 errors 0
adc raw value 1481 adc filtered 851 errors 0
adc raw value 371 adc filtered 944 errors 0
adc raw value 1013 adc filtered 735 errors 0
adc raw value 763 adc filtered 907 errors 0
adc raw value 237 adc filtered 596 errors 0
adc raw value 1465 adc filtered 869 errors 0
adc raw value 0 adc filtered 616 errors 0
adc raw value 1913 adc filtered 903 errors 0
adc raw value 0 adc filtered 844 errors 0
adc raw value 1720 adc filtered 908 errors 0
adc raw value 209 adc filtered 960 errors 0
adc raw value 1327 adc filtered 814 errors 0
adc raw value 537 adc filtered 948 errors 0
adc raw value 729 adc filtered 700 errors 0
adc raw value 1107 adc filtered 925 errors 0
adc raw value 0 adc filtered 593 errors 0
adc raw value 1695 adc filtered 882 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 700 errors 0
adc raw value 1856 adc filtered 887 errors 0
adc raw value 71 adc filtered 905 errors 0
adc raw value 1533 adc filtered 865 errors 0
adc raw value 371 adc filtered 957 errors 0
adc raw value 1087 adc filtered 765 errors 0
adc raw value 778 adc filtered 942 errors 0
adc raw value 273 adc filtered 627 errors 0
adc raw value 1493 adc filtered 907 errors 0
adc raw value 0 adc filtered 636 errors 0
adc raw value 1951 adc filtered 929 errors 0
adc raw value 0 adc filtered 861 errors 0
adc raw value 1748 adc filtered 924 errors 0
adc raw value 201 adc filtered 975 errors 0
adc raw value 1331 adc filtered 820 errors 0
adc raw value 519 adc filtered 949 errors 0
adc raw value 789 adc filtered 710 errors 0
adc raw value 1115 adc filtered 938 errors 0
Button State: 0 LDR State: 1
adc raw value 0 adc filtered 605 errors 0
adc raw value 1789 adc filtered 923 errors 0
adc raw value 0 adc filtered 726 errors 0
adc raw value 1979 adc filtered 942 errors 0
adc raw value 35 adc filtered 950 errors 0
adc raw value 1637 adc filtered 912 errors 0
adc raw value 319 adc filtered 992 errors 0
adc raw value 1147 adc filtered 784 errors 0
adc raw value 731 adc filtered 958 errors 0
adc raw value 483 adc filtered 670 errors 0
adc raw value 1395 adc filtered 939 errors 0
adc raw value 0 adc filtered 652 errors 0
adc raw value 1775 adc filtered 913 errors 0
adc raw value 0 adc filtered 792 errors 0
adc raw value 1717 adc filtered 873 errors 0
adc raw value 211 adc filtered 925 errors 0
adc raw value 1436 adc filtered 841 errors 0
adc raw value 581 adc filtered 986 errors 0
adc raw value 966 adc filtered 798 errors 0
Button State: 0 LDR State: 1
adc raw value 1101 adc filtered 1021 errors 0
adc raw value 267 adc filtered 728 errors 0
adc raw value 1673 adc filtered 1001 errors 0
adc raw value 0 adc filtered 760 errors 0
adc raw value 1861 adc filtered 950 errors 0
adc raw value 53 adc filtered 896 errors 0
adc raw value 1463 adc filtered 844 errors 0
adc raw value 2263 adc filtered 1410 errors 0
adc raw value 1493 adc filtered 1318 errors 0
adc raw value 2063 adc filtered 1820 errors 0
adc raw value 1929 adc filtered 1937 errors 0
adc raw value 1835 adc filtered 1830 errors 0
adc raw value 2173 adc filtered 2000 errors 0
adc raw value 1679 adc filtered 1904 errors 0
adc raw value 2387 adc filtered 2018 errors 0
adc raw value 1479 adc filtered 1929 errors 0
adc raw value 2366 adc filtered 1977 errors 0
adc raw value 1497 adc filtered 1932 errors 0
Button State: 0 LDR State: 1
adc raw value 2407 adc filtered 1937 errors 0
adc raw value 2054 adc filtered 2081 errors 0
adc raw value 1824 adc filtered 1945 errors 0
adc raw value 1491 adc filtered 2016 errors 0
adc raw value 1383 adc filtered 2057 errors 0
adc raw value 2584 adc filtered 2029 errors 0
adc raw value 1531 adc filtered 2039 errors 0
adc raw value 2381 adc filtered 1969 errors 0
adc raw value 1683 adc filtered 2044 errors 0
adc raw value 2213 adc filtered 1952 errors 0
adc raw value 1669 adc filtered 2010 errors 0
adc raw value 1445 adc filtered 2068 errors 0
adc raw value 1496 adc filtered 2086 errors 0
Button State: 0 LDR State: 1
adc raw value 2601 adc filtered 2065 errors 0
adc raw value 2491 adc filtered 2057 errors 0
adc raw value 1909 adc filtered 2032 errors 0
adc raw value 1701 adc filtered 2057 errors 0
adc raw value 1582 adc filtered 2098 errors 0
adc raw value 2525 adc filtered 2096 errors 0
adc raw value 1653 adc filtered 2084 errors 0
adc raw value 2530 adc filtered 2072 errors 0
adc raw value 1636 adc filtered 2086 errors 0
adc raw value 2318 adc filtered 2034 errors 0
adc raw value 1893 adc filtered 2017 errors 0
adc raw value 1763 adc filtered 2064 errors 0
Button State: 0 LDR State: 1
adc raw value 2203 adc filtered 2060 errors 0
adc raw value 1637 adc filtered 1996 errors 0
adc raw value 1891 adc filtered 1873 errors 0
adc raw value 2095 adc filtered 1956 errors 0
adc raw value 1334 adc filtered 1739 errors 0
adc raw value 1389 adc filtered 1677 errors 0
adc raw value 1628 adc filtered 1611 errors 0
adc raw value 717 adc filtered 1267 errors 0
adc raw value 2013 adc filtered 1436 errors 0
adc raw value 517 adc filtered 1218 errors 0
adc raw value 2111 adc filtered 1339 errors 0
adc raw value 851 adc filtered 1373 errors 0
adc raw value 1747 adc filtered 1306 errors 0
adc raw value 647 adc filtered 1339 errors 0
adc raw value 1311 adc filtered 1139 errors 0
adc raw value 1060 adc filtered 1191 errors 0
adc raw value 917 adc filtered 983 errors 0
adc raw value 1801 adc filtered 1272 errors 0
Button State: 0 LDR State: 1
adc raw value 379 adc filtered 1039 errors 0
adc raw value 2066 adc filtered 1290 errors 0
adc raw value 295 adc filtered 1135 errors 0
adc raw value 1875 adc filtered 1153 errors 0
adc raw value 747 adc filtered 1245 errors 0
adc raw value 1555 adc filtered 1118 errors 0
adc raw value 1097 adc filtered 1318 errors 0
adc raw value 1159 adc filtered 1139 errors 0
adc raw value 1531 adc filtered 1335 errors 0
adc raw value 715 adc filtered 1125 errors 0
adc raw value 1898 adc filtered 1325 errors 0
adc raw value 583 adc filtered 1181 errors 0
adc raw value 1997 adc filtered 1298 errors 0
adc raw value 762 adc filtered 1310 errors 0
adc raw value 1622 adc filtered 1241 errors 0
adc raw value 1097 adc filtered 1369 errors 0
adc raw value 1317 adc filtered 1199 errors 0
adc raw value 1415 adc filtered 1362 errors 0
adc raw value 1022 adc filtered 1212 errors 0
Button State: 0 LDR State: 1
adc raw value 1816 adc filtered 1392 errors 0
adc raw value 671 adc filtered 1231 errors 0
btn 8738
adc raw value 2385 adc filtered 1473 errors 0
adc raw value 1205 adc filtered 1519 errors 0
adc raw value 2054 adc filtered 1578 errors 0
adc raw value 1397 adc filtered 1760 errors 0
adc raw value 1683 adc filtered 1584 errors 0
btn 8789
adc raw value 1660 adc filtered 1698 errors 0
adc raw value 1430 adc filtered 1542 errors 0
adc raw value 1885 adc filtered 1664 errors 0
adc raw value 1197 adc filtered 1543 errors 0
adc raw value 2124 adc filtered 1659 errors 0
btn 8840
adc raw value 1179 adc filtered 1596 errors 0
adc raw value 2108 adc filtered 1652 errors 0
adc raw value 1303 adc filtered 1678 errors 0
adc raw value 1787 adc filtered 1594 errors 0
btn 8891
adc raw value 1553 adc filtered 1687 errors 0
adc raw value 1512 adc filtered 1538 errors 0
Button State: 1 LDR State: 1
adc raw value 1803 adc filtered 1663 errors 0
adc raw value 1331 adc filtered 1549 errors 0
adc raw value 2079 adc filtered 1681 errors 0
btn 8942
adc raw value 1203 adc filtered 1604 errors 0
adc raw value 2132 adc filtered 1686 errors 0
adc raw value 1207 adc filtered 1655 errors 0
adc raw value 1976 adc filtered 1629 errors 0
btn 8993
adc raw value 1432 adc filtered 1686 errors 0
adc raw value 1646 adc filtered 1565 errors 0
adc raw value 1660 adc filtered 1678 errors 0
adc raw value 1436 adc filtered 1543 errors 0
adc raw value 1893 adc filtered 1658 errors 0
btn 9044
adc raw value 1209 adc filtered 1549 errors 0
adc raw value 2125 adc filtered 1665 errors 0
adc raw value 1202 adc filtered 1607 errors 0
adc raw value 2039 adc filtered 1643 errors 0
adc raw value 1309 adc filtered 1668 errors 0
btn 9095
adc raw value 1752 adc filtered 1575 errors 0
Button State: 1 LDR State: 1
adc raw value 1560 adc filtered 1665 errors 0
adc raw value 1528 adc filtered 1537 errors 0
adc raw value 1813 adc filtered 1663 errors 0
btn 9146
adc raw value 1369 adc filtered 1567 errors 0
adc raw value 2075 adc filtered 1696 errors 0
adc raw value 1181 adc filtered 1609 errors 0
adc raw value 2101 adc filtered 1681 errors 0
adc raw value 1209 adc filtered 1641 errors 0
btn 9197
adc raw value 1932 adc filtered 1605 errors 0
adc raw value 1429 adc filtered 1667 errors 0
adc raw value 1635 adc filtered 1551 errors 0
adc raw value 1683 adc filtered 1669 errors 0
adc raw value 1387 adc filtered 1533 errors 0
btn 9248
adc raw value 1846 adc filtered 1637 errors 0
adc raw value 1215 adc filtered 1532 errors 0
adc raw value 2044 adc filtered 1623 errors 0
adc raw value 1172 adc filtered 1569 errors 0
btn 9299
adc raw value 2410 adc filtered 1710 errors 0
Button State: 1 LDR State: 1
adc raw value 1251 adc filtered 1719 errors 0
adc raw value 2011 adc filtered 1711 errors 0
adc raw value 1483 adc filtered 1788 errors 0
adc raw value 1783 adc filtered 1632 errors 0
btn 9350
adc raw value 1725 adc filtered 1750 errors 0
adc raw value 1403 adc filtered 1598 errors 0
adc raw value 2134 adc filtered 1761 errors 0
adc raw value 1145 adc filtered 1601 errors 0
adc raw value 2471 adc filtered 1788 errors 0
btn 9401
adc raw value 1169 adc filtered 1729 errors 0
adc raw value 2207 adc filtered 1748 errors 0
adc raw value 1255 adc filtered 1775 errors 0
adc raw value 1976 adc filtered 1651 errors 0
btn 9452
adc raw value 1462 adc filtered 1725 errors 0
adc raw value 1625 adc filtered 1579 errors 0
adc raw value 1849 adc filtered 1728 errors 0
adc raw value 1146 adc filtered 1520 errors 0
adc raw value 2420 adc filtered 1760 errors 0
btn 9503
Button State: 1 LDR State: 1
adc raw value 1148 adc filtered 1640 errors 0
adc raw value 2745 adc filtered 1864 errors 0
adc raw value 1175 adc filtered 1872 errors 0
adc raw value 2411 adc filtered 1869 errors 0
btn 9554
adc raw value 1352 adc filtered 1920 errors 0
adc raw value 1960 adc filtered 1724 errors 0
adc raw value 1619 adc filtered 1835 errors 0
adc raw value 1437 adc filtered 1592 errors 0
adc raw value 2213 adc filtered 1807 errors 0
btn 9605
adc raw value 1143 adc filtered 1603 errors 0
adc raw value 2637 adc filtered 1857 errors 0
adc raw value 1157 adc filtered 1787 errors 0
adc raw value 2591 adc filtered 1882 errors 0
adc raw value 1253 adc filtered 1909 errors 0
btn 9656
adc raw value 2151 adc filtered 1788 errors 0
adc raw value 1467 adc filtered 1865 errors 0
adc raw value 1692 adc filtered 1640 errors 0
adc raw value 1803 adc filtered 1778 errors 0
btn 9707
Button State: 1 LDR State: 1
adc raw value 1164 adc filtered 1531 errors 0
adc raw value 2395 adc filtered 1763 errors 0
adc raw value 1150 adc filtered 1628 errors 0
adc raw value 2707 adc filtered 1854 errors 0
adc raw value 1169 adc filtered 1855 errors 0
btn 9758
adc raw value 2309 adc filtered 1833 errors 0
adc raw value 1363 adc filtered 1887 errors 0
adc raw value 1891 adc filtered 1683 errors 0
adc raw value 1597 adc filtered 1790 errors 0
adc raw value 1459 adc filtered 1577 errors 0
btn 9809
adc raw value 2136 adc filtered 1770 errors 0
adc raw value 1147 adc filtered 1584 errors 0
adc raw value 2589 adc filtered 1832 errors 0
adc raw value 1159 adc filtered 1757 errors 0
btn 9860
adc raw value 2597 adc filtered 1873 errors 0
adc raw value 1243 adc filtered 1897 errors 0
adc raw value 2105 adc filtered 1776 errors 0
adc raw value 1465 adc filtered 1852 errors 0
adc raw value 1755 adc filtered 1642 errors 0
Button State: 1 LDR State: 1
btn 9911
adc raw value 1802 adc filtered 1781 errors 0
adc raw value 1164 adc filtered 1546 errors 0
adc raw value 2427 adc filtered 1787 errors 0
adc raw value 1148 adc filtered 1635 errors 0
adc raw value 2532 adc filtered 1817 errors 0
btn 9962
adc raw value 1171 adc filtered 1819 errors 0
adc raw value 2407 adc filtered 1814 errors 0
adc raw value 1309 adc filtered 1854 errors 0
adc raw value 1945 adc filtered 1708 errors 0
btn 10013
adc raw value 1615 adc filtered 1819 errors 0
adc raw value 1495 adc filtered 1591 errors 0
adc raw value 2135 adc filtered 1797 errors 0
adc raw value 1141 adc filtered 1596 errors 0
adc raw value 2495 adc filtered 1816 errors 0
btn 10064
adc raw value 1163 adc filtered 1733 errors 0
adc raw value 2393 adc filtered 1798 errors 0
adc raw value 1237 adc filtered 1822 errors 0
adc raw value 2028 adc filtered 1705 errors 0
Button State: 1 LDR State: 1
btn 10115
adc raw value 1471 adc filtered 1782 errors 0
adc raw value 1587 adc filtered 1580 errors 0
adc raw value 1806 adc filtered 1723 errors 0
adc raw value 1147 adc filtered 1502 errors 0
adc raw value 2328 adc filtered 1717 errors 0
btn 10166
adc raw value 1141 adc filtered 1605 errors 0
adc raw value 2531 adc filtered 1786 errors 0
adc raw value 1187 adc filtered 1796 errors 0
adc raw value 2213 adc filtered 1768 errors 0
adc raw value 1341 adc filtered 1818 errors 0
btn 10217
adc raw value 1774 adc filtered 1628 errors 0
adc raw value 1639 adc filtered 1741 errors 0
adc raw value 1431 adc filtered 1546 errors 0
adc raw value 2131 adc filtered 1743 errors 0
btn 10268
adc raw value 1143 adc filtered 1586 errors 0
adc raw value 2487 adc filtered 1798 errors 0
adc raw value 1138 adc filtered 1724 errors 0
adc raw value 2376 adc filtered 1786 errors 0
Button State: 1 LDR State: 1
adc raw value 1235 adc filtered 1809 errors 0
btn 10319
adc raw value 1976 adc filtered 1681 errors 0
adc raw value 1467 adc filtered 1763 errors 0
adc raw value 1519 adc filtered 1549 errors 0
adc raw value 1773 adc filtered 1683 errors 0
adc raw value 1147 adc filtered 1476 errors 0
btn 10370
adc raw value 2261 adc filtered 1675 errors 0
adc raw value 1147 adc filtered 1582 errors 0
adc raw value 2493 adc filtered 1762 errors 0
adc raw value 1176 adc filtered 1769 errors 0
btn 10421
adc raw value 2045 adc filtered 1715 errors 0
adc raw value 1339 adc filtered 1763 errors 0
adc raw value 1714 adc filtered 1568 errors 0
adc raw value 1612 adc filtered 1677 errors 0
adc raw value 1399 adc filtered 1516 errors 0
btn 10472
adc raw value 2092 adc filtered 1704 errors 0
adc raw value 1141 adc filtered 1561 errors 0
adc raw value 2382 adc filtered 1753 errors 0
Button State: 1 LDR State: 1
adc raw value 1164 adc filtered 1694 errors 0
adc raw value 2230 adc filtered 1729 errors 0
btn 10523
adc raw value 1239 adc filtered 1753 errors 0
adc raw value 1973 adc filtered 1651 errors 0
adc raw value 1469 adc filtered 1727 errors 0
adc raw value 1641 adc filtered 1580 errors 0
btn 10574
adc raw value 1789 adc filtered 1718 errors 0
adc raw value 1148 adc filtered 1511 errors 0
adc raw value 2299 adc filtered 1719 errors 0
adc raw value 1148 adc filtered 1596 errors 0
adc raw value 2503 adc filtered 1774 errors 0
btn 10625
adc raw value 1174 adc filtered 1781 errors 0
adc raw value 2220 adc filtered 1761 errors 0
adc raw value 1355 adc filtered 1813 errors 0
adc raw value 1835 adc filtered 1646 errors 0
btn 10676
adc raw value 1605 adc filtered 1753 errors 0
adc raw value 1428 adc filtered 1555 errors 0
adc raw value 2091 adc filtered 1739 errors 0
Button State: 1 LDR State: 1
adc raw value 1141 adc filtered 1566 errors 0
adc raw value 2405 adc filtered 1766 errors 0
btn 10727
adc raw value 1141 adc filtered 1694 errors 0
adc raw value 2364 adc filtered 1762 errors 0
adc raw value 1231 adc filtered 1785 errors 0
adc raw value 2014 adc filtered 1687 errors 0
adc raw value 1449 adc filtered 1764 errors 0
btn 10778
adc raw value 1579 adc filtered 1568 errors 0
adc raw value 1797 adc filtered 1709 errors 0
adc raw value 1191 adc filtered 1504 errors 0
adc raw value 2253 adc filtered 1705 errors 0
btn 10829
adc raw value 1160 adc filtered 1600 errors 0
adc raw value 2509 adc filtered 1778 errors 0
adc raw value 1172 adc filtered 1773 errors 0
adc raw value 2173 adc filtered 1753 errors 0
adc raw value 1367 adc filtered 1805 errors 0
btn 10880
adc raw value 1848 adc filtered 1640 errors 0
adc raw value 1611 adc filtered 1749 errors 0
adc raw value 1453 adc filtered 1569 errors 0
Button State: 1 LDR State: 1
adc raw value 2029 adc filtered 1735 errors 0
adc raw value 1145 adc filtered 1559 errors 0
btn 10931
adc raw value 2379 adc filtered 1751 errors 0
adc raw value 1161 adc filtered 1678 errors 0
adc raw value 2390 adc filtered 1768 errors 0
adc raw value 1229 adc filtered 1789 errors 0
btn 10982
adc raw value 2030 adc filtered 1702 errors 0
adc raw value 1464 adc filtered 1778 errors 0
adc raw value 1657 adc filtered 1595 errors 0
adc raw value 1747 adc filtered 1724 errors 0
adc raw value 1197 adc filtered 1516 errors 0
btn 11033
adc raw value 2294 adc filtered 1723 errors 0
adc raw value 1147 adc filtered 1596 errors 0
adc raw value 2508 adc filtered 1786 errors 0
adc raw value 1175 adc filtered 1781 errors 0
adc raw value 2147 adc filtered 1744 errors 0
btn 11084
adc raw value 1357 adc filtered 1796 errors 0
adc raw value 1817 adc filtered 1624 errors 0
Button State: 1 LDR State: 1
adc raw value 1627 adc filtered 1737 errors 0
adc raw value 1496 adc filtered 1574 errors 0
btn 11135
adc raw value 2037 adc filtered 1744 errors 0
adc raw value 1145 adc filtered 1576 errors 0
adc raw value 2344 adc filtered 1755 errors 0
adc raw value 1161 adc filtered 1671 errors 0
adc raw value 2339 adc filtered 1747 errors 0
btn 11186
adc raw value 1227 adc filtered 1767 errors 0
adc raw value 1956 adc filtered 1670 errors 0
adc raw value 1455 adc filtered 1744 errors 0
adc raw value 1701 adc filtered 1584 errors 0
btn 11237
adc raw value 1797 adc filtered 1727 errors 0
adc raw value 1240 adc filtered 1548 errors 0
adc raw value 2279 adc filtered 1754 errors 0
adc raw value 1147 adc filtered 1615 errors 0
adc raw value 2525 adc filtered 1797 errors 0
btn 11288
adc raw value 1167 adc filtered 1779 errors 0
adc raw value 2169 adc filtered 1752 errors 0
Button State: 1 LDR State: 1
adc raw value 1325 adc filtered 1796 errors 0
adc raw value 1783 adc filtered 1611 errors 0
adc raw value 1594 adc filtered 1717 errors 0
btn 11339
adc raw value 1483 adc filtered 1546 errors 0
adc raw value 2011 adc filtered 1717 errors 0
adc raw value 1127 adc filtered 1553 errors 0
adc raw value 2343 adc filtered 1741 errors 0
btn 11390
adc raw value 1158 adc filtered 1659 errors 0
adc raw value 2313 adc filtered 1735 errors 0
adc raw value 1221 adc filtered 1758 errors 0
adc raw value 1947 adc filtered 1659 errors 0
adc raw value 1439 adc filtered 1730 errors 0
btn 11441
adc raw value 1695 adc filtered 1575 errors 0
adc raw value 1727 adc filtered 1702 errors 0
adc raw value 1246 adc filtered 1526 errors 0
adc raw value 2263 adc filtered 1732 errors 0
adc raw value 1150 adc filtered 1596 errors 0
btn 11492
adc raw value 2462 adc filtered 1780 errors 0
Button State: 1 LDR State: 1
adc raw value 1163 adc filtered 1759 errors 0
adc raw value 2268 adc filtered 1760 errors 0
adc raw value 1306 adc filtered 1799 errors 0
btn 11543
adc raw value 1855 adc filtered 1648 errors 0
adc raw value 1609 adc filtered 1759 errors 0
adc raw value 1549 adc filtered 1579 errors 0
adc raw value 2020 adc filtered 1758 errors 0
adc raw value 1145 adc filtered 1580 errors 0
btn 11594
adc raw value 2303 adc filtered 1754 errors 0
adc raw value 1146 adc filtered 1653 errors 0
adc raw value 2451 adc filtered 1761 errors 0
adc raw value 1229 adc filtered 1782 errors 0
adc raw value 2024 adc filtered 1712 errors 0
btn 11645
adc raw value 1483 adc filtered 1796 errors 0
adc raw value 1739 adc filtered 1618 errors 0
adc raw value 1788 adc filtered 1758 errors 0
adc raw value 1228 adc filtered 1559 errors 0
btn 11696
adc raw value 2303 adc filtered 1764 errors 0
Button State: 1 LDR State: 1
adc raw value 1145 adc filtered 1616 errors 0
adc raw value 2294 adc filtered 1742 errors 0
adc raw value 1165 adc filtered 1726 errors 0
adc raw value 2211 adc filtered 1703 errors 0
E (33393) task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time:
E (33393) task_wdt:  - loopTask (CPU 1)
E (33393) task_wdt: Tasks currently running:
E (33393) task_wdt: CPU 0: IDLE0
E (33393) task_wdt: CPU 1: loopTask
E (33393) task_wdt: Aborting.

abort() was called at PC 0x4200c7b0 on core 0


Backtrace: 0x40377896:0x3fc93770 0x4137afb9:0x3fc93790 0x403806b1:0x3fc947b0 0x4200c7b0:0x3fc93830 0x40378a59:0x3fc93850 0x420258c7:0x3fcf4760 0x4200cfd2:0x4fcf4780 0x4037c154:0x3fcf47a0




ELF file SHA256: 86ba768ae8e4f4d3

Rebooting...
␀�ESP-ROM:esp32s3-21210427
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x9 (SPI_FAST_FLASH_BOOT)
Saved PC:0x403774a4
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce3808,len:0x4bc
load:0x403c9700,len:0xbd8
load:0x403cc700,len:0x2a0c
entry 0x403c98d0
Watchdog initialized: 5 seconds
reset reason: 6