<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'general.inc'));


/**
 * Return the string which is joined from $pieces with $glue.
 *
 * @param  string $glue
 * @param  array  $pieces
 * @return string
 */
function follow_join($glue, array $pieces)
{
   ensure(is_string($glue), type_violation_message('The first argument', 'string', $glue));

   return array_reduce($pieces, function ($carry, $piece) use($glue) { return "$carry$piece$glue"; }, '');
}


/**
 * Set encoding config for system and regex.
 *
 * @param string $encoding
 */
function set_encoding($encoding = 'UTF-8') {
   mb_internal_encoding($encoding);
   mb_regex_encoding($encoding);
}


/**
 * Judge if $haystack starts with $needle.
 *
 * @param  string  $haystack
 * @param  string  $needle
 * @return boolean
 */
function start_with($haystack, $needle)
{
   ensure(is_string($haystack), type_violation_message('The first argument' , 'string', $haystack));
   ensure(is_string($needle  ), type_violation_message('The second argument', 'string', $needle  ));

   return $needle === '' || strpos($haystack, $needle) === 0;
}

/**
 * Judge if $haystack ends with $needle.
 */
function end_with($haystack, $needle)
{
   ensure(is_string($haystack), type_violation_message('The first argument' , 'string', $haystack));
   ensure(is_string($needle  ), type_violation_message('The second argument', 'string', $needle  ));

   return $needle === '' || mb_strrpos($haystack, $needle, 0) === (mb_strlen($haystack) - mb_strlen($needle));
}


/**
 * Split the multibyte characters by num of former characters.
 * If $at is negative, it means "num of latter characters" X "-1".
 *
 * @param  string          $string
 * @param  int             $at
 * @param  string          $encoding
 * @return [string,string]
 */
function split_at($string, $at)
{
   ensure(is_string($string), type_violation_message('The first argument' ,  'string', $string));
   ensure(is_int($at)       , type_violation_message('The second argument', 'integer', $at    ));

   $former = mb_substr($string,   0,  $at);
   $latter = mb_substr($string, $at, null);
   return array($former, $latter);
}

/**
 * Return the array of strings which arg split with $witdh.
 *
 * @param  string $string
 * @param  int    $width
 * @return array
 */
function mb_str_split($string, $width)
{
   ensure(is_string($string), type_violation_message('The first argument', 'string', $string));
   ensure(is_int($width) && $width > 0, variable_violation_message('The second argument', 'positive integer', $width));

   $split  = array();
   $length = mb_strlen($string);
   for ($from = 0; $from < $length; $from += $width) {
      $split[] = mb_substr($string, $from, $width);
   }
   return $split;
}


/**
 * Judge if $string is blank.
 *
 * @param  $string
 * @return boolean
 */
function is_blank($string)
{
   ensure(is_string($string), type_violation_message('The first argument' ,  'string', $string));

   return preg_match('/^\s*$/u', preg_quote($string, '/')) === 1 ? true : false;
}

/**
 * Return the string whose both ends are trimmed.
 *
 * @param  string $string
 * @return string
 */
function mb_trim($string)
{
   ensure(is_string($string), type_violation_message('The first argument' ,  'string', $string));

   return preg_replace('/(^\s+|\s+$)/u', '', preg_quote($string, '/'));
}
