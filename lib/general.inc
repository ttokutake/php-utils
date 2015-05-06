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
   ensure_string($file, 'The first argument');

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
   ensure_numeric($num, 'The first argument');

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
   ensure_numeric($num, 'The first argument');

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
   ensure_numeric($num, 'The first argument');

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
   ensure_int($first, 'The first argument' );
   ensure_int($last , 'The second argument');

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
   ensure_int($first, 'The first argument' );
   ensure_int($last , 'The second argument');

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
   ensure_callable($closure, 'The first argument');

   return function($var) use($closure) { return !$closure($var); };
}
