<?php

require_once('array.php');

class ArrayTest extends PHPUnit_Framework_TestCase
{
   private $arrays = [
      [],

      [1      ],
      [1, 2   ],
      [1, 2, 3],

      ['one' => 1                          ],
      ['one' => 1, 'two' => 2              ],
      ['one' => 1, 'two' => 2, 'three' => 3],
   ];

   public function testArrayZipForArrayBehead()
   {
      $next_expected = [
         [null, []],

         [1, [    ]],
         [1, [2   ]],
         [1, [2, 3]],

         [1, [                        ]],
         [1, ['two' => 2              ]],
         [1, ['two' => 2, 'three' => 3]],
      ];

      $patterns = array_zip($next_expected, $this->arrays);
      $expected = array_map(function ($e1, $e2) { return [$e1, $e2]; }, $next_expected, $this->arrays);

      $this->assertEquals($expected, $patterns);

      return $patterns;
   }
   /**
    * @depends testArrayZipForArrayBehead
    */
   public function testArrayBehead($patterns)
   {
      foreach ($patterns as list($expected, $arrays)) {
         $this->assertEquals($expected, array_behead($arrays));
      }
   }

   public function testArrayZipForArrayDepeditate()
   {
      $next_expected = [
         [[], null],

         [[    ], 1],
         [[1   ], 2],
         [[1, 2], 3],

         [[                      ], 1],
         [['one' => 1            ], 2],
         [['one' => 1, 'two' => 2], 3],
      ];

      $patterns = array_zip($next_expected, $this->arrays);
      $expected = array_map(function ($e1, $e2) { return [$e1, $e2]; }, $next_expected, $this->arrays);

      $this->assertEquals($expected, $patterns);

      return $patterns;
   }
   /**
    * @depends testArrayZipForArrayDepeditate
    */
   public function testArrayDepeditate($patterns)
   {
      foreach ($patterns as list($expected, $arrays)) {
         $this->assertEquals($expected, array_depeditate($arrays));
      }
   }
}
