<?php

require_once(implode(DIRECTORY_SEPARATOR, array(__DIR__, '..', 'mandatory.inc')));
require_lib('array.inc');
require_lib('general.inc');

class CombinationMap
{
   private $name;
   private $delimiter;
   private $array = array();

   public function __construct($delimiter = ',')
   {
      $this->name      = __CLASS__ . '::';
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
      ensure(is_callable($function), type_violation_message($this->name . __FUNCTION__, 'The second argument', 'callable', $function));
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

   public function values()
   {
      return array_values($this->array);
   }

   public function sum()
   {
      return array_sum($this->array);
   }

   public function map($function)
   {
      ensure(is_callable($function), type_violation_message($this->name . __FUNCTION__, 'The first argument', 'callable', $function));
      $cm        = new CombinationMap($this->delimiter);
      $cm->array = array_map($function, $this->array);
      return $cm;
   }

   public function reduce($function, $initialize = null)
   {
      ensure(is_callable($function), type_violation_message($this->name . __FUNCTION__, 'The first argument', 'callable', $function));
      return array_reduce($this->array, $function, $initialize);
   }

   public function fromAssociative(array $associative)
   {
      foreach ($associative as $key => $value) {
         if (is_array($value)) {
            $this->chainFrom($value, $key);
         } else {
            $this->array[$key] = $value;
         }
      }
   }

   public function toAssociative()
   {
      $associative = array();
      foreach ($this->array as $key => $value)
      {
         $combination = explode($this->delimiter, $key);

         $pointer = &$associative;
         foreach ($combination as $group) {
            $pointer = &$pointer[$group];
         }
         $pointer = $value;
      }
      return $associative;
   }


   private function toKey(array $combination)
   {
      return implode($this->delimiter, $combination);
   }

   private function chainFrom(array $associative, $key_chain)
   {
      foreach ($associative as $key => $value) {
         if (is_array($value)) {
            $this->chainFrom($value, $this->toKey(array($key_chain, $key)));
         } else {
            $this->array[$this->toKey(array($key_chain, $key))] = $value;
         }
      }
   }


   public function dump()
   {
      print_r($this->array);
   }
}
