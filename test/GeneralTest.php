<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class GeneralTest extends PHPUnit_Framework_TestCase
{
   private $reals = [1.5, -1.5, '1.5', '-1.5'];
   private $odds  = [1, 3, 5, -1, 1.0, -1.0, 1., -1., '1', '-1', '1.0', '-1.0', '1.', '-1.', '1.00', '-1.00'];
   private $evens = [0, 2, 4, -2, 2.0, -2.0, 2., -2., '2', '-2', '2.0', '-2.0', '2.', '-2.', '2.00', '-2.00'];

   function testInZ()
   {
      foreach (array_merge($this->odds, $this->evens) as $integer) {
         $this->assertTrue(in_z($integer));
      }

      foreach ($this->reals as $real) {
         $this->assertFalse(in_z($real));
      }
   }

   /**
    * @depends testInZ
    */
   function testIsOdd()
   {
      foreach ($this->odds as $odd) {
         $this->assertTrue(is_odd($odd));
      }

      foreach ($this->evens as $even) {
         $this->assertFalse(is_odd($even));
      }

      foreach ($this->reals as $real) {
         $this->assertFalse(is_odd($real));
      }
   }

   /**
    * @depends testInZ
    */
   function testIsEven()
   {
      foreach ($this->evens as $even) {
         $this->assertTrue(is_even($even));
      }

      foreach ($this->odds as $odd) {
         $this->assertFalse(is_even($odd));
      }

      foreach ($this->reals as $real) {
         $this->assertFalse(is_even($real));
      }
   }

   function testBetween()
   {
      $target_int =  0;
      $min_int    = -5;
      $max_int    =  5;

      $target_iso8601 = '1987-04-20 00:00:00';
      $min_iso8601    = '1987-04-01 00:00:00';
      $max_iso8601    = '1987-04-30 00:00:00';

      $patterns = [
         [true , $target_int, $target_int, $max_int   ],
         [true , $target_int, $min_int   , $target_int],
         [true , $target_int, $min_int   , $max_int   ],
         [false, $target_int, 1          , $max_int   ],
         [false, $target_int, $min_int   , -1         ],
         [false, $target_int, $max_int   , $min_int   ],

         [true , $target_iso8601, $target_iso8601      , $max_iso8601         ],
         [true , $target_iso8601, $min_iso8601         , $target_iso8601      ],
         [true , $target_iso8601, $min_iso8601         , $max_iso8601         ],
         [false, $target_iso8601, '1987-04-20 00:00:01', $max_iso8601         ],
         [false, $target_iso8601, $min_iso8601         , '1987-04-19 23:59:59'],
         [false, $target_iso8601, $max_iso8601         , $min_iso8601         ],
      ];
      foreach ($patterns as list($expected, $target, $min, $max)) {
         $this->assertEquals($expected, between($target, $min, $max));
      }
   }

   function testIncrementalRange()
   {
      $this->assertEquals([       ], incremental_range(0, -1));
      $this->assertEquals([0      ], incremental_range(0,  0));
      $this->assertEquals([0, 1   ], incremental_range(0,  1));
      $this->assertEquals([0, 1, 2], incremental_range(0,  2));
   }

   /**
    * @depends testIncrementalRange
    */
   function testDecrementalRange()
   {
      $this->assertEquals([0, -1, -2], decremental_range(0, -2));
      $this->assertEquals([0, -1    ], decremental_range(0, -1));
      $this->assertEquals([0        ], decremental_range(0,  0));
      $this->assertEquals([         ], decremental_range(0,  1));
   }


   function testReverseClosure()
   {
      $is_non_int = reverse_closure('is_int');

      $non_ints = [
         null,
         true,
         1.0 ,
         '1' ,
         []  ,

         function() { echo 'testReverseClosure'; },
      ];
      foreach ($non_ints as $non_int) {
         $this->assertTrue($is_non_int($non_int));
      }
      $this->assertFalse($is_non_int(1));
   }
}
