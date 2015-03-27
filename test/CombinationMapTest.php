<?php

require_once(implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'constants.inc']));
require_once(PATH_TO_CLASS . 'CombinationMap.class.php');

class CombinationMapTest extends PHPUnit_Framework_TestCase
{
   private $combination = ['blowser', 'firefox'];
   private $element     = true;

   public function testPushAndSize()
   {
      $cm = new CombinationMap();
      $cm->push($this->combination, $this->element);
      $this->assertEquals(1, $cm->size());
      return $cm;
   }

   /**
    * @depends testPushAndSize
    */
   public function testGet($cm)
   {
      $this->assertEquals($this->element, $cm->get($this->combination));
   }

   /**
    * @depends testPushAndSize
    */
   public function testErase($cm)
   {
      $cm->erase($this->combination);
      $this->assertEquals(0, $cm->size());
   }
}
