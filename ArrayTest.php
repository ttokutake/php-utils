<?php

require_once('array.php');

class ArrayTest extends PHPUnit_Framework_TestCase
{
   private $array             = [1, 2, 3, 4, 5];
   private $associative_array = ['one' => 1, 'two' => 2, 'three' => 3];

   public function testArrayBehead()
   {
      $this->assertEquals([1, [2, 3, 4, 5]]              , array_behead($this->array));
      $this->assertEquals([1, ['two' => 2, 'three' => 3]], array_behead($this->associative_array));
   }

   public function testArrayDepeditate()
   {
      $this->assertEquals([[1, 2, 3, 4], 5]            , array_depeditate($this->array));
      $this->assertEquals([['one' => 1, 'two' => 2], 3], array_depeditate($this->associative_array));
   }
}
