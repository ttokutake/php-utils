<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'error.inc'));
require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'array.inc'));


/**
 * Return the array set the value.
 *
 * @param  array $aoa
 * @param  array $keys
 * @param  mixed $value
 * @return array
 */
function aoa_set(array $aoa, array $keys, $value)
{
   ensure_non_empty($keys, 'The second argument');

   $pointer = &$aoa;
   foreach ($keys as $key) {
      ensure_scalar($key, 'Each element of the second argument');
      if (!(is_array($pointer) || is_null($pointer))) {
         break;
      }
      $pointer = &$pointer[$key];
   }
   $pointer = $value;
   return $aoa;
}

/**
 * Return the array unset the value.
 *
 * @param  array $aoa
 * @param  array $keys
 * @return array
 */
function aoa_unset(array $aoa, array $keys)
{
   ensure_non_empty($keys, 'The second argument');

   $pointer = &$aoa;
   list($init, $last) = array_depeditate($keys);
   ensure_scalar($last, 'Each element of the second argument');
   foreach ($init as $key) {
      ensure_scalar($key, 'Each element of the second argument');
      if (!(is_array($pointer) && array_key_exists($key, $pointer))) {
         break;
      }
      $pointer = &$pointer[$key];
   }
   unset($pointer[$last]);
   return $aoa;
}

/**
 * Return the array collected by specified key.
 *
 * @param  array $aoa
 * @param  mixed $key
 * @return array
 */
function aoa_collect(array $aoa, $key)
{
   $collected = array();
   foreach ($aoa as $k => $v) {
      if ($k === $key) {
         $collected[] = $v;
      } else if (is_array($v)) {
         $collected = array_merge($collected, aoa_collect($v, $key));
      }
   }
   return $collected;
}


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
      ensure_array($row, 'Each element of the first argument');
      foreach ($row as $c_key => $entry) {
         $transposed[$c_key][$r_key] = $entry;
      }
   }
   return $transposed;
}


/**
 * Return the array of elements for specified key.
 *
 * @param  array  $aoa
 * @param  scalar $key
 * @return array
 */
function aoa_values(array $aoa, $key)
{
   ensure_scalar($key, 'The second argument');

   return array_map(function($array) use($key) { return array_get($array, $key); }, $aoa);
}

/**
 * Return the sum of elements for specified key.
 *
 * @param  array  $aoa
 * @param  scalar $key
 * @return numeric
 */
function aoa_sum(array $aoa, $key)
{
   ensure_scalar($key, 'The second argument');

   return array_reduce($aoa, function($sum, $array) use($key) { return $sum + array_get_or_else($array, $key, 0); }, 0);
}

/**
 * Return the AoA mapped by specified key.
 *
 * @param  array   $aoa
 * @param  scalar  $key
 * @param  Closure $closure
 * @return array
 */
function aoa_map(array $aoa, $key, $closure)
{
   ensure_scalar  ($key    , 'The second argument');
   ensure_callable($closure, 'The third argument' );

   $result = array();
   foreach ($aoa as $k => $array) {
      ensure_array($array, 'Each element of the first argument');
      if (array_key_exists($key, $array)) {
         $array[$key] = $closure($array[$key]);
      }
      $result[$k] = $array;
   }
   return $result;
}

/**
 * Return the AoA reduced by specified key.
 *
 * @param  array   $aoa
 * @param  scalar  $key
 * @param  Closure $closure
 * @param  mixed   $initial
 * @return mixed
 */
function aoa_reduce(array $aoa, $key, $closure, $initial)
{
   ensure_scalar  ($key    , 'The second argument');
   ensure_callable($closure, 'The third argument' );

   return array_reduce(aoa_values($aoa, $key), $closure, $initial);
}

/**
 * Return the AoA filtered by specified key.
 *
 * @param  array   $aoa
 * @param  scalr   $key
 * @param  Closure $closure
 * @return array
 */
function aoa_filter(array $aoa, $key, $closure)
{
   ensure_scalar  ($key    , 'The second argument');
   ensure_callable($closure, 'The third argument' );

   $result = array();
   foreach ($aoa as $k => $array) {
      ensure_array($array, 'Each element of the first argument');
      if (array_key_exists($key, $array) && $closure($array[$key])) {
         $result[$k] = $array;
      }
   }
   return $result;
}

/**
 * Return the AoA which sorted by an array value of specified key.
 *
 * @param  array  $aoa
 * @param  scalar $key
 * @return array
 */
function aoa_sort(array $aoa, $key, $order = SORT_ASC, $option = SORT_REGULAR)
{
   ensure_scalar($key, 'The second argument');

   array_multisort(aoa_values($aoa, $key), $order, $option, $aoa);
   return $aoa;
}

/**
 * Return the AoA which each key is an array value of specified key.
 *
 * @param  array  $aoa
 * @param  scalar $key
 * @return array
 */
function aoa_associate(array $aoa, $key)
{
   ensure_scalar($key, 'The second argument');

   $associated = array();
   foreach ($aoa as $array) {
      ensure_array($array, 'Each element of the first argument');
      $value = array_get($array, $key);
      ensure_scalar($value, 'Each element of specified key');
      unset($array[$key]);
      $associated[$value] = $array;
   }
   return $associated;
}
