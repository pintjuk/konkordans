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
	//Testa alltid hörnfall
	if (rand(1, 50) != 1 && strtolower($word) != ('a') && strtolower($word) != ('regering') && strtolower($word) != ('özkök') && strtolower($word) != ('özsoy') && $word != strtolower('för')) continue; //Only test 1 in 100 words
	echo "Testing ".$i." of ".count($known)."... (".$word.")                                    ";

	$testdata = trim(shell_exec("yes | ./search ".$word));
	if (count(explode("\n", $testdata)) != $no) {
		echo "\n";
		echo "TEST CASE FAILED FOR WORD: ".$word."\nWill not continue.\n";
		die();
	}

	echo "\r";
}
echo "\n";

?>
