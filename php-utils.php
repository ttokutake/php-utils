<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


/**
 * Return the path with DIRECTORY_SEPARATOR.
 *
 * @param  array $dirs
 * @return string
 */
function create_path(array $dirs)
{
   return array_reduce($dirs, function ($path, $dir) { return $path . $dir . DIRECTORY_SEPARATOR; }, '');
}

/**
 * Run "require_once" that is equal to "require_once __DIR__ . $path_to_file;".
 * But global variables can't be created.
 *
 * @param  string|array $path_to_file
 */
function require_relative($path_to_file)
{
   $backtrace = debug_backtrace();
   $first     = reset($backtrace);
   $base      = dirname($first['file']);

   if (is_array($path_to_file)) {
      $path_to_file = implode(DIRECTORY_SEPARATOR, $path_to_file);
   }

   require_once $base . DIRECTORY_SEPARATOR . $path_to_file;
}

define('PATH_TO_LIB_FOR_PHP_UTILS', create_path(array(__DIR__, 'lib')));

require_once PATH_TO_LIB_FOR_PHP_UTILS . 'general.inc'       ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'debug.inc'         ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'string.inc'        ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'array.inc'         ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'array_of_array.inc';
