#!/bin/bash
cat korpus | ./tokenizer | php tests.php 2> /dev/null
