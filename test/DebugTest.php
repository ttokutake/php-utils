<?php

require_once('../lib/debug.php');

class DebugTest extends PHPUnit_Framework_TestCase
{
   private $platitude = 'hello, world!';

   public function testEcholn()
   {
      $this->expectOutputString("{$this->platitude}\n");
      echoln($this->platitude);
   }

   public function testDebugAssumingHtml()
   {
      $this->expectOutputString("<!--<pre>\n{$this->platitude}\n</pre>-->\n");
      debug_assuming_html($this->platitude, 'echoln');
   }

   public function testDebugAssumingHtmlWithoutCommentOut()
   {
      $str = $this->platitude;
      $this->expectOutputString("<pre>\n{$this->platitude}\n</pre>\n");
      debug_assuming_html($this->platitude, 'echoln', false);
   }


   private $array = ['one' => 1, 'two' => 2];

   public function testVarDumpHtml()
   {
      $this->expectOutputString("<!--<pre>\narray(2) {\n  [\"one\"]=>\n  int(1)\n  [\"two\"]=>\n  int(2)\n}\n</pre>-->\n");
      var_dump_html($this->array);
   }

   public function testVarDumpHtmlWithoutCommentOut()
   {
      $this->expectOutputString("<pre>\narray(2) {\n  [\"one\"]=>\n  int(1)\n  [\"two\"]=>\n  int(2)\n}\n</pre>\n");
      var_dump_html($this->array, false);
   }

   public function testPrintRHtml()
   {
      $this->expectOutputString("<!--<pre>\nArray\n(\n    [one] => 1\n    [two] => 2\n)\n</pre>-->\n");
      print_r_html($this->array);
   }

   public function testPrintRHtmlWithoutCommentOut()
   {
      $this->expectOutputString("<pre>\nArray\n(\n    [one] => 1\n    [two] => 2\n)\n</pre>\n");
      print_r_html($this->array, false);
   }
}
