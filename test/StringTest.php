<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class StringTest extends PHPUnit_Framework_TestCase
{
   private $platitude    = 'hello, world!';
   private $mb_platitude = 'こんにちは、世界！';

   public function testSplitAt()
   {
      $patterns = [
         [['', 'hello, world!'], -14],
         [['', 'hello, world!'], -13],
         [['h', 'ello, world!'], -12],
         [['hello, ', 'world!'], - 6],
         [['hello, world', '!'], - 1],
         [['', 'hello, world!'],   0],
         [['h', 'ello, world!'],   1],
         [['hello, ', 'world!'],   7],
         [['hello, world', '!'],  12],
         [['hello, world!', ''],  13],
         [['hello, world!', ''],  14],
      ];
      foreach ($patterns as list($expected, $at)) {
         $this->assertEquals($expected, split_at($this->platitude, $at));
      }
      $mb_patterns = [
         [['こ', 'んにちは、世界！'], 1],
         [['こんにちは、', '世界！'], 6],
         [['こんにちは、世界', '！'], 8],
      ];
      foreach ($mb_patterns as list($expected, $at)) {
         $this->assertEquals($expected, split_at($this->mb_platitude, $at));
      }
   }

   public function testStartWith()
   {
      $patterns = [
         [true , 'hello'],
         [false, 'ello,'],
      ];
      foreach ($patterns as list($expected, $needle)) {
         $this->assertEquals($expected, start_with($this->platitude, $needle));
      }
      $mb_patterns = [
         [true , 'こんにちは'],
         [false, 'んにちは、'],
      ];
      foreach ($mb_patterns as list($expected, $needle)) {
         $this->assertEquals($expected, start_with($this->mb_platitude, $needle));
      }
   }

   public function testEndWith()
   {
      $patterns = [
         [true , 'world!'],
         [false, ' world'],
      ];
      foreach ($patterns as list($expected, $needle)) {
         $this->assertEquals($expected, end_with($this->platitude, $needle));
      }
      $mb_patterns = [
         [true , '世界！'],
         [false, '、世界'],
      ];
      foreach ($mb_patterns as list($expected, $needle)) {
         $this->assertEquals($expected, end_with($this->mb_platitude, $needle));
      }
   }
}
