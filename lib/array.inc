<?php

require_once(implode(DIRECTORY_SEPARATOR, array(__DIR__, '..', 'mandatory.inc')));
require_lib('general.inc');

/**
 * Return the specified value of an array if it's defined.
 * Otherwise, return "null".
 *
 * @param  array      $array
 * @param  int|string $key
 * @return mixed      $array[$key]|null
 */
function array_get(array &$array, $key)
{
   return isset($array[$key]) ? $array[$key] : null;
}

/**
 * Return the specified value of an array if it's defined.
 * Otherwise, return $default.
 *
 * @param  array      $array
 * @param  int|string $key
 * @return mixed      $array[$key]|$default
 */
function array_get_or_else(array &$array, $key, $default)
{
   return array_key_exists($key, $array) ? $array[$key] : $default;
}


/**
 * Return an array consisting of the pairs of each element for two arrays.
 *
 * @param  array $array1,$array2,...
 * @return array [[$element1_1,$element2_1,...],...]
 */
function array_zip()
{
   $arrays = func_get_args();
   foreach ($arrays as $array) {
      ensure(is_array($array), type_violation_message(__FUNCTION__, 'Each argument', 'array', $array));
   }

   $formatted_arrays = array_map('array_values', $arrays);
   $min_length       = min(array_map('count', $formatted_arrays));

   $zipped_array = array();
   for ($i = 0; $i < $min_length; $i++) {
      $zipped_array[] = array_reduce($formatted_arrays, function ($carry, $array) use($i) {
            $carry[] = $array[$i];
            return $carry;
         }, array()
      );
   }

   return $zipped_array;
}


/**
 * Return the pair of first element and the others of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return array [$head, $tail]
 */
function array_behead(array &$array)
{
   ensure(!empty($array), type_violation_message(__FUNCTION__, 'The first argument', 'non-empty', $array));

   $head = reset($array);
   $tail = array_slice($array, 1, count($array) - 1);
   return array($head, $tail);
}

/**
 * Return the first element of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return mixed
 */
function array_head(array &$array)
{
   list($head) = array_behead($array);
   return $head;
}

/**
 * Return the array excluding the first element of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return array
 */
function array_tail(array &$array)
{
   list(, $tail) = array_behead($array);
   return $tail;
}


/**
 * Return the pair of last element and the others of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return array [$init, $last]
 */
function array_depeditate(array &$array)
{
   ensure(!empty($array), type_violation_message(__FUNCTION__, 'The first argument', 'non-empty', $array));

   $init = array_slice($array, 0, count($array) - 1);
   $last = end($array);
   reset($array);
   return array($init, $last);
}

/**
 * Return the array excluding the last element of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return array
 */
function array_init(array &$array)
{
   list($init) = array_depeditate($array);
   return $init;
}

/**
 * Return the last element of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return mixed
 */
function array_last(array &$array)
{
   list(, $last) = array_depeditate($array);
   return $last;
}


/**
 * Return the pair of Arrays, which of former is true value and latter is false value.
 * Side effect: Array's internal pointer point nothing.
 *
 * @param  array    $array
 * @param  callable $true_or_false
 * @return array    [$trues, $falses]
 */
function array_partition(array &$array, $true_or_false)
{
   $former = $latter = array();
   foreach ($array as $key => $value) {
      if ($true_or_false($value)) {
         $former[$key] = $value;
      } else {
         $latter[$key] = $value;
      }
   }
   return array($former, $latter);
}
