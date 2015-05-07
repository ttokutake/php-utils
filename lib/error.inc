<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'cover.inc'));


/**
 * Throw the LogicException class if $boolean is false.
 *
 * @param boolean $boolean
 * @param string  $error_message
 */
function ensure($boolean, $error_message)
{
   if (!(is_bool($boolean) && $boolean)) {
      throw new LogicException(string_or_default($error_message, 'no message'));
   }
}

/**
 * Throw RuntimeException.
 *
 * @param string $error_message
 */
function plague($error_message)
{
   throw new RuntimeException(string_or_default($error_message, 'no message'));
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
   $depth     = 1 + force_non_negative_int($added_depth);
   $call      = isset($backtrace[$depth]) ? $backtrace[$depth] : $backtrace[count($backtrace) - 1];
   $class     = isset($call['class']) ? $call['class'] : ''       ;
   $type      = isset($call['type' ]) ? $call['type' ] : ''       ;
   $file      = isset($call['file' ]) ? $call['file' ] : 'unknown';
   $line      = isset($call['line' ]) ? $call['line' ] : 'unknown';
   $function  = $call['function'];
   $message   = string_or_default($message, 'no message');
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
   $which_one = string_or_default($which_one, 'The variable'  );
   $expected  = string_or_default($expected , 'expected one'  );
   $actual    = string_or_default($actual   , 'unexpected one');
   return error_message("$which_one must be $expected, actually $actual", 1 + force_non_negative_int($added_depth));
}


/**
 * Throw the DomainException if $var is not "boolean".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_bool(&$var, $which_one)
{
   if (!is_bool($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'boolean', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_int(&$var, $which_one)
{
   if (!is_int($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'integer', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "float".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_float(&$var, $which_one)
{
   if (!is_float($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'float', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "numeric".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_numeric(&$var, $which_one)
{
   if (!is_numeric($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'numeric', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "string".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_string(&$var, $which_one)
{
   if (!is_string($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'string', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "scalar".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_scalar(&$var, $which_one)
{
   if (!is_scalar($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'scalar', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "resource".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_resource(&$var, $which_one)
{
   if (!is_resource($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'resource', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "array".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_array(&$var, $which_one)
{
   if (!is_array($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'array', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not "callable".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_callable(&$var, $which_one)
{
   if (!is_callable($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'Closure', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is not instance of specified class.
 *
 * @param mixed  &$var
 * @param mixed   $class
 * @param string  $which_one
 */
function ensure_instance_of(&$var, $class, $which_one)
{
   $class_name = is_object($class) ? get_class($class) : $class;
   ensure_string($class_name, 'The second argument');

   if (!($var instanceof $class_name)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, "instance of $class_name", to_type($var), 1));
   }
}


/**
 * Throw the DomainException if $var is null.
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_null(&$var, $which_one)
{
   if (is_null($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'non-null', to_type($var), 1));
   }
}

/**
 * Throw the DomainException if $var is "empty".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_empty(&$var, $which_one)
{
   if (empty($var)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'non-empty', to_string(wrap_if_string($var)), 1));
   }
}

/**
 * Throw the DomainException if $var is not "positive integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_positive_int(&$var, $which_one)
{
   if (!(is_int($var) && $var > 0)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'positive integer', to_string(wrap_if_string($var)), 1));
   }
}

/**
 * Throw the DomainException if $var is "negative integer".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_non_negative_int(&$var, $which_one)
{
   if (!(is_int($var) && $var >= 0)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, 'non-negative integer', to_string(wrap_if_string($var)), 1));
   }
}

/**
 * Throw the DomainException if $var is not in elements of the array.
 *
 * @param mixed  &$var
 * @param array  &$white_list
 * @param string  $which_one
 */
function ensure_in_array(&$var, array &$white_list, $which_one)
{
   if (!in_array($var, $white_list)) {
      $which_one = string_or_default($which_one, 'The variable');
      $white = implode(', ', $white_list);
      throw new DomainException(variable_violation_message($which_one, "in [$white]", to_string(wrap_if_string($var)), 1));
   }
}

/**
 * Throw the DomainException if $var is in elements of the array.
 *
 * @param mixed  &$var
 * @param array  &$black_list
 * @param string  $which_one
 */
function ensure_not_in_array(&$var, array &$black_list, $which_one)
{
   if (in_array($var, $black_list)) {
      $which_one = string_or_default($which_one, 'The variable');
      $black = implode(' ,', $black_list);
      throw new DomainException(variable_violation_message($which_one, "out of [$black]", to_string(wrap_if_string($var)), 1));
   }
}


/**
 * Throw the BadFunctionCallException if $argc is less than $min.
 *
 * @param int $argc
 * @param int $min
 */
function ensure_argc_at_least($argc, $min)
{
   ensure_non_negative_int($argc, 'The first argument' );
   ensure_non_negative_int($min , 'The second argument');

   if ($argc < $min) {
      throw new BadFunctionCallException(error_message("Specify $min arguments at least, actually $argc arguments", 1));
   }
}

/**
 * Throw the BadFunctionCallException if $argc is more than $min.
 *
 * @param int $argc
 * @param int $max
 */
function ensure_argc_at_most($argc, $max)
{
   ensure_non_negative_int($argc, 'The first argument' );
   ensure_non_negative_int($max , 'The second argument');

   if ($argc > $max) {
      throw new BadFunctionCallException(error_message("Specify $max arguments at most, actually $argc arguments", 1));
   }
}
