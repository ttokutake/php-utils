<?php

/**
 * Return the transposed matrix
 *
 * @param  array $matrix
 * @return array
 */
function aoa_transpose(array &$matrix)
{
   $transposed = array();
   foreach ($matrix as $r_key => $row) {
      ensure(is_array($row), type_violation_message(__FUNCTION__, 'each', 'array', $row));
      foreach ($row as $c_key => $entry) {
         $transposed[$c_key][$r_key] = $entry;
      }
   }
   return $transposed;
}

/**
 * Return the sum of elements for specified key.
 *
 * @param  array   $aoa
 * @return numeric
 */
function aoa_sum(array &$aoa, $key)
{
   ensure(is_scalar($key), type_violation_message(__FUNCTION__, 'second', 'scalar', $key));

   return array_reduce($aoa, function ($sum, $array) use($key) { return $sum + array_get_or_else($array, $key, 0); }, 0);
}

/**
 * Return the AoA which each key is an array value of specified key.
 *
 * @param  array $aoa
 * @return array
 */
function aoa_associate(array &$aoa, $key)
{
   ensure(is_scalar($key), type_violation_message(__FUNCTION__, 'second', 'scalar', $key));

   $filtered = array_filter($aoa, function ($array) use($key) { return array_key_exists($key, $array); });

   $associated = array();
   foreach ($filtered as $array) {
      $value = $array[$key];
      ensure(is_scalar($value) || is_null($value), __FUNCTION__ . "(): value of specified key must be scalar or null.");
      unset($array[$key]);
      $associated[$value] = $array;
   }
   return $associated;
}
