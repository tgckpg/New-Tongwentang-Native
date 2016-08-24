# 新同文堂 Native [![Build Status](https://travis-ci.org/tgckpg/New-Tongwentang-Native.svg?branch=master)](https://travis-ci.org/tgckpg/New-Tongwentang-Native)
這是新同文堂 Native ( 對照表直接取自新同文堂 web )

### Native 有什麼用？
當然就是可以轉換得比較快吧，順便我想學習怎麼用 travis-ci 和寫 make file。不過主要自的是想整合 CI ，因為我喜歡新同文堂的轉換概念，而且轉換這種東西挺適合用 CI 測試呢。

記得幾年前電郵給 softcup 先生回報有關「發 -> 髮」的 bug。意外得到回信説他很懶 ( 其實我也很懶所以也不是不能理解ww )，覺得好可惜……又因為這東西我一直也有在用 ( wenku10 )，所以就索性這樣直接 fork 一個出來做好了。

沒有覺得 make test 很帥嗎？

### s2trad ( native/s2trad/bin/ )
`s2trad <FILE> 簡 -> 繁`

### t2simp ( native/t2simp/bin/ )
`t2simp <FILE> 繁 -> 簡`
