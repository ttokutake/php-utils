<?php

require_once('string.php');

class StringTest extends PHPUnit_Framework_TestCase
{
   public function testSplitAt()
   {
      $str = 'hello, world!';
      $this->assertEquals(['hello, ', 'world!'], split_at($str, 7));

      $mb_str = 'こんにちは、世界！';
      $this->assertEquals(['こんにちは、', '世界！'], split_at($mb_str, 6));
   }
}
