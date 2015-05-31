<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'error.inc'  ));
require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'general.inc'));


/**
 * Judge if the array is pure sequencal array.
 *
 * @param  array   $array
 * @return boolean
 */
function is_seq(array $array)
{
   return array_keys($array) === incremental_range(0, count($array) - 1);
}

/**
 * Return array_values().
 *
 * @param  array $array
 * @return array
 */
function to_seq(array $array)
{
   return array_values($array);
}

/**
 * Return array_filter() whose indices is sequal.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return array
 */
function seq_filter(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   $result = array();
   foreach ($array as $value) {
      if ($closure($value)) {
         $result[] = $value;
      }
   }
   return $result;
}


/**
 * Return array_map() which can use keys of the array.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return array
 */
function assoc_map(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   $result = array();
   foreach ($array as $key => $value) {
      $result[$key] = $closure($key, $value);
   }
   return $result;
}

/**
 * Return array_reduce() which can use keys of the array.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @param  mixed   $initial
 * @return mixed
 */
function assoc_reduce(array $array, $closure, $initial)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   foreach ($array as $key => $value) {
      $initial = $closure($initial, $key, $value);
   }
   return $initial;
}

/**
 * Return array_filter() which can use keys of the array.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return array
 */
function assoc_filter(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   $result = array();
   foreach ($array as $key => $value) {
      if ($closure($key, $value)) {
         $result[$key] = $value;
      }
   }
   return $result;
}

/**
 * Judge if the element which return true for $closure exists.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return boolean
 */
function assoc_exist(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   foreach ($array as $key => $value) {
      if ($closure($key, $value)) {
         return true;
      }
   }
   return false;
}

/**
 * Judge if all elements return true for $closure.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return boolean
 */
function assoc_for_all(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   return !assoc_exist($array, reverse_closure($closure, 2));
}


/**
 * Return the array set the value.
 *
 * @param  array  $array
 * @param  scalar $key
 * @param  mixed  $value
 * @return array
 */
function array_set(array $array, $key, $value)
{
   ensure_scalar($key, SUBJECT_FOR_SECOND_ARGUMENT);

   $array[$key] = $value;
   return $array;
}

/**
 * Return the array unset the value.
 *
 * @param  array  $array
 * @param  scalar $key
 * @return array
 */
function array_unset(array $array, $key)
{
   ensure_scalar($key, SUBJECT_FOR_SECOND_ARGUMENT);

   unset($array[$key]);
   return $array;
}

/**
 * Return the array added $hat as first element.
 *
 * @param  array $array
 * @param  mixed $hat
 * @return array
 */
function array_hat(array $array, $hat)
{
   return array_merge(array($hat), $array);;
}

/**
 * Return the array added $shoe as last element.
 *
 * @param  array $array
 * @param  mixed $shoe
 * @return array
 */
function array_shoe(array $array, $shoe)
{
   return array_merge($array, array($shoe));
}


/**
 * Return the specified value of an array if it's defined.
 * Otherwise, return "null".
 *
 * @param  array  &$array
 * @param  scalar  $key
 * @return mixed
 */
function array_get(array &$array, $key)
{
   return isset($array[$key]) ? $array[$key] : null;
}

/**
 * Return the specified value of an array if it's defined.
 * Otherwise, return $default.
 *
 * @param  array  &$array
 * @param  scalar  $key
 * @param  mixed   $default
 * @return mixed
 */
function array_get_or_else(array &$array, $key, $default)
{
   return array_key_exists($key, $array) ? $array[$key] : $default;
}

/**
 * Return the specified value of an array if it isn't null.
 * Otherwise, return $default.
 *
 * @param  array  &$array
 * @param  scalar  $key
 * @param  mixed   $default
 * @return mixed
 */
function array_get_non_null(array &$array, $key, $default)
{
   return isset($array[$key]) ? $array[$key] : $default;
}

/**
 * Return the specified value of an array if it isn't empty.
 * Otherwise, return $default.
 *
 * @param  array  &$array
 * @param  scalar  $key
 * @param  mixed   $default
 * @return mixed
 */
function array_get_non_empty(array &$array, $key, $default)
{
   return empty($array[$key]) ? $default : $array[$key];
}

/**
 * Return the array which orthogonal to array_filter().
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return array
 */
function array_filter_not(array $array, $closure = null)
{
   if (is_null($closure)) {
      $closure = function($value) { return $value; };
   }
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   return array_filter($array, reverse_closure($closure));
}

/**
 * Return the flatten array.
 *
 * @param  array $array
 * @return array
 */
function array_flat(array $array)
{
   return array_reduce($array, function($flatten, $e) { return array_merge($flatten, is_array($e) ? $e : array($e)); }, array());
}


/**
 * Return an array consisting of the pairs of each element for two arrays.
 *
 * @param  array $first
 * @param  array $second
 * @param  array ...
 * @return array
 */
function array_zip(array $first, array $second)
{
   $arrays = func_get_args();
   foreach ($arrays as $array) {
      ensure_array($array, 'Each argument');
   }

   $sequences = array_map('to_seq', $arrays);
   return array_map(
      function($i) use($sequences) {
         return array_reduce($sequences, function($piled, $array) use($i) { return array_shoe($piled, $array[$i]); }, array());
      },
      incremental_range(0, min(array_map('count', $sequences)) - 1)
   );
}


/**
 * Return the first element of an array.
 *
 * @param  array $array
 * @return mixed
 */
function array_head(array $array)
{
   ensure_non_empty($array, SUBJECT_FOR_FIRST_ARGUMENT);

   return reset($array);
}

/**
 * Return the array excluding the first element of an array.
 *
 * @param  array $array
 * @return array
 */
function array_tail(array $array)
{
   ensure_non_empty($array, SUBJECT_FOR_FIRST_ARGUMENT);

   return array_slice($array, 1);
}

/**
 * Return the pair of first element and the others of an array.
 *
 * @param  array $array
 * @return array
 */
function array_behead(array $array)
{
   ensure_non_empty($array, SUBJECT_FOR_FIRST_ARGUMENT);

   return array(array_head($array), array_tail($array));
}


/**
 * Return the array excluding the last element of an array.
 *
 * @param  array $array
 * @return array
 */
function array_init(array $array)
{
   ensure_non_empty($array, SUBJECT_FOR_FIRST_ARGUMENT);

   return array_slice($array, 0, count($array) - 1);
}

/**
 * Return the last element of an array.
 *
 * @param  array $array
 * @return mixed
 */
function array_last(array $array)
{
   ensure_non_empty($array, SUBJECT_FOR_FIRST_ARGUMENT);

   return end($array);
}

/**
 * Return the pair of last element and the others of an array.
 *
 * @param  array $array
 * @return array
 */
function array_depeditate(array $array)
{
   ensure_non_empty($array, SUBJECT_FOR_FIRST_ARGUMENT);

   return array(array_init($array), array_last($array));
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
   ensure_non_negative_int($num, SUBJECT_FOR_SECOND_ARGUMENT);

   return array_slice($array, 0, $num);
}

/**
 * Return the array taking tails of $array.
 *
 * @param  array $array
 * @param  int   $num
 * @return array
 */
function array_take_right(array $array, $num)
{
   ensure_non_negative_int($num, SUBJECT_FOR_SECOND_ARGUMENT);

   return array_reverse(array_take(array_reverse($array), $num, 1));
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
   ensure_non_negative_int($num, SUBJECT_FOR_SECOND_ARGUMENT);

   return array_slice($array, $num);
}

/**
 * Return the array dropping tails of $array.
 *
 * @param  array $array
 * @param  int   $num
 * @return array
 */
function array_drop_right(array $array, $num)
{
   ensure_non_negative_int($num, SUBJECT_FOR_SECOND_ARGUMENT);

   return array_reverse(array_drop(array_reverse($array), $num, 1));
}

/**
 * Return the array split in $offset position.
 *
 * @param  array $array
 * @param  int   $offset
 * @return array
 */
function array_split(array $array, $offset)
{
   ensure_int($offset, SUBJECT_FOR_SECOND_ARGUMENT);

   $offset = $offset < 0 ? count($array) + $offset : $offset;
   $former = $latter = array();
   $count  = 0;
   foreach ($array as $key => $value) {
      if ($count++ < $offset) {
         $former[$key] = $value;
      } else {
         $latter[$key] = $value;
      }
   }
   return is_seq($array) ? array_map('to_seq', array($former, $latter)) : array($former, $latter);
}

/**
 * Return the cluster of slided array.
 *
 * @param  array $array
 * @param  int   $size
 * @param  int   $step
 * @return array
 */
function array_slide(array $array, $size, $step = 1)
{
   ensure_non_negative_int($size, SUBJECT_FOR_SECOND_ARGUMENT);
   ensure_non_negative_int($step, SUBJECT_FOR_THIRD_ARGUMENT );

   $length = count($array);
   $slided = array();
   for ($offset = 0; $offset < $length; $offset += $step) {
      $slided[] = array_slice($array, $offset, $size);
      if ($offset + $size == $length) {
         break;
      }
   }
   return $slided;
}


/**
 * Judge if the element which return true for $closure exists.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return boolean
 */
function array_exist(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   foreach ($array as $value) {
      if ($closure($value)) {
         return true;
      }
   }
   return false;
}

/**
 * Judge if all elements return true for $closure.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return boolean
 */
function array_for_all(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   return !array_exist($array, reverse_closure($closure));
}

/**
 * Return the first element returning $closure($element_of_array) to be true.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return mixed
 */
function array_find(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   foreach ($array as $value) {
      if ($closure($value)) {
         return $value;
      }
   }
   return null;
}

/**
 * Return the pair of Arrays, which of former is true values and latter is false values.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return array
 */
function array_partition(array $array, $closure)
{
   ensure_callable($closure, SUBJECT_FOR_SECOND_ARGUMENT);

   $former = $latter = array();
   foreach ($array as $key => $value) {
      if ($closure($value)) {
         $former[$key] = $value;
      } else {
         $latter[$key] = $value;
      }
   }
   return is_seq($array) ? array_map('to_seq', array($former, $latter)) : array($former, $latter);
}
