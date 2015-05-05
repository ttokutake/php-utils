<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


/**
 * Throw the LogicException class if $boolean is false.
 *
 * @param boolean $boolean
 * @param string  $error_message
 * @param int     $added_depth
 */
function ensure($boolean, $error_message) {
   if (!(is_bool($boolean) && $boolean)) {
      throw new LogicException(is_string($error_message) ? $error_message : 'no message');
   }
}

/**
 * Throw RuntimeException.
 *
 * @param string $error_message
 */
function plague($error_message)
{
   throw new RuntimeException(is_string($error_message) ? $error_message : 'no message');
}


/**
 * Return the type of $var.
 */
function to_type($var)
{
   $type = gettype($var);
   switch ($type) {
      case 'NULL':
         $type = strtolower($type);
         break;
      case 'double':
         $type = 'float';
         break;
      case 'object':
         $type = get_class($var);
         break;
      case 'unknown type';
         $type = 'unknown';
         break;
   }
   return $type;
}

/**
 * Return the string transformed from $var.
 *
 * @param  mixed  $var
 * @return string
 */
function to_string($var)
{
   $type = gettype($var);
   switch ($type) {
      case 'boolean':
         $string = $var ? 'true' : 'false';
         break;
      case 'integer':
         $string = number_format($var);
         break;
      case 'double':
         $float  = number_format($var, 8);
         $string = preg_replace('/^(\d+\.\d[1-9]*)0+$/', '$1', $float);
         break;
      case 'string':
         $string = $var;
         break;
      case 'resource':
         $string = 'resource <' . get_resource_type($var) . '> #' . intval($var);
         break;
      case 'object':
         $string = 'object of ' . get_class($var);
         break;
      default:
         $string = to_type($var);
   }
   return $string;
}

/**
 * Return the string wrapped with double quotations if $var is string.
 *
 * @param  mixed $var
 * @return mixed
 */
function wrap_if_string($var)
{
   return is_string($var) ? "\"$var\"" : $var;
}


/**
 * Return non-negative integer.
 *
 * @param  mixed $var
 * @return int
 */
function force_non_negative($var) {
   return (is_int($var) && $var >= 0) ? $var : 0;
}

/**
 * Return the error message.
 *
 * @param  string $message
 * @param  int    $added_depth
 * @return string
 */
function error_message($message, $added_depth = 0)
{
   $backtrace = debug_backtrace();
   $depth     = 1 + force_non_negative($added_depth);
   $call      = isset($backtrace[$depth]) ? $backtrace[$depth] : $backtrace[count($backtrace) - 1];
   $class     = isset($call['class']) ? $call['class'] : ''       ;
   $type      = isset($call['type' ]) ? $call['type' ] : ''       ;
   $file      = isset($call['file' ]) ? $call['file' ] : 'unknown';
   $line      = isset($call['line' ]) ? $call['line' ] : 'unknown';
   $function  = $call['function'];
   return "{$class}{$type}$function(): $message [FILE: $file, LINE: $line]";
}
/**
 * Return the variable's violation message.
 *
 * @param  string $which_one
 * @param  string $expected
 * @param  string $actual
 * @param  int    $added_depth
 * @return string
 */
function variable_violation_message($which_one, $expected, $actual, $added_depth = 0)
{
   return error_message("$which_one must be $expected, actually $actual", 1 + force_non_negative($added_depth));
}

/**
 * Throw the LogicException if $var is null.
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_null(&$var, $which_one)
{
   if (is_null($var)) {
      throw new LogicException(variable_violation_message($which_one, 'non-null', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "boolean".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_bool(&$var, $which_one)
{
   if (!is_bool($var)) {
      throw new LogicException(variable_violation_message($which_one, 'boolean', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_int(&$var, $which_one)
{
   if (!is_int($var)) {
      throw new LogicException(variable_violation_message($which_one, 'integer', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "float".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_float(&$var, $which_one)
{
   if (!is_float($var)) {
      throw new LogicException(variable_violation_message($which_one, 'float', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "numeric".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_numeric(&$var, $which_one)
{
   if (!is_numeric($var)) {
      throw new LogicException(variable_violation_message($which_one, 'numeric', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "string".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_string(&$var, $which_one)
{
   if (!is_string($var)) {
      throw new LogicException(variable_violation_message($which_one, 'string', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "scalar".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_scalar(&$var, $which_one)
{
   if (!is_scalar($var)) {
      throw new LogicException(variable_violation_message($which_one, 'scalar', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "resource".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_resource(&$var, $which_one)
{
   if (!is_resource($var)) {
      throw new LogicException(variable_violation_message($which_one, 'resource', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "array".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_array(&$var, $which_one)
{
   if (!is_array($var)) {
      throw new LogicException(variable_violation_message($which_one, 'array', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "callable".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_callable(&$var, $which_one)
{
   if (!is_callable($var)) {
      throw new LogicException(variable_violation_message($which_one, 'Closure', to_type($var)));
   }
}

/**
 * Throw the LogicException if $var is not "object".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_object(&$var, $which_one)
{
   if (!is_object($var)) {
      throw new LogicException(variable_violation_message($which_one, 'object', to_type($var)));
   }
}


/**
 * Throw the LogicException if $var is "empty".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_empty(&$var, $which_one)
{
   if (empty($var)) {
      throw new LogicException(variable_violation_message($which_one, 'non-empty', to_string(wrap_if_string($var))));
   }
}

/**
 * Throw the LogicException if $var is not "positive integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_positive_int(&$var, $which_one)
{
   if (!(is_int($var) && $var > 0)) {
      throw new LogicException(variable_violation_message($which_one, 'positive integer', to_string(wrap_if_string($var))));
   }
}

/**
 * Throw the LogicException if $var is "negative integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_negative_int(&$var, $which_one)
{
   if (!(is_int($var) && $var >= 0)) {
      throw new LogicException(variable_violation_message($which_one, 'non-negative integer', to_string(wrap_if_string($var))));
   }
}

/**
 * Throw the LogicException if $var is not in elements of the array.
 *
 * @param mixed  &$var
 * @param array   $white_list
 * @param string  $which_one
 */
function ensure_in_array(&$var, array $white_list, $which_one)
{
   if (!in_array($var, $white_list)) {
      $white = implode(', ', $white_list);
      throw new LogicException(variable_violation_message($which_one, "in [$white]", to_string(wrap_if_string($var))));
   }
}

/**
 * Throw the LogicException if $var is in elements of the array.
 *
 * @param mixed  &$var
 * @param array   $black_list
 * @param string  $which_one
 */
function ensure_not_in_array(&$var, array $black_list, $which_one)
{
   if (in_array($var, $black_list)) {
      $black = implode(' ,', $black_list);
      throw new LogicException(variable_violation_message($which_one, "out of [$black]", to_string(wrap_if_string($var))));
   }
}
