<?php

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
      if (!is_array($array)) {
         throw new UnexpectedValueException(__FUNCTION__ . ': Each argment must be "array" type.');
      }
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
 *
 * @param  array $array
 * @return array [$head, $tail]
 */
function array_behead(array $array)
{
   if (empty($array)) {
      throw new UnexpectedValueException(__FUNCTION__ . ': The array must not be empty.');
   }
   $head = array_shift($array);
   return array($head, $array);
}

/**
 * Return the pair of last element and the others of an array.
 *
 * @param  array $array
 * @return array [$init, $last]
 */
function array_depeditate(array $array)
{
   if (empty($array)) {
      throw new UnexpectedValueException(__FUNCTION__ . ': The array must not be empty.');
   }
   $last = array_pop($array);
   return array($array, $last);
}
