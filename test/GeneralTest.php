<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class GeneralTest extends PHPUnit_Framework_TestCase
{
   /**
    * @expectedException LogicException
    */
   public function testEnsure()
   {
      ensure(false, 'Message for LogicException');
      return true;
   }

   /**
    * @depends testEnsure
    * @expectedException LogicException
    */
   public function testInZException($ok)
   {
      in_z('not a number');
      return true;
   }
   /**
    * @depends testInZException
    */
   public function testInZ($ok)
   {
      $this->assertTrue(in_z(  1 ));
      $this->assertTrue(in_z( -1 ));
      $this->assertTrue(in_z( "1"));
      $this->assertTrue(in_z("-1"));

      $this->assertTrue(in_z( 1.0));
      $this->assertTrue(in_z(-1.0));
      $this->assertTrue(in_z( '1.'  ));
      $this->assertTrue(in_z( '1.00'));
      $this->assertTrue(in_z('-1.00'));

      $this->assertFalse(in_z( 1.5));
      $this->assertFalse(in_z(-1.5));
   }

   private $odds  = [1, 3, 5, 1.0, '1.0'];
   private $evens = [0, 2, 4, 0.0, '0.0'];

   /**
    * @depends testInZ
    */
   public function testIsOdd()
   {
      foreach ($this->odds as $odd) {
         $this->assertTrue(is_odd($odd));
      }

      foreach ($this->evens as $even) {
         $this->assertFalse(is_odd($even));
      }

      $this->assertFalse(is_odd(1.5));
   }

   /**
    * @depends testInZ
    */
   public function testIsEven()
   {
      foreach ($this->evens as $even) {
         $this->assertTrue(is_even($even));
      }

      foreach ($this->odds as $odd) {
         $this->assertFalse(is_even($odd));
      }

      $this->assertFalse(is_even(1.5));
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
      $this->assertTrue (between($iso8601, '1987-04-01 00:00:00', '1987-04-30 00:00:00'));
      $this->assertFalse(between($iso8601, '1987-05-01 00:00:00', '1987-05-31 00:00:00'));
   }

   /**
    * @depends testEnsure
    */
   public function testIncrementalRange($ok)
   {
      $this->assertEquals([       ], incremental_range(0, -1));
      $this->assertEquals([0      ], incremental_range(0,  0));
      $this->assertEquals([0, 1   ], incremental_range(0,  1));
      $this->assertEquals([0, 1, 2], incremental_range(0,  2));
   }

   /**
    * @depends testEnsure
    */
   public function testDecrementalRange($ok)
   {
      $this->assertEquals([0, -1, -2], decremental_range(0, -2));
      $this->assertEquals([0, -1    ], decremental_range(0, -1));
      $this->assertEquals([0        ], decremental_range(0,  0));
      $this->assertEquals([         ], decremental_range(0,  1));
   }
}
