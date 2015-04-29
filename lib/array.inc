<?php

/**
 * This file is part of the php-utils.php package.
 *
 * Copyright (C) 2015 Tadatoshi Tokutake <tadatoshi.tokutake@gmail.com>
 *
 * Licensed under the MIT License
 */


require_once implode(DIRECTORY_SEPARATOR, array(__DIR__, 'error.inc'  ));


/**
 * Return the specified value of an array if it's defined.
 * Otherwise, return "null".
 *
 * @param  array      &$array
 * @param  int|string  $key
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
 * @param  array      &$array
 * @param  int|string  $key
 * @param  mixed       $default
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
 * @param  array      &$array
 * @param  int|string  $key
 * @param  mixed       $default
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
 * @param  array      &$array
 * @param  int|string  $key
 * @param  mixed       $default
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
   if (is_callable($closure)) {
      $closure_not = function ($value) use($closure) { return !$closure($value); };
   } else if (is_null($closure)) {
      $closure_not = function ($value) { return !$value; };
   } else {
      throw new LogicException(variable_violation_text('The second argument', 'callable or null', to_type($closure)));
   }
   return array_filter($array, $closure_not);
}

/**
 * Return array_map() which can use keys of $array.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return array
 */
function array_map_with_key(array $array, $closure)
{
   ensure_callable($closure, 'The second argument');

   $result = array();
   foreach ($array as $key => $value) {
      $result[$key] = $closure($key, $value);
   }
   return $result;
}

/**
 * Return the flatten array.
 *
 * @param  array $array
 * @return array
 */
function array_flat(array $array)
{
   return array_reduce($array, function ($carry, $item) { return array_merge($carry, is_array($item) ? $item : array($item));  }, array());
}


/**
 * Return an array consisting of the pairs of each element for two arrays.
 *
 * @param  array $array1,$array2,...
 * @return array
 */
function array_zip()
{
   $arrays = func_get_args();
   foreach ($arrays as $array) {
      ensure_array($array, 'Each argument');
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
 *
 * @param  array $array
 * @return array
 */
function array_behead(array $array)
{
   ensure_non_empty($array, 'The first argument');

   $head = reset($array);
   $tail = array_slice($array, 1);
   return array($head, $tail);
}

/**
 * Return the first element of an array.
 *
 * @param  array $array
 * @return mixed
 */
function array_head(array $array)
{
   ensure_non_empty($array, 'The first argument');

   list($head) = array_behead($array, 1);
   return $head;
}

/**
 * Return the array excluding the first element of an array.
 *
 * @param  array $array
 * @return array
 */
function array_tail(array $array)
{
   ensure_non_empty($array, 'The first argument');

   list(, $tail) = array_behead($array, 1);
   return $tail;
}


/**
 * Return the pair of last element and the others of an array.
 *
 * @param  array $array
 * @return array
 */
function array_depeditate(array $array)
{
   ensure_non_empty($array, 'The first argument');

   $init = array_slice($array, 0, count($array) - 1);
   $last = end($array);
   reset($array);
   return array($init, $last);
}

/**
 * Return the array excluding the last element of an array.
 *
 * @param  array $array
 * @return array
 */
function array_init(array $array)
{
   ensure_non_empty($array, 'The first argument');

   list($init) = array_depeditate($array, 1);
   return $init;
}

/**
 * Return the last element of an array.
 *
 * @param  array $array
 * @return mixed
 */
function array_last(array $array)
{
   ensure_non_empty($array, 'The first argument');

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
   ensure_non_positive_int($num, 'The second argument');

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
   ensure_non_positive_int($num, 'The second argument');

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
   ensure_non_positive_int($num, 'The second argument');

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
   ensure_non_positive_int($num, 'The second argument');

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
   ensure_int($offset, 'The second argument');

   $former = $latter = array();
   $count  = 0;
   foreach ($array as $key => $value) {
      if ($count < $offset) {
         $former[$key] = $value;
      } else {
         $latter[$key] = $value;
      }
      $count++;
   }
   return array($former, $latter);
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
   ensure_callable($closure, 'The second argument');

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
   ensure_callable($closure, 'The second argument');

   $closure_not = function ($value) use($closure) { return !$closure($value); };
   return !array_exist($array, $closure_not);
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
   ensure_callable($closure, 'The second argument');

   foreach ($array as $value) {
      if ($closure($value)) {
         return $value;
      }
   }
   return null;
}

/**
 * Return the pair of Arrays, which of former is true value and latter is false value.
 *
 * @param  array   $array
 * @param  Closure $closure
 * @return array
 */
function array_partition(array $array, $closure)
{
   ensure_callable($closure, 'The second argument');

   $former = $latter = array();
   foreach ($array as $key => $value) {
      if ($closure($value)) {
         $former[$key] = $value;
      } else {
         $latter[$key] = $value;
      }
   }
   return array($former, $latter);
}
