$rows = Get-Content "src/app/AndroidPattern.cpp" | Where-Object { $_.Trim().StartsWith('"') }
foreach ($row in $rows) {
    $clean = $row.Trim().Trim('",')
    $clean = $clean.Replace('W',' ').Replace('B','#').Replace('G','@')
    Write-Host $clean
}
