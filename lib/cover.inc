<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


/**
 * Return string or default string.
 *
 * @param  mixed  $var
 * @param  string $default
 * @return string
 */
function string_or_default($var, $default)
{
   return is_string($var) ? $var : (is_string($default) ? $default : '');
}

/**
 * Return non-negative integer.
 *
 * @param  mixed $var
 * @return int
 */
function force_non_negative_int($var)
{
   return (is_int($var) && $var >= 0) ? $var : 0;
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
