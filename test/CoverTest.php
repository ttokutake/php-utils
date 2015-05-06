<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class CoverTest extends PHPUnit_Framework_TestCase
{
   public function testStringOrDefault()
   {
      $this->assertEquals('string'    , string_or_default('string', 'non-string'));
      $this->assertEquals('non-string', string_or_default(       1, 'non-string'));
      $this->assertEquals(''          , string_or_default(     1.1,            1));
   }

   public function testForceNonNegativeInt()
   {
      $this->assertEquals(1, force_non_negative_int(  1));
      $this->assertEquals(0, force_non_negative_int('1'));
   }

   public function testWrapIfString()
   {
      $this->assertEquals('"string"', wrap_if_string('string'));
      $this->assertEquals(         1, wrap_if_string(       1));
   }

   public function testToType()
   {
      $f = fopen('testToType', 'w');
      $patterns = [
         ['null'     , null                             ],
         ['boolean'  , true                             ],
         ['integer'  , 1                                ],
         ['float'    , 1.1                              ],
         ['string'   , 'string'                         ],
         ['resource' , $f                               ],
         ['array'    , [1, 2, 3]                        ],
         ['Closure'  , function() { echo 'testToType'; }],
         ['Exception', new Exception('testToType')      ],
      ];
      foreach ($patterns as list($expected, $var)) {
         $this->assertEquals($expected, to_type($var));
      }
      fclose($f);
      unlink('testToType');
   }

   public function testToString()
   {
      $patterns = [
         ['null'               , null                               ],
         ['true'               , true                               ],
         ['false'              , false                              ],
         ['1'                  , 1                                  ],
         ['1.0'                , 1.                                 ],
         ['1.0'                , 1.0                                ],
         ['1.04'               , 1.040                              ],
         ['string'             , 'string'                           ],
         ['array'              , [1, 2, 3]                          ],
         ['object of Closure'  , function() { echo 'testToString'; }],
         ['object of Exception', new Exception('testToString')      ],
      ];
      foreach ($patterns as list($expected, $var)) {
         $this->assertEquals($expected, to_string($var));
      }
   }
}
