<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

set_jp_encoding();

class StringTest extends PHPUnit_Framework_TestCase
{
   private $platitude    = 'hello, world!';
   private $mb_platitude = 'こんにちは、世界！';


   function testWrap()
   {
      $wrapper = '/';
      $this->assertEquals("$wrapper{$this->platitude}$wrapper", wrap($this->platitude, $wrapper));
   }

   function testWrapByTag()
   {
      $tag   = 'p';
      $class = 'greeting';
      $this->assertEquals("<$tag>{$this->platitude}</$tag>"                    , wrap_by_tag($this->platitude   , $tag        ));
      $this->assertEquals("<$tag class=\"$class\">{$this->mb_platitude}</$tag>", wrap_by_tag($this->mb_platitude, $tag, $class));
   }

   function testFollowJoin()
   {
      $eol      = PHP_EOL;
      $expected = "{$this->platitude}$eol{$this->mb_platitude}$eol";
      $this->assertEquals($expected, follow_join($eol, [$this->platitude, $this->mb_platitude]));
   }


   function testStartWith()
   {
      $patterns = [
         [true , $this->platitude, 'hello'],
         [false, $this->platitude, 'ello,'],

         [true , $this->mb_platitude, 'こんにちは'],
         [false, $this->mb_platitude, 'んにちは、'],
      ];
      foreach ($patterns as list($expected, $haystack, $needle)) {
         $this->assertEquals($expected, start_with($haystack, $needle));
      }
   }

   function testEndWith()
   {
      $patterns = [
         [true , $this->platitude, 'world!'],
         [false, $this->platitude, ' world'],

         [true , $this->mb_platitude, '世界！'],
         [false, $this->mb_platitude, '、世界'],
      ];
      foreach ($patterns as list($expected, $haystack, $needle)) {
         $this->assertEquals($expected, end_with($haystack, $needle));
      }
   }


   function testSplitAt()
   {
      $patterns = [
         [['', 'hello, world!'], $this->platitude, -14],
         [['', 'hello, world!'], $this->platitude, -13],
         [['h', 'ello, world!'], $this->platitude, -12],
         [['hello, world', '!'], $this->platitude, - 1],
         [['', 'hello, world!'], $this->platitude,   0],
         [['h', 'ello, world!'], $this->platitude,   1],
         [['hello, world', '!'], $this->platitude,  12],
         [['hello, world!', ''], $this->platitude,  13],
         [['hello, world!', ''], $this->platitude,  14],

         [['', 'こんにちは、世界！'], $this->mb_platitude, -10],
         [['', 'こんにちは、世界！'], $this->mb_platitude, - 9],
         [['こ', 'んにちは、世界！'], $this->mb_platitude, - 8],
         [['こんにちは、世界', '！'], $this->mb_platitude, - 1],
         [['', 'こんにちは、世界！'], $this->mb_platitude,   0],
         [['こ', 'んにちは、世界！'], $this->mb_platitude,   1],
         [['こんにちは、世界', '！'], $this->mb_platitude,   8],
         [['こんにちは、世界！', ''], $this->mb_platitude,   9],
         [['こんにちは、世界！', ''], $this->mb_platitude,  10],
      ];
      foreach ($patterns as list($expected, $string, $at)) {
         $this->assertEquals($expected, split_at($string, $at));
      }
   }

   function testMbStrSplit()
   {
      $patterns = [
         [['h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'], $this->platitude,  1],
         [['he', 'll', 'o,', ' w', 'or', 'ld', '!']                        , $this->platitude,  2],
         [['hel', 'lo,', ' wo', 'rld', '!']                                , $this->platitude,  3],
         [['hell', 'o, w', 'orld', '!']                                    , $this->platitude,  4],
         [['hello', ', wor', 'ld!']                                        , $this->platitude,  5],
         [['hello,', ' world', '!']                                        , $this->platitude,  6],
         [['hello, ', 'world!']                                            , $this->platitude,  7],
         [['hello, w', 'orld!']                                            , $this->platitude,  8],
         [['hello, wo', 'rld!']                                            , $this->platitude,  9],
         [['hello, wor', 'ld!']                                            , $this->platitude, 10],
         [['hello, worl', 'd!']                                            , $this->platitude, 11],
         [['hello, world', '!']                                            , $this->platitude, 12],
         [['hello, world!']                                                , $this->platitude, 13],

         [['こ', 'ん', 'に', 'ち', 'は', '、', '世', '界', '！'], $this->mb_platitude, 1],
         [['こん', 'にち', 'は、', '世界', '！']                , $this->mb_platitude, 2],
         [['こんに', 'ちは、', '世界！']                        , $this->mb_platitude, 3],
         [['こんにち', 'は、世界', '！']                        , $this->mb_platitude, 4],
         [['こんにちは', '、世界！']                            , $this->mb_platitude, 5],
         [['こんにちは、', '世界！']                            , $this->mb_platitude, 6],
         [['こんにちは、世', '界！']                            , $this->mb_platitude, 7],
         [['こんにちは、世界', '！']                            , $this->mb_platitude, 8],
         [['こんにちは、世界！']                                , $this->mb_platitude, 9],
      ];
      foreach ($patterns as list($expected, $string, $width)) {
         $this->assertEquals($expected, mb_str_split($string, $width));
      }
   }


   private $blanks = [
      ''    ,
      ' '   ,
      "\t"  ,
      //"\v"  ,
      "\r"  ,
      "\n"  ,
      "\r\n",
      "\f"  ,
      '　'  ,
   ];

   function testIsBlank()
   {
      foreach ($this->blanks as $blank) {
         $this->assertTrue(is_blank($blank));
      }
      $false_patterns = [
         '1' ,
         'a' ,
         'A' ,
         'あ',
      ];
      foreach ($false_patterns as $string) {
         $this->assertFalse(is_blank($string));
      }
   }

   function testMbTrim()
   {
      $expected = 'remain';
      foreach ($this->blanks as $blank) {
         $this->assertEquals($expected, mb_trim("{$blank}{$expected}{$blank}"));
      }
   }

   function testHaveMb()
   {
      $this->assertFalse(have_mb($this->platitude   ));
      $this->assertTrue (have_mb($this->mb_platitude));
      $this->assertTrue (have_mb('JAM パターン'     ));
   }
}
