[Rainmeter]
DynamicVariables=1
AccurateText=1
Update=-1
RightMouseUpAction=[!SkinCustomMenu]

ContextTitle=[#CmLs.[#CM].T01]
ContextTitle2=[#CmLs.[#CM].T02]
ContextTitle3=[#CmLs.[#CM].T03]
ContextTitle4=[#CmLs.[#CM].T04]
ContextTitle5=[#CmLs.[#CM].T05]
ContextTitle6=[#CmLs.[#CM].T06]
ContextTitle7=[#CmLs.[#CM].T07]
ContextTitle8=[#CmLs.[#CM].T08]
ContextTitle9=[#CmLs.[#CM].T09]
ContextTitle10=[#CmLs.[#CM].T10]
ContextTitle11=[#CmLs.[#CM].T11]
ContextTitle12=[#CmLs.[#CM].T12]
ContextTitle13=[#CmLs.[#CM].T13]
ContextTitle14=[#CmLs.[#CM].T14]
ContextTitle15=[#CmLs.[#CM].T15]
ContextTitle16=[#CmLs.[#CM].T16]
ContextTitle17=[#CmLs.[#CM].T17]
ContextTitle18=[#CmLs.[#CM].T18]
ContextTitle19=[#CmLs.[#CM].T19]
ContextTitle20=[#CmLs.[#CM].T20]
ContextTitle21=[#CmLs.[#CM].T21]
ContextTitle22=[#CmLs.[#CM].T22]
ContextTitle23=[#CmLs.[#CM].T23]
ContextTitle24=[#CmLs.[#CM].T24]
ContextTitle25=[#CmLs.[#CM].T25]
ContextAction=[#CmLs.[#CM].A01]
ContextAction2=[#CmLs.[#CM].A02]
ContextAction3=[#CmLs.[#CM].A03]
ContextAction4=[#CmLs.[#CM].A04]
ContextAction5=[#CmLs.[#CM].A05]
ContextAction6=[#CmLs.[#CM].A06]
ContextAction7=[#CmLs.[#CM].A07]
ContextAction8=[#CmLs.[#CM].A08]
ContextAction9=[#CmLs.[#CM].A09]
ContextAction10=[#CmLs.[#CM].A10]
ContextAction11=[#CmLs.[#CM].A11]
ContextAction12=[#CmLs.[#CM].A12]
ContextAction13=[#CmLs.[#CM].A13]
ContextAction14=[#CmLs.[#CM].A14]
ContextAction15=[#CmLs.[#CM].A15]
ContextAction16=[#CmLs.[#CM].A16]
ContextAction17=[#CmLs.[#CM].A17]
ContextAction18=[#CmLs.[#CM].A18]
ContextAction19=[#CmLs.[#CM].A19]
ContextAction20=[#CmLs.[#CM].A20]
ContextAction21=[#CmLs.[#CM].A21]
ContextAction22=[#CmLs.[#CM].A22]
ContextAction23=[#CmLs.[#CM].A23]
ContextAction24=[#CmLs.[#CM].A24]
ContextAction25=[#CmLs.[#CM].A25]

MouseActionCursor=0
DefaultKeepOnScreen=0
BackgroundMode=2
SolidColor=0,0,0,(#EzSl#)
SelectedColor=#Cl.Ac.R#,#Cl.Ac.G#,#Cl.Ac.B#,128

[Variables]
Project.Name=Quanto Flx
Null=0
Lorem=Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Quis ipsum suspendisse ultrices gravida. Risus commodo viverra maecenas accumsan lacus vel facilisis. 

Pk@=#@#Package\@\
Ac.Variants=[!SetVariable "CM" "#Sk.Nm#.CMStyle"][!Delay 16][!Update][!SkinCustomMenu][!Delay 16][!Update][!SetVariable "CM" "#Sk.Nm#.CMCommon"][!Update]
Ac.Skin_Settings=[!ZPos 1][!KeepOnScreen 1][!WriteKeyValue "Variables" "PrvConfig" "#CURRENTFILE#" "#CURRENTSKINSETTINGS#"][!ActivateConfig "#CURRENTCONFIG#" "Settings.ini"]
Ac.Manage_Project=[]
Ac.Refresh=[!Refresh]
Ac.Unload.RPSAU_0=
Ac.Unload.RPSAU_1=[!Move 0 0]
Ac.Unload=[!DeactivateConfig "#CURRENTCONFIG#"][#Ac.Unload.RPSAU_[#RPSAU]]
Ac.More=[!SkinMenu "#CURRENTCONFIG#"]
Tf_0=%#I:%M
Tf_1=%#H:%M
Tf_0_Ex=%#I:%M %p
Tf_1_Ex=%#H:%M
Tf_0_AMPM=%p
Tf_1_AMPM=" "

@include=#@#Config\Settings.inc
@include2=#@#Config\Language\en-us\Terms.inc
@include3=#@#Config\Language\#Lg#\Terms.inc
Cl.Ac.Ar=((#Cl.Ac.R#+#Cl.Ac.G#+#Cl.Ac.B#)/3)
; Average Value of Accent Color ((R+G+B)/3)
@include4=#@#Config\ColorScheme\#Cl.Sh#\#Sk.Ty#.inc

CM=#Sk.Nm#.CMCommon

Da.Sk=StrokeWidth 0 | Stroke Color 0,0,0,0
; Disable Stroke
Da.Bg=Fill Color 0,0,0,0
; To make a Blank Shape, usually used in Restricted Zone

Fl.Cl.Bd=Fill Color #Cl.Gn.Fg.Sd#,(128*#Op.Bd#*#Op.Bg_Cstm#)
; Fill in Borders color
Fl.Cl.Ob=Fill Color #Cl.Gn.Fg.Gn#,(32*#Cl.SwBd#)
; Fill in Option Borders color

Cl.Cb.-1=#Cl.Gn.Fg.Gn#
Cl.Cb.0=#Cl.Gn.Fg.Gn#
Cl.Cb.1=#Cl.Ac.Bg.Gn#
; Check Box Color

MOA.TcMd_00=[]
MLA.TcMd_00=[]
MOA.TcMd_01=[]
MLA.TcMd_01=[]
MOA.TcMd_10=[]
MLA.TcMd_10=[]
MOA.TcMd_11=[!ShowMeterGroup "Gp.MvBts"][!Redraw]
MLA.TcMd_11=[!HideMeterGroup "Gp.MvBts"][!Redraw]

|Gl.MOA|.Em_0=[!SetTransparency "(255*(#RmSk.Op#+(1-#RmSk.Op#)/4))"][!Delay 16][!SetTransparency "(255*(#RmSk.Op#+(1-#RmSk.Op#)*2/4))"][!Delay 16][!SetTransparency "(255*(#RmSk.Op#+(1-#RmSk.Op#)3*/4))"][!Delay 16][!SetTransparency "(255)"]
|Gl.MLA|.Em_0=[!SetTransparency "(255*(#RmSk.Op#+(1-#RmSk.Op#)*3/4))"][!Delay 16][!SetTransparency "(255*(#RmSk.Op#+(1-#RmSk.Op#)*2/4))"][!Delay 16][!SetTransparency "(255*(#RmSk.Op#+(1-#RmSk.Op#)/4))"][!Delay 16][!SetTransparency "(255*#RmSk.Op#)"]
|Gl.MOA|.Em_1=[!SetTransparency "(255)"]
|Gl.MLA|.Em_1=[!SetTransparency "(255*#RmSk.Op#)"]

GdntHv=270 | #Cl.Gn.Fg.Gn#,(12+52*((#Hl.Op#=0)?0:1)) ; 0.0 | #Cl.Gn.Fg.Gn#,(12+20*((#Hl.Op#=0)?0:1)) ; ((#Hl.Op#=0)?-1:0.499) | #Cl.Ac.Bg.Gn#,12 ; ((#Hl.Op#=0)?-1:0.5) | #Cl.Ac.Bg.Gn#,64 ; ((#Hl.Op#=0)?-1:1)

CURRENTSKINSETTINGS=#Pk@#Config\SkinSettings\#Sk.Nm#.inc

[St.Ft]
; Global Font Style
FontFace=#Ft.Fc.Gn#
FontSize=(10*#Sc#*#Ft.Sc.Gn#)
FontColor=#Cl.Gn.Fg.Gn#,(255*#Op.Fg#)
FontWeight=(Clamp(#Ft.Wt.Gn#,1,999))
AntiAlias=1
DynamicVariables=1

[St.Ft.Bd]
; Make the text (Global Font) Bolder. Must be used with "St.Ft"
FontWeight=(Clamp((#Ft.Wt.Gn#+#Ft.Wt.Bd#),1,999))

[St.Sl]
; Protect text (Global Font) or Monochrome Icons from "Op.Fg". Must be used with "St.Ft" or "St.Mi"
FontColor=#Cl.Gn.Fg.Gn#
ImageTint=#Cl.Gn.Fg.Gn#

[St.Ft.Ww]
; Word warp. Must be used with "St.Ft"
ClipString=2

[St.Ft.Splk]
; Superlink Style. Must be used with "St.Ft"
FontColor=#Cl.Ac.Bg.Gn#,(255*#Op.Fg#)
InlineSetting=None
InlineSetting2=None
InlinePattern=.*
InlinePattern2=.*
MouseActionCursor=1
MouseActionCursorName=HAND
MouseOverAction=[!SetOption #CURRENTSECTION# "InlineSetting" "Underline"][!SetOption #CURRENTSECTION# "InlineSetting2" "Color | #Cl.Ac.Bg.Gn#"][!Delay 16][!UpdateMeter "#CURRENTSECTION#"][!Redraw]
MouseLeaveAction=[!SetOption #CURRENTSECTION# "InlineSetting" "None"][!SetOption #CURRENTSECTION# "InlineSetting2" "None"][!Delay 16][!UpdateMeter "#CURRENTSECTION#"][!Redraw]
LeftMouseUpAction=[]

[St.Ft.Splk.Sl]
; Superlink Style, protecting text from "Op.Fg". Must be used with "St.Ft"
FontColor=#Cl.Ac.Bg.Gn#
InlineSetting=Underline
InlinePattern=.*
MouseActionCursor=1
MouseActionCursorName=HAND
LeftMouseUpAction=[]

[St.Ft.CmTxFm]
; Quanto Flx Common Text Formats (QFCTF). Must be used with "St.Ft"
InlinePattern=//[\s\S]*?//
InlineSetting=Italic
InlinePattern2=\*\*[\s\S]*?\*\*
InlineSetting2=Weight | (Clamp((#Ft.Wt.Gn#+#Ft.Wt.Bd#),1,999))
InlinePattern3=__[\s\S]*?__
InlineSetting3=Underline
InlinePattern4=--[\s\S]*?--
InlineSetting4=Strikethrough
InlinePattern5=``[\s\S]*?``
InlineSetting5=Face | Consolas
InlinePattern6=@@[\s\S]*?@@
InlineSetting6=Color | #Cl.Ac.Bg.Gn#
InlinePattern7=\^\^[\s\S]*?\^\^
InlineSetting7=Case | Upper
InlinePattern8=\++1[\s\S]*?\++1
InlineSetting8=Size | (11.73*#Sc#*#Ft.Sc.Gn#)
InlinePattern9=\++2[\s\S]*?\++2
InlineSetting9=Size | (13.7*#Sc#*#Ft.Sc.Gn#)
InlinePattern10=\++3[\s\S]*?\++3
InlineSetting10=Size | (16*#Sc#*#Ft.Sc.Gn#)
InlinePattern11=\+-1[\s\S]*?\+-1
InlineSetting11=Size | (8.55*#Sc#*#Ft.Sc.Gn#)
InlinePattern12=\+-2[\s\S]*?\+-2
InlineSetting12=Size | (7.29*#Sc#*#Ft.Sc.Gn#)
InlinePattern13=\+-3[\s\S]*?\+-3
InlineSetting13=Size | (6.2*#Sc#*#Ft.Sc.Gn#)
InlinePattern14=@\^0[\s\S]*?@\^0
InlineSetting14=Color | 0,0,0
InlinePattern15=@\^1[\s\S]*?@\^1
InlineSetting15=Color | 170,0,0
InlinePattern16=@\^2[\s\S]*?@\^2
InlineSetting16=Color | 170,85,0
InlinePattern17=@\^3[\s\S]*?@\^3
InlineSetting17=Color | 0,170,0
InlinePattern18=@\^4[\s\S]*?@\^4
InlineSetting18=Color | 0,170,170
InlinePattern19=@\^5[\s\S]*?@\^5
InlineSetting19=Color | 0,0,170
InlinePattern20=@\^6[\s\S]*?@\^6
InlineSetting20=Color | 170,0,170
InlinePattern21=@\^7[\s\S]*?@\^7
InlineSetting21=Color | 170,170,170
InlinePattern22=@\^8[\s\S]*?@\^8
InlineSetting22=Color | 85,85,85
InlinePattern23=@\^9[\s\S]*?@\^9
InlineSetting23=Color | 255,85,85
InlinePattern24=@\^A[\s\S]*?@\^A
InlineSetting24=Color | 255,255,85
InlinePattern25=@\^B[\s\S]*?@\^B
InlineSetting25=Color | 85,255,85
InlinePattern26=@\^C[\s\S]*?@\^C
InlineSetting26=Color | 85,255,255
InlinePattern27=@\^D[\s\S]*?@\^D
InlineSetting27=Color | 85,85,255
InlinePattern28=@\^E[\s\S]*?@\^E
InlineSetting28=Color | 255,85,255
InlinePattern29=@\^F[\s\S]*?@\^F
InlineSetting29=Color | 255,255,255
InlinePattern30=\*\*|//|__|--|``|\^\^|@@|@\^[(0-9)|(A-F)]|\+[\+\-][123]
InlineSetting30=Size | 0.0001
InlinePattern31=(?<=[\*/_-`\^@\+])\\
InlineSetting31=Size | 0.0001
InlinePattern32=#CRLF##CRLF#
InlineSetting32=Size | (5*#sc#*#Ft.Sc.Gn#)

[St.Rz]
; Restricted Zone Style
LeftMouseUpAction=[]
LeftMouseDownAction=[]
RightMouseUpAction=[]
RightMouseDownAction=[]
DynamicVariables=1

[St.Mi]
; Monochrome Icon Style
ImageTint=#Cl.Gn.Fg.Gn#,(255*#Op.Fg#)
SolidColor=0,0,0,1
AntiAlias=1
DynamicVariables=1

[St.Hv]
; Hover Style
Hidden=1

[St.Bt.Gn]
; Button Style, in response to one Hover Meter
MouseOverAction=[!ShowMeter H#CURRENTSECTION#][!Redraw]
MouseLeaveAction=[!HideMeter H#CURRENTSECTION#][!Redraw]
DynamicVariables=1

[St.Bt.Mt]
; Button Style, in response to multiple Hover Meters in a Group
MouseOverAction=[!ShowMeterGroup H#CURRENTSECTION#][!Redraw]
MouseLeaveAction=[!HideMeterGroup H#CURRENTSECTION#][!Redraw]
DynamicVariables=1

[St.Bt.Sp]
; Button Style, for "Shape" Meters ONLY
; Hover shape must be defined
Hover=#Da.Bg#
GdntHv=#GdntHv#
MouseOverAction=[!SetOption "#CURRENTSECTION#" "Hover" "#Fl.Cl.Hv#"][!UpdateMeter "#CURRENTSECTION#"][!Redraw]
MouseLeaveAction=[!SetOption "#CURRENTSECTION#" "Hover" "#Da.Bg#"][!UpdateMeter "#CURRENTSECTION#"][!Redraw]
DynamicVariables=1

[St.MOAHdCs]
; Change the shape of the mouse to a hand shape when it passes over the meter
LeftMouseUpAction=[]
MouseActionCursor=1
MouseActionCursorName=HAND

[St.WrngIm]
; Warning icon style
ImageName=#@#Image\MonoIcons\32\Warning
W=(32*#sc#)
H=(32*#sc#)
X=(#CURRENTCONFIGWIDTH#/2-16*#sc#)
Y=(#CURRENTCONFIGHEIGHT#/2-16*#sc#)
DynamicVariables=1
Hidden=1
ToolTipTitle=Text
ToolTipText=Text

[St.ZnCt]
; Set "Mt.Zn" as a container
Container=Mt.Zn
DynamicVariables=1
[St.ZnCt2]
; Set "Mt.Zn2" as a container
Container=Mt.Zn2
DynamicVariables=1
[St.ZnCt3]
; Set "Mt.Zn3" as a container
Container=Mt.Zn3
DynamicVariables=1
[St.ZnCt4]
; Set "Mt.Zn4" as a container
Container=Mt.Zn4
DynamicVariables=1

[St.Rsz]
; The entry of "Quick Resizing". Must be used with "St.Mi"
; Modifiy "LeftMouseDownAction" or "MouseActionCursorName" if necessary
ImageName=#@#Image\MonoIcons\16\Resize
X=(#CURRENTCONFIGWIDTH#-24*#sc#)
Y=(#CURRENTCONFIGHEIGHT#-24*#sc#)
W=(16*#sc#)
H=(16*#sc#)
LeftMouseDownAction=[!Delay 500][!ActivateConfig "#CURRENTCONFIG#" "Resizing.ini"]
MouseActionCursor=1
MouseActionCursorName=SIZE_NWSE
Hidden=1
