[Variables]
Pk.MnIm=#@#Image\Null.png
; Head diagram of the Package (Path)
Pk.Info=Enhanced Rainmeter to-do list skin for everyday task tracking.
; Introduction of the Package
Pk.Vrsn=2.01 ZhuoEEEE
; Version on Display
Pk.VBld=1200
; Version Build (Actual Version)
Pk.Athr=ZhuoEEEE, Codex-gpt5.5 (based on Quanto Flx by Steve Hsu)
; Author
Pk.SpTo=2.00 Delta
; Supported version of Quanto Flx
Pk.SpVB=1101
; Supported version build of Quanto Flx
Pk.Wbst.Hd=0
; Hide "Website" entry
Pk.Wbst=https://github.com/ZhuoEEEE/ToDoTasks
; Website URL

Sl.Tt=#Tm.Quanto_Flx_Gadgets#
Sl.SuTt.0=#Tm.Skin_List#
Sl.SuTt.1=#Tm.Backup_and_Restore#
Sl.SuTt.2=#Tm.About#
Sl.SuTt.3=
Sl.SuTt.4=
Sl.SuTt.5=
Sl.SuTt.6=
Sl.SuTt.7=
Sl.SuTt.8=
Sl.SuTt.9=

;============ Settings of "Restoring from an older version of backup" Feature ============

; Do users be allowed to "restore from an older version of backup"?
;   0 - No
;   1 - Yes
Rs.AlowRstr=1

; At a minimum, which version of Build is this version compatible with?
Rs.VBldLmtt=1100

; Do you need to exclude files or folders when restoring?
;   0 - No
;   1 - Yes
; If "1" is written, you should fill in the phrase of the file name to be excluded in 
; "RestoreExclusion.txt" (SAVE IT IN UTF-8 ENCODING).
; For example, if you need to exclude "SampleSkin1" and "SampleSkin2", you should write in
; this file (without semicolon and space):
; SampleSkin1
; SampleSkin2
; This will exclude files with the above keywords in their names when performing a restore 
; operation, and the related clone skin setting files will not be restored.
Rs.ExclNeed=0

; Describe why these folders or files are excluded.
;   Example: They are not compatible with the new version
; If you don't need it, leave it blank.
Rs.ExclRasn=
