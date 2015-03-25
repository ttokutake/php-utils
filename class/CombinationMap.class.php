<?php

class CombinationMap
{
   private $array = array();
   private $delimiter;

   public function __construct($delimiter = null)
   {
      $this->delimiter = empty($delimiter) ? uniqid() : $delimiter;
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
      return $this->array[$this->toKey($combination)];
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
