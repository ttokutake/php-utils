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
 * Judge if the class has "__toString" method.
 *
 * @param  string  $instance
 * @return boolean
 */
function has_toString($instance)
{
   return method_exists($instance, '__toString');
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
      case 'NULL':
         $string = strtolower($type);
         break;
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
      case 'array':
         $string = $type;
         break;
      case 'object':
         $string = has_toString($var) ? strval($var) : 'instance of ' . get_class($var);
         break;
      default:
         $string = 'unknown';
   }
   return $string;
}

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
         if (has_toString($var)) {
            $pretty .= withln(strval($var));
         } else {
            $name              = get_class($var);
            $object_properties = get_object_vars($var);
            $static_properties = array_diff_assoc(get_class_vars($name), $object_properties);
            $methods           = get_class_methods($name);

            $pretty .= withln("instance of $name {");
            $pretty .= "{$next_indent}instance properties => " . pretty($object_properties, $next_indent);
            $pretty .= "{$next_indent}static properties => "   . pretty($static_properties, $next_indent);
            $pretty .= "{$next_indent}methods => "             . pretty($methods          , $next_indent);
            $pretty .= withln("$row_prefix}");
         }
         break;
      case 'string':
         $pretty .= withln(wrap($var, "'"));
         break;
      default:
         $pretty .= withln($var);
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
