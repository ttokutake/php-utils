<?php

function create_path(array $dirs_and_file, $dir_only = false)
{
   return implode(DIRECTORY_SEPARATOR, $dirs_and_file) . ($dir_only ? DIRECTORY_SEPARATOR : '');
}

function require_lib($file)
{
   require_once(create_path(array(__DIR__, 'lib', $file)));
}

function require_class($file)
{
   require_once(create_path(array(__DIR__, 'class', $file)));
}
