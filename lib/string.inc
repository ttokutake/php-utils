<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'general.inc'));


/**
 * Split the multibyte characters by num of former characters.
 * If $at is negative, it means "num of latter characters" X "-1".
 *
 * @param  string          $str
 * @param  int             $at
 * @param  string          $encoding
 * @return [string,string]
 */
function split_at($str, $at, $encoding = 'UTF-8')
{
   ensure(is_string($str), type_violation_message('The first argument' ,  'string', $str));
   ensure(is_int($at)    , type_violation_message('The second argument', 'integer', $at ));

   $former = mb_substr($str,   0,  $at, $encoding);
   $latter = mb_substr($str, $at, null, $encoding);
   return array($former, $latter);
}
