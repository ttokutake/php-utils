<?php

/**
 * Split the multibyte characters by num of former characters.
 *
 * @param  string               $str
 * @param  int                  $former_length
 * @return array(string,string)
 */
function split_at($str, $former_length, $encoding = 'UTF-8')
{
   $former = mb_substr($str,              0, $former_length, $encoding);
   $latter = mb_substr($str, $former_length,           null, $encoding);
   return [$former, $latter];
}
