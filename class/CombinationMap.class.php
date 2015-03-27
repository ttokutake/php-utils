<?php

require_once(implode(DIRECTORY_SEPARATOR, array(__DIR__, '..', 'constants.inc')));
require_once(PATH_TO_LIB . 'array.inc');

class CombinationMap
{
   private $array = array();
   private $delimiter;

   public function __construct($delimiter = ',')
   {
      $this->delimiter = $delimiter;
   }

   public function size()
   {
      return count($this->array);
   }

   public function set(array $combination, $value)
   {
      $this->array[$this->toKey($combination)] = $value;
   }

   public function apply(array $combination, $function)
   {
      $key = $this->toKey($combination);
      $this->array[$key] = $function(array_get($this->array, $key));
   }

   public function erase(array $combination)
   {
      unset($this->array[$this->toKey($combination)]);
   }

   public function get(array $combination)
   {
      return array_get($this->array, $this->toKey($combination));
   }


   private function toKey(array $combination)
   {
      return implode($this->delimiter, $combination);
   }

}
