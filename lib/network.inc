<?php

/**
 * Judge if the string is IPv4 (or CIDR).
 *
 * @param  string  $str
 * @return boolean
 */
function is_ipv4($str)
{
   static $byte = '(?:25[0-5]|2[0-4]\d|1\d\d|[1-9]\d|\d)';
   return preg_match("/^(?:$byte\.){3}$byte(?:\/(?:3[0-2]|[12]\d|\d))?$/", $str) == 1;
}

function in_cidr($ipv4, $cidr)
{
   return 'under construction';
}
