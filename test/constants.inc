<?php

function create_path(array $array)
{
   return array_reduce($array, function ($path, $dir) { return $dir . DIRECTORY_SEPARATOR; }, '');
}

define('PATH_TO_LIB', create_path([__DIR__, '..', 'lib']));
