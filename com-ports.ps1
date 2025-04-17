Add-Type -AssemblyName PresentationFramework
$ports = Get-WmiObject Win32_SerialPort | Select-Object Name | Out-String
[System.Windows.MessageBox]::Show($ports)