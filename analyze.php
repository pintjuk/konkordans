<?php

$f = fopen("php://stdin", "r");

$s = array(
	'total' => 0,
	'maxlength' => 0,
	'unique' => 0,
	'unique3' => 0,
);

$known = $known3 = array();

$buffer = $maxword = '';

$no = 0;

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

foreach($known as $word => $void) {
	$word = substr($word, 0, 3);
	if (!isset($known3[$word])) {
		$known3[$word] = 0;
		$s['unique3']++;
	}
	$known3[$word]++;
}

arsort($known);
arsort($known3);

echo "Last word: ".$word." (".$maxword.")\n";

echo "Saving words...\n";
file_put_contents("unique.txt", print_r($known, true));
file_put_contents("unique3.txt", print_r($known3, true));
print_r($s);
echo "\n";

?>
