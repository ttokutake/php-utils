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
 * Return array_map() which can use keys of $array.
 * Side effect: Array's internal pointer will point nothing.
 *
 * @param  array    $array
 * @param  callable $callable
 * @return array
 */
function array_map_with_key(array &$array, $callable)
{
   $result = array();
   foreach ($array as $key => $value) {
      $result[$key] = $callable($key, $value);
   }
   return $result;
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
      ensure(is_array($array), type_violation_message('Each argument', 'array', $array));
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
 * Return the array added $hat as first element.
 *
 * @param  array $array
 * @param  mixed $hat
 * @return array
 */
function array_hat(array $array, $hat) {
   return array_merge(array($hat), $array);;
}

/**
 * Return the array added $shoe as last element.
 *
 * @param  array $array
 * @param  mixed $shoe
 * @return array
 */
function array_shoe(array $array, $shoe) {
   return array_merge($array, array($shoe));
}

/**
 * Return the pair of first element and the others of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return array [$head, $tail]
 */
function array_behead(array &$array, $added_trace_depth = 0)
{
   ensure(!empty($array), variable_violation_message('The first argument', 'non-empty', '[]', $added_trace_depth));

   $head = reset($array);
   $tail = array_slice($array, 1);
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
   list($head) = array_behead($array, 1);
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
   list(, $tail) = array_behead($array, 1);
   return $tail;
}


/**
 * Return the pair of last element and the others of an array.
 * Side effect: Array's internal pointer is reset.
 *
 * @param  array $array
 * @return array [$init, $last]
 */
function array_depeditate(array &$array, $added_trace_depth = 0)
{
   ensure(!empty($array), variable_violation_message('The first argument', 'non-empty', '[]', $added_trace_depth));

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
   list($init) = array_depeditate($array, 1);
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
   list(, $last) = array_depeditate($array, 1);
   return $last;
}

/**
 * Return the array taking heads of $array.
 *
 * @param  array $array
 * @param  int   $num
 * @return array
 */
function array_take(array $array, $num)
{
   ensure(is_int($num) && $num >= 0, variable_violation_message('The second argument', 'non-negative integer', $num));
   return array_slice($array, 0, $num);
}

/**
 * Return the array dropping heads of $array.
 *
 * @param  array $array
 * @param  int   $num
 * @return array
 */
function array_drop(array $array, $num)
{
   ensure(is_int($num) && $num >= 0, variable_violation_message('The second argument', 'non-negative integer', $num));
   return array_slice($array, $num);
}

/**
 * Return the first element returning $callable($element_of_array) to be true.
 * Side effect: Array's internal pointer will point nothing.
 *
 * @param  $array    $array
 * @param  $callable $callable
 * @return mixed
 */
function array_find(array &$array, $callable)
{
   foreach ($array as $value) {
      if ($callable($value)) {
         return $value;
      }
   }
   return null;
}

/**
 * Return the pair of Arrays, which of former is true value and latter is false value.
 * Side effect: Array's internal pointer will point nothing.
 *
 * @param  array    $array
 * @param  callable $callable
 * @return array    [$trues, $falses]
 */
function array_partition(array &$array, $callable)
{
   $former = $latter = array();
   foreach ($array as $key => $value) {
      if ($callable($value)) {
         $former[$key] = $value;
      } else {
         $latter[$key] = $value;
      }
   }
   return array($former, $latter);
}
