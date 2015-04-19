<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class ArrayTest extends PHPUnit_Framework_TestCase
{
   private $array = ['defined_key' => null, 'not_null' => true];

   /**
    * @expectedException PHPUnit_Framework_Error_Notice
    */
   public function testPhpNotice()
   {
      echo $this->array['undefined_key'];
   }

   public function testArrayGet()
   {
      $this->assertNull(array_get($this->array, 'undefined_key'));
      $this->assertNull(array_get($this->array, 'defined_key'  ));
      $this->assertTrue(array_get($this->array, 'not_null'     ));
   }

   public function testArrayGetOrElse()
   {
      $default = false;
      $this->assertFalse(array_get_or_else($this->array, 'undefined_key', $default));
      $this->assertNull (array_get_or_else($this->array, 'defined_key'  , $default));
      $this->assertTrue (array_get_or_else($this->array, 'not_null'     , $default));
   }

   public function testArrayMapWithKey()
   {
      $pattern = [['one' => 'one => 1'], ['one' => 1]];
      $this->assertEquals($pattern[0], array_map_with_key($pattern[1], function ($key, $value) { return "$key => $value"; }));
   }


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


   public function testArrayHat()
   {
      $patterns = [
         [[0   ], [ ], 0],
         [[1, 0], [0], 1],
      ];
      foreach ($patterns as list($expected, $array, $value)) {
         $this->assertEquals($expected, array_hat($array, $value));
      }
   }

   public function testArrayShoe()
   {
      $patterns = [
         [[0   ], [ ], 0],
         [[0, 1], [0], 1],
      ];
      foreach ($patterns as list($expected, $array, $value)) {
         $this->assertEquals($expected, array_shoe($array, $value));
      }
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
      $expectations = [
         [1, [    ]],
         [1, [2   ]],
         [1, [2, 3]],

         [1, [                        ]],
         [1, ['two' => 2              ]],
         [1, ['two' => 2, 'three' => 3]],
      ];
      foreach (array_zip($expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_behead($array));
      }
   }
   /**
    * @depends           testArrayBehead
    * @expectedException LogicException
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
      $expectations = [
         [[    ], 1],
         [[1   ], 2],
         [[1, 2], 3],

         [[                      ], 1],
         [['one' => 1            ], 2],
         [['one' => 1, 'two' => 2], 3],
      ];
      foreach (array_zip($expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_depeditate($array));
      }
   }
   /**
    * @depends           testArrayDepeditate
    * @expectedException LogicException
    */
   public function testArrayDepeditateException()
   {
      array_depeditate($this->empty_array);
   }

   /**
    * @depends testArrayZip
    */
   public function testArrayTake()
   {
      $expectations = [
         [1   ],
         [1, 2],
         [1, 2],

         ['one' => 1            ],
         ['one' => 1, 'two' => 2],
         ['one' => 1, 'two' => 2],
      ];
      foreach (array_zip($expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_take($array, 2));
      }
   }
   /**
    * @depends           testArrayTake
    * @expectedException LogicException
    */
   public function testArrayTakeException()
   {
      array_take([1, 2, 3], -1);
   }

   /**
    * @depends testArrayZip
    */
   public function testArrayDrop()
   {
      $expectations = [
         [ ],
         [ ],
         [3],

         [            ],
         [            ],
         ['three' => 3],
      ];
      foreach (array_zip($expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_drop($array, 2));
      }
   }
   /**
    * @depends           testArrayDrop
    * @expectedException LogicException
    */
   public function testArrayDropException()
   {
      array_drop([1, 2, 3], -1);
   }


   /**
    * @depends testArrayZip
    */
   public function testArrayFind($ok)
   {
      $odd_expected = [1, 1, 1];
      foreach (array_zip($odd_expected, $this->arrays) as list($expected, $array))
      {
         $this->assertEquals($expected, array_find($array, 'is_odd'));
      }
      $even_expected = [null, 2, 2];
      foreach (array_zip($even_expected, $this->arrays) as list($expected, $array))
      {
         $this->assertEquals($expected, array_find($array, 'is_even'));
      }
   }

   /**
    * @depends testArrayZip
    */
   public function testArrayPartition($ok)
   {
      $odd_expectations = [
         [[0 => 1        ], [      ]],
         [[0 => 1        ], [1 => 2]],
         [[0 => 1, 2 => 3], [1 => 2]],

         [['one' => 1              ], [          ]],
         [['one' => 1              ], ['two' => 2]],
         [['one' => 1, 'three' => 3], ['two' => 2]],
      ];
      foreach (array_zip($odd_expectations, $this->arrays) as list($odd_expected, $array)) {
         $this->assertEquals($odd_expected, array_partition($array, 'is_odd'));
      }

      $even_expectations = [
         [[      ], [0 => 1        ]],
         [[1 => 2], [0 => 1        ]],
         [[1 => 2], [0 => 1, 2 => 3]],

         [[          ], ['one' => 1              ]],
         [['two' => 2], ['one' => 1              ]],
         [['two' => 2], ['one' => 1, 'three' => 3]],
      ];
      foreach (array_zip($even_expectations, $this->arrays) as list($even_expected, $array)) {
         $this->assertEquals($even_expected, array_partition($array, 'is_even'));
      }
   }
}
