<?php

require_once(implode(DIRECTORY_SEPARATOR, array(__DIR__, '..', 'mandatory.inc')));
require_lib('array.inc');
require_lib('general.inc');

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
      ensure(is_callable($function), type_violation_message(__CLASS__ . '::' .  __FUNCTION__, 'The second argument', 'callable', $function));
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

   public function exist(array $combination)
   {
      return array_key_exists($this->toKey($combination), $this->array);
   }

   public function sum()
   {
      return array_sum($this->array);
   }


   private function toKey(array $combination)
   {
      return implode($this->delimiter, $combination);
   }


   public function dump()
   {
      print_r($this->array);
   }
}
