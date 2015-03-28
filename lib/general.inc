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
 * Return the message for function argument's type violation.
 *
 * @param  string $function_name
 * @param  string $which_one
 * @param  string $expected_type
 * @param  mixed  &$var
 * @return string
 */
function type_violation_message($function_name, $which_one, $expected_type, &$var)
{
   return "$function_name(): $which_one argument must be $expected_type, actually '" . gettype($var) . "'.";
}


/**
 * Judge if $num is in integer numbers.
 *
 * @param  mixed $num
 * @return boolean
 */
function in_z($num)
{
   // Actually, type_violation_message() should be lazy.
   ensure(is_numeric($num), type_violation_message(__FUNCTION__, 'first', 'numeric', $num));
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
   return in_z($num) ? ($num % 2 == 1) : false;
}

/**
 * Judge if $num is even.
 *
 * @param  mixed   $num
 * @return boolean
 */
function is_even($num)
{
   return in_z($num) ? ($num % 2 == 0) : false;
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
   ensure(is_integer($first), type_violation_message(__FUNCTION__,  'first', 'integer', $first));
   ensure(is_integer($last ), type_violation_message(__FUNCTION__, 'second', 'integer', $last ));

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
