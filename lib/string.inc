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
 * Return the string wrapped by $wrapper.
 *
 * @param  string $string
 * @param  string $wrapper
 * @return string
 */
function wrap($string, $wrapper)
{
   ensure_string($string , 'The first argument' );
   ensure_string($wrapper, 'The second argument');

   return "$wrapper$string$wrapper";
}

/**
 * Return the string wrapped with html tags.
 *
 * @param  string $string
 * @param  string $tag
 * @param  string $class
 * @return string
 */
function wrap_by_tag($string, $tag, $class = '')
{
   ensure_string($string, 'The first argument' );
   ensure_string($tag   , 'The second argument');
   ensure_string($class , 'The third argument' );

   $attr = empty($class) ? $class : " class=\"$class\"";
   return "<$tag$attr>$string</$tag>";
}

/**
 * Return the string which is joined from $pieces with $glue.
 *
 * @param  string $glue
 * @param  array  $pieces
 * @return string
 */
function follow_join($glue, array $pieces)
{
   ensure_string($glue, 'The first argument');

   return array_reduce($pieces, function ($carry, $piece) use($glue) { return "$carry$piece$glue"; }, '');
}


/**
 * Set encoding config for system and regex.
 *
 * @param string $encoding
 */
function set_encoding($encoding = 'UTF-8')
{
   $enable_encodings = array('ISO-8859-1', 'ASCII', 'JIS', 'UTF-8', 'EUC-JP', 'SJIS');
   ensure_in_array($encoding, $enable_encodings, 'The first argument');

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
   ensure_string($haystack, 'The first argument' );
   ensure_string($needle  , 'The second argument');

   return $needle === '' || strpos($haystack, $needle) === 0;
}

/**
 * Judge if $haystack ends with $needle.
 *
 * @param  string  $haystack
 * @param  string  $needle
 * @return boolean
 */
function end_with($haystack, $needle)
{
   ensure_string($haystack, 'The first argument' );
   ensure_string($needle  , 'The second argument');

   return $needle === '' || mb_strrpos($haystack, $needle, 0) === (mb_strlen($haystack) - mb_strlen($needle));
}


/**
 * Split the multibyte characters by num of former characters.
 * If $at is negative, it means "num of latter characters" X "-1".
 *
 * @param  string          $string
 * @param  int             $at
 * @return [string,string]
 */
function split_at($string, $at)
{
   ensure_string($string, 'The first argument' );
   ensure_int   ($at    , 'The second argument');

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
   ensure_string      ($string, 'The first argument' );
   ensure_positive_int($width , 'The second argument');

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
   ensure_string($string, 'The first argument');

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
   ensure_string($string, 'The first argument');

   return preg_replace('/(^\s+|\s+$)/u', '', preg_quote($string, '/'));
}
