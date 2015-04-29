<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class ArrayTest extends PHPUnit_Framework_TestCase
{
   public function testIsSeq()
   {
      $true_expectations = [
         [       ],
         [1      ],
         [1, 2   ],
         [1, 2, 3],

         [ 0  => 1,  1  => 2,  2  => 3],
         ['0' => 1, '1' => 2, '2' => 3],
      ];
      foreach ($true_expectations as $array) {
         $this->assertTrue(is_seq($array));
      }
      $false_expectations = [
         [ 1  => 1,  2  => 2,  3  => 3],
         ['a' => 1, 'b' => 2, 'c' => 3],
      ];
      foreach ($false_expectations as $array) {
         $this->assertFalse(is_seq($array));
      }
   }


   public function testArraySet()
   {
      $array    = [0 => null];
      $patterns = [
         [[0     => true                ], 0    , true ],
         [[0     => null, 'key' => false], 'key', false],
      ];
      foreach ($patterns as list($expected, $key, $value)) {
         $this->assertEquals($expected, array_set($array, $key, $value));
      }
   }

   public function testArrayUnset()
   {
      $array = [
         0     => true ,
         'key' => false,
      ];
      $patterns = [
         [['key' => false], 0       ],
         [[0     => true ], 'key'   ],
         [$array          , 'no_key'],
      ];
      foreach ($patterns as list($expected, $key)) {
         $this->assertEquals($expected, array_unset($array, $key));
      }
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

   private $array = [
      'defined key'  => null ,
      'not null'     => true ,
      'empty bool'   => false,
      'empty int'    => 0    ,
      'empty float'  => 0.0  ,
      'empty string' => ''   ,
      'empty array'  => []   ,
   ];

   /**
    * @expectedException PHPUnit_Framework_Error_Notice
    */
   public function testPhpNotice()
   {
      echo $this->array['undefined key'];
   }

   /**
    * @depends testPhpNotice
    */
   public function testArrayGet()
   {
      $this->assertNull(array_get($this->array, 'undefined key'));
      $this->assertNull(array_get($this->array, 'defined key'  ));
      $this->assertTrue(array_get($this->array, 'not null'     ));
   }

   /**
    * @depends testPhpNotice
    */
   public function testArrayGetOrElse()
   {
      $default = false;
      $this->assertFalse(array_get_or_else($this->array, 'undefined key', $default));
      $this->assertNull (array_get_or_else($this->array, 'defined key'  , $default));
      $this->assertTrue (array_get_or_else($this->array, 'not null'     , $default));
   }

   /**
    * @depends testPhpNotice
    */
   public function testArrayGetNonNull()
   {
      $default = false;
      $this->assertFalse(array_get_non_null($this->array, 'undefined key', $default));
      $this->assertFalse(array_get_non_null($this->array, 'defined key'  , $default));
      $this->assertTrue (array_get_non_null($this->array, 'not null'     , $default));
   }

   /**
    * @depends testPhpNotice
    */
   public function testArrayGetNonEmpty()
   {
      $default = 1;
      $this->assertEquals($default, array_get_non_empty($this->array, 'undefined key', $default));
      $this->assertEquals($default, array_get_non_empty($this->array, 'defined key'  , $default));
      $this->assertEquals($default, array_get_non_empty($this->array, 'empty bool'   , $default));
      $this->assertEquals($default, array_get_non_empty($this->array, 'empty int'    , $default));
      $this->assertEquals($default, array_get_non_empty($this->array, 'empty floaat' , $default));
      $this->assertEquals($default, array_get_non_empty($this->array, 'empty string' , $default));
      $this->assertEquals($default, array_get_non_empty($this->array, 'empty array'  , $default));
      $this->assertTrue(array_get_or_else($this->array, 'not null', $default));
   }

   public function testArrayFilterNot()
   {
      $array = [0, 1, 2];
      $this->assertEquals([0 => 0], array_filter_not($array           ));
      $this->assertEquals([1 => 1], array_filter_not($array, 'is_even'));
   }

   public function testArrayMapWithKey()
   {
      $patterns = [
         [['one' => 'one => 1'], ['one' => 1], function ($key, $value) { return "$key => $value"; }],
      ];
      foreach ($patterns as list($expected, $array, $closure)) {
         $this->assertEquals($expected, array_map_with_key($array, $closure));
      }
   }

   public function testArrayReduceWithKey()
   {
      $patterns = [
         ['- key => value', ['key' => 'value'], function ($carry, $key, $value) { return "$carry$key => $value"; }],
      ];
      foreach ($patterns as list($expected, $array, $closure)) {
         $this->assertEquals($expected, array_reduce_with_key($array, $closure, '- '));
      }
   }

   public function testArrayFilterWithKey()
   {
      $patterns = [
         [[1 => 1], [1 => 1], function ($key, $value) { return is_even($key + $value); }],
         [[      ], [1 => 1], function ($key, $value) { return is_odd ($key + $value); }],
      ];
      foreach ($patterns as list($expected, $array, $closure)) {
         $this->assertEquals($expected, array_filter_with_key($array, $closure));
      }
   }

   public function testArrayFlatten()
   {
      $patterns = [
         [[       ], [             ]],
         [[1, 2, 3], [1  , 2  , 3  ]],
         [[1, 2, 3], [[1], 2  , 3  ]],
         [[1, 2, 3], [[1 , 2] , 3  ]],
         [[1, 2, 3], [[1], 2  , [3]]],
         [[1, 2, 3], [[1 , 2] , [3]]],
         [[1, 2, 3], [[1], [2], [3]]],
      ];
      foreach ($patterns as list($expected, $array)) {
         $this->assertEquals($expected, array_flat($array));
      }
   }


   /**
    * @depends testArrayShoe
    */
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
    * @expectedException LogicException
    */
   public function testArrayBeheadException()
   {
      array_behead($this->array['empty array']);
   }
   /**
    * @depends testArrayZip
    */
   public function testArrayBehead()
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
    * @expectedException LogicException
    */
   public function testArrayDepeditateException()
   {
      array_depeditate($this->array['empty array']);
   }
   /**
    * @depends testArrayZip
    */
   public function testArrayDepeditate()
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
    * @expectedException LogicException
    */
   public function testArrayTakeException()
   {
      array_take([1, 2, 3], -1);
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
    * @depends testArrayTake
    */
   public function testArrayTakeRight()
   {
      $expectations = [
         [1   ],
         [1, 2],
         [2, 3],

         ['one' => 1              ],
         ['one' => 1, 'two'   => 2],
         ['two' => 2, 'three' => 3],
      ];
      foreach (array_zip($expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_take_right($array, 2));
      }
   }

   /**
    * @expectedException LogicException
    */
   public function testArrayDropException()
   {
      array_drop([1, 2, 3], -1);
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
    * @depends testArrayDrop
    */
   public function testArrayDropRight()
   {
      $expectations = [
         [ ],
         [ ],
         [1],

         [          ],
         [          ],
         ['one' => 1],
      ];
      foreach (array_zip($expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_drop_right($array, 2));
      }
   }

   public function testArraySplit()
   {
      $array    = [1, 2, 3];
      $patterns = [
         [[[       ], [1,      2,      3]], 0],
         [[[1      ], [   1 => 2, 2 => 3]], 1],
         [[[1, 2   ], [           2 => 3]], 2],
         [[[1, 2, 3], [                 ]], 3],
      ];
      foreach ($patterns as list($expected, $offset)) {
         $this->assertEquals($expected, array_split($array, $offset));
      }
   }


   /**
    * @depends testArrayZip
    */
   public function testArrayExist()
   {
      $odd_expectations = array_fill(0, 6, true);
      foreach (array_zip($odd_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_exist($array, 'is_odd'));
      }
      $even_expectations = [false, true, true, false, true, true];
      foreach (array_zip($even_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_exist($array, 'is_even'));
      }
   }

   /**
    * @depends testArrayExist
    */
   public function testArrayForAll()
   {
      $odd_expectations = [true, false, false, true, false, false];
      foreach (array_zip($odd_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_for_all($array, 'is_odd'));
      }
      $even_expectations = array_fill(0, 6, false);
      foreach (array_zip($even_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_for_all($array, 'is_even'));
      }
   }

   /**
    * @depends testArrayZip
    */
   public function testArrayFind()
   {
      $odd_expectations = array_fill(0, 6, 1);
      foreach (array_zip($odd_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_find($array, 'is_odd'));
      }
      $even_expectations = [null, 2, 2, null, 2, 2];
      foreach (array_zip($even_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_find($array, 'is_even'));
      }
   }

   /**
    * @depends testArrayZip
    */
   public function testArrayPartition()
   {
      $odd_expectations = [
         [[0 => 1        ], [      ]],
         [[0 => 1        ], [1 => 2]],
         [[0 => 1, 2 => 3], [1 => 2]],

         [['one' => 1              ], [          ]],
         [['one' => 1              ], ['two' => 2]],
         [['one' => 1, 'three' => 3], ['two' => 2]],
      ];
      foreach (array_zip($odd_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_partition($array, 'is_odd'));
      }

      $even_expectations = [
         [[      ], [0 => 1        ]],
         [[1 => 2], [0 => 1        ]],
         [[1 => 2], [0 => 1, 2 => 3]],

         [[          ], ['one' => 1              ]],
         [['two' => 2], ['one' => 1              ]],
         [['two' => 2], ['one' => 1, 'three' => 3]],
      ];
      foreach (array_zip($even_expectations, $this->arrays) as list($expected, $array)) {
         $this->assertEquals($expected, array_partition($array, 'is_even'));
      }
   }
}
