<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class DebugTest extends PHPUnit_Framework_TestCase
{
   private $patterns = [
      ['null' , null ],
      ['false', false],
      ['true' , true ],
      ['0'    , 0    ],
      ['1'    , 1    ],
      ['0.0'  , 0.0  ],
      ['0.04' , 0.04 ],
      ['1.0'  , 1.00 ],
   ];

   public function testToString()
   {
      $closure = function() { return 'closure'; };
      $added_patterns = [
         [''                                  , ''      ],
         ['0'                                 , '0'     ],
         ['a'                                 , 'a'     ],
         ['array'                             , []      ],
         ['instance of ' . get_class($closure), $closure],
      ];
      foreach (array_merge($this->patterns, $added_patterns) as list($expected, $var)) {
         $this->assertEquals($expected, to_string($var));
      }

      $resource = fopen('testToString', 'w');
      $this->assertEquals('resource <' . get_resource_type($resource) . '> #' . intval($resource), to_string($resource));
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
      $this->assertEquals(withln('<!--<pre>') . $this->platitude . withln('</pre>-->'), html_friendly($this->platitude       ));
      $this->assertEquals(withln(    '<pre>') . $this->platitude . withln('</pre>'   ), html_friendly($this->platitude, false));
   }

   /**
    * @depends testWithln
    */
   public function testPretty()
   {
      $added_patterns = [
         ['""'             , '' ],
         ['"0"'            , '0'],
         ['"a"'            , 'a'],
         [withln('[') . ']', [] ],
      ];
      foreach (array_merge($this->patterns, $added_patterns) as list($expected, $var)) {
         $this->assertEquals(withln($expected), pretty($var));
      }

      $expected = array_reduce([
            '!! ['                        ,
            '!!    "windows" => "10"'     ,
            '!!    "osx"     => "10.10"'  ,
            '!!    "linux"   => ['        ,
            '!!       "ubuntu" => "15.04"',
            '!!       "rhel"   => "7"'    ,
            '!!    ]'                     ,
            '!! ]'                        ,
         ], function($text, $row) { return $text . withln($row); }, '');
      $array = [
         'windows' => '10'   ,
         'osx'     => '10.10',
         'linux'   => [
            'ubuntu' => '15.04',
            'rhel'   => '7'    ,
         ]
      ];
      $this->assertEquals($expected, pretty($array, '!! '));

      // class test?
   }
}
