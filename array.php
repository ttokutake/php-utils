<?php

/**
 * Create an associative array from pair arrays of keys and values.
 * Length of The associative array is shorter length of pair arrays.
 *
 * @param  array $keys
 * @param  array $values
 * @return array
 */
function associative_zip(array $keys, array $values)
{
   $formatted_keys   = array_values($keys);
   $formatted_values = array_values($values);

   $associative_array = [];
   $min_length        = min(count($formatted_keys), count($formatted_values));
   for ($i = 0; $i < $min_length; $i++) {
      $associative_array[$formatted_keys[$i]] = $formatted_values[$i];
   }
   return $associative_array;
}

function array_behead(array $array)
{
   $head = array_shift($array);
   return [$head, $array];
}

function array_depeditate(array $array)
{
   $last = array_pop($array);
   return [$array, $last];
}
