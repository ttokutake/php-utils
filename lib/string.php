<?php

/**
 * Split the multibyte characters by num of former characters.
 * If $at is negative, it means "num of latter characters" X "-1".
 *
 * @param  string               $str
 * @param  int                  $at
 * @return array(string,string)
 */
function split_at($str, $at, $encoding = 'UTF-8')
{
   $former = mb_substr($str,   0,  $at, $encoding);
   $latter = mb_substr($str, $at, null, $encoding);
   return [$former, $latter];
}
