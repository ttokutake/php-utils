<?php

require_once(implode(DIRECTORY_SEPARATOR, array(__DIR__, '..', 'constants.inc')));
require_once(PATH_TO_LIB . 'general.inc');

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

   public function push(array $combination, $value)
   {
      $this->array[$this->toKey($combination)] = $value;
   }

   public function erase(array $combination)
   {
      unset($this->array[$this->toKey($combination)]);
   }

   public function get(array $combination)
   {
      return get_or_null($this->array[$this->toKey($combination)]);
   }

   private function toKey(array $combination)
   {
      return implode($this->delimiter, $combination);
   }

   private function apply(array $combination, $function)
   {
      $key = $this->toKey($combination);
      $this->array[$key] = $function($this->array[$key]);
   }
}
