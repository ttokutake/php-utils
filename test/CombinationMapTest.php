<?php

require_once(implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'mandatory.inc']));
require_class('CombinationMap.class.php');
require_lib('array.inc');
require_lib('general.inc');

class CombinationMapTest extends PHPUnit_Framework_TestCase
{
   private $combinations = [['blowser', 'firefox'], ['blowser', 'chrome']];
   private $elements     = [100, 200];

   public function testSetAndSize()
   {
      $cm = new CombinationMap();
      foreach (array_zip($this->combinations, $this->elements) as $index => list($combination, $element)) {
         $cm->set($combination, $element);
         $this->assertEquals($index + 1, $cm->size());
      }
      return $cm;
   }

   /**
    * @depends testSetAndSize
    */
   public function testGet($cm)
   {
      foreach (incremental_range(0, count($this->elements) - 1) as $index) {
         $this->assertEquals($this->elements[$index], $cm->get($this->combinations[$index]));
      }
      $this->assertNull($cm->get([]));
      return $cm;
   }

   /**
    * @depends testSetAndSize
    */
   public function testExist($cm)
   {
      foreach ($this->combinations as $combination) {
         $this->assertTrue($cm->exist($combination));
      }
      $this->assertFalse($cm->exist(['blowser', 'opera']));
   }

   /**
    * @depends testSetAndSize
    */
   public function testValues($cm)
   {
      $this->assertEquals($this->elements, $cm->values());
   }

   /**
    * @depends testSetAndSize
    */
   public function testSum($cm)
   {
      $this->assertEquals(array_sum($this->elements), $cm->sum());
   }

   /**
    * @depends testGet
    */
   public function testMap($cm)
   {
      $triple = function ($int) { return 3 * $int; };
      $mapped = $cm->map($triple);
      foreach (array_zip($this->combinations, $this->elements) as list($combination, $element)) {
         $this->assertEquals($triple($element), $mapped->get($combination));
      }
   }

   /**
    * @depends testSetAndSize
    */
   public function testReduce($cm)
   {
      $connect = function ($result, $elem) { return strval($result) . ' + ' . strval($elem); };
      $this->assertEquals(array_reduce($this->elements, $connect), $cm->reduce($connect));
   }

   /**
    * @depends testSetAndSize
    */
   public function testToAssociation($cm)
   {
      $expected = ['blowser' => ['firefox' => 100, 'chrome' => 200]];
      $this->assertEquals($expected, $cm->toAssociation());
   }

   /**
    * @depends testGet
    */
   public function testApply($cm)
   {
      $twice = function ($int) { return 2 * $int; };
      foreach (incremental_range(0, count($this->elements) - 1) as $index) {
         $cm->apply($this->combinations[$index], $twice);
         $this->assertEquals($twice($this->elements[$index]), $cm->get($this->combinations[$index]));
      }
   }

   /**
    * @depends testSetAndSize
    */
   public function testErase($cm)
   {
      foreach (decremental_range(count($this->elements) - 1, 0) as $index) {
         $cm->erase($this->combinations[$index]);
         $array_size = $index;
         $this->assertEquals($array_size, $cm->size());
      }
   }
}
