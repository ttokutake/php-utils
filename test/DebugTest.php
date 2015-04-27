<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class DebugTest extends PHPUnit_Framework_TestCase
{
   private $vars = [
      null ,
      false,
      true ,
      0    ,
      1    ,
      0.0  ,
      0.1  ,
      1.0  ,
      ''   ,
      '0'  ,
      'a'  ,
      []   ,
   ];

   public function testToString()
   {
      $expectations = [
         'null' ,
         'false',
         'true' ,
         '0'    ,
         '1'    ,
         '0.0'  ,
         '0.1'  ,
         '1.0'  ,
         ''     ,
         '0'    ,
         'a'    ,
         'array',
      ];
      foreach (array_zip($expectations, $this->vars) as list($expected, $var)) {
         $this->assertEquals($expected, to_string($var));
      }

      $closure = function () { return 'closure'; };
      $this->assertEquals('class Closure', to_string($closure));

      $resource = fopen('testToString', 'w');
      $this->assertEquals('resource', to_string($resource));
      unlink('testToString');

      // class test?
   }

   private $platitude = 'hello, world!';

   /**
    * @depends testToString
    */
   public function testWithln()
   {
      $this->assertEquals($this->platitude . PHP_EOL, withln($this->platitude));
   }

   /**
    * @depends testWithln
    */
   public function testEcholn()
   {
      $this->expectOutputString($this->platitude . PHP_EOL);
      echoln($this->platitude);
   }

   /**
    * @depends testWithln
    */
   public function testHtmlFriendly()
   {
      $eol = PHP_EOL;
      $this->assertEquals("<!--<pre>$eol" . $this->platitude . "</pre>-->$eol", html_friendly($this->platitude       ));
      $this->assertEquals("<pre>$eol"     . $this->platitude . "</pre>$eol"   , html_friendly($this->platitude, false));
   }

   /**
    * @depends testWithln
    */
   public function testPretty()
   {
      $this->assertTrue(true);
   }
}
