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
 * Return the message with debug information.
 *
 * @param  string $message
 * @param  int    $added_depth
 * @return string
 */
function append_debug_info($message, $added_depth = 0)
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
   return append_debug_info("$which_one must be $expected, actually $actual", 1 + force_non_negative_int($added_depth));
}


const SUBJECT_FOR_FIRST_ARGUMENT  = 'The first argument';
const SUBJECT_FOR_SECOND_ARGUMENT = 'The second argument';
const SUBJECT_FOR_THIRD_ARGUMENT  = 'The third argument';
const SUBJECT_FOR_FOURTH_ARGUMENT = 'The fourth argument';
const SUBJECT_FOR_FIFTH_ARGUMENT  = 'The fifth argument';

/**
 * Throw the DomainException if $var is not "boolean".
 *
 * @param mixed  &$var
 * @param string  $which_one
 */
function ensure_bool(&$var, $which_one)
{
   if (!is_bool($var)) {
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
      throw new DomainException(variable_violation_message($which_one, 'Closure', to_type($var), 1));
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
 * Throw the DomainException if $var is not less than or equal to $min and greater than or equal to $max.
 *
 * @param mixed  &$var
 * @param mixed   $min
 * @param mixed   $max
 * @param string  $which_one
 */
function ensure_between(&$var, $min, $max, $which_one)
{
   if (!(is_scalar($var) && $min <= $var && $var <= $max)) {
      $which_one = string_or_default($which_one, 'The variable');
      throw new DomainException(variable_violation_message($which_one, "gte $min or lte $max", to_string(wrap_if_string($var)), 1));
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
      $black = implode(' ,', $black_list);
      throw new DomainException(variable_violation_message($which_one, "out of [$black]", to_string(wrap_if_string($var)), 1));
   }
}


/**
 * Throw the DomainException if $var is not one of objects of specified classes.
 *
 * @param mixed  &$var
 * @param string  $which_one
 * @param mixed   $class
 * @param mixed   ...
 */
function ensure_instance_of(&$var, $which_one, $class)
{
   $classes     = array_slice(func_get_args(), 2); // should use array_drop()
   $class_names = array_map(function ($class) { return is_object($class) ? get_class($class) : $class; }, $classes);
   foreach ($class_names as $class_name) {
      ensure_string($class_name, 'Arguments following second one');
      if (!(class_exists($class_name) || interface_exists($class_name))) {
         throw new DomainException(append_debug_info("class or interface \"$class_name\" is not defined"));
      }
   }

   foreach ($class_names as $class_name) { // should use array_exist() or array_for_all()
      if ($var instanceof $class_name) {
         return;
      }
   }
   $joined = implode(', ', $class_names);
   throw new DomainException(variable_violation_message($which_one, "one of instances [$joined]", to_type($var), 1));
}
