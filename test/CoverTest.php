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
      $this->assertEquals('null'     , to_type(null                        ));
      $this->assertEquals('boolean'  , to_type(true                        ));
      $this->assertEquals('integer'  , to_type(1                           ));
      $this->assertEquals('float'    , to_type(1.1                         ));
      $this->assertEquals('string'   , to_type('string'                    ));
      $f = fopen('testToType', 'w');
      $this->assertEquals('resource' , to_type($f                          ));
      fclose($f);
      unlink('testToType');
      $this->assertEquals('array'    , to_type([1, 2, 3]                   ));
      $this->assertEquals('Closure'  , to_type(function ($a) { return $a; }));
      $this->assertEquals('Exception', to_type(new Exception('class test') ));
   }

   public function testToString()
   {
      $this->assertEquals('null'               , to_string(null                        ));
      $this->assertEquals('true'               , to_string(true                        ));
      $this->assertEquals('false'              , to_string(false                       ));
      $this->assertEquals('1'                  , to_string(1                           ));
      $this->assertEquals('1.0'                , to_string(1.0                         ));
      $this->assertEquals('1.01'               , to_string(1.010                       ));
      $this->assertEquals('string'             , to_string('string'                    ));
      $this->assertEquals('array'              , to_string([1, 2, 3]                   ));
      $this->assertEquals('object of Closure'  , to_string(function ($a) { return $a; }));
      $this->assertEquals('object of Exception', to_string(new Exception('class test') ));
   }
}
