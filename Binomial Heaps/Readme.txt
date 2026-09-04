

1.file output:

Get-Content input2.txt | .\main.exe | Out-File output2.txt -Encoding utf8
2.compile:
 
g++ 2405010.cpp -o main.exe

3.main.exe deletion:
Stop-Process -Name main -Force -ErrorAction SilentlyContinue
Stop-Process -Name g++ -Force -ErrorAction SilentlyContinue
Remove-Item .\main.exe -Force 