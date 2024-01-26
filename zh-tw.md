## 編譯指令

用C或C++都可以

```
gcc -o horse_racing horse_racing.c
```

```
g++ -o horse_racing horse_racing.c
```

## 程式碼參數說明

- horse：馬的數量

- arena_size：跑道長度(單位：字元)

- frequency：畫面更新速度(單位：毫秒/次數)

## 執行參數說明

- [-horse=\<horse amount\>]：更改馬的數量

- [-arena=\<arena size\>]：跑道長度(單位：字元)

- [-freq=\<update frequency\>]：畫面更新速度(單位：毫秒/次數)

指令範例(順序可互換，不加就是使用初始值)：

```
horse_racing -horse=5 -arena=34 -freq=400
```
