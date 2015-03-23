<?php

require_once('constants.inc');
require_once(PATH_TO_LIB . '/string.php');

class StringTest extends PHPUnit_Framework_TestCase
{
   public function testSplitAt()
   {
      $platitude = 'hello, world!';
      $patterns = [
         [['', 'hello, world!'], $platitude, -14],
         [['', 'hello, world!'], $platitude, -13],
         [['h', 'ello, world!'], $platitude, -12],
         [['hello, ', 'world!'], $platitude, - 6],
         [['hello, world', '!'], $platitude, - 1],
         [['', 'hello, world!'], $platitude,   0],
         [['h', 'ello, world!'], $platitude,   1],
         [['hello, ', 'world!'], $platitude,   7],
         [['hello, world', '!'], $platitude,  12],
         [['hello, world!', ''], $platitude,  13],
         [['hello, world!', ''], $platitude,  14],
      ];
      foreach ($patterns as list($expected, $str, $at)) {
         $this->assertEquals($expected, split_at($str, $at));
      }

      $mb_str = 'こんにちは、世界！';
      $this->assertEquals(['こんにちは、', '世界！'], split_at($mb_str, 6));
   }
}
