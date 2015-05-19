<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'error.inc'  ));


/**
 * Return the string wrapped by $wrapper.
 *
 * @param  string $string
 * @param  string $wrapper
 * @return string
 */
function wrap($string, $wrapper)
{
   ensure_string($string , SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_string($wrapper, SUBJECT_FOR_SECOND_ARGUMENT);

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
   ensure_string($string, SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_string($tag   , SUBJECT_FOR_SECOND_ARGUMENT);
   ensure_string($class , SUBJECT_FOR_THIRD_ARGUMENT );

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
   ensure_string($glue, SUBJECT_FOR_FIRST_ARGUMENT);

   return array_reduce($pieces, function($carry, $piece) use($glue) { return "$carry$piece$glue"; }, '');
}


/**
 * Set encoding config for system and regex.
 *
 * @param string $encoding
 */
function set_jp_encoding($encoding = 'UTF-8')
{
   $enable_encodings = array('ISO-8859-1', 'ASCII', 'JIS', 'UTF-8', 'EUC-JP', 'SJIS');
   ensure_in_array($encoding, $enable_encodings, SUBJECT_FOR_FIRST_ARGUMENT);

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
   ensure_string($haystack, SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_string($needle  , SUBJECT_FOR_SECOND_ARGUMENT);

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
   ensure_string($haystack, SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_string($needle  , SUBJECT_FOR_SECOND_ARGUMENT);

   return $needle === '' || mb_strrpos($haystack, $needle, 0) === (mb_strlen($haystack) - mb_strlen($needle));
}

/**
 * Judge if any one of $needles is in $haystack.
 *
 * @param  string  $haystack
 * @param  array   $needles
 * @return boolean
 */
function str_search($haystack, array $needles)
{
   ensure_string($haystack, SUBJECT_FOR_FIRST_ARGUMENT);

   $escaped = array_map(function($n) { return preg_quote($n, '/'); }, $needles);
   return preg_match('/(' . implode('|', $escaped) . ')/u', $haystack) === 1;
}

/**
 * Return first only version of str_replace().
 *
 * @param  string $search
 * @param  string $replace
 * @param  string $subject
 * @return string
 */
function str_replace_first($search, $replace, $subject)
{
   ensure_string($search , SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_string($replace, SUBJECT_FOR_SECOND_ARGUMENT);
   ensure_string($subject, SUBJECT_FOR_THIRD_ARGUMENT );

   return preg_replace('/' . preg_quote($search, '/') . '/u', $replace, $subject, 1);
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
   ensure_string($string, SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_int   ($at    , SUBJECT_FOR_SECOND_ARGUMENT);

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
function mb_str_split($string, $width = 1)
{
   ensure_string      ($string, SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_positive_int($width , SUBJECT_FOR_SECOND_ARGUMENT);

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
   ensure_string($string, SUBJECT_FOR_FIRST_ARGUMENT);

   return preg_match('/^\s*$/u', $string) === 1;
}

/**
 * Return the string whose both ends are trimmed.
 *
 * @param  string $string
 * @return string
 */
function mb_trim($string)
{
   ensure_string($string, SUBJECT_FOR_FIRST_ARGUMENT);

   return preg_replace('/(^\s+|\s+$)/u', '', $string);
}

/**
 * Judge if $string include multibyte charactors.
 *
 * @param  string  $string
 * @return boolean
 */
function have_mb_char($string)
{
   ensure_string($string, SUBJECT_FOR_FIRST_ARGUMENT);

   return strlen($string) != mb_strlen($string);
}
