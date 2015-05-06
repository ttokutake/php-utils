<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class ErrorTest extends PHPUnit_Framework_TestCase
{
   /**
    * @expectedException LogicException
    */
   public function testEnsure()
   {
      ensure(false, 'Message for LogicException');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureWithNonStringMessage()
   {
      ensure(false, 1);
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureWithNonBoolean()
   {
      ensure(1, 'next to non-boolean');
   }

   /**
    * @expectedException RuntimeException
    */
   public function testPlague()
   {
      $success = false or plague('Message for RuntimeException');
   }
   /**
    * @depends           testPlague
    * @expectedException RuntimeException
    */
   public function testPlagueWithNonStringMessage()
   {
      $success = false or plague(1);
   }


   /**
    * @expectedException LogicException
    */
   public function testEnsureNonNull()
   {
      $null = null;
      ensure_non_null($null, 'this');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureBool()
   {
      $not_bool = 0;
      ensure_bool($not_bool, 'argument');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureInt()
   {
      $not_int = 0.0;
      ensure_int($not_int, 'must');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureFloat()
   {
      $not_float = '0.0';
      ensure_float($not_float, 'be');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureNumeric()
   {
      $not_numeric = 'hellow, world!';
      ensure_numeric($not_numeric, 'the');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureString()
   {
      $not_string = true;
      ensure_string($not_string, 'subject');
   }
   /**
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
    * @expectedException LogicException
    */
   public function testEnsureResource()
   {
      $not_resource = [1, 2, 3];
      ensure_resource($not_resource, 'the');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureArray()
   {
      $not_array = function() { return 'callable'; };
      ensure_array($not_array, 'error');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureCallable()
   {
      $not_callable = new Exception('object');
      ensure_callable($not_callable, 'message');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureObject()
   {
      $not_object = null;
      ensure_object($not_object, ':p');
   }

   /**
    * @expectedException LogicException
    */
   public function testEnsureNonEmpty()
   {
      $vacant = false;
      ensure_non_empty($vacant, 'can');
   }

   /**
    * @expectedException LogicException
    */
   public function testEnsurePositiveInt()
   {
      $non_positive = 0;
      ensure_positive_int($non_positive, 'you');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureNonPositiveInt()
   {
      $negative = -1;
      ensure_positive_int($negative, 'understand');
   }


    private $blowser = ['chrome', 'firefox', 'safari'];
   /**
    * @expectedException LogicException
    */
   public function testEnsureInArray()
   {
      $not_in_array = 'ie';
      ensure_in_array($not_in_array, $this->blowser, '?');
   }
   /**
    * @expectedException LogicException
    */
   public function testEnsureNotInArray()
   {
      $in_array = 'chrome';
      ensure_not_in_array($in_array, $this->blowser, ':)');
   }
}
