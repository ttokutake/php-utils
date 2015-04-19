<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class DebugTest extends PHPUnit_Framework_TestCase
{
   private $platitude = 'hello, world!';

   public function testEcholn()
   {
      $this->expectOutputString($this->platitude . PHP_EOL);
      echoln($this->platitude);
   }

   /**
    * @depends testEcholn
    */
   public function testDebugAssumingHtml()
   {
      $eol = PHP_EOL;
      $this->expectOutputString("<!--<pre>{$eol}{$this->platitude}{$eol}</pre>-->{$eol}");
      debug_assuming_html($this->platitude, 'echoln');
   }

   /**
    * @depends testEcholn
    */
   public function testDebugAssumingHtmlWithoutCommentOut()
   {
      $eol = PHP_EOL;
      $this->expectOutputString("<pre>{$eol}{$this->platitude}{$eol}</pre>{$eol}");
      debug_assuming_html($this->platitude, 'echoln', false);
   }
}
