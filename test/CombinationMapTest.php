<?php

require_once(implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'constants.inc']));
require_once(PATH_TO_CLASS . 'CombinationMap.class.php');
require_once(PATH_TO_LIB   . 'array.inc');
require_once(PATH_TO_LIB   . 'general.inc');

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
      foreach (range(0, count($this->elements) - 1) as $index) {
         $this->assertEquals($this->elements[$index], $cm->get($this->combinations[$index]));
      }
      $this->assertNull($cm->get([]));
      return $cm;
   }

   /**
    * @depends testSetAndSize
    */
   public function testSum($cm)
   {
      $this->assertEquals(array_sum($this->elements), $cm->sum());
   }

   /**
    * @depends testSetAndSize
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
