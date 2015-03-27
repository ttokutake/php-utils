<?php

function create_path(array $dirs)
{
   return implode(array_map(function ($dir) { return $dir . DIRECTORY_SEPARATOR; }, $dirs));
}

define('PATH_TO_LIB'  , create_path(array(__DIR__, 'lib'  )));
define('PATH_TO_CLASS', create_path(array(__DIR__, 'class')));
