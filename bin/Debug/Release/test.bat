Practice.exe < 01-example.input.txt > 01-example.actual.txt 2>NUL
fc /N 01-example.actual.txt 01-example.expected.txt
Practice.exe < 02-alignment.input.txt > 02-example.actual.txt 2>NUL
fc /N 02-example.actual.txt 02-alignment.expected.txt
Practice.exe < 03-scaling.input.txt > 03-example.actual.txt 2>NUL
fc /N 03-example.actual.txt 03-scaling.expected.txt || pause
