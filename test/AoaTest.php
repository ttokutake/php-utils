<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

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

   public function testAoaValues()
   {
      $expected = ['hoge', 'fuga', 'piyo'];
      $this->assertEquals($expected, aoa_values($this->aoa, 'name'));
   }

   /**
    * @depends testAoaValues
    */
   public function testAoaSum()
   {
      $key      = 'point';
      $expected = array_sum(aoa_values($this->aoa, $key));
      $this->assertEquals($expected, aoa_sum($this->aoa, $key));
   }

   public function testAoaMap()
   {
      $key      = 'point';
      $square   = function ($num) { return pow($num, 2); };
      $expected = array_map(function ($array) use($key, $square) {
            $array[$key] = $square($array[$key]);
            return $array;
         }, $this->aoa);
      $this->assertEquals($expected, aoa_map($this->aoa, $key, $square));
   }

   /**
    * @depends testAoaValues
    */
   public function testAoaReduce()
   {
      $connect  = function ($carry, $str) { return "$carry/$str"; };
      $expected = '/hoge/fuga/piyo';
      $this->assertEquals($expected, aoa_reduce($this->aoa, 'name', $connect, ''));
   }

   public function testAoaFilter()
   {
      $key      = 'id';
      $expected = array_filter($this->aoa, function ($array) use($key) { return is_odd($array[$key]); });
      $this->assertEquals($expected, aoa_filter($this->aoa, $key, 'is_odd'));
   }

   /**
    * @depends testAoaValues
    */
   public function testAoaSort()
   {
      $this->assertEquals([2, 1, 3], aoa_values(aoa_sort($this->aoa, 'name'           ), 'id'));
      $this->assertEquals([3, 2, 1], aoa_values(aoa_sort($this->aoa, 'id'  , SORT_DESC), 'id'));
   }

   /**
    * @depends testAoaValues
    */
   public function testAoaAssociate()
   {
      $target_key = 'email';
      $keys       = aoa_values($this->aoa, $target_key);
      $unset_aoa  = array_map(function ($array) use($target_key) {
            unset($array[$target_key]);
            return $array;
         }, $this->aoa);
      $this->assertEquals(array_combine($keys, $unset_aoa), aoa_associate($this->aoa, $target_key));
   }
}
