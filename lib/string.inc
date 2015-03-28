<?php

require_once(implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'mandatory.inc']));
require_lib('general.inc');

/**
 * Split the multibyte characters by num of former characters.
 * If $at is negative, it means "num of latter characters" X "-1".
 *
 * @param  string               $str
 * @param  int                  $at
 * @param  string               $encoding
 * @return array(string,string)
 */
function split_at($str, $at, $encoding = 'UTF-8')
{
   ensure(is_string($str), type_violation_message(__FUNCTION__, 'The first argument',  'string', $str));
   ensure(is_int($at)    , type_violation_message(__FUNCTION__, 'The second argument', 'integer', $at ));

   $former = mb_substr($str,   0,  $at, $encoding);
   $latter = mb_substr($str, $at, null, $encoding);
   return array($former, $latter);
}
