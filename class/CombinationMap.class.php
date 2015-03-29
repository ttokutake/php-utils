<?php

require_once(implode(DIRECTORY_SEPARATOR, array(__DIR__, '..', 'mandatory.inc')));
require_lib('array.inc');
require_lib('general.inc');

class CombinationMap
{
   private $name;
   private $delimiter;
   private $array;

   public function __construct($delimiter = ',')
   {
      $this->name      = __CLASS__ . '::';
      $this->delimiter = $delimiter;
      $this->array     = array();
   }

   public function size()
   {
      return count($this->array);
   }

   public function set(array $combination, $value)
   {
      $this->array[$this->toKey($combination)] = $value;
   }

   public function get(array $combination)
   {
      return array_get($this->array, $this->toKey($combination));
   }

   public function exist(array $combination)
   {
      return array_key_exists($this->toKey($combination), $this->array);
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

   public function partLeft(array $partial_combination)
   {
      return $this->part($partial_combination, 'left');
   }

   public function partRight(array $partial_combination)
   {
      return $this->part($partial_combination, 'right');
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

   private function part(array $combination, $type)
   {
      $regex = implode($this->delimiter, $this->escape($combination));
      switch ($type) {
         case 'left':
            $regex = "^$regex";
            break;
         case 'right':
            $regex = "$regex$";
            break;
      }

      $part = array();
      foreach ($this->array as $key => $value) {
         if (preg_match("/$regex/", $key) === 1) {
            $part[$key] = $value;
         }
      }
      $cm = new CombinationMap($this->delimiter);
      $cm->array = $part;
      return $cm;
   }

   private function escape(array $combination)
   {
      return array_map(function ($key) { return $key == '*' ? "[^$this->delimiter]*" : preg_quote($key); }, $combination);
   }


   public function dump()
   {
      print_r($this->array);
   }
}
