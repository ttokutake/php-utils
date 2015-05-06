<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

class ErrorTest extends PHPUnit_Framework_TestCase
{
   public function testEnsure()
   {
      $true_equations = [
         is_null  (null),
         is_int   (0   ),
         is_float (0.0 ),
         is_string(''  ),
         is_array ([]  ),

         is_callable(function() { echo "testEnsure"; }),
      ];
      foreach ($true_equations as $true_equation) {
         ensure($true_equation, 'This line will be passed!');
      }
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureWithFalseEquation()
   {
      ensure(0 < 0, 'Message for LogicException');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureWithoutBoolean()
   {
      ensure(1, 'next to non-boolean');
   }
   /**
    * @depends           testEnsure
    * @expectedException LogicException
    */
   public function testEnsureWithoutStringMessage()
   {
      ensure(1 < 1, 1);
   }

   public function testPlague()
   {
      $f = fopen('testPlague', 'w') or plague('This line will not be passed!');
      fclose($f);
      unlink('testPlague');
   }
   /**
    * @expectedException RuntimeException
    */
   public function testPlagueWithEmptyEquation()
   {
      $f = false or plague('Message for RuntimeException');
   }
   /**
    * @expectedException RuntimeException
    */
   public function testPlagueWithoutString()
   {
      $f = false or plague(1);
   }


   public function testEnsureBool()
   {
      $bool = false;
      ensure_bool($bool, 'argument');
   }
   /**
    * @depends           testEnsureBool
    * @expectedException LogicException
    */
   public function testEnsureBoolWithoutBoolean()
   {
      $non_bool = 0;
      ensure_bool($non_bool, 'argument');
   }

   public function testEnsureInt()
   {
      $int = 0;
      ensure_int($int, 'must');
   }
   /**
    * @depends           testEnsureInt
    * @expectedException LogicException
    */
   public function testEnsureIntWithoutInt()
   {
      $non_int = 0.0;
      ensure_int($non_int, 'must');
   }

   public function testEnsureFloat()
   {
      $float = 0.0;
      ensure_float($float, 'be');
   }
   /**
    * @depends           testEnsureFloat
    * @expectedException LogicException
    */
   public function testEnsureFloatWithoutFloat()
   {
      $non_float = '0.0';
      ensure_float($non_float, 'be');
   }

   public function testEnsureNumeric()
   {
      $numerics = [
         0   ,
         1   ,
         0.0 ,
         0.  ,
         '0' ,
         '0.',
      ];
      foreach ($numerics as $numeric) {
         ensure_numeric($numeric, 'the');
      }
   }
   /**
    * @depends           testEnsureNumeric
    * @expectedException LogicException
    */
   public function testEnsureNumericWithoutNumeric()
   {
      $not_numeric = 'string';
      ensure_numeric($not_numeric, 'the');
   }

   public function testEnsureString()
   {
      $string = 'string';
      ensure_string($string, 'subject');
   }
   /**
    * @depends           testEnsureString
    * @expectedException LogicException
    */
   public function testEnsureStringWithoutString()
   {
      $non_string = true;
      ensure_string($non_string, 'subject');
   }

   public function testEnsureScalar()
   {
      $scalars = [
         false,
         0    ,
         0.0  ,
         ''   ,
      ];
      foreach ($scalars as $scalar) {
         ensure_scalar($scalar, 'of');
      }
   }
   /**
    * @depends           testEnsureScalar
    * @expectedException LogicException
    */
   public function testEnsureScalarWithoutScalar()
   {
      $not_scalar = fopen('testEnsureScalarWithoutScalar', 'w');
      unlink('testEnsureScalarWithoutScalar');
      ensure_scalar($not_scalar, 'of');
   }

   public function testEnsureResource()
   {
      $resource = fopen('testEnsureResource', 'w');
      ensure_resource($resource, 'the');
      fclose($resource);
      unlink('testEnsureResource');
   }
   /**
    * @depends           testEnsureResource
    * @expectedException LogicException
    */
   public function testEnsureResourceWithoutResource()
   {
      $non_resource = [1, 2, 3];
      ensure_resource($non_resource, 'the');
   }

   public function testEnsureArray()
   {
      $array = [];
      ensure_array($array, 'error');
   }
   /**
    * @depends           testEnsureArray
    * @expectedException LogicException
    */
   public function testEnsureArrayWithoutArray()
   {
      $non_array = function() { echo 'testEnsureArray'; };
      ensure_array($non_array, 'error');
   }

   public function testEnsureCallable()
   {
      $callable = function() { echo 'testEnsureCallable'; };
      ensure_callable($callable, 'message');
   }
   /**
    * @depends           testEnsureCallable
    * @expectedException LogicException
    */
   public function testEnsureCallableWithoutCallable()
   {
      $not_callable = new Exception('testEnsureCallableWithoutCallable');
      ensure_callable($not_callable, 'message');
   }

   public function testEnsureObject()
   {
      $object = new Exception('testEnsureObject');
      ensure_object($object, ':p');
   }
   /**
    * @depends           testEnsureObject
    * @expectedException LogicException
    */
   public function testEnsureObjectWithoutObject()
   {
      $non_object = null;
      ensure_object($non_object, ':p');
   }


   public function testEnsureNonNull()
   {
      $non_nulls = [
         false,
         0    ,
         0.0  ,
         ''   ,
         []   ,

         function() { echo 'testEnsureNonNull'; },
      ];
      foreach ($non_nulls as $non_null) {
         ensure_non_null($non_null, 'this');
      }
   }
   /**
    * @depends           testEnsureNonNull
    * @expectedException LogicException
    */
   public function testEnsureNonNullWithNull()
   {
      $null = null;
      ensure_non_null($null, 'this');
   }

   public function testEnsureNonEmpty()
   {
      $non_empties = [
         true,
         1   ,
         0.1 ,
         'a' ,
         [1] ,
      ];
      foreach ($non_empties as $non_empty) {
         ensure_non_empty($non_empty, 'This line is passed!');
      }
   }
   /**
    * @depends           testEnsureNonEmpty
    * @expectedException LogicException
    */
   public function testEnsureNonEmptyWithNull()
   {
      $subject = null;
      ensure_non_empty($subject, 'The subject');
   }
   /**
    * @depends           testEnsureNonEmpty
    * @expectedException LogicException
    */
   public function testEnsureNonEmptyWithFalse()
   {
      $subject = false;
      ensure_non_empty($subject, 'The subject');
   }
   /**
    * @depends           testEnsureNonEmpty
    * @expectedException LogicException
    */
   public function testEnsureNonEmptyWithZero()
   {
      $subject = 0;
      ensure_non_empty($subject, 'The subject');
   }
   /**
    * @depends           testEnsureNonEmpty
    * @expectedException LogicException
    */
   public function testEnsureNonEmptyWithZeroDotZero()
   {
      $subject = 0.0;
      ensure_non_empty($subject, 'The subject');
   }
   /**
    * @depends           testEnsureNonEmpty
    * @expectedException LogicException
    */
   public function testEnsureNonEmptyWithEmptyString()
   {
      $subject = '';
      ensure_non_empty($subject, 'The subject');
   }
   /**
    * @depends           testEnsureNonEmpty
    * @expectedException LogicException
    */
   public function testEnsureNonEmptyWithEmptyArray()
   {
      $subject = [];
      ensure_non_empty($subject, 'The subject');
   }

   public function testEnsurePositiveInt()
   {
      $positive_ints = [1, PHP_INT_MAX];
      foreach ($positive_ints as $positive_int) {
         ensure_positive_int($positive_int, 'This line will be passed!');
      }
   }
   /**
    * @depends           testEnsurePositiveInt
    * @expectedException LogicException
    */
   public function testEnsurePositiveIntWithZero()
   {
      $non_positive = 0;
      ensure_positive_int($non_positive, 'next to zero');
   }
   /**
    * @depends           testEnsurePositiveInt
    * @expectedException LogicException
    */
   public function testEnsurePositiveIntWithMinInt()
   {
      $non_positive = PHP_INT_MIN;
      ensure_positive_int($non_positive, 'next to min int');
   }
   /**
    * @depends           testEnsurePositiveInt
    * @expectedException LogicException
    */
   public function testEnsurePositiveIntWithoutInt()
   {
      $non_int = 1.0;
      ensure_positive_int($non_int, 'next to non-int');
   }

   public function testEnsureNonNegativeInt()
   {
      $non_negative_ints = [0, PHP_INT_MAX];
      foreach ($non_negative_ints as $non_negative_int) {
         ensure_non_negative_int($non_negative_int, 'This line will be passed!');
      }
   }
   /**
    * @depends           testEnsureNonNegativeInt
    * @expectedException LogicException
    */
   public function testEnsureNonNegativeIntWithMinusOne()
   {
      $negative = -1;
      ensure_non_negative_int($negative, 'next to -1');
   }
   /**
    * @depends           testEnsureNonNegativeInt
    * @expectedException LogicException
    */
   public function testEnsureNonNegativeIntWithMinInt()
   {
      $negative = PHP_INT_MIN;
      ensure_non_negative_int($negative, 'next to min int');
   }
   /**
    * @depends           testEnsureNonNegativeInt
    * @expectedException LogicException
    */
   public function testEnsureNonNegativeIntWithoutInt()
   {
      $non_int = '1';
      ensure_non_negative_int($non_int, 'next to non-int');
   }


   private $blowsers = ['chrome', 'firefox', 'safari'];

   public function testEnsureInArray()
   {
      foreach ($this->blowsers as $blowser) {
         ensure_in_array($blowser, $this->blowsers, 'This line will be passed!');
      }
   }
   /**
    * @depends           testEnsureInArray
    * @expectedException LogicException
    */
   public function testEnsureInArrayWithoutElementInArray()
   {
      $not_in_array = 'ie';
      ensure_in_array($not_in_array, $this->blowsers, '?');
   }

   public function testEnsureNotInArray()
   {
      $non_in_array = 'ie';
      ensure_not_in_array($non_in_array, $this->blowsers, '?');
   }
   /**
    * @depends           testEnsureNotInArray
    * @expectedException LogicException
    */
   public function testEnsureNotInArrayWithElementInArray()
   {
      $in_array = 'chrome';
      ensure_not_in_array($in_array, $this->blowsers, ':)');
   }
}
