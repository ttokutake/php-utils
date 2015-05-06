<?php

require_once implode(DIRECTORY_SEPARATOR, [__DIR__, '..', 'php-utils.php']);

set_jp_encoding();

class StringTest extends PHPUnit_Framework_TestCase
{
   private $platitude    = 'hello, world!';
   private $mb_platitude = 'こんにちは、世界！';


   public function testWrap()
   {
      $wrapper = '/';
      $this->assertEquals("$wrapper{$this->platitude}$wrapper", wrap($this->platitude, $wrapper));
   }

   public function testWrapByTag()
   {
      $tag   = 'p';
      $class = 'greeting';
      $this->assertEquals("<$tag>{$this->platitude}</$tag>", wrap_by_tag($this->platitude, $tag));
      $this->assertEquals("<$tag class=\"$class\">$this->mb_platitude</$tag>", wrap_by_tag($this->mb_platitude, $tag, $class));
   }

   public function testFollowJoin()
   {
      $eol      = PHP_EOL;
      $expected = "{$this->platitude}$eol{$this->mb_platitude}$eol";
      $this->assertEquals($expected, follow_join($eol, [$this->platitude, $this->mb_platitude]));
   }


   public function testStartWith()
   {
      $patterns = [
         [true , $this->platitude   , 'hello'     ],
         [false, $this->platitude   , 'ello,'     ],
         [true , $this->mb_platitude, 'こんにちは'],
         [false, $this->mb_platitude, 'んにちは、'],
      ];
      foreach ($patterns as list($expected, $haystack, $needle)) {
         $this->assertEquals($expected, start_with($haystack, $needle));
      }
   }

   public function testEndWith()
   {
      $patterns = [
         [true , $this->platitude   , 'world!'],
         [false, $this->platitude   , ' world'],
         [true , $this->mb_platitude, '世界！'],
         [false, $this->mb_platitude, '、世界'],
      ];
      foreach ($patterns as list($expected, $haystack, $needle)) {
         $this->assertEquals($expected, end_with($haystack, $needle));
      }
   }


   public function testSplitAt()
   {
      $patterns = [
         [['', 'hello, world!'], -14],
         [['', 'hello, world!'], -13],
         [['h', 'ello, world!'], -12],
         [['hello, world', '!'], - 1],
         [['', 'hello, world!'],   0],
         [['h', 'ello, world!'],   1],
         [['hello, world', '!'],  12],
         [['hello, world!', ''],  13],
         [['hello, world!', ''],  14],
      ];
      foreach ($patterns as list($expected, $at)) {
         $this->assertEquals($expected, split_at($this->platitude, $at));
      }
      $mb_patterns = [
         [['', 'こんにちは、世界！'], -10],
         [['', 'こんにちは、世界！'], - 9],
         [['こ', 'んにちは、世界！'], - 8],
         [['こんにちは、世界', '！'], - 1],
         [['', 'こんにちは、世界！'],   0],
         [['こ', 'んにちは、世界！'],   1],
         [['こんにちは、世界', '！'],   8],
         [['こんにちは、世界！', ''],   9],
         [['こんにちは、世界！', ''],  10],
      ];
      foreach ($mb_patterns as list($expected, $at)) {
         $this->assertEquals($expected, split_at($this->mb_platitude, $at));
      }
   }

   public function testMbStrSplit()
   {
      $patterns = [
         [['h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'],  1],
         [['he', 'll', 'o,', ' w', 'or', 'ld', '!']                        ,  2],
         [['hel', 'lo,', ' wo', 'rld', '!']                                ,  3],
         [['hell', 'o, w', 'orld', '!']                                    ,  4],
         [['hello', ', wor', 'ld!']                                        ,  5],
         [['hello,', ' world', '!']                                        ,  6],
         [['hello, ', 'world!']                                            ,  7],
         [['hello, w', 'orld!']                                            ,  8],
         [['hello, wo', 'rld!']                                            ,  9],
         [['hello, wor', 'ld!']                                            , 10],
         [['hello, worl', 'd!']                                            , 11],
         [['hello, world', '!']                                            , 12],
         [['hello, world!']                                                , 13],
      ];
      foreach ($patterns as list($expected, $width)) {
         $this->assertEquals($expected, mb_str_split($this->platitude, $width));
      }
      $mb_patterns = [
         [['こ', 'ん', 'に', 'ち', 'は', '、', '世', '界', '！'], 1],
         [['こん', 'にち', 'は、', '世界', '！']                , 2],
         [['こんに', 'ちは、', '世界！']                        , 3],
         [['こんにち', 'は、世界', '！']                        , 4],
         [['こんにちは', '、世界！']                            , 5],
         [['こんにちは、', '世界！']                            , 6],
         [['こんにちは、世', '界！']                            , 7],
         [['こんにちは、世界', '！']                            , 8],
         [['こんにちは、世界！']                                , 9],
      ];
      foreach ($mb_patterns as list($expected, $width)) {
         $this->assertEquals($expected, mb_str_split($this->mb_platitude, $width));
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

   public function testIsBlank()
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

   public function testMbTrim()
   {
      $expected = 'remain';
      foreach ($this->blanks as $blank) {
         $this->assertEquals($expected, mb_trim("{$blank}{$expected}{$blank}"));
      }
   }

   public function testIncludeMb()
   {
      $this->assertFalse(include_mb($this->platitude   ));
      $this->assertTrue (include_mb($this->mb_platitude));
      $this->assertTrue (include_mb('JAM パターン'     ));
   }
}
