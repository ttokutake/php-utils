<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class AoaTest extends PHPUnit_Framework_TestCase
{
   function testAoaSet()
   {
      $aoa      = [0 => ['key' => 100]];
      $value    = 200;
      $patterns = [
         [[0 => ['key' => $value                 ]    ], [0, 'key']],
         [[0 => ['key' => 100   , 'new' => $value]    ], [0, 'new']],
         [[0 => ['key' => 100], 1 => ['new' => $value]], [1, 'new']],
      ];
      foreach ($patterns as list($expected, $keys)) {
         $this->assertEquals($expected, aoa_set($aoa, $keys, $value));
      }
   }

   function testAoaUnset()
   {
      $aoa      = [0 => ['key' => 100]];
      $patterns = [
         [[0 => []], [0, 'key']],
         [$aoa     , [0, 'new']],
         [$aoa     , [1, 'key']],
      ];
      foreach ($patterns as list($expected, $keys)) {
         $this->assertEquals($expected, aoa_unset($aoa, $keys));
      }
   }

   function testAoaCollect()
   {
      $aoa = [
         'main' => [
            'title'   => 'FF V',
            'authors' => ['A'],
            'words'   => ['crystal', 'job'],
         ],
         'subs' => [
            ['title' => 'FF IV', 'authors' => ['B', 'U'], 'words' => ['crystal', 'dark knight']],
            ['title' => 'FF VI', 'authors' => ['C', 'V'], 'words' => ['magic'  , 'magic stone']],
         ],
      ];
      $expected = [['A'], ['B', 'U'], ['C', 'V']];
      $this->assertEquals($expected, aoa_collect($aoa, 'authors'));
   }


   function testAoaTranspose()
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

   function testAoaValues()
   {
      $expected = ['hoge', 'fuga', 'piyo'];
      $this->assertEquals($expected, aoa_values($this->aoa, 'name'));
   }

   /**
    * @depends testAoaValues
    */
   function testAoaSum()
   {
      $key      = 'point';
      $expected = array_sum(aoa_values($this->aoa, $key));
      $this->assertEquals($expected, aoa_sum($this->aoa, $key));
   }

   /**
    * @depends testAoaValues
    */
   function testAoaSort()
   {
      $this->assertEquals([2, 1, 3], aoa_values(aoa_sort($this->aoa, 'name'           ), 'id'));
      $this->assertEquals([3, 2, 1], aoa_values(aoa_sort($this->aoa, 'id'  , SORT_DESC), 'id'));
   }

   /**
    * @depends testAoaValues
    */
   function testAoaAssociate()
   {
      $target    = 'email';
      $keys      = aoa_values($this->aoa, $target);
      $unset_aoa = array_map(function($array) use($target) { return array_unset($array, $target); }, $this->aoa);
      $this->assertEquals(array_combine($keys, $unset_aoa), aoa_associate($this->aoa, $target));
   }
}
