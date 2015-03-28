<?php

/**
 * Throw the LogicException class if $boolean is false.
 * @param  boolean $boolean
 * @param  string  $error_message
 */
function ensure($boolean, $error_message) {
   if (!$boolean) {
      throw new LogicException($error_message);
   }
}


/**
 * Judge if $num is in integer numbers.
 *
 * @param  mixed $num
 * @return boolean
 */
function in_z($num)
{
   ensure(is_numeric($num), __FUNCTION__ . "(): The first argument must be numeric, actually '$num'.");
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
   ensure(in_z($num), __FUNCTION__ . "(): The first argument must be integer, actually '$num'.");
   return $num % 2 == 1;
}

/**
 * Judge if $num is even.
 *
 * @param  mixed   $num
 * @return boolean
 */
function is_even($num)
{
   return !is_odd($num);
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
   return ($min <= $var && $var <= $max) ? true : false;
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
   ensure(is_integer($first), __FUNCTION__ . "(): the first argument must be integer, actually was '$first'.");
   ensure(is_integer($last ), __FUNCTION__ . "(): the second argument must be integer, actually was '$last'.");

   $array = array();
   for ($i = $first; $i <= $last; $i++) {
      $array[] = $i;
   }
   return $array;
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
   return array_reverse(incremental_range($last, $first));
}
