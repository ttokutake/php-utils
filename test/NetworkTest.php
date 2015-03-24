<?php

require_once('constants.inc');
require_once(PATH_TO_LIB . 'network.inc');

class NetworkTest extends PHPUnit_Framework_TestCase
{
   public function testIsIpv4()
   {
      $ipv4s = [
         '0.0.0.0'        ,
         '9.9.9.9'        ,
         '10.10.10.10'    ,
         '99.99.99.99'    ,
         '100.100.100.100',
         '199.199.199.199',
         '200.200.200.200',
         '249.249.249.249',
         '255.255.255.255',

         '0.0.0.0/0' ,
         '0.0.0.0/9' ,
         '0.0.0.0/10',
         '0.0.0.0/29',
         '0.0.0.0/30',
         '0.0.0.0/32',
      ];
      foreach ($ipv4s as $ipv4) {
         $this->assertTrue(is_ipv4($ipv4));
      }

      $incorrects = [
         '-1.-1,-1.-1'    ,
         '00.00,00.00'    ,
         '000.000,000.000',
         '256.256,256.256',

         '0.0.0.0/-1',
         '0.0.0.0/33',
      ];
      foreach ($incorrects as $incorrect) {
         $this->assertFalse(is_ipv4($incorrect));
      }
   }
}
