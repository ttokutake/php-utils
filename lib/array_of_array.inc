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
      foreach ($row as $c_key => $entry) {
         $transposed[$c_key][$r_key] = $entry;
      }
   }
   return $transposed;
}

/**
 * Return the sum of elements for specified key.
 *
 * @param  array $aoa
 * @return int|float
 */
function aoa_sum(array &$aoa, $key) {
   return array_reduce($aoa, function ($sum, $array) use($key) { return $sum + $array[$key]; }, 0);
}

/**
 * Return the AoA which each key is an array value of specified key.
 *
 * @param  array $aoa
 * @return array
 */
function aoa_associate(array &$aoa, $key) {
   $associated = array();
   foreach ($aoa as $array) {
      $value = $array[$key];
      unset($array[$key]);
      $associated[$value] = $array;
   }
   return $associated;
}
