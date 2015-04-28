<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


/**
 * Run "require_once" that is equal to "require_once __DIR__ . $path_to_file;".
 * Notice: global variables can't be created.
 *
 * @param  string|array $path_to_file
 */
function require_relative($path_to_file)
{
   list($first) = debug_backtrace();
   $base        = dirname($first['file']);

   if (is_array($path_to_file)) {
      $path_to_file = implode(DIRECTORY_SEPARATOR, $path_to_file);
   }

   require_once $base . DIRECTORY_SEPARATOR . $path_to_file;
}


/**
 * Throw the LogicException class if $boolean is false.
 *
 * @param boolean $boolean
 * @param string  $error_message
 */
function ensure($boolean, $error_message) {
   if (!$boolean) {
      throw new LogicException($error_message);
   }
}

/**
 * Return the message for an error.
 *
 * @param  string $message
 * @param  int    $added_trace_depth
 * @return string
 */
function error_message($message, $added_trace_depth = 0)
{
   $backtrace = debug_backtrace();
   $depth     = 1 + $added_trace_depth;
   $call      = isset($backtrace[0     ]) ? $backtrace[0     ] : array();
   $call      = isset($backtrace[$depth]) ? $backtrace[$depth] : $call  ;
   $class     = isset($call['class'   ]) ? $call['class'   ] : '';
   $type      = isset($call['type'    ]) ? $call['type'    ] : '';
   $function  = isset($call['function']) ? $call['function'] : '';
   $file      = isset($call['file'    ]) ? $call['file'    ] : '';
   $line      = isset($call['line'    ]) ? $call['line'    ] : '';
   return "{$class}{$type}$function(): $message [FILE: $file, LINE: $line]";
}

/**
 * Return the message for variable's violation.
 *
 * @param  string $which_one
 * @param  string $expected
 * @param  string $value
 * @param  int    $added_trace_depth
 * @return string
 */
function variable_violation_message($which_one, $expected_type, $value, $added_trace_depth = 0)
{
   return error_message("$which_one must be $expected_type, actually '$value'", 1 + $added_trace_depth);
}

/**
 * Return the message for variable's type violation.
 *
 * @param  string $which_one
 * @param  string $expected_type
 * @param  mixed  &$var
 * @param  int    $added_trace_depth
 * @return string
 */
function type_violation_message($which_one, $expected_type, &$var, $added_trace_depth = 0)
{
   $actual_type = is_object($var) ? get_class($var) : gettype($var);
   return variable_violation_message($which_one, $expected_type, $actual_type, 1 + $added_trace_depth);
}

/**
 * Throw the LogicException if $var is null.
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_null(&$var, $which_one)
{
   ensure(!is_null($var), type_violation_message($which_one, '"non-null"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "boolean".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_bool(&$var, $which_one)
{
   ensure(is_bool($var), type_violation_message($which_one, '"boolean"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_int(&$var, $which_one)
{
   ensure(is_int($var), type_violation_message($which_one, '"integer"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "float".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_float(&$var, $which_one)
{
   ensure(is_float($var), type_violation_message($which_one, '"float"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "numeric".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_numeric(&$var, $which_one)
{
   ensure(is_numeric($var), type_violation_message($which_one, '"numeric"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "string".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_string(&$var, $which_one)
{
   ensure(is_string($var), type_violation_message($which_one, '"string"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "scalar".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_scalar(&$var, $which_one)
{
   ensure(is_scalar($var), type_violation_message($which_one, '"scalar"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "resource".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_resource(&$var, $which_one)
{
   ensure(is_resource($var), type_violation_message($which_one, '"resource"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "array".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_array(&$var, $which_one)
{
   ensure(is_array($var), type_violation_message($which_one, '"array"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "callable".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_callable(&$var, $which_one)
{
   ensure(is_callable($var), type_violation_message($which_one, '"callable"', $var, 1));
}

/**
 * Throw the LogicException if $var is not "object".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_object(&$var, $which_one)
{
   ensure(is_object($var), type_violation_message($which_one, '"object"', $var, 1));
}


/**
 * Throw RuntimeException.
 *
 * @param string $message
 */
function plague($message)
{
   throw new RuntimeException($message);
}


/**
 * Return $var if $var is not null..
 * Otherwise, return $default.
 * Notice: Use array_get_non_null() for an element of 'array'.
 *
 * @param  mixed $var
 * @param  mixed $default
 * @return mixed $var|$default
 */
function get_non_null($var, $default)
{
   return isset($var) ? $var : $default;
}

/**
 * Return $var if $var is not empty.
 * Otherwise, return $default.
 * Notice: Use array_get_non_empty() for an element of 'array'.
 *
 * @param  mixed $var
 * @param  mixed $default
 * @return mixed $var|$default
 */
function get_non_empty($var, $default)
{
   return empty($var) ? $default : $var;
}


/**
 * Judge if $num is in integer numbers.
 *
 * @param  mixed   $num
 * @param  int     $added_trace_depth
 * @return boolean
 */
function in_z($num, $added_trace_depth = 0)
{
   // Actually, type_violation_message() should be lazy.
   ensure(is_numeric($num), type_violation_message('The first argument', 'numeric', $num, $added_trace_depth));
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
   return in_z($num, 1) ? ($num % 2 == 1) : false;
}

/**
 * Judge if $num is even.
 *
 * @param  mixed   $num
 * @return boolean
 */
function is_even($num)
{
   return in_z($num, 1) ? ($num % 2 == 0) : false;
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
 * @param  int   $added_trace_depth
 * @return array
 */
function incremental_range($first, $last, $added_trace_depth = 0)
{
   ensure(is_integer($first), type_violation_message('The first argument' , 'integer', $first, $added_trace_depth));
   ensure(is_integer($last ), type_violation_message('The second argument', 'integer', $last , $added_trace_depth));

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
   return array_reverse(incremental_range($last, $first, 1));
}
