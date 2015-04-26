<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'string.inc'));


/**
 * Return the string with system's line break.
 *
 * @param  mixed  $var;
 * @return string
 */
function withln($var)
{
   return strval($var) . PHP_EOL;
}

/**
 * Echo with system's line break.
 *
 * @param mixed $var
 */
function echoln($var)
{
   echo withln($var);
}

/**
 * Return the pretty string of the variable.
 *
 * @param  mixed $var
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
         $pretty .= withln('[');
         foreach ($var as $key => $elem) {
            if (is_string($key)) {
               $key = wrap($key, "'");
            }
            $pretty .= "$next_indent($key) => " . pretty($elem, "$next_indent");
         }
         $pretty .= withln("$row_prefix]");
         break;
      case 'object':
         if (is_callable($var)) {
            $pretty .= withln('function');
         } else {
            $name              = get_class($var);
            $object_properties = get_object_vars($var);
            $static_properties = array_diff_assoc(get_class_vars($name), $object_properties);
            $methods           = get_class_methods($name);

            $pretty .= withln("class $name {");
            $pretty .= "{$next_indent}object properties => " . pretty($object_properties, $next_indent);
            $pretty .= "{$next_indent}static properties => " . pretty($static_properties, $next_indent);
            $pretty .= "{$next_indent}methods => "           . pretty($methods          , $next_indent);
            $pretty .= withln("$row_prefix}");
         }
         break;
      case 'NULL':
         $pretty .= withln('null');
         break;
      case 'boolean':
         $pretty .= withln($var ? 'true' : 'false');
         break;
      case 'integer':
         $pretty .= withln(number_format($var));
         break;
      case 'double':
         $float = number_format($var, 16);
         $pretty .= withln(preg_replace('/^(\d+\.\d)0+$/', '$1', $float));
         break;
      case 'string':
         $pretty .= withln(wrap($var, "'"));
         break;
      case 'resource':
         $pretty .= withln('resource');
         break;
      default:
         $pretty .= withln('unknown');
   }

   return $pretty;
}

/**
 * Output a variable with <pre></pre> (and "<!--""-->").
 * This function assume debug using browser.
 *
 * @param mixed    $var
 * @param callable $echo
 * @param boolean  $comment_out
 */
function debug_assuming_html($var, $echo, $comment_out = true)
{
   echoln(($comment_out ? '<!--' : '') . '<pre>');
   $echo($var);
   echoln('</pre>' . ($comment_out ? '-->' : ''));
}

/**
 * debug_assuming_html() by var_dump().
 *
 * @param mixed   $var
 * @param boolean $comment_out
 */
function var_dump_html($var, $comment_out = true)
{
   debug_assuming_html($var, 'var_dump', $comment_out);
}

/**
 * debug_assuming_html() by print_r().
 *
 * @param mixed   $var
 * @param boolean $comment_out
 */
function print_r_html($var, $comment_out = true)
{
   debug_assuming_html($var, 'print_r', $comment_out);
}

/**
 * var_export() to the log file.
 *
 * @param mixed $var
 */
function var_export_log($var)
{
   error_log(var_export($var, true));
}

/**
 * print_r() to the log file.
 *
 * @param mixed $var
 */
function print_r_log($var)
{
   error_log(print_r($var, true));
}
