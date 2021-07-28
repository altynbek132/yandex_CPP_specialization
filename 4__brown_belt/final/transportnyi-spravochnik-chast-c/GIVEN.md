Реализуйте вторую версию задачи со следующими изменениями.

В базе появляются данные о реальном — измеренном по дорогам — расстоянии между остановками.

### **Stop** **_X_** (изменения запроса на добавление остановки)

Новый формат запроса на добавление остановки: **Stop** **_X_****:** **_latitude_****,** **_longitude_****,** **_D1_****m
to** **_stop1_****,** **_D2_****m to** **_stop2_****,** ...

А именно, теперь после широты и долготы может содержаться список расстояний от этой остановки до соседних. По умолчанию
предполагается, что расстояние от _**X**_ до _**stop#**_ равно расстоянию от _**stop#**_ до _**X**_, если только
расстояние от _**stop#**_ до _**X**_ не задано явным образом при добавлении остановки _**stop#**_

Гарантируется, что каждая из остановок _**stop#**_ определена в некотором запросе **Stop**.

В рамках одного запроса **Stop** все _**stop#**_ различны, и их количество не превосходит 100.

Все _**Di**_ являются целыми положительными числами, каждое из которых не превышает 1000000 и не меньше расстояния по
прямой между соответствующими остановками. После каждого расстояния обязательно следует буква **m**.

### **Bus** **_X_** (изменения запроса на информацию об автобусе)

Новый формат ответа на запрос информации об автобусе: **Bus** **_X_****:** **_R_** **stops on route,** **_U_** **unique
stops,** **_L_** **route length,** **_C_** **curvature**

- _**L**_ теперь вычисляется с использованием дорожного расстояния, а не географических координат.
- _**C**_ (извилистость) — отношение длины маршрута, вычисленной с помощью дорожного расстояния, (новое _**L**_) к длине
  маршрута, вычисленной с помощью географического расстояния (_**L**_ из предыдущих версий задачи). Таким образом, _**
  C**_ — вещественное число, большее единицы. Оно может быть равно единице только в том случае, если автобус едет между
  остановками по кратчайшему пути (и тогда больше похож на вертолёт), а меньше единицы может оказаться только благодаря
  телепортации или хордовым тоннелям.

Гарантируется, что для любых двух соседних остановок любого маршрута так или иначе задано расстояние по дорогам.

## Пример

### Ввод

```
13
Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino
Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam
Stop Biryusinka: 55.581065, 37.64839, 750m to Universam
Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
```

### Вывод

```
Bus 256: 6 stops on route, 5 unique stops, 5950 route length, 1.361239 curvature
Bus 750: 5 stops on route, 3 unique stops, 27600 route length, 1.318084 curvature
Bus 751: not found
Stop Samara: not found
Stop Prazhskaya: no buses
Stop Biryulyovo Zapadnoye: buses 256 828
```
