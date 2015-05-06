<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class ErrorTest extends PHPUnit_Framework_TestCase
{
   public function testStringOrDefault()
   {
      $this->assertEquals('string'    , string_or_default('string', 'non-string'));
      $this->assertEquals('non-string', string_or_default(       1, 'non-string'));
      $this->assertEquals(''          , string_or_default(     1.1,            1));
   }

   /**
    * @depends           testStringOrDefault
    * @expectedException LogicException
    */
   public function testEnsure()
   {
      ensure(false, 'Message for LogicException');
   }
   /**
    * @depends           testStringOrDefault
    * @expectedException LogicException
    */
   public function testEnsureWithNonStringMessage()
   {
      ensure(false, 1);
   }
   /**
    * @depends           testStringOrDefault
    * @expectedException LogicException
    */
   public function testEnsureWithNonBoolean()
   {
      ensure(1, 'next to non-boolean');
   }

   /**
    * @depends           testStringOrDefault
    * @expectedException RuntimeException
    */
   public function testPlague()
   {
      $success = false or plague('Message for RuntimeException');
   }
   /**
    * @depends           testStringOrDefault
    * @expectedException RuntimeException
    */
   public function testPlagueWithNonStringMessage()
   {
      $success = false or plague(1);
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

   public function testWrapIfString()
   {
      $this->assertEquals('"string"', wrap_if_string('string'));
      $this->assertEquals(         1, wrap_if_string(       1));
   }


   public function testForceNonNegativeInt()
   {
      $this->assertEquals(1, force_non_negative_int(  1));
      $this->assertEquals(0, force_non_negative_int('1'));
   }


   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureNonNull()
   {
      $null = null;
      ensure_non_null($null, 'this');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureBool()
   {
      $not_bool = 0;
      ensure_bool($not_bool, 'argument');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureInt()
   {
      $not_int = 0.0;
      ensure_int($not_int, 'must');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureFloat()
   {
      $not_float = '0.0';
      ensure_float($not_float, 'be');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureNumeric()
   {
      $not_numeric = 'hellow, world!';
      ensure_numeric($not_numeric, 'the');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureString()
   {
      $not_string = true;
      ensure_string($not_string, 'subject');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureScalar()
   {
      $temporary_file = 'testEnsureScalar';
      $not_scalar     = fopen($temporary_file, 'w');
      unlink($temporary_file);
      ensure_scalar($not_scalar, 'of');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureResource()
   {
      $not_resource = [1, 2, 3];
      ensure_resource($not_resource, 'the');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureArray()
   {
      $not_array = function() { return 'callable'; };
      ensure_array($not_array, 'error');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureCallable()
   {
      $not_callable = new Exception('object');
      ensure_callable($not_callable, 'message');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureObject()
   {
      $not_object = null;
      ensure_object($not_object, ':p');
   }

   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureNonEmpty()
   {
      $vacant = false;
      ensure_non_empty($vacant, 'can');
   }

   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsurePositiveInt()
   {
      $non_positive = 0;
      ensure_positive_int($non_positive, 'you');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureNonPositiveInt()
   {
      $negative = -1;
      ensure_positive_int($negative, 'understand');
   }


    private $blowser = ['chrome', 'firefox', 'safari'];
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureInArray()
   {
      $not_in_array = 'ie';
      ensure_in_array($not_in_array, $this->blowser, '?');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureNotInArray()
   {
      $in_array = 'chrome';
      ensure_not_in_array($in_array, $this->blowser, ':)');
   }
}
