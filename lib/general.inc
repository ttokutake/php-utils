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
 * But global variables can't be created.
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
 * Return the message for variable's violation.
 *
 * @param  string $function_name
 * @param  string $which_one
 * @param  string $expected
 * @param  string $value
 * @return string
 */
function variable_violation_message($which_one, $expected_type, $value, $added_trace_depth = 0)
{
   $backtrace = debug_backtrace();
   $depth     = 1 + $added_trace_depth;
   $call      = isset($backtrace[$depth]) ? $backtrace[$depth] : array();
   $class     = isset($call['class'   ]) ? $call['class'   ] : '';
   $type      = isset($call['type'    ]) ? $call['type'    ] : '';
   $function  = isset($call['function']) ? $call['function'] : '';
   $file      = isset($call['file'    ]) ? $call['file'    ] : '';
   $line      = isset($call['line'    ]) ? $call['line'    ] : '';
   return "{$class}{$type}$function(): $which_one must be $expected_type, actually '$value' [FILE: $file, LINE: $line]";
}

/**
 * Return the message for variable's type violation.
 *
 * @param  string $function_name
 * @param  string $which_one
 * @param  string $expected_type
 * @param  mixed  &$var
 * @return string
 */
function type_violation_message($which_one, $expected_type, &$var, $added_trace_depth = 0)
{
   return variable_violation_message($which_one, $expected_type, gettype($var), 1 + $added_trace_depth);
}


/**
 * Judge if $num is in integer numbers.
 *
 * @param  mixed $num
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
 * @return array
 */
function incremental_range($first, $last)
{
   ensure(is_integer($first), type_violation_message('The first argument' , 'integer', $first));
   ensure(is_integer($last ), type_violation_message('The second argument', 'integer', $last ));

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
