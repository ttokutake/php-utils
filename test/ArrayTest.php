<?php

require_once('constants.inc');
require_once(PATH_TO_LIB . 'array.inc');
require_once(PATH_TO_LIB . 'general.inc');

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


   private $empty_array = [];
   private $arrays      = [
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

      foreach ($patterns as list($expected, $array)) {
         $this->assertEquals($expected, array_behead($array));
      }
   }
   /**
    * @expectedException UnexpectedValueException
    */
   public function testArrayBeheadException()
   {
      array_behead($this->empty_array);
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

      foreach ($patterns as list($expected, $array)) {
         $this->assertEquals($expected, array_depeditate($array));
      }
   }
   /**
    * @expectedException UnexpectedValueException
    */
   public function testArrayDepeditateException()
   {
      array_depeditate($this->empty_array);
   }

   /**
    * @depends testArrayZip
    */
   public function testArrayPartition($ok)
   {
      $odd_expected = [
         [[0 => 1        ], [      ]],
         [[0 => 1        ], [1 => 2]],
         [[0 => 1, 2 => 3], [1 => 2]],

         [['one' => 1              ], [          ]],
         [['one' => 1              ], ['two' => 2]],
         [['one' => 1, 'three' => 3], ['two' => 2]],
      ];
      $patterns = array_zip($odd_expected, $this->arrays);

      foreach ($patterns as list($odd_expected, $array)) {
         $this->assertEquals($odd_expected, array_partition($array, 'is_odd'));
      }

      $even_expected = [
         [[      ], [0 => 1        ]],
         [[1 => 2], [0 => 1        ]],
         [[1 => 2], [0 => 1, 2 => 3]],

         [[          ], ['one' => 1              ]],
         [['two' => 2], ['one' => 1              ]],
         [['two' => 2], ['one' => 1, 'three' => 3]],
      ];
      $patterns = array_zip($even_expected, $this->arrays);

      foreach ($patterns as list($even_expected, $array)) {
         $this->assertEquals($even_expected, array_partition($array, 'is_even'));
      }
   }
}
