# php-utils [![Build Status](https://travis-ci.org/ttokutake/php-utils.svg?branch=master)](https://travis-ci.org/ttokutake/php-utils) [![Coverage Status](https://coveralls.io/repos/ttokutake/php-utils/badge.png?branch=master)](https://coveralls.io/r/ttokutake/php-utils)


"php-utils" is the function group which extends [PHP](http://php.net/) standard functions.

This library is mainly affected by [Scala](http://www.scala-lang.org/).

"php-utils.php" define `create_path()` function, and read fllowing files.

| file name          | description                                                                                        |
|--------------------|----------------------------------------------------------------------------------------------------|
| cover.inc          | defines the functions which throw no exception                                                     |
| error.inc          | defines the functions which are usefull for throwing some exception                                |
| string.inc         | defines the functions which complement PHP standard functions for "string"                         |
| debug.inc          | defines the functions which help developers to debug                                               |
| general.inc        | defines the basic functions                                                                        |
| array.inc          | defines the functions which complement PHP standard functions for "array"                          |
| array_of_array.inc | defines the functions which help computations of "array" having "array" elements, like RDB records |

If you want to know details, go to [wiki page](https://github.com/ttokutake/php-utils/wiki/)!

## Requirements

- PHP 5.3 or higher
- But PHP 5.5 or higher if you want to try [PHPUnit](https://phpunit.de/) tests.

## Licence

MIT Licence

## Example
**example.php**

```php
<?php

require_once PATH_TO_PHP_UTILS . 'php-utils.php'; // you need to define PATH_TO_PHP_UTILS

$sample_array = [
   'null'    => null                            ,
   'boolean' => true                            ,
   'int'     => 1                               ,
   'double'  => 1.1                             ,
   'string'  => 'hello, world!'                 ,
   'array'   => [1, 2, 3]                       ,
   'closure' => function() { return 'closure'; },
];

echo pretty($sample_array);
```
The above code lead to the following result,
```bash
$ php example.php
[
   "null"    => null
   "boolean" => true
   "int"     => 1
   "double"  => 1.1
   "string"  => "hello, world!"
   "array"   => [
      0 => 1
      1 => 2
      2 => 3
   ]
   "closure" => object of Closure {
      object properties => [
      ]
      static properties => [
      ]
      methods           => [
         0 => "bind"
         1 => "bindTo"
      ]
   }
]
```
