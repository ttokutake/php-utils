<?php

require_once(implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'constants.inc']));
require_lib('array_of_array.inc');
require_lib('array.inc');

class AoaTest extends PHPUnit_Framework_TestCase
{
   public function testAoaTranspose()
   {
      $inputs = [
         [
            [1, 2, 3],
         ],
         [
            [1],
            [2],
            [3],
         ],
         [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9],
         ],
      ];
      $outputs = [
         [
            [1],
            [2],
            [3],
         ],
         [
            [1, 2, 3],
         ],
         [
            [1, 4, 7],
            [2, 5, 8],
            [3, 6, 9],
         ],

      ];
      foreach (array_zip($outputs, $inputs) as list($expected, $input)) {
         $this->assertEquals($expected, aoa_transpose($input));
      }
   }

   private $aoa = [
      [
         'id'    => 1               ,
         'name'  => 'hoge'          ,
         'email' => 'hoge@localhost',
         'point' => 22              ,
      ],
      [
         'id'    => 2               ,
         'name'  => 'fuga'          ,
         'email' => 'fuga@localhost',
         'point' => 80              ,
      ],
      [
         'id'    => 3               ,
         'name'  => 'piyo'          ,
         'email' => 'piyo@localhost',
         'point' => 443             ,
      ],
   ];

   public function testAoaSum()
   {
      $expected = 22 + 80 + 443;
      $this->assertEquals($expected, aoa_sum($this->aoa, 'point'));
   }

   public function testAoaAssociate()
   {
      $expected = [
         'hoge@localhost' =>
            [
               'id'    => 1     ,
               'name'  => 'hoge',
               'point' => 22    ,
            ],
         'fuga@localhost' =>
            [
               'id'    => 2     ,
               'name'  => 'fuga',
               'point' => 80    ,
            ],
         'piyo@localhost' =>
            [
               'id'    => 3     ,
               'name'  => 'piyo',
               'point' => 443   ,
            ],
      ];
      $this->assertEquals($expected, aoa_associate($this->aoa, 'email'));
   }
}
