<?php

/**
 * echo with LF
 *
 * @param mixed $var
 */
function echoln($var)
{
   echo "$var\n";
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
   if ($comment_out) echo '<!--';
   echo "<pre>\n";
   $echo($var);
   echo '</pre>';
   if ($comment_out) echo '-->';
   echo "\n";
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
