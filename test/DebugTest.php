<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class DebugTest extends PHPUnit_Framework_TestCase
{
   private $platitude = 'hello, world!';

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
      $this->assertEquals(withln('<!--<pre>') . $this->platitude . withln('</pre>-->'), html_friendly($this->platitude       ));
      $this->assertEquals(withln(    '<pre>') . $this->platitude . withln('</pre>'   ), html_friendly($this->platitude, false));
   }

   /**
    * @depends testWithln
    */
   public function testPretty()
   {
      $patterns = [
         ['null'           , null ],
         ['false'          , false],
         ['true'           , true ],
         ['0'              , 0    ],
         ['1'              , 1    ],
         ['0.0'            , 0.0  ],
         ['0.0'            , 0.   ],
         ['0.04'           , 0.04 ],
         ['1.0'            , 1.00 ],
         ['""'             , ''   ],
         ['"0"'            , '0'  ],
         ['"a"'            , 'a'  ],
         [withln('[') . ']', []   ],
      ];
      foreach ($patterns as list($expected, $var)) {
         $this->assertEquals(withln($expected), pretty($var));
      }

      $prefix = '>> ';

      $array_expected = array_reduce([
            '['                        ,
            '   "windows" => "10"'     ,
            '   "osx"     => "10.10"'  ,
            '   "linux"   => ['        ,
            '      "ubuntu" => "15.04"',
            '      "rhel"   => "7"'    ,
            '   ]'                     ,
            ']'                        ,
         ], function($text, $row) use($prefix) { return $text . withln("$prefix$row"); }, '');
      $array = [
         'windows' => '10'   ,
         'osx'     => '10.10',
         'linux'   => [
            'ubuntu' => '15.04',
            'rhel'   => '7'    ,
         ]
      ];
      $this->assertEquals($array_expected, pretty($array, $prefix));

      $object_expected = array_reduce([
            'object of Closure {'      ,
            '   object properties => [',
            '   ]'                     ,
            '   static properties => [',
            '   ]'                     ,
            '   methods           => [',
            '      0 => "bind"'        ,
            '      1 => "bindTo"'      ,
            '   ]'                     ,
            '}'                        ,
         ], function($text, $row) use($prefix) { return $text . withln("$prefix$row"); }, '');
      $this->assertEquals($object_expected, pretty(function() { echo 'testPretty'; }, $prefix));
   }
}
