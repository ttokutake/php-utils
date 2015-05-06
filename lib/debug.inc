<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'cover.inc' ));
require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'error.inc' ));
require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'string.inc'));


/**
 * Return the string with system's line break.
 *
 * @param  mixed  $var;
 * @return string
 */
function withln($var)
{
   return to_string($var) . PHP_EOL;
}

/**
 * echo with a line break.
 *
 * @param mixed $var
 */
function echoln($var)
{
   echo withln($var);
}


/**
 * Return the pretty string of the variable.
 * Notice: For class, cannot read private scope and distinguish static methods.
 *
 * @param  mixed  $var
 * @param  string $row_prefix
 * @return string
 */
function pretty($var, $row_prefix = '')
{
   $indent      = '   ';
   $next_indent = $row_prefix . $indent;

   $calls         = debug_backtrace();
   $internal_call = isset($calls[1]) && $calls[1]['function'] === 'pretty';

   $pretty = $internal_call ? '' : $row_prefix;
   switch (gettype($var)) {
      case 'array':
         $pretties = array();
         foreach (array_keys($var) as $key) {
            $pretties[$key] = strval(wrap_if_string($key));
         }
         $lengths    = array_map(function($pre) {
               return array_reduce(mb_str_split($pre), function($len, $char) { return $len + (include_mb($char) ? 2 : 1); }, 0);
            }, $pretties);
         $max        = empty($lengths) ? 0 : max($lengths);
         $space_nums = array_map(function($len) use($max) { return $max - $len; }, $lengths);
         $spaces     = array_map(function($num) { return str_repeat(' ', $num); }, $space_nums);

         $pretty .= withln('[');
         foreach ($var as $key => $elem) {
            $pretty .= "$next_indent{$pretties[$key]}{$spaces[$key]} => " . pretty($elem, "$next_indent");
         }
         $pretty .= withln("$row_prefix]");
         break;
      case 'object':
         if (method_exists($var, '__toString')) {
            $pretty .= withln(strval($var));
         } else {
            $name              = get_class($var);
            $object_properties = get_object_vars($var);
            $static_properties = array_diff_assoc(get_class_vars($name), $object_properties);
            $methods           = get_class_methods($name);

            $pretty .= withln("object of $name {");
            $pretty .= "{$next_indent}object properties => " . pretty($object_properties, $next_indent);
            $pretty .= "{$next_indent}static properties => " . pretty($static_properties, $next_indent);
            $pretty .= "{$next_indent}methods           => " . pretty($methods          , $next_indent);
            $pretty .= withln("$row_prefix}");
         }
         break;
      default:
         $pretty .= withln(wrap_if_string($var));
   }

   return $pretty;
}

/**
 * Return var_export($var, true).
 *
 * @param  mixed  $var
 * @return string
 */
function var_detail($var)
{
   return var_export($var, true);
}

/**
 * Return print_r($var, true).
 *
 * @param  mixed  $var
 * @return string
 */
function print_detail($var)
{
   return print_r($var, true);
}


/**
 * Return the string enclosed by <pre> tags (and "<!--""-->").
 *
 * @param  string  $string
 * @param  boolean $comment_out
 * @return string
 */
function html_friendly($string, $comment_out = true)
{
   return withln(($comment_out ? '<!--' : '') . '<pre>') . $string . withln('</pre>' . ($comment_out ? '-->' : ''));
}
/**
 * Output html-friendly string with a line break.
 *
 * @param mixed   $var
 * @param boolean $comment_out
 */
function hf_echoln($var, $comment_out = true)
{
   echo html_friendly(withln($var), $comment_out);
}

/**
 * Output html-friendly pretty().
 *
 * @param mixed   $var
 * @param boolean $comment_out
 */
function hf_pretty($var, $comment_out = true)
{
   echo html_friendly(pretty($var), $comment_out);
}

/**
 * Output html-friendly var_export().
 *
 * @param mixed   $var
 * @param boolean $comment_out
 */
function hf_var_export($var, $comment_out = true)
{
   echo html_friendly(var_detail($var), $comment_out);
}

/**
 * Output html-friendly print_r().
 *
 * @param mixed   $var
 * @param boolean $comment_out
 */
function hf_print_r($var, $comment_out = true)
{
   echo html_friendly(print_detail($var), $comment_out);
}
