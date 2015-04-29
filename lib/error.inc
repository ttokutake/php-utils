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
function ensure($boolean, $error_message, $added_depth = 0) {
   if (!$boolean) {
      if (is_callable($error_message)) {
         $error_message = $error_message(1 + ((is_int($added_depth) && $added_depth > 0) ? $added_depth : 0));
      }
      throw new LogicException($error_message);
   }
}

/**
 * Throw RuntimeException.
 *
 * @param string $error_message
 */
function plague($error_message)
{
   throw new RuntimeException(is_callable($error_message) ? $error_message() : $error_message);
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
         $string = 'instance of ' . get_class($var);
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
 * Return the error message caller object.
 *
 * @param  string  $message
 * @return Closure
 */
function error_message_caller($message)
{
   return function ($added_depth = 0) use($message) {
      $backtrace = debug_backtrace();
      $depth     = 1 + ((is_int($added_depth) && $added_depth > 0) ? $added_depth : 0);
      $call      = isset($backtrace[$depth]) ? $backtrace[$depth] : $backtrace[count($backtrace) - 1];
      $class     = isset($call['class']) ? $call['class'] : ''       ;
      $type      = isset($call['type' ]) ? $call['type' ] : ''       ;
      $file      = isset($call['file' ]) ? $call['file' ] : 'unknown';
      $line      = isset($call['line' ]) ? $call['line' ] : 'unknown';
      $function  = $call['function'];
      return "{$class}{$type}$function(): $message [FILE: $file, LINE: $line]";
   };
}
/**
 * Return the error message.
 *
 * @param  string $message
 * @return string
 */
function error_message($message)
{
   $caller = error_message_caller($message);
   return $caller(1);
}

/**
 * Return the variable's violation message caller.
 *
 * @param  string  $which_one
 * @param  string  $expected
 * @param  string  $actual
 * @return Closure
 */
function variable_violation_message_caller($which_one, $expected, $actual)
{
   return error_message_caller("$which_one must be $expected, actually $actual");
}
/**
 * Return the variable's violation message.
 *
 * @param  string $which_one
 * @param  string $expected
 * @param  string $actual
 * @return string
 */
function variable_violation_message($which_one, $expected, $actual)
{
   $caller = variable_violation_message_caller($which_one, $expected, $actual);
   return $caller(1);
}

/**
 * Throw the LogicException if $var is null.
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_null(&$var, $which_one)
{
   ensure(!is_null($var), variable_violation_message_caller($which_one, 'non-null', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "boolean".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_bool(&$var, $which_one)
{
   ensure(is_bool($var), variable_violation_message_caller($which_one, 'boolean', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_int(&$var, $which_one)
{
   ensure(is_int($var), variable_violation_message_caller($which_one, 'integer', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "float".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_float(&$var, $which_one)
{
   ensure(is_float($var), variable_violation_message_caller($which_one, 'float', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "numeric".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_numeric(&$var, $which_one)
{
   ensure(is_numeric($var), variable_violation_message_caller($which_one, 'numeric', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "string".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_string(&$var, $which_one)
{
   ensure(is_string($var), variable_violation_message_caller($which_one, 'string', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "scalar".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_scalar(&$var, $which_one)
{
   ensure(is_scalar($var), variable_violation_message_caller($which_one, 'scalar', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "resource".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_resource(&$var, $which_one)
{
   ensure(is_resource($var), variable_violation_message_caller($which_one, 'resource', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "array".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_array(&$var, $which_one)
{
   ensure(is_array($var), variable_violation_message_caller($which_one, 'array', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "callable".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_callable(&$var, $which_one)
{
   ensure(is_callable($var), variable_violation_message_caller($which_one, 'Closure', to_type($var)), 1);
}

/**
 * Throw the LogicException if $var is not "object".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_object(&$var, $which_one)
{
   ensure(is_object($var), variable_violation_message_caller($which_one, 'object', to_type($var)), 1);
}


/**
 * Throw the LogicException if $var is "empty".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_empty(&$var, $which_one)
{
   ensure(!empty($var), variable_violation_message_caller($which_one, 'non-empty', to_string(wrap_if_string($var))), 1);
}

/**
 * Throw the LogicException if $var is not "positive integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_positive_int(&$var, $which_one)
{
   ensure(is_int($var) && $var > 0, variable_violation_message_caller($which_one, 'positive integer', to_string(wrap_if_string($var))), 1);
}

/**
 * Throw the LogicException if $var is "negative integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_positive_int(&$var, $which_one)
{
   ensure(is_int($var) && $var >= 0, variable_violation_message_caller($which_one, 'non-positive integer', to_string(wrap_if_string($var))), 1);
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
   $white = implode(', ', $white_list);
   ensure(in_array($var, $white_list), variable_violation_message_caller($which_one, "in [$white]", to_string(wrap_if_string($var))), 1);
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
   $black = implode(' ,', $black_list);
   ensure(!in_array($var, $black_list), variable_violation_message_caller($which_one, "out of [$black]", to_string(wrap_if_string($var))), 1);
}
