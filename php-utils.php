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
   return array_reduce($dirs, function ($path, $dir) { return "$path$dir" . DIRECTORY_SEPARATOR; }, '');
}

define('PATH_TO_LIB_FOR_PHP_UTILS', create_path(array(__DIR__, 'lib')));

require_once PATH_TO_LIB_FOR_PHP_UTILS . 'general.inc'       ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'debug.inc'         ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'string.inc'        ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'array.inc'         ;
require_once PATH_TO_LIB_FOR_PHP_UTILS . 'array_of_array.inc';
