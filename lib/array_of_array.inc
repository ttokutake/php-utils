<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'array.inc'  ));
require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'general.inc'));


/**
 * Return the transposed matrix
 *
 * @param  array $matrix
 * @return array
 */
function aoa_transpose(array $matrix)
{
   $transposed = array();
   foreach ($matrix as $r_key => $row) {
      ensure(is_array($row), type_violation_message('Each argument', 'array', $row));
      foreach ($row as $c_key => $entry) {
         $transposed[$c_key][$r_key] = $entry;
      }
   }
   return $transposed;
}


/**
 * Return the array of elements for specified key.
 *
 * @param  array      $aoa
 * @param  int|string $key
 * @return array
 */
function aoa_values(array $aoa, $key)
{
   ensure(is_scalar($key), type_violation_message('The second argument', 'scalar', $key));

   return array_map(function ($array) use($key) { return array_get($array, $key); }, $aoa);
}

/**
 * Return the sum of elements for specified key.
 *
 * @param  array      $aoa
 * @param  int|string $key
 * @return numeric
 */
function aoa_sum(array $aoa, $key)
{
   ensure(is_scalar($key), type_violation_message('The second argument', 'scalar', $key));

   return array_reduce($aoa, function ($sum, $array) use($key) { return $sum + array_get_or_else($array, $key, 0); }, 0);
}

/**
 * Return the AoA which sorted by an array value of specified key.
 *
 * @param  array      $aoa
 * @param  int|string $key
 * @return array
 */
function aoa_sort(array $aoa, $key, $order = SORT_ASC, $option = SORT_REGULAR)
{
   ensure(is_scalar($key), type_violation_message('The second argument', 'scalar', $key));

   array_multisort(aoa_values($aoa, $key), $order, $option, $aoa);
   return $aoa;
}

/**
 * Return the AoA which each key is an array value of specified key.
 *
 * @param  array      $aoa
 * @param  int|string $key
 * @return array
 */
function aoa_associate(array $aoa, $key)
{
   ensure(is_scalar($key), type_violation_message('The second argument', 'scalar', $key));

   $filtered = array_filter($aoa, function ($array) use($key) { return array_key_exists($key, $array); });

   $associated = array();
   foreach ($filtered as $array) {
      $value = $array[$key];
      ensure(is_scalar($value) || is_null($value), type_violation_message('The value of specified key', 'scalar or null', $value));
      unset($array[$key]);
      $associated[$value] = $array;
   }
   return $associated;
}
