 for compilation: g++ AVLTree.cpp -o avl_tree 

# 1. Force PowerShell to use UTF-8 for >> operators
$OutputEncoding = [System.Text.Encoding]::UTF8

# 2. Delete the corrupted file
Remove-Item timing_report.txt -ErrorAction SilentlyContinue

# 3. Create file cleanly using Out-File -Encoding utf8
"AVL" | Out-File -FilePath timing_report.txt -Encoding utf8

# 4. Append executable output using Out-File -Append
.\avl_tree.exe testcase_avl.txt output_avl.txt | Out-File -FilePath timing_report.txt -Encoding utf8 -Append



for compilation: g++ IntervalScheduler.cpp -o IntervalScheduler
# 1. Force PowerShell to use UTF-8 for >> operators
$OutputEncoding = [System.Text.Encoding]::UTF8

# 2. Delete the corrupted file
Remove-Item timing_report.txt -ErrorAction SilentlyContinue

# 3. Create file cleanly using Out-File -Encoding utf8
"Interval Scheduler" | Out-File -FilePath timing_report.txt -Encoding utf8 -Append

# 4. Append executable output using Out-File -Append
.\IntervalScheduler.exe testcase_basic_interval.txt output_basic_interval.txt | Out-File -FilePath timing_report.txt -Encoding utf8 -Append