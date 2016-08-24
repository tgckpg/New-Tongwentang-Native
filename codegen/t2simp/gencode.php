<?php

include __DIR__ . "/../mkcstable.php";

$wconv_t = get_function_group(__DIR__ . "/word_t2s.txt", "w_");
file_put_contents(__DIR__ . "/../../native/t2simp/wconv_gtable.cpp", $wconv_t);
