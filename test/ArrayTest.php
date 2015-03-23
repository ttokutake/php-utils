<?php

require_once('../lib/array.php');

class ArrayTest extends PHPUnit_Framework_TestCase
{
   public function testArrayZip()
   {
      $patterns = [
         [[], [ ], [ ]],
         [[], [1], [ ]],
         [[], [ ], [1]],

         [[[1, 4]        ], [1, 2], [4   ]],
         [[[1, 4]        ], [1   ], [4, 5]],
         [[[1, 4], [2, 5]], [1, 2], [4, 5]],
      ];
      foreach ($patterns as list($expected, $array1, $array2)) {
         $this->assertEquals($expected, array_zip($array1, $array2));
      }
      return true;
   }


   private $arrays = [
      [1      ],
      [1, 2   ],
      [1, 2, 3],

      ['one' => 1                          ],
      ['one' => 1, 'two' => 2              ],
      ['one' => 1, 'two' => 2, 'three' => 3],
   ];

   /**
    * @depends testArrayZip
    */
   public function testArrayBehead($ok)
   {
      $expected = [
         [1, [    ]],
         [1, [2   ]],
         [1, [2, 3]],

         [1, [                        ]],
         [1, ['two' => 2              ]],
         [1, ['two' => 2, 'three' => 3]],
      ];
      $patterns = array_zip($expected, $this->arrays);

      foreach ($patterns as list($expected, $arrays)) {
         $this->assertEquals($expected, array_behead($arrays));
      }
   }
   /**
    * @expectedException UnexpectedValueException
    */
   public function testArrayBeheadException()
   {
      $empty_array = [];
      array_behead($empty_array);
   }

   /**
    * @depends testArrayZip
    */
   public function testArrayDepeditate($ok)
   {
      $expected = [
         [[    ], 1],
         [[1   ], 2],
         [[1, 2], 3],

         [[                      ], 1],
         [['one' => 1            ], 2],
         [['one' => 1, 'two' => 2], 3],
      ];
      $patterns = array_zip($expected, $this->arrays);

      foreach ($patterns as list($expected, $arrays)) {
         $this->assertEquals($expected, array_depeditate($arrays));
      }
   }
   /**
    * @expectedException UnexpectedValueException
    */
   public function testArrayDepeditateException()
   {
      $empty_array = [];
      array_depeditate($empty_array);
   }
}
