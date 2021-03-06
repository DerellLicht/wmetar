; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{D4AF460E-F4C5-4B13-89D9-0FCC414C1D5D}
AppName=WMetar
AppVerName=WMetar V1.00
AppPublisher=Cathartes Aura
AppPublisherURL=http://home.comcast.net/~derelict/
AppSupportURL=http://home.comcast.net/~derelict/
AppUpdatesURL=http://home.comcast.net/~derelict/
DefaultDirName={sd}\WMetar
DisableDirPage=no
DefaultGroupName=WMetar
OutputDir=Output
OutputBaseFilename=wmetar.setup
SetupIconFile=earth.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "wmetar.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "readme.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "stations.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "klvk.bat"; DestDir: "{app}"; Flags: ignoreversion
Source: "klvk.txt"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\WMetar"; Filename: "{app}\wmetar.exe"
Name: "{group}\Read Me"; Filename: "{app}\readme.txt"
Name: "{commondesktop}\WMetar"; Filename: "{app}\wmetar.exe"; Tasks: desktopicon


