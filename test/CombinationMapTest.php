<?php

require_once(implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'constants.inc']));
require_once(PATH_TO_CLASS . 'CombinationMap.class.php');

class CombinationMapTest extends PHPUnit_Framework_TestCase
{
   private $combination = ['blowser', 'firefox'];
   private $element     = 100;

   public function testSetAndSize()
   {
      $cm = new CombinationMap();
      $cm->set($this->combination, $this->element);
      $this->assertEquals(1, $cm->size());
      return $cm;
   }

   /**
    * @depends testSetAndSize
    */
   public function testGet($cm)
   {
      $this->assertEquals($this->element, $cm->get($this->combination));
      $this->assertNull($cm->get([]));
      return $cm;
   }

   /**
    * @depends testGet
    */
   public function testApply($cm)
   {
      $double = function ($int) { return 2 * $int; };

      $cm->apply($this->combination, $double);
      $this->assertEquals($double($this->element), $cm->get($this->combination));
   }

   /**
    * @depends testSetAndSize
    */
   public function testErase($cm)
   {
      $cm->erase($this->combination);
      $this->assertEquals(0, $cm->size());
   }
}
