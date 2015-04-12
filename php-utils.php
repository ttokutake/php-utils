<?php

function create_path(array $dirs)
{
   return array_reduce($dirs, function ($path, $dir) { return $path . $dir . DIRECTORY_SEPARATOR; }, '');
}

function demand_lib($php_file)
{
   require_once create_path(array(__DIR__, 'lib')) . $php_file;
}

demand_lib('general.inc'       );
demand_lib('debug.inc'         );
demand_lib('string.inc'        );
demand_lib('array.inc'         );
demand_lib('array_of_array.inc');
