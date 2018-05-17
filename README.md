# 新同文堂 Native [![Build Status](https://travis-ci.org/tgckpg/New-Tongwentang-Native.svg?branch=master)](https://travis-ci.org/tgckpg/New-Tongwentang-Native)
這是新同文堂 Native ( 對照表基於 [新同文堂 Chrome](https://github.com/softcup/New-Tongwentang-for-Chrome) )

注：這邊的對照表翻譯上基本是以一般讀物 ( 例如小説 ) 為主，所以不會計對文言或專業術語作出修正。加上由於算法不同，所以對照表多少會跟原版有點出入 ( 這個出入亦會隨時間慢慢增長 )。

### 什麼是 Native ？
Native 就是指 native binary，轉換方式採用了 aho-chorasick 的算法。另外也整合了 CI 和 make test，讓修改對照表時可以快速地從 test 中找出是否吻合預期的轉換結果。

算法演示
```
-> 原文
　把考卷发回来

-> words.txt
　把考卷發回來

-> phrases.txt
　把考卷發回來
　　考卷
　　　捲髮
　　考卷發
```

### ntr-tw ( bin/ )
`ntr-tw <FILE>`
這個指令會在當前目錄尋找並根據對照表轉換 ( 如沒有對照表，則直接輸出原文 )：
 - `words.txt`
 - `phrases.txt`

## Windows 版
Windows library 請移步至 [libtranslate](https://github.com/tgckpg/libtranslate)
