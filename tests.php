<?php

$f = fopen("php://stdin", "r");

$s = array(
	'total' => 0,
	'maxlength' => 0,
	'unique' => 0,
);

$known = array();

$buffer = $maxword = '';

$no = 0;

echo "Reading output from tokenizer...\n";

while($row = fgets($f)) {
	$word = trim(explode(" ", $row)[0]);
	$s['total']++;

	if ($s['maxlength'] < strlen($word)) {
		$s['maxlength'] = strlen($word);
		$maxword = trim($word);
	}

	if (!isset($known[$word])) {
		$known[$word] = 0;
		$s['unique']++;
	}

	$known[$word]++;
	//echo $word."\n";
}

echo "Sorting data...\n";

arsort($known);

echo "Trying all words...\n";

$i = 0;
foreach($known as $word => $no) {
	++$i;
	echo "Testing ".$i." of ".count($known)."...";

	$testdata = trim(shell_exec("echo -n 'y' | ./search ".$word));
	if (!count(explode("\n", $testdata))) {
		echo "\n";
		echo "TEST CASE FAILED FOR WORD: ".$$word."\nWill not continue.\n";
	}

	echo "\r";
}
echo "\n";

?>
