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

   public function testDebugAssumingHtml()
   {
      $eol = PHP_EOL;
      $this->expectOutputString("<!--<pre>{$eol}{$this->platitude}{$eol}</pre>-->{$eol}");
      debug_assuming_html($this->platitude, 'echoln');
   }

   public function testDebugAssumingHtmlWithoutCommentOut()
   {
      $str = $this->platitude;
      $eol = PHP_EOL;
      $this->expectOutputString("<pre>{$eol}{$this->platitude}{$eol}</pre>{$eol}");
      debug_assuming_html($this->platitude, 'echoln', false);
   }


   private $array = ['one' => 1, 'two' => 2];

   //public function testVarDumpHtml()
   //{
   //   $eol = PHP_EOL;
   //   $this->expectOutputString("<!--<pre>{$eol}array(2) {{$eol}  [\"one\"]=>{$eol}  int(1){$eol}  [\"two\"]=>{$eol}  int(2){$eol}}{$eol}</pre>-->{$eol}");
   //   var_dump_html($this->array);
   //}

   //public function testVarDumpHtmlWithoutCommentOut()
   //{
   //   $eol = PHP_EOL;
   //   $this->expectOutputString("<pre>{$eol}array(2) {{$eol}  [\"one\"]=>{$eol}  int(1){$eol}  [\"two\"]=>{$eol}  int(2){$eol}}{$eol}</pre>{$eol}");
   //   var_dump_html($this->array, false);
   //}

   public function testPrintRHtml()
   {
      $eol = PHP_EOL;
      $this->expectOutputString("<!--<pre>{$eol}Array{$eol}({$eol}    [one] => 1{$eol}    [two] => 2{$eol}){$eol}</pre>-->{$eol}");
      print_r_html($this->array);
   }

   public function testPrintRHtmlWithoutCommentOut()
   {
      $eol = PHP_EOL;
      $this->expectOutputString("<pre>{$eol}Array{$eol}({$eol}    [one] => 1{$eol}    [two] => 2{$eol}){$eol}</pre>{$eol}");
      print_r_html($this->array, false);
   }
}
