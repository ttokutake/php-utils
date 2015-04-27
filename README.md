# php-utils ![Build Status](https://travis-ci.org/ttokutake/php-utils.svg?branch=master)

## Requirements

- PHP 5.3 or higher
- But PHP 5.5 or higher if you want to try phpunit's tests.

## Licence

MIT Licence

## Example

```php
require_once PATH_TO_PHP_UTILS . 'php-utils.php';

$array = incremental_range(1, 10);

list($head, $tail) = array_behead($array);

echoln($head);
echo pretty($tail);
```
