<?php

require_once('general.php');

class GeneralTest extends PHPUnit_Framework_TestCase
{
   /**
    * @expectedException PHPUnit_Framework_Error_Notice
    */
   public function testPhpNotice()
   {
      echo $undefined_var;
   }

   public function testGetOrElse()
   {
      $defined_var = 1;
      $this->assertEquals(1, get_or_else($defined_var  , 0));
      $this->assertEquals(0, get_or_else($undefined_var, 0));

      unset($undefined_var); // assertEquals() define $undefined_var above line, so this line unset it.
      $without_php_notice = get_or_null($undefined_var);
      $this->assertEquals(null, $without_php_notice);
   }

   public function testBetween()
   {
      $int = 0;
      $this->assertEquals( true, between($int,  0,  5));
      $this->assertEquals( true, between($int, -5,  0));
      $this->assertEquals( true, between($int, -5,  5));
      $this->assertEquals(false, between($int,  1,  5));
      $this->assertEquals(false, between($int, -5, -1));
      $this->assertEquals(false, between($int,  5, -5));

      $iso8601 = '1987-04-20 00:00:00';
      $this->assertEquals( true, between($iso8601, '1987-04-01 00:00:00', '1987-04-30 00:00:00'));
      $this->assertEquals(false, between($iso8601, '1987-05-01 00:00:00', '1987-05-31 00:00:00'));
   }
}
