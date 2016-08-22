<?php

//
// Code generation
// use php-cli to run
//

function myErrorHandler($errno, $errstr, $errfile, $errline)
{
	global $Log;
	if ($errno == E_NOTICE)
	{
		file_put_contents("mkcstable.log", $Log);
		die ("\n$errstr at $errline\n");
	}
	else
		return false; // Leave everything else to PHP's error handling
}

$Log = "";
$LogLine = function ($string)
{
	global $Log;
	$Log .= $string;
};

set_error_handler("myErrorHandler");

require_once __DIR__ . "/../bytemap/codegen/ByteMap.php";

///// C++  
//  void match_p_byte{X}(unsigned char const* str, int start, char const* &out, int &step_size)
//  {
//  	step_size = 0;
//	  if(str[start] == 65 && str[start + 1] == 65)
//  	{
//  		out = "AAAA";
//  		step_size = 2;
//  	}
//  }

class STCompiler implements ByteMapCompiler
{
    protected function get_indent($l)
    {
        return str_repeat("  ", $l);
    }

    protected function conditionMap($index, $value)
    {
        return "str[start + $index] == $value";
    }

    function branchOpen($level, \Branch $b)
    {
        $indent = $this->get_indent($level);
        $index = array_keys($b->byteSequence);

        $cond = implode(" && ", array_map([$this, 'conditionMap'], $index, $b->byteSequence));

        if($b->isHead)
        {
            return "{$indent}if( $cond )\n$indent{\n";
        }
        else
        {
            return "{$indent}else if ( $cond )\n$indent{\n";
        }
    }

    function branchValue($level, $value, $seq_len, $wholeByte, $index_byte)
    {
        $indent = $this->get_indent($level + 1);
        if($wholeByte)
        {
            return
                "{$indent}if( step_size == 0 )\n$indent{\n"
                . "$indent  out = \"$value\";\n"
                . "$indent  step_size = $seq_len;\n"
                . "$indent}\n"
                ;
        }
        else
        {
            return "{$indent}out = \"$value\";\n"
                . "{$indent}step_size = $seq_len;\n";
        }
    }

    function branchClose($level, $isHead)
    {
        return $this->get_indent($level) . "}\n";
    }
}


function generate_match_function($byteX, $seq_num, $token)
{
	$byteX_match_function = <<< ___BYTEARR___

void match_$token$seq_num(unsigned char const* str, int start, char const* &out, int &step_size)
{
  step_size = 0;

___BYTEARR___;
    global $LogLine;
    $bm = new ByteMap($LogLine);
    $bh = new STCompiler();
    return $byteX_match_function
     . $bm->cascade($byteX)->compile(1, $bh)
     . "\n}";
}



function get_function_group($file, $token)
{
	echo "Table file: $file\n";
	$string = "";
	$file = file($file, FILE_IGNORE_NEW_LINES);
	$k = count($file);

	$byte6 = array();
	$byte5 = array();
	$byte4 = array();
	$byte3 = array();
	$byte2 = array();
	$ascii = array();

	echo "Catergorizing bytes...\n";

	foreach($file as $value)
	{
		list($v1, $v2) = explode(',', $value);
		if(ord($value[0]) >> 1 == 0x7e)
		{
			$byte6[$v1] = $v2;
		}
		else if(ord($value[0]) >> 2 == 0x3e)
		{
			$byte5[$v1] = $v2;
		}
		else if(ord($value[0]) >> 3 == 0x1e)
		{
			$byte4[$v1] = $v2;
		}
		else if(ord($value[0]) >> 4 == 0xe)
		{
			$byte3[$v1] = $v2;
		}
		else if(ord($value[0]) >> 5 == 6)
		{
			$byte2[$v1] = $v2;
		}
		else if(ord($value[0]) < 128)
		{
			$ascii[$v1] = $v2;
		}
	}

	$wconv_table = "";
	echo "Generating byte functions...\n";
	echo "  byte6, Analyzing levels ...\n";
	$wconv_table .= generate_match_function($byte6, "byte6", $token);
	echo "  byte5, Analyzing levels ...\n";
	$wconv_table .= generate_match_function($byte5, "byte5", $token);
	echo "  byte4, Analyzing levels ...\n";
	$wconv_table .= generate_match_function($byte4, "byte4", $token);
	echo "  byte3, Analyzing levels ...\n";
	$wconv_table .= generate_match_function($byte3, "byte3", $token);
	echo "  byte2, Analyzing levels ...\n";
	$wconv_table .= generate_match_function($byte2, "byte2", $token);
	echo "  ascii, Analyzing levels ...";
	$wconv_table .= generate_match_function($ascii, "ascii", $token);
	echo " done\n";

	return $wconv_table;
}

$wconv_t = get_function_group(__DIR__ . "/phrase_s2t.txt", "p_");
$wconv_t .= get_function_group(__DIR__ . "/word_s2t.txt", "w_");
file_put_contents(__DIR__ . "/../native/s2trad/wconv_gtable.cpp", $wconv_t);


?>
