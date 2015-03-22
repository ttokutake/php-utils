<?php

/**
 * Return the pair of first element and the others of an array.
 *
 * @param  array $array
 * @return array [$head, $tail]
 */
function array_behead(array $array)
{
   $head = array_shift($array);
   return [$head, $array];
}

/**
 * Return the pair of last element and the others of an array.
 *
 * @param  array $array
 * @return array [$init, $last]
 */
function array_depeditate(array $array)
{
   $last = array_pop($array);
   return [$array, $last];
}
