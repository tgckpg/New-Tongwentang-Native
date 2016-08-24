<?php

include __DIR__ . "/../mkcstable.php";

$wconv_t = get_function_group(__DIR__ . "/phrase_s2t.txt", "p_");
$wconv_t .= get_function_group(__DIR__ . "/word_s2t.txt", "w_");
file_put_contents(__DIR__ . "/../../native/s2trad/wconv_gtable.cpp", $wconv_t);
