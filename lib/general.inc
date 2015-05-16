<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'error.inc'));


/**
 * Run "require_once" that is equal to "require_once __DIR__ . DIRECTORY_SEPARATOR . $file;".
 * Notice: If you want to create global variables, use $GLOBAL.
 *
 * @param string $file
 */
function require_relative($file)
{
   ensure_string($file, SUBJECT_FOR_FIRST_ARGUMENT);

   list($first) = debug_backtrace();
   $base_dir    = dirname($first['file']);

   require_once $base_dir . DIRECTORY_SEPARATOR . $file;
}


/**
 * Judge if $num is in integer numbers.
 *
 * @param  mixed   $num
 * @return boolean
 */
function in_z($num)
{
   ensure_numeric($num, SUBJECT_FOR_FIRST_ARGUMENT);

   return preg_match('/^-?\d+(?:\.0*)?$/', $num) === 1;
}

/**
 * Judge if $num is odd.
 *
 * @param  mixed   $num
 * @return boolean
 */
function is_odd($num)
{
   ensure_numeric($num, SUBJECT_FOR_FIRST_ARGUMENT);

   return in_z($num) && abs($num % 2) == 1;
}

/**
 * Judge if $num is even.
 *
 * @param  mixed   $num
 * @return boolean
 */
function is_even($num)
{
   ensure_numeric($num, SUBJECT_FOR_FIRST_ARGUMENT);

   return in_z($num) && abs($num % 2) == 0;
}

/**
 * Judge if $var is in the range between $min and $max.
 *
 * @param  mixed   $var
 * @param  mixed   $min
 * @param  mixed   $max
 * @return boolean
 */
function between($var, $min, $max)
{
   return $min <= $var && $var <= $max;
}

/**
 * Return the array which each integer is incremental.
 *
 * @param  int   $first
 * @param  int   $last
 * @return array
 */
function incremental_range($first, $last)
{
   ensure_int($first, SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_int($last , SUBJECT_FOR_SECOND_ARGUMENT);

   return $first <= $last ? range($first, $last) : array();
}

/**
 * Return the array which each integer is decremental.
 *
 * @param  int   $first
 * @param  int   $last
 * @return array
 */
function decremental_range($first, $last)
{
   ensure_int($first, SUBJECT_FOR_FIRST_ARGUMENT );
   ensure_int($last , SUBJECT_FOR_SECOND_ARGUMENT);

   return array_reverse(incremental_range($last, $first));
}


/**
 * Return the Closure object which is equal to reversed $closure.
 *
 * @param Closure $closure
 * @param Closure
 */
function reverse_closure($closure)
{
   ensure_callable($closure, SUBJECT_FOR_FIRST_ARGUMENT);

   return function($var) use($closure) { return !$closure($var); };
}
