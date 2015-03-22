<?php

/**
 * If $var's value is "defined" or not "null", return it.
 * Otherwise, return $default.
 * This function is for not outputting "PHP Notice".
 *
 * @param  &mixed $var
 * @param  mixed  $default
 * @return mixed  $var|$default
 */
function get_or_else(&$var, $default)
{
   return isset($var) ? $var : $default;
}

/**
 * The alias of get_or_else($var, null).
 *
 * @param  &mixed     $var
 * @return mixed|null $var|null
 */
function get_or_null(&$var)
{
   return get_or_else($var, null);
}

/**
 * Judge $var is in the range between $min and $max.
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
