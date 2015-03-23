<?php

require_once('../lib/general.php');

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

      $array = ['one' => 1, 'two' => 2];
      $this->assertEquals( 2, get_or_else($array['two'  ], -2));
      $this->assertEquals(-3, get_or_else($array['three'], -3));
   }

   public function testGetOrNull()
   {
      $defined_var = 'string';
      $this->assertEquals('string', get_or_null($defined_var));
      $this->assertNull(get_or_null($undefined_var));
   }

   public function testBetween()
   {
      $patterns = [
         [true , 0,  0,  5],
         [true , 0, -5,  0],
         [true , 0, -5,  5],
         [false, 0,  1,  5],
         [false, 0, -5, -1],
         [false, 0,  5, -5],
      ];
      foreach ($patterns as list($expected, $num, $min, $max)) {
         $this->assertEquals($expected, between($num, $min, $max));
      }

      $iso8601 = '1987-04-20 00:00:00';
      $this->assertEquals( true, between($iso8601, '1987-04-01 00:00:00', '1987-04-30 00:00:00'));
      $this->assertEquals(false, between($iso8601, '1987-05-01 00:00:00', '1987-05-31 00:00:00'));
   }
}
